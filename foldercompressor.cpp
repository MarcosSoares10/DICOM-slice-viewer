#include "foldercompressor.h"
#include "settings.h"





FolderCompressor::FolderCompressor(QObject *parent) :
    QObject(parent)
{


}

QFileInfoList filesList;
QDir dir,dir_download;
QDataStream dataStream;





// FOLDER COMPRESS
bool FolderCompressor::compressFolder(QString sourceFolder, QString destinationFile)
{
    QDir src(sourceFolder);
    if(!src.exists())//folder not found
    {
        return false;
    }

    QFile file;
    file.setFileName(destinationFile);
    if(!file.open(QIODevice::WriteOnly))//could not open file
    {
        return false;
    }

    dataStream.setDevice(&file);

    bool success = compressT();
    file.close();

    return success;
}

void spin()
{
    Settings reference;
    QDir up = dir;
    up.cdUp();

    QStringList files;
    for(auto file :filesList )
        files.append(file.absoluteFilePath());

    JlCompress::compressFiles(up.absolutePath() + "/compressed.zip",files);

    reference.setValueFolderCompressFilePath("filePathFolderCompress",up.absolutePath() + "/compressed");


}



bool FolderCompressor::compressT()
{


    const QString DEFAULT_DIR_KEY("default dir");
        QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"InfiniBrains","InfiniEditor");
        dir = QFileDialog::getExistingDirectory(new QWidget,tr("Open Directory"),
                                                        settings.value(DEFAULT_DIR_KEY).toString(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.exists())
        return false;


     filesList.clear();
     ListofCompression list;
     list.show();
     DicomDB::instance()->navigate(dir);

     list.init();
      DIRECTORY =  DicomDB::instance()->dicoms;


      for(int i=0; i<DIRECTORY.size();i++){
          filesList.append(DIRECTORY.at(i));
      }


   //Create a QFutureWatcher and connect signals and slots.
   QFutureWatcher<void> futureWatcher;


    QObject::connect(&futureWatcher, SIGNAL(finished()), &list, SLOT(close()));
   // QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
   // QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), &dialog, SLOT(setRange(int,int)));
   // QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), list, SLOT( progressChanged(int)));

    //Start the computation.
    QFuture<void> future = QtConcurrent::run(spin);

    futureWatcher.setFuture(future);

    //Display the dialog and start the event loop.

    list.exec();

   // dialog.exec();
   //  list->show();

    future.waitForFinished();

   // if(futureWatcher.isCanceled())
   // {
       // qDebug() << "canceled!";
        //QMessageBox::critical(this, "Canceled", "You cliked cancel!");
   // }
   // else
   // {
       // qDebug() << "finished!";
        //QMessageBox::critical(this, "finished", "Exam uploaded successfully!");
 //   }



    return true;
}



// funcao que retorna o hash de um array de bytes de um arquivo
QString FolderCompressor::hash(QByteArray dataToBeHashed)
{
    QCryptographicHash h(QCryptographicHash::Sha1);
    h.addData(dataToBeHashed);
    return h.result().toHex();
}

// ProgressBar Upload Exam
void FolderCompressor::progressChanged(qint64 a, qint64 b)
{


    if (b > 0)
    {
        qDebug() << "Uploading " << a  << "/" << b << "%" << (double)a/(double)b*100.0;
        //ui->progressBarUpload->setValue((a*100/b));
       // qApp->processEvents();

        // ui->txtLoadingUploadExam->setText(QString::number((double)a/(double)b*100.0,'f',2) +"%");
    }


}

