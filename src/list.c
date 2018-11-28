#include "list.h"

//Cette fonction prend en paramètre le tank qui a déjà été initialisé pour pouvoir initialiser son ID
TankList *initTankList(){

    TankList *list = malloc(sizeof(*list));
    Tank *tank = malloc(sizeof(*tank));

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

    list->firstTank->next = tank;
    list->firstTank->next->next = NULL;
    
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

    list->firstObus->next = obus;
    list->firstObus->next->next = NULL;
   
}

//Coder suppression en milieu de chaine
//Coder 
void deleteFirstObus(ObusList *list){
    if(list == NULL)
        exit(EXIT_FAILURE);
    if(list->firstObus != NULL){

        Obus *toDelete = list->firstObus;
        list->firstObus = list->firstObus->next;
        free(toDelete);

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
