#include "tank.h"



/** Fonctions liées à la liste de tanks **/
TankList *initTankList();
void insertNewTank(TankList *list, Tank *tank);
void deleteFirstTank(TankList *list);
void dispTankList(TankList *list);

/** Fonctions liées à la liste des obus **/
ObusList *initObusList();
void insertNewObus(ObusList *list, Obus *obus);
void deleteFirstObus(ObusList *obus);
void dispObusList(ObusList *list);
