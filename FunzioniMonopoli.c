#include "FunzioniMonopoli.h"
/**FUNZIONI DI STAMPA*/
char stampaMenuPrincipale(void)
{
 char azione;
  do {
    printf("+-----------------------------------------------------------------+\n\n");
    printf("\t                  * M O N O P O L Y *     \n\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("\t                  [N] Nuova partita  \n");
    printf("\t                  [C] Carica partita \n");
    printf("+-----------------------------------------------------------------+\n");
    scanf("%c", &azione);
    getchar();
    if (!(azione == 'n' || azione == 'N' || azione == 'c' || azione == 'C')) printf("ERRORE: opzione inesistente\n");
      } while (!(azione == 'n' || azione == 'N' || azione == 'c' || azione == 'C'));
    //stampa il menu sinche non viene selezionata almeno una delle operazioni presenti

    return azione; //ritorna la scelta dell utente
}
void stampaCasella(Aula casella, Giocatore giocatori[])
{
    printf("\t\t+------------------------------------------+\n");
    printf("\t\t|         %15s                  |", casella.nomeAula);
    printf("\n\t\t+------------------------------------------+");
    printf("\n\t\t|Costo acquisto:           %15dE|", casella.costo);
    printf("\n\t\t|Costo passaggio:          %15dE|", casella.costoPassaggio);
    if (casella.tipoAula == aula)
    {
      printf("\n\t\t|Costo passaggio Scrivania:%15dE|", casella.passaggScrivania);
      printf("\n\t\t|Costo passaggio Tenda:    %15dE|", casella.passaggTenda);
      if (casella.proprietario != IDBANCO)
      {
      printf("\n\t\t|Proprietario:              %15s|", giocatori[casella.proprietario].nome);
      }
    else printf("\n\t\t|Proprietario:\t\t\t      Banco|");
    }
    if (casella.Scrivania) printf("\n\t\t|Scrivania presente!\t\t\t   |");
    else if (casella.Tenda) printf("\n\t\t|Tenda presente!\t\t\t   |");
    printf("\n\t\t+------------------------------------------+\n");
  }
void stampaDettagliP(int modalita, Partita detPartita, Giocatore giocatori[])
{
      printf("+-----------------------------------------------------------------+\n");
      printf("\t\t\t  *M O N O P O L Y*\n");
      printf("+-----------------------------------------------------------------+\n");
      printf("+-----------------------------------------------------------------+\n");
      printf("+---------------------------+\t      +---------------------------+\n");
      printf("| DETTAGLI GIOCATORE        |\t      |DETTAGLI PARTITA           |\n");
      printf("+---------------------------+\t      +---------------------------+\n");
      printf("|Turno:\t     %15s|", giocatori[detPartita.gAttivo].nome);
      if (modalita) printf("\t      |modalita: conquista        |\n");
      else printf("\t      |modalita: Random           |\n");

      printf("|soldi:      %15d|\t      |Numero giocatori:%d\t  |\n", giocatori[detPartita.gAttivo].soldi, detPartita.nGiocatori);
      printf("|Segnaposto:");
      stampaSegnaposto(giocatori[detPartita.gAttivo].S);
      printf("\t    |\t      |Numero turni:%d\t\t  |\n", detPartita.nTurni);
      printf("+---------------------------+\t      +---------------------------+\n");

      printf("+-----------------------------------------------------------------+");
}
char stampaMenuGioco( Partita detPartita, Giocatore giocatori[], Aula Tabellone[])
{
     char azione;
      printf("\n+-----------------------------------------------------------------+");
      printf("\n[T]Tira dadi.\t\t[S] Salva partita\t\t[Q]Esci\n");
      printf("+-----------------------------------------------------------------+\n");
      stampaCasella(Tabellone[giocatori[detPartita.gAttivo].posizione], giocatori);
      scanf("%c", &azione);
      getchar();
      return azione; //viene restituita il valore dell azione che si vuole effettuare
}
/** FUNZIONI PER GESTIRE LE LISTE **/
aulaPosseduta *addAula(aulaPosseduta *firstElement, int idNuovaAula)
{
  aulaPosseduta * newElement = NULL;

  newElement = (aulaPosseduta * ) malloc(sizeof(aulaPosseduta)); //Allocazione di un elemento
  if (newElement == NULL) exit(-1);
  if (firstElement == NULL) // controlla se il nuovo elemento sara il primo
  {
    newElement->next = NULL;
    newElement->beck = NULL;
  }
  else //se non è il primo elemento viene collegato all'elemento precedente
  {
    newElement->next = firstElement;
    newElement->beck = firstElement->beck;
    firstElement->beck = newElement;
  }
  newElement->idA = idNuovaAula; //settaggio campo informazione del primo elemento
  return newElement;   //restituzione del nuovo primo elemento
}
void eraseList(aulaPosseduta *Element)
{
    if (Element != NULL) // controlla se la lista è arrivata alla fine
    {
      eraseList(Element = Element->next); //  passa a se stessa l'elemento successivo
      free(Element); //disallocazone dell'elemento
    }
}
/** FUNZIONI PER GESTIRE I SEGNAPOSTI**/
void stampaSegnaposto(Segnaposto n)
{
  switch (n)
  {
    case candela:
      printf("candela");
      break;
    case mela:
      printf("mela");
      break;
    case pera:
      printf("pera");
      break;
    case ciliegia:
      printf("ciliegia");
      break;
    case banana:
      printf("banana");
      break;
    case jack_D:
      printf("Jack_D");
      break;
    case wine:
      printf("wine");
      break;
    case birra:
      printf("birra");
      break;
  }
}
_Bool ctrlSegnap(int nGiocatori, Segnaposto segnaposto, Giocatore giocatori[])
{
  int j;
  for (j = 0; j < nGiocatori; j++)
    if (giocatori[j].S == segnaposto) return false; //se il segnaposto è utilizzato ritorna false
  return true; //se il segnaposto non è utilizzato da nessuno ritorna true
}
void segnaPliberi(int nGiocatori, Giocatore giocatori[])
{
    int i;
    for (i = 0; i < 8; i++)
      if (ctrlSegnap(nGiocatori, i, giocatori)) { //controllo se il relativo segnaposto e libero e lo stampo
        printf("[%d]", i);
        stampaSegnaposto(i);
        printf("\n");
      }
}
/** FUNZIONI INIZIALIZZAZIONE PARTITA**/
void popolaGioc(int nGiocatori, Giocatore giocatori[])
{
  int i, scelta;
  _Bool flagCtrl; // variabile utilizata per controllare se il segnaposto e utilizato da qualche giocatore
  /*inizializza i segnaposto a -1 valore
  che non rappresenta nessun segnaposto altrimenti
  il segnaposto 0 risultera occupato*/
  for (i = 0; i < nGiocatori; i++) giocatori[i].S=-1;
  for (i = 0; i < nGiocatori; i++)
  {
    printf("+-----------------------------------------------------------------+\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("\t\tInformazioni Giocatore %d\n", i);
    printf("+-----------------------------------------------------------------+\n");
    printf("+-----------------------------------------------------------------+\n");
     printf("\nnome:\t");
    scanf("%s", giocatori[i].nome);
    printf("\n+-----------------------------------------------------------------+\n");
    printf("segnaposti liberi:\n");
    printf("+-----------------------------------------------------------------+\n");
    segnaPliberi(nGiocatori, giocatori);
    printf("+-----------------------------------------------------------------+\n");
   do {
      printf("scegli segnaposto:\t");
      scanf("%d", &scelta);
      getchar();
      flagCtrl = ctrlSegnap(nGiocatori, scelta, giocatori);
      if (flagCtrl == false || scelta < 0 || scelta > 7) printf("ERRORE:Segnaposto gia in uso o inesistente!!!\n");
    } while (flagCtrl == false || scelta < 0 || scelta > 7);//stampa il menu di scelta segnaposto sin che il segnaposto non è valido
    /*settaggio informazioni giocatore */
    giocatori[i].S = scelta;
    giocatori[i].soldi = BANCA / nGiocatori; //soldi iniziali
    giocatori[i].numeroAule = 0;
    giocatori[i].puliziaBagni = 0;
    giocatori[i].posizione = PGO; //coordinate posizione via
    giocatori[i].listaAule = NULL;
  }
}
void assAuleRand(int nGiocatori, Giocatore giocatori[], Aula Tabellone[])
{
  int i;
  int presaPossesso; // contiene l'id Random del giocatore che si impossesera dell'aula
  int possScr;
  int nAule = NAULEAQUISTABILI / nGiocatori;  // numero aule
  int nAuleR = NAULEAQUISTABILI % nGiocatori; //aule in piu rimanenti

  for (i = 0; i < NAULE; i++)
  {
    if (Tabellone[i].tipoAula == aula) //se la casella è un aula
    {
      presaPossesso = 0 + rand() % nGiocatori; //generazione id giocatore random
      // il giocatore si impossessa il territorio solo se ci sono aule in piu o nel caso non abbia ancora raggiunto il numero di aule per giocatori
      if (giocatori[presaPossesso].numeroAule < nAule || giocatori[presaPossesso].numeroAule < nAule + 1 && nAuleR>0)
      {
        Tabellone[i].proprietario = presaPossesso;
        possScr = PMIN + rand() % (PMAX - PMIN + 1); //generazione numero casuale per ottenere scrivania gratis
        if (possScr ==PMAX ) Tabellone[i].Scrivania = true; //solo se il valore generato è uguale a PMAX il giocatore ottiene la scrivania
        giocatori[presaPossesso].listaAule = addAula(giocatori[presaPossesso].listaAule, i); //aggiunge l'aula alla lista delle aule possedute da giocatore
        giocatori[presaPossesso].numeroAule++;
        if(giocatori[presaPossesso].numeroAule > nAule) nAuleR--; //se e un aula in piu per il giocatore le aule in piu diminuiscono
        giocatori[presaPossesso].soldi -= Tabellone[i].costo; //viene rimosso il costo dell' aula dai soldi del giocatore
      } else i--; //se il giocatore non puo possedere l aula viene ricercato un nuovo giocatore per possedere l aula
    }
  }
}
Giocatore *CreaPartita(Partita *detPartita, int *modalita, Aula Tabellone[])
{
    Giocatore *giocatori = NULL;
    do {
      printf("\t\t+---------------------+\n");
      printf("\t\t|     MODALITA        |\n");
      printf("\t\t|_ _ _ _ _ _ _ _ _ _ _|\n");
      printf("\t\t|[0]modalita semplice |\n\t\t|[1]modalita conquista|\n");
      printf("\t\t+---------------------+\n");
      printf("\n\nscegli modalita:\t");
      scanf("%d", modalita);
      printf("\ninserisci numero giocatori(min:2 / max:8):\t");
      scanf("%d", &detPartita->nGiocatori);
      if (detPartita->nGiocatori < NGIOCMIN || detPartita->nGiocatori > NGIOCMAX || ( *modalita != MCONQUISTA && *modalita != MRANDOM)) printf("ERRORE:modalita o giocatori errati\n");
    } while (detPartita->nGiocatori < NGIOCMIN || detPartita->nGiocatori > NGIOCMAX || ( *modalita != MCONQUISTA && *modalita != MRANDOM));// se i dati non sono esatti ne ricchiede l inserimento
    /*settaggio dettagli partita*/
    detPartita->nTurni = 0;
    detPartita->gAttivo = 0;
    giocatori = (Giocatore* ) malloc(detPartita->nGiocatori * sizeof(Giocatore)); //allocca dinamicamente i giocatori nello Heap
    if (giocatori == NULL) exit(-1);
    popolaGioc(detPartita->nGiocatori, giocatori); // popolo l array di giocatori
    if ( *modalita == MRANDOM) assAuleRand(detPartita->nGiocatori, giocatori, Tabellone);//nel caso la modalita sia random assegna le aule casualmente
    return giocatori; // ritorna i giocatori
}
/**FUNZIONI DI SALVATAGGIO E CARICA PARTITA*/
strSalvaGiocatore *SalvaStrutturaG(int nGiocatori, Giocatore giocatori[])
{
  int i;
  strSalvaGiocatore *giocatoriS = NULL;

  giocatoriS = (strSalvaGiocatore* ) malloc(nGiocatori * sizeof(strSalvaGiocatore)); //allocca un array, nell'Heap, di giocatori utilizati per creare il file di salvataggio
  if (giocatoriS == NULL) exit(-1);
  for (i = 0; i < nGiocatori; i++) {
    strcpy(giocatoriS[i].nome, giocatori[i].nome);
    /*copia i valori dei giocatori nel nuovo array tranne la lista delle aule possedute*/
    giocatoriS[i].S = giocatori[i].S;
    giocatoriS[i].soldi = giocatori[i].soldi;
    giocatoriS[i].puliziaBagni = giocatori[i].puliziaBagni;
    giocatoriS[i].numeroAule = giocatori[i].numeroAule;
    giocatoriS[i].posizione = giocatori[i].posizione;
  }
  return giocatoriS;
}
Giocatore *CaricaStrutturaG(int nGiocatori, strSalvaGiocatore giocatoriC[], Aula Tabellone[])
{
  int i, j;
  Giocatore *giocatori = NULL;

  giocatori = (Giocatore* ) malloc(nGiocatori * sizeof(Giocatore));// allocca un array di giocatori utilizati nella partita
  if (giocatori == NULL) exit(-1);
  for (i = 0; i < nGiocatori; i++) {
    /* coppia le informazioni di ogni giocatore nella nuova struttura*/
    strcpy(giocatori[i].nome, giocatoriC[i].nome);
    giocatori[i].S = giocatoriC[i].S;
    giocatori[i].soldi = giocatoriC[i].soldi;
    giocatori[i].puliziaBagni = giocatoriC[i].puliziaBagni;
    giocatori[i].numeroAule = giocatoriC[i].numeroAule;
    giocatori[i].posizione = giocatoriC[i].posizione;
    giocatori[i].listaAule = NULL;
    for (j = 0; j < NAULE; j++) //per ogni giocatore cerca nel tabellone le aule possedute e le carica nella lista
      if (Tabellone[j].proprietario == i) giocatori[i].listaAule = addAula(giocatori[i].listaAule, j);
  }
  return giocatori;
}
void SalvaPartita(Partita detPartita, Giocatore giocatori[], Aula Tabellone[], int modalita)
{
  int scelta;
  strSalvaGiocatore *giocatoriS = SalvaStrutturaG(detPartita.nGiocatori, giocatori); //crea la nuova struttura giocatori per salvare
  FILE *fp = NULL;

  do {
      printf("Scegli blocco di memoria da sovrascrivere:\n");
      printf("\t\t+----------+\n");
      printf("\t\t|[1]BLOCCO1|\n\t\t|[2]BLOCCO2|\n\t\t|[3]BLOCCO3|\n");
      printf("\t\t+----------+\n");
      scanf("%d", &scelta);
      getchar();
      switch (scelta) // si possono memorizare sino a un massimo di tre partite
      {
        case 1:
          fp = fopen("Data/Blocco1.bin", "w+b");
          break;
        case 2:
          fp = fopen("Data/Blocco2.bin", "w+b");
          break;
        case 3:
          fp = fopen("Data/Blocco3.bin", "w+b");
          break;
          default: printf("ERRORE:Blocco selezionato non disponibile\n");
          break;
      }
     } while(scelta < 1 || scelta > 3);
  if (fp == NULL) exit(-1);
  //scrive il file binario relativo al salvataggio
  fwrite( &detPartita, sizeof(Partita), 1, fp);
  fwrite(giocatoriS, sizeof(strSalvaGiocatore), detPartita.nGiocatori, fp);
  fwrite(Tabellone, sizeof(Aula), NAULE, fp);
  fwrite( &modalita, sizeof(int), 1, fp);
  fclose(fp);
  free(giocatoriS); //disallocca la memoria utilizata dalle strutture giocatori al salvataggio
}
Giocatore *CaricaPartita(Partita *detPartita, Aula Tabellone[], int *modalita)
{
    int scelta;
    strSalvaGiocatore *giocatoriC = NULL;
    Giocatore *giocatori = NULL;
    FILE *fp = NULL;

    do {
        printf("Scegli partita da caricare:\n");
        printf("\t\t+----------+\n");
        printf("\t\t|[1]BLOCCO1|\n\t\t|[2]BLOCCO2|\n\t\t|[3]BLOCCO3|\n");
        printf("\t\t+----------+\n");
        scanf("%d", &scelta);
        getchar();
        switch (scelta)// permette di caricare la partita da '3 blocchi' di memoria diferenti
        {
          case 1:
            fp = fopen("Data/Blocco1.bin", "r+b");
            if (fp == NULL) printf("nessun salvataggio presente\n");
            break;
          case 2:
            fp = fopen("Data/Blocco2.bin", "r+b");
            if (fp == NULL) printf("nessun salvataggio presente\n");
            break;
          case 3:
            fp = fopen("Data/Blocco3.bin", "r+b");
            if (fp == NULL) printf("nessun salvataggio presente\n");
            break;
          default:
            printf("ERRORE:blocco inesistente\n");
            break;
        }
       } while(scelta < 1 || scelta > 3 || fp==NULL);
    /*carica la partita presente nel file di salvataggio binario*/
    fread(detPartita, sizeof(Partita), 1, fp);
    giocatoriC = (strSalvaGiocatore* ) malloc(detPartita->nGiocatori * sizeof(strSalvaGiocatore));//alloca lo spazio per i giocatori presenti nel file di salvataggio
    if (giocatoriC == NULL) exit(-1);
    fread(giocatoriC, sizeof(strSalvaGiocatore), detPartita->nGiocatori, fp);
    fread(Tabellone, sizeof(Aula), NAULE, fp);
    giocatori = CaricaStrutturaG(detPartita->nGiocatori, giocatoriC, Tabellone);//viene create l array dei giocatori per la partita
    fread(modalita, sizeof(int), 1, fp);
    fclose(fp);
    free(giocatoriC);//viene liberato lo spazio dell Heap occupato dall array di giocatori del file di salvataggio
    return giocatori;
}
/**FUNZIONI GESTIONE SFIGHE*/
Sfighe *inizializzaSfighe(int *numeroSfigheT)
{
  FILE *fp = fopen("ListaSfighe.txt", "r");
  int i, j, z = 0;
  int numeroSfighe[NTIPISFIGHE]; //array contenente il numero di sfighe per tipo
  Sfighe *sfighe = NULL; *numeroSfigheT = 0;

  //vengono caricati il numero di sfighe per tipo
  fscanf(fp, "%d %d %d %d", &numeroSfighe[0], &numeroSfighe[1], &numeroSfighe[2], &numeroSfighe[3]);
  for (i = 0; i < NTIPISFIGHE; i++) *numeroSfigheT += numeroSfighe[i];// sommando il numero di sfighe per tipo se ne ottiene il totale
  sfighe = (Sfighe* ) malloc(( *numeroSfigheT) * sizeof(Sfighe));//viene alloccato dinamicamente un array di sfighe
  if (sfighe == NULL) exit(-1);
  /*per ogni tipo di sfiga:
   vengono estratti il numero di sfighe corrispondenti.
   tramite un contatore z indipendente dalle inizializzazioni del
   for, scorre  il vettore delle sfighe e ne inizializza i campi*/
  for (i = 0; i < NTIPISFIGHE; i++)
    for (j = 0; j < numeroSfighe[i]; j++) {
      sfighe[z].tipo = i;//viene assegnato il tipo di sfiga
      switch (sfighe[z].tipo) //a seconda del tipo di sfiga vengono estratti i campi utili dal file
      {
        case tassaSemplice:
          {
            fscanf(fp, "%d ", &sfighe[z].tassaOrJump);
            sfighe[z].tassaScrivania = 0;
            sfighe[z].tassaTende = 0;
            fscanf(fp, "%[^\n]s", sfighe[z].frase);
            break;
          }
        case tassaImmobile:
          {
            fscanf(fp, "%d %d %d ", & sfighe[z].tassaOrJump, & sfighe[z].tassaScrivania, & sfighe[z].tassaTende);
            fscanf(fp, "%[^\n]s", sfighe[z].frase);
            break;
          }
        case BattutaMartina:
          {
            sfighe[z].tassaOrJump = 0;
            sfighe[z].tassaScrivania = 0;
            sfighe[z].tassaTende = 0;
            fscanf(fp, " %[^\n]s.", sfighe[z].frase);
            break;
          }
        case GoTo:
          {
            fscanf(fp, "%d ", &sfighe[z].tassaOrJump);
            sfighe[z].tassaScrivania = 0;
            sfighe[z].tassaTende = 0;
            fscanf(fp, "%[^\n]s", sfighe[z].frase);
            break;
          }
      }z++;//contantore indipendente dal for per caricare ordinatamente l array di sfighe
    }
  fclose(fp);
  return sfighe;
}
void mischiaSfighe(int numeroSfigheT, Sfighe sfighe[])
{
  int i = 0;
  int j = numeroSfigheT - 1;
  int posRand;
  Sfighe sfigheApp;
  /*ciclo a due indici rispettivamente inizializati uno all inizio e l altro alla fine dell array sfiga,
    ogni sfiga analizata (sia dall'indice iniziale che finale)
    viene scambiata con una sfiga random presente nel mazzo */
  while(i < numeroSfigheT)
  {
    sfigheApp = sfighe[i];
    posRand = 0 + rand() % numeroSfigheT;
    sfighe[i] = sfighe[posRand];
    sfighe[posRand] = sfigheApp;
    sfigheApp = sfighe[j];
    posRand = 0 + rand() % numeroSfigheT;
    sfighe[j] = sfighe[posRand];
    sfighe[posRand] = sfigheApp;
    j--;
    i++;
  }
}
Sfighe pescaSfiga(int numeroSfigheT, Sfighe sfighe[])
{
    static int i = 0; // variabile static inizializata solo alla prima chiamata
    Sfighe SfigaP = sfighe[i]; //pesca sfiga
    if (i == numeroSfigheT - 1) i = 0;// nel caso di fine mazzo l indice si riporta all inizio di questo
    else i++;                         // a ogni chiamata l indice viene portato avanti
    return SfigaP; //viene restituita la sfiga pescata
}
/**FUNZIONI GESTIONE PARTITA*/
void sceltaAzione(int numeroSfigheT, int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[], Sfighe sfighe[])
{
      char risp;
      char azione;

      do {
          azione = stampaMenuGioco(detPartita, giocatori, Tabellone);
          switch (azione)// base all azione viene avviata la funzione relativa
          {
            case 'S':
            case 's':
              SalvaPartita( detPartita, giocatori, Tabellone, modalita);//salva partita
              break;
            case 'T':
            case 't':
              TiraDadi(numeroSfigheT, modalita, detPartita, giocatori, Tabellone, sfighe);//Tira Dadi
              break;
            case 'Q':
            case 'q'://esci dalla partita
              {
                printf("\n\nVuoi salvare la partita?[Y/N]:\t");
                scanf("%c", &risp);
                getchar();
                if (risp == 'y' || risp == 'Y') SalvaPartita( detPartita, giocatori, Tabellone, modalita);
                ChiudiPartita(detPartita.nGiocatori, giocatori, sfighe);
                exit(0);
                break;
              }
              default: printf("ERRORE!opzione inesistente\n");
          }
       //finche l'azione eseguita non riguarda il lancio dei dadi,allora l'utente continuera a effetture una delle tre scelte
       } while (azione != 't' && azione != 'T');
}
void ControllaGiocatoriEliminati(Partita *detPartita, Giocatore giocatori[], Aula Tabellone[])
{
  aulaPosseduta *APP = NULL;
  int flagorder = 0;//variabile che serve ad attivare il ciclo di riassegnamento territori nel caso sia stato eliminato un  giocatore
  int i, j;

  for (i = 0; i < detPartita->nGiocatori; i++)
    if (giocatori[i].soldi < 0)//se i giocatore e' in bancarotta
    {
      flagorder = 1;
      printf("giocatore %s sei stato eliminato.....\n", giocatori[i].nome);
      getchar();
      APP = giocatori[i].listaAule;
      //vengono assegnate le aule del giocatore al banco e rimosse le scrivanie e le tende tramite la lista
      while (APP != NULL) {
        Tabellone[APP->idA].proprietario = IDBANCO;
        Tabellone[APP->idA].Scrivania = false;
        Tabellone[APP->idA].Tenda = false;
        APP = APP->next;
      }
      eraseList(giocatori[i].listaAule);//viene disalloccata la lista  dei territori posseduti
      for (j = i; j < detPartita->nGiocatori - 1; j++) giocatori[j] = giocatori[j + 1]; //vegono scalati i giocatori dal giocatore perdente alla fine
      detPartita->nGiocatori--; // viene diminuito il numero giocatori
      //la realloc cancella l ultimo elemento della lista
      if (detPartita->nGiocatori> 1){ //l ultimo giocatore se in bancarotta non viene cancellato
      giocatori = (Giocatore* ) realloc(giocatori, detPartita->nGiocatori * sizeof(Giocatore));
      if (giocatori == NULL) exit(1);
      }
      i--; //il contatore viene riportato indietro di un giro per poter controllare il giocatore successivo(cambio indice a ogni eliminazione)
    }
  i = 0;
  //se almeno un giocatore e stato eliminato vengono riassegnati i nuovi identificatori alle aule possedute
  while (i < detPartita->nGiocatori && flagorder == 1)
  {
    APP = giocatori[i].listaAule;
    while (APP != NULL)
    {
      Tabellone[APP->idA].proprietario = i;
      APP = APP->next;
    }
    i++;
  }
}
int ContaScr(aulaPosseduta *aule, Aula Tabellone[])
{
    int n=0;
    while(aule!=NULL){
        if(Tabellone[aule->idA].Scrivania) n++;
        aule=aule->next;
    }
    return n;
}
int ContaTnd(aulaPosseduta *aule, Aula Tabellone[])
{
  int n=0;
    while(aule!=NULL){
        if(Tabellone[aule->idA].Tenda) n++;
        aule=aule->next;
    }
    return n;
}
void Spostamento(int Shift, Partita detPartita, Giocatore giocatori[],Aula Tabellone[])
{
    giocatori[detPartita.gAttivo].posizione += Shift;
    if (giocatori[detPartita.gAttivo].posizione > NAULE - 1)//se con lo spostamento viene superata l ultima casella del tabellone
    {
    /*viene calcolata la nuova casella data dal espressione modulare
       posizione%NAULE*/
      giocatori[detPartita.gAttivo].posizione %=NAULE;
      giocatori[detPartita.gAttivo].soldi += Tabellone[PGO].costo;// vengono aggiunti al giocatore i soldi del passaggio dal via
      printf("sei passato dal VIA ritira %d\n", Tabellone[PGO].costo);
      getchar();
    }
}
void AvanzaTurno(Partita *detPartita, Giocatore giocatori[], Aula Tabellone[])
{
    if (detPartita->gAttivo == detPartita->nGiocatori - 1) //se e l ultimo giocatore
      {
        ControllaGiocatoriEliminati(detPartita, giocatori, Tabellone);//vengono controllati i gicatori in bancarotta e eliminati
        detPartita->gAttivo = 0;//il turno viene passato al primo giocatore
      }
      else detPartita->gAttivo++;//se non e' l ultimo giocatore il turno avanza semplicemente
      detPartita->nTurni++;//contatore turni

}
void casoAulaBanco(int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[])
{
    int posizione = giocatori[detPartita.gAttivo].posizione;
    int pagamento;
    char risp;

    if (modalita == MRANDOM)//in modalita random il giocatore paghera la dogana al banco
    {
         pagamento=Tabellone[posizione].costoPassaggio;
         printf("(%dE)devi pagare al banco:%dE (premi invio per pagare)....",giocatori[detPartita.gAttivo].soldi, pagamento);
         getchar();
         giocatori[detPartita.gAttivo].soldi-=pagamento;
    }
    else if(modalita == MCONQUISTA)//in modalita conquista il giocatore potra acquistare il terreno
    {
        printf("vuoi acquistare il territorio(y/n):");
        scanf("%c",&risp);
        getchar();
        if((risp=='y' || risp=='Y') && giocatori[detPartita.gAttivo].soldi  >= Tabellone[posizione].costo)
        {
        Tabellone[posizione].proprietario=detPartita.gAttivo;//viene settato il nuovo proprietario nel tabellone
        giocatori[detPartita.gAttivo].listaAule=addAula(giocatori[detPartita.gAttivo].listaAule,posizione);//aggiunge l aula alla lista di aule possedute
        printf("hai acquistato l'aula %s(premi invio per continuare)....",Tabellone[posizione].nomeAula);
        getchar();
        giocatori[detPartita.gAttivo].soldi-=Tabellone[posizione].costo;
        }
        else if((risp=='y' || risp=='Y') && giocatori[detPartita.gAttivo].soldi  < Tabellone[posizione].costo)
        {
         printf("soldi insuficenti per l acquisto(premi invio)...\n");
         getchar();
        }
    }
}
void CasoAulaGiocatore(Partita detPartita, Giocatore giocatori[], Aula Tabellone[])
{
    int posizione = giocatori[detPartita.gAttivo].posizione;
    int pagamento;
    char risp;

    if (Tabellone[posizione].proprietario == detPartita.gAttivo)//se l aula e del giocatore attivo
    {
        if(!Tabellone[posizione].Scrivania && !Tabellone[posizione].Tenda)//se non ci son scrivanie  e neanche tende ne richiede l acquisto
        {
            printf("vuoi acquistare una scrivania?(y/n)%dE",SCRIVANIA);
            scanf("%c",&risp);
            getchar();
            if((risp=='y' || risp=='Y') && giocatori[detPartita.gAttivo].soldi >= SCRIVANIA){
                Tabellone[posizione].Scrivania=true;
                giocatori[detPartita.gAttivo].soldi-=SCRIVANIA;
                printf("hai acquistato una scrivania(premi invio per continuare)...");
                getchar();
            }
            else if((risp=='y' || risp=='Y') && giocatori[detPartita.gAttivo].soldi < SCRIVANIA){
               printf("denaro insuficente...\n");
               getchar();
            }

        }
        else if(!Tabellone[posizione].Tenda && Tabellone[posizione].Scrivania)//se ce la scrivania ma non la tenda ne richiede l acquisto
        {
            printf("vuoi acquistare una tenda?(y/n)%dE",TENDA);
            scanf("%c",&risp);
            getchar();
            if((risp=='y' || risp=='Y') && giocatori[detPartita.gAttivo].soldi >= TENDA ){
                Tabellone[posizione].Tenda=true;//il  flag tenda viene attivato
                Tabellone[posizione].Scrivania=false;//il flag scrivania viene disattivato
                giocatori[detPartita.gAttivo].soldi-=TENDA;
                printf("hai acquistato una tenda(premi invio per continuare)...");
                getchar();
            }
            else if(giocatori[detPartita.gAttivo].soldi < TENDA){
               printf("denaro insuficente...\n");
               getchar();
            }
        }
        else// se il giocatore possiede la tenda
        {
           printf("benvenuto in %s (premi invio)...",Tabellone[posizione].nomeAula);
           getchar();
        }
    }
    else// se l aula e' di un aversario in base alla presenza di scrivanie o tende verra calcolato il pedaggio
    {
        //se il giocatore proprietario del territorio e a pulire i bagni non fa pagare la tassa
        if (giocatori[Tabellone[posizione].proprietario].puliziaBagni == 0){
        if (Tabellone[posizione].Tenda)          pagamento = Tabellone[posizione].passaggTenda;
        else if (Tabellone[posizione].Scrivania) pagamento = Tabellone[posizione].passaggScrivania;
        else                                     pagamento = Tabellone[posizione].costoPassaggio;
        printf("(%dE)devi pagare la dogana:%dE (premi invio per pagare)....",giocatori[detPartita.gAttivo].soldi, pagamento);
        getchar();
        giocatori[detPartita.gAttivo].soldi-=pagamento;
        giocatori[Tabellone[posizione].proprietario].soldi+=pagamento;
        }
        else
        {
            printf("il giocatore %s e in bagno fai finta di niente(premi invio)...",giocatori[Tabellone[posizione].proprietario].nome);
            getchar();
        }
    }
}
void CasoAula(int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[])
{
  int posizione = giocatori[detPartita.gAttivo].posizione;

  //viene contrallato se il territorio e del banco o di un giocatore qualsiasi
  if (Tabellone[posizione].proprietario==IDBANCO)
    casoAulaBanco(modalita,detPartita,giocatori,Tabellone);
  else
    CasoAulaGiocatore(detPartita,giocatori,Tabellone);

}
void CasoTassa(Partita detPartita, Giocatore giocatori[], Aula Tabellone[])
{
  int posizione = giocatori[detPartita.gAttivo].posizione;
  int pagamento;
  pagamento = Tabellone[posizione].costoPassaggio;

  printf("(%d E)Devi pagare una tassa di:%dE (premi invio per pagare)...",giocatori[detPartita.gAttivo].soldi, pagamento);
  //viene sotratto il valore della tassa da conto in banca del giocatore
  giocatori[detPartita.gAttivo].soldi -= pagamento;
  getchar();
}
void CasoSfiga(int numeroSfigheT, int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[], Sfighe sfighe[])
{
  int pagamento;
  int nTende;
  int nScr;
  int shift;
  Sfighe SfigaPescata = pescaSfiga(numeroSfigheT, sfighe);//viene pescata una sfiga

  printf("pesca una sfiga!(premi invio)...");
  getchar();
  switch (SfigaPescata.tipo) {// a seconda della sfiga pescata viene effetuata l azione relativa
    case BattutaMartina://viene stampata solo la frase
      printf("\nBattuta martina: %s\n(premi invio per ridere)...", SfigaPescata.frase);
      getchar();
      break;
    case tassaSemplice://viene sotratto il valore della tassa dal conto in banca del giocatore
      {
        pagamento = SfigaPescata.tassaOrJump;
        printf("\nTassa semplice: %s\n(%d E)devi pagare:%dE (premi invio per pagare)...", SfigaPescata.frase, giocatori[detPartita.gAttivo].soldi, pagamento);
        giocatori[detPartita.gAttivo].soldi -= pagamento;

        getchar();
        break;
      }
    case tassaImmobile://viene calcolata la tassa del giocatore in base alle tende e le scrivanie possedute
      {
        nScr=ContaScr(giocatori[detPartita.gAttivo].listaAule, Tabellone);//funzione che restituisce il numero di scrivanie
        nTende=ContaTnd(giocatori[detPartita.gAttivo].listaAule, Tabellone);//funzione che restituisce il numero di tende
        pagamento = SfigaPescata.tassaOrJump * giocatori[detPartita.gAttivo].numeroAule + SfigaPescata.tassaScrivania * nScr + SfigaPescata.tassaTende * nTende;
        printf("\nTassa immobile: %s\n(%d E)devi pagare:%dE (premi invio per pagare)...", SfigaPescata.frase, giocatori[detPartita.gAttivo].soldi, pagamento);
        giocatori[detPartita.gAttivo].soldi -= pagamento;
        getchar();
        break;
      }
    case GoTo://il giocatore deve spostarsi sino alla casella indicata
      {
        printf("\nGoto:%s\n(premi invio per teletrasportarti)...", SfigaPescata.frase);
        getchar();
        //viene calcolati il numero di passi
        shift =(NAULE + SfigaPescata.tassaOrJump  - giocatori[detPartita.gAttivo].posizione)%NAULE;
        Spostamento(shift, detPartita, giocatori, Tabellone);// effetua spostamento
        AzioneCasella(numeroSfigheT, modalita, detPartita, giocatori, Tabellone, sfighe);// interagisce con la casella
      }
  }
}
void AzioneCasella(int numeroSfigheT, int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[], Sfighe sfighe[])
{
  int posizione = giocatori[detPartita.gAttivo].posizione;

  printf("Sei finito nella casella:\n\n");
  stampaCasella(Tabellone[posizione], giocatori);//stampa casella di destinazione
  switch (Tabellone[posizione].tipoAula) //a seconda del tipo di casella vengono richiamate le funzioni corrispondenti
  {
    case aula:
      CasoAula(modalita, detPartita, giocatori, Tabellone);
      break;
    case tassa:
      CasoTassa(detPartita, giocatori, Tabellone);
      break;
    case sfiga:
      CasoSfiga(numeroSfigheT, modalita, detPartita, giocatori, Tabellone, sfighe);
      break;
    case other:
      {
        if (posizione == PBATCAVERNA)//nel caso ci si ritrova in batcaverna si viene spediti in bagno per N turni
        {
          printf("\n\nNON PUOI GIRARE NELLA BAT CAVERNA VAI IN BAGNO!!\n");
          getchar();
          giocatori[detPartita.gAttivo].puliziaBagni = NTURNIBAGNO;//vengono assegnati i turni da passare in bagno
          giocatori[detPartita.gAttivo].posizione = PBAGNI;//viene assegnata alla posizione del giocatore le coordinate del bagno
        }
        else
        {
          printf("\n\n.....NON SUCCEDE NIENTE......(premi invio per continuare)...");
          getchar();
        }

        break;
      }
  }
}
void TiraDadi(int numeroSfigheT, int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[], Sfighe sfighe[])
{
  int Dado1;
  int Dado2;
  int Doppia = 0; //variabile utilizata per il controllo numero doppie(dadi uguali)

  do {
    Dado1 = DADOMIN + rand() % (DADOMAX - DADOMIN + 1);//lancio dado 1
    Dado2 = DADOMIN + rand() % (DADOMAX - DADOMIN + 1);//lancio dado 2
    printf("DADO: %d \nDADO: %d\n(premi invio per spostarti)....", Dado1, Dado2);
    getchar();

   //se non si e raggiounto il limite di doppie e i dadi sono uguali o i dadi son diversi
    if (Dado1==Dado2 && Doppia < LIMITEDPP || Dado1!=Dado2)
    {
      Spostamento(Dado1 + Dado2, detPartita, giocatori, Tabellone);//effetua spostamento
      AzioneCasella(numeroSfigheT, modalita, detPartita, giocatori, Tabellone, sfighe);//interagisce con la casella
    }
    /*se il giocatore fa doppia ,non ha raggiunto il limite,
    e non e' ne in bancarotta ne a pulire i bagni allora puo rilanciare i dadi*/
    if ( Dado1==Dado2 && Doppia < LIMITEDPP && giocatori[detPartita.gAttivo].puliziaBagni == 0 && giocatori[detPartita.gAttivo].soldi >= 0 )
    {
      printf("\nHAI FATTO DOPPIA RITIRA I DADI!!(premi invio)\n");
      getchar();
      Doppia++;
    }
    else if (Dado1 == Dado2 && Doppia==LIMITEDPP)//se il giocatore raggiunge il limite di doppia va a pulire il bagno
    {
      printf("\ne la %d volta...Sei stato troppo fortunato vai in bagno!!... \n",Doppia);
      getchar();
      giocatori[detPartita.gAttivo].puliziaBagni = NTURNIBAGNO;//turni da passare in bagno
      giocatori[detPartita.gAttivo].posizione = PBAGNI;//vengono assegnate le coordinate del bagno
    }

  } while (Dado1 == Dado2 && Doppia <= LIMITEDPP && giocatori[detPartita.gAttivo].puliziaBagni == 0 && giocatori[detPartita.gAttivo].soldi >= 0);
}
void ChiudiPartita(int nGiocatori, Giocatore giocatori[], Sfighe sfighe[])
{
    int i;
    for (i = 0; i < nGiocatori; i++) eraseList(giocatori[i].listaAule);//disalloccazione liste giocatori
    free(giocatori);//disalloccazione giocatori
    free(sfighe);//disallocazione sfighe
}
/**FUNZIONE GIOCO*/
void Monopoly(int numeroSfigheT, int modalita, Partita detPartita, Giocatore giocatori[], Aula Tabellone[], Sfighe sfighe[])
{
  while (detPartita.nGiocatori > 1)//finche non rimane l ultimo giocatore
  {
      stampaDettagliP(modalita,detPartita,giocatori);//stampa dettagli turno
    //se il giocatore non e' a pulire il bagno potra effetuare il suo turno
    if (giocatori[detPartita.gAttivo].puliziaBagni == 0)
        sceltaAzione(numeroSfigheT,modalita,detPartita,giocatori,Tabellone,sfighe);
    else if(giocatori[detPartita.gAttivo].puliziaBagni > 0)//se il giocatore e in bagno
    {
      giocatori[detPartita.gAttivo].puliziaBagni--;//un turno e passato
      printf("\n%s deve pulire il bagno per altri %d turni...\n\n",giocatori[detPartita.gAttivo].nome,giocatori[detPartita.gAttivo].puliziaBagni);
      getchar();
    }
   AvanzaTurno(&detPartita,giocatori,Tabellone); //il turno passa al giocatore successivo
  }
  //viene controllato se anche l'ultimo giocatore rimasto e in bancarotta altrimenti non esiste vincitore
  if (giocatori->soldi >= 0) printf("IL VINCITORE E: %s", giocatori->nome);
  else printf("......NESSUN VINCITORE.........");
  ChiudiPartita(detPartita.nGiocatori, giocatori, sfighe);
}
/**TABELLONE*/
Tab inizializzaTabellone(void)
{
    int i;
    Tab T={{
            {20,0,0,0,"GO!",other,0,0,0},

            {60,0,0,0,"Aula G",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {60,0,0,0,"Aula C",aula,0,0,0},
            {80,0,0,0,"Aula F",aula,0,0,0},
            {0,100,0,0,"Tasse!",tassa,0,0,0},
            {100,0,0,0,"Aula Studio",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {100,0,0,0,"SIMAZ",aula,0,0,0},
            {120,0,0,0,"Lab T",aula,0,0,0},
            {0,0,0,0,"Bagni",other,0,0,0},

            {140,0,0,0,"VAX",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {140,0,0,0,"G.A.R",aula,0,0,0},
            {160,0,0,0,"Biblioteca",aula,0,0,0},
            {0,150,0,0,"Tasse!",tassa,0,0,0},
            {180,0,0,0,"Aula B",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {180,0,0,0,"Segreteria",aula,0,0,0},
            {200,0,0,0,"Aula A",aula,0,0,0},
            {0,0,0,0,"Corridoio",other,0,0,0},

            {220,0,0,0,"Ufficio Scateni",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {220,0,0,0,"Bagno Prof.",aula,0,0,0},
            {240,0,0,0,"Aula D",aula,0,0,0},
            {0,250,0,0,"Tasse!",tassa,0,0,0},
            {260,0,0,0,"Lab 3",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {260,0,0,0,"Lab 4",aula,0,0,0},
            {280,0,0,0,"Lab M",aula,0,0,0},
            {0,0,0,0,"BatCaverna",other,0,0,0},

            {300,0,0,0,"Aula Fisica",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {300,0,0,0,"Aula M Chimica",aula,0,0,0},
            {320,0,0,0,"Aula M Matematica",aula,0,0,0},
            {0,350,0,0,"Tasse!",tassa,0,0,0},
            {360,0,0,0,"Bar Rotondo",aula,0,0,0},
            {0,0,0,0,"Sfiga!",sfiga,0,0,0},
            {360,0,0,0,"Aula Anatomica",aula,0,0,0},
            {400,0,0,0,"Aula Costa",aula,0,0,0}

                    }};

    for(i=0;i<NAULE;i++){
        if(T.Tabellone[i].tipoAula==aula)
        {//tramite la costante moltiplicatore pedaggio se ne aumenta il valore(utilizata per velocizare la partita)
            T.Tabellone[i].costoPassaggio=T.Tabellone[i].costo/DIVPASS * MOLTIPLICATORE_PEDAGGIO;//calcolo costo passaggio
            T.Tabellone[i].passaggScrivania=T.Tabellone[i].costo/SCRPASS * MOLTIPLICATORE_PEDAGGIO;//calcolo costo passaggio con scrivania
            T.Tabellone[i].passaggTenda=T.Tabellone[i].costo/TNDPASS * MOLTIPLICATORE_PEDAGGIO;    //calcolo costo passaggio con scrivania
        }
        T.Tabellone[i].proprietario=IDBANCO;//ogni casella e' proprieta del banco a inizio partita
        }
return T;//rende il tabellone alla funzione chiamante
}






