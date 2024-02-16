#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QAudioOutput;
class QMediaPlayer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void getNextSong();
    void setBackgroundImage(QString path);
    void setPlaySongIcon(QString path);
    void setPausedSongIcon(QString path);
    void setNextSongIcon(QString path);
    void setLastSongIcon(QString path);


protected:
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放事件

private slots:
    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_close_clicked();

    void on_min_clicked();

    void on_options_clicked();

private:
    Ui::Widget *ui;
    QList<QUrl> playList;   //播放列表
    int curPlayerIndex; //当前播放下标
    QAudioOutput* audioOutput;
    QMediaPlayer* mediaPlayer;
    QPoint m_offPos;//鼠标点击点与窗口左上角的距离
    QIcon startIcon = QIcon(":/uiSource/start.png");
    QIcon nextIcon = QIcon(":/uiSource/quick.png");
    QIcon lastIcon = QIcon(":/uiSource/back.png");
    QIcon stopIcon = QIcon(":/uiSource/stop.png");

};
#endif // WIDGET_H
