#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_button(const QString & name,const QString & cmd ,int number ,int status)
{
    QPushButton * pushButton_3 = new QPushButton(ui->horizontalWidget);
    pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
    pushButton_3->setMouseTracking(true);
    pushButton_3->setStyleSheet("background-color: rgb(170, 0, 255);");
    ui->horizontalLayout->addWidget(pushButton_3);
}
