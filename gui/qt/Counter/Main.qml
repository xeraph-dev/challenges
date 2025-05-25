import QtQuick
import QtQuick.Controls.Basic

Window {
    minimumWidth: row.width
    minimumHeight: row.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Counter")

    Row {
        id: row
        spacing: 4
        padding: 12

        TextField {
            id: input
            text: "0"
            anchors.verticalCenter: parent.verticalCenter
            width: button.width
        }

        Button {
            id: button
            text: "Count"
            onClicked: input.text = ++input.text
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
