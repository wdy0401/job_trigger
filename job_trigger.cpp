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
//        not tested yet
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
    static int abc=1;
    abc++;
    static string name="a";
    name=name+"a";
    static string cmd="b";
    cmd=cmd+"b";
    emit show_job(name,cmd,1,abc%4);
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

//          a simply way is needed
//        if(key=="name")
//        {
//            if(cmd_line=="")
//            {
//                if(name=="")//the first name
//                {
//                    name=value;
//                    continue;
//                }
//                else//no cmd_line in pre name
//                {

//                }
//            }
//            else //name with cmd_line ahead
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

