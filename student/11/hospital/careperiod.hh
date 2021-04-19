/* Luokka: CarePeriod
 * ----------
 * COMP.CS.110 KEVAT 2021
 * ----------
 * Luokka, joka kuvaa yhtä hoitojaksoa sairaalassa.
 * Hoitojaksolla on aloitus- ja lopetuspäivät, potilas
 * ja sillä voi olla monta sairaalan työntekijää.
 *
 * Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Konstruktori, kun alkupäivämääräksi annetaan merkkijono
    CarePeriod(const std::string& start, Person* patient);

    // Konstruktori, kun alkupäivämääräksi annetaan date tyyppinen olio
    CarePeriod(const Date& start, Person* patient);

    // Destruktori
    ~CarePeriod();

    // Tulostaa hoitojakson alkupäivämäärän ja loppupäivämäään,
    // jos sellainen on
    void print_care_period();

    // Asettaa hoitojaksolle loppupäivämäärän
    void set_end_date(const Date& end);

    // Lisää henkilökuntaa hoitojaksolle
    void add_staff(const std::string staff_member);

    // Tulostaa hoitojaksolla työskentelvät
    // henkilökunnan jäsenet
    void print_staff();

    // Palauttaa hoitojakson potilaan
    std::string get_patient();

    // Palauttaa hoitojakson henkilökunnan
    std::vector<std::string> get_staff();



private:
    // Määritellään potilas, henkilökunta ja alku-ja loppupäivämäärät
    Person* patient_;
    Date start_;
    Date end_;
    std::vector<std::string> staff_;

};

#endif // CAREPERIOD_HH
