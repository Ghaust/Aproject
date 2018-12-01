#include "obus.h"

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


Tank *initTankEnemy(){
   Tank *tank = malloc(sizeof(Tank));
   int randArmorMax = 0, randArmorMin = 0;

   randArmorMax = rand()%50-1;
   randArmorMin = rand()%20-5;

   tank->bodyWork = matrixAlloc(nbLineTank, nbColTank);
    //On génère aléatoirement les tanks à des positions différentes

    if(randArmorMax == 13)
        tank->armor = 3;

    if(randArmorMin == 10  && randArmorMax != 13)
        tank->armor = 2;
    tank->armor = 1;

   tank->type= 'E'; //P pour player et E pour enemy
   tank->condition = 3;


   return tank;
}

int checkIfSpawnIsFree(char **map, int posX, int posY){
    int i, j;
    int isFree = 1;

    for(i=posX; i<posX+nbLineTank; i++){
        for(j=posY; j<posY+nbColTank; j++){
            if(map[i][j] != ' ')
                isFree=0;
        }
    }
    return isFree;
}

void generateTankEnemy(char **tankB_ts, char **tankB_tb, char **tankB_tub,
char **tankG_ts, char **tankG_tb, char **tankG_ub,
char **map, TankList *tankList){

    //Deux positions d'apparition de tanks sur la map, en haut et en bas
    int posX_droite = 2, posY_droite = 94, posX_haut = 16, posY_haut = 175, randPos;
    int nbTanks= 10;

    Tank *tank = initTankEnemy();

    randPos = rand()%2-1;
    
    if(randPos == 1){
                tank->posX = posX_droite;
                tank->posY = posY_droite;
                tank->direction = 'G';

                switch(tank->armor){
                        case 1:
                            replaceMatrixWithAnother(tankB_ts,tank->bodyWork);
                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                            else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                        case 2:
                            replaceMatrixWithAnother(tankB_tb,tank->bodyWork);

                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                            else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                        case 3:
                            replaceMatrixWithAnother(tankB_ts,tank->bodyWork);
                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                            else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                }
            }else{
                tank->posX = posX_haut;
                tank->posY = posY_haut;
                tank->direction = 'B';
                switch(tank->armor){
                        case 1:
                            replaceMatrixWithAnother(tankG_ts,tank->bodyWork);
                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                           else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                        case 2:
                            replaceMatrixWithAnother(tankG_tb,tank->bodyWork);
                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                            else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                        case 3:
                            replaceMatrixWithAnother(tankG_ts,tank->bodyWork);
                            if(checkIfSpawnIsFree(map, tank->posX, tank->posY) == 0)
                                return;
                            else{
                                loadTankInMatrix(map,tank);
                                moveTank(tank, map);
                            }
                            break;
                }
            }
            insertNewTank(tankList, tank);
            nbTanks--;
    /*do{



        //exit(0);
        }while(nbTanks != 0);*/


}

//on initialise le tank et on charge le fichier de départ en fonction du type et de la direction du tank;
Tank *initTankPlayer(){
    Tank *tank = malloc(sizeof(Tank));
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


void moveTank(Tank *tank, char **map){
    int i, j;
    for(i = 0 ; i < nbLineTank ; i++){
        for(j = 0;  j < nbColTank; j++){

            moveToPosXY(1+tank->posX+i, 1+tank->posY+j);
            printSwitch(tank->bodyWork[i][j]);

            map[tank->posX+i][tank->posY+j] = tank->bodyWork[i][j];

        }
    }

}

//fonction booléenne, retourne 1 si le tank peut avancer, 0 sinon

int isFree(char **map, Tank *tank){
    //On va vérifier que toute la ligne devant le tank est libre pour qu'il puisse avancer
    int res = 0;
    int posX = 0;
    int posY = 0;
    int i, j;
    int ok=1;
    switch(tank->direction){
        //Si haut
        case 'H':
            //Pour éviter les sorties du cadre

            if(tank->posX>0){
                for(i=0;i<nbColTank;i++){
                    if(map[tank->posX-1][tank->posY+i] != ' ')
                        return 0;
                }
                //On vérifie que toute la ligne (de taille largeurTank)
                return 1;
                break;
            }
        //Si Bas
        case 'B':
        ok=1;
            if(tank->posX<53){
                for(i=0;i<nbColTank;i++){
                    if(map[tank->posX+nbLineTank][tank->posY+i] != ' ') {
                      return 0;
                    }
                }
                return 1;
                break;
            }
        //Si Gauche
        case 'G':
            //posY--;
            if(tank->posY>0){
                for(i=0;i<nbLineTank;i++){
                    if(map[tank->posX+i][tank->posY-1] != ' ') {
                      printf("%c", map[posX+i][posY+1]);
                      return 0;
                    }
                }
                return 1;
                /*if(res == nbLineTank)
                    return 1;
                else
                    return 0;*/
                break;
            }
        case 'D':
            if(tank->posY<186+nbColTank){
                for(i=0;i<nbLineTank;i++) {
                    if(map[tank->posX+i][tank->posY+nbColTank] != ' ') {
                      return 0;
                    }
                }
                return 1;
                break;
            }
    }
    return EXIT_FAILURE;
}

void deleteTank(Tank *tank, char **map){
    int i, j;

        for(i=0; i < nbLineTank; i++){
            for(j=0; j < nbColTank; j++){

                moveToPosXY(1+tank->posX+i, 1+tank->posY+j);
                printf(" ");

                map[tank->posX+i][tank->posY+j] = ' ';

            }
        }
}


void moveTankEnemy(char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, TankList *tankList){

    Tank *eTank = tankList->firstTank;
    int randPos = 0;

    eTank = eTank->next;

    while(eTank != NULL){
        if(eTank->timer>5000000){
            randPos = rand()%4-1;
            if(eTank->armor == 1){
                switch(randPos){
                    case 1:
                        eTank->direction = 'H';
                        if(isFree(map, eTank) ){
                            deleteTank(eTank, map);
                            replaceMatrixWithAnother(tankG_ts,eTank->bodyWork);
                            eTank->posX--;
                            moveTank(eTank, map);
                        }
                        break;
                    case 2:
                        eTank->direction = 'B';
                        if(isFree(map, eTank) ){
                            deleteTank(eTank, map);
                            replaceMatrixWithAnother(tankG_ts,eTank->bodyWork);
                            eTank->posX++;
                            moveTank(eTank, map);
                        }
                        break;
                    case 3:
                        eTank->direction = 'G';
                        if(isFree(map, eTank) ){
                            deleteTank(eTank, map);
                            replaceMatrixWithAnother(tankG_ts,eTank->bodyWork);
                            eTank->posY--;
                            moveTank(eTank, map);
                        }
                        break;
                    case 4:
                        eTank->direction = 'D';
                        if(isFree(map, eTank) ){
                            deleteTank(eTank, map);
                            replaceMatrixWithAnother(tankG_ts,eTank->bodyWork);
                            eTank->posY++;
                            moveTank(eTank, map);
                        }
                        break;

                }
            }

            eTank->timer = 0;
        }else
            eTank->timer++;
        eTank = eTank->next;
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
                                    //printf("adresse Tank Joueur dans move tank player = %p\n", tankJ);
                                    replaceMatrixWithAnother(tankD_ts, tankJ->bodyWork);
                                    //exit(0);
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
                                generateObus(*tankJ, map, obusList);
                                break;
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
