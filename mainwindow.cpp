#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modbus_ctx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    } else {
        ui->txtDisp->appendPlainText("READ FAILED.\n");
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
    if (txt.startsWith("COM", Qt::CaseInsensitive) && txt[3].isDigit()) {
        mb_ctx.setComPort(txt);
    } else {
        ui->txtDisp->appendPlainText("INPUT COM PORT INVALID!\n");
        return;
    }


    if (checked) {
        if (mb_ctx.ModbusRtuInit() == -1) {
            ui->txtDisp->appendPlainText("INIT MODBUS FAILED!\n");
            return;
        }
        ret = mb_ctx.ModbusRtuConnect();
        if (ret == -1) {
            ui->txtDisp->appendPlainText("COM PORT OPEN FAILED.\n");
        } else {
            ui->txtDisp->appendPlainText("CONNECT SUCCESS!");
        }
    } else {
        if (mb_ctx.ModbusRtuIsConnected()) {
            mb_ctx.ModbusRtuDisconnect();
            ui->txtDisp->appendPlainText("DISCONNECT OK");
        }
    }
}

void MainWindow::on_btnReadHoldingRegs_clicked()
{
    QString txt;
    int addr = 0;
    int len = 0;
    int ret = 0;

    txt = ui->spinReadHoldingAddr->text();
    addr = txt.toInt();

    txt = ui->spinReadHoldingNum->text();
    len = txt.toInt();
    ret = mb_ctx.ReadHoldingRegs(addr, len);
    if (ret > 0) {
        ui->txtDisp->appendPlainText("Read Input Register OK.\n");
    } else {
        ui->txtDisp->appendPlainText("READ FAILED.\n");
    }
}

void MainWindow::on_btnWriteSingleReg_clicked()
{
    QString txt;
    int addr = 0;
    int val = 0;
    int ret = 0;

    txt = ui->spinWriteAddr->text();
    addr = txt.toInt();

    txt = ui->inputWriteValue->text();
    val = txt.toInt();
    ret = mb_ctx.WriteSingleReg(addr, val);
    if (ret != -1) {
        ui->txtDisp->appendPlainText("Write Single Register OK.\n");
    } else {
        ui->txtDisp->appendPlainText("Write FAILED.\n");
    }
}
