import QtQuick 2.15
import QtQuick.Controls 2.15
import "./qml"
Rectangle {
    id:root
    anchors.fill: parent
    color: "#F0F0F0"
    // 参数
    property int leftWidth: 220
    property int rightSplitterWidth: 4
    property int bottomSplitterHeight: 4
    property int rightPanelWidth: width * 0.3
    property int topAreaHeight: height * 0.8

    // ===== 左侧固定区域 =====
    ToolBar {
        x: 0
        y: 0
        width: root.leftWidth
        height: root.height
    }

    // ===== 右侧整体区域 =====
    Item {
        x: leftWidth
        y: 0
        width: parent.width - leftWidth
        height: parent.height

        // -------- 上半区域 --------
        Item {
            x: 0
            y: 0
            width: parent.width
            height: topAreaHeight

            // 主内容
            Rectangle {
                x: 0
                y: 0
                width: parent.width - rightPanelWidth - rightSplitterWidth
                height: parent.height
                color: "white"
            }

            // 竖向分隔条
            Rectangle {
                x: parent.width - rightPanelWidth - rightSplitterWidth
                y: 0
                width: rightSplitterWidth
                height: parent.height
                color: "#F0F0F0"

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.SizeHorCursor
                    drag.target: parent
                    drag.axis: Drag.XAxis
                    drag.minimumX: 100
                    drag.maximumX: parent.parent.width - 80

                    onPositionChanged: {
                        rightPanelWidth =
                            parent.parent.width - parent.x - rightSplitterWidth
                    }
                }
            }

            // 右侧可调区域
            Rectangle {
                x: parent.width - rightPanelWidth
                y: 0
                width: rightPanelWidth
                height: parent.height
                color: "white"
            }
        }

        // -------- 横向分隔条 --------
        Rectangle {
            x: 0
            y: topAreaHeight
            width: parent.width
            height: bottomSplitterHeight
            color: "#F0F0F0"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SizeVerCursor
                drag.target: parent
                drag.axis: Drag.YAxis
                drag.minimumY: 100
                drag.maximumY: parent.parent.height - 100

                onPositionChanged: {
                    topAreaHeight = parent.y
                }
            }
        }

        // -------- 下半区域 --------
        Rectangle {
            x: 0
            y: topAreaHeight + bottomSplitterHeight
            width: parent.width
            height: parent.height - y
            color: "transparent"
        }
    }
}
