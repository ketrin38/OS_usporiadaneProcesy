#ifndef APP_H
#define APP_H

typedef struct _App {
	const char* nazov_suboru;
} App;

extern App* up_app_vytvor(const char* nazov_suboru);
extern void up_app_spusti(App* inst);
extern void up_app_zrus(App* inst);

#endif
