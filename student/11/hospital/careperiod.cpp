#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::print_care_period()
{

}

void CarePeriod::set_end_date(const Date& end)
{
    end_ = end;
}

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
    if (!found)
    {
        staff_.push_back(staff_member);
    }

}
