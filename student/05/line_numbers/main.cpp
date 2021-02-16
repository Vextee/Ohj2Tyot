#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main()
{
    std::string in_tiedosto;
    std::string out_tiedosto;
    std::cout << "Input file: ";
    std::cin >> in_tiedosto;
    std::cout << "Output file: ";
    std::cin >> out_tiedosto;

    std::ifstream tiedosto_olio;
    tiedosto_olio.open(in_tiedosto);
    if (!tiedosto_olio.is_open())
    {
        std::cout << "Error! The file " << in_tiedosto <<  " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<std::string> rivit;
    std::string rivi;
    while(std::getline(tiedosto_olio, rivi))
    {
        rivit.push_back(rivi);
    }
    tiedosto_olio.close();


    std::ofstream tiedosto_olio2;
    tiedosto_olio2.open(out_tiedosto);
    unsigned int i = 1;
    for (std::string r : rivit)
    {
        tiedosto_olio2 << i << " " << r << std::endl;
        i += 1;
    }
    tiedosto_olio.close();

    return 0;
}
