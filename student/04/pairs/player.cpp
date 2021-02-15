/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#include "player.hh"
#include<iostream>

// Alustetaan luokka
Player::Player(const std::string &name):
name_(name), numb_of_pairs_(0)
{

}

// Palauttaa pelaajan nimen
std::string Player::get_name() const
{
    return name_;
}

// Palauttaa pelaajan keräämien parien määrän
unsigned int Player::number_of_pairs() const
{
    return numb_of_pairs_;
}

// Lisää pelaajalle yhden parin ja poistaa kortin pelilaudalta
void Player::add_card(Card &card)
{
    numb_of_pairs_ += 1;
    card.remove_from_game_board();
}

// Tulostaa pelaajan tiedot
void Player::print() const
{
    std::cout << "*** " << name_ << " has " << numb_of_pairs_ << " pair(s)." << std::endl;
}
