/* Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */

#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Poistaa henkilökunnan jäsenet
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Poistaa potilaat
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }

    /*for( std::vector<CarePeriod*>::iterator
         iter = all_care_periods_.begin();
         iter != all_care_periods_.end();
         ++iter )
    {
        delete all_care_periods_[iter];
    }*/
    for (auto cp : all_care_periods_)
    {
        delete cp;
    }
}

// Lisää uuden henkilökunna jäsenen
void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    // Jos työntekijä oli jo olemassa, häntä ei lisätä uudelleen
    // ja tulostetaan virheilmoitus
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    // Luodaan uusi henkilöolio ja lisätään se staff säiliöön
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

// Lisätään uusi potilas sairaalaan
void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    // Jos potilas on jo sairaalassa, häntä ei lisätä uudelleen
    // ja tulostetaan virheilmoitus
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // Jos potilas on jo kerran ollut sairaalassa,
    // ei tarvitse luoda uutta henkilöoliota vaan vanha olio voidaan
    // lisätä takaisin nykyisiin potilaisiin
    if( all_patients_.find(patient_id) != all_patients_.end() )
    {
        current_patients_.insert({patient_id, all_patients_[patient_id]});
        CarePeriod* new_careperiod = new CarePeriod(utils::today, all_patients_[patient_id]);
        active_care_periods_.insert({patient_id, new_careperiod});
        all_care_periods_.push_back(new_careperiod);
    }
    // jos taas potilas ei ole vielä ollut kertaakaan sairaalassa
    // pitää luoda uusi olio ja lisätä se
    // nykyisiin ja kaikkiin potilaisiin
    else
    {
        Person* new_patient = new Person(patient_id);
        current_patients_.insert({patient_id, new_patient});
        all_patients_.insert({patient_id, new_patient});
        CarePeriod* new_careperiod = new CarePeriod(utils::today, new_patient);
        active_care_periods_.insert({patient_id, new_careperiod});
        all_care_periods_.push_back(new_careperiod);
    }

    std::cout << PATIENT_ENTERED << std::endl;
}

// poistaa potilaan sairaalasta eli poistaa hänet
// nykyisitä potilaista, mutta ei kaikista potilaista
// Lopettaa myös hoitojakson
// eli asettaa sille loppumispäivämäärän
void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    // Jos potilasta ei löydy nykyisistä potilaista,
    // tulostetaan virheilmoitus
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    // Käydään läpi aktiiviset hoitojaksot
    /*for (auto cp : active_care_periods_)
    {
        // Jos potilas löytyy
        if (cp.first == patient_id)
        {

        }
    }*/
    // Poistetaan potilaan hoitojakso aktiivisista hoitojaksoista
    active_care_periods_.erase(patient_id);

    // asetetaan tämän hoitojakson loppupäivämäärksi
    // nykyinen päivämäärä
    for (auto cp : all_care_periods_)
    {
        if (cp->get_patient() == patient_id)
        {
            cp->set_end_date(utils::today);
        }
    }

    // Lopuksi poistetaan potilas nykyisistä potilaista
    current_patients_.erase(patient_id);

    std::cout << "Patient left hospital, care period closed." << std::endl;
}

// Asetetaan henkilökunnan jäsen työskentelemään potilaan aktiivisella hoitojaksolla
void Hospital::assign_staff(Params params)
{
    std::string specialist_id = params.at(0);
    std::string patient_id = params.at(1);

    // Jos työntekijää ei löydy, tulostetaan
    // virheilmoitus ja poistutaan funktiosta
    if( staff_.find(specialist_id) == staff_.end() )
    {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }
    // Jos potilasta ei löydy sairaalassa olevista potilaista
    // tulostetaan virheilmoitus ja poistutaan funktiosta
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    // Etstiään mikä hoitojakson on annetun potilaan
    // ja lisätään työntekijä työskentelemään tähän hoitojaksoon
    for (auto cp : active_care_periods_)
    {
        if (cp.first == patient_id)
        {
            active_care_periods_[patient_id]->add_staff(specialist_id);
        }
    }
    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

// Lisää potilaalle reseptilääkkeen, jolla on nimi, vahvuus ja annos
void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);

    // Tarkistetaan onko annetut vahvuuden ja annoksen arvot numeerisia
    // jos ei tulostetaan virheilmoitus ja poistutaan funktiosta
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
     // Jos potilasta ei löydy nykyisitä potilaista,
     // tulostetaan virheilmoitus ja poistutaan funktiosta
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    // Lisätään lääke
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
    all_medicine_.insert(medicine);
}

// Poistaa potilaalta lääkkeen
void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
    //Jos potilasta ei löydy nykyisitä potilaista,
    // tulostetaan virheilmoitus ja poistutaan funktiosta
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    // Poistetaan lääke
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

