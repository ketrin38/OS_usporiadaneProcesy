#include <stdlib.h>
#include "Front.h"

#define POVODNA_VELKOST 10

Front* up_front_vytvor() {
	Front* inst = (Front*)malloc(sizeof(Front));
	inst->pole = (int*)malloc(POVODNA_VELKOST * sizeof(int));
	inst->poc_prkov = 0;
	inst->akt_pozicia_pop = 0;
	inst->akt_pozicia_push = 0;
	return inst;
}

void up_front_zrus(Front* inst){
	free(inst->pole);
	free(inst);
}

void up_front_push(Front* inst, int prvok) {
	inst->pole[inst->akt_pozicia_push] = prvok;
	inst->poc_prkov++;
	inst->akt_pozicia_push++;
}

int up_front_pop(Front* inst){
	int docasny = inst->pole[inst->akt_pozicia_pop]; 
	inst->poc_prkov--;
	inst->akt_pozicia_pop++;
	return docasny;
}

int up_front_peek(Front* inst) {
	return inst->pole[inst->akt_pozicia_pop];
} 

int up_front_je_prazdny(Front* inst){
	return inst->poc_prkov == 0;
}

size_t up_front_daj_poc_prvkov(Front* inst) {
	return inst->poc_prkov;
}


