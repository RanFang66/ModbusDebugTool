#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modbus_ctx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int ret = 0;
    ui->setupUi(this);
    ret = mb_ctx.ModbusRtuInit();
    if (ret == -1) {
        ui->txtDisp->appendPlainText("MODBUS INIT FAILED\n");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnReadInputRegs_clicked()
{
    QString txt;
    int addr = 0;
    int len = 0;
    int ret = 0;

    txt = ui->spinReadInputAddr->text();
    addr = txt.toInt();

    txt = ui->spinReadInputNum->text();
    len = txt.toInt();
    ret = mb_ctx.ReadInputRegs(addr, len);
    if (ret > 0) {
        ui->txtDisp->appendPlainText("read ok.\n");
    }
}

void MainWindow::on_btnConnect_clicked(bool checked)
{
    int ret = 0;
    QString txt;
    int baudrate = 0;

    txt = ui->inputBaudrate->text();
    baudrate = txt.toInt();
    mb_ctx.setBaudrate(baudrate);

    txt = ui->inputComPort->text();
    if (txt.startsWith("COM") && txt[3].isDigit()) {
        mb_ctx.setComPort(txt);
    } else {
        ui->txtDisp->appendPlainText("INPUT COM PORT INVALID!\n");
        return;
    }

    if (checked) {
        ret = mb_ctx.ModbusRtuConnect();
        if (ret == -1) {
            ui->txtDisp->appendPlainText("COM PORT OPEN FAILED.\n");
        }
    } else {
        if (mb_ctx.ModbusRtuIsConnected())
            mb_ctx.ModbusRtuDisconnect();
    }
}
