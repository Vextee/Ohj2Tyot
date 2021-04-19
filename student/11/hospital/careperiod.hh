/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods
    void print_care_period();

    void set_end_date(const Date& end);

    void add_staff(const std::string staff_member);

    void print_staff();

    std::string get_patient();

    std::vector<std::string> get_staff();



private:
    Person* patient_;
    Date start_;
    Date end_;
    std::vector<std::string> staff_;

    // More attributes and methods
};

#endif // CAREPERIOD_HH