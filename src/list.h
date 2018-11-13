#include "tank.h"

/** Fonctions liées à la liste de tanks **/
TankList *initTankList(Tank *tank);
void insertNewTank(TankList *list, Tank *tank);
void deleteFirstTank(TankList *list);
void deleteTankById(TankList *list, int id);
void dispTankList(TankList *list);

/** Fonctions liées à la liste des obus **/
ObusList *initObusList(Obus *obus);
void insertNewObus(ObusList *list, Obus *obus);
void deleteFirstObus(ObusList *obus);
void deleteObusById(ObusList *list, int id);
void dispObusList(ObusList *list);
