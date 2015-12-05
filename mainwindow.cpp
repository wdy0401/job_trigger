#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <string>
using namespace std;
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

void MainWindow::add_button(const string & name,const string & cmd ,int number ,int status)
{
    //  yellow  255 255 100
    //  green   38  166 44
    //  blue    41  89  209
    //  red     224 7   2
    //  find in excel
    string color_type;
    switch(status)
    {
        case 0:color_type="background-color: rgb(255,255,100);";break;
        case 1:color_type="background-color: rgb(38,166,44);";break;
        case 2:color_type="background-color: rgb(41,89,209);";break;
        case 3:color_type="background-color: rgb(224,7,2);";break;
        default:color_type="background-color: rgb(150,16,150);";break;
    }
    QPushButton * pushButton_3 = new QPushButton(ui->horizontalWidget);
    pushButton_3->setFixedHeight(75);
    pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
    pushButton_3->setMouseTracking(true);
    pushButton_3->setStyleSheet(color_type.c_str());
    ui->horizontalLayout->addWidget(pushButton_3);
}
