/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#include "card.hh"
#include <iostream>

// Alustetaan card luokka ilman merkkiä ja merkitään sen tyhjäksi
Card::Card():
    letter_(EMPTY_CHAR), visibility_(EMPTY)
{

}

// Alustetaan card luokka ja täytetään se
// jollakin merkillä ja setetaan se piilotetuksi
Card::Card(const char c):
    letter_(c), visibility_(HIDDEN)
{

}

// Asetetaan korttiin jokin merkki
void Card::set_letter(const char c)
{
    letter_ = c;
}

// Asetetaan kortille jokin näkyvyys
void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

// Palautetaan kortissa oleva kirjain
char Card::get_letter() const
{
    return letter_;
}

// Palautetaan mitä näkyvyyttä kortti on
Visibility_type Card::get_visibility() const
{
    return visibility_;
}

// Käännetään kortti eli vaihdetaan sen näkyvyyttä
void Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;
    }
    else if(visibility_ == EMPTY)
    {
        std::cout << "Cannot turn an empty place." << std::endl;
    }
}

// Tulostetaan joko kortin merkki, piilotettu merkki tai tyhjä merkki
void Card::print() const
{
    if (visibility_ == OPEN)
    {
        std::cout << letter_;
    }
    else if (visibility_ == HIDDEN)
    {
        std::cout << HIDDEN_CHAR;
    }
    else
    {
        std::cout << EMPTY_CHAR;
    }

}

// Poistaa kortin pelilaudalta eli muuttaa sen näkyvyyden tyhjäksi
void Card::remove_from_game_board()
{
    visibility_ = EMPTY;
}
