#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T11:56:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Students
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    studentmodel.cpp \
    loadfile.cpp \
    delegate.cpp

HEADERS  += mainwindow.h \
    student.h \
    studentmodel.h \
    loadfile.h \
    delegate.h

FORMS    += mainwindow.ui \
    loadfile.ui
TRANSLATIONS    += app_ru.ts

RESOURCES += \
    src.qrc

