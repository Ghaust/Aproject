#include "obus.h"

Obus *initObus(Obus *o){
    o = malloc(1*sizeof(Obus));

    o->caractere = 'C';
    o->posX = 0;
    o->posY = 0;

    return o;
}


void generateObus(Tank *t, char **map, ObusList *obusList){
    Obus *o = initObus(o);

    switch(t->direction){

        case 'H':
            
            o->direction = 'H';
            o->posX = t->posX--;
            o->posY = t->posY+5;
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'B':

            o->direction = 'B';
            o->posX = t->posX+6; 
            o->posY = t->posY+5;
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'G':

            o->direction = 'G';
            o->posX += t->posX+3; 
            o->posY = t->posY--; 
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            break;

        case 'D':
            o->direction = 'D';
            o->posX += t->posX+3; 
            o->posY = (t->posY+10);
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            break;
    }
    //printf("✴");

    //Permet de stocker les infos sur les obus dans la liste
    insertNewObus(obusList, o);
   
}

//void collision(Obus *o, )


void moveObus(ObusList *o, char **map){
    int oldX, oldY;
    Obus *obus = o->firstObus->next;

    if(o == NULL)
        return;

    while(obus != NULL){
        //if(obus->timer>6)
        oldX = obus->posX;
        oldY = obus->posY;

        switch(obus->direction){
            case 'H':

                obus->posX--;
                moveToPosXY(obus->posX, obus->posY);
                //collision
                break;
            case 'B':

                obus->posX++;
                moveToPosXY(obus->posX, obus->posY);
                
                break;
            case 'G':

                obus->posY--;
                moveToPosXY(obus->posX, obus->posY);
                
                break;
            case 'D':

                obus->posY++;
                moveToPosXY(obus->posX, obus->posY);
                
                break;
        }
        //printf("*");
        obus = obus->next;
    }
    
}


/*void shotObus(Tank *tankJ, char **map, ObusList *obusList, int c){
    
    if(c == BANG){    
        generateObus(tankJ, map, obusList);
        //moveObus(obusList, map);
    }
}*/

/*
void isFreeFromCollision(Obus *o, char **map){
    int posX = o->posX; 
    int posY = o->posY;

    if(map[posX][posY] != ' '){

        if(map[posX][posY] == 'R'){
            map[posX][posY] = ' ';

            moveToPosXY(o->posX, o->posY);
            printf(" ");
        }
        else if(map[posX][posY] == 'A'){
            map[posX][posY] = 'R';

            moveToPosXY(o->posX, o->posY);
            printf(" ");
        }
    }
    
*/


