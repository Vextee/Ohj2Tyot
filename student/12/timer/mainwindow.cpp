#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    ui->lcdNumberSec->setStyleSheet("background: #000090;");

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 0, 0));
    ui->lcdNumberMin->setPalette(palette);
    ui->lcdNumberMin->setAutoFillBackground(true);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_start_button_clicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::on_stop_button_clicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_reset_button_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_close_button_clicked);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_timeout()
{
    int current_mins = ui->lcdNumberMin->intValue();
    int current_secs = ui->lcdNumberSec->intValue();

    if (current_secs == 59)
    {
        ui->lcdNumberMin->display(current_mins+1);
        ui->lcdNumberSec->display(0);
    }
    else
    {
        ui->lcdNumberSec->display(current_secs+1);
    }
}

void MainWindow::on_start_button_clicked()
{
    timer->start(1000);
}

void MainWindow::on_stop_button_clicked()
{
    timer->stop();
}

void MainWindow::on_reset_button_clicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::on_close_button_clicked()
{
    close();
}
