import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3 as Controls
import "../stockanalyserCore"

Page{
    id: signup_page
    title: Settings.windowTitle

    actions: [
        Action {
            iconName: "action/note_add"
            name: "Add Pop-up"

            onTriggered: {
                var component = Qt.createComponent("Add_Popup.qml")
                var window = component.createObject(signup_page)
                window.show()
            }
        },

        Action {
            iconName: "action/settings"
            name: "Configure"
            hoverAnimation: true

            onTriggered: {
                var component = Qt.createComponent("Configure.qml")
                var window = component.createObject(signup_page)
                window.show()
            }
        },

        Action {
            iconName: "action/account_circle"
            hoverAnimation: true
            name: "Accounts"

            onTriggered: {
                var component = Qt.createComponent("Account.qml")
                var window = component.createObject(signup_page)
                window.show()
            }
        }
    ]

//    RowLayout {
//        ColumnLayout {
        Charts {
            id: chart_window
            width: signup_page.width*0.7
            height: signup_page.height*0.8
        }
        Newsfeeds {
            anchors.top: chart_window.bottom
            width: signup_page.width*0.7
            height: signup_page.height*0.2
        }
//        }
    Popups {
        anchors.left: chart_window.right
        width: signup_page.width*0.3
        height: signup_page.height
    }
//    }
}
