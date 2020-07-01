#ifndef FUNZIONIMONOPOLI_H_INCLUDED
#define FUNZIONIMONOPOLI_H_INCLUDED
/**INCLUSIONE LIBRERIE*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
/**DEFINIZIONE COSTANTI*/
#define MOLTIPLICATORE_PEDAGGIO 70000 // +Costante utilzzata per velocizzare la  partita
#define MRANDOM 0    //+Modalita random
#define MCONQUISTA 1 //+Modalita conquista
#define NGIOCMIN 2   //+Numero giocatori minimo
#define NGIOCMAX 8   //+Numero giocatori massimo
#define NTURNIBAGNO 3//+Numero di turni da passare in bagno nel caso ci si ritrovi nella casella BATCAVERNA
#define LIMITEDPP 3 // +Limite doppia dadi
#define DIVPASS 20  // +Costante utilizzata per ricavere il valore del costo passaggio di ogni aula
#define SCRPASS 10  // +Costante utilizzata per ricavere il valore del costo passaggio con scrivania di ogni aula
#define TNDPASS 5   // +Costante utilizzata per ricavere il valore del costo passaggio con tenda di ogni aula
#define PMIN 1   // +PMIN e PMAX indicano la probabilita di ottenere una scrivania in modalita 0
#define PMAX 3   // Allargando o diminuendo il range di valori varia con essi la probabilita
#define DADOMIN 1  //+Valore minimo di un dado
#define DADOMAX 6 // +Valore massimo di un dado
#define NAULE 40  // +Numero caselle del tabellone
#define NAULEAQUISTABILI 24 //+Numero aule acquistabili dai giocatori
#define NTIPISFIGHE 4 //+Numero tipi di sfiga
#define MAXLENGTHFRASE 200  //+Grandezza massima di una frase contenuta in una sfiga
#define GS 23              //+Grandezza massima delle stringhe nome e nome terreno
#define BANCA 12000 //+Soldi da distribuire ai giocatori
#define IDBANCO -1  //+Identificatore banco
#define SCRIVANIA 50//+Costo scrivania
#define TENDA 100   //+Costo tenda
#define PGO 0         //+Coordinate casella via
#define PBAGNI 10     //+Coordinate casella bagni
#define PBATCAVERNA 30//+Coordinate BATCAVERNA
/**DEFINIZIONE STRUTTURE E ENUMERAZIONI*/
typedef enum{aula,tassa,sfiga,other}TipoAula;                               //Enumerazioni che rappresenta i tipi di caselle che sono presenti nel tabellone
typedef enum{candela,mela,pera,ciliegia,banana,jack_D,wine,birra}Segnaposto;//Enumerazione che rappresenta i segnaposto dei giocatori
typedef enum{tassaSemplice,tassaImmobile,BattutaMartina,GoTo}tipoSfiga;     //Enumerazione che rappresenta i tipi di sfiga presenti nel mazzo
//Struttura dei dettagli della partita
typedef struct{
int nGiocatori;
int nTurni;
int gAttivo;
}Partita;
//Lista contenente gli id delle aule possedute dal giocatore
struct aulaPosseduta{
    int idA;
    struct aulaPosseduta *next;
    struct aulaPosseduta *beck;
};
typedef struct aulaPosseduta aulaPosseduta;
//Struttura del giocatore nel file di caricamento
typedef struct{
char nome[GS+1];
Segnaposto S;
int soldi;
int puliziaBagni;
int numeroAule;
int posizione;
}strSalvaGiocatore;
//Struttura del giocatore durante la partita
typedef struct{
char nome[GS+1];
Segnaposto S;
int soldi;
int puliziaBagni;
int numeroAule;
int posizione;
aulaPosseduta *listaAule;
}Giocatore;
//Struttura delle caselle del tabellone
typedef struct{
int costo;
int costoPassaggio;
int passaggScrivania;
int passaggTenda;
char nomeAula[GS+1];
TipoAula tipoAula;
_Bool Scrivania;
_Bool Tenda;
int proprietario;
}Aula;
//Struttura tabellone utilizata nell inizializzazione del tabellone per poterlo tornare come singolo elemento
typedef struct{
Aula Tabellone[NAULE];
}Tab;
//Struttura delle sfighe
typedef struct{
tipoSfiga tipo;
int tassaOrJump;
int tassaScrivania;
int tassaTende;
char frase[MAXLENGTHFRASE+1];
}Sfighe;
/** DICHIARAZIONE FUNZIONI:**/
/**FUNZIONI DI STAMPA*/
char stampaMenuPrincipale(void);                     //Funzione di stampa del menu principale
void stampaCasella(Aula, Giocatore[]);               //Fnzione che stampa la casella passata
void stampaDettagliP(int, Partita, Giocatore[]);     //Funzione di stampa dettagli partita e del giocatore di turno
char stampaMenuGioco( Partita, Giocatore[], Aula[]); //Funzione di stampa menu della partita
/** FUNZIONI PER GESTIRE LE LISTE **/
aulaPosseduta* addAula(aulaPosseduta*, int);  //Funzione per aggiungere aule alla lista delle aule possedute
void eraseList(aulaPosseduta*);               //Funzione per eliminare la lista ricorsivamente
/** FUNZIONI PER GESTIRE I SEGNAPOSTI**/
void stampaSegnaposto(Segnaposto);             //Funzione che stampa i segnaposti definiti dall enumerazione Segnaposto
_Bool ctrlSegnap(int, Segnaposto, Giocatore[]);//Funzione che controlla se il segnaposto e utilizato da qualcuno o no
void segnaPliberi(int, Giocatore[]);           //Funzione che stampa i segnaposti liberi
/** FUNZIONI INIZZIALIZAZZIONE PARTITA**/
void popolaGioc(int, Giocatore[]);             //Funzione utilizzata nella creazione di una nuova partita e popola il vettore di giocatori
void assAuleRand(int, Giocatore[], Aula[]);    //Funzione utilizzata nella creazione di una nuova partita in modalita 0 e assegna le aule casualmente
Giocatore* CreaPartita(Partita*, int*, Aula[]);//Funzione che crea una nuova partita
/**FUNZIONI DI SALVATAGGIO PARTITA*/
strSalvaGiocatore* SalvaStrutturaG(int, Giocatore[]);         //Funzione che trasforma la struttura Giocatore in strSalvaGiocatore
Giocatore *CaricaStrutturaG(int, strSalvaGiocatore[], Aula[]);//Funzione che trasforma la struttura strSalvaGiocatore in Giocatore
void SalvaPartita(Partita,Giocatore[], Aula[], int);          //Funzione che salva la partita in un file binario permette il salvataggio di tre partite differenti definiti come blocchi
Giocatore* CaricaPartita(Partita*, Aula[], int*);             //Funzione che carica la partita da un file binario permette il caricamento di tre partite differenti definiti come blocchi
/**FUNZIONI GESTIONE SFIGHE*/
Sfighe* inizializzaSfighe(int*);  //Funzione che carica le sfighe da un file di testo
void mischiaSfighe(int, Sfighe[]);//Funzione che mischia le sfighe come un mazzo di carte
Sfighe pescaSfiga(int, Sfighe[]); //Funzione che pesca una sfiga, a ogni chiamata viene pescata la sfiga successiva tramite l utilizzo di un contatore static
/**FUNZIONI GESTIONE PARTITA*/
void sceltaAzione(int, int, Partita, Giocatore[], Aula[], Sfighe[]); //Controlla l'azione che effetua l'utente nel menu gioco
void ControllaGiocatoriEliminati(Partita*, Giocatore[], Aula[]);     //Funzione che controlla e elimina i giocatori in bancarotta e gestisce li eventuali cambi di id
int ContaScr(aulaPosseduta*, Aula[]);                                //Funzione che conta le scrivanie del giocatore
int ContaTnd(aulaPosseduta*, Aula[]);                                //Funzione che conta le tende del giocatore
void Spostamento(int, Partita, Giocatore[], Aula[]);                 //Funzione che simula l'avanzamento nel tabellone e il superamento del via
void AvanzaTurno(Partita*, Giocatore[], Aula[]);                     //Funzione che gestisce il cambio turno
void CasoAulaGiocatore(Partita, Giocatore[], Aula[]);                //Funzione contenete le attivita da effetuare se l aula e di un giocatore
void casoAulaBanco(int, Partita, Giocatore[], Aula[]);               //Funzione contenete le attivita da effetuare se l aula e del banco
void CasoAula(int, Partita, Giocatore[], Aula[]);                    //Funzione contenente le attivita da effetuare nel caso il giocatore finisca in un aula
void CasoTassa(Partita, Giocatore[], Aula[]);                        //Funzione contenente le attivita da effetuare nel caso il giocatore finisca in una casella di tipo tassa
void CasoSfiga(int, int, Partita, Giocatore[], Aula[], Sfighe[]);    //Funzione contenente le attivita da effetuare nel caso il giocatore finisca in una casella di tipo sfiga
void AzioneCasella(int, int, Partita, Giocatore[], Aula[], Sfighe[]);//Funzioni contenete i controlli per definire il tipo di casella in cui si trova il giocatore
void TiraDadi(int, int, Partita, Giocatore[], Aula[], Sfighe[]);     //Funzione che simula il lancio dei dadi e effetua i controlli relativi a questi
void ChiudiPartita(int, Giocatore[], Sfighe[]);                      //Funzione che disalloca tutta la memoria Heap utilizata
/**FUNZIONE GIOCO*/
void Monopoly(int,int, Partita, Giocatore[], Aula[], Sfighe[]);//Funzione che contiene la partita
/**TABELLONE*/
Tab inizializzaTabellone(void);//funzione che contiene e inizializza il tabellone

#endif // FUNZIONIMONOPOLI_H_INCLUDED
