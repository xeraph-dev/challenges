import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Dialogs

Window {
    id: window
    minimumWidth: column.width
    minimumHeight: column.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Flight Booker")



    component DateField : TextField {
        property var locale: Qt.locale()
        property bool valid: isValidDate(text)

        function isValidDate(str : string) : bool {
            return !isNaN(parseDate(str))
        }

        function parseDate(str : string) : date {
            return Date.fromLocaleDateString(locale, str, "dd.MM.yyyy")
        }

        function formatDate(d : date) : string {
            return d.toLocaleDateString(locale, "dd.MM.yyyy")
        }

        function isDateAfter(field : DateField) : bool {
            return parseDate(text).getTime() > parseDate(field.text).getTime()
        }

        text: formatDate(new Date())

        onTextEdited: {
            valid = isValidDate(text)
            print(text, Date.fromLocaleDateString(locale, text, "dd.MM.yyyy"), isValidDate(text))
        }

        color: valid ? "black" : "red"
    }

    Column {
        id: column
        spacing: 8
        padding: 12

        ComboBox {
            id: flightInput
            model: ListModel {
                ListElement { text: qsTr("one-way flight") }
                ListElement { text: qsTr("return flight") }
            }
        }

        DateField {
            id: startInput
            width: flightInput.width
        }

        DateField {
            id: returnInput
            width: flightInput.width
            enabled: flightInput.currentIndex === 1
        }

        Button {
            id: button
            text: "Book"
            width: flightInput.width
            enabled: (flightInput.currentIndex === 0 && startInput.valid) ||
                     (flightInput.currentIndex === 1 && startInput.valid && returnInput.valid && returnInput.isDateAfter(startInput))

            onClicked: {
                message.open()
            }
        }
    }

    MessageDialog {
        id: message
        text: `You have booked a one-way flight on ${startInput.text}.`
    }
}
