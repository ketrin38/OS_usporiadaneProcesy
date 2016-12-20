/**
 * @file main.c
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za riadenie a vytvorenie udajovej strukury front.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>

#include "Front.h"
#include "Parser.h"
#include "App.h"

static void pouzitie(char* nazov_programu) {
	printf("Pouzitie programu: %s <nazov_suboru>\n", nazov_programu);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "chyba: neplatne argumenty\n\n");
		pouzitie(basename(argv[0]));
		return EXIT_FAILURE;
	}
	
	App* app = up_app_vytvor(argv[1]);
	up_app_spusti(app);
	up_app_zrus(app);
	
	return EXIT_SUCCESS;
} 
