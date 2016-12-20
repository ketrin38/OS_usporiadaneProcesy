/**
 * @file App.h
 * @author Katarina Pilarcikova <ketrin.pilarcik@gmail.com
 * @date 20 Dec 2016
 * @brief Modul zodpoveny za beh aplikacie.
 */
 
#ifndef APP_H
#define APP_H

/**
 * @brief Pseudo-objekt specifikacia atributov
 *
 * Reprezentuje instanciu aplikacie
 */
typedef struct _App {
	const char* nazov_suboru; /**< Nazov vstupneho suboru s orientovanym grafom. */
} App;


/**
 * @brief Inicializacia aplikacie.
 *
 * @param nazov_suboru Nazov vstupneho suboru s orientovanym grafom.
 * @return Instancia matice.
 */
extern App* up_app_vytvor(const char* nazov_suboru);

/**
 * @brief Spustenie instancie aplikacie. 
 *
 * @param inst Smernik na aplikaciu, kt. pozadujeme spustit.
 */
extern void up_app_spusti(App* inst);

/**
 * @brief Zrusenie instancie aplikacie. 
 *
 * @param inst Smernik na aplikaciu, kt. pozadujeme zrusit.
 */
extern void up_app_zrus(App* inst);

#endif
