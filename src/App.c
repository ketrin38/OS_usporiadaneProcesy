#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Parser.h"
#include "App.h"
#include "Front.h"
#include "Matica.h"

typedef void (*proc_funkcia_t)(void);

typedef struct _Proces {
	sem_t* semafor;
	proc_funkcia_t proc_funkcia;
} Proces;


static void nacitaj_procesy(App* inst);
static Proces* proces_vytvor(sem_t* semafor, void* proces_funkcia);
static void poces_vykonaj(Proces* proces, void* nieco);



App* up_app_vytvor(const char* nazov_suboru) {
	App* inst = (App*)malloc(sizeof(App));
	inst->nazov_suboru = nazov_suboru;
	return inst;
}

void up_app_spusti(App* inst) {
	printf("Spustanie app ....... \n");
	Matica* matica = up_parser_nacitaj_subor (inst->nazov_suboru); // nacita subor a ukaze co je v buffri
	up_matica_vypis(matica);
}

void up_app_zrus(App* inst){
	free((void*)inst);
}

void nacitaj_procesy(App* inst, const Matica* matica, int prvy_proc) {
	int **pole = up_matica_vrat_pole(matica);
	Front* front = up_front_vytvor();
	// Indexovanie od nuly
	up_front_push(&prvy_proc);
	// Pole semaforov
	size_t velkost_matice = up_matica_daj_velkost(matica);
	sem_t* poleSemaforov[velkost_matice];
	// Inicializovat jednotlive semafory na potrebne pozicie
	memset(poleSemaforov, 0, velkost_matice * sizeof(sem_t*));
	while (!up_front_je_prazdny(front)) {
		int aktualny = *(int *) up_front_pop(front);
		// Prejde cez vsetky incidentne vrcholy
		int poc_inc_vrcholov = 0;
		for (int j = 0; j < velkost_matice; j++) {
			if (pole[aktualny][j] == 1) {
				poc_inc_vrcholov++;
				sem_t* semafor = poleSemaforov[aktualny];
				sem_t* semafor; // tu treba menit nazov semafora   !!!!!!!
				// INIT bude asi az potom ***********************
				Proces* proces = proces_vytvor(semafor,// nazov funkcie);
				pid_t fork_vysledok = fork();
				if (fork_vysledok == 0) { // Potomok
					proces_vykonaj(proces);
				} else if (fork_vysledok < 0) {
					// Chyba
				}
				up_front_push(proces);
			}
		}
	}
	up_front_zrus(front);
} 

static Proces* proces_vytvor(sem_t* semafor, void* proces_funkcia){
	Proces* inst = (Proces*)malloc(sizeof(Proces));
	inst->semafor = semafor;
	inst->proces_funkcia = proces_funkcia;
	return inst;
}

static void proces_vykonaj(Proces* proces) {
	while(1) {
		sem_wait(proces->semafor);
		proces->proces_funkcia();
		sem_post(proces->semafor);
	}
} 
