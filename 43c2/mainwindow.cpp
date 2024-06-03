#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "QDebug"
#include "dataloader.h"
#include "signalproc.h"
#include "packetspectrumcalculator.h"
#include "packetselector.h"
#include <QMainWindow>
#include <numeric> // для accumulate

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаём объект loader для считывания файла
    DataLoader loader;
    QByteArray rawData = loader.readData("C:/Qt/pcm-main/signal/Ft.pcm");

    // Создаём объект signalProcessor для формирования двух массивов из файла
    SignalProcessor signalProcessor(rawData);
    const QVector<double>& x = signalProcessor.getX();
    const QVector<double>& y = signalProcessor.getY();

    // Создаём окно для отображения графика  временного представления сигнала
    QMainWindow *signWindow = new QMainWindow();
    QCustomPlot *sign = new QCustomPlot(signWindow);
    sign->addGraph();
    sign->graph(0)->setData(x, y);
    sign->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    sign->xAxis->setLabel("Time");
    sign->yAxis->setLabel("Amplitude");
    sign->xAxis->setRange(0, x.size());
    sign->yAxis->setRange(0, y.size());
    sign->replot();
    signWindow->setCentralWidget(sign);
    signWindow->show();
    signWindow->showMaximized();

    int packetSize = 10000;
    double threshold = 1000000; // Пример порогового значения
    int numMeasurements = 500;
    double sampleRate = 600e6; // Частота дискретизации 600 МГц
    double Diap = 2e6;
    double Gerz=Diap/x.size();
    bool previousDetected = false;


    for (int i = 0; i < numMeasurements; ++i) {
        int start = i * packetSize;
        int end = std::min(start + packetSize, y.size());
        if (start >= y.size()) break;

        QVector<double> segment = y.mid(start, end - start);

        PacketSpectrumCalculator spectrumCalculator(segment, sampleRate);
        QVector<double> freq = spectrumCalculator.getFrequency();
        QVector<double> spectrum = spectrumCalculator.calculateSpectrum();

        double sum = 0.0;
        double maxSpectrum = 0.0;
        for (int j = 300; j < spectrum.size(); ++j) {
            sum += spectrum[j];
            if (maxSpectrum < spectrum[j]) {
                maxSpectrum = spectrum[j];
            }
        }

        double averageSpectrum = (sum / (spectrum.size()))*100;
        double thresholdValue = averageSpectrum + threshold;
        if (thresholdValue < maxSpectrum) {
            if (!previousDetected) {
                double minFrequency  =sampleRate + (start * Gerz);
                double maxFrequency  =sampleRate + (end * Gerz);
                QString minFrequencyStr = QString::number(minFrequency, 'f', 0);
                QString maxFrequencyStr = QString::number(maxFrequency, 'f', 0);
                QString thresholdStr = QString::number(thresholdValue, 'f', 2);
                QString maxSpectrumStr = QString::number(maxSpectrum, 'f', 2);
                qDebug() << "Drone detected in segment Гц" << minFrequencyStr << "to Гц" << maxFrequencyStr ;
                qDebug() << "Drone detected in time" << packetSize + start  << "to" <<packetSize + end ;
                qDebug() << "Threshold:" << thresholdStr << "Max Spectrum:" << maxSpectrumStr;
            }
               previousDetected = true; // Устанавливаем флаг, что текущий сегмент обнаружен
           } else {
               previousDetected = false; // Сбрасываем флаг, если текущий сегмент не обнаружен
           }
       }
   }

MainWindow::~MainWindow()
{
    delete ui;
}
