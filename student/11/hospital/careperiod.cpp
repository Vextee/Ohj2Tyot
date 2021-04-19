/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#include "careperiod.hh"
#include <iostream>
#include <algorithm>

// Alustetaan hoitojakso, kun alkuaika on merkkijono
CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

// Alustetaan hoitojakso, kun alkuaika on Date luokkainen olio
CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

// Tulostaa hoitojakson alku- ja loppupäivämäärän
void CarePeriod::print_care_period()
{
    start_.print();
    std::cout << " - ";
    // jos loppupäivämäärä on ns. oletusasennossa
    // eli päivämäärä on 0.0.0, loppupäivämäärä ei tulosteta
    if (!end_.is_default())
    {
        end_.print();
    }

}

// Sijoittaa loppupäivämäärksi parametriksi annetun päivämäärän
void CarePeriod::set_end_date(const Date& end)
{
    end_ = end;
}

// Lisää hoitojaksolle henkilökuntaa
void CarePeriod::add_staff(const std::string staff_member)
{
    bool found = false;
    for (std::string s : staff_)
    {
        if (s == staff_member)
        {
            found = true;
        }
    }
    // Lisää henkilökunnan jäsenen vain, jos hän ei ole
    // jo valmiiksi hoitojaksolla
    if (!found)
    {
        staff_.push_back(staff_member);
    }

}

// Tulostaa henkilökunnan jäsenet, jotka työskentelevät hoitojaksolla
void CarePeriod::print_staff()
{
    // Jos henkilökunnan jäseniä ei ole yhtään tulostetaan None
    if (staff_.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
    // Muuten käydään läpi henkilökunta akkosjärjestyksessä ja tulostetaan
    else
    {
        sort(staff_.begin(), staff_.end());
        for (std::string s : staff_)
        {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
}

// Palauttaa potilaan id:n
std::string CarePeriod::get_patient()
{
    return patient_->get_id();
}

// Palauttaa henkilökunta vektorin
std::vector<std::string> CarePeriod::get_staff()
{
    return staff_;
}


