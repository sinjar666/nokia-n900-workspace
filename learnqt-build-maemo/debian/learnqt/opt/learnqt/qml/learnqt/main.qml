import Qt 4.7

Rectangle {
    id: rectangle3
    width: 360
    height: 640
    color: "#161515"
    Text {
        id: le_name
        color: "#f9f9f9"
        text: "Enter file name"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 19
        font.pointSize: 12
    }



    Rectangle {
        id: rectangle1
        width: 149
        height: 24
        color: "#201b1b"
        opacity: 1
        anchors.left: parent.left
        anchors.leftMargin: 157
        anchors.top: parent.top
        anchors.topMargin: 17
        TextInput {
            id: ti_fname
            color: "#ecde14"
            text: ""
            font.pointSize: 10
            cursorVisible: true
            clip: true
            smooth: true
            anchors.fill: parent
            //onTextChanged: console.log("change")
        }
    }

    Rectangle   {
        id:rect_te1
        width: 302
        height: 495
        color: "#221e1d"
        anchors.left: parent.left
        anchors.leftMargin: 33
        anchors.top: parent.top
        anchors.topMargin: 117
        TextEdit {
            id: text_edit1
            width:parent.width
            height: parent.height
            color: "#ffffff"
            text: ""
            font.pointSize: 10
            selectedTextColor: "#e8d906"
            font.family: "Ubuntu"
            selectionColor: "#67c821"
            textFormat: TextEdit.PlainText
            smooth: true
            clip: true
            cursorVisible: true
            anchors.fill: parent
            wrapMode: TextEdit.WordWrap
        }
    }



    Rectangle {
        id: rectangle2
        y: 61
        width: 105
        height: 34
        color: "#3b3182"
        anchors.left: parent.left
        anchors.leftMargin: 46
        anchors.top: parent.top
        anchors.topMargin: 61
        MouseArea   {
            id:openbutton
            anchors.fill: parent
            onClicked: text_edit1.text=worker.perform(ti_fname.text)
        }

        Text {
            id: btext3
            x: 37
            y: 1
            color: "#ffffff"
            text: "OPEN"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }




    Rectangle {
        id: rectangle5
        x: 0
        y: 63
        width: 105
        height: 34
        color: "#3b3182"
        anchors.top: parent.top
        anchors.topMargin: 61
        MouseArea {
            id: savebutton
            anchors.fill: parent
            onClicked: console.log(worker.performWrite(ti_fname.text,text_edit1.text))
        }

        Text {
            id: btext2
            color:"#ffffff"
            text: "SAVE"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
        anchors.leftMargin: 200
        anchors.left: parent.left
    }
}
