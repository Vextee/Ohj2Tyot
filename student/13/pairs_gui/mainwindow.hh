#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <string>

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

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<char>> g_board_;
    std::string used_letters_;

    std::string player_in_turn_ = "P1";
    unsigned int turned_cards_ = 0;

    const unsigned int MAX_CARD_AMOUNT = 16;
    const std::string letters = "AABBCCDDEEFFGGHHIIJJ";

    const int CARD_BUTTON_WIDTH = 60;
    const int CARD_BUTTON_HEIGTH = 90;

    void calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor);
    void init_cards(const unsigned int& rows, const unsigned int& columns);
    void init_game_board(const unsigned int& rows, const unsigned int& columns);

};
#endif // MAINWINDOW_HH
