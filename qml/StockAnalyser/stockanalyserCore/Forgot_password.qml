import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page{
    id: forget_password_page
    title: Settings.windowTitle

    TextField {
        id: username
        implicitWidth: 200
        placeholderText: "Username"
        floatingLabel: true
        anchors.horizontalCenter: parent.horizontalCenter
        onAccepted: {

        }
    }
}
