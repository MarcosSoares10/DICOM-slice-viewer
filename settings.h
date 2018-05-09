#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class Settings : public QObject
{
    Q_OBJECT


public:
    explicit Settings(QObject *parent = 0);
     QString m_sSettingsFile;


    // UserName
    Q_INVOKABLE void setValue(const QString key, const QVariant value);
    Q_INVOKABLE QVariant value(const QString key, const QVariant defaultValue = QVariant()) const;

    // ExamType
    Q_INVOKABLE void setValueExam(const QString key, const QVariant value);
    Q_INVOKABLE QVariant valueExam(const QString key, const QVariant defaultValue = QVariant()) const;

    // Token
    Q_INVOKABLE void setValueToken(const QString key, const QVariant value);
    Q_INVOKABLE QVariant valueToken(const QString key, const QVariant defaultValue = QVariant()) const;

    // Id
    Q_INVOKABLE void setValueId(const QString  key, const QVariant value);
    Q_INVOKABLE QVariant valueId(const QString key, const QVariant defaultValue = QVariant()) const;

    // Folder Compress
    Q_INVOKABLE void setValueFolderCompressFilePath(const QString  key, const QVariant  value);
    Q_INVOKABLE QVariant valueFolderCompressFilePath(const QString key, const QVariant defaultValue = QVariant()) const;

    // ExamID
    Q_INVOKABLE void setValueExamID(const QString  key, const QVariant value);
    Q_INVOKABLE QVariant valueExamID(const QString key, const QVariant defaultValue = QVariant()) const;

   signals:
   public slots:
   private:

       // UserName
     //  QSettings settings_("settingsFileName",QSettings::NativeFormat);

       // ExamType
     //  QSettings settingsTypeExam_;

       // Token
   //    QSettings settingsToken_;

       // Id
  //     QSettings settingsId_;

       // Folder Compress
  //     QSettings settingsFolderCompressFilePath_;

   };

#endif // BACKEND_H
