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
    signal moveHome()
    signal moveEnd()

    Image {
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        Keys.onLeftPressed: window.moveBackward()
        Keys.onRightPressed: window.moveForward()
        Keys.onUpPressed: window.moveHome()
        Keys.onDownPressed: window.moveEnd()
        Keys.onEscapePressed: window.close()
        focus: true
    }
}

