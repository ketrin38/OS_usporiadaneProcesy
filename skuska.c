#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 


static void procesA(sem_t* sem_b, sem_t* sem_c);
static void procesB(sem_t* sem_b, sem_t* sem_a);
static void procesC(sem_t* sem_d, sem_t* sem_c);
static void procesD(sem_t* sem_d, sem_t* sem_a);

int main () {
	printf("Vytvaram semafory  ...... \n");
	sem_t *sem_a = sem_open("test_a", O_CREAT|O_EXCL, 0644, 0);
    sem_t *sem_b= sem_open("test_b", O_CREAT|O_EXCL, 0644, 0);
	sem_t *sem_c= sem_open("test_c", O_CREAT|O_EXCL, 0644, 0);
	sem_t *sem_d= sem_open("test_d", O_CREAT|O_EXCL, 0644, 0);
	printf("Inicializujem semafory  ...... \n");
	sem_unlink("test_a"); // INICIALIZOVAT!
    sem_unlink("test_b");
    sem_unlink("test_c"); // INICIALIZOVAT!
    sem_unlink("test_d");

	sem_init(sem_a,0,0);
	sem_init(sem_b,0,0);
	sem_init(sem_c,0,0);
	sem_init(sem_d,0,0);
	
	procesA(sem_b,sem_c);
	procesB(sem_b,sem_a);
	procesC(sem_d,sem_c);
	procesD(sem_d,sem_a);
	
	printf("Skoncil som sa .... \n");
	sem_destroy(sem_a);
	sem_destroy(sem_b);
	sem_destroy(sem_c);
	sem_destroy(sem_d);
	printf("zmazal som semafory .... \n");
} 


static void procesA(sem_t* sem_b, sem_t* sem_c) {
	printf("Som A\n");
	sem_post(sem_b);
	sem_post(sem_c);
} 
static void procesB(sem_t* sem_b, sem_t* sem_a) {
	sem_wait(sem_b);
	printf("Som B\n");
	sem_post(sem_a);
} 
static void procesC(sem_t* sem_d, sem_t* sem_c) {
	sem_wait(sem_c);
	printf("Som C\n");
	sem_post(sem_d);
} 
static void procesD(sem_t* sem_d, sem_t* sem_a) {
	sem_wait(sem_a);
	printf("Som pred D\n");
	sem_wait(sem_d);
	printf("Som D\n");
} 
