import QtQuick 1.1
import com.nokia.symbian 1.1

CommonDialog {
    id: popup
    titleText: "Choose one or more values"
    buttons: [
        Button {
            id: closeButton
            text: "Close"

            onClicked: popup.accept()
        }
    ]

    CheckableListView {
        id: view
    }

    onClickedOutside: popup.accept()
}
