#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void add_button(const std::string & ,const std::string & ,int,int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
