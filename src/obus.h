#include "dispFunc.h"

/** Fonctions liées à tout ce qui touche aux obus **/
Obus *initObus();
ObusList *generateObus(Tank t, char **map, ObusList *obusList);
void collision(Obus *o, char **map, int oldX, int oldY);
void moveObus(ObusList *obusList, char **map, Tank *t, TankList *tList);
void explodeTank(Tank *t);
int checkIfPiouPiouIsAlright(char c);
void checkArmor(Tank *t, TankList *tList, char **map);