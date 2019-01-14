import QtQuick 2.3
import QtQuick.Window 2.2

Window {

    visible: true
    width: 200
    height: 100

    Button {
        anchors.centerIn: parent
        id: button
        text: "Start"
        onClicked: {
            status.text = "Button clicked!"
        }
    }

    Text {
        anchors.top: button.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: button.horizontalCenter
        id: status
        width: 100; height: 20
        text: "waiting ..."
        horizontalAlignment: Text.AlignHCenter
    }
}
