import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as QuickControls
import "../stockanalyserCore"
import Material 0.2
import Material.ListItems 0.1 as ListItem

Page {
    id: popup_select_indicator_page
    title: "Add Notification"

    property string selected_stock: "stock"
    property string selected_indicator: "indicator"
    property string selected_condition: "condition"

    Rectangle {
        id: main_rect
        anchors.fill: parent

        Rectangle{
            id: label_rect
            width: Settings.screenWidth*0.85
            height: Settings.screenHeight*0.85*0.3
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                anchors.centerIn: parent
                text: "Select conditions for " + selected_indicator
                color: Theme.light.textColor
                style: "display1"
            }

            Button {
                text: "Done"
                anchors.right: parent.right
                anchors.rightMargin: 6
                anchors.verticalCenter: parent.verticalCenter
                elevation: 1
                activeFocusOnPress: true
                backgroundColor: Theme.primaryColor
                onClicked: {
//                    selected_condition = conditions_loader.item.select_condition_indicator1.selectedText
                    console.log(selected_condition)
                    popups_model.append({"popups_stock": selected_stock, "popups_indicator":selected_indicator, "popups_condition":selected_condition})
                    popup_select_stock.close()
                }
            }
        }

        Item {
            id: conditions
            anchors.centerIn: parent
            Loader {
                id: conditions_loader
                anchors.centerIn: parent
                sourceComponent: {
                    if(selected_indicator=="Indicator1"){
                        condition_indicator1
                    }
                    else if(selected_indicator=="Indicator2"){
                        condition_indicator2
                    }
                    else if(selected_indicator=="Indicator3"){
                        condition_indicator2
                    }

                }

            }
        }

        Component {
            id: condition_indicator1
            MenuField {
                id: select_condition_indicator1
                anchors.centerIn: parent
                width: 150
                model: ["Condition1", "Condition2", "Condition3"]       //From database later
            }
        }


        Component {
            id: condition_indicator2
            TextField {
                id: select_condition_indicator2
                placeholderText: "Conditon"
                anchors.centerIn: parent
            }
        }

        Component {
            id: condition_indicator3
            Label {
                anchors.centerIn: parent
                text: "Conditions for " + selected_indicator
                color: Theme.light.textColor
                style: "display1"
            }
        }
    }
}
