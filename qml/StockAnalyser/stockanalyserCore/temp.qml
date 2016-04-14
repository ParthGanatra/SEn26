import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem

Page {
    id: page
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
            anchors.right: parent.right
            anchors.rightMargin: 6
            anchors.verticalCenter: parent.verticalCenter
            elevation: 1
            activeFocusOnPress: true
            backgroundColor: Theme.primaryColor
            onClicked: {
                pageStack.replace(Qt.resolvedUrl("temp2.qml"));
            }
        }
//        Component.onCompleted: {
//            pageStack.replace(Qt.resolvedUrl("Login.qml"));
//        }

    }
}
