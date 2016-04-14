import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2 as Controls
import "../stockanalyserCore"

Page{
    id: central_window
    title: Settings.windowTitle

    actions: [
        Action {
            iconName: "action/note_add"
            name: "All Pop-up"

            onTriggered: {
                var component = Qt.createComponent("All_Popup.qml")
                var window = component.createObject(central_window)
                window.show()
            }
        },

        Action {
            iconName: "action/account_circle"
            hoverAnimation: true
            name: "Accounts"

            onTriggered: {
                pageStack.push(Qt.resolvedUrl("Account.qml"))
            }
        },


        Action {
            iconName: "action/power_settings_new"
            name: "Logout"
            hoverAnimation: true

            onTriggered: {
                pageStack.pop()
                pageStack.push(Qt.resolvedUrl("Login.qml"))
            }
        },

        Action {
            iconName: "action/power_settings_new"
            name: "Help"
            hoverAnimation: true

            onTriggered: {
                var component = Qt.createComponent("HelpWindow.qml")
                var window = component.createObject(central_window)
                window.show()
            }
        }
    ]

//    Charts {
//        id: chart_window
//        width: central_window.width*0.8
//        height: central_window.height*0.8
//    }
    Newsfeeds {
        anchors.top: chart_window.bottom
        width: central_window.width*0.8
        height: central_window.height*0.2
    }
    Popups {
        id: popup
        anchors.left: chart_window.right
        width: central_window.width*0.2
        height: central_window.height
    }
}
