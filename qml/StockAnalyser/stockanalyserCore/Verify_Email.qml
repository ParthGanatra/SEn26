import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page {
    id:verify_email
    ColumnLayout {

        id: column
        anchors.centerIn: parent
        spacing: Units.dp(32)

        TextField {
            id: username
            implicitWidth: 200
            placeholderText: "Enter OTP"
            floatingLabel: true
            anchors.horizontalCenter: parent.horizontalCenter
            onAccepted: {
                if (passwordField.text != "" && username.text != "") {
                    //check username and password
                }
            }
        }


        RowLayout{
            id: row
            anchors.top: parent.bottom*0.8
            spacing: Units.dp(32)

            Button {
                text: "Verify"
                elevation: 1
                anchors.right: parent.horizontalCenter*0.8
                onClicked: {
                    //check if otp is correct
                    //if correct then load configuration page and save user details in the database
                    pageStack.push(Qt.resolvedUrl("Configure.qml"))
                }
            }

            Button {
                text: "Back"
                elevation: 1
                activeFocusOnPress: true
                backgroundColor: Theme.primaryColor
                anchors.left: parent.horizontalCenter*1.2

                onClicked: {
                    pageStack.replace(Qt.resolvedUrl("Signup.qml"))
                }
            }
        }
    }

}



