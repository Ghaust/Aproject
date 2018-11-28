#include "headers.h"
#define moveToPosXY(x, y) printf("\033[%d;%dH", (x), (y))

/** Fonctions liées à tout ce qui touche aux tanks **/
void loadTankInMatrix(char **mat, Tank *tank);
Tank *initTankPlayer(Tank *tank);
Tank *initTankEnemy(Tank *tank);
void moveTank(Tank *tank, char **map);
int isFree(char **map, Tank *tank);
void deleteTank(Tank *tank, char **map);

void generateTankEnemy(char **tankB_ts, char **tankB_tb, char **tankB_tub,
char **tankG_ts, char **tankG_tb, char **tankG_ub, 
char **map, TankList *tankList, int modeJeu);

void moveTankEnemy(char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, TankList *tankList);

void moveTankPlayer(Tank *tankJ,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, int c, ObusList *obusList);





int key_pressed();
