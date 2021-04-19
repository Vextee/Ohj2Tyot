/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */
#include "person.hh"
#include <iostream>
#include <map>

// Alustaa luokan
Person::Person()
{
}

// Alustaa luokan henkilön id:n kanssa ja asettaa henkilön
// syntymäpäiväksi nykyisen päivämäärän
Person::Person(const std::string &id):
    id_(id)
{
    date_of_birth_ = Date();
}

// Alustaa luokan henkilön id:n ja syntymäpäivän kanssa
Person::Person(const std::string& id, const std::string& date_of_birth):
    id_(id), date_of_birth_(date_of_birth)
{
}


Person::~Person()
{
}

// Palauttaa henkilön id:n
std::string Person::get_id() const
{
    return id_;
}

// Palauttaa henkilölle määrätyt lääkkeet vectorissa
std::vector<std::string> Person::get_medicines() const
{
    std::vector<std::string> result;
    // Siirretään lääkkeet mapista vectoriin
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result.push_back(iter->first);
    }
    return result;
}

// Lisää henkilölle lääkkeen
void Person::add_medicine(const std::string& name,
                          unsigned int strength,
                          unsigned int dosage)
{
    Prescription pre;
    pre.strength_ = strength;
    pre.dosage_ = dosage;
    if( medicines_.find(name) != medicines_.end() )
    {
        medicines_.at(name) = pre;
    }
    else
    {
        medicines_.insert({name, pre});
    }
}

// Poistaa henkilöltä lääkkeen
void Person::remove_medicine(const std::string& name)
{
    medicines_.erase(name);
}

// Tulostaa henkilön id:n
void Person::print_id() const
{
    std::cout << id_;
}

// Tulostaa henkilölle määrätyt lääkkeet
void Person::print_medicines(const std::string& pre_text) const
{
    // Jos lääkkeitä ei ole yhtään tulostetaan None,
    // ja poistutaan funktiosta
    if( medicines_.empty() )
    {
        std::cout << " None" << std::endl;
        return;
    }
    std::cout << std::endl;
    // Käydään kaikki lääkkeet läpi ja tulostetaan niiden tiedot
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        std::cout << pre_text
                  << iter->first << " "
                  << iter->second.strength_ << " mg x "
                  << iter->second.dosage_ << std::endl;
    }
}

bool Person::operator<(const Person &rhs) const
{
    return id_ < rhs.id_;
}

