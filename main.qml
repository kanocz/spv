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
    Flickable {
        anchors.fill: parent
        id: flickable
        contentWidth: image.width
        contentHeight: image.height

        Image {
            x: 0
            y: 0
            id: image
            objectName: "image"
            fillMode: Image.PreserveAspectFit
            width: window.width
            height: window.height
            Keys.onLeftPressed: window.moveBackward()
            Keys.onRightPressed: window.moveForward()
            Keys.onUpPressed: window.moveHome()
            Keys.onDownPressed: window.moveEnd()
            Keys.onEscapePressed: window.close()
            Keys.onSpacePressed: {
                if (image.fillMode == Image.PreserveAspectFit) {
                    image.fillMode = Image.Pad
                    image.width = image.sourceSize.width
                    image.height = image.sourceSize.height

                } else {
                    image.fillMode = Image.PreserveAspectFit
                    image.width = window.width
                    image.height = window.height
                    flickable.contentX = 0
                    flickable.contentY = 0
                }
            }

            focus: true
        }
    }
}

