import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem
import "../stockanalyserCore"

Page {
    id: temp_page
    title: "Page with right sidebar"
    actions: [
        Action {
            iconName: "action/search"
            text: "Search"
        }
    ]

    Rectangle{
        anchors.fill: parent


        Button {
            text: "Next >>"
            anchors.rightMargin: 6
            anchors.centerIn: parent
            elevation: 1
            activeFocusOnPress: true
            backgroundColor: Theme.primaryColor
            onClicked: {
                pageStack.replace(Qt.resolvedUrl(Settings.calledby));
            }
        }
//        Component.onCompleted: {
//            pageStack.replace(Qt.resolvedUrl("Login.qml"));
//        }

    }
}
