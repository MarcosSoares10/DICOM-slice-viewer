#include "viewdicom2d.h"
#include "ui_viewdicom2d.h"


ViewDicom2d::ViewDicom2d(QString dir_view, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewDicom2d)
{
    ui->setupUi(this);
    this->setStyleSheet("Background-image:url(:/images/Background.png);");
    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"DicomViewer","DicomViewer");
    const QString DEFAULT_DIR_KEY("default_dir");
    OpenDialog();


}

void ViewDicom2d::OpenDialog(){

       const QString DEFAULT_DIR_KEY("default_dir");
       QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"InfiniBrains","InfiniEditor");

       QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                       settings.value(DEFAULT_DIR_KEY).toString(),
                                                       QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);
       if(!dir.isEmpty())
       {
           settings.setValue(DEFAULT_DIR_KEY,dir);
           qDebug()<< dir;
           DicomDB::instance()->navigate(dir);

       }
       else
       {
           return;
       }


LoadImages(DicomDB::instance()->dicoms);

}

ViewDicom2d::~ViewDicom2d()
{
    delete ui;
}


void ViewDicom2d::mousePressEvent(QMouseEvent *event){
lastPos = event->pos();
}

void ViewDicom2d::mouseMoveEvent(QMouseEvent *event){
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    if (event->buttons() & Qt::LeftButton) {
        setWindowcenter(dy);
        setWindowwidth(dx);
                }
    lastPos = event->pos();
}

void ViewDicom2d::setWindowcenter(int tam){
    if(tam!=windowcenter){
        windowcenter+=(tam);
        emit WindowcenterChanged((tam));
        updatewindowvalues();
//        qDebug()<<"centro"<<windowcenter;
    }
}
void ViewDicom2d::setWindowwidth(int tam){
    if(tam!=windowwidth){
        windowwidth+=(tam);
        emit WindowwidthChanged((tam));
        updatewindowvalues();
//        qDebug()<<"largura"<<windowwidth;
    }
}

void ViewDicom2d::updatewindowvalues(){
    imagensarray.clear();
    QListIterator<QString> itr(DicomDB::instance()->dicoms);
    while(itr.hasNext()){
        std::vector<char> vbuffer;
        gdcm::ImageReader reader;
        imageQt = NULL;
        QString namepath = "";
        namepath = itr.next();

        reader.SetFileName(namepath.toUtf8().constData());
        if(!reader.Read())
            continue;

        const  gdcm::Image &image = reader.GetImage();
        vbuffer.resize( image.GetBufferLength() );
        char *buffer = &vbuffer[0];
        if( !UpdateWindow_Center_Width(image, buffer, imageQt ) )
        {
        }
        else
        {
            imagensarray.push_back(*imageQt);
        }
    }

    ui->image->setPixmap(QPixmap::fromImage(imagensarray.at(0)));
    ui->image->setFixedHeight(512);
    ui->image->setFixedWidth(512);



}

