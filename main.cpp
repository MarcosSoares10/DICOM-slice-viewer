#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSplashScreen>
#include <QTimer>



#include <istream>
#include <QDebug>
#include <QSslSocket>

#include "settings.h"
#include "foldercompressor.h"
#include "download.h"
#include "viewdicom2d.h"
#include "viewdicom3d.h"
#include "pacswindow.h"


#include <QQmlContext>
#include <QSettings>

#include "quazip/JlCompress.h"

#include <QCoreApplication>
#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <QDebug>
#include <QFile>


using namespace std;
using namespace gdcm;
int main(int argc, char *argv[])
{


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   // QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    // Register Settings
    qmlRegisterType<Settings>("infinibrains.doceditor.com", 1, 0, "Settings");


    // Register FolderCompress
    qmlRegisterType<FolderCompressor>("infinibrains.doceditor.compress.com", 1, 0, "FolderCompressor");


     QQmlApplicationEngine engine;






    // Test of Initialization interfaces qml
   // engine.load(QUrl(QLatin1String("qrc:/main.qml")));
   // if (engine.rootObjects().isEmpty())
   //         return -1;


  // QTimer::singleShot(500,splash,SLOT(close()));



  // Register list of case available for download received from the server
  // Download down;
  // QQmlContext *ctxt = engine.rootContext();
  // ctxt->setContextProperty("downloads",QVariant::fromValue(down.listar_downloads()));






  // Test of Initialization mockup view dicom 3d
  // MainWindow dicom3d;
  // dicom3d.show();

   ViewDicom2d *dicom2d = new ViewDicom2d("");
   dicom2d->testviewer();
   dicom2d->show();


  // UploaderWindow up;
  // up.show();

  // PacsWindow pacs;
  // pacs.show();
  // QTimer::singleShot(500,&dicom2d,SLOT(show()));
  // QTimer::singleShot(500,splash,SLOT(close()));
  // QTimer::singleShot(500,&pacs,SLOT(show()));


   return app.exec();
}


