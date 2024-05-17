#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this)),
    m_videoWidget(new QVideoWidget(this))


{
    ui->setupUi(this);

    connect(ui->openImageButton, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(ui->openAudioButton, &QPushButton::clicked, this, &MainWindow::openAudio);
    connect(ui->openVideoButton, &QPushButton::clicked, this, &MainWindow::openVideo);


    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(ui->Volume_Control->value());
    ui->StartButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->PauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->StopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        QPixmap image(fileName);
        ui->imageLabel->setPixmap(image);
        ui->imageLabel->setScaledContents(true);
    }


}
void MainWindow::openAudio()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Audio"), "", tr("Audio Files (*.mp3 *.wav *.ogg)"));
    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));
        QFileInfo fileInfo(fileName);
        ui->audio_title2->setText(fileInfo.fileName());
    }
}
void MainWindow::openVideo()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.mp4 *.avi *.mov *.mkv)"));
    if (!fileName.isEmpty()){
        m_videoWidget->setGeometry(ui->imageLabel->geometry());
        player->setVideoOutput(m_videoWidget);
        player->setSource(QUrl::fromLocalFile(fileName)); // Установить медиафайл для проигрывания
        QFileInfo fileInfo(fileName);
        ui->audio_title2->setText(fileInfo.fileName());
        m_videoWidget->show(); // Показать виджет видео
        player->play(); // Начать воспроизведение
    }
}

void MainWindow::on_StartButton_clicked()
{
    player->play();
}


void MainWindow::on_PauseButton_clicked()
{
    player->pause();
}

void MainWindow::on_Volume_Control_valueChanged(int value)
{
    double volumeLevel = static_cast<double>(value) / 100.0;
    audioOutput->setVolume(volumeLevel);
}



void MainWindow::on_StopButton_clicked()
{
    player->stop();
    m_videoWidget->hide();
}

