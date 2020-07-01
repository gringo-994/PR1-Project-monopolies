#include "FunzioniMonopoli.h"

int main()
{
  int modalita; //modalita partita
  Partita detPartita;
  Giocatore *giocatori = NULL;
  Sfighe *sfighe = NULL;
  int numeroSfigheT;//numero totale di sfighe


  Tab T=inizializzaTabellone(); //Inizializazione tabellone
  srand(time(NULL));

   switch(stampaMenuPrincipale())//stampa menu principale a seconda della decisione dell utente
    {
      case 'N':
      case 'n':
        giocatori = CreaPartita( &detPartita, &modalita, T.Tabellone); // avvio creazione nuova partita
        break;
      case 'C':
      case 'c':
        giocatori = CaricaPartita( &detPartita, T.Tabellone, &modalita);// avvio caricamento partita
        break;
    }
  sfighe = inizializzaSfighe( &numeroSfigheT);  //inizializza mazzo di sfighe
  mischiaSfighe(numeroSfigheT, sfighe);         //mischia mazzo di sfighe
  Monopoly(numeroSfigheT,modalita,detPartita,giocatori,T.Tabellone,sfighe); // avvio inizio partita


  return 0;
}
