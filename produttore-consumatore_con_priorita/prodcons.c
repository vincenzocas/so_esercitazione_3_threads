#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"


void inizializza_prod_cons(PriorityProdCons* p){

    /* TBD: Inizializzare tutte le variabili del monitor */

}

void rimuovi_prod_cons(PriorityProdCons* p){

    /* TBD: Disattivare mutex e variabili condition */
    
}

void produci_alta_prio(PriorityProdCons* p){

	int value;


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     * 
     *      Si introduca nel monitor una variabile "threads_prio_1"
     *      per contare il numero di produttori sospesi ad alta priorità.
     */
    

	value = rand() % 12;

    printf("Produzione priorità alta: %d\n", value);

}




void produci_bassa_prio(PriorityProdCons* p){
	
    int value;
    
    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     * 
     *      Si introduca nel monitor una variabile "threads_prio_2"
     *      per contare il numero di produttori sospesi a bassa priorità.
     */
    

    
    
	value = 13 + (rand() % 12);

    printf("Produzione priorità bassa: %d\n", value);
    

}




void consuma(PriorityProdCons* p){
    
	int value;
    

    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     */
    
    /* Consumazione */
    
	value = /* TBD */

	printf("Consumato valore %d\n", value);

    
}
