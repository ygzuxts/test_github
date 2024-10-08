#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnnum0, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum1, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum2, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum3, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum4, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum5, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum6, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum7, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum8, SIGNAL(clicked()), this, SLOT(btnnumclick()));
    connect(ui->btnnum9, SIGNAL(clicked()), this, SLOT(btnnumclick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnnumclick()
{
    QString str = ui->display->text();
    str += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(str);
    ui->statusbar->showMessage(qobject_cast<QPushButton*>(sender())->text() + "clicked");

}
