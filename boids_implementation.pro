#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T15:24:18
#
#-------------------------------------------------

QT       += core gui\
             3d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = boids_implementation
TEMPLATE = app


SOURCES += main.cpp\
    boid.cpp \
    boidscene.cpp \
    boidalgo.cpp

HEADERS  += \
    boidscene.h \
    boidalgo.h \
    boid.h

FORMS    += mainwindow.ui
