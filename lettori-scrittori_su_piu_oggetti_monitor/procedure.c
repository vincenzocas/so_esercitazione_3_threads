#include "header.h"


void inizializza(struct monitor* m){

	m->stazione=0;
	m->id_treno=0;

	/* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
}

void rimuovi (struct monitor* m){

	/* TBD: Disattivare mutex e variabili condition */
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_stazione(struct monitor* m, int stazione){

	/* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
	 * 
	 * 		Utilizzare una variabile "num_cv_scrittori" per contare il numero
	 * 		di scrittori in attesa sulla variabile condition (da affiancare in aggiunta
	 * 		alla variabile "num_scrittori" dell'algoritmo).
	 * 
	 * 		La variabile "num_cv_scrittori" deve essere incrementata subito prima
	 * 		di wait_cond(), e decrementata subito dopo di wait_cond().
	 */


	// SCRITTURA
	m->stazione=stazione;


}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_stazione(struct monitor* m){

	/* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
	 * 
	 * 		Utilizzare una variabile "num_cv_lettori" per contare il numero
	 * 		di lettori in attesa sulla variabile condition (da affiancare in aggiunta
	 * 		alla variabile "num_lettori" dell'algoritmo).
	 * 
	 * 		La variabile "num_cv_lettori" deve essere incrementata subito prima
	 * 		di wait_cond(), e decrementata subito dopo di wait_cond().
	 */



	// LETTURA
	int ris=m->stazione;

	return ris;
}

