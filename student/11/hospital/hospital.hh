/* Luokka Hospital
 * ----------
 * COMP.CS.110 KEVAT 2021
 * ----------
 *
 * Luokka kuvaa sairaalaa. Vain yksi sairaala olio luodaan. Tässä luokassa
 * toteutetaan kaikki ohjelman komennot.
 *
 * Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 * */
#ifndef HOSPITAL_HH
#define HOSPITAL_HH

#include "person.hh"
#include "careperiod.hh"
#include "date.hh"
#include <map>
#include <set>

// Vika and informaatio tulosteet
const std::string ALREADY_EXISTS = "Error: Already exists: ";
const std::string NOT_NUMERIC = "Error: Wrong type of parameters.";
const std::string CANT_FIND = "Error: Can't find anything matching: ";
const std::string STAFF_RECRUITED = "A new staff member has been recruited.";
const std::string PATIENT_ENTERED = "A new patient has entered.";
const std::string PATIENT_LEFT = "Patient left hospital, care period closed.";
const std::string MEDICINE_ADDED= "Medicine added for: ";
const std::string MEDICINE_REMOVED= "Medicine removed from: ";
const std::string STAFF_ASSIGNED= "Staff assigned for: ";

using Params = const std::vector<std::string>&;

class Hospital
{
public:
    // Konstruktori.
    Hospital();

    // Destruktori.
    ~Hospital();

    // Rekrytoi uuden henkilökunnan jäsenen (luo uuden henkilö olion).
    void recruit(Params params);

    // Lisää potilaan sairaalaan ja luo uuden hoitojakson.
    void enter(Params params);

    // Poistaa henkilön sairaalasta ja lopettaa hoitojakson.
    void leave(Params params);

    // Asettaa henkilökunnan jäsenen työskentelemään
    // potilaan hoitojaksolla.
    void assign_staff(Params params);

    // Lisää annetun lääkkeen (nimi, vahvuus, annos) potilaalle.
    void add_medicine(Params params);

    // Poistaa annetun lääkkeen potilaalta.
    void remove_medicine(Params params);

    // Tulostaa tietyn potilaan kaikki hoitojaksot, niillä työskentelevät
    // henkilökunnan jäsenet ja potilaan lääkkeet.
    void print_patient_info(Params params);

    // Tulostaa kaikki hoitojaksot, joilla henkilökunnan jäsen
    // on työskennellyt
    void print_care_periods_per_staff(Params params);

    // Tulostaa kaikki lääkkeet, joita joku sairaalassa käynyt käyttää
    // Tulostaa myös kuka näitä lääkkeitä käyttää
    void print_all_medicines(Params);

    // Tulostaa kaikki sairaalaan rekrytoimat työntekijät
    void print_all_staff(Params);

    // Tulostaa kaikki potilaat, jotka ovat joskus vierailleet sairaalassa
    // Tulostaa tarkemmin potilaan nimen, hoitojaksot ja lääkkeet.
    void print_all_patients(Params);

    // Tulostaa kaikkien tällä hetkellä sairaallssa olevien potilaiden tiedot
    void print_current_patients(Params);

    // Asettaa uuden tämänhetkisen päivämäärän
    void set_date(Params params);

    // siirtää aikaa eteenpäin annetun määrän verran
    void advance_date(Params params);

private:
    // Säiliöitä potilaille, henkilökunnalle, hoitojaksoille ja lääkkeille
    std::map<std::string, Person*> current_patients_;
    std::map<std::string, Person*> staff_;
    std::map<std::string, Person*> all_patients_;
    std::vector<CarePeriod*> all_care_periods_;
    std::map<std::string, CarePeriod*> active_care_periods_;
    std::set<std::string> all_medicine_;
};

#endif // HOSPITAL_HH
