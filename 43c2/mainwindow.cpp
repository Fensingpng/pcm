#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "QDebug"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание объекта CustomPlot
    QCustomPlot *sign = new QCustomPlot(this);
    QCustomPlot *real = new QCustomPlot(this);
    QCustomPlot *imag = new QCustomPlot(this);
    QCustomPlot *spectr =  new QCustomPlot(this);



    // Чтение данных из файла PCM
    QFile file("C:/Users/Admin/Desktop/pcm-main/43c2/часть 1.pcm");
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
    fftw_complex *in, *out;
    fftw_plan plan;

    int N = sampleCount; // Размер входных данных

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) *N);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) *N);

    // Создание плана для преобразования Фурье
    plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);


    for (int i = 0; i < sampleCount; i++) {
        qint16 sample = *reinterpret_cast<const qint16*>(rawData.constData() + i * sizeof(qint16));
        in[i][0] = sample; // Вещественная часть
        in[i][1] = 0;      // Мнимая часть
    }

    fftw_execute(plan);

    double* spectrum = new double[N];

    for (int i = 0; i < N; i++) {
        double real = out[i][0];
        double imaginary = out[i][1];
        spectrum[i] = sqrt(real * real + imaginary * imaginary);
    }





    QVector<double> xData(N);
    QVector<double> yData(N);
    for(int i = 0; i < N; i++) {
        xData[i] = i; // Частота
        yData[i] = spectrum[i]; // Амплитуда
    }




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


    spectr->addGraph();
    spectr->graph(0)->setData(xData, yData);
    spectr->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    spectr->xAxis->setLabel("Frequency");
    spectr->yAxis->setLabel("Amplitude");
    spectr->setGeometry(700,500,700,500);

    spectr->replot();
    imag->replot();
    real->replot();
    sign->replot();

}
MainWindow::~MainWindow()
{
    delete ui;
}
