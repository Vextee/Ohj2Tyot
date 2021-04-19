/* Class Person
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 *
 * Luokka kuvaa henkilöä, joka voi olla joko potilas tai
 * sairaalan henkilökunnan jäsen
 *
 * Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 * */

#ifndef PERSON_HH
#define PERSON_HH

#include "date.hh"
#include <string>
#include <map>
#include <vector>

class Person
{
public:
    // Oletus konstruktori
    Person();

    // Konstruktori id:n kanssa
    Person(const std::string& id);

    // Konstruktori id:n ja syntymäpäivän kanssa
    Person(const std::string& id, const std::string& date_of_birth);

    // Destruktori
    ~Person();

    // Hakija metodeja
    std::string get_id() const;
    std::vector<std::string> get_medicines() const;

    // Lisää lääkkeen henkilölle
    void add_medicine(const std::string& name,
                      unsigned int strength,
                      unsigned int dosage);

    // Poistaa lääkkeen henkilöltä
    void remove_medicine(const std::string& name);

    // Tulostaa henkilön id:n
    void print_id() const;

    // Tulostaa henkilön lääkkeet
    void print_medicines(const std::string& pre_text) const;

    // Vertailu operaattori
    bool operator<(const Person& rhs) const;



private:
    std::string id_;     // Voi olla nimi tai jokin muu identitaattori
    Date date_of_birth_; // Date luokkainen olio

    struct Prescription
    {
        unsigned int strength_;
        unsigned int dosage_;
    };
    // Lääkkeiden nimet ja niiden reseptit
    std::map<std::string, Prescription> medicines_;

};

#endif // PERSON_HH
