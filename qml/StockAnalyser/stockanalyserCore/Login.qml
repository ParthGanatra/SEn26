import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls

Page {
    id: login_page
//    anchors.horizontalCenter: parent.horizontalCenter
//    anchors.fill: parent
//    signal activated

    ColumnLayout {

        id: column
        anchors.centerIn: parent
        spacing: Units.dp(32)

        TextField {
            id: username
            implicitWidth: 200
            placeholderText: "Username"
            floatingLabel: true
            anchors.horizontalCenter: parent.horizontalCenter
            onAccepted: {
                if (passwordField.text != "" && username.text != "") {
                    //check username and password
                }
            }
        }

        TextField {
            id: passwordField
            implicitWidth: 200
            placeholderText: "Password"
            floatingLabel: true
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter

            onAccepted: {
                if (passwordField.text != "" && username.text != "") {
                    //check username and password
                }
            }
        }

        Button {
            text: "Forgot Password"
            textColor: Theme.accentColor
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: pageStack.push(Qt.resolvedUrl("Forgot_password.qml"))
        }

        RowLayout{
            id: row
            anchors.top: parent.bottom*0.8
            spacing: Units.dp(32)

            Button {
                text: "SignUp"
                elevation: 1
                anchors.right: parent.horizontalCenter*0.8
                onClicked: pageStack.push(Qt.resolvedUrl("Signup.qml"))
            }

            Button {
                text: "Login"
                elevation: 1
                activeFocusOnPress: true
                backgroundColor: Theme.primaryColor
                anchors.left: parent.horizontalCenter*1.2

                onClicked: {
                    pageStack.replace(Qt.resolvedUrl("Central_window.qml"))
//                    activated()
                }
            }
        }
    }
}
