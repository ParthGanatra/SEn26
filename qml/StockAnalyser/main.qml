import QtQuick 2.4
import QtQuick.Layouts 1.1

import "stockanalyserCore"
import "stockanalyserCore/javascriptFiles/main.js" as Mainjs

import Material 0.2
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: mainwindow
    title: "Stock Analyser"
    visible: true

    width: 1000
    height: 1000

    theme {
        primaryColor: "blue"
        accentColor: "red"
        tabHighlightColor: "white"
    }

    initialPage: TabbedPage {
        id: mainpage
        title: "Stock Analyser"
        actionBar.maxActionCount: 1

        actions: [
            Action {
                name: "Login"
                hoverAnimation: true

                onTriggered: {
                    var component = Qt.createComponent("login.qml")
                    var window = component.createObject(mainpage)
                    window.show()
                }
            },

            Action {
                name: "Sign Up"
                hoverAnimation: true

                onTriggered: {
                    var component = Qt.createComponent("signup.qml")
                    var window = component.createObject(mainpage)
                    window.show()
                }
            },

            Action {
                name: "Add Pop-up"
                hoverAnimation: true

                onTriggered: {
                    var component = Qt.createComponent("add_popup.qml")
                    var window = component.createObject(mainpage)
                    window.show()
                }
            },

            Action {
                iconName: "action/settings"
                name: "Configure"
                hoverAnimation: true
                onTriggered: {
                    var component = Qt.createComponent("configure.qml")
                    var window = component.createObject(mainpage)
                    window.show()
                }
            },

            Action {
                iconName: "action/account_circle"
                name: "Accounts"
                onTriggered: {
                    var component = Qt.createComponent("account.qml")
                    var window = component.createObject(mainpage)
                    window.show()
                }
            }

            /*Action {
                iconName: "alert/warning"
                name: "THIS SHOULD BE HIDDEN!"
                visible: false
            },

            Action {
                iconName: "action/language"
                name: "Language"
                enabled: false
            },*/
        ]

        RowLayout {

            ColumnLayout {
                Charts{}
                Newsfeeds{}
            }
            Popups{}
        }
    }
}
