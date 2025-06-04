pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.Basic

import CircleDrawer

Window {
    minimumWidth: root.width
    minimumHeight: root.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Circle Drawer")

    UUIDGenerator { id: uuid }

    component CircleData : QtObject {
        required property string uid
        required property point center
        property real radius: 10
    }

    Component { id: circleDataComponent; CircleData {} }

    component HistoryAction : QtObject {
        function undo() {}
        function redo() {}
    }

    component HistoryAdd : HistoryAction {
        required property CircleData cdata

        function undo() {
            state.circles.pop()
        }

        function redo() {
            state.circles.push(cdata)
        }
    }

    Component { id: historyAddComponent; HistoryAdd {} }

    component HistorySelect : HistoryAction {
        required property string uid
        required property string prevUid

        function undo() {
            state.selected = state.circles.find(el => el.uid === prevUid) ?? null
        }

        function redo() {
            state.selected = state.circles.find(el => el.uid === uid) ?? null
        }
    }

    Component { id: historySelectComponent; HistorySelect {} }

    component HistoryUpdate : HistoryAction {
        required property string uid
        required property real radius
        required property real prevRadius

        function undo() {
            const index = state.circles.findIndex(el => el.uid === uid)
            state.circles[index].radius = prevRadius
        }

        function redo() {
            const index = state.circles.findIndex(el => el.uid === uid)
            state.circles[index].radius = radius
        }
    }

    Component { id: historyUpdateComponent; HistoryUpdate {} }

    component Circle : Rectangle {
        required property CircleData cdata
        property bool selected: false

        signal clicked

        width: cdata.radius * 2
        height: cdata.radius * 2
        radius: width / 2
        border.color: "black"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: cdata.center.y - cdata.radius
        anchors.leftMargin: cdata.center.x - cdata.radius
        color: selected ? "lightgrey" : "white"

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            propagateComposedEvents: true
            onClicked: mouse => {
                switch (mouse.button) {
                    case Qt.LeftButton: {
                        const vector = Qt.vector2d(mouse.x - parent.cdata.radius, mouse.y - parent.cdata.radius)
                        const center = Math.abs(vector.length())
                        if (center <= parent.cdata.radius) {
                            parent.clicked()
                        } else {
                            mouse.accepted = false
                        }
                        break
                    }
                    case Qt.RightButton: {
                        if (parent.selected) {
                            dialog.open()
                        }
                        break
                    }
                }
            }
        }
    }

    QtObject {
        id: state

        property CircleData selected: null
        property list<CircleData> circles: []
        property list<HistoryAction> history: []
        property int historyIndex: -1

        function add(center : point) {
            const data = circleDataComponent.createObject(this, { "uid": uuid.v4(), "center": center })
            circles.push(data)
            const action = historyAddComponent.createObject(this, { "cdata": data })
            addAction(action)
        }

        function select(cdata : CircleData) {
            const action = historySelectComponent.createObject(this, { "uid": cdata.uid, "prevUid": selected?.uid ?? null })
            selected = circleDataComponent.createObject(this, { "uid": cdata.uid, "center": cdata.center, "radius": cdata.radius })
            addAction(action)
        }

        function update() {
            const cdata = circles.find(el => el.uid === selected.uid)
            const action = historyUpdateComponent.createObject(this, { "uid": cdata.uid, "radius": cdata.radius, "prevRadius": selected.radius })
            selected.radius = cdata.radius
            addAction(action)
        }

        function addAction(action : HistoryAction) {
            historyIndex++
            history = history.slice(0, historyIndex)
            history.push(action)
        }

        function undo() {
            history[historyIndex].undo()
            historyIndex--
        }

        function redo() {
            historyIndex++
            history[historyIndex].redo()
        }
    }

    Column {
        id: root
        padding: 12
        spacing: 12

        Row {
            spacing: 12
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: "Undo"
                onClicked: state.undo()
                enabled: state.historyIndex >= 0
            }

            Button {
                text: "Redo"
                onClicked: state.redo()
                enabled: state.historyIndex + 1 < state.history.length
            }
        }

        Rectangle {
            width: 400
            height: 300
            clip: true

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onClicked: mouse => mouse.button === Qt.LeftButton && state.add(Qt.point(mouse.x, mouse.y))
            }

            Repeater {
                model: state.circles.length

                Circle {
                    required property int index
                    cdata: state.circles[index] ?? null
                    selected: state.selected?.uid === cdata?.uid
                    onClicked: state.select(cdata)
                }
            }

            Rectangle {
                anchors.fill: parent
                border.color: "black"
                color: "transparent"
            }
        }
    }

    Dialog {
        id: dialog
        modal: true

        onClosed: state.update()

        Column {
            readonly property int cindex: state.circles.findIndex(el => el.uid === state.selected?.uid)
            readonly property CircleData cdata: state.circles[cindex] ?? null

            Text {
                text: `Adjust diameter of circle at (${parent.cdata?.center.x.toFixed(0)}, ${parent.cdata?.center.y.toFixed(0)})`
            }

            Slider {
                from: 5
                value: parent.cdata?.radius ?? 10
                to: 20
                onMoved: state.circles[parent.cindex].radius = value
            }
        }
    }
}
