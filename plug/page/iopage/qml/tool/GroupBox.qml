import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle{
    Layout.leftMargin: 5
    Layout.topMargin: 10
    Layout.minimumHeight: 50
    width:parent.width-10
    property alias title:titleItem.text
    border.width:1
    color:"transparent"
    Rectangle {
        x:20
        y:-5
        height:20
        width:60
        color:"#F0F0F0"
        Text {
            id:titleItem
            text: "设备配置"

        }
    }
}