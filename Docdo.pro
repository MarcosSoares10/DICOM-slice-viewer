QT += qml quick
QT += widgets
QT += concurrent
QT += core gui sql network opengl concurrent

CONFIG += c++11





# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += $$PWD/qml.qrc



DEFINES += NOMINMAX
DEFINES += QUAZIP_STATIC
INCLUDEPATH += $$PWD/quazip

INCLUDEPATH += $$PWD/Dependencies/GDCM/bin \
               $$PWD/Dependencies/GDCM/include/gdcm-2.8 \
               $$PWD/Dependencies/GDCM/lib

   LIBS += -lgdcmMSFF -lgdcmCommon \
       -lgdcmDICT -lgdcmDSED \
       -lgdcmexpat -lgdcmIOD \
       -lgdcmjpeg8 -lgdcmjpeg12 \
       -lgdcmjpeg16  \
       -lgdcmzlib -lgdcmcharls -lgdcmexpat -lgdcmgetopt -lopengl32 -lglu32

     LIBS += -L"$$PWD/Dependencies/GDCM/bin" \
             -L"$$PWD/Dependencies/GDCM/include/gdcm-2.8" \
             -L"$$PWD/Dependencies/GDCM/lib"



HEADERS += \
   settings.h \
   $$PWD/quazip/quaziodevice.h \
   $$PWD/quazip/JlCompress.h \
   $$PWD/quazip/zip.h \
   $$PWD/quazip/unzip.h \
   $$PWD/quazip/quazipnewinfo.h \
   $$PWD/quazip/quazipfileinfo.h \
   $$PWD/quazip/quazipfile.h \
   $$PWD/quazip/quazipdir.h \
   $$PWD/quazip/quazip.h \
   $$PWD/quazip/quazip_global.h \
   $$PWD/quazip/quagzipfile.h \
   $$PWD/quazip/quacrc32.h \
   $$PWD/quazip/quachecksum32.h \
   $$PWD/quazip/quaadler32.h \
   $$PWD/quazip/ioapi.h \
   $$PWD/quazip/crypt.h \
   foldercompressor.h\
   viewdicom2d.h \
   download.h \
   downloadlist.h \
   viewdicom3d.h \
    dicomdb.h \
    pacswindow.h \
    progress.h \
    listofcompression.h


SOURCES += main.cpp \
    settings.cpp \
    $$PWD/quazip/qioapi.cpp \
    $$PWD/quazip/quazipnewinfo.cpp \
    $$PWD/quazip/quazipfile.cpp \
    $$PWD/quazip/quaziodevice.cpp \
    $$PWD/quazip/JlCompress.cpp \
    $$PWD/quazip/quazip.cpp \
    $$PWD/quazip/quazipfileinfo.cpp \
    $$PWD/quazip/quazipdir.cpp \
    $$PWD/quazip/quagzipfile.cpp \
    $$PWD/quazip/quacrc32.cpp \
    $$PWD/quazip/quaadler32.cpp \
    $$PWD/quazip/zip.c \
    $$PWD/quazip/unzip.c \
    foldercompressor.cpp \
    viewdicom2d.cpp \
    download.cpp \
    downloadlist.cpp \
    viewdicom3d.cpp \
    dicomdb.cpp \
    pacswindow.cpp \
    progress.cpp \
    listofcompression.cpp


FORMS += \
    viewdicom2d.ui \
    viewdicom3d.ui \
    pacswindow.ui \
    progress.ui \
    listofcompression.ui














