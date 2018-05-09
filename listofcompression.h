#ifndef LISTOFCOMPRESSION_H
#define LISTOFCOMPRESSION_H

#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTimer>
#include "dicomdb.h"



namespace Ui {
class ListofCompression;
}

class ListofCompression : public QDialog
{
    Q_OBJECT

public:
    explicit ListofCompression(QWidget *parent = 0);
    ~ListofCompression();
    void init();


public slots:
void timeout();

private:
    Ui::ListofCompression *ui;

    QTimer  *timer;
       int   counter;
};

#endif // LISTOFCOMPRESSION_H
