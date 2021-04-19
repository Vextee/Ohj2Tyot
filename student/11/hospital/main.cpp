/* Sairaala
 *
 * Kuvaus:
 * Ohjelmassa toteutetaan sairaalan tietokanta, joka sisältää potilaita,
 * henkilökuntaa, hoitojaksoja ja lääkkeitä. Potilaita voidaan lisätä teitokantaan
 * tai poistaa sieltä. Kun potilas lisätään, luodaan myös uusi hoitojakso.
 * Potilaan poistuessa hoitojakso lopetetaan eli sen päättymispäivämäärksi
 * asetetaan se päivä, jona potilas poistui sairaalasta. Henkilökuntaa
 * voi asettaa, jollekin tietylle sairaalassa olevalle potilaalle,
 * jolloin henkilökunnan jäsen työskentelee potilaan
 * aktiivisella hoitojaksolla. Potilaille voidaan myös asettaa ja poistaa
 * reseptilääkkeittä. Ohjelmassa on myös mahdollista tulostaa yhden
 * potilaan tiedot, yhden henkilökunnan jäsenen kaikki hoitojaksot,
 * kaikkien potilaiden tiedot, jotka ovat koskaan olleet sairaallassa,
 * kaikkien tällä hetkellä sairaalassa olevien potilaiden tiedot sekä
 * kaikki asetetut lääkkeet ja kenelle ne on asetettu.
 *
 * Ohjelman kirjoittaja
 * Nimi: Veikko Svanstrom
 * Opiskelijanumero: 50149539
 * Kayttajatunnus: scvesv
 * E-Mail: veikko.svanstrom@tuni.fi
 */


#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    // Luodaan uusi sairaalaolio
    Hospital* hospital = new Hospital();
    // Siirrytään cli luokkaan
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    // Lopuksi poistetaan sairaalaolio
    delete hospital;
    return EXIT_SUCCESS;
}
