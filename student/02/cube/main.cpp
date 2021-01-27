#include <iostream>

using namespace std;

int main()
{
    int number = 0;

    cout << "Enter a number: ";
    cin >> number;

    int cube = number * number * number;
    if (number != 0){
        if (cube / number / number != number) {
            std::cout << "Error! The cube of " << number << " is not " << cube << endl;
            return 0;
        }
    }

    std::cout << "The cube of " << number << " is " << cube << "." << endl;

    return 0;
}
