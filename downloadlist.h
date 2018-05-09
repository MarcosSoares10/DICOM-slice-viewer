#ifndef DOWNLOADLIST_H
#define DOWNLOADLIST_H

#include <QObject>

class DownloadList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString Type READ Type WRITE setType NOTIFY TypeChanged)
    Q_PROPERTY(bool lockstate READ lockstate WRITE setLockstate NOTIFY lockstateChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
public:
    DownloadList(QObject *parent = 0);
    DownloadList(const QString &name,const QString &Type,const bool &lockstate,const QString &url,QObject *parent = 0);

    QString name()const;
    void setName(const QString &name);

    QString Type()const;
    void setType(const QString &Type);

    bool lockstate()const;
    void setLockstate(const bool &lockstate);

    QString url()const;
    void setUrl(const QString &url);

signals:
    void nameChanged();
    void TypeChanged();
    void lockstateChanged();
    void urlChanged();




private:
  QString Name;
  QString TypeA;
   bool Lockstate;
    QString Url;
};

#endif // DOWNLOADLIST_H
