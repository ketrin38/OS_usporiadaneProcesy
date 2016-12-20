/**
 * @file App.c
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za beh aplikacie.
 */
 
#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>

#include "Parser.h"
#include "App.h"
#include "Front.h"
#include "Matica.h"

#define PAMAT_VELKOST 4 // velkost zdielanej pamate
#define ZD_PAMAT_KLUC 292929

typedef struct _Proces {
	sem_t * semafor;
	int koeficient;
	Front* semafory_wait;  
	Front* semafory_signal;
} Proces;


static void nacitaj_procesy(Matica* matica);
static void proces_vytvor(Proces* proces, int koeficient);
static void proces_vykonaj(Proces* proces);


App* up_app_vytvor(const char* nazov_suboru) {
	App* inst = (App*)malloc(sizeof(App));
	inst->nazov_suboru = nazov_suboru;
	return inst;
}

void up_app_spusti(App* inst) {
	printf("Spustanie app ....... \n");
	Matica* matica = up_parser_nacitaj_subor (inst->nazov_suboru); // nacita subor a ukaze co je v buffri
	up_matica_vypis(matica);
	nacitaj_procesy(matica);
}

void up_app_zrus(App* inst){
	free((void*)inst);
}

static void nacitaj_procesy(Matica* matica) {
	int **pole = up_matica_vrat_pole(matica);
	size_t matica_velkost = up_matica_daj_velkost(matica);
	Proces procesy[5];
	
	// Pole semaforov
	size_t velkost_matice = up_matica_daj_velkost(matica);
	sem_t* poleSemaforov[velkost_matice];
	// Inicializovat jednotlive semafory na potrebne pozicie
	memset(poleSemaforov, 0, velkost_matice * sizeof(sem_t*));
	
	int poc_semaforov = 0;
	
	int zdielana_pam_id;
	int* zd_pamat;
	key_t key = ZD_PAMAT_KLUC;
	if ((zdielana_pam_id = shmget(key, ZD_PAMAT_KLUC, IPC_CREAT | 0666)) < 0) {
		fprintf(stderr, "chyba pri inicializacii zdielanej pamate");
		return;
	}
	zd_pamat = (int*) shmat(zdielana_pam_id, NULL, 0);
	if (zd_pamat == (int *) -1) {
		fprintf(stderr, "chyba pri alokacii pamate\n");
		return;
	}
	*zd_pamat = 1;
	
	for (size_t i = 0; i < matica_velkost; i++) {
		proces_vytvor(&procesy[i], (int) (i + 1));
	}
	
	for (size_t i = 0; i < matica_velkost; i++) {
		for (size_t j = 0; j < matica_velkost; j++) {
			if (pole[i][j] == 1) {
				int poz = poc_semaforov++;
				poleSemaforov[poz] = mmap(NULL, sizeof(sem_t *),
					PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
				if (poleSemaforov[poz] == MAP_FAILED) {
					fprintf(stderr, "mmap zlyhal: %s\n", strerror(errno));
					return;
				}
				if (sem_init(poleSemaforov[poz], 1, 0) < 0) {
					fprintf(stderr, "sem_init zlyhal: %s\n", strerror(errno));
					return;
				}
				up_front_push(procesy[i].semafory_signal,
					(void *) poleSemaforov[poz]);
				up_front_push(procesy[j].semafory_wait,
					(void *) poleSemaforov[poz]);
			}
		}
	}
	
	for (size_t i = 0; i < 5; i++) {
		pid_t fork_vysledok = fork();
		if (fork_vysledok == 0) {
			proces_vykonaj(&procesy[i]);
			return;
		} else if (fork_vysledok < 0) {
			fprintf(stderr, "Chyba: nepodarilo fork(): %s\n", strerror(errno));
		}
	}
	
	int status;
	
	while (wait(&status) > 0);
	
	for (size_t i = 0; i < 5; i++) {
		sem_destroy(poleSemaforov[i]);
		munmap(poleSemaforov[i], sizeof(poleSemaforov[i]));
	}
	
	printf("\nVYSLEDNA HODNOTA 5! = %d\n", *zd_pamat);
} 

static void proces_vytvor(Proces *proces, int koeficient) {
	proces->semafory_wait = up_front_vytvor();
	proces->semafory_signal = up_front_vytvor();
	proces->koeficient = koeficient;
}

static void proces_vykonaj(Proces* proces) {
	while (!up_front_je_prazdny(proces->semafory_wait)) {
		sem_wait((sem_t *) up_front_pop(proces->semafory_wait));
	}
	
	int zdielana_pam_id;
	int* zd_pamat;
	key_t key = ZD_PAMAT_KLUC;
	if ((zdielana_pam_id = shmget(key, ZD_PAMAT_KLUC, IPC_CREAT | 0666)) < 0) {
		fprintf(stderr, "chyba pri inicializacii zdielanej pamate");
		return;
	}
	zd_pamat = (int*) shmat(zdielana_pam_id, NULL, 0);
	if (zd_pamat == (int *) -1) {
		fprintf(stderr, "chyba pri alokacii pamate\n");
		return;
	}
	
	printf("\n*************************************************************\n");
	printf("Pred vykonanim procesu\n");
	printf("\thodnota = %d\t", *zd_pamat);
	printf("\tkoeficient = %d\n", proces->koeficient);
	
	*zd_pamat *= proces->koeficient;
	
	printf("Po vykonanim procesu\n");
	printf("\thodnota = %d\t", *zd_pamat);
	printf("\tkoeficient = %d\n", proces->koeficient);
	
	while (!up_front_je_prazdny(proces->semafory_signal)) {
		sem_post((sem_t *) up_front_pop(proces->semafory_signal));
	}
}


