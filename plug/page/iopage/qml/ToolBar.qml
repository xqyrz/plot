import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "./tool"
Item {
    id:root
    width:300
    height:1000
    ColumnLayout {
        anchors.fill:parent
        spacing: 10
        Layout.margins:5
        //contrl dev
        GroupBox{
            title:"设备配置"
        }
        GroupBox{
            title:"接收设置"
        }
        GroupBox{
            title:"工具使用"
            Layout.fillHeight: true
            Layout.fillWidth: true  // 填充剩余空间
        }
        GroupBox{
            Layout.bottomMargin: 5
            title:"发送设置"
        }

    }

}
