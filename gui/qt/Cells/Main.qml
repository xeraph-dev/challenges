pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Window {
    id: window
    minimumWidth: edge.width + state.cellWidths[0]
    minimumHeight: edge.height + state.cellHeights[0]
    maximumWidth: edge.width + cells.width
    maximumHeight: edge.height + cells.height
    visible: true
    title: qsTr("Cells")

    Component.onCompleted: {
        width = 640
        height = 480
    }

    QtObject {
        id: state

        readonly property int columns: 8
        readonly property int rows: 24

        property list<int> cellWidths: Array.from({ length: columns }).map(() => 100)
        property list<int> cellHeights: Array.from({ length: rows }).map(() => 22)
        property list<CellData> cells: Array.from({ length: columns * rows }).map((_, index) => createCell(index))

        function createCell(index : int) : QtObject {
            const x = index % columns
            const y = Math.floor(index / columns)

            return cellDataComponent.createObject(this, { "point": Qt.point(x, y) })
        }

        function eof(str, idx) {
            return str.length <= idx
        }

        function tryScanNumber(str, idx) {
            if (eof(str, idx)) return [idx, null]
            if (!'-.0123456789'.includes(str[idx])) return [idx, null]

            const startIdx = idx

            const isNegative = str[idx] === "-"
            if (isNegative) idx++

            let hasDot = false

            while (!eof(str, idx)) {
                if (str[idx] >= "0" && str[idx] <= "9") idx++
                else if (str[idx] === ".") {
                    if (hasDot) throw new Error(`scan: invalid character at ${idx}: numbers can have one one dot`)
                    if (idx === 0) throw new Error(`scan: invalid character at ${idx}: numbers can not start with a dot (.)`)
                    if (isNegative && idx === 1) throw new Error(`scan: invalid character at ${idx}: negative numbers can not start with a dot (.)`)

                    hasDot = true
                    idx++
                } else {
                    break
                }
            }

            if (str[idx - 1] === ".") throw new Error(`scan: invalid character at ${idx}: numbers can not end with a dot (.)`)

            return [idx, { type: "number", value: str.slice(startIdx, idx) }]
        }

        function scanCell(str) {
            const tokens = []
            let token = null
            let idx = 0

            while (!eof(str, idx)) {
                if (token === null) [idx, token] = tryScanNumber(str, idx)
                if (token === null) throw new Error(`scan: unexpected character at ${idx}`)

                tokens.push(token)
                token = null
            }

            return tokens
        }

        function tryParseNumber(tokens, idx) {
            if (eof(tokens, idx)) return [idx, null]
            if (tokens[idx].type !== "number") return [idx, null]
            return [idx + 1, { type: "number", value: parseFloat(tokens[idx].value) }]
        }

        function tryParseExpression(tokens, idx) {
            let atom = null

            if (atom === null) [idx, atom] = tryParseNumber(tokens, idx)
            if (atom === null) throw new Error(`parse: unexpected token at ${idx}`)

            return [idx, atom]
        }

        function parseCell(tokens) {
            const ast = []

            let atom = null
            let idx = 0

            while (!eof(tokens, idx)) {
                ;[idx, atom] = tryParseExpression(tokens, idx)
                ast.push(atom)
            }

            return ast
        }

        function tryEvalNumber(atom) {
            if (atom.type !== "number") return null
            return atom.value
        }

        function evalCell(ast) {
            let value = null
            let idx = 0

            if (value === null) value = tryEvalNumber(ast[idx++])

            return value
        }

        function processCell(index) {
            let value = state.cells[index].value.trim()

            if (value.startsWith("=")) {
                try {
                    const tokens = scanCell(value.slice(1))
                    const ast = parseCell(tokens)
                    value = evalCell(ast).toString()
                } catch (error) {
                    console.log(error)
                    value = "error"
                }
            }

            state.cells[index].visualValue = value
        }
    }

    component CellData : QtObject {
        required property point point
        property string value: ""
        property string visualValue: ""
    }

    Component { id: cellDataComponent; CellData{} }

    component Cell : Rectangle {
        required property CellData cdata

        property alias text: cellInput.text

        signal edited
        signal finished

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.right: parent.right
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.bottom: parent.bottom
        }

        TextInput {
            id: cellInput

            anchors.fill: parent
            anchors.margins: 3

            activeFocusOnPress: false
            visible: focus

            text: parent.cdata.value
            onTextChanged: parent.edited()
            onFocusChanged: !focus && parent.finished()

            Keys.onReturnPressed: focus = false
        }

        Text {
            anchors.fill: parent
            anchors.margins: 3
            visible: !cellInput.focus

            text: parent.cdata.visualValue
        }

        MouseArea {
            anchors.fill: parent

            onClicked: cellInput.forceActiveFocus()
        }
    }

    component ColumnCell : Rectangle {
        required property int index

        color: "lightgrey"

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.right: parent.right
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.top: parent.top
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.bottom: parent.bottom
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 3
            text: String.fromCharCode(65 + parent.index)
        }
    }

    component RowCell : Rectangle {
        required property int index

        color: "lightgrey"

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.left: parent.left
        }

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.right: parent.right
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.bottom: parent.bottom
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.margins: 3
            text: parent.index + 1
        }
    }

    component EdgeCell : Rectangle {
        color: "lightgrey"

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.left: parent.left
        }

        Rectangle {
            width: 1
            height: parent.height
            color: "black"
            anchors.right: parent.right
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.top: parent.top
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "black"
            anchors.bottom: parent.bottom
        }
    }

    GridLayout {
        columns: 2
        rows: 2
        columnSpacing: 0
        rowSpacing: 0

        EdgeCell {
            id: edge

            implicitWidth: 30
            implicitHeight: 22
        }

        Flickable {
            Layout.preferredWidth: cellsScroll.width
            Layout.preferredHeight: edge.height

            interactive: false
            contentWidth: columnsLayout.width;
            contentHeight: columnsLayout.height
            clip: true
            contentX: cellsScroll.contentX

            Row {
                id: columnsLayout
                Repeater {
                    model: state.columns

                    ColumnCell {
                        width: state.cellWidths[index]
                        height: edge.height
                    }
                }
            }
        }

        Flickable {
            Layout.preferredWidth: edge.width
            Layout.preferredHeight: cellsScroll.height

            interactive: false
            contentWidth: rowsLayout.width;
            contentHeight: rowsLayout.height
            clip: true
            contentY: cellsScroll.contentY

            Column {
                id: rowsLayout
                Repeater {
                    model: state.rows

                    RowCell {
                        width: edge.width
                        height: state.cellHeights[index]
                    }
                }
            }
        }

        ScrollView {
            Layout.preferredWidth: Math.min(cells.width, window.width - edge.width)
            Layout.preferredHeight: Math.min(cells.height, window.height - edge.height)

            Flickable {
                id: cellsScroll

                contentWidth: cells.width
                contentHeight: cells.height
                clip: true
                boundsBehavior: Flickable.StopAtBounds

                Grid {
                    id: cells
                    columns: state.columns
                    rows: state.rows

                    Repeater {
                        model: state.columns * state.rows

                        Cell {
                            required property int index
                            cdata: state.cells[index]

                            width: state.cellWidths[cdata.point.x]
                            height: state.cellHeights[cdata.point.y]

                            onEdited: state.cells[index].value = text
                            onFinished: state.processCell(index)
                        }
                    }
                }
            }
        }
    }
}
