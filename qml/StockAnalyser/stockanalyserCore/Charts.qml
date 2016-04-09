import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtWebEngine 1.2

import "javascriptFiles/main.js" as Mainjs

Rectangle {

//    Canvas {
//        id: canvas
//        anchors.fill: parent
//        onPaint: {
//            var ctx = getContext("2d");
//            Mainjs.drawGraph(ctx);
//        }
//    }

    WebEngineView {
            id: webview
            anchors.fill: parent
            anchors.centerIn: parent
            url: "../stockanalyserCore/javascriptFiles/index.html"
            webChannel: [{width: 100}]
        }
}
