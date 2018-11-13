#include "dispFunc.h"

void loadTankInMatrix(char **mat, Tank *tank){
    int i, j;
    int k = 0, l = 0;

    for(i=tank->posX; i<tank->posX+nbLineTank; i++){
        l=0;
        for(j=tank->posY; j<tank->posY+nbColTank; j++){
            mat[i][j] = tank->bodyWork[k][l];

            
            l++;
        }
        k++;
    }
    

}

//on initialise le tank et on charge le fichier de départ en fonction du type et de la direction du tank;
Tank *initTankPlayer(Tank *tank){
   tank->bodyWork = matrixAlloc(nbLineTank, nbColTank);
    //Position de départ de notre tank
   tank->posX=38;
   tank->posY=2;

   tank->armor = 1;
   tank->type= 'P'; //P pour player et E pour enemy
   tank->condition = 3;
 
   tank->direction='D';
   tank->id=1;

   return tank;
}

Tank *initTankEnemy(Tank *tank){
   int randPos = 0, randArmorMax = 0, randArmorMin = 0;

   randArmorMax = rand()%50-1;
   randArmorMin = rand()%20-5;
   randPos = rand()%2-1;

   tank->bodyWork = matrixAlloc(nbLineTank, nbColTank);
    //On génère aléatoirement les tanks à des positions différentes
   if(randPos == 1){
       tank->posX=2;
       tank->posY=94;
       tank->direction='B';
       
   }
   else{
       tank->posX=16;
       tank->posY=175;
       tank->direction='G';
   }
    //Position de départ du tank enemi

    if(randArmorMax == 13)
        tank->armor = 3;

    if(randArmorMin == 10  && randArmorMax != 13)
        tank->armor = 2;
    tank->armor = 1;

   tank->type= 'E'; //P pour player et E pour enemy
   tank->condition = 3;
 
   
   //à faire varier
   tank->id=0;

   return tank;
}

void moveTank(Tank *tank, char **map){
    int i, j;
    int k=tank->posX, l=tank->posY;

    for(i = 0 ; i < nbLineTank ; i++){
        l=0;
        for(j = 0;  j < nbColTank; j++){

            moveToPosXY(1+tank->posX+i, 1+tank->posY+j);
            printSwitch(tank->bodyWork[i][j]);
            
            map[k][l] = tank->bodyWork[i][j];
            
            l++;
        }
        k++;
    }

}

//fonction booléenne, retourne 1 si le tank peut avancer, 0 sinon

//Changer le raisonnement isfree par rapport au terminal
//PosX correspond à la position de l'extrémité 
int isFree(char **map, Tank *tank){
    //On va vérifier que toute la ligne devant le tank est libre pour qu'il puisse avancer
    int res = 0; 
    int posX = 0;
    int posY = 0;

    switch(tank->direction){
        //Si haut
        case 'H':
            posX = tank->posX;
            posX--;
            //Pour éviter les sorties du cadre
        
            if(posX>0){
                for(posY=tank->posY; posY < tank->posY+9; posY++){
                    if(map[posX][posY] == ' ')
                        res++;
                }
                //On vérifie que toute la ligne (de taille largeurTank)
                if(res == nbColTank)
                    return 1;
                else
                    return 0;
                break;
            }
        //Si Bas
        case 'B':
            posX = tank->posX;
            posX+=(nbLineTank); //Pour descendre d'une ligne +1
            if(posX<53){
                for(posY=tank->posY; posY < tank->posY+9; posY++){
                    if(map[posX][posY] == ' ')
                        res++;
                }
                //On vérifie que toute la ligne (de taille largeurTank)
                if(res == nbColTank)
                    {
                        return 1;
                    }
                   
                else
                    return 0;
                break;
            }
        //Si Gauche
        case 'G':
            posY=tank->posY;
            posY--;
            if(posY>0){
                for(posX=tank->posX; posX < tank->posX+5; posX++){
                    if(map[posX][posY] == ' ')
                        res++;
                }
                if(res == nbLineTank)
                {
                    return 1;
                }
                else  
                {
                    return 0;
                }
                break;
            }
        case 'D':
            posY=tank->posY;
            posY+=(nbColTank+1); //par rapport à la gauche +1
            if(posY<186){
                for(posX=tank->posX; posX < tank->posX+5; posX++){
                    if(map[posX][posY] == ' ')
                        res++;
                }
                 if(res == nbLineTank)
                {
                    return 1;
                }
                else  
                {
                    return 0;
                }
                break;
            }
    }
    return EXIT_FAILURE;
}

