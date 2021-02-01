#include <iostream>

using namespace std;

unsigned long int kertoma(int luku){
    unsigned long int tulos = 1;
    if (luku == 0) {
        tulos = 1;
    }
    else {
        while ( luku > 0 ) {
                    tulos = tulos * luku;
                    --luku;
        }
    }
    return tulos;
}


unsigned long int rivit(int kok, int arv)
{
    unsigned long int kok_kertoma = kertoma(kok);
    unsigned long int arv_kertoma = kertoma(arv);
    int ero = kok - arv;
    unsigned long int ero_kertoma = kertoma(ero);

    unsigned long int rivit = kok_kertoma/(ero_kertoma*arv_kertoma);
    return rivit;
    }


int main()
{
    int kok = 0;
    int arv = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> kok;
    cout << "Enter the number of drawn balls: ";
    cin >> arv;
    if (kok < 0 || arv <0) {
            cout << "The number of balls must be a positive number." << endl;
        } else if (kok<arv) {
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        } else {
            unsigned long int rivien_maara = rivit(kok, arv);
            cout << "The probability of guessing all " << arv << " balls correctly is 1/" << rivien_maara << endl;
        }

    return EXIT_SUCCESS;
}
