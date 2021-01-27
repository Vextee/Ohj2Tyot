#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    cout << "Enter a positive number: ";

    int luku = 0;
    std::cin >> luku;

    if (luku <= 0) {
        std::cout << "Only positive numbers accepted" << std::endl;
        return EXIT_FAILURE;
    }

    int factor1 = 0;
    int factor2 = 0;
    int factor_cand = std::max(static_cast<int>(sqrt(luku)), 1);

    for(; luku % factor_cand != 0; --factor_cand);

        factor1 = factor_cand;
        factor2 = luku / factor_cand;



    std::cout << luku << " = " << factor1 << " * " << factor2 << std::endl;


    return EXIT_SUCCESS;
}
