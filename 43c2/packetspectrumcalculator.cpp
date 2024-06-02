#include "packetspectrumcalculator.h"
#include <fftw3.h>
#include <cmath>

PacketSpectrumCalculator::PacketSpectrumCalculator(const QVector<double>& packetData, double sampleRate, QObject *parent)
    : QObject(parent), m_sampleRate(sampleRate)
{
    int N = packetData.size();

    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    for (int i = 0; i < N; i++) {
        in[i][0] = packetData[i];
        in[i][1] = 0;
    }

    fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    m_freq.resize(N);
    m_spectrum.resize(N);

    // Рассчитываем реальные частоты
    double freqResolution = m_sampleRate / N;
    for (int i = 0; i < N; i++) {
        m_freq[i] = 600e6 + i * freqResolution; // Начинаем с 600 МГц и увеличиваем на шаг freqResolution
        m_spectrum[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

PacketSpectrumCalculator::~PacketSpectrumCalculator()
{
}

QVector<double> PacketSpectrumCalculator::calculateSpectrum()
{
    return m_spectrum;
}

QVector<double> PacketSpectrumCalculator::getFrequency() const
{
    return m_freq;
}
