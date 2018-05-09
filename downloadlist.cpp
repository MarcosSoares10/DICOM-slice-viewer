#include "downloadlist.h"

DownloadList::DownloadList(const QString &name, const QString &Type, const bool &lockstate, const QString &url, QObject *parent)
    : QObject(parent),Name(name),TypeA(Type),Lockstate(lockstate),Url(url)
{

}

QString DownloadList::name()const
{
    return Name;

}

void DownloadList::setName(const QString &name){
    if(name!=Name){
        Name=name;
        emit nameChanged();

    }
}

QString DownloadList::Type()const
{
    return TypeA;

}

void DownloadList::setType(const QString &Type){
    if(Type!=TypeA){
        TypeA=Type;
        emit TypeChanged();

    }
}

bool DownloadList::lockstate()const
{
    return Lockstate;

}

void DownloadList::setLockstate(const bool &lockstate){
    if(lockstate!=Lockstate){
        Lockstate=lockstate;
        emit lockstateChanged();

    }
}

QString DownloadList::url()const
{
    return Url;

}

void DownloadList::setUrl(const QString &url){
    if(url!=Url){
        Url=url;
        emit urlChanged();

    }
}
