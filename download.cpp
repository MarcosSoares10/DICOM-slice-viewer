#include "download.h"

Download::Download(QObject *parent) : QObject(parent)
{


}


QList<QObject*> Download::listar_downloads(){

    download_lista.append(new DownloadList("TESTE","Tomografia","false","https"));
    download_lista.append(new DownloadList("TESTE2","Tomografia","false","https2"));

  return download_lista;

}

void Download::recebe_api(){
   /*     QNetworkRequest req = QNetworkRequest(QUrl("https://www.docdo.com.br/v3/process/api.php"));
        req.setHeader(req.ContentTypeHeader,"application/x-www-form-urlencoded");
        QString postString = "api=listexams&sort=dateup&pageid=0&token=302e38303432323330302031353038383932333739";
         manager = new QNetworkAccessManager(this);
         reply = manager->post(req,postString.toUtf8());

            QEventLoop loop;
            QMetaObject::Connection con = loop.connect(manager, SIGNAL(finished(QNetworkReply*)),SLOT(quit()));
            loop.exec();
            loop.disconnect(con);
            QString responsedata = QString(reply->readAll());
                qDebug() << "read" << responsedata;*/

}
