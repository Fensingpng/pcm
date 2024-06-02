#include "DataLoader.h"

DataLoader::DataLoader(QObject *parent) : QObject(parent)
{

}

QByteArray DataLoader::readData(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();

    return rawData;
}

