#include "stack.h"

#include <stdlib.h>

void StackInit(Stack * s, int dim) {

	/* TBD: Inizializzare mutex e variabili condition */

	s->dati = (Elem *) malloc(sizeof(Elem)*dim);
	s->dim = dim;
	s->testa = 0;
}


void StackRemove(Stack * s) {

	/* TBD: Disattivare mutex e variabili condition */

	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	/* TBD: Aggiungere la sincronizzazione */
	
	s->dati[s->testa] = e;
	s->testa++;

}


Elem StackPop(Stack * s) {

	int elemento;

	/* TBD: Aggiungere la sincronizzazione */

	s->testa--;	
	elemento=s->dati[s->testa];

	return elemento;
}

int StackSize(Stack * s) {
	
	int size;

	/* TBD: Aggiungere la sincronizzazione */

	size = s->testa;

	return size;
}
