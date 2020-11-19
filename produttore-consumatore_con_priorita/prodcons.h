#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include <pthread.h>

#define DIM 3

typedef struct{

	int buffer[DIM];
	int coda;
	int testa;
	int num_prod_high;
	int num_totale;
	pthread_cond_t prod_high;
	pthread_cond_t prod_low;

	pthread_cond_t cons;

	pthread_mutex_t mutex;


	/* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
    
} PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons * p);
void produci_alta_prio(PriorityProdCons * p);
void produci_bassa_prio(PriorityProdCons * p);
void consuma(PriorityProdCons * p);
void rimuovi_prod_cons(PriorityProdCons * p);

#endif
