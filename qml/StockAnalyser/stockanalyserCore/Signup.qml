import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page{
    id: signup_page
    title:"Sign Up"

    ColumnLayout {

        id: column
        anchors.centerIn: parent
        spacing: Units.dp(32)

          TextField {
              id: firstname
              implicitWidth: 200
              placeholderText: "First Name"
              floatingLabel: true
              anchors.horizontalCenter: parent.horizontalCenter
          }
          TextField {
              id: lastname
              implicitWidth: 200
              placeholderText: "Last Name"
              floatingLabel: true
              anchors.horizontalCenter: parent.horizontalCenter

          }

        TextField {
            id: email
            implicitWidth: 200
            placeholderText: "email"
            floatingLabel: true
            anchors.horizontalCenter: parent.horizontalCenter

        }

        TextField {
            id: passwordField
            implicitWidth: 200
            placeholderText: "Password"
            floatingLabel: true
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField {
            id: verifyPasswordField
            implicitWidth: 200
            placeholderText: "Verify Password"
            floatingLabel: true
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
        }

        RowLayout{
            id: row
            anchors.top: parent.bottom*0.8
            spacing: Units.dp(32)

            Button {
                property string otp: ""
                text: "Next"
                elevation: 1
                anchors.right: parent.horizontalCenter*0.8
                onClicked: {
                    //Check if details are valid in their context
                    //If valid then generate OTP to the specified email.
                    //If not valid donot open verify page

                    otp=_frontent.generateOtp();
                    _frontent.sendOTP(email.text,otp);

                    pageStack.push(Qt.resolvedUrl("Verify_Email.qml"),{otp:otp})
                }
            }

            Button {
                text: "Back"
                elevation: 1
                activeFocusOnPress: true
                backgroundColor: Theme.primaryColor
                anchors.left: parent.horizontalCenter*1.2

                onClicked: {
                    pageStack.replace(Qt.resolvedUrl("Login.qml"))
//                    activated()
                }
            }
        }
    }
}
