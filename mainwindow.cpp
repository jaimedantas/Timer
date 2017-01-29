#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->continuarCronBt->setVisible(false);

    this->relogio = new QTimer(this);
    this->cronometro = new QTimer(this);
    this->cronometro->setInterval(20);
    connect(this->cronometro, SIGNAL(timeout()), this, SLOT(iniciarCronometro()));

    connect(this->relogio, SIGNAL(timeout()), this, SLOT(iniciarRelogio()));
    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->relogio->start(1000);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate d = date;

    struct tm dia_nasc = {0};
    dia_nasc.tm_hour = 0;
    dia_nasc.tm_min = 0;
    dia_nasc.tm_sec = 0;

    dia_nasc.tm_mday = d.day();
    dia_nasc.tm_mon = d.month() - 1;
    dia_nasc.tm_year = d.year() - 1900;

    time_t hoje;
    time(&hoje);

    double segundos = difftime(hoje, mktime(&dia_nasc));

    ui->lcdSegundosLabel->display(segundos);
}

void MainWindow::on_iniciarCronBt_clicked()
{
    if(ui->iniciarCronBt->text() == "Iniciar"){
        ui->iniciarCronBt->setText("Parar");
        ui->continuarCronBt->setVisible(true);

        //iniciar cronometro
        this->centCron = 0;
        this->segCron = 0;
        this->minCron = 0;
        this->hrCron = 0;

        this->cronometro->start();
    }
    else{
        //parar cronometro
        this->cronometro->stop();
    }
}

void MainWindow::on_resetarCronBt_clicked()
{
    ui->iniciarCronBt->setText("Iniciar");
    ui->continuarCronBt->setVisible(false);

    //parar e resetar cronometro
    this->cronometro->stop();

    this->centCron = 0;
    this->segCron = 0;
    this->minCron = 0;
    this->hrCron = 0;

    ui->cronometro_cent->display(this->centCron);
    ui->cronometro_seg->display(this->segCron);
    ui->cronometro_min->display(this->minCron);
    ui->cronometro_hr->display(this->hrCron);
}

void MainWindow::on_continuarCronBt_clicked()
{
    //continuar cronometro
    this->cronometro->start();
}

void MainWindow::iniciarCronometro()
{
   if(this->centCron == 1000)
   {
      this->centCron = 0;
      this->segCron += 1;
   }

   if(this->segCron > 60)
   {
       this->segCron = 0;
       this->minCron += 1;
   }

   if(this->minCron > 60)
   {
       this->minCron = 0;
       this->hrCron += 1;
   }

    ui->cronometro_cent->display(this->centCron);
    ui->cronometro_seg->display(this->segCron);
    ui->cronometro_min->display(this->minCron);
    ui->cronometro_hr->display(this->hrCron);

    this->centCron += 20;
}

void MainWindow::iniciarRelogio()
{
    struct tm *tm_ptr;
    time_t  hoje;
    time(&hoje);

    tm_ptr = localtime(&hoje);

    double hr = tm_ptr->tm_hour;
    double min = tm_ptr->tm_min;
    double sec = tm_ptr->tm_sec;

    ui->hora_atual_hr->display(hr);
    ui->hora_atual_min->display(min);
    ui->hora_atual_sec->display(sec);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[3] = {
          QPoint(7, 8),
          QPoint(-7, 8),
          QPoint(0, -40)
      };
      static const QPoint minuteHand[3] = {
          QPoint(7, 8),
          QPoint(-7, 8),
          QPoint(0, -70)
      };

      QColor hourColor(153, 0, 153);
      QColor minuteColor(255, 0, 255,191);

      int side = qMin(width(), height());
      QTime time = QTime::currentTime();



      QPainter painter(this);

      painter.setRenderHint(QPainter::Antialiasing);

      painter.translate(width() / 1.6, height() / 1.75);

      painter.scale(side / 600.0, side / 600.0);



      painter.setPen(Qt::NoPen);

      painter.setBrush(hourColor);



      painter.save();

      painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
      painter.drawConvexPolygon(hourHand, 3);
      painter.restore();



      painter.setPen(hourColor);


      for (int i = 0; i < 12; ++i) {
          painter.drawLine(88, 0, 96, 0);
          painter.rotate(30.0);
      }



      painter.setPen(Qt::NoPen);

      painter.setBrush(minuteColor);


      painter.save();
      painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
      painter.drawConvexPolygon(minuteHand, 3);
      painter.restore();



      painter.setPen(minuteColor);



      for (int j = 0; j < 60; ++j) {
          if ((j % 5) != 0)
              painter.drawLine(92, 0, 96, 0);
          painter.rotate(6.0);
      }

  }

