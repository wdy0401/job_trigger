#include "job_trigger.h"
#include <QDebug>
job_trigger::job_trigger(QObject *parent) :
    QObject(parent)
{
    timer=new QTimer(this);
    begtime =QDateTime::currentDateTime();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(start_job()));
    timer->start(1000);
}
void job_trigger::init()
{

}
void job_trigger::on_click_start_job(int jobnum)
{

}
void job_trigger::start_job()
{
    qDebug()<<"aa";
    emit show_job("a","a",1,1);
}

void job_trigger::load_job()
{

}


////////////////////////////
/// \brief The job class
///////////////////////////



job::job(QString name,QString cmd,int num,int sta)
{
    _name=name;
    _cmd_line=cmd;
    _job_num=num;
    _job_status=sta;
}

void job::run()
{
    _qp=new QProcess;
}

