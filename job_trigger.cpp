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
//    qDebug()<<"aa";
    static int abc=0;
    static string name="a";
    static string cmd="b";
    if(abc>5){return;}
//    q_button * bt=new q_button;
//    bt->init("name","cmd",1,0);

//    emit show_job_1(bt);



    abc++;
    name=name+"a";
    cmd=cmd+"b";
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
        if(tmpstring.substr(0,7)=="__END__" && tmpstring.size()==7)
        {
            cout<<"break"<<tmpstring<<endl;
            break;
        }
        if(tmpstring.find(_sep)==string::npos)
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



                job_name=value;
                job_cmdline="";
                job_status=0;
            }
            job_count++;
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
/// \brief The job class
///////////////////////////



job::job(const string & name,const string & cmd,int num,int sta)
{
    _name=name;
    _cmd_line=cmd;
    _job_num=num;
    _job_status=sta;
}

void job::run()
{
    _qp=new QProcess;
    _qp->start(_cmd_line.c_str());
}
void job::stateChanged(QProcess::ProcessState newState)
{
//    if(newState ==        NotRunning,
//            Starting,
//            Running)

    switch (newState)
    {
        case QProcess::NotRunning: cout << "NotRunning" << endl; break;
        case QProcess::Starting: cout << "Starting" << endl; break;
        case QProcess::Running: cout << "Running" << endl; break;
        default: break;
    }
            //,  NotRunning,
        //Starting,
        //Running)

}