bool ViewDicom2d::UpdateWindow_Center_Width(const gdcm::Image &gimage, char *buffer, QImage *&imageQt)
{
    //           if      (x  <= c - 0.5 - (w-1)/2), then y = ymin
    //        >           else if (x > c - 0.5 + (w-1)/2), then y = ymax,
    //        >           else    y = ((x - (c - 0.5)) / (w-1) + 0.5) * (ymax - ymin)+ ymin

    const unsigned int* dimension = gimage.GetDimensions();
    unsigned int dimX = dimension[0];
    unsigned int dimY = dimension[1];
    gimage.GetBuffer(buffer);
    // Let's start with the easy case:
    if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB )
    {
        if( gimage.GetPixelFormat() != gdcm::PixelFormat::UINT8 )
        {
            return false;
        }
        unsigned char *ubuffer = (unsigned char*)buffer;
        // QImage::Format_RGB888  13  The image is stored using a 24-bit RGB format (8-8-8).
        imageQt = new QImage((unsigned char *)ubuffer, dimX, dimY, 3*dimX, QImage::Format_RGB888);
    }
    else if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 )
    {
        if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT8 )
        {
            // We need to copy each individual 8bits into R / G and B:
            unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
            unsigned char *pubuffer = ubuffer;

            for(unsigned int i = 0; i < dimX*dimY; i++)
            {
                *pubuffer++ = *buffer;
                *pubuffer++ = *buffer;
                *pubuffer++ = *buffer++;
            }

            imageQt = new QImage(ubuffer, dimX, dimY, QImage::Format_RGB888);
        }
        else if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT16 || gimage.GetPixelFormat() == gdcm::PixelFormat::INT16)
            {
                buffer16 = (short*)buffer;
                ubuffer = new unsigned char[dimX*dimY*3];
                pubuffer = ubuffer;
                for(unsigned int i = 0; i < dimX*dimY; i++)
                {
                    for(int x = 0; x < 3; x++)
                    {
                        if(*buffer16<=(windowcenter - 0.5 - (windowwidth-1)/2))
                        {
                           *pubuffer++ = 0 ;
                         }
                        else if(*buffer16 > (windowcenter - 0.5 + (windowwidth-1)/2))
                        {
                             *pubuffer++ =255 ;
                         }
                        else
                        {
                            *pubuffer++ = ((*buffer16 -(windowcenter-0.5))/(windowwidth-1)+0.5)*(255-0)+0;
                         }

                    }
                    buffer16++;
                }
                imageQt = new QImage(ubuffer, dimX, dimY, QImage::Format_RGB888);
        }

        else
        {
            std::cerr << "Pixel Format is: " << gimage.GetPixelFormat() << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
        return false;
    }

    return true;
}


bool ViewDicom2d::ConvertToFormat_RGB888(const gdcm::Image &gimage, char *buffer, QImage *&imageQt)
{
    //           if      (x  <= c - 0.5 - (w-1)/2), then y = ymin
    //        >           else if (x > c - 0.5 + (w-1)/2), then y = ymax,
    //        >           else    y = ((x - (c - 0.5)) / (w-1) + 0.5) * (ymax - ymin)+ ymin

    const unsigned int* dimension = gimage.GetDimensions();
    unsigned int dimX = dimension[0];
    unsigned int dimY = dimension[1];
    gimage.GetBuffer(buffer);
    // Let's start with the easy case:
    if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB )
    {
        if( gimage.GetPixelFormat() != gdcm::PixelFormat::UINT8 )
        {
            return false;
        }
        unsigned char *ubuffer = (unsigned char*)buffer;
        // QImage::Format_RGB888  13  The image is stored using a 24-bit RGB format (8-8-8).
        imageQt = new QImage((unsigned char *)ubuffer, dimX, dimY, 3*dimX, QImage::Format_RGB888);
    }
    else if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 )
    {
        if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT8 )
        {
            // We need to copy each individual 8bits into R / G and B:
            unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
            unsigned char *pubuffer = ubuffer;

            for(unsigned int i = 0; i < dimX*dimY; i++)
            {
                *pubuffer++ = *buffer;
                *pubuffer++ = *buffer;
                *pubuffer++ = *buffer++;
            }

            imageQt = new QImage(ubuffer, dimX, dimY, QImage::Format_RGB888);
        }
        else if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT16 || gimage.GetPixelFormat() == gdcm::PixelFormat::INT16)
            {
                short *buffer16 = (short*)buffer;
                unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
                unsigned char *pubuffer = ubuffer;
                for(unsigned int i = 0; i < dimX*dimY; i++)
                {
                    for(int x = 0; x < 3; x++)
                    {
                        if(*buffer16<=(windowcenter - 0.5 - (windowwidth-1)/2))
                        {
                           *pubuffer++ = 0 ;
                         }
                        else if(*buffer16 > (windowcenter - 0.5 + (windowwidth-1)/2))
                        {
                             *pubuffer++ =255 ;
                         }
                        else
                        {
                            *pubuffer++ = ((*buffer16 -(windowcenter-0.5))/(windowwidth-1)+0.5)*(255-0)+0;
                         }

                    }
                    buffer16++;
                }
                imageQt = new QImage(ubuffer, dimX, dimY, QImage::Format_RGB888);
        }

        else
        {
            std::cerr << "Pixel Format is: " << gimage.GetPixelFormat() << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
        return false;
    }

    return true;
}

