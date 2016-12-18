#include <stdlib.h>

#include "Matica.h"

Matica* up_matica_vytvor(size_t velkost_strany) {
	Matica *inst = (Matica *) malloc(sizeof(Matica));
	inst->velkost_strany = velkost_strany;
	inst->pole = (int **) malloc(velkost_strany * sizeof(int));
	for (int i = 0; i < velkost_strany; i++) {
		inst->pole[i] = (int *) malloc(velkost_strany * sizeof(int));
	}
	return inst;
}
 
int** up_matica_vrat_pole(Matica* inst){
	return inst->pole;
}

size_t up_matica_daj_velkost (Matica* inst)
{
	return inst->velkost_strany;
}

void up_matica_zrus(Matica* inst){
	for (int i = 0; i < inst->velkost_strany; i++) {
		free ((void *) inst->pole[i]);
	}
	free ((void *) inst->pole);
	free((void *) inst);
}
