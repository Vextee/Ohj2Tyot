#include <iostream>

using namespace std;

int main()
{
    int number = 0;

    cout << "Enter a number: ";
    cin >> number;

    int cube = number * number * number;
    if (cube / number / number != number) {
        std::cout << "Error! The cube of " << number << " is not " << cube << endl;
    }
    else {
        std::cout << "The cube of " << number << " is " << cube << "." << endl;
    }

    return 0;
}
