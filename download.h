#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QList>
#include "downloadlist.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

class Download : public QObject
{
    Q_OBJECT
public:
    explicit Download(QObject *parent = 0);
    QList<QObject*> download_lista;
    QList<QObject*> listar_downloads();
    QNetworkReply *reply;
    void recebe_api();

signals:

public slots:

private:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

};

#endif // DOWNLOAD_H
