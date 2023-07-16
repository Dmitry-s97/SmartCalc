QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += Credit/creditcalc.cpp \
    main.cpp \
    MainCalc/mainwindow.cpp \
    qcustomplot.cpp \
    Controller/s21_controller.cc \
    Model/s21_model.cc

HEADERS += Credit/creditcalc.h \
    MainCalc/mainwindow.h \
    qcustomplot.h \
    Controller/s21_controller.h \
    Model/s21_model.h

FORMS += Credit/creditcalc.ui \
    MainCalc/mainwindow.ui

win32:RC_FILE = MainCalc/file.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Page/css/style.css \
    Page/image/about/classic.jpg \
    Page/image/about/credit.jpg \
    Page/image/about/deposit.jpg \
    Page/image/intro/intro.jpg \
    Page/image/work/classic_work.jpg \
    Page/image/work/credit_work.jpg \
    Page/image/work/deposit_work.jpg \
    Page/page.html \
    Page/file.rc \
    Page/img/credit.png

RESOURCES += \
    resource.qrc