void deleteTank(Tank *tank, char **map){
    int i, j;
    int k=tank->posX, l=tank->posY;

        for(i=0; i < nbLineTank; i++){
            l=0;
            for(j=0; j < nbColTank; j++){

                moveToPosXY(1+tank->posX+i, 1+tank->posY+j);
                printf(" ");
                
                map[k][l] = ' ';
                
                l++;
            }
            k++;
        }
}

void moveTankEnemy(Tank *e,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map){

   int nbAl = 0; 

    if(e->armor == 1){
        nbAl = rand()%4-1;
            switch(nbAl){
                case 1:
                        e->direction = 'H';
                        if(isFree(map, e) ){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankH_ts, e->bodyWork);
                             e->posX--;
                             moveTank(e, map);

                        }
                        break;
                    
                case 2:
                        e->direction = 'B';
                        if(isFree(map, e)){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankB_ts, e->bodyWork);
                             e->posX++;
                             moveTank(e, map);
                            }
                        break;
                case 3:
                        e->direction = 'D';
                        if((isFree(map, e))){
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankD_ts, e->bodyWork);
                                 e->posY++;
                                 moveTank(e, map);
                                }
                        break;
                        
                case 4:
                        e->direction = 'G';
                        if(isFree(map, e)) {
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankG_ts, e->bodyWork);
                                 e->posY--;
                                 moveTank(e, map);
                                }
                                 break;
                /*
                case BANG:
                                Obus *o = generateObus(e, map, oList);
                                moveObus(o, map);
                                break;
                    }*/
            }
    }
            
    else if(e->armor == 2){
            nbAl = rand()%4-1;
            switch(nbAl){
                case 1:
                        e->direction = 'H';
                        if(isFree(map, e) ){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankH_tb, e->bodyWork);
                             e->posX--;
                             moveTank(e, map);

                        }
                        break;
                    
                case 2:
                        e->direction = 'B';
                        if(isFree(map, e)){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankB_tb, e->bodyWork);
                             e->posX++;
                             moveTank(e, map);
                            }
                        break;
                case 3:
                        e->direction = 'D';
                        if((isFree(map, e))){
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankD_tb, e->bodyWork);
                                 e->posY++;
                                 moveTank(e, map);
                                }
                        break;
                        
                case 4:
                        e->direction = 'G';
                        if(isFree(map, e)) {
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankG_tb, e->bodyWork);
                                 e->posY--;
                                 moveTank(e, map);
                                }
                                 break;
                /*
                case BANG:
                                Obus *o = generateObus(e, map, oList);
                                moveObus(o, map);
                                break;
                    }*/
            }
        }
    else if(e->armor == 3){
            nbAl = rand()%4-1;
            switch(nbAl){
                case 1:
                        e->direction = 'H';
                        if(isFree(map, e) ){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankH_tub, e->bodyWork);
                             e->posX--;
                             moveTank(e, map);

                        }
                        break;
                    
                case 2:
                        e->direction = 'B';
                        if(isFree(map, e)){
                             deleteTank(e, map);
                             replaceMatrixWithAnother(tankB_tub, e->bodyWork);
                             e->posX++;
                             moveTank(e, map);
                            }
                        break;
                case 3:
                        e->direction = 'D';
                        if((isFree(map, e))){
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankD_tub, e->bodyWork);
                                 e->posY++;
                                 moveTank(e, map);
                                }
                        break;
                        
                case 4:
                        e->direction = 'G';
                        if(isFree(map, e)) {
                                 deleteTank(e, map);
                                 replaceMatrixWithAnother(tankG_tub, e->bodyWork);
                                 e->posY--;
                                 moveTank(e, map);
                                }
                                 break;
                /*
                case BANG:
                                Obus *o = generateObus(e, map, oList);
                                moveObus(o, map);
                                break;
                    }*/
            }
        }
}



