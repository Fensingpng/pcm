QT += core gui
QT += datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# Указываем пути к заголовочным файлам
INCLUDEPATH += $$PWD/../bibl/fftw \
               $$PWD/../bibl/rtl-sdr-master/include \
               $$PWD/../bibl/libusb

# Указываем пути к библиотекам и сами библиотеки
LIBS += -L$$PWD/../bibl/fftw -lfftw3-3 \
        $$PWD/../bibl/fftw/libfftw3-3.a \
        $$PWD/../bibl/fftw/libfftw3f-3.a \
        $$PWD/../bibl/fftw/libfftw3l-3.a \
        -L$$PWD/../bibl/rtl-sdr-master -lrtlsdr \
        -L$$PWD/../bibl/libusb libusb-1.0

# Определения
DEFINES += QT_DEPRECATED_WARNINGS

# Источники и заголовочные файлы
SOURCES += \
    dataloader.cpp \
    main.cpp \
    mainwindow.cpp \
    packetspectrumcalculator.cpp \
    qcustomplot.cpp \
    signalproc.cpp

HEADERS += \
    dataloader.h \
    fftw/fftw3.h \
    mainwindow.h \
    packetspectrumcalculator.h \
    qcustomplot.h \
    signalproc.h

FORMS += \
    form.ui

# Правила по умолчанию для развертывания
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
