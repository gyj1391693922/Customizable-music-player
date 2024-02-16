#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件

private slots:
    void on_opt_close_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Options *ui;
    Widget *wid;

    QPoint m_offPos;//鼠标点击点与窗口左上角的距离

};

#endif // OPTIONS_H
