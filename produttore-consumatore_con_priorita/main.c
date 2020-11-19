#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include "prodcons.h"


void * produttore_alta_priorita(void * p)
{	
	PriorityProdCons * pc = ((PriorityProdCons*) p);

	int i;
	    
    
	for(i=0; i<3; i++) {

		produci_alta_prio(pc);

		sleep(2);
	}

	pthread_exit(NULL);
}


void * produttore_bassa_priorita(void * p)
{
    PriorityProdCons * pc = ((PriorityProdCons*) p);

	int i;
        
    
	for(i=0; i<3; i++) {
        
		produci_bassa_prio(pc);

		sleep(1);
	}
    
	pthread_exit(NULL);
}


void * consumatore(void * p)
{
	PriorityProdCons * pc = ((PriorityProdCons*) p);

	int i;

    
    
	for(i=0; i<12; i++) {
        
		consuma(pc);
        
		sleep(1);
	}
    
	pthread_exit(NULL);
}




int main(int argc, char *argv[])
{

	pthread_t threads[5];
	pthread_attr_t attr;
    
	int rc;
	int i;

	srand(time(NULL));

    
	PriorityProdCons * prodcons = (PriorityProdCons *)malloc(sizeof(PriorityProdCons));

    
    
	inizializza_prod_cons(prodcons);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	for(int i=0; i<3; i++){
		rc  = pthread_create(&threads[i],&attr,produttore_bassa_priorita,(void *)prodcons);
		if(rc){
		printf("errore prduttore bassa priorità %d \n",rc);
		exit(-1);
	}
	

	rc = pthread_create(&threads[3],&attr,consumatore,(void *)prodcons);
	if(rc){
		printf("errore consumatore\n");
		exit(-1);
	}

	rc = pthread_create(&threads[4],&attr,produttore_alta_priorita,(void *)prodcons);
	if(rc){
		printf("errore produttore alta priorità\n");
		exit(-1);
	}
	
	

	}
    
	for(int i=0; i<5; i++){
		pthread_join(threads[i],NULL);
	}



	rimuovi_prod_cons(prodcons);

	return 0;
}



