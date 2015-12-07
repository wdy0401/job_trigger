#ifndef Q_BUTTON_H
#define Q_BUTTON_H

#include <QPushButton>
#include <QMouseEvent>

#include <string>

class q_button : public QPushButton
{
    Q_OBJECT
public:
    explicit q_button(QObject *parent = 0);
    void init(const std::string & ,const std::string & ,int,int);

signals:

public slots:

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    std::string _name;
    std::string _cmd ;
    int _number;
    int _status;

    bool display_cmd;

};

#endif // Q_BUTTON_H
