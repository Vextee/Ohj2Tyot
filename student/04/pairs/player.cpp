/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#include "player.hh"
#include<iostream>


Player::Player(const std::string &name):
name_(name), numb_of_pairs_(0)
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return numb_of_pairs_;
}

void Player::add_card(Card &card)
{
    numb_of_pairs_ += 1;
    card.remove_from_game_board();
}

void Player::print() const
{
    std::cout << "*** " << name_ << " has " << numb_of_pairs_ << " pair(s)." << std::endl;
}
