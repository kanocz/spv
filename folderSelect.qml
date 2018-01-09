import QtQuick.Dialogs 1.3
import QtQuick.Window 2.2


Window {
    visible: true
    title: "Image viewer"
    id: fswindow
    visibility: "Maximized"
    color: "#000000"

    signal folderSelected(string folder)
    function openit() {
        fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        objectName: "fileDialog"
        title: "Please choose folder with images"
        folder: shortcuts.pictures
        selectFolder: true
        visible: false
        onAccepted: {
            fswindow.hide()
            fswindow.folderSelected(fileDialog.folder)
        }
        onRejected: {
            Qt.quit()
        }
    }
}
