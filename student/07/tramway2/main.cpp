/*
 *Rasse 2
 *
 *Kuvaus:
 *Käynnistyessään ohjelma aluksi tulostaa kuvan rassesta.
 *Tämän jälkeen käyttäjltä kysytään pohjatiedoston nimeä,
 *joka sisältää raitiovaunu linjoja,joilla on pysähdyksiä
 *ja pysähdyksillä tietty etäisyys lähtöpysäkistä.
 *Tämä data tallennetaan tietoraknteeseen.
 *Nyt tietorakenteeksi on valittu map, jonka sisällä on toinen map.
 *Tämän jälkeen siirrytään käyttöliittymään,
 *jonka avulla käyttäjä voi tarkastella ja muokata tätä tietorakennetta.
 *Käyttäjä voi esimerkiksi halutessaa tulostaa kaikki linjat tai pysäkit.
 *Käyttäjä voi myös lisätä linjoja ja pysäkkejä tietorakenteeseen.
 *Pysäkkejä voi tämän lisäksi myös poistaa.
 *Jos ohjelman suorittaessa tulee ilmi virhe,
 *siitä ilmoitetaan ja joko lopetetaan ohjelman suoritus
 *tai jatketaan silmukkassa uudelle kierrokselle.
 *
 *
 *Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 050149539
 * Käyttäjätunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Yllättävää oli se, että kun ohjleman koodauksessa
 * pääsi vauhtiin, se olikin yllättävän helppoa.
 * Osiot, jotka vaikuttivat alunperin tehtävänantoa
 * katsoessa olivatkin helpoimpia. Näitä oli erityisesti
 * funktiot, jotka muokkasivat tietorakennetta, jotenkin.
*/

#include <iostream>
#include <map>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

// Suurenmoisin funktio koko tässä ohjelmassa.
// Tulostaa RASSEn
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Otetaan tietorakenne käyttöön kaikkiin funktioihin
// , jotta sitä ei tarvitse alustaa joka kerta uudelleen.
using Tramlines = std::map<std::string, std::map<double, std::string>>;

// Funktio, joka jakaa merkkijonon osiin tietyn erottajan kohdalta.
std::vector<std::string> split(std::string s, const char delimiter){
    std::vector<std::string> result = {""};
    std::string tmp = s;
    bool quote_found = false;

    // Jos merkkijonossa on heittomerkit, ne poistetaan.
    for (char c : s)
    {
        if (c == '"')
        {
            quote_found = !quote_found;
        }
        else if (c == delimiter and quote_found == false)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(c);
        }
    }

    if (result.back() == "")
    {
        result.pop_back();
    }

    return result;
}

// Lukee käyttäjältä avattavan tiedoston nimen.
std::string read_file_name()
{
    std::string file_name;
    std::cout << "Give a name for input file: ";
    getline(std::cin, file_name);
    return file_name;
}

// Avataan tiedosto ja tarkistetaan sen sisältämä data.
// Jos data on virheellistä palautetaan false.
// Muullois palautetaan true.
bool check_data(const std::string& file_name)
{
    // Avataan tiedosto
    std::ifstream file(file_name);

    // Jos tiedostoa ei saada auki
    // Tulostetaan virheilmoitus
    // ja palautetaan false.
    if (!file)
    {
        std::cout << "Error: File could not be read." << std::endl;
        file.close();
        return false;
    }
    else
    {
        std::string line;
        // Käydään tiedosto riveittäin läpi
        while (getline(file, line))
        {

           // Jaetaan tiedoston rivi paloihin
           std::vector<std::string> parts = split(line, ';');

           // Jos jollakin tiedoston rivillä on liian paljon tai vähän osia tai
           // jompikumpi ensimmäisistä osista on tyhjä merkkijono,
           // tulostetaan virheilmoitus ja palautetaan false.
           if (parts.size() > 3 or parts.size() < 2 or parts.at(0) == "" or parts.at(1) == "")
           {
               std::cout << "Error: Invalid format in file." << std::endl;
               file.close();
               return false;
           }
        }
    }
    file.close();
    return true;
}

