#include "dataloader.h"

DataLoader::DataLoader(QObject *parent) : QObject(parent) {}

QByteArray DataLoader::readDataFromRTLSDR(int deviceIndex, int frequency, int sampleRate, int durationSec) {
    if (initDevice(deviceIndex, frequency, sampleRate) < 0) {
        qDebug() << "Failed to initialize RTL-SDR device.";
        return QByteArray();
    }

    int bufferSize = sampleRate * durationSec;
    QByteArray data(bufferSize, 0);
    int n_read;

    if (rtlsdr_read_sync(device, data.data(), bufferSize, &n_read) < 0) {
        qDebug() << "Error reading from RTL-SDR device.";
    }

    rtlsdr_close(device);
    return data;
}

int DataLoader::initDevice(int deviceIndex, int frequency, int sampleRate) {
    if (rtlsdr_open(&device, deviceIndex) < 0) {
        qDebug() << "Failed to open RTL-SDR device.";
        return -1;
    }

    if (rtlsdr_set_center_freq(device, frequency) < 0) {
        qDebug() << "Failed to set center frequency.";
        rtlsdr_close(device);
        return -1;
    }

    if (rtlsdr_set_sample_rate(device, sampleRate) < 0) {
        qDebug() << "Failed to set sample rate.";
        rtlsdr_close(device);
        return -1;
    }

    if (rtlsdr_reset_buffer(device) < 0) {
        qDebug() << "Failed to reset buffer.";
        rtlsdr_close(device);
        return -1;
    }

    return 0;
}
