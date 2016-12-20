#ifndef FRONT_H
#define FRONT_H

/**
 * @file Front.h
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za riadenie a vytvorenie udajovej strukury front.
 */

/**
 * @brief Pseudo-objekt specifikacia atributov.
 *
 * Reprezentuje instanciu udajovej struktury front implementovany implicitne.
 */
typedef struct _Front {
	void** pole;  /**< Pole riadniace front. */
	size_t poc_prkov; /**< Pocet prvkov vo fronte. */
	int akt_pozicia_pop; /**< Aktualna pozicia vo fronte na pop operaciu. */
	int akt_pozicia_push; /**< Aktualna pozicia vo fronte na pusp operaciu. */
} Front;


/**
 * @brief Inicializuje front.
 *
 * @return Pointer na instanciu frontu
 */
extern Front* up_front_vytvor();

/**
 * @brief Zrusenie frontu.
 *
 * @param inst Smernik na instanciu frontu, kt pozadujeme zrusit.
 */
extern void up_front_zrus(Front* inst);

/**
 * @brief Pridanie prvku do frontu.
 *
 * @param inst Instancia frontu do ktoreho chceme pridat prvok.
 * @param prvok Pridavany prvok do frontu.
 */
extern void up_front_push(Front* inst, void* prvok);

/**
 * @brief Odobratie prvku z frontu.
 *
 * @param inst Instancia frontu z ktoreho vyberame.
 * @return Prvok z prvy vo fronte.
 */
extern void* up_front_pop(Front* inst);

/**
 * @brief Spristupnenie prveho prvku na pop.
 *
 * @param inst Instancia frontu z ktoreho zistujeme prvok.
 */
extern void* up_front_peek(Front* inst);

/**
 * @brief Zisti, ci je front prazdny.
 *
 * @param inst Instancia frontu
 * @return 0 ak obsahuje prvky, 1 aj je prazdny.
 */
extern int up_front_je_prazdny(Front* inst);

/**
 * @brief Vrati pocet prvkov frontu.
 *
 * @param inst Instancia frontu
 * @return size_t Aktualny pocet prvkov frontu.
 */
extern size_t up_front_daj_poc_prvkov(Front* inst);

#endif
