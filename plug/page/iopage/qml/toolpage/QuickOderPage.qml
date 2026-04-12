import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0  // Qt5.15 需此模块支持 TableModel

Item {
    id: root
    // 1. 定义数据模型（与截图数据完全一致）
    TableModel {
        id: tableModel
        TableModelColumn { role: "name"; title: "名称" }
        TableModelColumn { role: "data"; title: "数据" }

        rows: [
            { name: "版本显示", data: "EE B1 10 00 01 00 08 B0 B6 B1 BE FF FC FF FF" },
            { name: "画面2:等待插枪画面", data: "EE B1 00 00 01 FF FC FF FF" },
            { name: "画面3:查询订单号", data: "EE B1 00 00 02 FF FC FF FF" },
            { name: "画面4:", data: "EE B1 00 00 03 FF FC FF FF" },
            { name: "画面5:检测中", data: "EE B1 00 00 04 FF FC FF FF" }
        ]
    }

    // 2. 表格主体（核心控件）
    TableView {
        id: tableView
        anchors.fill: parent
        anchors.margins: 10
        model: tableModel
        selectionMode: TableView.SingleSelection  // 单选模式
        clip: true  // 防止内容溢出

        // 表头样式
        headerDelegate: Rectangle {
            height: 30
            color: "#e0e0e0"
            border.color: "#a0a0a0"
            Text {
                anchors.centerIn: parent
                text: model.title
                font.bold: true
                font.pixelSize: 12
                elide: Text.ElideRight
            }
        }

        // 行样式（选中高亮）
        rowDelegate: Rectangle {
            color: styleData.selected ? "#3daee9" : (styleData.row % 2 === 0 ? "#ffffff" : "#f5f5f5")
            border.color: "#e0e0e0"
            border.width: 1
        }

        // 3. 列定义
        TableColumn {
            role: "name"
            title: "名称"
            width: 200
            // 名称列委托（支持图标+文本，还原截图左侧小图标）
            delegate: Item {
                anchors.fill: parent
                Image {
                    id: icon
                    width: 16
                    height: 16
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    source: "qrc:/icons/setting.png"  // 替换为你的图标资源，无资源可隐藏
                    visible: true
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon.right
                    anchors.leftMargin: 5
                    text: styleData.value
                    font.pixelSize: 12
                    elide: Text.ElideRight
                    color: styleData.selected ? "white" : "black"
                }
            }
        }

        TableColumn {
            role: "data"
            title: "数据"
            width: 400
            // 数据列委托（十六进制 monospace 字体，更符合工程师习惯）
            delegate: Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                text: styleData.value
                font.family: "Consolas, 'Courier New', monospace"  // 等宽字体
                font.pixelSize: 12
                elide: Text.ElideRight
                color: styleData.selected ? "white" : "black"
            }
        }

        TableColumn {
            title: "快捷键"
            width: 80
            // 快捷键列委托（垂直排列的箭头按钮，还原截图样式）
            delegate: Column {
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2  // 按钮间距

                // 上箭头按钮
                Button {
                    id: btnUp
                    width: 24
                    height: 24
                    flat: true  // 扁平样式
                    ToolTip.text: "上移"  // 鼠标悬浮提示

                    contentItem: Text {
                        text: "▲"
                        font.pixelSize: 10
                        color: btnUp.pressed ? "darkblue" : "black"
                    }

                    onClicked: {
                        let row = styleData.row;
                        if (row > 0) {
                            tableModel.moveRow(row, row - 1);  // 行上移
                            tableView.currentRow = row - 1;     // 保持选中状态
                        }
                    }
                }

                // 下箭头按钮
                Button {
                    id: btnDown
                    width: 24
                    height: 24
                    flat: true
                    ToolTip.text: "下移"

                    contentItem: Text {
                        text: "▼"
                        font.pixelSize: 10
                        color: btnDown.pressed ? "darkblue" : "black"
                    }

                    onClicked: {
                        let row = styleData.row;
                        if (row < tableModel.rowCount - 1) {
                            tableModel.moveRow(row, row + 1);
                            tableView.currentRow = row + 1;
                        }
                    }
                }
            }
        }
    }
}
