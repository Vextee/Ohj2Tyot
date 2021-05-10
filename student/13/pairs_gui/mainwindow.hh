/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <string>
#include <map>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Ajastin
    QTimer* timer;

private slots:
    // Nappien ja ajastinmen sloteja
    void handleCardClick();
    void handleCloseButtonClick();
    void handleTurnBackButtonClick();
    void handelResetButtonClick();
    void handleTimerTimeout();

private:
    Ui::MainWindow *ui;

    // Säiliöt, joissa säilytetään
    // nappuloita ja niiden kirjaimia
    std::vector<std::vector<char>> letters_g_board_;
    std::map<QPushButton*, QString> game_board_;
    std::string used_letters_;
    // Scenet johon korttipinot lisätään
    QGraphicsScene* scene1_;
    QGraphicsScene* scene2_;
    // Suorakulmioita, joita lisätään korttipinoon
    QGraphicsRectItem* rect11_;
    QGraphicsRectItem* rect12_;
    QGraphicsRectItem* rect21_;
    QGraphicsRectItem* rect22_;
    // Grid layout, johon kortit asettaan
    QGridLayout* grid_ = new QGridLayout();

    // Rivien ja sarakkeiden määrä
    // joka tulee muuttumaan riippuen
    // korttien määrästä
    unsigned int rows_ = 1;
    unsigned int columns_ = 1;
    // Vuorossa oleva pelaaja
    std::string player_in_turn_ = "P1";
    // Painetut napit ja niiden määrä
    unsigned int turned_cards_ = 0;
    std::vector<QPushButton*> pressed_buttons_;

    // Pelaajien pisteet
    unsigned int p1_points_ = 0;
    unsigned int p2_points_ = 0;

    // Korttien määrä
    // Voi muuttaa parilliseksi luvuksi
    // väliltä 2-32
    const unsigned int CARD_AMOUNT = 32;
    // Kirjaimet, joiden järjestys arvotaan
    const std::string letters = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPP";

    // Kortin leveys ja pituus
    const int CARD_BUTTON_WIDTH = 60;
    const int CARD_BUTTON_HEIGTH = 90;

    // Alustus funktiota
    void calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);
    void init_cards(const unsigned int& rows_, const unsigned int& columns_);
    void init_game_board(const unsigned int& rows_, const unsigned int& columns_);
    void init_graphics_views();

};
#endif // MAINWINDOW_HH
