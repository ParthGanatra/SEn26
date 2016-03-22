import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page{
    id: signup_page
    title: Settings.windowTitle

    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: qsTr("Signup")
        }
    }
}
