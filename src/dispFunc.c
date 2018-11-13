#include "dispFunc.h"
#include "tank.h"


void dispMatrix(int nbL, int nbC, char **mat){
    int i, j;
    for(i=0; i<nbL; i++){
        for(j=0; j<nbC; j++){
            printSwitch(*(*(mat + i) + j));
        }
        printf("\n");
    }
}

int deployMenu(){
    FILE *menu = NULL;
    
    menu = fopen("../models/menus/menu_accueil.txt", "r+");
    
    int toucheSaisie = 0;

    system("clear");
    if(menu != NULL){
        system("play -q ../sons/intro.wav &"); // $! pour le PID
        
        do{
            toucheSaisie = key_pressed();
            dispFile(menu);
        }while(toucheSaisie == 0);

        system("clear");
        menu = fopen("../models/menus/menu_attente.txt", "r+");
        if(toucheSaisie == 49 || toucheSaisie == 38){
            return 1;
            
        }
        else if(toucheSaisie== 50 || toucheSaisie == 0233){
            return 2;
            
        }
        else if(toucheSaisie== 51 || toucheSaisie == 34){
            return 3;
            
        }
        //Si l'utilisateur tape 4 ou ' on quitte le jeu
        else if(toucheSaisie== 52 || toucheSaisie == 39){
        }
        return 4;
    }
    else{
        printf("Fichier vide. Erreur");
        exit(-1);
     }
    
    //on stoppe le processus qui s'exécute en arrière plan echo lordeje >
    system("sudo pkill play");
    
    fclose(menu);
}



//Permet d'afficher le menu
void dispFile(FILE *file){
    int c = 0;
    while( (c = fgetc(file)) != EOF){
        printf("%c", (char)c);
    }
    
}


void playGame_easyMode(int playerChoice){

    if(playerChoice == 1){
        //Obus *oPlayer = initObus(oPlayer); 
        //régler le pb d'inclusion de fichiers
        //ObusList *obusList = initObusList(oPlayer);
        //TankList *tankList = NULL;
        
        Tank *tankJ = malloc(1*sizeof(Tank));
        Tank *tankE = malloc(1*sizeof(Tank));


        FILE *fmap = NULL;
        //tankJ->bodyWork = matrixAlloc(nbLineTank, nbColTank);
        
        char **tankH_ts = matrixAlloc(nbLineTank, nbColTank), **tankB_ts = matrixAlloc(nbLineTank, nbColTank), **tankG_ts = matrixAlloc(nbLineTank, nbColTank), **tankD_ts = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tb = matrixAlloc(nbLineTank, nbColTank), **tankB_tb = matrixAlloc(nbLineTank, nbColTank), **tankG_tb = matrixAlloc(nbLineTank, nbColTank), **tankD_tb = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tub = matrixAlloc(nbLineTank, nbColTank), **tankB_tub = matrixAlloc(nbLineTank, nbColTank), **tankG_tub = matrixAlloc(nbLineTank, nbColTank), **tankD_tub = matrixAlloc(nbLineTank, nbColTank);
        char **map = matrixAlloc(nbLineMap, nbColMap);

        //On charge ici les 16 matrices de tanks
        loadTankModel(tankH_ts, tankB_ts, tankG_ts, tankD_ts, 
        tankH_tb, tankB_tb, tankG_tb, tankD_tb,
        tankH_tub, tankB_tub, tankG_tub, tankD_tub);
		
        
        

        //Lié au key_pressed
        int c;

        tankJ = initTankPlayer(tankJ);
        //TankList *t = initTankList(tankJ);
        tankE = initTankEnemy(tankE);

        replaceMatrixWithAnother(tankD_ts,tankJ->bodyWork);
       
        if(tankE->armor == 1 && tankE->direction=='G')
            replaceMatrixWithAnother(tankG_ts,tankE->bodyWork);
        else if(tankE->armor == 2 && tankE->direction=='G')
            replaceMatrixWithAnother(tankG_tb,tankE->bodyWork);
        else if(tankE->armor == 2 && tankE->direction=='B')
            replaceMatrixWithAnother(tankB_tb,tankE->bodyWork);
        else if(tankE->armor == 3 && tankE->direction=='G')
            replaceMatrixWithAnother(tankG_tub,tankE->bodyWork);
        else if(tankE->armor == 3 && tankE->direction=='B')
            replaceMatrixWithAnother(tankB_tub,tankE->bodyWork);
            
        //On charge le tank dans la matrice à la position de départ

        

    
        fmap = fopen("../models/map/map_alph.txt", "r+");
        if(fmap != NULL){
            writingMat(nbLineMap, nbColMap, map, fmap);
           
            loadTankInMatrix(map, tankJ);
            loadTankInMatrix(map, tankE);
            fclose(fmap);

        }
        else
            exit(-1);

        system("clear");
        dispMatrix(nbLineMap, nbColMap, map);
        system("stty -echo");
        system("setterm -cursor off");
        while (1){

                    c = key_pressed();


                    /*moveTankEnemy(tankE,
                    tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                    tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                    tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                    map);*/

                
                    moveTankPlayer(tankJ,
                    tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                    tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                    tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                    map, c);

                    //

                    //Lié aux déplacements de l'utilisateur
                   

                }
        
       // dispTankList(tankList);

		freeMat(nbLineMap, map);
        freeMat(nbLineTank, tankJ->bodyWork);
        freeMat(nbLineTank, tankE->bodyWork);
        freeMat(nbLineTank,tankH_ts);
        freeMat(nbLineTank,tankB_ts);
        freeMat(nbLineTank,tankD_ts);
        freeMat(nbLineTank,tankG_ts);
        freeMat(nbLineTank,tankH_tb);
        freeMat(nbLineTank,tankB_tb);
        freeMat(nbLineTank,tankD_tb);
        freeMat(nbLineTank,tankG_tb);
        freeMat(nbLineTank,tankH_tub);
        freeMat(nbLineTank,tankB_tub);
        freeMat(nbLineTank,tankD_tub);
        freeMat(nbLineTank,tankG_tub);


    system("stty echo");
    }
    else
        printf("Nique ta mère.");
}

void printSwitch(char c){
    switch(c){
                    case '0':
                        printf("╔");
                        break;
                    case '1':
                        printf("╗");
                        break;
                    case '2':
                        printf("╝");
                        break;
                    case '3':
                        printf("╚");
                        break;
                    case '-':
                        printf("═");
                        break;
                    case '|':
                        printf("║");
                        break;
                    case 'E':
                        printf("\033[34m▓\033[00m");
                        break;
                     
                    case 'A':
                        printf("\033[31m☎\033[00m");
                        break;
                    case 'R':
                        printf("\033[37m☎\033[00m");
                        break;
                    case 'P': //palmier
                        printf("\033[37m☎\033[00m");
                        break;     
                    case 'O':
                        printf("O");
                        break;
                    case 'M':
                        printf("▓");
                        break;
                    case 'L':
                        printf("_");
                        break;
                    case 'T':
                        printf("|");
                        break;
                    case 'B':
                        printf("█");
                        break;
                    case 'I':
                        printf("▀");
                        break;
                    case 'U':
                        printf("─");
                        break;
                    default:
                        printf("%c", c);
        }
    
}