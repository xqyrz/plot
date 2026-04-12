import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import "./qml"
Rectangle {
    id:root
    anchors.fill: parent
    color: "#F0F0F0"
    // 参数
    property int leftWidth: 300
    property int rightSplitterWidth: 4
    property int bottomSplitterHeight: 4
    property int rightPanelWidth: width * 0.3
    property int topAreaHeight: 100
    property color bgcolor: "#e0e0e0"
    property color bdcolor: "#A0A0A0"
    RowLayout {
        spacing: 10
        width: parent.width
        height: parent.height-20
        // ===== 左侧固定区域 =====
        ToolBar {
            id:toolBar
            Layout.preferredWidth: root.leftWidth
            Layout.preferredHeight: parent.height

        }

        // ===== 右侧整体区域 =====
        Item {
            Layout.preferredWidth:parent.width-root.leftWidth-20
            Layout.preferredHeight:parent.height-10

            ColumnLayout{
                anchors.fill: parent
                spacing: 10
                // -------- 上半区域 --------

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight : true
                    // 主内容
                    Rectangle {
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
                    ToolPage{
                        x: parent.width - rightPanelWidth
                        y: 0
                        width: rightPanelWidth
                        height: parent.height
                    }

                }

                // -------- 下半区域 --------
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 100
                RowLayout {
                    width: parent.width-10
                    height: parent.height
                    spacing: 10
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight : true
                        ScrollView {
                            anchors.fill:parent
                            TextArea {
                                placeholderText: "发送数据"
                                wrapMode: TextArea.Wrap
                                font.pixelSize: 16
                                // 文本变化时自动滚动到底部
                                onTextChanged: {
                                    cursorPosition = length
                                    //positionViewAtEnd()
                                }
                            }
                        }

                    }
                    XButton {
                        text: "发送"
                        font.bold: true
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 70
                    }
                }
            }
            }
        }
        }
    Rectangle{
        anchors.bottom: parent.bottom
        width: parent.width
        height: 20
        color:root.bgcolor
        border.width: 2
        radius: 5
        border.color:root.bdcolor
    }
}
