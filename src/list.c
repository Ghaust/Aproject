#include "list.h"

//Cette fonction prend en paramètre le tank qui a déjà été initialisé pour pouvoir initialiser son ID
TankList *initTankList(Tank *tank){

    TankList *list = malloc(sizeof(*list));

    if(list == NULL || tank == NULL)
        exit(EXIT_FAILURE);

    list->firstTank = tank;
    tank->next = NULL;
    tank->id = 1;
    list->id = 1;

    return list;
}

void insertNewTank(TankList *list, Tank *tank){

    if(list == NULL || tank == NULL)
        exit(EXIT_FAILURE);
    list->id++;
    tank->id = list->id;

    Tank *actuel = list->firstTank;
    while(actuel->next != NULL){
        actuel = actuel->next;
    }
    actuel->next = tank;
    tank->next = NULL;

}

void deleteFirstTank(TankList *list){
    if(list == NULL)
        exit(EXIT_FAILURE);

    if(list->firstTank != NULL){

        Tank *toDelete = list->firstTank;
        list->firstTank = list->firstTank->next;
        free(toDelete);

    }
}

int damage_tank(TankList *tList, int id_damaged, int id_damager, char **map, ObusList *oList) {
  if((id_damaged!=90)&&(id_damager!=90)) 
        return 0;
  Tank* actuel;
  Tank* damaged = NULL;
  Tank* damager = NULL;
  actuel = tList->firstTank;
  while(actuel!=NULL) {
    if(actuel->id == id_damaged) damaged = actuel;
    if(actuel->id == id_damager) damager = actuel;
    actuel = actuel->next;
  }
  //damaged->touche += damager->statut;
  damaged->armor--;
  if(damaged->armor == 1) {
    deleteAllObus(id_damaged, oList);
    deleteTankById(tList, damaged->id, map);
    return 1;
  }
  return 0;
}


void deleteTankById(TankList *list, int id, char **map){
  if(list == NULL)
     exit(EXIT_FAILURE);

  if(list->firstTank->id == id) {
    Tank *toDelete = list->firstTank;
    deleteTank(toDelete, map);
    list->firstTank = list->firstTank->next;
    return;
  }

  Tank *next;
  Tank *actualT = list->firstTank;
  while(actualT != NULL) {
    if(actualT->next->id == id) {
      next = actualT->next->next;
      deleteTank(actualT->next, map);
      free(actualT->next);
      actualT->next = next;
      return;
    }
    actualT = actualT->next;
  }
}


void dispTankList(TankList *list){
    if(list == NULL)
        exit(EXIT_FAILURE);

    Tank *first = list->firstTank;

    while(first != NULL){
        printf("%d -> ", first->id);
        first = first->next;
    }
    printf("NULL\n");
}

ObusList *initObusList(){

    ObusList *list = malloc(sizeof(*list));
    Obus *obus = malloc(sizeof(*obus));

    if(list == NULL || obus == NULL)
        exit(EXIT_FAILURE);

    list->firstObus = obus;
    obus->next = NULL;
    obus->id = 1;
    list->id = 1;
    return list;
}

void insertNewObus(ObusList *list, Obus *obus){

    if(list == NULL || obus == NULL)
        exit(EXIT_FAILURE);

    list->id++;
    obus->id = list->id;
    Obus *actuel = list->firstObus;
    
    while(actuel->next != NULL){
      actuel=actuel->next;
    }
    actuel->next= obus;
    obus->next=NULL;
}

void deleteFirstObus(ObusList *list){
    if(list == NULL)
        exit(EXIT_FAILURE);
    if(list->firstObus != NULL){

        Obus *toDelete = list->firstObus;
        list->firstObus = list->firstObus->next;
        free(toDelete);

    }
}


void deleteObusById(ObusList *list, int id){
  if(list == NULL)
     exit(EXIT_FAILURE);

  if(list->firstObus->id == id) {
    list->firstObus = list->firstObus->next;
    return;
  }

  Obus *next;
  Obus *actualO = list->firstObus;

  while(actualO->next != NULL) {
    if(actualO->next->id == id) {
      next = actualO->next->next;
      free(actualO->next);
      actualO->next = next;
      return;
    }
    actualO = actualO->next;
  }
}

void deleteAllObus(int iddamaged, ObusList *list) {
  Obus *actuel = list->firstObus->next;
  while(actuel != NULL) {
    if(actuel->provenance == iddamaged) {
      moveToPosXY(actuel->posX, actuel->posY);
      deleteObusById(list, actuel->id);
    }
    actuel = actuel->next;
  }
}


void dispObusList(ObusList *list){
    if(list == NULL)
        exit(EXIT_FAILURE);

    Obus *first = list->firstObus;

    while(first != NULL){
        printf("%d -> ", first->id);
        first = first->next;
    }
    printf("NULL\n");
}
