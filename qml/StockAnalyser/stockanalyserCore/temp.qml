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

        Label {
            id: text
//            font.family: "Roboto"
//            font.weight: Font.bold
            text: "Click to proceed"
            font.pixelSize: Units.dp(24)

            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                bottomMargin: 20
            }
        }


        Button {
            text: "Next >>"
            anchors{
                top: text.bottom
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }

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
