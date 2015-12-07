#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

#include"q_button.h"

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
    q_button * button = new q_button(ui->horizontalWidget);
    button->init(name,cmd,number,status);
//    button>init(name,cmd,number,status);
    ui->horizontalLayout->addWidget(button);
    return;
}
