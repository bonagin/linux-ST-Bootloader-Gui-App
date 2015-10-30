#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QRect>
#include <QDesktopWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <qcombobox.h>
#include <qdialog.h>
#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flash_loader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < ports.size(); i++)
    {
       ui->comboBox->addItem(ports.at(i).portName());
    }
    connect_slots();

}

void MainWindow::connect_slots()
{

    cFlashLoader * cFlashLoader_signal = new cFlashLoader();
    connect(ui->btnprogramm, SIGNAL(clicked()), cFlashLoader_signal, SLOT(run_program()));
    connect(cFlashLoader_signal, SIGNAL(set_pg_value(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->btnInfo,SIGNAL(clicked()), cFlashLoader_signal, SLOT(read_devInfo()));
    connect(cFlashLoader_signal, SIGNAL(set_textedit(QString)),     ui->textEdit, SLOT(append(QString)));
    connect(cFlashLoader_signal, SIGNAL(disable_btnconnect(bool)),  ui->btconnect_dev, SLOT(setEnabled(bool)));
    connect(cFlashLoader_signal, SIGNAL(disable_btnProgram(bool)),  ui->btnprogramm, SLOT(setEnabled(bool)));
    connect(cFlashLoader_signal, SIGNAL(disable_btnload(bool)),     ui->btnload, SLOT(setEnabled(bool)));
    connect(cFlashLoader_signal, SIGNAL(disable_btnreadinfo(bool)), ui->btnInfo, SLOT(setEnabled(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnload_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file.."), " ", tr("*.bin binary files"));
    cFlashLoader::get()->get_path(path);
    cFlashLoader::get()->get_portname(ui->comboBox->currentText());
    ui->lineEdit->setText(path);
}

void MainWindow::on_btconnect_dev_clicked()
{
    cFlashLoader::get()->get_portname(ui->comboBox->currentText());
    ui->btconnect_dev->setText("Connected");
}
