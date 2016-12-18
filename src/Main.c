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
