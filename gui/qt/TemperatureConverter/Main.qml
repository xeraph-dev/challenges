import QtQuick
import QtQuick.Controls.Basic

Window {
    minimumWidth: row.width
    minimumHeight: row.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Temperature Converter")

    Row {
        id: row
        padding: 12
        spacing: 8

        TextField {
            id: celsiusInput
            anchors.verticalCenter: parent.verticalCenter
            width: fahrenheitLabel.width
            text: {
                if (!focus) {
                    if (text == "") return 0
                    return (((+fahrenheitInput.text || 0) - 32) * (5/9)).toFixed(0)
                }
            }
        }

        Text {
            id: celsiusLabel
            text: "Celsius"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            text: "="
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: fahrenheitInput
            anchors.verticalCenter: parent.verticalCenter
            width: fahrenheitLabel.width
            text: {
                if (!focus) return ((+celsiusInput.text || 0) * (9/5) + 32).toFixed(0)
            }

        }

        Text {
            id: fahrenheitLabel
            text: "Fahrenheit"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
