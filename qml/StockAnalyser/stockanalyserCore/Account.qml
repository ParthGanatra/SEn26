import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import Material 0.2
import Material.Extras 0.1
import QtQuick.Controls 1.3 as QuickControls


Window {
    id: account_window
    width: 500
    height: 500

    Rectangle {

        anchors.fill: parent
        id: main_rect

        Dialog {
            id: textFieldDialog
            title: "Change Text"
            hasActions: true

            TextField {
                id: optionText
                width: parent.width
                placeholderText: "New Option to Confirm"
            }

            onAccepted: {
                //            dialogSnackBar.open("You entered: %1".arg(optionText.text))
            }
        }

        ColumnLayout {

            id: column
            anchors.centerIn: parent

            Row {

                Label {
                    style: "title"
                    text: "Username:"
                }

                TextField {
                    id: firstname
                    text: _helper
                    floatingLabel: true
                }
            }

            Row {

                Label {
                    style: "title"
                    text: "Lastname:"
                }

                TextField {
                    id: lastname
                    text: "lastname"
                    floatingLabel: true
                }
            }


            Row {

                Label {
                    style: "title"
                    text: "Email:"
                }

                TextField {
                    id: email
                    text: "email"
                    floatingLabel: true
                }
            }

            Row {
                id: pass_row
                visible: false
                Label {
                    style: "title"
                    text: "New Password:"
                }

                TextField {
                    id: new_pass
                    text: "email"
                    echoMode: TextInput.Password
                    floatingLabel: true
                }
            }

            Row {
                id: con_pass_row
                visible: false
                Label {
                    style: "title"
                    text: "Confirm Password:"
                }

                TextField {
                    id: new_confirm_pass
                    text: "Confirm Password"
                    echoMode: TextInput.Password
                    floatingLabel: true
                }
            }
        }

        Row {
            anchors.bottom: main_rect.bottom
            anchors.bottomMargin: 50

            Button {
                id: change_password
                textColor: "white"
                backgroundColor: Theme.primaryColor
                elevation: 1
                text: "Change Password"

                onClicked: {
                    //                    pass_row.visible.
                }
            }

            Button {
                id: save_changes
                textColor: "white"
                backgroundColor: Theme.primaryColor
                elevation: 1
                text: "Save Changes"

                onClicked: {
                    snackBar.open("saving changes");
                    textFieldDialog.show()
                }
            }
        }
        Snackbar {
            id: snackBar
        }
    }
}
