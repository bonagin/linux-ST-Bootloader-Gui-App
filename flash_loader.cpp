#include <QThread>
#include <qdebug.h>
#include <QFile>
#include <qfiledevice.h>
#include <qdialog.h>
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QProcess>
#include <QFileDialog>
//#include "wait_dialog.h"
#include "sleeper.h"
#include "flash_loader.h"

QString path = "" ;
QString portName = "";

cFlashLoader * cFlashLoader::__instance = NULL;

cFlashLoader * cFlashLoader::get()
{
    if(!__instance)
    {
        __instance = new cFlashLoader();
    }

    return __instance;
}


cFlashLoader::cFlashLoader(QObject *parent) :
    QThread(parent)
{

}

void cFlashLoader::connect_com(QString portName)
{
    port = new QSerialPort(QLatin1String(portName.toLatin1()));

    if(port->isOpen())
    {
        port->close();
    }

    port->setBaudRate(115200);
    port->setFlowControl(port->NoFlowControl);
    port->setParity(port->EvenParity);
    port->setDataBits(port->Data8);
    port->setStopBits(port->OneStop);

    if(port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
    {
        qDebug()<< portName << " opened\n";
    }
    else
    {
        qDebug()<< "Failed to open " << portName << "\n";
    }
}

void cFlashLoader::run()
{

}

void cFlashLoader::run_program()
{
    if(path == "")
    {
     emit set_textedit("Please Load binary file\n");
    }
    else
    {
    emit disable_btnconnect(false);
    emit disable_btnload(false);
    emit disable_btnreadinfo(false);
    emit disable_btnProgram(false);

    mProcess = new QProcess(this);

    connect(mProcess, SIGNAL(started()), this, SLOT(process_started()));
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(getOutput()));

    QString program = "stm32flash";
    QStringList Arguments;
    Arguments<<"-w"
             << path
             << portName;
    mProcess->setReadChannelMode(QProcess::MergedChannels);
    mProcess->start(program,Arguments);
    }
}

void cFlashLoader::read_devInfo()
{
    mProcess = new QProcess(this);

    connect(mProcess, SIGNAL(started()), this, SLOT(process_started()));
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(get_devInfo()));
    connect(this, SIGNAL(kill_process()),  mProcess, SLOT(kill()));

    QString program = "stm32flash";
    QStringList Arguments;
    Arguments << portName;
    mProcess->setReadChannelMode(QProcess::MergedChannels);
    mProcess->start(program,Arguments);
}

void cFlashLoader::get_file(QString file)
{
    path = file ;
}

void cFlashLoader::getOutput()
{
    QByteArray stdout = mProcess->readAllStandardOutput();
    char * stdout_ = stdout.data();
    //qDebug() << stdout_;

    int argc = 20;
    char * argv[20];

    util_parse_params(stdout_,argv,argc,'(','%');

    if(argc > 0)
    {
        QString value = argv[1];
        int pg_value = value.toFloat();

        emit set_pg_value(pg_value);

        if(pg_value > 97.00)
        {
            pg_value = 0;
            argc = 0;
            emit disable_btnconnect(true);
            emit disable_btnload(true);
            emit disable_btnreadinfo(true);
            emit disable_btnProgram(true);

            emit set_pg_value(pg_value);
        }
    }

}
void cFlashLoader::get_devInfo()
{
    QByteArray stdout = mProcess->readAllStandardOutput();
    char * stdout_ = stdout.data();
    //qDebug() << stdout_;

    int argc = 20;
    char * argv[20];

    util_parse_params(stdout_,argv,argc,'_','_');

    if(argc > 0)
    {
        QString value = argv[1];

        emit set_textedit(value);
    }

}

void cFlashLoader::process_started()
{

}

void cFlashLoader::get_path(QString path_)
{
    path = path_;
}

void cFlashLoader::get_portname(QString portName_)
{
   portName = "/dev/" + portName_;
}

void cFlashLoader::util_parse_params(char *str,char *argv[],int &argc,char delim1,char delim2)
{

    int max_args = argc;
    char * cmdl = str;
    bool done = false;
    argc = 0;
    char delim = delim1;

    while ( !done )
    {

 /*      Strip Leading Whitespce
        while ( isspace(*cmdl) )
        {
            if ( *cmdl )
            {
                cmdl++;
            }
            else
            {
                done = true;
                break;
            }
        }*/

        /* Now we are at an arg */
        if ( !done && *cmdl )
        {
            argv[argc] = cmdl;
            argc++;
            if (argc >= max_args)
            {
                done =true;
                break;
            }
        }
        /* Go to the next delim */
        while ( delim != *cmdl )
        {
            if ( *cmdl )
            {
                cmdl++;
            }
            else
            {
                done = true;
                break;
            }
        }
        if ( *cmdl )
        {
            *cmdl = 0;
            cmdl++;
        }
        else
        {
            done = true;
        }
        if (argc)
        {
            delim = delim2;
        }
    }
}

cFlashLoader::~cFlashLoader()
{

}

