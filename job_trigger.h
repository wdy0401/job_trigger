#ifndef JOB_TRIGGER_H
#define JOB_TRIGGER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <map>
#include <string>
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
    void show_job(const std::string &,const std::string & ,int,int);//name,cmdline,number,job status

public slots:
    void on_click_start_job(int);
    void start_job();

private:
    QTimer * timer;
    QDateTime begtime;
    std::map<int,job*> job_map;
};
class job
{
public:
    job(const std::string & ,const std::string & ,int,int);
    void run();
    int get_status();
private:
    std::string _name;
    std::string _cmd_line;
    int _job_num;
    int _job_status;//0：没跑过   1：正在跑   2：已结束   3：跑过有错误
    QProcess *_qp;
};

#endif // JOB_TRIGGER_H

/* job_triger

    待添加内容
        load txt文档以得到任务信息
        在click时运行对应任务
        在时间恰当时运行对应任务

*/

/* job

    待添加内容
        在不同进程运行任务
        在任务 进行 完成 出错 时改变_job_status
*/
