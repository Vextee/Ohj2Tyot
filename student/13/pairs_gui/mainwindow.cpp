#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QGridLayout>
#include <QPushButton>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    unsigned int rows = 1;
    unsigned int columns = 1;

    calculate_factors(rows, columns);
    //init_cards(rows, columns);
    init_game_board(rows, columns);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    for(unsigned int i = 1; i * i <= MAX_CARD_AMOUNT; ++i)
    {
        if(MAX_CARD_AMOUNT% i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = MAX_CARD_AMOUNT / smaller_factor;
}

void MainWindow::init_cards(const unsigned int& rows, const unsigned int& columns)
{
    used_letters_ = letters.substr(0,MAX_CARD_AMOUNT+2);
    random_shuffle(used_letters_.begin(), used_letters_.end());

    int counter = 0;

    for (unsigned int i = 0; i < rows; ++i)
    {
        std::vector<char> row = {};
        for (unsigned int j = 0; j < columns; ++j)
        {
            row.push_back(used_letters_.at(counter));
            counter++;
        }
        g_board_.push_back(row);
    }
}


void MainWindow::handleButtonClick()
{

}

void MainWindow::init_game_board(const unsigned int& rows, const unsigned int& columns)
{
    QWidget* central = new QWidget(this);
    QGridLayout* grid = new QGridLayout(central);

    for (unsigned int r = 0; r < rows; ++r)
    {
        for (unsigned int c = 0; c < columns; ++c)
        {
            QPushButton* pushButton = new QPushButton(this);
            pushButton->setFixedSize(CARD_BUTTON_WIDTH, CARD_BUTTON_HEIGTH);
            grid->addWidget(pushButton,r,c);
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handleButtonClick);
        }
    }
    setCentralWidget(central);
}



