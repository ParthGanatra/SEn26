import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page {

    property string otp: ""

    id:verify_email
    ColumnLayout {

        id: column
        anchors.centerIn: parent
        spacing: Units.dp(32)

        TextField {
            id: otp_field
            implicitWidth: 200
            placeholderText: "Enter OTP"
            floatingLabel: true
            anchors.horizontalCenter: parent.horizontalCenter
            onAccepted: {

            }
        }


        RowLayout{
            id: row
            anchors.top: parent.bottom*0.80
            spacing: Units.dp(32)

            Button {
                text: "Verify"
                elevation: 1
                anchors.right: parent.horizontalCenter*0.8
                onClicked: {
                    //check if otp is correct
                    //if correct then load configuration page and save user details in the database

                    if(otp.toString().match(otp_field.text) && (otp.toString().length===otp_field.text.length))
                    pageStack.push(Qt.resolvedUrl("Configure.qml"))
                    else
                    otp_field.placeholderText="Verification Failed"
                }
            }

            Button {
                text: "Reveal Otp"
                elevation: 1
                activeFocusOnPress: true
                backgroundColor: Theme.primaryColor
                anchors.left: parent.horizontalCenter*1.2

                onClicked: {
                    otp_field.text=otp
                }
            }
        }
    }

}



