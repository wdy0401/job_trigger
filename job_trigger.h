#ifndef JOB_TRIGGER_H
#define JOB_TRIGGER_H

#include <QObject>
#include <QString>
#include <QTimer>

class job_trigger : public QObject
{
    Q_OBJECT
public:
    explicit job_trigger(QObject *parent = 0);

signals:
    void show_job(const QString &,const QString &,int,int);//name,cmdline,number,job status

public slots:
    void on_click_start_job(int);
    void start_job();

private:
    void load_job();
    QTimer * timer;
};

#endif // JOB_TRIGGER_H
