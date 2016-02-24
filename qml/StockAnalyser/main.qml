import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.2
import QtWebKit 3.0

import "stockAnalyserCore"
import "stockAnalyserCore/javascriptFiles/main.js" as Mainjs

ApplicationWindow {
    visible: true
    title: "Stock Analyser"
    width: Settings.screenWidth
    height: Settings.screenHeight

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Log out"
            }
            MenuItem {
                text: "Exit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: "Settings"
            MenuItem {
                text: "Edit Config. File"
                onTriggered: Mainjs.drawGraph()
            }
        }
    }

//    WebView
//    {
//        visible: true
//        height: 500
//        width: 800
//        url: "stockAnalyserCore/index.html"
//        smooth: true
//    }
    TabView {
        id: tabView
        anchors.fill: parent
        Layout.minimumWidth: 360
        Layout.minimumHeight: 360
        Layout.preferredWidth: 480
        Layout.preferredHeight: 640
        Tab {
            title: "Buttons"
        }
        Tab {
            title: "Progress"

        }
    }
}
