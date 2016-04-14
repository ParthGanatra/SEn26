import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import "../stockanalyserCore"
import QtQuick.Layouts 1.3

Rectangle {
    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: 500 //_backend.get_Popup_size()*(Units.dp(12) + 60)


        ListView {
            id: popup_list
            anchors.fill: parent
            model: trig_model
            delegate: popupDelegate
        }


    }

    Component {
        id: popupDelegate
        Rectangle{
            id: rect
            color: "#ecf0f1"
            height: 60
            width: Settings.screenWidth*0.2
            ActionButton {
                isMiniSize: true
                backgroundColor: "#95a5a6"
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                action: Action {
                    id: removeContent
                    onTriggered: _backend.remove_Popup_data(index)
                }
                iconName: "action/delete"
            }

            Column {
                anchors.top: parent.top
                anchors.topMargin: 10

                Text { text: "stock"}
                Text { text: "indicator"}
                Text { text: "condition"}
            }
        }
    }

    Scrollbar {
        flickableItem: flickable
    }
}
//        Column{
//            id: main_popup
//            spacing: Units.dp(12)
//            anchors.fill: parent


//            Repeater{
//                model: _backend.get_Popup_data()

//                delegate: Rectangle{
//                    id: rect
//                    color: "#ecf0f1"
//                    height: 60
//                    width: Settings.screenWidth*0.2
//                    ActionButton {
//                        isMiniSize: true
//                        backgroundColor: "#95a5a6"
//                        anchors {
//                            right: parent.right
//                            verticalCenter: parent.verticalCenter
//                        }
//                        action: Action {
//                            id: removeContent
//                            onTriggered: _backend.remove_Popup_data(index)
//                        }
//                        iconName: "action/delete"
//                    }

//                    Column {
//                        anchors.top: parent.top
//                        anchors.topMargin: 10

//                        Text { text: modelData["stock"]}
//                        Text { text: modelData["indicator"]}
//                        Text { text: modelData["condition"]}
//                    }
//                }
//            }
