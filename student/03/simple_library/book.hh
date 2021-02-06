#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"

#include <iostream>

class Book
{
public:
    Book(const std::string& author_name, const std::string& title);
    void print();
    void loan(const Date& loand_date);
    void renew();
    void give_back();

private:
    const std::string AUTHOR_NAME_;
    const std::string TITLE_;

    bool is_loaned_;
    Date loan_date_;
    Date expiry_date_;
};

#endif // BOOK_HH
