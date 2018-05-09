import QtQuick 2.0
//import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.2


import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
//import QtQuick.Controls.Material 2.1
//import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0
import QtQuick.Controls 2.2

import infinibrains.doceditor.com 1.0


ApplicationWindow {
    id: windowPassword
    minimumWidth: 360
    maximumWidth: 360
    minimumHeight: 520
    maximumHeight: 520
    visible: true
    title: "DOCEDITOR"
    background: BorderImage {
        source: "images/Backgorund.png"
    }

    Loader {
        id: windowPasswordLoader
        //source: "main.qml"

    }


    StackView {
        id: stackView
        anchors.fill: parent

            Image {
                id: logo
                width: 200
                height: 200
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -80
                fillMode: Image.PreserveAspectFit
                       }

            TextField {
                id: password
                width: 230
//                text: backend.userName
//                onTextChanged: backend.userName = text
                placeholderText: "Password"
                echoMode: TextInput.Password
                anchors.horizontalCenter: logo.horizontalCenter
                anchors.top: logo.bottom
                anchors.topMargin: 5
                background: Rectangle {
                            radius: 4
                            color: "#fffafa"
                        }
                Keys.onPressed: if (event.key === Qt.Key_Return) { loadWindowUploader(); }


            }

            Label {
                id: passwordError
                font.pointSize: 14
                anchors.top: password.bottom
                anchors.horizontalCenter: password.horizontalCenter
                anchors.topMargin: 5
            }

            // Reference to Settings
            Settings {
                 id: settings
            }



            Button {
                id: enterPassword
                text: "ENTER"
                highlighted: true
                anchors.horizontalCenter: password.right
                anchors.top: password.bottom
                anchors.topMargin: 30
                background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 25
                            radius: 4
                            color: "#003961"
                }


                onClicked: loadWindowUploader();

            }


    }


    // Show Window Passwrod if name exist
    function loadWindowUploader()
    {

        if(password.text == "")
        {
            passwordError.text = "CAMPO VAZIO";
            passwordError.color =  "red";

        }
       else{
            var doc = new XMLHttpRequest();

            doc.onreadystatechange = function() {
                if (doc.readyState == XMLHttpRequest.DONE) {

                   // console.log("JSON: " + doc.responseText);
                    var JsonObject = JSON.parse(doc.responseText);

                    console.log("TOKEN: " + JsonObject.data["token"]);
                   // console.log("ID: " + JsonObject.data["id"]);


                    if(JsonObject["error"] != "")
                    {
                        passwordError.text = "PASSWORD INVÁLIDO";
                        passwordError.color =  "red";
                        return;
                    }

                    // Set TOKEN and ID to settings for CreateExam
                    settings.setValueToken("Token", JsonObject.data["token"]);
                    settings.setValueId("Id", JsonObject.data["id"]);

                    windowMain.close();
                    windowMainLoader.source = "uploader.qml"



                }
            }

            doc.open("POST", "https://api.php");
            doc.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
            var params = "api=xxxxxxx&login=" + settings.value("userName") +"&password="+password.text;

            doc.send(params);

        }
    }


}
