#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modbus_ctx.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnReadInputRegs_clicked();

    void on_btnConnect_clicked(bool checked);

    void on_btnReadHoldingRegs_clicked();

    void on_btnWriteSingleReg_clicked();

private:
    Ui::MainWindow *ui;
    modbus_ctx mb_ctx;
};
#endif // MAINWINDOW_H
