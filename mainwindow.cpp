#include "mainwindow.h"
#include "ui_mainwindow.h"
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

void MainWindow::add_button(q_button* button)
{
    button->setParent(ui->horizontalWidget);
    ui->horizontalLayout->addWidget(button);
}
