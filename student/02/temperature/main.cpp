#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp;
    cin >> temp;

    double fahrenheit = temp * 1.8 + 32;
    double celsius = (temp-32)/1.8;

    cout << temp << " degrees Celsius is " << fahrenheit
         << " degrees Fahrenheit" << endl;

    cout << temp << " degrees Fahrenheit is " << celsius
         << " degrees Celsius" << endl;



    return 0;
}
