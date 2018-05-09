#ifndef DICOMDB_H
#define DICOMDB_H

#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QImageReader>
#include <QMimeDatabase>
#include <QDebug>

#include "gdcmImageReader.h"
#include "gdcmImage.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmImageWriter.h"
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmStringFilter.h"

#include <string>
#include <vector>
#include <map>
class DicomDB
{
public:
   static DicomDB* instance();
    void navigate(QDir dir);
    QStringList dicoms,pictures,diconsname;

private:
    DicomDB(){}
    DicomDB(DicomDB const&){}             // copy constructor is private
    DicomDB& operator=(DicomDB const&){}  // assignment operator is private
    static DicomDB* _instance;
};

#endif // DICOMDB_H
