#include "job_trigger.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include<string>
#include<iostream>
using namespace std;

job_trigger::job_trigger(QObject *parent) :
    QObject(parent)
{
    timer=new QTimer(this);
    begtime =QDateTime::currentDateTime();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(start_job_ontime()));
    timer->start(1000);
    job_count=0;
}
void job_trigger::init()
{

}
void job_trigger::on_click_start_job(int job_num)
{
   for(auto iter=job_map.begin();iter!=job_map.end();iter++)
   {
        //not tested yet
        if(iter->first==job_num)
        {
            iter->second->run();
            break;
        }
   }
}
void job_trigger::start_job_ontime()
{

}

void job_trigger::load_job(const QString & filename)
{


    QFile qf(filename);
    if(! qf.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream in(&qf);

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
        else if(tmpstring.find(_sep)==string::npos)
        {
            continue;
        }

        if(key=="name" || key=="end")
        {
            if(job_count==0)
            {
                job_name=value;
            }
            else
            {
                job * new_job=new job(job_name,job_cmdline,job_count,job_status);
                job_map[job_count]=new_job;

                q_button * button = new q_button();
                button->init(job_name,job_cmdline,job_count,job_status);
                emit show_job_1(button);
                button_map[job_count]=button;

                QObject::connect(button,&q_button::double_click,new_job,&job::run);
                QObject::connect(new_job,&job::change_status,button,&q_button::change_status);

                job_name=value;
                job_cmdline="";
                job_status=0;
            }
            job_count++;
            if(key=="end")
            {
                break;
            }
         }
        if(key=="cmd_line")
        {
            job_cmdline=value;
        }
        if(key=="status")
        {
            job_status=int(atof(value.c_str()));
        }
    }
    qf.close();
}
void job_trigger::load_job()
{
    load_job("c:/cfg/daily_job.txt");
}


////////////////////////////
///  The job class
///////////////////////////



job::job(const string & name,const string & cmd,int num,int sta)
{
    _name=name;
    _cmd_line=cmd;
    _job_num=num;
    _job_status=sta;
    _qp=nullptr;
}

void job::run()
{
    cerr <<"RunJob\t"<<_name<<endl;
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
    QObject::connect(_qp,
                     static_cast<void (QProcess:: *)(int, QProcess::ExitStatus)>(&QProcess::finished),this,&job::finished);
    _qp->start(_cmd_line.c_str());
}
void job::stateChanged(QProcess::ProcessState newState)
{
    switch (newState)
    {
        //case QProcess::Starting: cout << "Starting" << endl;{_job_status=1;emit change_status(_job_status);}; break;//这个不在状态分类中
        case QProcess::Running: cout << "Running" << endl;{_job_status=1;emit change_status(_job_status);}; break;
        //case QProcess::NotRunning: cout << "NotRunning" << endl;{_job_status=2;emit change_status(_job_status);} break;//这个与状态分类逻辑不一致
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