// Avaa tiedoston ja tallnetaan sen datan tietorakenteeseen
bool save_data(Tramlines& tramlines, const std::string& file_name)
{

    // Avataan tiedosto
    std::ifstream file(file_name);
    std::string line;

    // Käydään tiedosto riveittäin läpi
    while (getline(file, line))
    {

        // Jaetaan rivin tiedot osiin
        std::vector<std::string> parts = split(line, ';');

        // Jos rivillä ei ole etäisyyttä,
        // etäisyydeksi asetetaan oletuksena 0
        if(parts.size() < 3)
        {
            parts.push_back("0.0");
        }
        else if(parts.at(2) == "")
        {
            parts.at(2) = "0.0";
        }

        // Muunnetaan etäissy double muotoon
        double distance = stod(parts.at(2));

        // Muodostetaan pari etäisyydestä ja pysäkin nimestä
        std::pair<double, std::string> stop_and_dis = {distance, parts.at(1)};

        // Tarkistetaan onko linja jo tietorakenteessa.
        // Jos ei ole, muodostetaan tyhjä mappi sen paikalle
        if (tramlines.find(parts.at(0)) == tramlines.end())
        {
            tramlines[parts.at(0)] = {};
        }

        // Tarkistetaan onko linjalla jo valmiiksi tietty pysäkki tai
        // jokin toinen pysäkki samalla etäisyydellä
        // Jos on, tulostetaan virheilmoitus, suljetaan tiedosto ja palutetaan false.
        for (std::pair<double, std::string> stops : tramlines.at(parts.at(0)))
        {
            if (stops.first == distance or stops.second == parts.at(1))
            {
                std::cout << "Error: Stop/line already exists." << std::endl;
                file.close();
                return false;
            }
        }

        // Lopuksi lisätään pysäkki ja sen etäisyys tietorakenteeseen
        // linjan kohdalle.
        tramlines[parts.at(0)].insert(stop_and_dis);
    }

    // Suljetaan tiedosto
    file.close();

    // Jos kaikki sujui hyvin palautetaan true
    return true;
}

// Tarkistetaan onko kaksi komentoa sama
// Syötetty komento voi olla myös pienellä
// ja se silti hyväksytään.
// Käyttäjän syöttämä komento pitää siis isoiksi kirjaimiksi,
// jotta sitä voidaan vertailla toiseen komentoo, joka on isolla.
bool same_command(const std::string& real_command, std::string input_command)
{
    // Käytetään isoihin kirjaimiin muuttamiseen transform funktiota.
    std::transform(input_command.begin(), input_command.end(), input_command.begin(), ::toupper);

    // Jos kommenot olivat samat,
    // plautetaan true.
    // Jos taas eivät,
    // palautettaan false.
    if (input_command == real_command)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Tulostaa kaikki linjat aakkosjärjestyksessä
void print_lines(const Tramlines& tramlines)
{
    std::cout << "All tramlines in alphabetical order:" << std::endl;
    std::vector<std::string> line_names = {};

    // Kerätään kaikki linjat vektoriin
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        line_names.push_back(lines.first);
    }

    // Järjestellään linjat aakkosjärjestykseen
    sort(line_names.begin(), line_names.end());

    // Tulostetaan linjat
    for (std::string s : line_names)
    {
        std::cout << s << std::endl;
    }

    return;
}

// Tulostetaan tietyn linjan kaikki pysäkit ja niiden etäisyydet
void print_line_stops(const Tramlines& tramlines, const std::string& line)
{

    // Tarkistetaan löytyykö annettua linjaa tietorakenteesta
    bool line_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    // Jos ei löytynyt tulostetaan virheilmoitus
    // ja poistutaan funktiosta
    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    // Jos linja löytyi tietorakenteeesta,
    // Käydään läpi linja pysäkit ja
    //tulostetaan niiden tiedot
    std::cout << "Line " << line << " goes through these stops in the order they are listed:" << std::endl;
    for (std::pair<double, std::string> stops : tramlines.at(line))
    {
        std::cout << " - " << stops.second << " : " << stops.first << std::endl;
    }
    return;
}

// Tulostaa kaikki pysäkit
void print_stops(const Tramlines& tramlines)
{ 
    std::cout << "All stops in alphabetical order:" << std::endl;
    std::vector<std::string> stops = {};

    // Kerää kaikki pysäkit vektoriin.
    // Jos pysäkki on jo vektorissa,
    // sitä ei lisätä uudelleen.
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> stop : lines.second)
        {
            if (std::find(stops.begin(), stops.end(), stop.second) == stops.end())
            {
                stops.push_back(stop.second);
            }
        }
    }

    // Järjestellään pysäkit aakkosjärjestykseen
    sort(stops.begin(), stops.end());

    // Tulostetaan pysäkit
    for (std::string s : stops)
    {
        std::cout << s << std::endl;
    }
    return;
}

