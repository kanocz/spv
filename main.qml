import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.3

Window {
    visible: true
    title: "Image viewer"
    id: window
    objectName: "window"
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
            autoTransform: true
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
                    flickable.contentX = (image.width - window.width) / 2
                    flickable.contentY = (image.height - window.height) / 2
                } else {
                    image.fillMode = Image.PreserveAspectFit
                    image.width = window.width
                    image.height = window.height
                    flickable.contentX = 0
                    flickable.contentY = 0
                }
            }

            onSourceChanged: {
                image.fillMode = Image.PreserveAspectFit
                image.width = window.width
                image.height = window.height
                flickable.contentX = 0
                flickable.contentY = 0
                loading.visible = false
            }

            function selectFolder() {
                fileDialog.open()
                return fileDialog.folder
            }

            focus: true
        }
    }
    Text {
        id: loading
        objectName: "loading"
        text: "Loading..."
        font.pointSize: 20
        color: "white"
        style: Text.Raised
        styleColor: "black"
        anchors.centerIn: parent
        visible: false
    }
}

