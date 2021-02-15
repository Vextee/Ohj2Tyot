/* Muistipeli
 *
 * Kuvaus:
 *  Ohjelma toteuttaa muistipelin. Pelissä on vaihteleva määrä kortteja ja
 * pelaajia. Pelin alussa käyttäjältä kysytään myös siemenluku, koska kortit
 * arvotaan satunnaisesti pelilaudalle.
 *  Joka kierroksella vuorossa oleva pelaaja antaa kahden kortin
 * koordinaatit (yhteensä neljä lukua), minkä jälkeen kyseiset kortit
 * käännetään näkyviin ja kerrotaan, ovatko ne parit vai ei.
 * Jos pelaaja sai parit, kortit poistetaan pelilaudalta, pelaajan
 * pistesaldoa kasvatetaan, ja hän saa uuden vuoron. Jos pelaaja ei saanut
 * pareja, kortit käännetään takaisin piiloon, ja vuoro siirtyy seuraavalle
 * pelaajalle.
 *  Ohjelma tarkistaa pelaajan antamat koordinaatit. Koordinaattien pitää
 * olla sellaiset, että niiden märä kortti löytyy pelilaudalta.
 *  Muutosten jälkeen pelilauta tulostetaan aina uudelleen. Kortit kuvataan
 * kirjaimina alkaen A:sta niin pitkälle, kuin kortteja on. Kun pelilauta
 * tulostetaan, näkyvissä oleva kortti kuvataan kyseisellä kirjaimella.
 * Piiloon kännettyä korttia kuvaa risuaita (#), ja laudalta poistetun
 * kortin kohdalle tulostetaan piste.
 *  Peli päättyy, kun kaikki parit on löydetty, ja pelilauta on tyhjä.
 * Tällöin kerrotaan, kuka tai ketkä voittivat eli saivat eniten pareja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Käyttäjätunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";


using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Lisää funktioita
std::vector<Player> ask_number_and_names_of_players(unsigned int& maara)
{
    std::vector<Player> pelaajat;
    std::string maara_str = "";
    std::string nimi = "";
    while(true)
    {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        std::cin >> maara_str;
        maara = stoi_with_check(maara_str);
        if (maara == 0 or maara <= 0)
        {
            continue;
        }

        std::cout << "List " << maara << " players: ";

        for (unsigned int i = 0; i < maara; ++i)
        {
            std::cin >> nimi;
            Player pelaaja(nimi);
            pelaajat.push_back(pelaaja);
        }

        return pelaajat;
    }




}

std::vector<std::string> split(const std::string& line, char sep, bool empty = false)
{
    std::vector<std::string> parts;

    std::string::size_type left = 0;
    std::string::size_type right = 0;

    while(right != std::string::npos)
    {
        right = line.find(sep, left);

        std::string part = line.substr(left, right - left);

        if (part == "" and empty == true)
        {
            left = right + 1;
            continue;
        }

        parts.push_back(part);

        left = right + 1;
    }



    return parts;
}

bool ask_coordinates(Player pelaaja, int X_MAX, int Y_MAX, Game_board_type& g_board)
{


    std::vector<int> koordinaatit_int;
    std::cout << X_MAX << Y_MAX << std::endl;
    std::string koordinaatti;

    while(true)
    {
        bool on_kirjaimia = false;
        bool on_alle_nolla = false;
        koordinaatti = "";
        koordinaatit_int.clear();

        std::cout << pelaaja.get_name() << ": " << INPUT_CARDS;
        std::cin >> koordinaatti;
        if (koordinaatti == "q")
        {
            std::cout << GIVING_UP << std::endl;
            return true;
        }
        koordinaatit_int.push_back(stoi_with_check(koordinaatti)-1);
        cin >> koordinaatti;
        koordinaatit_int.push_back(stoi_with_check(koordinaatti)-1);
        cin >> koordinaatti;
        koordinaatit_int.push_back(stoi_with_check(koordinaatti)-1);
        cin >> koordinaatti;
        koordinaatit_int.push_back(stoi_with_check(koordinaatti)-1);


        for (int s : koordinaatit_int)
        {
            if (s == -1)
            {
                on_kirjaimia = true;
                break;
            }
            else if(s <= -1)
            {
                on_alle_nolla = true;
                break;
            }
        }
        if (on_kirjaimia or on_alle_nolla)
        {
            std::cout << INVALID_CARD << std::endl;
        }
        else if (koordinaatit_int.at(0) > X_MAX or koordinaatit_int.at(1) > Y_MAX
            or koordinaatit_int.at(2) > X_MAX
            or koordinaatit_int.at(3) > Y_MAX)
        {
            std::cout << INVALID_CARD << std::endl;
        }
        else if(koordinaatit_int.at(0) == koordinaatit_int.at(2)
                and koordinaatit_int.at(1) == koordinaatit_int.at(3))
        {
            std::cout << INVALID_CARD << std::endl;
        }
        else if(g_board.at(koordinaatit_int.at(1)).at(koordinaatit_int.at(0)).get_visibility() != HIDDEN
                or g_board.at(koordinaatit_int.at(3)).at(koordinaatit_int.at(2)).get_visibility() != HIDDEN)
        {
            std::cout << INVALID_CARD << std::endl;
        }
        else
        {
            g_board.at(koordinaatit_int.at(1)).at(koordinaatit_int.at(0)).turn();
            g_board.at(koordinaatit_int.at(3)).at(koordinaatit_int.at(2)).turn();
            print(g_board);
            if(g_board.at(koordinaatit_int.at(1)).at(koordinaatit_int.at(0)).get_letter() == g_board.at(koordinaatit_int.at(3)).at(koordinaatit_int.at(2)).get_letter())
            {
                g_board.at(koordinaatit_int.at(1)).at(koordinaatit_int.at(0)).set_visibility(EMPTY);
                g_board.at(koordinaatit_int.at(3)).at(koordinaatit_int.at(2)).set_visibility(EMPTY);
            }
            else
            {
                g_board.at(koordinaatit_int.at(1)).at(koordinaatit_int.at(0)).turn();
                g_board.at(koordinaatit_int.at(3)).at(koordinaatit_int.at(2)).turn();
            }
            return false;
        }
    }


}





int main()
{
    Game_board_type game_board;

    unsigned int maara = 0;
    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);




    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    vector<Player> pelaajat = ask_number_and_names_of_players(maara);

    print(game_board);

    bool on_loppu = false;

    while(true)
    {
        for(unsigned int vuoro = 0; vuoro < maara; vuoro++)
        {
            if (ask_coordinates(pelaajat.at(vuoro), (factor1), (factor2), game_board))
            {
                on_loppu = true;
                break;
            }
            print(game_board);
        }
        if (on_loppu)
        {
            break;
        }


    }

    return EXIT_SUCCESS;
}

