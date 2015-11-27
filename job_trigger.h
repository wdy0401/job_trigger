#ifndef JOB_TRIGGER_H
#define JOB_TRIGGER_H

#include <QObject>
#include <QString>
#include <Qtimer>

class job_trigger : public QObject
{
    Q_OBJECT
public:
    explicit job_trigger(QObject *parent = 0);

signals:
    void show_job(int,const QString &,int);//job number,        job name,       job status

public slots:
    void start_job(int);
    void start_job();

private:
    void load_job();
    QTimer timer;
};

#endif // JOB_TRIGGER_H
