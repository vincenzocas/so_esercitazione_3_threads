#include "header.h"

/*Funzione che,per 10 volte,incrementa di uno la stazione, ovvero la posizione del treno, 
e tramite scrivi_stazione effettua la modifica poi attende 3 secondi*/
void * Capotreno (void * p){
	struct monitor* m = (struct monitor*) p;
	int i,s;
	s=leggi_stazione(m);
	for(i=0; i<10; i++){
		s=s+1;
		scrivi_stazione(m,s);
		printf("[C: Posizione del treno %d modificata. La nuova posizione è: %d]\n",m->id_treno,s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un treno per tre volte
void * Viaggiatori (void * p){
	struct monitor* m = (struct monitor*) p;
	int i;
	int ris;
	for(i=0;i<3;i++){
		sleep(rand()%6+1);
		ris=leggi_stazione(m);
		printf("[V]~Il treno n.ro %d è nella %da stazione\n",m->id_treno,ris);
	}
	pthread_exit(NULL);
}

int main() {


	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[4];//l'array di monitor per gestire i 4 treni

	pthread_t capo[4];//4 capitreno
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

	
	for(i=0;i<4;i++){
		m[i] = (struct monitor*) malloc(sizeof(struct monitor));
		inizializza(m[i]);
	}
	



	//assegno un id ad ogni treno
	m[0]->id_treno=1;
	m[1]->id_treno=2;
	m[2]->id_treno=3;
	m[3]->id_treno=4;

	//creazione dei 4 threads capitreno
	for(i=0;i<4;i++){
		int	rc = pthread_create(&capo[i],&attr,Capotreno, (void*)  m[i]);
		if(rc){
			printf("errore thread capo %d \n",rc);
		}
	} 

	


	for(i=0;i<10;i++){
		int j = rand() % 4;
		int	rc = pthread_create(&viagg[i],&attr,Viaggiatori, (void*)  m[j]);
		if(rc){
			printf("errore thread viaggiatore %d \n",rc);
		}
	} 


	for(i=0;i<4;i++){
		pthread_join(capo[i],NULL);
	
	} 

	for(i=0;i<10;i++){
		pthread_join(viagg[i],NULL);
	
	} 

	for(int i=0; i<4; i++){
		rimuovi(m[i]);
		free(m[i]);
	}

	return 0;
}	
