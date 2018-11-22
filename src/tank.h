#include "headers.h"
#define moveToPosXY(x, y) printf("\033[%d;%dH", (x), (y))

/** Fonctions liées à tout ce qui touche aux tanks **/
void loadTankInMatrix(char **mat, Tank *tank);
Tank *initTankPlayer(Tank *tank);
Tank *initTankEnemy(Tank *tank);
void moveTank(Tank *tank, char **map);
int isFree(char **map, Tank *tank);
void deleteTank(Tank *tank, char **map);
void moveTankEnemy(Tank *e,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map);


void moveTankPlayer(Tank *tankJ,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, int c, ObusList *obusList);

/** Fonctions liées à tout ce qui touche aux obus **/
Obus *initObus(Obus *o);
ObusList *generateObus(Tank *t, char **map, ObusList *obusList);
void moveObus(ObusList *obusList, char **map);



int key_pressed();
