#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QThread>

class serial : public QThread
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = 0);

    static serial * get();
    ~serial();

signals:
    void wait_window_show();
    void wait_window_close();

public slots:
    void run();
    void get_file(QString file);

private:
     static serial* __instance;

};

#endif // SERIAL_H
