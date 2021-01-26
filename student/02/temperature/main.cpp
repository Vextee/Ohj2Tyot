#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp;
    cin >> temp;

    double fahrenheit = temp * 1.8 + 32;
    double celcius = (temp-32)/1.8;

    cout << temp << " degrees Celcius is " << fahrenheit
         << " degrees Fahrenheit" << endl;

    cout << temp << " degrees Fahrenheit is " << celcius
         << " degrees Celcius" << endl;



    return 0;
}
