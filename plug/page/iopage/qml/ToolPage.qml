import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../"
Item {

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: tabBar
            Layout.fillWidth: parent.width

            XTabButton { text: "Tab 1" }
            XTabButton { text: "Tab 2" }
            XTabButton { text: "Tab 3" }
            background: Rectangle {
                radius: 20
                color: "#E0E5EC"     // 拟态背景色
                border.color: "#E0E5EC"
            }

        }
        StackLayout {
            id: stack
            Layout.fillWidth: parent.width
            Layout.fillHeight: parent.height
            currentIndex: tabBar.currentIndex

            Rectangle { color: "red"; }
            Rectangle { color: "#0ff"; }
            Rectangle { color: "#f0f"; }
        }
    }

}
