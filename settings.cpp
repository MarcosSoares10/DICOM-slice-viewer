#include "settings.h"
#include "quazip/JlCompress.h"
#include "QDebug"

#include "QFileDialog"


Settings::Settings(QObject *parent) :
    QObject(parent)
{
m_sSettingsFile = QApplication::applicationDirPath().left(1) + "/infinisettings.ini";
}

// Set UserName
void Settings::setValue(const QString key, const QVariant value) {
   QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);


}

// Get UserName
QVariant Settings::value(const QString key, const QVariant defaultValue) const {
 QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}


// Set ExamType
void Settings::setValueExam(const QString key, const QVariant value) {
    QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);


}

// Get ExamType
QVariant Settings::valueExam(const QString key, const QVariant defaultValue) const {
    QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}


// Set Token
void Settings::setValueToken(const QString key, const QVariant value) {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);

}

// Get Token
QVariant Settings::valueToken(const QString key, const QVariant defaultValue) const {
    QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}

// Set Id
void Settings::setValueId(const QString key, const QVariant value) {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);


}

// Get Id
QVariant Settings::valueId(const QString key, const QVariant defaultValue) const {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}


// Set FolderCompressFilePath
void Settings::setValueFolderCompressFilePath(const QString key, const QVariant value) {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);


}

// Get FolderCompressFilePath
QVariant Settings::valueFolderCompressFilePath(const QString key, const QVariant defaultValue) const {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}

// Set ExamID
void Settings::setValueExamID(const QString key, const QVariant value) {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
   settings_.setValue(key, value);


}

// Get ExamID
QVariant Settings::valueExamID(const QString key, const QVariant defaultValue) const {
QSettings settings_(m_sSettingsFile,QSettings::IniFormat);
    return settings_.value(key, defaultValue);

}



