#include "mainwindow.h"
#include "job_trigger.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");
    if(current_date>"2016-12-31")
    {
        QMessageBox::about(0,"本软件已过期","请联系兴证期货资管部续期");
        return 0;
    }

    MainWindow w;
    w.show();

    job_trigger * jt=new job_trigger;
    jt->init();

    QObject::connect(jt,&job_trigger::show_job,&w,&MainWindow::add_button);


    jt->load_job();

    return a.exec();
}

//涉及时间的trigger尚未完成 其余为锦上添花内容 可在有时间时处理


/*
job_trigger 如何完成任务
读取开始时间
读取任务列表及状态（展示状态）

接收到timer信号开始查询任务
    if nowt大于任务时间 and 开始时间大于任务时间 and 任务并未进行过 开始任务
接收到双击信号开始任务

新进程运行任务（展示状态）
运行结束返回运行结果（展示状态）

状态分类
    未运行过
    正在运行
    正常结束
    出现错误
*/



/*
任务以何种形式存放
1.默认位置存放每日任务
2.每日执行时新建c:/tmp/$date/ 在其中存放任务状态信息
3.初始化时读取任务信息 按时间读取并覆盖 仅出现错误状态信息有效
4.得到信息并展示

任务存放方法
默认方法 1###21：00：00="perl c:/code/1.pl"
运行时方法
    21：00：01###1###="perl c:/code/1.pl" begin
    21：00：02###1###="perl c:/code/1.pl" end
    21：00：03###1###="perl c:/code/1.pl" begin
    21：00：04###1###="perl c:/code/1.pl" error
*/
