#include <QCoreApplication>
#include <QFile>
#include <QtEndian>
#include <QDebug>

#include <mem.h>

void readWav(const QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    quint32 chunkDataSize = 0;
    QByteArray temp_buff;
    char buff[0x04];
    while (true) {
        QByteArray tmp = file.read(0x04);
        temp_buff.append(tmp);
        int idx = temp_buff.indexOf("data");
        if (idx >= 0) {
            int lenOfData = temp_buff.length() - (idx + 4);
            memcpy(buff, temp_buff.constData() + idx + 4, lenOfData);
            int bytesToRead = 4 - lenOfData;

            if (bytesToRead > 0) {
                int read = file.read(buff + lenOfData, bytesToRead);
                if (bytesToRead != read) {
                    qDebug() << "something awful happens";
                    return;
                }
            }
            chunkDataSize = qFromLittleEndian<quint32>((const uchar*)buff);
            break;
        }
        if (temp_buff.length() >= 8) {
            temp_buff.remove(0, 0x04);
        }
    }
    if (!chunkDataSize) {
        qDebug() << "chunk data not found";
        return;
    }
    qDebug() << "length of chunks =" << chunkDataSize;
    int samples = 0;
    while (file.read(buff, 0x04) > 0) {
        chunkDataSize -= 4;
        ++samples;
        qint16 sampleCannel1 = qFromLittleEndian<qint16>((const uchar*)buff);
        qint16 sampleCannel2 = qFromLittleEndian<qint16>((const uchar*)buff);

        if (chunkDataSize == 0 || chunkDataSize & 0x80000000) {
            break;
        }
    }
    qDebug() << "readed" << samples << "samples";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    readWav("C:/Users/ovsya/OneDrive/Рабочий стол/123/124.wav");
    return a.exec();
}
