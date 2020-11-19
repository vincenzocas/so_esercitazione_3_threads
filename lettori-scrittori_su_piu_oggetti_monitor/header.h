#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


struct monitor {

	int stazione;
	int id_treno;

	pthread_mutex_t mutex;

	int num_cv_scrittori;
	int num_cv_lettori;
	int num_lettori;
	int num_scrittori;

	pthread_cond_t	scrittori;
	pthread_cond_t lettori; 
	
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_stazione(struct monitor * m, int stazione);
int leggi_stazione(struct monitor * m);



#endif
