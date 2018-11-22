#include "dispFunc.h"

Obus *initObus(Obus *o){
    o = malloc(1*sizeof(Obus));

    o->caractere = 'C';
    o->posX = 0;
    o->posY = 0;

    return o;
}


ObusList *generateObus(Tank *t, char **map, ObusList *obusList){
    Obus *o = initObus(o);

    //printf("Adresse Obus dans generate Obus = %p\n", o);
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
	//printf("Adresse Obus dans generate Obus = %p\n", o);
    //Permet de stocker les infos sur les obus dans la liste
	//exit(0);
    insertNewObus(obusList, o);
    return(obusList);
}

void collision(Obus *o, char **map, ObusList *obusList){
	
	switch(o->direction){
	
		case 'H':
			if(map[o->posX--][o->posY] != ' '){
				//if map à cette pos correspond à un truc tank damage tank pour la vie
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
				deleteFirstObus(obusList);
				//gérer dégats
			}else{
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
			}
			break;
		case 'B':
			if(map[o->posX++][o->posY] != ' '){
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
				deleteFirstObus(obusList);
				//gérer dégats
			}else{
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
					printf(" ");
			}
			break;
		case 'G':
			if(map[o->posX][o->posY--] != ' '){
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
				deleteFirstObus(obusList);
				//gérer dégats
			}else{
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
					printf(" ");
			}
			break;
		case 'D':
			if(map[o->posX][o->posY++] != ' '){
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
				deleteFirstObus(obusList);	
				//gérer dégats
			}else{
				map[o->posX][o->posY] = ' ';
				moveToPosXY(o->posX, o->posY);
				printf(" ");
			}
			break;
		
	}	
}


void moveObus(ObusList *o, char **map){
    int oldX, oldY;
    Obus *obus = o->firstObus->next;

    if(o == NULL)
        exit(EXIT_FAILURE);

	
    while(obus != NULL){
        //if(obus->timer>6)
        oldX = obus->posX;
        oldY = obus->posY;

        switch(obus->direction){
            case 'H':

                obus->posX--;
                moveToPosXY(obus->posX, obus->posY);
		//exit(0);
                collision(obus, map, o);
                break;
            case 'B':

                obus->posX++;
                moveToPosXY(obus->posX, obus->posY);
		//exit(0);
                collision(obus, map, o);
                break;
            case 'G':

                obus->posY--;
                moveToPosXY(obus->posX, obus->posY);
		//exit(0);
                collision(obus, map, o);
                break;
            case 'D':

                obus->posY++;
                moveToPosXY(obus->posX, obus->posY);
                collision(obus, map, o);
                break;
        }
        printf("✴");

        obus = obus->next;
    }
    
}