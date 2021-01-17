QT       += core gui widgets opengl

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Dependencies/GDCM/bin \
               $$PWD/Dependencies/GDCM/include/gdcm-3.0 \
               $$PWD/Dependencies/GDCM/lib


LIBS += -lgdcmMSFF -lgdcmCommon \
        -lgdcmDICT -lgdcmDSED \
        -lgdcmexpat -lgdcmIOD \
       -lgdcmjpeg8 -lgdcmjpeg12 \
       -lgdcmjpeg16  \
       -lgdcmzlib -lgdcmcharls -lgdcmexpat -lgdcmopenjp2  -ldl

LIBS += -L"$$PWD/Dependencies/GDCM/bin" \
        -L"$$PWD/Dependencies/GDCM/include/gdcm-3.0" \
        -L"$$PWD/Dependencies/GDCM/lib"

SOURCES += \
    main.cpp \
    dicomdb.cpp \
    viewdicom2d.cpp

HEADERS += \
    dicomdb.h \
    viewdicom2d.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



FORMS += \
    viewdicom2d.ui
