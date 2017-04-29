#include "mainwindow.h"
#include "job_trigger.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    // Time limitation
    /*
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd");
        if(current_date>"2016-12-31")
        {
            QMessageBox::about(0,"本软件已过期","本软件已过期");
            return 0;
        }
    }
    */

    MainWindow w;
    job_trigger * jt=new job_trigger;

    QObject::connect(jt,&job_trigger::show_job,&w,&MainWindow::add_button);

    jt->init();
    jt->load_job();

    w.show();

    return a.exec();
}
