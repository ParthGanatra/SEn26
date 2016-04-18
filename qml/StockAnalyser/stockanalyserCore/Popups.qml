import QtQuick 2.4
import QtQuick.Layouts 1.1
import Material 0.2
import Material.ListItems 0.1 as ListItem
import "../stockanalyserCore"
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0

Rectangle {
    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: 500 //_backend.get_Popup_size()*(Units.dp(12) + 60)

        ListView {
            id: popup_list
            anchors.fill: parent
            model: _backend.trigpopupsmodel
            delegate: popupDelegate
            spacing: 10
        }
    }

    Component {
        id: popupDelegate
        Rectangle{
            id: rect
            color: "#ecf0f1"
            height: Screen.height*0.12
            width: parent.width

//            Row {
//                spacing: Units.dp(rect.width*0.2)

                Column {
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    spacing: Units.dp(10)

                    Text { text: stock.slice(0,-1)}
                    Text { text: indicator}
                    Text { text: condition + threshold}
                }

                Column {
                    id: buttonColumn
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width - (1.5*showchartbutton.width)
                    spacing: Units.dp(10)

                    ActionButton {
                        id:showchartbutton
                        isMiniSize: true
                        backgroundColor: "#95a5a6"
                        action: Action {
                            onTriggered: _chartdata.showTrigPopup(stock)
                        }
                        iconName: "editor/insert_chart"
                    }

                    ActionButton {
                        id:deletepopupbutton
                        isMiniSize: true
                        backgroundColor: "#95a5a6"
                        action: Action {
                            //                    id: removeContent
                            onTriggered: _backend.remove_popup_trigger(stock,indicator,condition,threshold)
                        }
                        iconName: "action/delete"
                    }
                }
//            }
        }
    }

    Scrollbar {
        flickableItem: flickable
    }

    Snackbar {
        id: snackbar
    }
}
