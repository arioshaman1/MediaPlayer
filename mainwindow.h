#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QStyle>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   void openImage();
    void openAudio();
   void openVideo();


    void on_StartButton_clicked();

    void on_Volume_Control_valueChanged(int value);

    void on_PauseButton_clicked();

    void on_StopButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QVideoWidget *m_videoWidget;
};

#endif // MAINWINDOW_H
