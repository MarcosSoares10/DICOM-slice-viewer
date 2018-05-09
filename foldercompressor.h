#ifndef FOLDERCOMPRESSOR_H
#define FOLDERCOMPRESSOR_H


#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <QCryptographicHash>
#include <QEventLoop>
#include <QtCore>
#include <QMessageBox>
#include <QDialog>
#include <QProgressDialog>
#include <QThread>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QtWidgets>
#include <QDirIterator>
#include <QFile>
#include <QObject>
#include <QDir>
#include <QDataStream>



#include "quazip/JlCompress.h"
#include "progress.h"
#include "dicomdb.h"
#include "listofcompression.h"




class FolderCompressor : public QObject
{
    Q_OBJECT




public:

    explicit FolderCompressor(QObject *parent=0);


    Q_INVOKABLE bool compressFolder(QString sourceFolder, QString destinationFile);
    Q_INVOKABLE bool compressT();

    Q_INVOKABLE QString hash(QByteArray dataToBeHashed);
    Q_INVOKABLE QString presignedUrl;
    QString returnList;

    Q_INVOKABLE QString fileId;



    Q_INVOKABLE void on_selecionarpasta_clicked();



    void UploadtoS3();
    void ValidateFile();
    void Uploadcomplete();
    QByteArray blob;
    QString h;
    QStringList DIRECTORY,FILENAMES;

public slots:
    void httpSigns3(QNetworkReply *aux);
    void httpS3upload(QNetworkReply *aux);
    void httpS3Validate(QNetworkReply *aux);
    void httpUploadcomplete(QNetworkReply *aux);

private slots:

    void progressChanged(qint64, qint64);
    void progressChangedFilePath(qint64,qint64);


signals:
     void signreplyreceived();
     void S3uploaded();
     void S3validate();
     void Examvalidate();

private:

     QNetworkAccessManager *managersigns3 = new QNetworkAccessManager(this);
     QNetworkAccessManager *manageruploadfile = new QNetworkAccessManager(this);
     QNetworkAccessManager *managervalidadefile = new QNetworkAccessManager(this);
     QNetworkAccessManager *managerdownloadfile = new QNetworkAccessManager(this);
     QNetworkAccessManager *manageruploadcomplete= new QNetworkAccessManager(this);


};

#endif // FOLDERCOMPRESSOR_H
