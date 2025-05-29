pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.Basic

import CRUD

Window {
    id: window
    minimumWidth: root.width
    minimumHeight: root.height
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true
    title: qsTr("Hello World")

    UUIDGenerator {
        id: uuid
    }

    function clearForm() {
        state.selected = null
        usersList.currentIndex = -1
        nameInput.clear()
        surnameInput.clear()
        fillList()
    }

    function fillList() {
        usersModel.clear()

        const filtered = state.users.filter(el => el.surname.trim().toLowerCase().startsWith(filter.text.trim().toLowerCase()))
        for (const user of filtered) {
            usersModel.append(user)
        }
    }

    component User : QtObject {
        required property string uid
        required property string name
        required property string surname
    }

    Component {
        id: userComponent
        User {}
    }

    QtObject {
        id: state

        property User selected: null

        property list<User> users: []
    }

    Column {
        id: root
        padding: 12
        spacing: 12

        Row {
            spacing: 12

            Column {
                id: left
                spacing: 12

                Row {
                    spacing: 12
                    id: filterContainer

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Filter prefix:"
                    }
                    TextField {
                        id: filter

                        Component.onCompleted: window.fillList()
                        onTextEdited: window.fillList()
                    }
                }

                ScrollView {
                    height: right.height * 2
                    width: parent.width
                    clip: true

                    Rectangle {
                        anchors.fill: parent
                        border.color: "#d0d0d0"

                        ListView {
                            id: usersList
                            anchors.fill: parent
                            currentIndex: -1

                            model: ListModel {
                                id: usersModel
                            }

                            delegate: ItemDelegate {
                                required property int index
                                required property string name
                                required property string surname

                                width: usersList.width
                                highlighted: ListView.isCurrentItem

                                text: `${surname}, ${name}`

                                onClicked: ListView.view.currentIndex = index
                            }

                            ScrollIndicator.vertical: ScrollIndicator {}

                            onCurrentIndexChanged: {
                                if (currentIndex >= 0) {
                                    const id = usersModel.get(currentIndex).uid
                                    const index = state.users.findIndex(el => el.uid === id)
                                    state.selected = state.users[index]
                                }
                            }
                        }
                    }
                }
            }

            Column {
                id: right
                width: left.width
                spacing: 12
                anchors.top: parent.top
                anchors.topMargin: filterContainer.height + parent.spacing

                Row {
                    spacing: 12

                    Text {
                        text: "Name:"
                        width: surnameLabel.width
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    TextField {
                        id: nameInput
                        text: state.selected?.name ?? ""
                    }
                }

                Row {
                    spacing: 12

                    Text {
                        id: surnameLabel
                        text: "Surname:"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    TextField {
                        id: surnameInput
                        text: state.selected?.surname ?? ""
                    }
                }
            }
        }
        Row {
            spacing: 12

            Button {
                text: "Create"
                enabled: nameInput.text !== "" && surnameInput.text !== ""
                onClicked: {
                    state.users.push(userComponent.createObject(this, { "uid": uuid.v4(), "name": nameInput.text, "surname": surnameInput.text }))
                    window.clearForm()
                }
            }

            Button {
                visible: state.selected !== null
                text: "Update"
                onClicked: {
                    const index = state.users.findIndex(el => el.uid === state.selected.uid)
                    state.users[index].name = nameInput.text
                    state.users[index].surname = surnameInput.text
                    window.clearForm()
                }
            }

            Button {
                visible: state.selected !== null
                text: "Delete"
                onClicked: {
                    const index = state.users.findIndex(el => el.uid === state.selected.uid)
                    state.users.splice(index, 1)
                    window.clearForm()
                }
            }
        }
    }
}
