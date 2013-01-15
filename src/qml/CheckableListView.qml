import QtQuick 1.1
import Qt.labs.components 1.1
import Qt.labs.components.native 1.1

Item {
    ListView {
        id: checkableListView
        width: 180
        height: 400
        model: checkableListViewItemModel
        delegate: checkableListViewItemDelegate
        focus: true

        ListModel {
            id: checkableListViewItemModel

            ListElement {
                name: "Bill Smith"
                check: false
            }

            ListElement {
                name: "John Brown"
                check: false
            }

            ListElement {
                name: "Sam Wise"
                check: false
            }
        }

        Component {
            id: checkableListViewItemDelegate

            CheckBox {
                id: itemCheckBox
                width: 180
                height: 40
                checked: check
                pressed: itemMouseArea.pressed
                text: name

                MouseArea {
                    id: itemMouseArea
                    anchors.fill: parent

                    onClicked: itemCheckBox.checked = !itemCheckBox.checked
                }
            }
        }
    }
}
