#ifndef DATALOADER_H
#define DATALOADER_H

#include <QObject>
#include <QFile>

class DataLoader: public QObject
{
    Q_OBJECT
public:
    explicit DataLoader(QObject *parent = nullptr);

    QByteArray readData(const QString &filePath);

};

#endif // DATALOADER_H
