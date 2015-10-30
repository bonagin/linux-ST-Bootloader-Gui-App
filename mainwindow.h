#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usb_thread.h"
#include "usb_device.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    usbThread * thread;

public:
    explicit MainWindow(QWidget *parent = 0);

    void connect_slots();

    void on_btnLoad_clicked();

    ~MainWindow();

private slots:
    void on_btnload_clicked();
    void on_btconnect_dev_clicked();
};

#endif // MAINWINDOW_H
