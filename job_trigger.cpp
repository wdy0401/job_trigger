#include "job_trigger.h"
#include <QDebug>
#include<QMessageBox>
#include <QFile>

#include<string>
#include<iostream>
using namespace std;

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
void job_trigger::on_click_start_job(int job_num)
{
   for(auto iter=job_map.begin();iter!=job_map.end();iter++)
   {
//          未经测试的功能
//        if(iter->first==job_num)
//        {
//            iter->second->run();
//            break;
//        }
   }
}
void job_trigger::start_job()
{
    qDebug()<<"aa";
    emit show_job("a","a",1,1);
}

void job_trigger::load_job(const QString & filename)
{
    QFile qf(filename);
    if(! qf.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream in(&qf);
    string name="";
    string cmd_line="";
    int sta=0;

    while (!in.atEnd())
    {
        string _sep="=";
        string tmpstring = in.readLine().toStdString();
        unsigned int fp=tmpstring.find_first_of(_sep);
        string key=tmpstring.substr(0,fp);
        string value=tmpstring.substr(fp+1,tmpstring.size());

        if(tmpstring.size()==0 || tmpstring[0]=='#')//排除空行和#开头的注释行
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

//          得想个简单的办法
//        if(key=="name")
//        {
//            if(cmd_line=="")
//            {
//                if(name=="")//第一个name
//                {
//                    name=value;
//                    continue;
//                }
//                else//前一个name没有cmd_line
//                {

//                }
//            }
//            else //有前一个cmd_line
//            {
//                if(name=="")
//                {
//                    QString msg="cmd_line without name\t";
//                    msg=msg+QString::fromStdString(value);
//                    QMessageBox::warning(nullptr, "warning",msg);
//                }
//                int count=1+job_map.size();
//                job * new_job=new job(name,cmd_line,count,sta);
//                job_map[count]=new_job;
//                name="";
//                cmd_line="";
//                sta=0;
//            }
//         }
//        if(key=="cmd_line")
//        {
//            if(name=="")
//            {
//                QString msg="cmd_line without name\t";
//                msg=msg+QString::fromStdString(value);
//                QMessageBox::warning(nullptr, "warning",msg);
//            }
//            else
//            {
//                cmd_line=value;
//            }
//            break;
//        }
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
}

