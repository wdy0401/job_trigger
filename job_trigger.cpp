#include "job_trigger.h"
#include <QDebug>
job_trigger::job_trigger(QObject *parent) :
    QObject(parent)
{
    timer=new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(start_job()));
    timer->start(1000);
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