void moveTankPlayer(Tank *tankJ,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, int c, ObusList *obusList){
   
    switch(c) {
                        case UP:
                            tankJ->direction = 'H';
                            if(isFree(map, tankJ) ){
                                
                                deleteTank(tankJ, map);
                                
                                replaceMatrixWithAnother(tankH_ts, tankJ->bodyWork);
                                tankJ->posX--;
                                moveTank(tankJ, map);
                            }
                             break;
                    
                        case DOWN:
                            tankJ->direction = 'B';
                            if(isFree(map, tankJ)){
                                deleteTank(tankJ, map);
                                replaceMatrixWithAnother(tankB_ts, tankJ->bodyWork);
                                
                                tankJ->posX++;
                                moveTank(tankJ, map);
                                
                            }
                             break;
                        case RIGHT:
                                
                                tankJ->direction = 'D';
                                if((isFree(map, tankJ))){

                                    deleteTank(tankJ, map);
                                    replaceMatrixWithAnother(tankD_ts, tankJ->bodyWork);
                                    tankJ->posY++;
                                    moveTank(tankJ, map);
                                }
                                 break;
                        
                        case LEFT:
                                tankJ->direction = 'G';
                                if(isFree(map, tankJ)) {
                                    
                                    deleteTank(tankJ, map);
                                    replaceMatrixWithAnother(tankG_ts, tankJ->bodyWork);
                                    
                                    tankJ->posY--;
                                    moveTank(tankJ, map);
                                
                                }
                                 break;
                        
                        case BANG:
                                generateObus(tankJ, map, obusList);
                                moveObus(obusList, map);
                                break;
                    } 
}


Obus *initObus(Obus *o){
    o->caractere = 'C';
    o->posX = 0;
    o->posY = 0;

    return o;
}

void generateObus(Tank *t, char **map, ObusList *obusList){
    Obus *o = NULL;
    o = initObus(o);
    switch(t->direction){
        case 'H':
            
            o->direction = 'H';
            o->posX = t->posX--;
            o->posY = t->posY+5;
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            printf("✴");
            break;

        case 'B':

            o->direction = 'B';
            o->posX = t->posX+6; 
            o->posY = t->posY+5;
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            printf("✴");
            break;

        case 'G':

            o->direction = 'G';
            o->posX += t->posX+3; 
            o->posY = t->posY--; 
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            printf("✴");
            break;

        case 'D':
            o->direction = 'D';
            o->posX += t->posX+3; 
            o->posY = (t->posY+10);
            map[o->posX][o->posY] = o->caractere;
            moveToPosXY(o->posX, o->posY);
            printf("✴");
            break;
    }

    //Permet de stocker les infos sur les obus dans la liste
    insertNewObus(obusList, o);
   
}

void moveObus(ObusList *obusList, char **map){
    int posX = 0, posY = 0;

    while(obusList != NULL){
        switch(obusList->firstObus->direction){

            case 'H':
                posX = obusList->firstObus->posX--;
                posY = obusList->firstObus->posY;

                if(map[posX][posY] != ' '){
                    map[posX][posY] = ' ';
                    map[posX+1][posY]= ' ';
                    break;
                }
                map[posX+1][posY]= ' ';
                printf(" ");

                map[posX][posY] = obusList->firstObus->caractere;
                printf("✴");
                
            case 'B':
                posX = obusList->firstObus->posX++;
                posY = obusList->firstObus->posY;

                if(map[posX][posY] != ' '){
                    map[posX][posY] = ' ';
                    break;
                }
                map[posX-1][posY]= ' ';
                printf("%c", map[posX-1][posY]);

                map[posX][posY] = obusList->firstObus->caractere;
                printf("✴");
                
                break;

            case 'G':
                posX = obusList->firstObus->posX;
                posY = obusList->firstObus->posY-1;
            
                if(map[posX][posY] != ' '){
                        map[posX][posY] = ' ';
                        break;
                    }
                map[posX][posY-1]= ' ';
                printf("%c", map[posX][posY-1]);

                map[posX][posY] = obusList->firstObus->caractere;
                printf("✴");
                
                break;

            case 'D':
                posX = obusList->firstObus->posX;
                posY = obusList->firstObus->posY+1;

                if(map[posX][posY] != ' '){
                        map[posX][posY] = ' ';
                        break;
                    }

                map[posX][posY+1]= ' ';
                //mettre le curseur à cette position?
                printf("%c", map[posX][posY+1]);

                map[posX][posY] = obusList->firstObus->caractere;
                printf("✴");
                break;
        }
        obusList->firstObus = obusList->firstObus->next;
    }
}




int key_pressed(){
    struct termios oldterm, newterm;

    int oldfd; char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) {ungetc(c, stdin); result = getchar();}
    return result;
}
