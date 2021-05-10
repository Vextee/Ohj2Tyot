/*Muistipeli gui
*
* Kuvaus:
*  Toteutettu ohjelma on muistipeli, jossa 2 pelaaja pyrkii löytämään
* maksimissaan 32 kortista kirjain pareja. Korttien määrää voi kuitenkin
* muuttaa muuttaa mihin tahansa muuhun pienempään parilliseen lukuun,
* muuttamalla vakiomuuttujan CARD_AMOUNT arvoa.
*  Pelaaja painaa kahta laudalla olevaa korttia jolloin kortit kääntyvät
* ja niiden kirjain tulee näkyviin. Tämän jälkeen pelaaja painaa
* "Turn back" nappia, jolloin kortin kirjain menee takaisin piiloon,
* jos kortit eivät olleet pari tai kortit lähtevät laudalta, jos kortit olivat pari.
* Jos pelaaja löytää vuorollaan parin, hän saa pisteen ja voi jatkaa vuoroaan
* ja yrittää löytää toisen parin. Vuoro vaihtuu, kun pelaaja ei löydä paria
*  Peli loppuu kun kaikki parit on löydetty pelilaudalta ja pelilauta on tyhjä.
* Pelin voittaja on se pelaaja, jolla on pelin lopuksi eniten korttipareja.
* Jos molemmilla pelaajilla on yhtä paljon pisteitä, peli on tasapeli.
*
* Ohjelman kirjoittaja
* Nimi: Veikko Svanstrom
* Opiskelijanumero: 50149539
* Käyttäjätunnus: scvesv
* E-Mail: veikko.svanstrom@tuni.fi
*/



#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <algorithm>



// Kostruktori
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Piilotetaan reset button
    ui->resetButton->setVisible(false);
    // Alustetaan taulukko johon korit asetetaan
    grid_->setSpacing(20);
    ui->cardsGraphicsView->setLayout(grid_);

    // Lasketaan suurin yhteinen tekijä korttien määrästä
    // ja alustetaan kortit, pelilauta ja korttipinkoille
    // tarkoitetut graphics view:t
    calculate_factors(rows_, columns_);
    init_cards(rows_, columns_);
    init_game_board(rows_, columns_);
    init_graphics_views();

    // Yhdistetään kaikkien nappien signaalit
    // niille kuuluviin sloteihin
    connect(ui->closeButton, &QPushButton::clicked,
            this, &MainWindow::handleCloseButtonClick);
    connect(ui->turnBackButton, &QPushButton::clicked,
            this, &MainWindow::handleTurnBackButtonClick);
    connect(ui->resetButton, &QPushButton::clicked,
            this, &MainWindow::handelResetButtonClick);
    // Yhdistetään myös ajastimen timeout signaalin sen slotiin
    connect(timer, &QTimer::timeout, this, &MainWindow::handleTimerTimeout);

    // Aloitetaan ajastin
    timer->start(1000);

}

// Destruktori
MainWindow::~MainWindow()
{
    delete ui;
    delete grid_;
}

// Käsittelee kortin painalluksen
void MainWindow::handleCardClick()
{
    // Etsitään painettu nappi
    QPushButton* pressed_button = static_cast<QPushButton*>(sender());
    // Jos käännettyjä kortteja on vähemmän kuin 2,
    // käännetään kortti
    if (turned_cards_ < 2)
    {
        // Näytetään kortin kirjain
        pressed_button->setText(game_board_.at(pressed_button));
        // Lisätään kortti painettuihin nappeihin
        pressed_buttons_.push_back(pressed_button);
        ++turned_cards_;

        // Asetetaan nappi pois käytöstä,
        // jotta sitä ei voida painaa uudelleen
        // ja muutetaan sen väriä
        pressed_button->setDisabled(true);
        pressed_button->setStyleSheet("background-color: grey");

    }
}

// Käsittelee close napin painalluksen
void MainWindow::handleCloseButtonClick()
{
    // Sulkee ohjelman
    close();
}

