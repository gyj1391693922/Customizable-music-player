#include "options.h"
#include "ui_options.h"
#include <QGraphicsDropShadowEffect>
#include "widget.h"
#include <QMouseEvent>
#include <QFileDialog>//文件对话框

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    wid = (Widget *)parentWidget();

    //设置窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    //设置阴影边框;
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(ui->wg_bg);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(140, 140, 140));
    shadow->setBlurRadius(8);
    ui->wg_bg->setGraphicsEffect(shadow);
}

Options::~Options()
{
    delete ui;
}

//鼠标拖动
void Options::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint startPos = event->globalPos();
        m_offPos = startPos - geometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void Options::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QPoint endPos = event->globalPos();
        move(endPos - m_offPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Options::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}


void Options::on_opt_close_clicked()
{
    this->close();
}


void Options::on_pushButton_clicked()
{
    QString ImagePath = QFileDialog::getOpenFileName(this, "选择背景图片", "", "Images (*.png *.jpg *.jpeg)");
    wid->setBackgroundImage(ImagePath);
}


void Options::on_pushButton_2_clicked()
{
    QString IconPath = QFileDialog::getOpenFileName(this, "选择图标", "", "Images (*.png *.jpg *.jpeg)");
    wid->setPlaySongIcon(IconPath);
}


void Options::on_pushButton_4_clicked()
{
    QString IconPath = QFileDialog::getOpenFileName(this, "选择图标", "", "Images (*.png *.jpg *.jpeg)");
    wid->setNextSongIcon(IconPath);
}


void Options::on_pushButton_5_clicked()
{
    QString IconPath = QFileDialog::getOpenFileName(this, "选择图标", "", "Images (*.png *.jpg *.jpeg)");
    wid->setLastSongIcon(IconPath);
}

