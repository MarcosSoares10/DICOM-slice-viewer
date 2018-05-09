import QtQuick 2.0
//import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.2


import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
//import QtQuick.Controls.Material 2.1
//import QtQuick.Controls.Universal 2.1
import Qt.labs.settings 1.0

import infinibrains.doceditor.com 1.0

ApplicationWindow {
    id: windowMain
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
        id: windowMainLoader
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
                id: email
                width: 230
//                text: backend.userName
//                onTextChanged: backend.userName = text
                placeholderText: "Email"
                anchors.horizontalCenter: logo.horizontalCenter
                anchors.top: logo.bottom
                anchors.topMargin: 5
                background: Rectangle {
                            radius: 4
                            color: "#fffafa"
                        }
                Keys.onPressed: if (event.key === Qt.Key_Return) { loadWindowPassword(); }


            }

            Label {
                id: emailError
                font.pointSize: 14
                anchors.top: email.bottom
                anchors.horizontalCenter: email.horizontalCenter
                anchors.topMargin: 5
            }

            // Reference to Settings
            Settings {
                 id: settings
            }



            Button {
                id: enterEmail
                text: "ENTER"
                highlighted: true
                anchors.horizontalCenter: email.right
                anchors.top: email.bottom
                anchors.topMargin: 30
                background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 25
                            radius: 4
                            color: "#003961"
                }


                onClicked: loadWindowPassword();

            }


    }


    // Show Window Passwrod if name exist
    function loadWindowPassword()
    {

        if(email.text == "")
        {
            emailError.text = "CAMPO VAZIO";
            emailError.color =  "red";

        }
       else{
            var doc = new XMLHttpRequest();

            doc.onreadystatechange = function() {
                if (doc.readyState == XMLHttpRequest.DONE) {

                   // console.log(doc.responseText);
                    var JsonObject = JSON.parse(doc.responseText);
                  //  console.log(JsonObject["status"]);

                    if(JsonObject["data"] == "")
                    {
                        emailError.text = "NOME INVÁLIDO";
                        emailError.color =  "red";
                        return;
                    }


                    settings.setValue("userName", email.text);
                  //  console.log("User " +settings.value("userName"));

                    windowMain.close();
                    windowMainLoader.source = "password.qml"



                }

            }

            doc.open("POST", "api.php");
            doc.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
            var params = "api=xxxxxxx&login=" + email.text;
            doc.send(params);
        }
    }


}


