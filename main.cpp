#include "mainwindow.h"
#include "job_trigger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    job_trigger * jt=new job_trigger;

    jt->init();
    jt->load_job();
    QObject::connect(jt,&job_trigger::show_job,&w,&MainWindow::add_button);


    w.show();
    return a.exec();
}

/*
mainwindow ���չʾ

����jobt���ź� ��̬���ɸ��Ӳ�չʾ ���ӵ�uniq ID����������к� �յ�double click�ź�ʱ���������кŵ�job_trigger
*/



/*
job_trigger ����������
��ȡ��ʼʱ��
��ȡ�����б�״̬��չʾ״̬��

���յ�timer�źſ�ʼ��ѯ����
    if nowt��������ʱ�� and ��ʼʱ���������ʱ�� and ����δ���й� ��ʼ����
���յ�˫���źſ�ʼ����

�½�����������չʾ״̬��
���н����������н����չʾ״̬��

״̬����
    δ���й�
    ��������
    ��������
    ���ִ���
*/



/*
�����Ժ�����ʽ���
1.Ĭ��λ�ô��ÿ������
2.ÿ��ִ��ʱ�½�c:/tmp/$date/ �����д������״̬��Ϣ
3.��ʼ��ʱ��ȡ������Ϣ ��ʱ���ȡ������ �����ִ���״̬��Ϣ��Ч
4.�õ���Ϣ��չʾ

�����ŷ���
Ĭ�Ϸ��� 1###21��00��00="perl c:/code/1.pl"
����ʱ����
    21��00��01###1###="perl c:/code/1.pl" begin
    21��00��02###1###="perl c:/code/1.pl" end
    21��00��03###1###="perl c:/code/1.pl" begin
    21��00��04###1###="perl c:/code/1.pl" error
*/
