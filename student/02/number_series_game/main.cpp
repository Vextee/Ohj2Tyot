#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numbers;
    std::cin >> numbers;

    for ( int luku = 1; luku <= numbers; ++luku) {
        if (luku % 3 == 0 && luku % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        }
        else if ( luku % 7 == 0) {
            std::cout << "boing" << std::endl;
        }
        else if (luku % 3 == 0) {
            std::cout << "zip" << std::endl;
        }
        else {
            std::cout << luku << std::endl;
        }

        }
    }

