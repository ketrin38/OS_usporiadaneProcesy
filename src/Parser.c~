#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "Matica.h"
#include "Parser.h"

#define MAX_POCET_RIADKOV 3
#define MAX_DLZKA_RIADKU 50

#define ZNAK_NA_CISLO(z) ((z) - '0')


static char** nacitaj_subor_pamat(const char* nazov_suboru, int* poc_riadkov);
static void zrus_subor_pamat (char **buffer, int poc_riadkov);

static void nacitaj_riadok (const char** buffer, int** inc_matica,
	int riadok_index, int predosly_proces, int poz, int poc_riadkov);
static Matica* nacitaj_inc_maticu (const char** buffer);

Matica* up_parser_nacitaj_subor(const char* nazov_suboru) {
	int poc_riadkov;
	char** buffer = nacitaj_subor_pamat (nazov_suboru, &poc_riadkov);
	
	for (int i = 0; i < poc_riadkov; i++) {
		printf("%s\n", buffer[i]);
	}
	
	Matica* matica = nacitaj_inc_maticu((const char **) buffer);
	
	zrus_subor_pamat(buffer, poc_riadkov);
	
	return matica;
} 

static char** nacitaj_subor_pamat(const char* nazov_suboru, int* poc_riadkov) {
	FILE *fr = fopen(nazov_suboru, "r");
	if ((fr == NULL))
	{
		fprintf(stderr,"chyba: ubor sa nepodarilo otvorit: %s",
			strerror(errno));
		return NULL;
	}
	 
	char** buffer = (char **) malloc (MAX_POCET_RIADKOV * sizeof(char *));
	memset (buffer, 0, MAX_POCET_RIADKOV);
	
	int riadok_index = 0;
	int maxDlzka = 0;
	while (!feof(fr)) {
		char* riadok = (char *) malloc (MAX_DLZKA_RIADKU * sizeof(char));
		fgets (riadok, MAX_DLZKA_RIADKU, fr);
		int aktualna_dlzka = strlen(riadok);
		for (int i = aktualna_dlzka; i < MAX_DLZKA_RIADKU; i++) {
			riadok[i] = ' ';
		}
		if (aktualna_dlzka > maxDlzka) {
			maxDlzka = aktualna_dlzka;
		}
		if (riadok[aktualna_dlzka - 1] == '\n') {
			riadok[aktualna_dlzka - 1] = ' ';			
		}
		buffer[riadok_index] = riadok;
		riadok_index++;
	}
	
	*poc_riadkov = riadok_index;
	
	for (int i = 0; i < *poc_riadkov; i++) {
		buffer[i][maxDlzka] = '\0';
	}
	
	fclose(fr);
	return buffer;
} 

static void zrus_subor_pamat (char **buffer, int poc_riadkov)
{
	for (int i = 0; i < poc_riadkov; i++) {
		free ((void *) buffer[i]);
	}
	
	free ((void *) buffer);
}

static void nacitaj_riadok (const char** buffer, int** inc_matica,
	int riadok_index, int predosly_proces, int poz, int poc_riadkov)
{
	int i = poz;
	char aktualny_znak = buffer[riadok_index][i];
	while (aktualny_znak != '\0') {
		aktualny_znak = buffer[riadok_index][i];
		if (isdigit(aktualny_znak)) {
			int cislo_proc = (int) ZNAK_NA_CISLO(aktualny_znak);
			if (predosly_proces == 0) {
			} else {
				inc_matica[predosly_proces - 1][cislo_proc - 1] = 1;
			}
			predosly_proces = cislo_proc;
		}
		
		if (riadok_index >= 2) {
			char znak_vyssie = buffer[riadok_index - 1][i];
			if (znak_vyssie == '/') {
				nacitaj_riadok(buffer, inc_matica, riadok_index - 2,
					predosly_proces, i, poc_riadkov);
			}
		} else if (riadok_index < (poc_riadkov - 1)) {
			char znak_nizsie = buffer[riadok_index + 1][i];
			if (znak_nizsie == '\\') {
				nacitaj_riadok(buffer, inc_matica, riadok_index + 2,
					predosly_proces, i, poc_riadkov);
			}
		}
		i++;
	}
}

static Matica* nacitaj_inc_maticu (const char** buffer)
{
	Matica* matica = up_matica_vytvor(5);
	nacitaj_riadok(buffer, up_matica_vrat_pole(matica), 2, 0, 0, 3);
	return matica;
}

