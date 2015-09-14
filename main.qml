import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    title: "Image viewer"
    id: window
    visibility: "Maximized"
    color: "#000000"

    signal moveForward()
    signal moveBackward()

    Image {
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        Keys.onLeftPressed: window.moveBackward()
        Keys.onRightPressed: window.moveForward()
        Keys.onEscapePressed: window.close()
        focus: true
    }
}

