#include <stdlib.h>
#include <stdio.h>
#include "Front.h"

int main() {
	Front* frontSemafor = up_front_vytvor();
	printf("%d\n",up_front_daj_poc_prvkov(frontSemafor));
	int a = 5;
	int b = 8;
	int c = 3;
	up_front_push(frontSemafor,&a);
	up_front_push(frontSemafor,&c);
	up_front_push(frontSemafor,&b);
	while(!up_front_je_prazdny(frontSemafor)){
		printf("%d\n",*(int *)up_front_pop(frontSemafor));
	}
	up_front_zrus(frontSemafor);
	return 0;
} 
