/**
 * @file Matica.c
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za riadenie a vytvorenie incidencnej matice.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Matica.h"

static void vycisti_pole(int **pole, size_t velkost);

Matica* up_matica_vytvor(size_t velkost_strany) {
	Matica *inst = (Matica *) malloc(sizeof(Matica));
	inst->velkost_strany = velkost_strany;
	inst->pole = (int **) malloc(velkost_strany * sizeof(int *));
	for (size_t i = 0; i < velkost_strany; i++) {
		inst->pole[i] = (int *) malloc(velkost_strany * sizeof(int));
	}
    vycisti_pole(inst->pole, inst->velkost_strany);
	return inst;
}
 
int** up_matica_vrat_pole(Matica* inst){
	return inst->pole;
}

size_t up_matica_daj_velkost (Matica* inst)
{
	return inst->velkost_strany;
}

void up_matica_vypis(Matica *inst)
{
	for (size_t i = 0; i < inst->velkost_strany; i++) {
		char *oddelovac = " ";
		for (size_t j = 0; j < inst->velkost_strany; j++) {
			printf("%s%3d", oddelovac, inst->pole[i][j]);
			oddelovac = " |";
		}
		printf("\n");	
	}
}

void up_matica_zrus(Matica* inst){
	for (size_t i = 0; i < inst->velkost_strany; i++) {
		free ((void *) inst->pole[i]);
	}
	free ((void *) inst->pole);
	free((void *) inst);
}

static void vycisti_pole(int **pole, size_t velkost) {
    for (size_t i = 0; i < velkost; i++) {
        for (size_t j = 0; j < velkost; j++) {
            pole[i][j] = 0;
        }
    }
}
