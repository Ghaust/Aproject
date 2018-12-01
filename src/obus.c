#include "dispFunc.h"

Obus *initObus(){
    Obus *o = malloc(1*sizeof(Obus));

    o->posX = 0;
    o->posY = 0;
    o->timer = 0;

    return o;
}


ObusList *generateObus(Tank t, char **map, ObusList *obusList){
    Obus *o = initObus();
    o->provenance = t.id;
    switch(t.direction){

        case 'H':

            o->direction = 'H';
            o->posX = t.posX--;
            o->posY = t.posY+5;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'B':

            o->direction = 'B';
            o->posX = t.posX+6;
            o->posY = t.posY+5;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'G':

            o->direction = 'G';
            o->posX = t.posX+3;
            o->posY = t.posY--;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'D':
            o->direction = 'D';
            o->posX = t.posX+3;
            o->posY = (t.posY+10);
            moveToPosXY(o->posX, o->posY);
            break;
    }
    printf("✴");

    //Permet de stocker les infos sur les obus dans la liste
    insertNewObus(obusList, o);
    return NULL;
}


void checkIfPiouPiouIsAlright(char c){
    FILE *fgameover = NULL;
    fgameover = fopen("../models/menus/gameover.txt", "r+");

    if(fgameover != NULL){
        if(c == 'K'){
            system("clear");
            dispFile(fgameover);

            fclose(fgameover);
            exit(0);
        }
    }
}

// Tank *t, TankList *tList
int collision(Obus *o, char **map, int oldX, int oldY){
    int oldx, oldy;
    oldx = o->posX;
    oldy=o->posY;

    switch(map[o->posX][o->posY]){
        case 'R':        //Brique blanche
            map[o->posX][o->posY]= ' ';
            return 0;
        case 'A':           //Brique rouge
            map[o->posX][o->posY]= 'R';
            return 1;
        case 'K':         //Oiseau
            checkIfPiouPiouIsAlright('K');
        case 'E':       //Eau
            return 2;
        case '|':
            map[o->posX][o->posX] = ' ';
            return 2;
        case '-':
            map[o->posX][o->posX] = ' ';
            return 2;
        case ' ':
            return 3;
        default:
            return 4;

    }
}


void moveObus(ObusList *o, char **map, Tank *t, TankList *tList){
    int oldX, oldY;
    int returnValue = 0; int id_tank_damaged = 0;
    if(o->firstObus->next==NULL) return;
    Obus *obus = o->firstObus->next;

    
    while(obus != NULL){
       if(obus->timer>1000){
            oldX = obus->posX;
            oldY = obus->posY;

           if(obus->direction == 'H')
                obus->posX--;
            else if(obus->direction == 'B')
                obus->posX++;
            else if(obus->direction == 'G')
                obus->posY--;
            else if(obus->direction == 'D')
                obus->posY++;
            
            returnValue = collision(obus, map, oldX, oldY);

            switch(returnValue){
                case 0:
                    moveToPosXY(oldX, oldY);
                    printf(" ");
                    moveToPosXY(obus->posX, obus->posY);
                    printf(" ");
                    deleteObusById(o, obus->id);
                    break;
                case 1:
                    moveToPosXY(oldX, oldY);
                    printf(" ");
                    moveToPosXY(obus->posX, obus->posY);
                    printf(" ");
                    moveToPosXY(obus->posX, obus->posY);
                    printf("\033[37m☎");
                    deleteObusById(o, obus->id);
                    break;
                case 2:
                    moveToPosXY(oldX, oldY);
                    printf(" ");
                    deleteObusById(o, obus->id);
                    break;
                case 3:
                    moveToPosXY(oldX, oldY);
                    printf(" ");
                    moveToPosXY(obus->posX, obus->posY);
                    printf("✴");
                    break;
                case 4:
                    moveToPosXY(oldX, oldY);
                    id_tank_damaged = map[obus->posX][obus->posY];
                    damage_tank(tList, id_tank_damaged, obus->provenance, map, o);
                    break;
            }
            obus->timer = 0;
        }else{
          obus->timer++;
        }
        obus = obus->next;
    }

}