// Käsittelee turn back napin painalluksen
void MainWindow::handleTurnBackButtonClick()
{
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    // Jos käännettyjen korttien määrä ei ole 2,
    // ei tehdä mitään
    if (turned_cards_ == 2)
    {
        // Jos korttien tekstit ovat samat, kortit ovat pari
        if (pressed_buttons_[0]->text() == pressed_buttons_[1]->text())
        {
            // Piilotettaan kortit
            pressed_buttons_[0]->setVisible(false);
            pressed_buttons_[1]->setVisible(false);
            // Annetaan pisteet vuorossa olevalle pelaajalle ja
            // lisätää kortti heidän korttpinoonsa
            if (player_in_turn_ == "P1")
            {
                ++p1_points_;
                std::string points_str = std::to_string(p1_points_);
                QString points_qstr = QString::fromStdString("Player1: " + points_str);
                ui->p1PointsLabel->setText(points_qstr);
                rect11_ = scene1_->addRect(100,0+10*(p1_points_-1),100,5,blackPen,redBrush);
                rect12_ = scene1_->addRect(100,5+10*(p1_points_-1),100,5,blackPen,redBrush);
            }
            else
            {
                ++p2_points_;
                std::string points_str = std::to_string(p2_points_);
                QString points_qstr = QString::fromStdString("Player2: " + points_str);
                ui->p2PointsLabel->setText(points_qstr);
                rect21_ = scene2_->addRect(100,0+10*(p2_points_-1),100,5,blackPen,redBrush);
                rect22_ = scene2_->addRect(100,5+10*(p2_points_-1),100,5,blackPen,redBrush);
            }
        }
        // jos kortit olivat eri,
        // vaihdetaan vuoroa
        else
        {
            if (player_in_turn_ == "P1")
            {
                player_in_turn_ = "P2";
                ui->currentTurnLabel->setText("Current turn: P2");
            }
            else
            {
                player_in_turn_ = "P1";
                ui->currentTurnLabel->setText("Current turn: P1");
            }
            // Käännetään kortit takaisin
            // eli tehdään niistä samanlaisia kuin
            // pelin alussa
            pressed_buttons_[0]->setText("");
            pressed_buttons_[1]->setText("");
            pressed_buttons_[0]->setEnabled(true);
            pressed_buttons_[1]->setEnabled(true);
            pressed_buttons_[0]->setStyleSheet("background-color: red");
            pressed_buttons_[1]->setStyleSheet("background-color: red");

        }
        // Tyhjennetään muuttujat seuraavaa vuoroa varten
        pressed_buttons_ = {};
        turned_cards_ = 0;
    }

    // Tarkistetaan onko peli loppunut
    if (p1_points_ + p2_points_ == CARD_AMOUNT/2)
    {
        // Jos peli on loppunut, tulostetaan oikea ilmoitus
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
        // Lopuksi tuodaan reset nappi näkyviin
        // ja pysäytetään ajastin
        ui->resetButton->setVisible(true);
        timer->stop();

    }
}

// Käsittelee reset napin painalluksen
void MainWindow::handelResetButtonClick()
{
    // Poistetaan vanhat kortit
    for (auto card : game_board_)
    {
        if (game_board_.size() > 0)
        {
            grid_->removeWidget(card.first);
            delete card.first;
        }

    }
    // Tyhjennetään säiliöt
    game_board_.clear();
    letters_g_board_.clear();
    // Alustetaan kortit ja pelilauta uudelleen
    init_cards(rows_, columns_);
    init_game_board(rows_, columns_);
    // Asetetaan kaikki pelin alkutilanteeseen
    ui->resetButton->setVisible(false);
    ui->winnerLabel->setText("");
    ui->p1PointsLabel->setText("Player1: 0");
    ui->p2PointsLabel->setText("Player2: 0");
    ui->currentTurnLabel->setText("Current turn: P1");
    p1_points_ = 0;
    p2_points_ = 0;
    player_in_turn_ = "P1";
    // Tyhjennetään scenet korttipinoista
    scene1_->clear();
    scene2_->clear();

    // Aloitetaan ajastin alusta
    timer->start(1000);
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

}

// Käsittelee ajastimen timeoutin
void MainWindow::handleTimerTimeout()
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

// Laskee luvun suurimmat yhteiset tekijät
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

// Alustaa kortit eli arpoo satunnaisen järjestyksen niille
// ja lisää ne vektorin sisäiseen vektoriin
// omalle riville ja sarakkeelle
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

// Alustaa pelilaudan korteilla eli painonappuloilla
void MainWindow::init_game_board(const unsigned int& rows, const unsigned int& columns)
{
    // Käy läpi kaikki rivit ja sarakkeet
    for (unsigned int r = 0; r < rows; ++r)
    {
        for (unsigned int c = 0; c < columns; ++c)
        {
            // Etsii kirjaimen kyseisestä kohdasta
            char letter = letters_g_board_[r][c];
            std::string letter_str;
            letter_str += letter;
            QString qstr = QString::fromStdString(letter_str);
            QPushButton* pushButton = new QPushButton(this);
            pushButton->setStyleSheet("background-color: red");
            // Lisää kortin eli painonappulan
            //ja sille kuuluvan kirjaimen pelilaudalle
            game_board_.insert({pushButton, qstr});
            pushButton->setFixedSize(CARD_BUTTON_WIDTH, CARD_BUTTON_HEIGTH);
            // Lisää painonapin taulukkoon omalle paikalleen
            grid_->addWidget(pushButton,r,c);
            // Yhdistää painonapin painallus signaalin
            // sen slotiin
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handleCardClick);
        }
    }
}

// Alustaa scenet ja graphics view:t
void MainWindow::init_graphics_views()
{
    scene1_ = new QGraphicsScene(this);
    ui->p1CardGraphicsView->setScene(scene1_);

    scene2_ = new QGraphicsScene(this);
    ui->p2CardsGraphicsView->setScene(scene2_);

}


