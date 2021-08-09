#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T15:55:57
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Naivipi2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Audio/threadaudio.cpp \
    Communicate/threadcommunicate.cpp \
    Process/threadprocess.cpp \
    Screen/threadscreen.cpp \
    mainaction.cpp \
    Process/processcontrol.cpp \
    Process/processmodel.cpp \
    debug.cpp \
    common.cpp \
    Communicate/communicatecontrol.cpp \
    Communicate/communicatemodel.cpp \
    Communicate/communicateview.cpp \
    Screen/screencontrol.cpp \
    Screen/screenhmi.cpp \
    Screen/screenmodel.cpp \
    Audio/audio.cpp \
    Audio/audiocontrol.cpp \
    Audio/audiomodel.cpp

HEADERS  += mainwindow.h \
    Audio/threadaudio.h \
    Communicate/threadcommunicate.h \
    Process/threadprocess.h \
    Screen/threadscreen.h \
    mainaction.h \
    Process/processcontrol.h \
    Process/processmodel.h \
    define_thread.h \
    structcommunicatedata.h \
    debug.h \
    common.h \
    Communicate/communicatecontrol.h \
    Communicate/communicatemodel.h \
    Communicate/communicateview.h \
    Screen/screencontrol.h \
    Screen/screenHMI.h \
    Screen/screenmodel.h \
    Audio/audio.h \
    Audio/audiocontrol.h \
    Audio/audiomodel.h \
    Define_Api.h \
    Audio/define_audio.h

FORMS    += mainwindow.ui
