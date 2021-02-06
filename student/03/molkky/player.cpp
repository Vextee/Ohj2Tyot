#include "player.hh"
#include <iostream>

Player::Player( const std::string& name) :
    NAME_(name),
    points_(0)
{
}

const std::string& Player::get_name()
{
    return NAME_;
}

int Player::get_points()
{
    return points_;
}

void Player::add_points(int amount)
{
    points_ += amount;
    if (points_ > 50)
    {
        points_ = 25;
        std::cout << NAME_ << " gets penalty points!" << std::endl;
    }
}

bool Player::has_won()
{
    return points_ == 50;
}

