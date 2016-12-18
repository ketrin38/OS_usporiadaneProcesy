#ifndef MATICA_H
#define MATICA_H

typedef struct _Matica {
	int** pole;
	size_t velkost_strany;
} Matica;

extern Matica* up_matica_vytvor(size_t velkost_strany);
extern int** up_matica_vrat_pole(Matica* inst);
extern size_t up_matica_daj_velkost (Matica* inst);
extern void up_matica_zrus(Matica* inst);

#endif