#include "listofcompression.h"
#include "ui_listofcompression.h"

ListofCompression::ListofCompression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListofCompression)
{
    ui->setupUi(this);
    timer = new QTimer();



        counter = 0;

        connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

        timer->start(400);

}

ListofCompression::~ListofCompression()
{
    delete ui;
}

void ListofCompression::init(){

    QStringList FILESDIRECTORY =  DicomDB::instance()->diconsname;

    QStandardItemModel *model= new QStandardItemModel();
    QStandardItem *item;

    int j=0;
     for(int i=0; i<FILESDIRECTORY.size();i++){
         item = new QStandardItem(FILESDIRECTORY.at(i));
         model->setItem(j,item);
         j++;
    }

        ui->nameListView->setModel(model);

}

void ListofCompression::timeout()
{
    if(counter%2)
       ui->statusLabel->setText("Compressing Files");
    else
         ui->statusLabel->setText("");
    counter++;
}




