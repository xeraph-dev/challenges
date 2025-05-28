import QtQuick
import QtQuick.Controls.Basic

Window {
    id: window
    minimumWidth: column.width
    minimumHeight: column.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Timer")

    QtObject {
        id: state

        property int elapsed: 0
        property int duration: 5000
        readonly property int minimumDuration: 1000
        readonly property int maximumDuration: 20000
    }

    Timer {
        id: timer
        interval: 100; running: true; repeat: true
        onTriggered: {
            if (state.elapsed >= state.duration) {
                timer.stop()
                return
            }

            state.elapsed += 100
        }
    }

    Column {
        id: column
        spacing: 8
        padding: 12

        ProgressBar {
            id: progress
            value: state.elapsed / state.duration
        }

        Text {
            text: (state.elapsed / 1000).toFixed(1)
        }

        Slider {
            from: state.minimumDuration
            to: state.maximumDuration
            value: state.duration
            onMoved: state.duration = value
        }

        Button {
            text: "Reset"
            width: progress.width
            onClicked: {
                state.elapsed = 0
                timer.start()
            }
        }
    }
}
