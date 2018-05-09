#ifndef UPLOADERWINDOW_H
#define UPLOADERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDirIterator>
#include <QStringList>
#include <QImage>
#include <QLabel>
#include <QSettings>
#include <QWidgetList>
#include <QStringList>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QTimer>
#include <QVectorIterator>
#include <QStandardItemModel>

#include "dicomdb.h"
#include "gdcmImageReader.h"
#include "gdcmStringFilter.h"
#include "gdcmStrictScanner.h"
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmFileNameEvent.h"
#include "gdcmSorter.h"
#include "gdcmIPPSorter.h"
#include "gdcmScanner.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmTesting.h"
#include "JlCompress.h"
#include "viewdicom2d.h"



namespace Ui {
class PacsWindow;
}

class PacsWindow : public QMainWindow
{
    Q_OBJECT
public slots:

    void httpDownload(QNetworkReply *aux);
    void httpUpload(QNetworkReply *aux);
    void UpdateLoadPatients(QNetworkReply *aux);
    void receivePatientsList(QNetworkReply *aux);
    void receiveStudiesList(QNetworkReply *aux);
    void receivePreview(QNetworkReply *aux);



public:
    explicit PacsWindow(QWidget *parent = 0);
    ~PacsWindow();

    QFileInfoList filelist;
    QDir dir,dir_upload;
    QDataStream dataStream;
    QVector<QVector<QString>> tablepatientsInfo;
    QVector<QVector<QString>> tablesstudiesInfo;
     void upload_orthanc_docker();
     void download_orthanc_docker();
     void preview_slices();
     int indexTable1;
    QJsonObject tagsdescription;



private:
    Ui::PacsWindow *ui;

        void initTables();
        void UpdateListPatients(QString link);
        void UpdateListStudies(QString link);

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkAccessManager *managerdownload = new QNetworkAccessManager(this);
        QNetworkAccessManager *managerpatient = new QNetworkAccessManager(this);
        QNetworkAccessManager *managerInit = new QNetworkAccessManager(this);
        QNetworkAccessManager *managerstudies= new QNetworkAccessManager(this);
        QNetworkAccessManager *managerpreview= new QNetworkAccessManager(this);

signals:
        void downloaded();
        void uploaded();
        void patientloaded();
        void studiesloaded();
        void initloaded();


private slots:
        void on_selectFolder_clicked();
        void on_nameListView_clicked(const QModelIndex &index);
        void on_pushButton_4_clicked();
        void on_studiesListView_clicked(const QModelIndex &index);
        void on_seriesListView_clicked(const QModelIndex &index);
        void on_pushButton_clicked();
        void on_pushButton_3_clicked();
};

#endif // UPLOADERWINDOW_H
