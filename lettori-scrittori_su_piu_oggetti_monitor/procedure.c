#include "header.h"


void inizializza(struct monitor* m){

	m->stazione=0;
	m->id_treno=0;
	m->num_cv_scrittori=0;
	m->num_cv_lettori=0;
	m->num_lettori=0;
	m->num_scrittori=0;


	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->lettori),NULL);
	pthread_cond_init(&(m->scrittori),NULL);
}

void rimuovi (struct monitor* m){

	pthread_mutex_destroy(&(m->mutex));
	pthread_cond_destroy(&(m->lettori));
	pthread_cond_destroy(&(m->scrittori));
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_stazione(struct monitor* m, int stazione){


	pthread_mutex_lock(&(m->mutex));

	while(m->num_scrittori>0 ){
		++m->num_cv_scrittori;
		pthread_cond_wait(&(m->scrittori),&(m->mutex));
		--m->num_cv_scrittori;
	}

	++m->num_scrittori;

	pthread_mutex_unlock(&(m->mutex));

	// SCRITTURA
	m->stazione=stazione;
	
	pthread_mutex_lock(&(m->mutex));

	

	if(m->num_cv_scrittori>0){
		pthread_cond_signal(&(m->scrittori));
	}else if(m->num_cv_lettori>0){
		pthread_cond_signal(&(m->lettori));
	}

	--m->num_scrittori;
	
	pthread_mutex_unlock(&(m->mutex));

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
	 * 
	 * 
	 */

	pthread_mutex_lock(&(m->mutex));

	while (m->num_scrittori>0)
	{	++m->num_cv_lettori;
		pthread_cond_wait(&(m->lettori),&(m->mutex));
		--m->num_cv_lettori;
	}
	
	++m->num_lettori;

	pthread_cond_signal(&(m->lettori));
	
	pthread_mutex_unlock(&(m->mutex));

	// LETTURA
	int ris=m->stazione;

	printf("Fine lettura\n");

	pthread_mutex_lock(&(m->mutex));

	--m->num_lettori;
	if(m->num_lettori==0){
		pthread_cond_signal(&(m->scrittori));
	}

	pthread_mutex_unlock(&(m->mutex));

	return ris;
}

