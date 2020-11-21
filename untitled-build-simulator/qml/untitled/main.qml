import QtQuick 1.0

Rectangle {
    id: page
    width: 640
    height: 1280
    color: "#383838"

    Flickable   {
        id: flick1
        width: parent.width
        height:parent.height
        contentWidth: 640
        contentHeight: 1280

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: parent.width
        height: 1086
        color: "#ffffff"
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: image1
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "suji.png"

            MouseArea {
                id: yog1
                x: 263
                y: 7
                width: 70
                height: 74
                onClicked: page.state='State1'
            }

            MouseArea {
                id: yog2
                x: 0
                y: 498
                width: 56
                height: 83
                onClicked: page.state='State1'
            }

            MouseArea {
                id: yog3
                x: 478
                y: 481
                width: 97
                height: 136
                onClicked: page.state='State1'
            }
        }
    }

    Text {
        id: t_head
        x: 426
        color: "#d7cb19"
        text: "BAKRA"
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 22
    }
    Text {
        id: t_result
        x: 266
        y: 1200
        text: "Bakra khoj"
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pixelSize: 18
        color: "#ffffff"
        Timer   {
            id: time1
            interval: 3000
            running: false
            onTriggered: page.state=""
        }
    }

    Rectangle {
        id: rectangle2
        x: 53
        y: 1214
        width: 162
        height: 35
        color: "#ffffff"

        Text {

            id: text_input1
            anchors.fill: parent
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle3
        x: 450
        y: 1208
        width: 93
        height: 55
        color: "#ffffff"

        MouseArea {
            id: mouse_area1
            anchors.fill: parent
            onClicked: console.log(factorial.fact)

    }
    }
    }

    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: t_result
                text: "Sahi pakda..:))"
            }
            PropertyChanges {
                target: time1
                running: true

            }
        }
    ]
}

