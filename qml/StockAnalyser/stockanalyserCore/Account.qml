
import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import Material 0.2
import Material.Extras 0.1
import QtQuick.Controls 1.3 as QuickControls
import "../stockanalyserCore"

Page {
    title: "Account Settings"
    id: account_window
    property string dial: "0"

    Dialog {
        id: new_password_dialog
        title: "Enter new Password"
        hasActions: true

        TextField {
            id: new_password
            width: parent.width
            echoMode: TextInput.Password
            placeholderText: "New Password"
        }

        TextField {
            id: new_password_verify
            width: parent.width
            echoMode: TextInput.Password
            placeholderText: "Verify Password"
        }

        onAccepted: {
            if((!new_password.text.localeCompare(new_password_verify.text)) && new_password.text.length > 7)
            {
                _helper.change_password(Settings.username,new_password.text);
                new_password.text = "";
                new_password_verify.text = "";
                dialogSnackBar.open("Password Changed")
            }
            else
            {
                dialogSnackBar.open("Password doesn't match")
                new_password_dialog.show()
            }
        }

        onRejected: {
            new_password.text = "";
            new_password_verify.text = "";
            new_password.placeholderText = "New Password"
            new_password_verify.placeholderText = "Verify Password"
        }
    }

    Dialog {
        id: verify_password
        title: "Enter Password"
        hasActions: true

        TextField {
            id: password_field
            width: parent.width
            echoMode: TextInput.Password
            placeholderText: "Password"
        }

        onAccepted: {
            var result = _helper.verify_user_password(Settings.username, password_field.text)
            password_field.text = "";
            if(result == true)
            {
                if(account_window.dial == "1")
                {
                    new_password_dialog.show()
                }
                else if(account_window.dial == "2")
                {
                    _helper.change_details(Settings.username,firstname.text,lastname.text,email.text)
                    Settings.username = firstname.text
                    dialogSnackBar.open("Changes Saved")
                }
            }
            else
            {
                dialogSnackBar.open("Invalid Password")
                verify_password.show()
            }
        }


        onRejected: {
            console.log("cancel")
            verify_password.text
        }
    }

    Rectangle {
        anchors.fill: parent
        id: main_rect

        ColumnLayout {

            id: column
            anchors.centerIn: parent
            spacing: Units.dp(10)

            Row {
                spacing: Units.dp(10)

                Label {
                    style: "title"
                    text: "Firstname:"
                }

                TextField {
                    id: firstname
                    text: Settings.username
                    floatingLabel: true
                }
            }

            Row {
                spacing: Units.dp(10)

                Label {
                    style: "title"
                    text: "Lastname:"
                }

                TextField {
                    id: lastname
                    text: qsTr(_helper.get_user_lastname(Settings.username))
                    floatingLabel: true
                }

                TextField {
                    id: username
                    visible: false
                    implicitWidth: 200
                    placeholderText: "Enter username"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }


            Row {
                spacing: Units.dp(10)
                Label {
                    style: "title"
                    text: "Email:"
                }

                Label {
                    id: email
                    text: _helper.get_user_email(Settings.username)
                    style: "title"
                }
            }
        }

        Row {
            anchors.bottom: main_rect.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: main_rect.horizontalCenter
            spacing: Units.dp(10)

            Button {
                id: change_password
                textColor: "white"
                backgroundColor: Theme.primaryColor
                elevation: 1
                text: "Change Password"

                onClicked: {
                    dial = "1"
                    verify_password.show()

                }
            }

            Button {
                id: save_changes
                textColor: "white"
                backgroundColor: Theme.primaryColor
                elevation: 1
                text: "Save Changes"

                onClicked: {
                    dial = "2"
                    verify_password.show()
                }
            }
        }

        Snackbar {
            id: dialogSnackBar
        }
    }

}
