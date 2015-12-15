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
    void show_job_1(q_button *);

public slots:
    void on_click_start_job(int);
    void start_job_ontime();

private:
    std::string job_name;
    std::string job_cmdline;
    int job_count;
    int job_status;
    QTimer * timer;
    QDateTime begtime;
    std::map<int,job*> job_map;
    std::map<int,q_button*> button_map;
};
class job : public QObject
{
        Q_OBJECT
public:
    job(const std::string & ,const std::string & ,int,int);
    int get_status();

public slots:
    void stateChanged(QProcess::ProcessState newState);//��ʼ����ʱ�򱻴���
    void finished(int exitCode, QProcess::ExitStatus exitStatus);//����ʱ������
    void run();

signals:
    void change_status(int);
private:
    std::string _name;
    std::string _cmd_line;
    int _job_num;
    int _job_status;//0��û�ܹ�   1��������   2���ѽ���   3���ܹ��д���   4+ others δ����
    QProcess *_qp;
};

#endif // JOB_TRIGGER_H

/* job_triger

    ���������
        load txt�ĵ��Եõ�������Ϣ
        ��clickʱ���ж�Ӧ����
        ��ʱ��ǡ��ʱ���ж�Ӧ����

*/

/* job

    ���������
        �ڲ�ͬ������������
        ������ ���� ��� ���� ʱ�ı�_job_status
*/