// Tulostaa potilaan tiedot
void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);
    //Jos potilasta ei löydy kaikista potilaista,
    // tulostetaan virheilmoitus ja poistutaan funktiosta
    if( all_patients_.find(patient_id) == all_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    // Käydään läpi kaikki potilaat ja tulostetaan potilaan tiedot, kun potilas löytyy
    for (auto cp : all_care_periods_)
    {
        if (cp->get_patient() == patient_id)
        {
            std::cout << "* Care period: ";
            cp->print_care_period();
            std::cout << std::endl;
            std::cout << "  - Staff: ";
            cp->print_staff();

        }
    }
    // Tulostetaan vielä lopuksi potilaan kaikki lääkkeet
    std::cout << "* Medicines:";
    all_patients_[patient_id]->print_medicines("  - ");
}

// Tulostaa kaikki hoitojaksot, joilla työntekijä on työskennellyt
void Hospital::print_care_periods_per_staff(Params params)
{
    std::string specialist_id = params.at(0);
    //Jos annettua työntekijää ei löydy työntekijöistä,
    // tulostetaan virheilmoitus ja poistutaan funktiosta
    if( staff_.find(specialist_id) == staff_.end() )
    {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }
    bool found = false;
    // Käydään kaikki hoitojaksot läpi
    for (auto cp : all_care_periods_)
    {
        // Käydään hoitojakson työntekijät läpi
        for (std::string s : cp->get_staff())
        {
            // Jos hoitojakson työntekijä on sama kuin annettu työntekijä
            // Voidaan päätellä, että työntekijä työskentelee hoitojaksolla
            if (s == specialist_id)
            {
                // Tulostetaan tämän hoitojakson tiedot
                cp->print_care_period();
                std::cout << std::endl;
                std::cout << "* Patient: " <<cp->get_patient() << std::endl;
                found = true;
            }
        }
    }
    // Jos hoitojaksoja ei löytynyt ollenkaan tulostetaan None
    if (!found)
    {
        std::cout << "None" << std::endl;
    }

}

// Tulostaa kaikki lääkkeet, joita on sinä hetkenä jollakin käytössä
void Hospital::print_all_medicines(Params)
{
    // Jos lääkkeitä ei ole yhtään tulostetaan None
    // ja poistutaan funktiosta
    if(all_medicine_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Käydään kaikki lääkkeet läpi ja tarkistetaan kennellä potilaista sitä on käytössä
    for (std::string m : all_medicine_)
    {
        bool in_use = false;
        for (auto patient : all_patients_)
        {
            std::vector<std::string> medicine = patient.second->get_medicines();
            if(std::find(medicine.begin(), medicine.end(), m) != medicine.end())
            {
                in_use = true;
            }
        }
        if (in_use)
        {
           std::cout << m << " prescribed for" << std::endl;
           for (auto patient : all_patients_)
           {
               std::vector<std::string> medicine = patient.second->get_medicines();
               if(std::find(medicine.begin(), medicine.end(), m) != medicine.end())
               {
                   std::cout << "* " << patient.first << std::endl;
               }
           }
        }
    }
}

// Tulostaa kaikki henkilökunnan jäsenet
void Hospital::print_all_staff(Params)
{
    // Jos henkilökuntaa ei ole yhtään tulostetaan None
    // ja poistutaa funktiosta
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    // Käydään henkilökunta mappi läpi ja tulostetaan jokainen työntekijä
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

// Tulostaa kaikki potilaat ja heidän tiedot
void Hospital::print_all_patients(Params)
{
    // Jos potilaita ei ole yhtään,
    // tulostetaan none ja poistutaa funktiosta
    if (all_patients_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    // Käydään kaikki potilaat läpi ja tulostetaan heidän
    // tiedot yhksitellen
    for (auto patient : all_patients_)
    {
        std::cout << patient.first << std::endl;
        std::vector<std::string> params;
        params.push_back(patient.second->get_id());
        print_patient_info(params);

    }
}

// Tulostaa tällä hetkellä sairaalassa olevien potilaiden tiedot
void Hospital::print_current_patients(Params)
{
    // Jos potilaita ei ole yhtään sairaalassa,
    // tulostetaan none ja poistutaa funktiosta
    if (current_patients_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    // Käydään sairaalassa olevat potilaat
    // läpi ja tulostetaan heidän
    // tiedot yhksitellen
    for (auto patient : current_patients_)
    {
        std::cout << patient.first << std::endl;
        std::vector<std::string> params;
        params.push_back(patient.second->get_id());
        print_patient_info(params);

    }
}

// Asettaa nykyiseksi päivämääräksi annetun päivämäärän
void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    // Tarkisteaan onko annetut syötteet numeerisia
    // jos ei, tulostetaan virheilmoitus ja poistutaan funktiosta
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    // Asetetaan päivämäär
    utils::today.set(stoi(day), stoi(month), stoi(year));
    // Tulostetaan päivämäär
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

// Siirretään aikaa eteenpäin annetujen päivien verran
void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    // Tarkistetaan onko syöte numeerinen
    // jos ei, tulostetaan virheilmoitus ja poistutaan funktiosta
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    // Siirretään aikaa eteenpäin ja tulostetaan uusi aika
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
