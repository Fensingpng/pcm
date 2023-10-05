#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание объекта CustomPlot
    QCustomPlot *customPlot = new QCustomPlot(this);

    // Чтение данных из файла PCM
    QFile file("C:/qtt/43 c++/Часть 1.pcm");
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

        // Вычисление времени для каждого сэмпла
        time[i] = i;

        // Преобразование сэмпла в сигнал (если необходимо)
        signal[i] = sample;
    }

    // Установка данных на графике
    customPlot->addGraph();
    customPlot->graph(0)->setData(time, signal);

    // Управление масштабированием и перемещением графика
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Оси координат
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Signal");

    // Отображение графика
    customPlot->replot();

    // Добавление графика на главное окно
    setCentralWidget(customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