// Tulostaa kaikki linjat, joilla tietty pysäkki on
void print_stop_lines(const Tramlines& tramlines, const std::string& stop)
{

    // Kerätään pysäkin linjat vektoriin
    std::vector<std::string> line_names = {};;

    // Käy läpi kaikkien linjojen pysäkit ja tarkistaa
    // onko annettu pysäkki niiden joukossa
    // jos pysäkki löytyi linjan pysäkeistä
    // linja lisätään vektoriin
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                line_names.push_back(lines.first);
            }
        }
    }

    // Järjestellään linjat aakkosjärjestykseen
    sort(line_names.begin(), line_names.end());

    // Jos linja vektroissa ei ole yhtään linjaa
    // pysäkkiä ei siis löydetty.
    // Tulostetaan virheilmoitus
    // ja poistutaan funktiosta
    if (line_names.size() == 0)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
    }

    // Muuten tulostetaan löydetyt linjat
    else
    {
        std::cout << "Stop " << stop << " can be found on the following lines:" << std::endl;
        for (std::string l : line_names)
        {
            std::cout << " - " << l << std::endl;
        }
    }

    return;
}

// Laskee ja tulostaa jonkin linja pysäkkien välisen etäisyyden
void print_distance_between_stops(const Tramlines& tramlines, const std::string& line,
                                  const std::string& stop1, const std::string& stop2)
{

    // Alustetaan etäisyydet
    double dis1 = -1;
    double dis2 = -1;
    double dis_between = 0;

    // Tarkistetaan onko linja tietorakenteessa
    bool line_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    // Jos linjaa ei löytynyt,
    // tulostetaan ilmoitus
    // ja poistutaan funktiosta
    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    // Etsitään tietorakenteesta
    // mikä on tietyn pysäkin etäisyys
    for (std::pair<double, std::string> stops : tramlines.at(line))
    {
        if (stops.second == stop1)
        {
            dis1 = stops.first;
        }
        else if (stops.second == stop2)
        {
            dis2 = stops.first;
        }
    }

    // Jos jommankumman pysäkin etäisyydeksi
    // on jäänyt -1, tulostetaan ilmoitus
    // ja poistutaan funktiosta
    if (dis1 == -1 or dis2 == -1)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
        return;
    }

    // Muuten vähennetään etäisyydet toisistaan
    else
    {
        if (dis1 > dis2)
        {
            dis_between = dis1 - dis2;
        }
        else
        {
            dis_between = dis2 - dis1;
        }
    }

    // Tulostetaan saatu etäisyys pysäkkien välillä
    std::cout << "Distance between " << stop1 << " and " << stop2 << " is " << dis_between << std::endl;

    return;
}

// Lisää uuden linjan
void add_line(Tramlines& tramlines, const std::string& line)
{

    // Tarkastetaan ensin löytyykö linja
    // jo valmiiksi tietorakenteesta
    bool line_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    // Jos löytyi,
    // tulostetaan virheilmoitus
    // ja poistutaan funktiosta
    if (line_found)
    {
        std::cout << "Error: Stop/line already exists." << std::endl;
        return;
    }

    // Jos taas ei löytynyt
    // Asetetaan linja paikalle tyhjä mappi
    // Linjalle ei siis vielä anneta
    // pysäkkejä ja etäisyyksiä
    tramlines[line] = {};
    std::cout << "Line was added." << std::endl;

    return;
}

// Lisää pysäkin ja sille etäisyyden
// jollekin linjalle
void add_stop(Tramlines& tramlines, const std::string& line,
              const std::string& new_stop, const double& distance)
{

    // Tarkistetaan löytyykö linja tietokannasta
    bool line_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    // Jos ei löydy,
    // tulostetaan virheilmoitus
    // ja poistutaan funktiosta
    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    // jos linja löytyi,
    // Tarkistetaan onko lisättävää pysäkkiä
    // jo valmiiksi linjalla tai onko
    // linjalla pysäkkiä samalla etäisyydellä
    for (std::pair<double, std::string> s : tramlines.at(line))
    {
        // jos jompikumpi käy toteen,
        // tulostettaan virheilmoitus
        // ja poistutaan funktiosta
        if (s.second == new_stop or s.first == distance)
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
            return;
        }
    }

    // Jos virheitä ei löytynyt, voidaan
    // pysäkki ja sen etäisyys lisätä
    // tietokantaan linjan kohdalle
    std::pair<double, std::string> stop_and_dis = {distance, new_stop};
    tramlines[line].insert(stop_and_dis);
    std::cout << "Stop was added." << std::endl;
    return;
}

