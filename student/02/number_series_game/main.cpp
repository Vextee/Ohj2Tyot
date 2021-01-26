#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numbers;
    std::cin >> numbers;

    for ( int luku = 1; luku <= 10; ++luku) {
        if (luku % 3 == 0) {
            std::cout << "zip" << std::endl;
        }
        else {
            std::cout << luku << std::endl;
        }

        }
    }

