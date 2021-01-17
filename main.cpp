#include "viewdicom2d.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewDicom2d *dicom2d = new ViewDicom2d("");
    //dicom2d->testviewer();
    dicom2d->show();
    return a.exec();
}