// Poistaa jonkun pysäkin kokonaan tietokannasta
void remove_stop(Tramlines& tramlines, const std::string& stop)
{

    // Tarkistetaan löytyykö poistettavaa
    // pysäkkiä tietokannasta
    bool stop_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                stop_found = true;
            }
        }
    }

    // Jos ei löytynyt
    // tulostettaan virheilmoitus
    // ja poistutaan funktiosta
    if (!stop_found)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
        return;
    }

    // Muuten käydään tietokanta läpi ja poistetaan
    // pysäkki kaikilta linjoilta
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                tramlines.at(lines.first).erase(s.first);
            }
        }
    }
    std::cout << "Stop was removed from all lines." << std::endl;
    return;
}

// Käyttöliittymä, jossa kysytään käyttäjältä
// komentoa ja sen parametrejä
bool interface(std::string file_name)
{
    Tramlines tramlines;

    // Tallennetaan data tiedostota
    // Jos tallennuksessa tapahtui virhe
    // poistutaan funktiosta
    if (!save_data(tramlines, file_name))
    {
        return false;
    }
    while(true)
    {

        // Kysytään käyttäjältä komentoa
        std::string full_command;
        std::cout << "tramway> ";
        getline(std::cin, full_command);

        // Jaetaan komento osiin
        std::vector<std::string> command_parts = split(full_command, ' ');

        // Jos komennoksi ei annettu mitään,
        // siirrytään uudelle silmukan kierrokselle
        if (command_parts.size() == 0)
        {
            continue;
        }

        // Ensimmäinen osa syötteestä on itse komento
        std::string command = command_parts.at(0);

        // Tarkistetaan mikä komento oli.
        // Jos komento on QUIT ohjelman suoritus lopetetaan.
        // Muuten arkistetaan komentojen kohdalla erikseen
        // oliko komennolla tarpeeksi parameterjä.
        // Jos oli liian vähän parametrejä
        // tulostettaan virheilmoitus
        // ja jatketaan silmukkaa.
        // Jokaisella komennolla kutsutaan omaa funktiota,
        // joka toteuttaa komennon toiminnon
        if (same_command("QUIT", command))
        {
            break;
        }
        else if (same_command("LINES", command))
        {
            print_lines(tramlines);
        }
        else if (same_command("LINE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                print_line_stops(tramlines, line);
            }
        }
        else if (same_command("STOPS", command))
        {
            print_stops(tramlines);
        }
        else if (same_command("STOP", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string stop = command_parts.at(1);
                print_stop_lines(tramlines, stop);
            }
        }
        else if (same_command("DISTANCE", command))
        {
            if (command_parts.size() < 4)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                std::string stop1 = command_parts.at(2);
                std::string stop2 = command_parts.at(3);
                print_distance_between_stops(tramlines, line, stop1, stop2);
            }

        }
        else if (same_command("ADDLINE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                add_line(tramlines, line);
            }
        }
        else if (same_command("ADDSTOP", command))
        {
            if (command_parts.size() < 4)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                std::string new_stop = command_parts.at(2);
                double distance = stod(command_parts.at(3));
                add_stop(tramlines, line, new_stop, distance);
            }

        }
        else if (same_command("REMOVE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string stop = command_parts.at(1);
                remove_stop(tramlines, stop);
            }
        }

        // Jos komento ei ollut mikään määritellyistä
        // tulostettaan virheilmoitus
        else
        {
            std::cout << "Error: Invalid input." << std::endl;
        }
    }
    return true;
}

// Lyhyt ja ytimekäs main.
int main()
{

    // Tulostetaan RASSE
    print_rasse();

    // Pyydetään tiedoston nimeö
    std::string file_name = read_file_name();

    // Tarkistetaan tiedoston datan oikeellisuus
    // ja sen mukaan palautetaan joko
    // EXIT_SUCCESS tai EXIT_FAILURe
    if (check_data(file_name))
    {
        if (interface(file_name))
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;

}
