import QtQuick 2.4

import "stockAnalyserCore"
import "stockAnalyserCore/javascriptFiles/main.js" as Mainjs

import Material 0.2
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: demo
    title: "Stock Analyser"
    visible: true

    width: Settings.screenWidth
    height: Settings.screenHeight

    theme {
        primaryColor: "blue"
        accentColor: "red"
        tabHighlightColor: "white"
    }
    property var option1: [
            "Option 1_1", "Option 1_2"
    ]
    property var option2: [
            "Option 2_1", "Option 2_2"
    ]
    property var option3: [
            "Option 3_1", "Option 3_2"
    ]
    property var sections: [ option1, option2, option3 ]
    property var sectionTitles: [ "Option 1", "Option 2", "Option 3" ]
    property string selectedComponent: sections[0][0]

    initialPage: TabbedPage {
        id: page
        title: "Stock Analyser"
        actionBar.maxActionCount: navDrawer.enabled ? 1 : 1

        actions: [
            Action {
                iconName: "action/settings"
                name: "Settings"
                hoverAnimation: true
            },

            Action {
                iconName: "alert/warning"
                name: "THIS SHOULD BE HIDDEN!"
                visible: false
            },

            Action {
                iconName: "action/language"
                name: "Language"
                enabled: false
            },

            Action {
                iconName: "action/account_circle"
                name: "Accounts"
            }
        ]

        backAction: navDrawer.action

        NavigationDrawer {
            id: navDrawer
            enabled: page.width < Units.dp(500)

            onEnabledChanged: smallLoader.active = enabled
            Flickable {
                anchors.fill: parent
                contentHeight: Math.max(content.implicitHeight, height)

                Column {
                    id: content
                    anchors.fill: parent

                    Repeater {
                        model: sections

                        delegate: Column {
                            width: parent.width

                            ListItem.Subheader {
                                text: sectionTitles[index]
                            }

                            Repeater {
                                model: modelData
                                delegate: ListItem.Standard {
                                    text: modelData
                                    selected: modelData == demo.selectedComponent
                                    onClicked: {
                                        demo.selectedComponent = modelData
                                        navDrawer.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Repeater {
            model: !navDrawer.enabled ? sections : 0

            delegate: Tab {
                title: sectionTitles[index]

                property string selectedComponent: modelData[0]
                property var section: modelData

                sourceComponent: tabDelegate
            }
        }

        Loader {
            id: smallLoader
            anchors.fill: parent
            sourceComponent: tabDelegate

            property var section: []
            visible: active
            active: false
        }
    }

    Component {
        id: tabDelegate

        Item {

            Sidebar {
                id: sidebar
                width: parent.width/6
                expanded: !navDrawer.enabled

                Column {
                    width: parent.width

                    Repeater {
                        model: section
                        delegate: ListItem.Standard {
                            text: modelData
                            selected: modelData == selectedComponent
                            onClicked: selectedComponent = modelData
                        }
                    }
                }
            }
            Flickable {
                id: flickable
                anchors {
                    left: sidebar.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                clip: true
                contentHeight: Math.max(example.implicitHeight + 40, height)
                Loader {
                    id: example
                    anchors.fill: parent
                    asynchronous: true
                    visible: status == Loader.Ready
                    // selectedComponent will always be valid, as it defaults to the first component
                    source: {
                        if (navDrawer.enabled) {
                            return Qt.resolvedUrl("%1Demo.qml").arg(demo.selectedComponent.replace(" ", ""))
                        } else {
                            return Qt.resolvedUrl("%1Demo.qml").arg(selectedComponent.replace(" ", ""))
                        }
                    }
                }

                ProgressCircle {
                    anchors.centerIn: parent
                    visible: example.status == Loader.Loading
                }
            }
            Scrollbar {
                flickableItem: flickable
            }
        }
    }
}
