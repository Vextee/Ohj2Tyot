#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false, std::string iban="", double balance = 0, double credit_limit = 0);

    // More methods
    void print() const;
    void set_credit_limit(int limit);
    void save_money(int save_amount);
    bool take_money(int take_amount);
    void transfer_to(Account &account, int transf_amount);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    const std::string& owner_;
    std::string iban_;
    double balance_;
    double credit_;
    double credit_limit_;
    bool has_credit_;
};

#endif // ACCOUNT_HH