// ProgressBar Upload File Path
void FolderCompressor::progressChangedFilePath(qint64 a, qint64 b)
{
    if (b > 0)
    {
        qDebug() << "Uploading " << a  << "/" << b << "%" << (double)a/(double)b*100.0;
        //ui->progressBarFilePath->setValue((a*100/b));
      //  qApp->processEvents();

         //ui->txtLoadingUploadExam->setText(QString::number((double)a/(double)b*100.0,'f',2) +"%");
    }

}
void FolderCompressor::httpSigns3(QNetworkReply *aux){
    QString responsedata = QString(aux->readAll());
    qDebug() << "read s3" << responsedata;

    QString responseSignS3 = responsedata;
    if(responseSignS3.isEmpty()){
       //ui->status->setText("no response from server");
       return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(responseSignS3.toUtf8());
    if(!doc.isObject()){
       // ui->status->setText("received invalid response from server");
        return;
    }
    QJsonObject json = doc.object();
    QString error = json["error"].toString();
    if(!error.isEmpty()&&!error.isNull()){
       //ui->status->setText(error);
       return;
    }
    QJsonObject data = json["data"].toObject();
    if(data.isEmpty()){
      //ui->status->setText("data response from server is empty");
      return;
    }

    presignedUrl = data["signed_request"].toString();
    fileId = data["file_id"].toString();




    UploadtoS3();
     emit signreplyreceived();

}
void FolderCompressor::httpS3upload(QNetworkReply *aux){
  // connect(aux, SIGNAL(uploadProgress(qint64, qint64)),this, SLOT(progressChanged(qint64,qint64)));
   // aux->deleteLater();
   ValidateFile();
    emit S3uploaded();

}
void FolderCompressor::httpS3Validate(QNetworkReply *aux){

    QString responsedata = QString(aux->readAll());
    qDebug() << "Validate file " << responsedata;

     Uploadcomplete();
    emit S3validate();

}
void FolderCompressor::UploadtoS3(){
Progress *p = new Progress;
p->show();

   QNetworkRequest request(presignedUrl);
   request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/zip"));
 QNetworkReply *reply=manageruploadfile->put(request,blob);

    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),p,SLOT(progressChanged(qint64,qint64)));

         QEventLoop loop;
         QMetaObject::Connection con = loop.connect(manageruploadfile, SIGNAL(finished(QNetworkReply*)),this,SLOT(httpS3upload(QNetworkReply*)));
         loop.exec();
         loop.disconnect(con);


}
void FolderCompressor::ValidateFile(){
    Settings reference;
    QNetworkRequest req2 = QNetworkRequest(QUrl("https:api.php"));
    req2.setHeader(req2.ContentTypeHeader,"application/x-www-form-urlencoded");
    QString postString2 = "api=xxxxxxxxx&type=exams&file_id="+fileId;


    managervalidadefile->post(req2,postString2.toUtf8());

 QEventLoop loop;
 QMetaObject::Connection con = loop.connect(managervalidadefile, SIGNAL(finished(QNetworkReply*)),this,SLOT(httpS3Validate(QNetworkReply *)));
 loop.exec();
 loop.disconnect(con);


}
void FolderCompressor::on_selecionarpasta_clicked()
{
    Settings reference;

    QString filepath = reference.valueFolderCompressFilePath("filePathFolderCompress").toString()+".zip";
   // qDebug()<< filepath;
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    blob = file.readAll();
    h = hash(blob);
    file.close();

    QNetworkRequest req = QNetworkRequest(QUrl("https://api.php"));
    req.setHeader(req.ContentTypeHeader,"application/x-www-form-urlencoded");
    QString pa = reference.valueFolderCompressFilePath("filePathFolderCompress").toString();
   // qDebug()<<reference.valueToken("Token").toString();

    QString postString = "api=xxxxxxxxxxx&file_name="+pa;
    //replySignS3 = manager->post(req,postString.toUtf8());

   // QNetworkReply *replySignS3 =
    managersigns3->post(req,postString.toUtf8());

    QEventLoop loop;
    QMetaObject::Connection con = loop.connect(managersigns3,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpSigns3(QNetworkReply*)));
    loop.exec();
    loop.disconnect(con);




}
void FolderCompressor::Uploadcomplete(){
      Settings reference;
    QNetworkRequest req = QNetworkRequest(QUrl("https://api.php"));
    req.setHeader(req.ContentTypeHeader,"application/x-www-form-urlencoded");
  //  QString pa = reference.valueFolderCompressFilePath("filePathFolderCompress").toString();

    QString postString = "api=xxxxxxxxxxxxxxx&exame_id="+reference.valueExamID("examId").toString();
   // QNetworkReply *replyUploadcomplete =
    manageruploadcomplete->post(req,postString.toUtf8());

    QEventLoop loop;
    QMetaObject::Connection con = loop.connect(manageruploadcomplete, SIGNAL(finished(QNetworkReply*)),this,SLOT(httpUploadcomplete(QNetworkReply *)));
    loop.exec();
    loop.disconnect(con);


}
void FolderCompressor::httpUploadcomplete(QNetworkReply *aux){
    QString responsedata = QString(aux->readAll());
     qDebug() << "Upload Complete file " << responsedata;
  //   progress->close();
   emit Examvalidate();
}

