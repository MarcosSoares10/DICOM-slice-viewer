#include "pacswindow.h"
#include "ui_pacswindow.h"


#include <iostream>
#include <stdio.h>
#include <QThread>


PacsWindow::PacsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PacsWindow)
{
    ui->setupUi(this);

    connect(managerdownload, SIGNAL(finished(QNetworkReply*)),this, SLOT(httpDownload(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(httpUpload(QNetworkReply*)));
    connect(managerpatient, SIGNAL(finished(QNetworkReply*)),this, SLOT(UpdateLoadPatients(QNetworkReply*)));
    connect(managerInit, SIGNAL(finished(QNetworkReply*)),this, SLOT(receivePatientsList(QNetworkReply*)));
    connect(managerstudies, SIGNAL(finished(QNetworkReply*)),this, SLOT(receiveStudiesList(QNetworkReply*)));
    connect(managerpreview, SIGNAL(finished(QNetworkReply*)), this, SLOT(receivePreview(QNetworkReply*)));



    initTables();


}

PacsWindow::~PacsWindow()
{
    delete ui;
}

void PacsWindow::initTables(){
    QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/patients/"));
    request.setRawHeader("Content-Type","application/dicom");
    QString concatenated ="orthanc:orthanc";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("authorization", headerData.toLocal8Bit());
    managerInit->get(request);

}

void PacsWindow::receivePatientsList(QNetworkReply *aux){
    QString responsedata = QString(aux->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(responsedata.toUtf8());
   // qDebug()<< responsedata;

    // QJsonObject json = doc.object();
     QJsonArray studies = doc.array();
    // QJsonObject tags= json["MainDicomTags"].toObject();


    for(int i=0; i<studies.size();i++){
   // qDebug()<<"Exam "<<studies.at(0).toString();
        UpdateListPatients(studies.at(i).toString());
       }

     aux->deleteLater();
      emit initloaded();

}

void PacsWindow::UpdateListStudies(QString link)
{
    QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/studies/"+link+"/"));
    request.setRawHeader("Content-Type","application/dicom");
    QString concatenated ="orthanc:orthanc";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("authorization", headerData.toLocal8Bit());
    managerstudies->get(request);
}

void PacsWindow::receiveStudiesList(QNetworkReply *aux){
    QString responsedata = QString(aux->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(responsedata.toUtf8());
     QJsonObject json = doc.object();

    QJsonArray series = json["Series"].toArray();
    tagsdescription= json["PatientMainDicomTags"].toObject();
   // qDebug()<<json["MainDicomTags"].toObject();
     QStandardItemModel *model= new QStandardItemModel();
     QStandardItem *item;
     int j=0;


     for(int i=0; i<series.size();i++){
         item = new QStandardItem(series.at(i).toString());
         model->setItem(j,item);
         j++;
     }
    ui->seriesListView->setModel(model);
   aux->deleteLater();
  emit studiesloaded();
}

void PacsWindow::UpdateListPatients(QString link)
{
QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/patients/"+link+"/"));
request.setRawHeader("Content-Type","application/dicom");
QString concatenated ="orthanc:orthanc";
QByteArray data = concatenated.toLocal8Bit().toBase64();
QString headerData = "Basic " + data;
request.setRawHeader("authorization", headerData.toLocal8Bit());
managerpatient->get(request);
}

void PacsWindow::UpdateLoadPatients(QNetworkReply *aux){
    QString responsedata = QString(aux->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(responsedata.toUtf8());
     QJsonObject json = doc.object();
     QJsonArray studies = json["Studies"].toArray();
     QJsonObject tags= json["MainDicomTags"].toObject();
     QVector<QString> vectoraux;
    vectoraux.append(json["ID"].toString());
    vectoraux.append(tags["PatientName"].toString());


    for(int i=0; i<studies.size();i++){
   // qDebug()<<"Studies "<<studies.at(i).toString();
    vectoraux.append(studies.at(i).toString());
       }

    tablepatientsInfo.append(vectoraux);
     aux->deleteLater();
    emit patientloaded();
    vectoraux.clear();

    //QVector<Qstring> tablepatientsInfo;
    //[0] -> ID exam
    //[1] -> Patient name
    //next index --> Studies

    QStandardItemModel *model= new QStandardItemModel();
    QStandardItem *item;

                       for(int j=0; j<tablepatientsInfo.size();j++){
                              QVector<QString>interno = tablepatientsInfo.at(j);
                                  for(int i =0;i<interno.size();i++){
                                  item = new QStandardItem(interno.at(1));
                                  model->setItem(j,item);}
                                  }


        ui->nameListView->setModel(model);

}

void PacsWindow::on_nameListView_clicked(const QModelIndex &index)
{
    indexTable1 = index.row();
    QStandardItemModel *model= new QStandardItemModel();
    QStandardItem *item;
    QVector<QString> aux = tablepatientsInfo.at(index.row());
   int j=0;
    for(int i=2;i<aux.size();i++){
        item = new QStandardItem(aux.at(i));
        model->setItem(j,item);
        j++;
   }

   ui->studiesListView->setModel(model);

}
void PacsWindow::on_seriesListView_clicked(const QModelIndex &index)
{

  QString a ="Patient ID: " + tagsdescription["PatientID"].toString()+"\n";
  QString b ="Patient Name: " +  tagsdescription["PatientName"].toString()+"\n";
  QString c ="Patient Birth Date ID: " +  tagsdescription["PatientBirthDate"].toString()+"\n";
  QString d ="Patient Sex: " +  tagsdescription["PatientSex"].toString()+"\n";
  QString e ="Patient Age: " +  tagsdescription["PatientAge"].toString()+"\n";


ui->textEdit->setText(a+b+c+d+e);

}
void PacsWindow::on_studiesListView_clicked(const QModelIndex &index)
{
    UpdateListStudies(tablepatientsInfo.at(indexTable1).at(index.row()+2));
}

void PacsWindow::httpUpload(QNetworkReply *aux){
    QByteArray resposta = aux->readAll();
   // qDebug()<< "Orthanc " << resposta;
     aux->deleteLater();
    emit uploaded();
   }


void PacsWindow::download_orthanc_docker(){

    QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/patients/"+tablepatientsInfo.at(indexTable1).at(0)+"/archive"));
    request.setRawHeader("Content-Type","application/dicom");
    QString concatenated ="orthanc:orthanc";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("authorization", headerData.toLocal8Bit());
    managerdownload->get(request);
}

void PacsWindow::httpDownload(QNetworkReply* aux){
   const QByteArray file_downloaded = aux->readAll();
    QFile file("C:/Users/Marquinhos/Documents/TESTANDO/download.zip");
        if(!file.open(QIODevice::WriteOnly))//could not open file
        {
          //  return false;
        }

        file.write(file_downloaded);
        file.close();

    aux->deleteLater();
    emit downloaded();
}

void PacsWindow::receivePreview(QNetworkReply* aux){
   const QByteArray file_downloaded = aux->readAll();
    QFile file("C:/Documents/TESTANDO/preview.zip");
    QDir dir("C:/Documents/TESTANDO/Preview");

    if(file.exists()){
        file.remove();
    }

    if(dir.exists()){
        dir.removeRecursively();
    }


    if(!file.open(QIODevice::WriteOnly))//could not open file
        {
          //  return false;
        }else{

        file.write(file_downloaded);
        file.close();

    aux->deleteLater();
    emit downloaded();

    JlCompress::extractDir("C:/Documents/TESTANDO/preview.zip","C:/Documents/TESTANDO/Preview");

    ViewDicom2d *viewslices = new ViewDicom2d("C:/Documents/TESTANDO/Preview");
                viewslices->show();
       }

}

void PacsWindow::preview_slices(){

    QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/patients/"+tablepatientsInfo.at(indexTable1).at(0)+"/archive"));
    request.setRawHeader("Content-Type","application/dicom");
    QString concatenated ="orthanc:orthanc";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("authorization", headerData.toLocal8Bit());
    managerpreview->get(request);

}
void PacsWindow::on_selectFolder_clicked()
{
   QNetworkRequest request= QNetworkRequest(QUrl("http://192.168.99.100:8042/instances"));
    request.setRawHeader("Content-Type","application/dicom");
    QString concatenated ="orthanc:orthanc";
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("authorization", headerData.toLocal8Bit());

    const QString DEFAULT_DIR_KEY("default dir");
        QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"InfiniBrains","InfiniEditor");
        dir_upload = QFileDialog::getExistingDirectory(new QWidget,tr("Open Directory"),
                                                        settings.value(DEFAULT_DIR_KEY).toString(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


       // ProgressAnimation *progress = new ProgressAnimation("Uploading");
       // progress->show();
       if(!dir_upload.exists())
        return;

    if(!dir_upload.isEmpty())
    {


        QMimeDatabase mimedb;
        QStringList mimeTypeFilters;

        mimeTypeFilters << "image/jpeg" << "image/pjpeg" << "image/png" << "image/gif"
                        << "image/x-portable-bitmap" << "image/x-portable-graymap"
                        << "application/dicom";


        // while there is new file, fill file list

        // file directory iterator
        QDirIterator it(dir_upload.absolutePath(), QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);
         while (it.hasNext())
        {


            QString path = it.next();

            // check mime type
            QMimeType mime = mimedb.mimeTypeForFile(path);

            // check if it is supported
            if(!mimeTypeFilters.contains(mime.name()))
            {
             //   qDebug()<<mime.name() << path;
                continue;
            }


            QFile file(path);
            if (!file.open(QIODevice::ReadOnly))
                return;

            QByteArray blob = file.readAll();
            manager->post(request,blob);

         }

    }




}


void PacsWindow::on_pushButton_4_clicked()
{
    initTables();
}





void PacsWindow::on_pushButton_clicked()
{
    download_orthanc_docker();
}

void PacsWindow::on_pushButton_3_clicked()
{
    preview_slices();
}
