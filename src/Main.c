/**
 * @file main.c
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za riadenie a vytvorenie udajovej strukury front.
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "Front.h"
#include "Parser.h"
#include "App.h"

int main() {
	App* app = up_app_vytvor("./resources/semestralkaStruktura.txt");
	up_app_spusti(app);
	up_app_zrus(app);
	
	return 0;
} 
