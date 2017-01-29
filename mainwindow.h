#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "time.h"
#include "unistd.h" //para: sleep()
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   QTimer *relogio, *cronometro;
   double centCron, segCron, minCron, hrCron;

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_iniciarCronBt_clicked();

    void on_resetarCronBt_clicked();

    void on_continuarCronBt_clicked();

    void iniciarCronometro();

    void iniciarRelogio();

private:
    Ui::MainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
