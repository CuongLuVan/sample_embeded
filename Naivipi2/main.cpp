#include "mainwindow.h"
#include <QApplication>
#include "mainaction.h"
#include "Communicate/communicatecontrol.h"
#include "Communicate/communicatemodel.h"
#include "process.h"
#include "Screen/screencontrol.h"
#include "Audio/audio.h"

QTimer *timer;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainAction mac;
    MainWindow w;
    mac.start();
    w.show();

    return a.exec();
}
