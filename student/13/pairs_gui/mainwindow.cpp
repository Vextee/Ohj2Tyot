#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <algorithm>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    unsigned int rows = 1;
    unsigned int columns = 1;

    ui->resetButton->setVisible(false);
    calculate_factors(rows, columns);
    init_cards(rows, columns);
    init_game_board(rows, columns);
    init_graphics_views();
    connect(ui->CloseButton, &QPushButton::clicked,
            this, &MainWindow::handleCloseButtonClick);
    connect(ui->TurnBackButton, &QPushButton::clicked,
            this, &MainWindow::handleTurnBackButtonClick);
    connect(ui->resetButton, &QPushButton::clicked,
            this, &MainWindow::handeResetButtonClick);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    for(unsigned int i = 1; i * i <= CARD_AMOUNT; ++i)
    {
        if(CARD_AMOUNT% i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = CARD_AMOUNT / smaller_factor;
}

void MainWindow::init_cards(const unsigned int& rows, const unsigned int& columns)
{
    used_letters_ = letters.substr(0,CARD_AMOUNT);
    random_shuffle(used_letters_.begin(), used_letters_.end());

    int counter = 0;

    for (unsigned int i = 0; i < rows; ++i)
    {
        std::vector<char> row = {};
        for (unsigned int j = 0; j < columns; ++j)
        {
            row.push_back(used_letters_.at(counter));
            ++counter;
        }
        letters_g_board_.push_back(row);
    }
}


void MainWindow::handleCardClick()
{
    if (turned_cards_ < 2)
    {
        QPushButton* pressed_button = static_cast<QPushButton*>(sender());
        pressed_button->setText(game_board_.at(pressed_button));
        pressed_buttons_.push_back(pressed_button);
        ++turned_cards_;
    }
}

void MainWindow::handleCloseButtonClick()
{
    close();
}

void MainWindow::handleTurnBackButtonClick()
{
    if (turned_cards_ == 2)
    {
        if (pressed_buttons_[0]->text() == pressed_buttons_[1]->text())
        {
            pressed_buttons_[0]->setVisible(false);
            pressed_buttons_[1]->setVisible(false);
            if (player_in_turn_ == "P1")
            {
                ++p1_points_;
                std::string points_str = std::to_string(p1_points_);
                QString points_qstr = QString::fromStdString("Player1: " + points_str);
                ui->P1PointsLabel->setText(points_qstr);
            }
            else
            {
                ++p2_points_;
                std::string points_str = std::to_string(p2_points_);
                QString points_qstr = QString::fromStdString("Player2: " + points_str);
                ui->P2PointsLabel->setText(points_qstr);
            }
        }
        else
        {
            if (player_in_turn_ == "P1")
            {
                player_in_turn_ = "P2";
                ui->CurrentTurnLabel->setText("Current turn: P2");
            }
            else
            {
                player_in_turn_ = "P1";
                ui->CurrentTurnLabel->setText("Current turn: P1");
            }
            pressed_buttons_[0]->setText("");
            pressed_buttons_[1]->setText("");

        }
        pressed_buttons_ = {};
        turned_cards_ = 0;
    }


    if (p1_points_ + p2_points_ == CARD_AMOUNT/2)
    {
        if (p1_points_ > p2_points_)
        {
            ui->winnerLabel->setText("Player1 has won!");
        }
        else if (p2_points_ > p1_points_)
        {
            ui->winnerLabel->setText("Player2 has won!");
        }
        else
        {
            ui->winnerLabel->setText("It's a Draw");
        }
        ui->resetButton->setVisible(true);

    }
}

void MainWindow::handeResetButtonClick()
{

}

void MainWindow::init_game_board(const unsigned int& rows, const unsigned int& columns)
{

    QGridLayout* grid = new QGridLayout;
    grid->setSpacing(20);
    ui->CardsGraphicsView->setLayout(grid);


    for (unsigned int r = 0; r < rows; ++r)
    {
        for (unsigned int c = 0; c < columns; ++c)
        {
            char letter = letters_g_board_[r][c];
            std::string letter_str;
            letter_str += letter;
            QString qstr = QString::fromStdString(letter_str);
            QPushButton* pushButton = new QPushButton(this);
            game_board_.insert({pushButton, qstr});
            pushButton->setFixedSize(CARD_BUTTON_WIDTH, CARD_BUTTON_HEIGTH);
            grid->addWidget(pushButton,r,c);
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handleCardClick);
        }
    }
}

void MainWindow::init_graphics_views()
{
    scene1_ = new QGraphicsScene(this);
    ui->P1CardGraphicsView->setScene(scene1_);

    scene2_ = new QGraphicsScene(this);
    ui->P2CardsGraphicsView->setScene(scene2_);
    /*QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    rect_ = scene_->addRect(100,0,80,100,blackPen,redBrush);*/

}


