#ifndef FRONT_H
#define FRONT_H

typedef struct _Front {
	void** pole;
	size_t poc_prkov;
	int akt_pozicia_pop;
	int akt_pozicia_push;
} Front;

extern Front* up_front_vytvor();
extern void up_front_zrus(Front* inst);
extern void up_front_push(Front* inst, void* prvok);
extern void* up_front_pop(Front* inst);
extern void* up_front_peek(Front* inst);
extern int up_front_je_prazdny(Front* inst);
extern size_t up_front_daj_poc_prvkov(Front* inst);

#endif
