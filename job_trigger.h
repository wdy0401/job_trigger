#ifndef JOB_TRIGGER_H
#define JOB_TRIGGER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <map>
#include <string>

#include "./q_button.h"
#include "mainwindow.h"

class job;
class job_trigger : public QObject
{
    Q_OBJECT
public:
    explicit job_trigger(QObject *parent = 0);
    void init();
    void load_job();
    void load_job(const QString & filename);

signals:
    void show_job(q_button *);

public slots:
    void start_job_ontime();

private:
    std::string job_name;
    std::string job_cmdline;
    int job_count;
    int job_status;
    QDateTime *job_time;

    QTimer * timer;
    QDateTime begtime;
    std::map<int,job*> job_map;
    std::map<int,q_button*> button_map;
};
class job : public QObject
{
        Q_OBJECT
public:
    job(const std::string & ,const std::string & ,int,int,QDateTime *);
    int get_status(){return _job_status;}
    QDateTime * get_time(){return _time;}


public slots:
    void stateChanged(QProcess::ProcessState newState);//开始运行时候被触发
    void finished(int exitCode, QProcess::ExitStatus exitStatus);//结束时被触发
    void run();

signals:
    void change_status(int);
private:
    std::string _name;
    std::string _cmd_line;
    int _job_num;
    int _job_status;//0：没跑过   1：正在跑   2：已结束   3：跑过有错误   4+ others 未定义
    QDateTime * _time;
    QProcess *_qp;
};

#endif // JOB_TRIGGER_H
