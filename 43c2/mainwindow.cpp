#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание объекта CustomPlot
    QCustomPlot *sign = new QCustomPlot(this);
    QCustomPlot *real = new QCustomPlot(this);
    QCustomPlot *imag = new QCustomPlot(this);
    QCustomPlot* customPlot = new QCustomPlot();


    // Чтение данных из файла PCM
    QFile file("C:/43c2/часть 1.pcm");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();

    // Размер сэмпла в байтах
    int byteSize = sizeof(qint16);

    // Количество сэмплов
    int sampleCount = rawData.size() / byteSize;

    // Создание временной шкалы и сигнала на основе данных PCM
    QVector<double> time(sampleCount);
    QVector<double> signal(sampleCount);
    QVector<double> realSignal(sampleCount);
    QVector<double> imaginarySignal(sampleCount);

    for(int i = 0; i < sampleCount; i++) {
        // Чтение сэмпла из данных PCM
        qint16 sample = *reinterpret_cast<const qint16*>(rawData.constData() + i * sizeof(qint16));
        time[i] = i;
        signal[i] = sample;
        realSignal[i] = qCos(qDegreesToRadians(static_cast<double>(sample)));
        imaginarySignal[i] = qSin(qDegreesToRadians(static_cast<double>(sample)));
    }
    //-----------------------------------------------------------------------
    //спектр
//    fftw_complex* fftInput = fftw_alloc_complex(sampleCount);
//    fftw_complex* fftOutput = fftw_alloc_complex(sampleCount);
//    fftw_plan plan = fftw_plan_dft_1d(sampleCount, fftInput, fftOutput, FFTW_FORWARD, FFTW_ESTIMATE);

//    for(int i = 0; i < sampleCount; i++) {
//        fftInput[i][0] = time[i];
//        fftInput[i][1] = signal[i];
//    }

//    fftw_execute(plan);



//    QVector<double> frequencies(sampleCount/2);
//    QVector<double> amplitudes(sampleCount/2);
//    double frequencyStep = 1.0 / (sampleCount * 2);

//    for(int i = 0; i < sampleCount/2; i++) {
//        double frequency = i * frequencyStep;
//        double magnitude = sqrt(fftOutput[i][0] * fftOutput[i][0] + fftOutput[i][1] * fftOutput[i][1]);

//        frequencies[i] = frequency;
//        amplitudes[i] = magnitude;


//    }


//    customPlot->setWindowTitle("Spectrum Plot");
//    customPlot->xAxis->setLabel("Frequency");
//    customPlot->yAxis->setLabel("Amplitude");
//    customPlot->legend->setVisible(true);
//    customPlot->addGraph();
//    customPlot->graph(0)->setData(frequencies, amplitudes);
//    customPlot->xAxis->setRange(0, 0.5);
//    customPlot->yAxis->setRange(0, *std::max_element(amplitudes.begin(), amplitudes.end()));



//    fftw_destroy_plan(plan);
//    fftw_free(fftInput);
//    fftw_free(fftOutput);









    //-----------------------------------------------------------------------
    //Построение графиков


    sign->addGraph();
    sign->graph(0)->setData(time, signal);
    sign->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    sign->xAxis->setLabel("Time");
    sign->yAxis->setLabel("Signal");
    sign->setGeometry(700,0,700,500);


    real->addGraph();
    real->graph(0)->setData(time, realSignal);
    real->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    real->xAxis->setLabel("Time");
    real->yAxis->setLabel("Amlit");
    real->setGeometry(0,0,700,500);


    imag->addGraph();
    imag->graph(0)->setData(time, imaginarySignal);
    imag->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    imag->xAxis->setLabel("Time");
    imag->yAxis->setLabel("Phase");
    imag->setGeometry(0,500,700,500);

    customPlot->replot();
    imag->replot();
    real->replot();
    sign->replot();

}
MainWindow::~MainWindow()
{
    delete ui;
}
