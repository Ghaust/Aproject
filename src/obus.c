#include "dispFunc.h"

Obus *initObus(Obus *o){
    o = malloc(1*sizeof(Obus));

    o->caractere = 'C';
    o->posX = 0;
    o->posY = 0;
    o->timer = 0;

    return o;
}


ObusList *generateObus(Tank *t, char **map, ObusList *obusList){
    Obus *o = NULL;
    o = initObus(o);

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
    printf("✴");

    //Permet de stocker les infos sur les obus dans la liste
    insertNewObus(obusList, o);
    return(obusList);
}

void explodeTank(Tank *t){
    int i, j;

    for(i=0; i<nbLineTank; i++){
        for(j=0; j<nbColTank; j++){

            moveToPosXY(1+t->posX+i, 1+t->posX+j);
            printf("\033[37m✴\033[00m");

        }
    }
}

void checkArmor(Tank *t, TankList *tList, char **map){
    switch(t->armor){
        case 1:
            explodeTank(t);
            deleteTank(t, map);
            deleteFirstTank(tList);
            break;
        case 2:
            t->armor--;
            break;
        case 3:
            t->armor--;
            break;

    }
}

int damage_tank(Tank *t, char c, Obus *o, TankList *tList, char **map){

    if(c != 'A' || c != 'R' || c != 'P' || c != 'E' || c != 'K'){
       checkArmor(t, tList, map);
       return 1;
    }
    return 0;
}


int changeBlock(char **map, int posX, int posY){
    if(map[posX][posY] == 'R'){

        map[posX][posY] = 'A';
        moveToPosXY(posX, posY);
        printf("\033[31m☎\033[00m");
        return 1;
    }else if(map[posX][posY] == 'A'){

        map[posX][posY] = ' ';
        moveToPosXY(posX, posY);
        printf(" ");

        return 1;
    }
    return 0;
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

void collision(Obus *o, char **map, ObusList *obusList, Tank *t, TankList *tList){
    int posX = o->posX, posY = o->posY;
	switch(o->direction){
        
        case 'H':
             if(map[o->posX-1][o->posY] == ' '){
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY] = ' ';
                printf(" ");
                
                o->posX--;
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY]=o->caractere;
                printf("✴");

                
            }
            else{
                //system("clear");
                //printf("%c\n\n", map[posX][posY]);
                /*damage_tank(t, map[posX-1][posY], o, tList, map) ||*/ 
                if(changeBlock(map, o->posX, o->posY))
                    deleteFirstObus(obusList->firstObus);
                checkIfPiouPiouIsAlright(map[o->posX][o->posY]);
                //;
                //exit(0);
            }
            break;
        case 'B':
             if(map[o->posX+1][o->posY] == ' '){
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY] = ' ';
                printf(" ");
                
                o->posX++;
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY]=o->caractere;
                printf("✴");

                
            }
            else{
                system("clear");
                printf("%c\n\n", map[posX][posY]);
                //damage_tank(t, map[posX-1][posY], o, tList, map);
                //checkIfPiouPiouIsAlright(map[posX-1][posY]);
                //changeBlock(map, posX, posY);
                exit(0);
            }
            break;
        case 'G':
             if(map[o->posX][o->posY-1] == ' '){
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY] = ' ';
                printf(" ");
                
                o->posY--;
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY]=o->caractere;
                printf("✴");

                
            }
            else{
                system("clear");
                printf("%c\n\n", map[posX][posY]);
                //damage_tank(t, map[posX-1][posY], o, tList, map);
                //checkIfPiouPiouIsAlright(map[posX-1][posY]);
                //changeBlock(map, posX, posY);
                exit(0);
            }
            break;
        case 'D':
            if(map[o->posX][o->posY+1] == ' '){
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY] = ' ';
                printf(" ");
                
                o->posY++;
                moveToPosXY(o->posX, o->posY);
                map[o->posX][o->posY]=o->caractere;
                printf("✴");

                
            }
            else{
                system("clear");
                printf("%c\n\n", map[posX][posY]);
                //damage_tank(t, map[posX-1][posY], o, tList, map);
                //checkIfPiouPiouIsAlright(map[posX-1][posY]);
                //changeBlock(map, posX, posY);
                exit(0);
            }
            break;
	}
}


void moveObus(ObusList *o, char **map, Tank *t, TankList *tList){
    int oldX, oldY;
    Obus *obus = o->firstObus->next;
    if(o == NULL)
        exit(EXIT_FAILURE);

	
    while(obus != NULL){
       if(obus->timer>500){
            oldX = obus->posX;
            oldY = obus->posY;

            switch(obus->direction){
                case 'H':

                    collision(obus, map, o, t, tList);
                    break;
                case 'B':
            
                    collision(obus, map, o, t, tList); 
                    break;

                case 'G':

                    collision(obus, map, o, t, tList);
                    break;

                case 'D':

                    collision(obus, map, o, t, tList);
                    break;
                    
            }
            
            obus->timer = 0;
        }else
            obus->timer++;
        obus = obus->next;
    }
    
}

