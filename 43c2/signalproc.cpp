#include "signalproc.h"

SignalProcessor::SignalProcessor(const QByteArray& rawData) {
    const qint16 *data = reinterpret_cast<const qint16 *>(rawData.constData());
    int sampleCount = rawData.size() / sizeof(qint16);

    QVector<std::complex<float>> complexSignal(sampleCount / 2);
    for(int i = 0; i < sampleCount; i += 2) {
        complexSignal[i / 2] = std::complex<float>(static_cast<float>(data[i]), static_cast<float>(data[i + 1]));
    }

    x.resize(complexSignal.size());
    y.resize(complexSignal.size());
    for(int i = 0; i < complexSignal.size(); ++i) {
        x[i] = i;
        y[i] = std::abs(complexSignal[i]);
    }
}

const QVector<double>& SignalProcessor::getX() const {
    return x;
}

const QVector<double>& SignalProcessor::getY() const {
    return y;
}
