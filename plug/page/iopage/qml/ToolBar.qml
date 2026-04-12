import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "./tool"
import "../"
Item {
    id:root
    width:200
    height:1000
    ColumnLayout {
        anchors.fill:parent
        spacing: 10
        Layout.margins:5
        //contrl dev
        GroupBox{
            title:"设备配置"
            height:340
            Layout.fillWidth: true  // 填充剩余空间
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 0

                // 串口号
                RowLayout {
                    anchors.margins: 0
                    Label {
                        text: "串口号"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "COM17 #蓝牙" }
                            ListElement { text: "COM1" }
                            ListElement { text: "COM3" }
                            ListElement { text: "COM5" }
                        }
                        currentIndex: 0
                    }
                }

                // 波特率
                RowLayout {
                    Label {
                        text: "波特率"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "1152000" }
                            ListElement { text: "921600" }
                            ListElement { text: "115200" }
                            ListElement { text: "38400" }
                            ListElement { text: "9600" }
                        }
                        currentIndex: 0
                    }
                }

                // 数据位
                RowLayout {
                    Label {
                        text: "数据位"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "8" }
                            ListElement { text: "7" }
                            ListElement { text: "6" }
                            ListElement { text: "5" }
                        }
                        currentIndex: 0
                    }
                }

                // 停止位
                RowLayout {
                    Label {
                        text: "停止位"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "1" }
                            ListElement { text: "1.5" }
                            ListElement { text: "2" }
                        }
                        currentIndex: 0
                    }
                }

                // 校验位
                RowLayout {
                    Label {
                        text: "校验位"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "NONE" }
                            ListElement { text: "ODD" }
                            ListElement { text: "EVEN" }
                            ListElement { text: "MARK" }
                            ListElement { text: "SPACE" }
                        }
                        currentIndex: 0
                    }
                }

                // 流控制
                RowLayout {
                    Label {
                        text: "流控制"
                        font.pixelSize: 12
                        Layout.preferredWidth: 40
                    }
                    ComboBox {
                        Layout.fillWidth: true
                        textRole: "text"
                        model: ListModel {
                            ListElement { text: "NONE" }
                            ListElement { text: "RTS/CTS" }
                            ListElement { text: "XON/XOFF" }
                        }
                        currentIndex: 0
                    }
                }

                // 打开按钮区域
                    XButton {
                        text: "   打开   "
                        font.pixelSize: 18
                        padding: 15
                        Layout.alignment: Qt.AlignRight
                        //Layout.rightMargin: 20
                        Layout.preferredWidth:60
                        onClicked: {
                            console.log("打开串口: " + comboPort.currentText);
                        }
                    }
            }
        }
        GroupBox{
            title:"接收设置"
            Layout.fillWidth: true  // 填充剩余空间
        }
        GroupBox{
            title:"工具使用"
            Layout.fillHeight: true
            Layout.fillWidth: true  // 填充剩余空间
        }
        GroupBox{
            Layout.bottomMargin: 5
            title:"发送设置"
            height:200
            // 核心：GridLayout 网格布局
            GridLayout {
                anchors.fill: parent
                anchors.margins: 20
                // 列数：2列（适配标签/控件、辅助元素的排版）
                columns: 2
                // 行间距/列间距
                rowSpacing: 15
                columnSpacing: 10

                // 第一行：ASCII / HEX 单选（跨2列）
                RowLayout {
                    Layout.columnSpan: 2  // 跨2列显示
                    Layout.fillWidth: true
                    spacing: 40

                    RadioButton {
                        id: radioAscii
                        text: "ASCII"
                        font.pixelSize: 14
                        checked: true
                    }

                    RadioButton {
                        id: radioHex
                        text: "HEX"
                        font.pixelSize: 14
                        checked: false
                    }
                }

                // 第二行：FILE 单选（跨2列）
                RadioButton {
                    Layout.columnSpan: 2
                    text: "FILE #传输文件"
                    font.pixelSize: 14
                    checked: false
                }

                // 第三行：自动解析转义符 + 信息图标
                CheckBox {
                    text: "自动解析转义符"
                    font.pixelSize: 14
                    checked: false
                }
                // 信息图标 (i)
                Rectangle {
                    width: 32
                    height: 32
                    radius: 16
                    color: "transparent"
                    border.color: "#666"
                    border.width: 2
                    Text {
                        text: "i"
                        font.pixelSize: 20
                        font.bold: true
                        anchors.centerIn: parent
                    }
                    ToolTip.visible: hovered
                    ToolTip.text: "自动解析 \\n、\\r、\\t 等转义字符"
                }

                // 第四行：自动发送附加位（跨2列）
                CheckBox {
                    Layout.columnSpan: 2
                    text: "自动发送附加位"
                    font.pixelSize: 14
                    checked: false
                }

                // 第五行：循环周期 + 输入框 + 单位
                CheckBox {
                    text: "循环周期"
                    font.pixelSize: 14
                    checked: false
                    id: checkCycle
                }
                RowLayout {
                    spacing: 10
                    Layout.alignment: Qt.AlignLeft

                    TextField {
                        id: editCycle
                        text: "1000"
                        font.pixelSize: 20
                        width: 100
                        background: Rectangle {
                            color: "white"
                            border.color: "#999"
                        }
                        enabled: checkCycle.checked
                    }

                    Label {
                        text: "ms"
                        font.pixelSize: 20
                    }
                }

                // 第六行：快捷指令 + 历史发送（跨2列）
                RowLayout {
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    spacing: 40
                    Layout.topMargin: 10

                    Text {
                        text: "快捷指令"
                        font.pixelSize: 14
                        color: "#0000ff"
                        font.underline: true
                        MouseArea {
                            anchors.fill: parent
                            onClicked: console.log("打开快捷指令面板")
                        }
                    }

                    Text {
                        text: "历史发送"
                        font.pixelSize: 14
                        color: "#0000ff"
                        font.underline: true
                        MouseArea {
                            anchors.fill: parent
                            onClicked: console.log("打开历史发送记录")
                        }
                    }
                }
            }
        
        }

    }

}
