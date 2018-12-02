//#include "matrix.h"
#include "obus.h"

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
                    case 'K':
                        printf("K");
                        break;
                    default:
                        printf("%c", c);
        }
    
}


void dispMatrix(int nbL, int nbC, char **mat){
    int i, j;
    for(i=0; i<nbL; i++){
        for(j=0; j<nbC; j++){
            printSwitch(*(*(mat + i) + j));
            //printf("%c", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

//Permet d'afficher le menu
void dispFile(FILE *file){
    int c = 0;
    while( (c = fgetc(file)) != EOF){
        printf("%c", (char)c);
    }
    
}

int deployMenu(){
    FILE *menu = NULL, *help = NULL;
    
    menu = fopen("../models/menus/menu_accueil.txt", "r+");
    help = fopen("../models/menus/help.txt", "r+");
    int toucheSaisie = 0;

    system("clear");
    if(menu != NULL && help != NULL){
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
            dispFile(help);
            sleep(10);
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
    
    
    fclose(help);
    fclose(menu);
}


void playGame_easyMode(int playerChoice){

    if(playerChoice == 1){
        
        //régler le pb d'inclusion de fichiers
        ObusList *obusList = initObusList();
        Tank *tankJ = initTankPlayer(); 
        TankList *tList = initTankList(tankJ);
        
        
        int timer_enemy = 0;
        FILE *fmap = NULL;
        
        char **tankH_ts = matrixAlloc(nbLineTank, nbColTank), **tankB_ts = matrixAlloc(nbLineTank, nbColTank), **tankG_ts = matrixAlloc(nbLineTank, nbColTank), **tankD_ts = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tb = matrixAlloc(nbLineTank, nbColTank), **tankB_tb = matrixAlloc(nbLineTank, nbColTank), **tankG_tb = matrixAlloc(nbLineTank, nbColTank), **tankD_tb = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tub = matrixAlloc(nbLineTank, nbColTank), **tankB_tub = matrixAlloc(nbLineTank, nbColTank), **tankG_tub = matrixAlloc(nbLineTank, nbColTank), **tankD_tub = matrixAlloc(nbLineTank, nbColTank);
        char **map = matrixAlloc(nbLineMap, nbColMap);

        //On charge ici les 16 matrices de tanks
        loadTankModel(tankH_ts, tankB_ts, tankG_ts, tankD_ts, 
        tankH_tb, tankB_tb, tankG_tb, tankD_tb,
        tankH_tub, tankB_tub, tankG_tub, tankD_tub);
		
        
        replaceMatrixWithAnother(tankD_ts,tankJ->bodyWork);

        //Lié au key_pressed
        int c;

        
       
        //On charge le tank dans la matrice à la position de départ
        fmap = fopen("../models/map/map_alph.txt", "r+");
        if(fmap != NULL){
            writingMat(nbLineMap, nbColMap, map, fmap);
           
            loadTankInMatrix(map, tankJ);
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
                    
                   
                    moveTankPlayer(tList->firstTank,
                    tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                    tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                    tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                    map, c, obusList);
                    
                    if(timer_enemy == 1000){
                        timer_enemy = 0;
                        generateTankEnemy(tankB_ts, tankB_tb, tankB_tub, tankG_ts, tankG_tb, 
                        tankG_tub, map, tList);
                        youWon(tList);
                    }
                    timer_enemy++;  
                    
                        moveTankEnemy(tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                        tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                        tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                        map, tList, obusList);

                    moveObus(obusList, map, tList->firstTank, tList);

            
                
                }
        

		freeMat(nbLineMap, map);
        freeMat(nbLineTank, tankJ->bodyWork);
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


    //system("stty echo");
    }
    else
        printf("Allez les bleus !\n\n\n");
}

void playGame_hardMode(int playerChoice){

    if(playerChoice == 2){
        
        //régler le pb d'inclusion de fichiers
        ObusList *obusList = initObusList();
        Tank *tankJ = initTankPlayer(); 
        TankList *tList = initTankList(tankJ);
        
        
        int timer_enemy = 0;
        FILE *fmap = NULL;
        
        char **tankH_ts = matrixAlloc(nbLineTank, nbColTank), **tankB_ts = matrixAlloc(nbLineTank, nbColTank), **tankG_ts = matrixAlloc(nbLineTank, nbColTank), **tankD_ts = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tb = matrixAlloc(nbLineTank, nbColTank), **tankB_tb = matrixAlloc(nbLineTank, nbColTank), **tankG_tb = matrixAlloc(nbLineTank, nbColTank), **tankD_tb = matrixAlloc(nbLineTank, nbColTank);
        char **tankH_tub = matrixAlloc(nbLineTank, nbColTank), **tankB_tub = matrixAlloc(nbLineTank, nbColTank), **tankG_tub = matrixAlloc(nbLineTank, nbColTank), **tankD_tub = matrixAlloc(nbLineTank, nbColTank);
        char **map = matrixAlloc(nbLineMap, nbColMap);

        //On charge ici les 16 matrices de tanks
        loadTankModel(tankH_ts, tankB_ts, tankG_ts, tankD_ts, 
        tankH_tb, tankB_tb, tankG_tb, tankD_tb,
        tankH_tub, tankB_tub, tankG_tub, tankD_tub);
		
        
        replaceMatrixWithAnother(tankD_ts,tankJ->bodyWork);

        //Lié au key_pressed
        int c;
       
        //On charge le tank dans la matrice à la position de départ
        fmap = fopen("../models/map/map_alph.txt", "r+");
        if(fmap != NULL){
            writingMat(nbLineMap, nbColMap, map, fmap);
           
            loadTankInMatrix(map, tankJ);
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
                
                    moveTankPlayer(tList->firstTank,
                    tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                    tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                    tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                    map, c, obusList);
                    
                   
                    if(timer_enemy>6000){
                        timer_enemy = 0;
                            generateTankEnemy(tankB_ts, tankB_tb, tankB_tub, tankG_ts, tankG_tb, 
                            tankG_tub, map, tList);
                        youWon(tList);
                    }else
                            timer_enemy++;
                        
            
                    
                    moveTankEnemy(tankH_ts, tankB_ts, tankG_ts, tankD_ts,
                    tankH_tb, tankB_tb, tankG_tb, tankD_tb,
                    tankH_tub, tankB_tub, tankG_tub, tankD_tub,
                    map, tList, obusList);

                    moveObus(obusList, map, tankJ, tList);

            
                
                }
        

		freeMat(nbLineMap, map);
        freeMat(nbLineTank, tankJ->bodyWork);
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


    //system("stty echo");
    }
    else
        printf("Allez les bleus !\n\n\n");
}