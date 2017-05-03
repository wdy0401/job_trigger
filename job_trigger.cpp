#include "job_trigger.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDate>

#include<string>
using namespace std;

job_trigger::job_trigger(QObject *parent) :
    QObject(parent)
{

}
void job_trigger::init()
{
    timer=new QTimer(this);
    begtime =QDateTime::currentDateTime();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(start_job_ontime()));
    timer->start(1000);

    job_name="";
    job_cmdline="";
    job_status=0;
    job_time=nullptr;

    begtime=QDateTime::currentDateTime();
}
void job_trigger::start_job_ontime()
{

    if(QDate::currentDate().dayOfWeek() > 5)
    {
        return;
    }
    for(auto iter=job_map.begin();iter!=job_map.end();iter++)
    {
        if(iter->second->get_time()==nullptr)
        {
            continue;
        }
        if(begtime.msecsTo(*iter->second->get_time())>0
                && QDateTime::currentDateTime().msecsTo(*iter->second->get_time())<0
                && iter->second->get_status()==0)
        {
            iter->second->run();
        }
    }
}

void job_trigger::load_job(const QString & filename)
{
    QFile qf(filename);
    if(! qf.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream in(&qf);

    int nextday=0;
    while (!in.atEnd())
    {
        string _sep="=";
        string tmpstring = in.readLine().toStdString();
        unsigned int fp=tmpstring.find_first_of(_sep);
        string key=tmpstring.substr(0,fp);
        string value=tmpstring.substr(fp+1,tmpstring.size());

        if(tmpstring.size()==0 || tmpstring[0]=='#')//exclude empty line and line started with #
        {
            continue;
        }
        else if(tmpstring.substr(0,7)=="__END__" && tmpstring.size()==7)
        {
            key="end";
            value="";
        }
        else if(tmpstring.substr(0,9)=="__BEGIN__" && tmpstring.size()==9)
        {
            key="begin";
            value="";
        }
        else if(tmpstring.find(_sep)==string::npos)
        {
            continue;
        }

        if(key=="name")
        {
            job_name=value;
        }
        if(key=="cmdline")
        {
            job_cmdline=value;
        }
        if(key=="status")
        {
            job_status=int(atof(value.c_str()));
        }
        if(key=="time")
        {
           if(job_time==nullptr)
           {
               job_time=new QDateTime;
               (*job_time)=QDateTime::currentDateTime();
           }
           (*job_time)=QDateTime::fromString(job_time->toString("yyyy-MM-dd")+" "+value.c_str(), "yyyy-MM-dd hh:mm:ss");
        }
        if(key=="nextday")
        {
            if(job_time==nullptr)
            {
                job_time=new QDateTime;
                (*job_time)=QDateTime::currentDateTime();
            }
            (*job_time)=job_time->addDays(atoi(value.c_str()));
            nextday=int(atof(value.c_str()));
        }
        if(key=="begin")
        {
            job_name="";
            job_cmdline="";
            job_status=0;
            job_time=nullptr;
        }
        if(key=="end")
        {
            job_count++;

            job * new_job=new job(job_name,job_cmdline,job_count,job_status,job_time);
            job_map[job_count]=new_job;

            q_button * button = new q_button();
            string job_time_display=job_time->toString("hh:mm").toStdString();
            if(nextday>0)
            {
                job_time_display=job_time_display+"   next day "+to_string(nextday);
            }
            nextday=0;
            button->init(job_name,job_cmdline,job_count,job_status,job_time_display);

            button_map[job_count]=button;

            QObject::connect(button,&q_button::double_click,new_job,&job::run);
            QObject::connect(new_job,&job::change_status,button,&q_button::change_status);

            emit show_job(button);
        }
    }
    qf.close();
}
void job_trigger::load_job()
{
    load_job("c:/cfg/daily_job.txt");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///  The job class
///
///
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



job::job(const string & name,const string & cmd,int num,int sta,QDateTime *time)
{
    _name=name;
    _cmd_line=cmd;
    _job_num=num;
    _job_status=sta;
    _time=time;
    _qp=nullptr;
}

void job::run()
{
    if(_job_status==1)
    {
        return;
    }
    if(_qp!=nullptr)
    {
        delete _qp;
    }

    _qp=new QProcess;
    QObject::connect(_qp,&QProcess::stateChanged,this,&job::stateChanged);
    QObject::connect(
                        _qp,
                        static_cast<void (QProcess:: *)(int, QProcess::ExitStatus)>(&QProcess::finished),
                        this,
                        &job::finished
                     );
    _qp->start(_cmd_line.c_str());
}
void job::stateChanged(QProcess::ProcessState newState)
{
    switch (newState)
    {
        //case QProcess::Starting: cout << "Starting" << endl;{_job_status=1;emit change_status(_job_status);}; break;//not in status classification
        case QProcess::NotRunning:{_job_status=4;emit change_status(_job_status);} break;
        case QProcess::Running:{_job_status=1;emit change_status(_job_status);}; break;
        default: break;
    }
}
void job::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitCode==0 && exitStatus==QProcess::NormalExit)
    {
        _job_status=2;
    }
    else
    {
        _job_status=3;
    }
    emit change_status(_job_status);
}


