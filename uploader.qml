import QtQuick 2.0
import QtQuick.Window 2.3
//import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.2


import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
//import QtQuick.Controls.Material 2.1
//import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1


import infinibrains.doceditor.com 1.0
import infinibrains.doceditor.compress.com 1.0



ApplicationWindow {
    id: windowUploader
    width: 620
    minimumWidth: 360
    maximumWidth: 360
    minimumHeight: 520
    maximumHeight: 520
    visible: true
    title: "DOCEDITOR"


    // Reference to FOLDERCOMPRESS
    FolderCompressor {
         id: folderCompressor
    }


    // TOP
    header: ToolBar {
    //    Material.foreground: "white"

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
               // source: "images/LogoUpload2.png"
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
               // source: "images/LogoUpload.png"
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                Layout.topMargin: 15

                anchors {

                    left: parent.left
                    margins: 75
                 }


            }



            ToolButton {
                Layout.topMargin: 15

                contentItem: Image {
                    fillMode: Image.Pad
                    source: "images/Logout.png"
                }
                anchors {
                    right: parent.right
                    margins: 30
                }
                onClicked: optionsMenu.open()
            }


        }


    }

    // Reference to Settings
    Settings {
         id: settings
    }

    // WELCOME USER
    Rectangle {
        id: welcomeUser
        width: 360
        height: 50
        color: "#eeeeee"

        Text {
            anchors.fill:parent
            font.family: "Helvetica"
            font.pointSize: 11
            text:  qsTr("Welcome " + settings.value("userName") + " Let's Start?")
            anchors.topMargin: 28
            anchors.leftMargin: 30
            color: "#808080"

        }


    }

    // EXAM TYPE
    Text {
        id: examType
        font.family: "Helvetica"
        font.pointSize: 13
        text:  qsTr("Exam Type")
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 30
        color: "#000000"
        anchors.top: welcomeUser.bottom

    }



    ToolBar{
        id: examTypeButtons
        x: 0
        anchors.top: examType.bottom
        width: parent.width
        anchors.topMargin: 3
        spacing: 20



        RowLayout{
            anchors.left: parent.left
            anchors.leftMargin: 22

            ToolButton{
                text: "Tomografia"
                id: examTC
                Image{
                    id: iconExamSelectedTC;
                    anchors.left: rect1.left
                    anchors.topMargin: 20
                    visible: false
                    source: "images/selectedexam.png"
                    //fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignVCenter


                }
                onClicked: {
                    settings.setValueExam("examType", "tomografia")
                    iconExamSelectedTC.visible = true
                    iconExamSelectedRess.visible = false
                    iconExamSelectedUltra.visible = false
                   // console.log(settings.value(("examType")));
                }


            }
            ToolButton{
                text: "Ressonancia"
                id: examRess
                Image{
                    id: iconExamSelectedRess;
                    anchors.left: rect1.left
                    anchors.topMargin: 20
                    source: "images/selectedexam.png"
                    visible: false
                    //fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignVCenter


                }
                onClicked: {
                    settings.setValueExam("examType", examRess.text)
                    iconExamSelectedTC.visible = false
                    iconExamSelectedRess.visible = true
                    iconExamSelectedUltra.visible = false
                 //   console.log(settings.value(("examType")));
                }


            }
            ToolButton{
                text: "Ultrasom"
                id: examUltra
                Image{
                    id: iconExamSelectedUltra;
                    anchors.left: rect1.left
                    anchors.topMargin: 20
                    source: "images/selectedexam.png"
                    visible: false
                    //fillMode: Image.PreserveAspectFit
                    verticalAlignment: Image.AlignVCenter


                }
                onClicked: {
                    settings.setValueExam("examType", examUltra.text)
                    iconExamSelectedTC.visible = false
                    iconExamSelectedRess.visible = false
                    iconExamSelectedUltra.visible = true
                //    console.log(settings.value(("examType")));
                }


            }
        }

    }




    // REFERENCES
  //  Text {
    //    id: txtReference
     //   anchors.top: examTypeButtons.bottom
     //   font.family: "Helvetica"
     //   anchors.topMargin: 10
     //   font.pointSize: 13
     //   text:  qsTr("Reference")
     //   anchors.left: parent.left
     //   anchors.leftMargin: 30
   // }

   // TextField {
   //      id: txtFieldReference
         //placeholderText: "Enter name"
    //     anchors.left: parent.left
    //     anchors.top: txtReference.bottom
    //     anchors.leftMargin: 30
    //     width: 280
  //  }

    // DESCRIPTION
    Text {
        id: txtDescription
        y: 157
        //  anchors.top: txtFieldReference.bottom
        font.family: "Helvetica"
        anchors.topMargin: 10
        font.pointSize: 13
        text:  qsTr("Description")
        anchors.left: parent.left
        anchors.leftMargin: 30
    }

    TextArea {
        width: 313
        height: 44
        anchors.topMargin: -2
        id: txtAreaDescription
        anchors.top: txtDescription.bottom
        anchors.left: parent.left
        anchors.leftMargin: 22

    }


    Button {
        id: btnUpload
        text: "Upload Server"
        anchors.horizontalCenterOffset: -1
        width: 172
        height: 56
        property string source
        anchors.top: txtAreaDescription.bottom
        anchors.horizontalCenter: txtAreaDescription.horizontalCenter
        anchors.topMargin: 40
        onClicked: {

            // CREATE EXAM SYSTEM


            if(folderCompressor.compressT()===true){
             createExam();
            }




        }

        Image {
            id: iconUpload
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent.left
            sourceSize.height: btnUpload.background.height - 10
            height: sourceSize.height
            source: "images/UploadIcon.png"

        }

    }


    // PROGRESSBAR
    Column {
        anchors.topMargin: 20
        spacing: 10
        width: parent.width
        anchors.top: btnUpload.bottom
        anchors.horizontalCenter: txtAreaDescription.horizontalCenter
        id: progressbarUpload
    }

    // CANCEL BUTTON



    // CREATE EXAM
    function createExam()
    {

        var doc = new XMLHttpRequest();

        doc.onreadystatechange = function() {
            if (doc.readyState === XMLHttpRequest.DONE) {

                console.log("JSON CREAT EXAM: " + doc.responseText);
                var JsonObject = JSON.parse(doc.responseText);

                // set ExamID to settings
                settings.setValueExamID("examId", JsonObject.data["exam_id"]);

                if(JsonObject["error"] !== "")
                {
                    passwordError.text = "ERROR IN CREATE EXAM";
                    passwordError.color =  "red";
                    return false;
                }

            folderCompressor.on_selecionarpasta_clicked();
            return true;
            }

        }

        doc.open("POST", "https://www.docdo.com.br/v3/process/api.php");
        doc.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        var params = "api=createexam&token=" + settings.valueToken("Token") +"&type="+settings.value("examType") + "&patient_id=" +settings.value("Id") + "&description="+txtAreaDescription.text;
        doc.send(params);
        //console.log("api=createexam&token=" + settings.valueToken("Token") +"&type="+settings.value("examType") + "&patient_id=" +settings.value("Id") + "&description="+"TESTE USANDO QT QUICK Marquinhos");



    }


    // UPLOAD COMPLETED
   /* function uploadCompleted()
    {

        var doc = new XMLHttpRequest();

        doc.onreadystatechange = function() {
            if (doc.readyState == XMLHttpRequest.DONE) {

                console.log("JSON FINISHED EXAM: " + doc.responseText);

            }

        }

        doc.open("POST", "https://www.docdo.com.br/v3/process/api.php");
        doc.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
        var params = "api=finishedupload&exame_id="+settings.valueExamID("examId")+"&token="+settings.valueToken("Token");
        doc.send(params);


    }*/




}
