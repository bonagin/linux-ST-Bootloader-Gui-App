#include <QThread>
#include <qdebug.h>
#include <QFile>
#include <qfiledevice.h>
#include <qdialog.h>
#include <QtWidgets>
//#include "wait_dialog.h"
//#include "sleeper.h"
#include "serial.h"

//QString path = "" ;

serial * serial::__instance = NULL;

serial * serial::get()
{
    if(!__instance)
    {
        __instance = new serial();
    }

    return __instance;
}


serial::serial(QObject *parent) :
    QThread(parent)
{

}

void serial::run()
{

}

void serial::get_file(QString file)
{

}

serial::~serial()
{

}
