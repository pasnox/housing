import QtQuick 1.1

import "/opt/Qt4.8.4/imports/Qt/labs/components/"
import "/opt/Qt4.8.4/imports/Qt/labs/components.1.1/"
import "/opt/Qt4.8.4/imports/com/nokia/symbian.1.1/"
import "/opt/Qt4.8.4/imports/com/nokia/extras.1.1/"

import Qt.labs.components 1.1
import Qt.labs.components.native 1.1
import com.nokia.symbian 1.1
import com.nokia.extras 1.1

Window {
    id: window

    StatusBar {
        id: statusbar1
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    PageStack {
        id: page1
        x: 0
        y: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 48
        anchors.leftMargin: 0
        anchors.topMargin: 26
        anchors.fill: parent

        SelectionListItem {
            id: backend
            x: 0
            y: 11
            width: 360
            height: 68
            title: "Backend"
            subTitle: backendSelectionDialog.selectedIndex >= 0
                      ? backendSelectionDialog.model.get(backendSelectionDialog.selectedIndex).name
                      : "Please select a backend"
            onClicked: backendSelectionDialog.open()

            SelectionDialog {
                id: backendSelectionDialog
                titleText: "Select one of the values"
                selectedIndex: -1
                model: ListModel {
                    ListElement { name: "SeLoger.com" }
                }
            }
        }

        SelectionListItem {
            id: type
            x: 0
            y: 110
            width: 360
            height: 68
            title: "Type"
            subTitle: typeSelectionDialog.selectedIndex >= 0
                      ? typeSelectionDialog.model.get(typeSelectionDialog.selectedIndex).name
                      : "Please select a type"
            onClicked: typeSelectionDialog.open()

            SelectionDialog {
                id: typeSelectionDialog
                titleText: "Select one of the types"
                selectedIndex: -1
                model: ListModel {
                    ListElement { name: "Rent" }
                    ListElement { name: "Purchase" }
                }
            }
        }

        SelectionListItem {
            id: properties
            x: 0
            y: 191
            width: 360
            height: 68
            title: "Type"
            subTitle: propertiesSelectionDialog.selectedIndex >= 0
                      ? propertiesSelectionDialog.model.get(propertiesSelectionDialog.selectedIndex).name
                      : "Please select properties"
            onClicked: propertiesSelectionDialog.open()

            SelectionDialog {
                id: propertiesSelectionDialog
                titleText: "Select one or more properties"
                selectedIndex: -1
                model: ListModel {
                    ListElement { name: "All" }
                    ListElement { name: "Appartement" }
                    ListElement { name: "Maison" }
                    ListElement { name: "Parking" }
                    ListElement { name: "Terrain" }
                    ListElement { name: "Boutique" }
                    ListElement { name: "Local commercial" }
                    ListElement { name: "Bureaux" }
                    ListElement { name: "Loft" }
                    ListElement { name: "Immeuble" }
                    ListElement { name: "Batiment" }
                    ListElement { name: "Chateau" }
                    ListElement { name: "Hotel particulier" }
                    ListElement { name: "Divers" }
                }
            }
        }

        CheckableListViewPopup {
            id: popupDialog
        }

        Button {
            id: button
            text: "push me"

            onClicked: popupDialog.open()
        }
    }

    ToolBar {
        x: -71
        y: 462
        height: 48
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }



}


