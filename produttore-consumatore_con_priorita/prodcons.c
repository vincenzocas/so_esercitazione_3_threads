#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"


void inizializza_prod_cons(PriorityProdCons* p){

    p->testa=0;
    p->coda=0;
    p->num_prod_high=0;
    p->num_totale=0;
    pthread_mutex_init(&(p->mutex),NULL);
    pthread_cond_init(&(p->prod_high),NULL);
    pthread_cond_init(&(p->prod_low),NULL);
    pthread_cond_init(&(p->cons),NULL);

}

void rimuovi_prod_cons(PriorityProdCons* p){

    pthread_mutex_destroy(&(p->mutex));

    pthread_cond_destroy(&(p->prod_high));
    pthread_cond_destroy(&(p->prod_low));
    pthread_cond_destroy(&(p->cons));
    
}

void produci_alta_prio(PriorityProdCons* p){

	int value;

    pthread_mutex_lock(&(p->mutex));
    while(p->num_totale == DIM){
        printf("blocca produzione alta\n");
        ++p->num_prod_high;
        pthread_cond_wait(&(p->prod_high),&(p->mutex));
        --p->num_prod_high;
    }

    
    value = rand() % 12;

    p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
    ++p->num_totale;
    
   
   pthread_cond_signal(&(p->cons));

    printf("Produzione priorità alta: %d\n", value);

    pthread_mutex_unlock(&(p->mutex));
}




void produci_bassa_prio(PriorityProdCons* p){
	
    int value;
    
    pthread_mutex_lock(&(p->mutex));
    while( p->num_totale==DIM || p->num_prod_high>0){
        printf("blocca produzione bassa\n");
        pthread_cond_wait(&(p->prod_low),&(p->mutex));
    }
    
    value = 13 + (rand() % 12);

    p->buffer[p->testa] = value;
	p->testa = (p->testa + 1) % DIM;
    ++p->num_totale;

    pthread_cond_signal(&(p->cons));

    printf("Produzione priorità bassa: %d\n", value);
    
    pthread_mutex_unlock(&(p->mutex));

}




void consuma(PriorityProdCons* p){
    
	int value;

    pthread_mutex_lock(&(p->mutex));
    while( p->num_totale==0){
        printf("blocca consumatore \n");
        pthread_cond_wait(&(p->cons),&(p->mutex));
    }
    
	value = p->buffer[p->coda];
	p->coda = (p->coda + 1) % DIM;
	--p->num_totale;

    if(p->num_prod_high>0){
        pthread_cond_signal(&(p->prod_high));
    }else{
        pthread_cond_signal(&(p->prod_low));
    }

	printf("Consumato valore %d\n", value);

    pthread_mutex_unlock(&(p->mutex));

    
}
