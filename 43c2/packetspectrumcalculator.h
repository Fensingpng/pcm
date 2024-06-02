#ifndef PACKETSPECTRUMCALCULATOR_H
#define PACKETSPECTRUMCALCULATOR_H

#include <QObject>
#include <QVector>
#include <fftw3.h>
#include <cmath>

class PacketSpectrumCalculator : public QObject
{
    Q_OBJECT
public:
    explicit PacketSpectrumCalculator(const QVector<double>& packetData, double sampleRate, QObject *parent = nullptr);
    ~PacketSpectrumCalculator();

    QVector<double> calculateSpectrum();
    QVector<double> getFrequency() const;

private:
    QVector<double> m_freq;
    QVector<double> m_spectrum;
    double m_sampleRate;
};

#endif // PACKETSPECTRUMCALCULATOR_H
