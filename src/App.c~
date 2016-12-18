#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <semaphore.h>

#include "Parser.h"
#include "App.h"
#include "Front.h"
#include "Matica.h"

typedef void (*proc_funkcia_t)(void);

typedef struct _Proces {
	sem_t * semafor;
	proc_funkcia_t proc_funkcia;
} Proces;


static void nacitaj_procesy(App* inst, const Matica* matica, int prvy_proc);
static Proces* proces_vytvor(sem_t* semafor, void* proces_funkcia);
static void proces_vykonaj(Proces* proces);
static void funkcia_1();
static void funkcia_2();
static void funkcia_3();
static void funkcia_4();
static void funkcia_5();


App* up_app_vytvor(const char* nazov_suboru) {
	App* inst = (App*)malloc(sizeof(App));
	inst->nazov_suboru = nazov_suboru;
	return inst;
}

void up_app_spusti(App* inst) {
	printf("Spustanie app ....... \n");
	Matica* matica = up_parser_nacitaj_subor (inst->nazov_suboru); // nacita subor a ukaze co je v buffri
	up_matica_vypis(matica);
	nacitaj_procesy(inst, matica, 0);
}

void up_app_zrus(App* inst){
	free((void*)inst);
}

void nacitaj_procesy(App* inst, const Matica* matica, int prvy_proc) {
	int **pole = up_matica_vrat_pole(matica);
	Front* front = up_front_vytvor();
	// Indexovanie od nuly
	up_front_push(front, prvy_proc);
	// Pole semaforov
	size_t velkost_matice = up_matica_daj_velkost(matica);
	sem_t* poleSemaforov[velkost_matice];
	sem_t *katka = sem_open("test_1", O_CREAT|O_EXCL, 0, 1);
    sem_unlink("test_1"); // INICIALIZOVAT!
	sem_t *miska = sem_open("test_2", O_CREAT|O_EXCL, 0, 1);
    sem_unlink("test_2");
	sem_init(katka,1,1);
	sem_init(miska,1,1);
	poleSemaforov[0]= katka;
	poleSemaforov[1]= katka;
	poleSemaforov[2]= katka;
	poleSemaforov[3]= miska;
	poleSemaforov[4]= miska;
	
	proc_funkcia_t funkcie[5] = {
		funkcia_1,
		funkcia_2,
		funkcia_3,
		funkcia_4,
		funkcia_5
	};
	
	// Inicializovat jednotlive semafory na potrebne pozicie
	memset(poleSemaforov, 0, velkost_matice * sizeof(sem_t*));
	while (!up_front_je_prazdny(front)) {
		int aktualny = up_front_pop(front);
		// Prejde cez vsetky incidentne vrcholy
		int poc_inc_vrcholov = 0;
		for (size_t j = 0; j < velkost_matice; j++) {
			if (pole[aktualny][j] == 1) {
				poc_inc_vrcholov++;
				sem_t* semafor = poleSemaforov[aktualny];
				//sem_t* semafor; // tu treba menit nazov semafora   !!!!!!!
				// INIT bude asi az potom ***********************
				Proces* proces = proces_vytvor(semafor, funkcie[aktualny]);
				pid_t fork_vysledok = fork();
				if (fork_vysledok == 0) { // Potomok
					printf("After fork....\n");
					proces_vykonaj(proces);
					printf("PO fork....\n");
					return;
				} else if (fork_vysledok < 0) {
					// Chyba
				}
				up_front_push(front, j);
			}
		}
	}
	up_front_zrus(front);
} 

static Proces* proces_vytvor(sem_t* semafor, void* proces_funkcia){
	Proces* inst = (Proces*)malloc(sizeof(Proces));
	inst->semafor = semafor;
	inst->proc_funkcia = proces_funkcia;
	return inst;
}

static void proces_vykonaj(Proces* proces) {
	while(1) {
		printf("vo WHILEEE\n");
		int hodnota;
		sem_getvalue(proces->semafor, &hodnota);
	    printf("pred waitom, semafor hodnota = %d\n", hodnota);
		sem_wait(proces->semafor);
		printf("HERE 1\n");
		proces->proc_funkcia();
		sem_post(proces->semafor);
	}
} 

static void funkcia_1() {
	printf("1\n");
}

static void funkcia_2() {
	printf("2\n");
}
static void funkcia_3() {
	printf("3\n");
}
static void funkcia_4() {
	printf("4\n");
}
static void funkcia_5() {
	printf("5\n");
}

