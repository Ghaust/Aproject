#include "tank.h"



/** Fonctions liées à la liste de tanks **/
TankList *initTankList();
void insertNewTank(TankList *list, Tank *tank);
void deleteFirstTank(TankList *list);
void dispTankList(TankList *list);
void deleteTankById(TankList *list, int id, char **map);
void deleteObusById(ObusList *list, int id, char **map);

/** Fonctions liées à la liste des obus **/
ObusList *initObusList();
void insertNewObus(ObusList *list, Obus *obus);
void deleteFirstObus(ObusList *obus);
void dispObusList(ObusList *list);
