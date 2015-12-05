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
    int _job_status;//0��û�ܹ�   1��������   2���ѽ���   3���ܹ��д���
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
