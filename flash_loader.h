#ifndef FlashLoader_H
#define FlashLoader_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QProcess>
#include "qprocess.h"

class QProcess;

class cFlashLoader : public QThread
{
    Q_OBJECT

public:
    explicit cFlashLoader(QObject *parent = 0);

    static cFlashLoader * get();

    QProcess * mProcess ;

    QSerialPort *port;

    void get_path(QString path_);
    void get_portname(QString portName_);
    void util_parse_params(char *str,char *argv[],int &argc,char delim1,char delim2);
    ~cFlashLoader();

signals:
    void wait_window_show();
    void wait_window_close();
    void set_pg_value(int value);
    void set_textedit(QString Value);
    void disable_btnconnect(bool state);
    void disable_btnload(bool state);
    void disable_btnreadinfo(bool state);
    void disable_btnProgram(bool state);
    void kill_process();

public slots:
    void run();
    void get_file(QString file);
    void connect_com(QString portName);
    void process_started();
    void getOutput();
    void get_devInfo();
    void run_program();
    void read_devInfo();

private:
     static cFlashLoader* __instance;
};

#endif // FlashLoader_H
