import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Button {
    id: control
    width: 100
    height: 60
    text: "Neumorphic"
    font.pixelSize: 22

    property color baseColor: "#E0E5EC"       // 背景色
    property color lightShadow: "#FFFFFF"     // 高光
    property color darkShadow: "#A3B1C6"      // 阴影
    property int radius: 15

    background: Item {
        anchors.fill: parent
        Rectangle {
            id: bg
            anchors.fill: parent
            radius: control.radius
            color: control.down ?"#e0e9e9":control.baseColor
            border.width: 2
            border.color: "#d6d6d6"
        }

        // 上左高光
        DropShadow {
            anchors.fill: bg
            source: bg
            horizontalOffset: control.down ? -2 : -6
            verticalOffset: control.down ? -2 : -6
            radius: 15
            samples: 25
            color: control.lightShadow
        }

        // 下右阴影
        DropShadow {
            anchors.fill: bg
            source: bg
            horizontalOffset: control.down ? 2 : 6
            verticalOffset: control.down ? 2 : 6
            radius: 15
            samples: 25
            color: control.darkShadow
        }

        // 按下时内凹效果
        Rectangle {
            anchors.fill: parent
            radius: control.radius
            color: "transparent"
            border.width: control.down ? 2 : 0
            border.color: "#B8C6DB"
        }
    }
    contentItem: Text {
        text: control.text
        font: control.font
        color: "#004700"        // 字体颜色
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }

    Behavior on scale {
        NumberAnimation { duration: 100 }
    }

    scale: control.down ? 0.93 : 1.0
}
