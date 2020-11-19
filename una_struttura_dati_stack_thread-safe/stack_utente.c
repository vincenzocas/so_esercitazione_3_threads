#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "colors.h"

#define NUM_TRHEAD 6

void *Inserisci(void * s)
{	
	Stack* stack = (Stack*) s;

	int i;
	Elem v;


	for(i=0; i<4; i++) {

		sleep(1);

		v = rand() % 11;
		
		StackPush(stack,v);
		
		printf(RED("Inserimento:") "%d\n", v);
		
	}

	pthread_exit(NULL);
}


void *Preleva(void * s)
{	
	Stack* stack = (Stack*) s;

	int i;
	Elem v1, v2;

    
	for(i=0; i<10; i++) {
	
		sleep(3);

		v1 = StackPop(stack);

		printf(BLUE("Prelievo:")  "%d\n", v1);


		v2 = StackPop(stack);

		printf(BLUE("Prelievo:")  "%d\n", v2);

		printf("Somma: %d\n", v1+v2);

		
	}

	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{
	pthread_t threads[NUM_TRHEAD];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	int rc;
	int i;

	srand(time(NULL));


	Stack * stack = (Stack *)malloc(sizeof(Stack));

	StackInit(stack,4);

	for(i=0; i<NUM_TRHEAD-1; i++) {

	rc = pthread_create(&threads[i],&attr,Inserisci,(void*)stack);
	if(rc){
		printf("errore thread inserisci %d \n",rc);
	}

	}


	pthread_create(&threads[5],&attr,Preleva,(void *)stack);
	if(rc){
		printf("errore thread preleva %d \n",rc);
	}


	for(i=0; i<NUM_TRHEAD; i++) {
		
		pthread_join(threads[i],NULL);
	}



	StackRemove(stack);
}

