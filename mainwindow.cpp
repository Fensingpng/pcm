#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = "C:/qtt/43 c++/43c/12333.pcm";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return;
    }

    QByteArray pcmData = file.readAll();
    file.close();


    // Пример вывода информации о PCM данных
    qDebug() << "PCM data size:" << pcmData.size();
}


