#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_canvas->setBar(ui->statusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->widget_canvas->setType(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget_canvas->setType(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->widget_canvas->setType(3);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->widget_canvas->setType(4);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->widget_canvas->setNum(ui->spinBox->value());
    ui->widget_canvas->setType(5);
}
