#ifndef SIGNALPROC_H
#define SIGNALPROC_H

#include <QVector>
#include <complex>

extern int x,y;

class SignalProcessor
{
public:
    SignalProcessor(const QByteArray& rawData);

        const QVector<double>& getX() const;
        const QVector<double>& getY() const;
private:
        QVector<double> x;
        QVector<double> y;
};

#endif // SIGNALPROC_H
