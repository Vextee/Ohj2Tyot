#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::on_countButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_closeButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    weight_ = ui->weightLineEdit->text();
}

void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weight_ = arg1;
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    height_ = ui->heightLineEdit->text();
}

void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    height_ = arg1;
}

void MainWindow::on_countButton_clicked()
{
    double weight = weight_.toDouble();
    double height = height_.toDouble()/100;
    double bmi = weight/(height*height);
    QString result = QString::number(bmi);
    ui->resultLabel->setText(result);
    if (bmi < 18.5)
    {
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if (bmi > 25.0)
    {
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else
    {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

void MainWindow::on_closeButton_clicked()
{
    close();
}
