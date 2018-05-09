import QtQuick 2.7
import QtQuick 2.0

import QtQuick.Window 2.3
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.2


import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0


ApplicationWindow {
    id: windowDownloader
    minimumWidth: 360
    maximumWidth: 360
    minimumHeight: 520
    maximumHeight: 520
    visible: true
    title: "DOWNLOADER"


Settings{
id:settings
}

    // TOP
        header: ToolBar {
            Material.foreground: "white"

            background: Rectangle {
                height: 80
                gradient: Gradient {
                    GradientStop { position: 0 ; color: "#262a32" }
                    GradientStop { position: 1 ; color: "#262a32" }
                }
            }

            RowLayout {
                anchors.fill: parent
                Image {
                    id: logo
                    source: "images/LogoUpload2.png"
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 50
                    Layout.topMargin: 15

                    anchors {
                        left: parent.left
                        margins: 30
                    }

                }

                Image {
                    id: logoDocdo
                    source: "images/LogoUpload.png"
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 40
                    Layout.topMargin: 15

                    anchors {

                        left: parent.left
                        margins: 75
                     }

                }

                Image {
                    id: logodown
                    source: "images/icondownload.png"
                    Layout.topMargin: 15
                    anchors {
                        margins: 95
                     }


                }






            }
        }

/*
        ListModel {
            id:contactModel
            ListElement {
                name: "Exame A"
                Type: "Ressonancia"
            }
            ListElement {
                name: "Exame B"
                Type: "Tomografia"
            }
            ListElement {
                name: "Exame C"
                Type: "Ressonancia"
            }
        }
*/

        Rectangle {
            x: 0
            y: -22
            width: 378; height: 379

            Component {
                id: contactDelegate
                Item {
                    width: 360; height: 40
                    Column {
                        width: 378
                        Text { text: '<b>Name:</b> ' + name }
                        Text { text: '<b>Type:</b> ' + Type }
                    }
                }
            }

            ListView {
                width: 800
                anchors.leftMargin: 0
                anchors.topMargin: 40
                anchors.rightMargin: 0
                anchors.bottomMargin: 25
                anchors.fill: parent
                model: downloads
                delegate: contactDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

                focus: true
            }
        }


        Button {
                id: btnDownload
                text: "Download"
                anchors.horizontalCenterOffset: -70
                width: 140
                property string source
                x: 40
                y: 375
                //anchors.top: txtAreaDescription.bottom
                //anchors.horizontalCenter: txtAreaDescription.horizontalCenter
                //anchors.topMargin: 19
                onClicked: {




                }



            }

            Button {
                id: btnCancel
                text: "Cancelar"
                anchors.horizontalCenterOffset: 76
                width: 140
                property string source
                x: 186
                anchors.top: btnUpload.bottom
                //anchors.horizontalCenter: txtAreaDescription.horizontalCenter
                anchors.topMargin: -48
                onClicked: {





                }

}
}
