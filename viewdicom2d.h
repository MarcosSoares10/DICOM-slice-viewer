#ifndef VIEWDICOM2D_H
#define VIEWDICOM2D_H

#include <QMainWindow>

#include <QSlider>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QImageReader>
#include <QMimeDatabase>
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QImage>


#include <string>
#include <vector>
#include <map>

#include "gdcmImageReader.h"
#include "gdcmImage.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageWriter.h"
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmStringFilter.h"
#include "dicomdb.h"

namespace Ui {
class ViewDicom2d;
}

class ViewDicom2d : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewDicom2d(QString dir_view, QWidget *parent = nullptr);
    ~ViewDicom2d();
    void LoadImages(QStringList dicoms);
    void OpenDialog();
    bool ConvertToFormat_RGB888(gdcm::Image const &gimage,char *buffer,QImage* &imageQt);
    bool UpdateWindow_Center_Width(const gdcm::Image &gimage, char *buffer, QImage *&imageQt);
    void updatewindowvalues();
    QPoint lastPos;
    QImage *imageQt = NULL;
    short *buffer16;
    unsigned char *ubuffer;
    unsigned char *pubuffer;


    QVector<QImage> imagensarray;
    int64_t minValue;
    int64_t maxValue;
    int64_t windowcenter;
    int64_t windowwidth;

public slots:
    void setWindowcenter(int tam);
    void setWindowwidth(int tam);
    void changeValueP(int value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

    void WindowcenterChanged(int aux);
    void WindowwidthChanged(int aux);

private:
    Ui::ViewDicom2d *ui;
};

#endif // VIEWDICOM2D_H
