#include "dispFunc.h"

/** Fonctions liées à tout ce qui touche aux obus **/
Obus *initObus(Obus *o);
ObusList *generateObus(Tank *t, char **map, ObusList *obusList);
void collision(Obus *o, char **map, ObusList *obusList, Tank *t, TankList *tList);
void moveObus(ObusList *obusList, char **map, Tank *t, TankList *tList);
void damage_tank(Tank *t, char c, Obus *o, TankList *tList, char **map);
void explodeTank(Tank *t);
void changeBlock(char **map, Obus *o);
void checkIfPiouPiouIsAlright(char c);
void checkArmor(Tank *t, TankList *tList, char **map);