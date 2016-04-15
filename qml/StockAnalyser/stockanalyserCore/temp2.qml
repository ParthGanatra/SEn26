import QtQuick 2.4
import QtQuick.Controls 1.4

import "../stockanalyserCore"

//import "../StockAnalyser/stockanalyserCore/javascriptFiles/main.js" as Mainjs

import Material 0.2
import Material.ListItems 0.1 as ListItem

ApplicationWindow {
    id: temp2_window
    title: "StockAnalyser"
    visible: true
    width: Settings.screenWidth
    height: Settings.screenHeight

    theme {
        primaryColor: "blue"
        accentColor: "red"
        tabHighlightColor: "white"
    }

    initialPage: TabbedPage {
        id: page
        title: Settings.windowTitle

        Loader {
            id: loginLoader
            anchors.fill: parent
            asynchronous: true
            visible: status == Loader.Ready

            //  For testing your component change the login below to the name of your file.
            source: {
                return Qt.resolvedUrl("temp.qml")
            }
        }

//        Connections {
//            id: mainConnection
//            target: loginLoader.item
//            onActivated:
//            {
//                page.actionBar.visible = true;
//            }
//        }
    }
}
