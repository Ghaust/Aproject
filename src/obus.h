#include "dispFunc.h"

/** Fonctions liées à tout ce qui touche aux obus **/
Obus *initObus(Obus *o);
void generateObus(Tank *t, char **map, ObusList *obusList);
void moveObus(ObusList *obusList, char **map);