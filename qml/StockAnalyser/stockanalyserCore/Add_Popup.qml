import QtQuick 2.5
import QtQuick.Window 2.0
import Material 0.2
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1
import QtQuick.Controls 1.4 as Controls

Window {
    id: add_popups_window
    width: 1000
    height: 700

    ListModel {         // Need to replace with database

        id: popups_model
        ListElement {
            popups_stock: "stock1"
            popups_indicator: "indicator1"
            popups_condition: "condition1"
        }
        ListElement {
            popups_stock: "stock2"
            popups_indicator: "indicator2"
            popups_condition: "condition2"
        }
        ListElement {
            popups_stock: "stock3"
            popups_indicator: "indicator3"
            popups_condition: "condition3"
        }

    }

    Component {
        id: popupsDelegate

        ListItem.Standard {
            text: '<b>Stock:</b> ' + popups_stock + "\t" + '<b>Indicator:</b> ' + popups_indicator + "\t" + '<b>Condition:</b> ' + popups_condition + "\t"
        }
    }

    ListView {
        id: popups_list
        anchors.fill: parent
        model: popups_model
        delegate: popupsDelegate
    }

    Button {
        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: 20
        }

        textColor: "white"
        backgroundColor: "blue"
        elevation: 1
        text: "Add Pop-up"

        onClicked: {
            var num = popups_model.count + 1
            popups_model.append({"popups_stock": "stock" + num , "popups_indicator":"indicator" + num , "popups_condition":"condition" + num})
        }
    }
}
