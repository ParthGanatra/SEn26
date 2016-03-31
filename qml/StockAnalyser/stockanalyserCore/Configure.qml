import QtQuick 2.4
import Material 0.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page {
    id: configure_page
    title: "Configurations Page"

    Text {
        anchors.centerIn: parent
        text: qsTr("Indicators Configuration Window")
    }
}
