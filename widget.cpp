#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>//文件对话框
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <qpainter.h>
#include <QMouseEvent>
#include "options.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


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

    //鼠标拖动





    //播放音乐
        //先new一个output对象
    audioOutput = new QAudioOutput(this);

        //添加一个媒体播放对象
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);


    //获取当前媒体时长 通过信号关联获取
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->endLable->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60));
        ui->PlayTime->setRange(0,duration);
    });

    //当前播放时长
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 pos){
        ui->startLable->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));
        //进度条
        ui->PlayTime->setValue(pos);
    });

    //拖动进度条
    connect(ui->PlayTime,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);
    audioOutput->setVolume(0.5);


    //图标
    QIcon startIcon(":/uiSource/start.png");
    ui->pushButton_7->setIcon(startIcon);
    ui->pushButton_2->setIcon(nextIcon);
    ui->pushButton_8->setIcon(lastIcon);

}

Widget::~Widget()
{
    delete ui;
}

//鼠标拖动
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint startPos = event->globalPos();
        m_offPos = startPos - geometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QPoint endPos = event->globalPos();
        move(endPos - m_offPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

//void Widget::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    painter.fillRect(this->rect().adjusted(10, 10, -10, -10), QColor(223, 223, 223));
//}
//切换下一首播放封装类
void Widget::getNextSong(){
    curPlayerIndex = (curPlayerIndex+1)%playList.size();
    ui->listWidget->setCurrentRow(curPlayerIndex);
    mediaPlayer->setSource(playList[curPlayerIndex]);
    mediaPlayer->play();
    ui->pushButton_7->setIcon(stopIcon);

}


void Widget::on_pushButton_clicked()
{
    auto path =  QFileDialog::getExistingDirectory(this,"选择音乐");
    //获取目录中所有mp3、wav文件
    QDir dir(path);
    QList musicList = dir.entryList(QStringList()<<"*.mp3" << "*.wav" << "*.m4a");
    //展示音乐列表,将音乐名字放到listwidget展示
    ui->listWidget->addItems(musicList);

    //默认选中第一个音乐
    ui->listWidget->setCurrentRow(0);

    //把音乐的完整路径保存
    for(auto file : musicList)
        playList.append(QUrl::fromLocalFile(path +"/"+ file));
}


void Widget::on_pushButton_7_clicked()
{
    switch(mediaPlayer->playbackState()){
        case QMediaPlayer::PlaybackState::StoppedState://停止
            {//播放音乐
        ui->pushButton_7->setIcon(startIcon);
                    //获取选中的行号
                curPlayerIndex = ui->listWidget->currentRow();
                if(curPlayerIndex != -1){
                    mediaPlayer->setSource(playList[curPlayerIndex]);
                    ui->pushButton_7->setIcon(stopIcon);
                    mediaPlayer->play();
                }else{
                    Widget::on_pushButton_clicked();
                }

            break;
            }
        case QMediaPlayer::PlaybackState::PausedState://暂停
            ui->pushButton_7->setIcon(stopIcon);
            //如果当前暂停，则继续播放
            mediaPlayer->play();
            break;
        case QMediaPlayer::PlaybackState::PlayingState://播放
            ui->pushButton_7->setIcon(startIcon);
            //如果正在播放，暂停音乐
            mediaPlayer->pause();
            break;
    }


}


void Widget::on_pushButton_2_clicked()
{
    curPlayerIndex = ui->listWidget->currentRow();
    //上一曲
    if(curPlayerIndex == -1){
            Widget::on_pushButton_clicked();

    }else{
            ui->pushButton_7->setIcon(stopIcon);
            curPlayerIndex = curPlayerIndex-1;
            if(curPlayerIndex < 0){
                curPlayerIndex=playList.size()-1;
            }
            ui->listWidget->setCurrentRow(curPlayerIndex);
            mediaPlayer->setSource(playList[curPlayerIndex]);
            mediaPlayer->play();
    }
}


void Widget::on_pushButton_8_clicked()
{
    ui->pushButton_7->setIcon(stopIcon);
    curPlayerIndex = ui->listWidget->currentRow();
    //下一曲
    if(curPlayerIndex == -1){
         Widget::on_pushButton_clicked();

    }else{
         getNextSong();
    }
}


void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    ui->pushButton_7->setIcon(stopIcon);
    curPlayerIndex = index.row();
    mediaPlayer->setSource(playList[curPlayerIndex]);
    mediaPlayer->play();
}


void Widget::on_close_clicked()
{
    this->close();
}



void Widget::on_min_clicked()
{
     Widget::showMinimized(); //最小化
}


void Widget::on_options_clicked()
{
     Options *opt = new Options(this);
     opt->show();
}

void Widget::setBackgroundImage(QString path){
     if(path != ""){
         ui->wg_bg->setStyleSheet("border-image:url("+path+");border-radius:15px;");
     }
}
void Widget::setPlaySongIcon(QString path){

     if(path != ""){
         startIcon = QIcon(path);
         ui->pushButton_7->setIcon(startIcon);
     }
}
void Widget::setPausedSongIcon(QString path){
     if(path !=""){
         stopIcon = QIcon(path);
         ui->pushButton_7->setIcon(stopIcon);
     }

}
void Widget::setNextSongIcon(QString path){
     if(path != ""){
         nextIcon = QIcon(path);
        ui->pushButton_8->setIcon(nextIcon);
     }
}
void Widget::setLastSongIcon(QString path){
     if(path != ""){
         lastIcon = QIcon(path);
        ui->pushButton_2->setIcon(lastIcon);
     }
}
