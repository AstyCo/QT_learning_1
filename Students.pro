#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T11:56:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Students
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    studentmodel.cpp \
    loadfile.cpp \
    delegate.cpp \
    loginsql.cpp \
    editablesqlmodel.cpp

HEADERS  += mainwindow.h \
    student.h \
    studentmodel.h \
    loadfile.h \
    delegate.h \
    loginsql.h \
    editablesqlmodel.h

FORMS    += mainwindow.ui \
    loadfile.ui \
    loginsql.ui
TRANSLATIONS    += app_ru.ts

RESOURCES += \
    src.qrc

