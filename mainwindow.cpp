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

    // Чтение данных из файла PCM
    QFile file("C:/Users/Admin/Desktop/43c1/часть 1.pcm");
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

    for(int i = 0; i < sampleCount; i++) {
        // Чтение сэмпла из данных PCM
        qint16 sample = *reinterpret_cast<const qint16*>(rawData.constData() + i * sizeof(qint16));
        time[i] = i;

        signal[i] = sample;
    }

    // Установка данных на графике
    sign->addGraph();
    sign->graph(0)->setData(time, signal);

    // Управление масштабированием и перемещением графика
    sign->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Оси координат
    sign->xAxis->setLabel("Time");
    sign->yAxis->setLabel("Signal");

    // Отображение графика
    sign->replot();

    // Добавление графика на главное окно
    setCentralWidget(sign);




    //-----------------------------------------------------------------------
    //Построение графика спектра

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


    QCustomPlot *spectr =  new QCustomPlot(this);
    QCustomPlot();
    spectr->xAxis->setLabel("Frequency");
    spectr->yAxis->setLabel("Amplitude");

    QVector<double> xData(N);
    QVector<double> yData(N);
    for(int i = 0; i < N; i++) {
        xData[i] = i; // Частота
        yData[i] = spectrum[i]; // Амплитуда
    }
    QCPGraph* graph = spectr->addGraph();
    graph->setData(xData, yData);
    // Отображение графика
    spectr->replot();

    // Добавление графика на главное окно
    setCentralWidget(spectr);

}

MainWindow::~MainWindow()
{
    delete ui;
}
