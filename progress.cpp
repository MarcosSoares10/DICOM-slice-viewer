#include "progress.h"
#include "ui_progress.h"
#include <QDebug>

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);
    ui->statusLabel->setText("Uploading File");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
}

Progress::~Progress()
{
    delete ui;
}



void Progress::progressChanged(qint64 a, qint64 b){


    if (b > 0)
    {
       // qDebug() << "Uploading " << a  << "/" << b << "%" << (double)a/(double)b*100.0;
        ui->progressBar->setValue((int)((double)a/(double)b*100.0));
    }else if(a==b){
         ui->statusLabel->setText("Upload Complete");
        QTimer::singleShot(2000, this, SLOT(close()));
    }


}