void ViewDicom2d::changeValueP(int value)
{
        ui->image->setPixmap(QPixmap::fromImage(imagensarray.at(value)));
        ui->image->setScaledContents(true);
        ui->image->setFixedHeight(512);
        ui->image->setFixedWidth(512);
        ui->image->show();
}

void ViewDicom2d::LoadImages(QStringList dicoms)
{
    gdcm::Tag dicomwindowcenterTag   (0x0028,0x1050);
    gdcm::Tag dicomwindowwidthTag    (0x0028,0x1051);
    gdcm::Tag dicomimageposition (0x0020,0x0032);

    QListIterator<QString> itr(dicoms);


    while(itr.hasNext())
    {


        std::vector<char> vbuffer;
        gdcm::ImageReader reader;
        QImage *imageQt = NULL;
        QString namepath = "";



        namepath = itr.next();

        //qDebug()<<namepath.toUtf8().constData();

        reader.SetFileName(namepath.toUtf8().constData());
        if(!reader.Read())
        {
            continue;
        }

        gdcm::File &file = reader.GetFile();
        gdcm::DataSet &ds = file.GetDataSet();
        gdcm::StringFilter sf;

        sf.SetFile(file);

        // Window Center
        if(ds.FindDataElement(dicomwindowcenterTag))
        {
              windowcenter = std::stoi(sf.ToString(dicomwindowcenterTag));
        }
        else
        {
              windowcenter = 0;
        }

        // Window Width
        if(ds.FindDataElement(dicomwindowwidthTag))
        {
             windowwidth = std::stoi(sf.ToString(dicomwindowwidthTag));
        }
        else
        {
             windowwidth = 0;
        }

        const gdcm::Image &image = reader.GetImage();
        vbuffer.resize( image.GetBufferLength() );
        char *buffer = &vbuffer[0];
        if( !ConvertToFormat_RGB888(image, buffer, imageQt ))
          {
            continue;
          }
        imagensarray.push_back(*imageQt);
        }

        ui->horizontalSlider->setRange(0,imagensarray.size()-1);
        ui->horizontalSlider->setOrientation(Qt::Horizontal);
        ui->horizontalSlider->setMinimumHeight(100);
        ui->horizontalSlider->setMinimumWidth(100);
        ui->horizontalSlider->setStyleSheet(
                            "QSlider::groove:horizontal {"
                            "border: 0px none;"
                            "background: white;"
                            "height: 30px;"
                            "width: 500px;"
                            "border-radius: 5px;"
                            "}"

                            "QSlider::handle:horizontal {"
                            "background: #D8D8D8;"
                            "border: 0px none;"
                            "width: 50px;"
                            "border-radius: 5px;"
                            "margin: 0px 0;"
                            "}"

                            "QSlider::add-page:horizontal {"
                            "background: #A2C511;"
                            "border-radius: 5px;"
                            "}"

                            "QSlider::sub-page:horizontal {"
                            "background: #DD4814;"
                            "border-radius: 5px;"
                            "}"

                            );

        connect(ui->horizontalSlider,  SIGNAL(valueChanged(int)), this, SLOT(changeValueP(int)));
        ui->image->setPixmap(QPixmap::fromImage(imagensarray.at(0)));
        ui->image->setFixedHeight(512);
        ui->image->setFixedWidth(512);

        this->show();







}
