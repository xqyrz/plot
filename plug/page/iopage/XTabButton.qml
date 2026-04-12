import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

TabButton {
    id:tabButton
    property color baseColor: "#E0E5EC"       // 背景色
    property color lightShadow: "#FFFFFF"     // 高光
    property color darkShadow: "#A3B1C6"      // 阴影
    property int radius: 8
    font.pixelSize: 8

    background: Item {
        anchors.fill: parent

        Rectangle {
            id: bg
            anchors.fill: parent
            radius: tabButton.radius
            color: tabButton.checked ?"#d0d5db": tabButton.baseColor
        }

        // 内凹/凸起效果
        DropShadow {
            anchors.fill: bg
            source: bg
            horizontalOffset: tabButton.checked ? 2 : -4
            verticalOffset: tabButton.checked ? 2 : -4
            radius: 8
            samples: 25
            color: tabButton.checked ? tabButton.darkShadow : tabButton.lightShadow
        }

        DropShadow {
            anchors.fill: bg
            source: bg
            horizontalOffset: tabButton.checked ? -2 : 4
            verticalOffset: tabButton.checked ? -2 : 4
            radius: 8
            samples: 25
            color: tabButton.checked ? tabButton.lightShadow : tabButton.darkShadow
        }
    }

    contentItem: Text {
        text: tabButton.text
        anchors.centerIn: parent
        color: tabButton.checked ? "#333333" : "#666666"
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent
        onClicked: tabButton.checked = true
    }
    scale: tabButton.checked ? 0.9 : 1.0
    onDownChanged: {
        console.log("DOW")
    }
    onPressed: tabButton.down =true
    onReleased: tabButton.down=false
}
