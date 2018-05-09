#include "dicomdb.h"

// Global static pointer used to ensure a single instance of the class.
DicomDB* DicomDB::_instance = nullptr;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/


DicomDB* DicomDB::instance()
{
    if (!_instance)   // Only allow one instance of class to be generated.
        _instance = new DicomDB;
    return _instance;
}

void DicomDB::navigate(QDir dir)
{
    QDirIterator it(dir.absolutePath(), QStringList() << "*", QDir::Files, QDirIterator::Subdirectories);

    QMimeDatabase mimedb;
    QStringList mimeTypeFilters;

    mimeTypeFilters << "image/jpeg" << "image/pjpeg" << "image/png" << "image/gif"
                    << "image/x-portable-bitmap" << "image/x-portable-graymap"
                    << "application/dicom";



    while (it.hasNext())
    {

        QString namepath = it.next();
        QString namefile = it.fileName();
        QMimeType mime = mimedb.mimeTypeForFile(namepath);
        // check if it is supported
        if(!mimeTypeFilters.contains(mime.name()))
        {
             qDebug()<<mime.name() << namepath;
            continue;
        }

        if(mime.inherits("application/dicom"))
        {


            if(!dicoms.contains(namepath))
                dicoms.push_back(namepath);


            if(!diconsname.contains(namefile))
                diconsname.push_back(namefile);

        }
        else
        {
            //  qDebug()<<"Image: " << mime.name() << path;

            if(!pictures.contains(namepath))
                pictures.push_back(namepath);
        }

    }
 //   qDebug()<<dicoms.size();
    diconsname.sort(Qt::CaseInsensitive);
    dicoms.sort(Qt::CaseInsensitive);
    pictures.sort(Qt::CaseInsensitive);


}




