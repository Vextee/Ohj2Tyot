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
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    if( all_patients_.find(patient_id) != all_patients_.end() )
    {
        current_patients_.insert({patient_id, all_patients_[patient_id]});
        CarePeriod* new_careperiod = new CarePeriod(utils::today, all_patients_[patient_id]);
        active_care_periods_.insert({patient_id, new_careperiod});
        all_care_periods_.push_back(new_careperiod);
    }
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

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    for (auto cp : active_care_periods_)
    {
        if (cp.first == patient_id)
        {
            active_care_periods_.erase(patient_id);
        }
    }

    for (auto cp : all_care_periods_)
    {
        if (cp->get_patient() == patient_id)
        {
            cp->set_end_date(utils::today);
        }
    }

    current_patients_.erase(patient_id);

    std::cout << "Patient left hospital, care period closed." << std::endl;
}


void Hospital::assign_staff(Params params)
{
    std::string specialist_id = params.at(0);
    std::string patient_id = params.at(1);
    if( staff_.find(specialist_id) == staff_.end() )
    {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    for (auto cp : active_care_periods_)
    {
        if (cp.first == patient_id)
        {
            active_care_periods_[patient_id]->add_staff(specialist_id);
        }
    }
    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);
    if( all_patients_.find(patient_id) == all_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    for (auto cp : all_care_periods_)
    {
        if (cp->get_patient() == patient_id)
        {
            std::cout << "* Care period: ";
            cp->print_care_period();
            std::cout << std::endl;
            std::cout << "  - Staff: ";
            std::vector<std::string> staff = cp->get_staff();
            if (staff.size() == 0)
            {
                std::cout << "None" << std::endl;
            }
            else
            {
                sort(staff.begin(), staff.end());
                for (std::string s : staff)
                {
                    std::cout << s << " ";
                }
                std::cout << std::endl;
            }

        }
    }

    std::cout << "* Medicines:";
    all_patients_[patient_id]->print_medicines("  - ");


}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) == staff_.end() )
    {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }
    bool found = false;
    for (auto cp : all_care_periods_)
    {
        for (std::string s : cp->get_staff())
        {
            if (s == specialist_id)
            {
                cp->print_care_period();
                std::cout << std::endl;
                std::cout << "* Patient: " <<cp->get_patient() << std::endl;
                found = true;
            }
        }
    }
    if (!found)
    {
        std::cout << "None" << std::endl;
    }

}

void Hospital::print_all_medicines(Params)
{

}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    if (all_patients_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (auto patient : all_patients_)
    {
        std::cout << patient.first << std::endl;
        std::string patient_id = patient.second->get_id();

        for (auto cp : all_care_periods_)
        {

            if (cp->get_patient() == patient_id)
            {
                std::cout << "* Care period: ";
                cp->print_care_period();
                std::cout << std::endl;
                std::cout << "  - Staff: ";
                std::vector<std::string> staff = cp->get_staff();
                if (staff.size() == 0)
                {
                    std::cout << "None" << std::endl;
                }
                else
                {
                    sort(staff.begin(), staff.end());
                    for (std::string s : staff)
                    {
                        std::cout << s << " ";
                    }
                    std::cout << std::endl;
                }

            }
        }

        std::cout << "* Medicines:";
        all_patients_[patient_id]->print_medicines("  - ");


    }
}

void Hospital::print_current_patients(Params)
{
    if (current_patients_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (auto patient : current_patients_)
    {
        std::cout << patient.first << std::endl;
        std::string patient_id = patient.second->get_id();

        for (auto cp : all_care_periods_)
        {
            if (cp->get_patient() == patient_id)
            {
                std::cout << "* Care period: ";
                cp->print_care_period();
                std::cout << std::endl;
                std::cout << "  - Staff: ";
                std::vector<std::string> staff = cp->get_staff();
                if (staff.size() == 0)
                {
                    std::cout << "None" << std::endl;
                }
                else
                {
                    sort(staff.begin(), staff.end());
                    for (std::string s : staff)
                    {
                        std::cout << s << " ";
                    }
                    std::cout << std::endl;
                }

            }
        }

        std::cout << "* Medicines:";
        all_patients_[patient_id]->print_medicines("  - ");


    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
