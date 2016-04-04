import QtQuick 2.5
import QtQuick.Window 2.0
import Material 0.2
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1
import "../stockanalyserCore"

Window {
    id: all_popups_window
    width: 600
    height: 700

    //    ListModel {         // Need to replace with database
    //        id: popups_model
    //        ListElement {
    //            popups_id: "1"
    //            popups_stock: "stock1"
    //            popups_indicator: "indicator1"
    //            popups_condition: "condition1"
    //        }
    //        ListElement {
    //            popups_id: "2"
    //            popups_stock: "stock2"
    //            popups_indicator: "indicator2"
    //            popups_condition: "condition2"
    //        }
    //        ListElement {
    //            popups_id: "3"
    //            popups_stock: "stock3"
    //            popups_indicator: "indicator3"
    //            popups_condition: "condition3"
    //        }

    //    }

    Component {
        id: popupsDelegate
        Item {
            id: popups_list_item
            width: parent.width
            height: Units.dp(50)
            anchors.margins: Units.dp(8)

            ListItem.Standard {

                content: RowLayout {
                    anchors.centerIn: parent
                    spacing: Units.dp(10)
                    width: parent.width
                    Label {
                        id: popups_list_stock
                        style: "title"
                        text: modelData["stock"]
                    }


                    Label {
                        id: popups_list_indicator
                        style: "title"
                        text: modelData["indicator"]
                    }


                    Label {
                        id: popups_list_condition
                        style: "title"
                        text: modelData["condition"]
                    }

                    Button {
                        id: popups_modify
                        text: "Modify"
                        elevation: 1
                        onClicked: snackbar.open("Method to modify popup")
                    }

                    Button {
                        id: popups_dismiss
                        text: "Dismiss"
                        elevation: 1
                        onClicked: snackbar.open("Method to dismiss popup")
                    }
                }
            }
        }

    }

    Component {
        id: popups_list_header
        RowLayout {
            spacing: Units.dp(10)
            width: parent.width
            Label {
                style: "title"
                text: "Stock"
            }


            Label {
                style: "title"
                text: "Indicator"
            }


            Label {
                style: "title"
                text: "Condition"
            }
        }
    }


    ListView {
        id: popups_list
        anchors.fill: parent
        header: popups_list_header
        model: _backend.get_Popup_data()
        delegate: popupsDelegate
    }

    //    Button {        //Temporary
    //        anchors {
    //            bottom: parent.bottom
    //            left: parent.left
    //            margins: Units.dp(10)
    //        }

    //        textColor: "white"
    //        backgroundColor: Theme.primaryColor
    //        elevation: 1
    //        text: "Add Random Pop-up"

    //        onClicked: {
    //            var num = popups_model.count + 1
    //            popups_model.append({"popups_stock": "stock" + num , "popups_indicator":"indicator" + num , "popups_condition":"condition" + num})

    //        }
    //    }

    Button {
        id: add_popup_button
        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: Units.dp(10)
        }

        textColor: "white"
        backgroundColor: Theme.primaryColor
        elevation: 1
        text: "Add Pop-up"

        onClicked: {
            var component = Qt.createComponent("popup_select_stock.qml")
            var window = component.createObject(all_popups_window)
            window.show()
        }
    }

    Snackbar {
        id: snackbar
    }
}
