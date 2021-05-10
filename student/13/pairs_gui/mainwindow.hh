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
    void handleCardClick();
    void handleCloseButtonClick();
    void handleTurnBackButtonClick();
    void handeResetButtonClick();

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<char>> letters_g_board_;
    std::map<QPushButton*, QString> game_board_;
    std::string used_letters_;
    QGraphicsScene* scene1_;
    QGraphicsScene* scene2_;

    std::string player_in_turn_ = "P1";
    unsigned int turned_cards_ = 0;
    std::vector<QPushButton*> pressed_buttons_;

    unsigned int p1_points_ = 0;
    unsigned int p2_points_ = 0;

    const unsigned int CARD_AMOUNT = 12;
    const std::string letters = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPP";

    const int CARD_BUTTON_WIDTH = 60;
    const int CARD_BUTTON_HEIGTH = 90;

    void calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);
    void init_cards(const unsigned int& rows, const unsigned int& columns);
    void init_game_board(const unsigned int& rows, const unsigned int& columns);
    void init_graphics_views();

};
#endif // MAINWINDOW_HH
