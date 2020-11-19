#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

void StackInit(Stack * s, int dim) {


	pthread_mutex_init(&(s->mutex),NULL);
	pthread_cond_init(&(s->pop),NULL);
	pthread_cond_init(&(s->push),NULL);

	s->dati = (Elem *) malloc(sizeof(Elem)*dim);
	s->dim = dim;
	s->testa = 0;
	printf("inizializzazione conclusa\n");
}


void StackRemove(Stack * s) {

	pthread_mutex_destroy(&(s->mutex));
	pthread_cond_destroy(&(s->push));
	pthread_cond_destroy(&(s->pop));
	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	

	pthread_mutex_lock(&(s->mutex));

	while(s->dim == s->testa){
		pthread_cond_wait(&(s->push),&(s->mutex));
	}


	s->dati[s->testa] = e;
	s->testa++;

	pthread_cond_signal(&(s->pop));

	pthread_mutex_unlock(&(s->mutex));
}


Elem StackPop(Stack * s) {

	
	int elemento;

	pthread_mutex_lock(&(s->mutex));

	while(s->testa==0){
		pthread_cond_wait(&(s->pop),&(s->mutex));
	}


	s->testa--;	
	elemento=s->dati[s->testa];

	pthread_cond_signal(&(s->push));

	pthread_mutex_unlock(&(s->mutex));

	return elemento;
}

int StackSize(Stack * s) {
	
	int size;

	pthread_mutex_lock(&(s->mutex));
	
	size = s->testa;

	pthread_mutex_unlock(&(s->mutex));

	return size;
}
