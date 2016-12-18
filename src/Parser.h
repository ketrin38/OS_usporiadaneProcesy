#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	/*int *nazov;
	printf("Zadajte nazov suboru, kde je struktura\n");
	scanf("%s", nazov);*/

	FILE *fr = fopen("suborNaNacitanie.txt", "r"); // subor, kde najdem strukturu
	FILE *fw = fopen("vyslednaMatica.txt", "w"); // subor, kde ulozim strukturu

	char * buffer = 0;
	if ((fr == NULL))
	{
		printf("Subor sa nepodarilo otvorit");
		return 1;
	}

	// Idem na koniec, aby som nasla velkost
	if (fseek(fr, 0L, SEEK_END) == 0) {
		long buff_size = ftell(fr);
		if (buff_size == -1);// CHYBA OSETRI TO DAJAKO KATKA :P ;

		// tu alokujem pamat podla velkosti
		buffer = malloc(sizeof(char) * (buff_size + 1));

		// idem na zaciatok suboru
		if (fseek(fr, 0L, SEEK_SET) != 0) { /* OSETRIT*/ }

		// natrepem to do pamate 
		size_t new_size = fread(buffer, sizeof(char), buff_size, fr);
		if (ferror(fr) != 0) {
			fputs("Chyba pri citani", stderr);
		}
		else {
			buffer[new_size++] = '\0'; // zaklincujem koniec
		}

		if (fclose(fr) == EOF)
			printf("Nastala chyba pri zatvatvarani suboru");

		// juchu ide to
		printf_s(buffer);

		/* ********************************* NAJDENIE ZNAKU V STRINGU
		char *hladanyZnak = "(P4)";
		getchar();
	
		const char *ptr = strstr(buffer, hladanyZnak);
		if (ptr != NULL) { // AK NASLO NIECO
			int index = ptr - buffer;
			printf(" bol najdeny na  %d\n ", index);
			// do something
         */

		// ********************************** NAJDENIE NAJVYSSIEHO CISLA PROCESU
		int max;
		while (*buffer) { 
			if (isdigit(*buffer)) {
				long val = strtol(buffer, &buffer, 10); // http://ics.upjs.sk/~novotnyr/blog/1392/c-prevod-retazcov-na-cisla-cez-atoi-a-strtol
				max = val;
				//printf("%ld\n", val); // 
			}
			else { // Otherwise, move on to the next character.
				buffer++;
			}
		}
		printf("\nMaximalne cislo procesu je %d ", max);

		// ************* VYTVORENIE POLA

		int **pole, i;
		pole = (int **)malloc(max * sizeof(int *));
		for (i = 0; i < max; i++) 
		{
			pole = (int *)malloc(max * sizeof(int));
		}


		// uvolnenie
		int j;
		for (i = 0; i < max; i++)
			free((void *) pole[i]);

		free((void *)pole);
		}

	getchar();
	// potom treba uvolnit NEZABUDNUT  |
	free(buffer);
	return 0;
}
