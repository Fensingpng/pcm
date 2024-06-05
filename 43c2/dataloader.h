#ifndef DATALOADER_H
#define DATALOADER_H
#include <rtl-sdr.h>
#include <QByteArray>
#include <QDebug>

class DataLoader : public QObject {
    Q_OBJECT
public:
    explicit DataLoader(QObject *parent = nullptr);

    QByteArray readDataFromRTLSDR(int deviceIndex = 0, int frequency = 1090000000, int sampleRate = 2000000, int durationSec = 10);

private:
    int initDevice(int deviceIndex, int frequency, int sampleRate);

    rtlsdr_dev_t *device = nullptr;
};


#endif // DATALOADER_H
