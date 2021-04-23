#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::on_findPushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileLineEdit_editingFinished()
{
    file_name_ = ui->fileLineEdit->text();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    word_ = ui->keyLineEdit->text();
}

void MainWindow::on_findPushButton_clicked()
{
    on_fileLineEdit_editingFinished();
    on_keyLineEdit_editingFinished();
    bool found = false;
    std::ifstream file;
    file.open(file_name_.toStdString());
    if (!file.is_open())
    {
        ui->textBrowser->setText("File not found");
    }
    else
    {
        if (word_.length() == 0)
        {
            ui->textBrowser->setText("File found");
        }
        else
        {
            std::string line;
            std::string s_word= word_.toStdString();
            while(std::getline(file, line))
            {
                if (!ui->matchCheckBox->isChecked())
                {
                    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                    std::transform(s_word.begin(), s_word.end(), s_word.begin(), ::toupper);
                }
                if(line.find(s_word, 0) != std::string::npos)
                {
                    ui->textBrowser->setText("Word found");
                    found = true;
                }
            }
            if (!found)
            {
                ui->textBrowser->setText("Word not found");
            }
        }
    }
}
