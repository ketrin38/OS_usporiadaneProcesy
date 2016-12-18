#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types,h>

#include "Parser.h"
#include "App.h"
#include "Matica.h"

static void nacitaj_procesy(App* inst);

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

void nacitaj_procesy(App* inst) {
	
} 
