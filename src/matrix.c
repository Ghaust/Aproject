#include "headers.h"

//Cette fonction permet de réserver l'espace mémoire nécessaire pour notre matrice
char ** matrixAlloc(int nbL, int nbC){
    int i;
    char **t = malloc(nbL * sizeof(char*));

    for(i=0; i<nbL; i++){
        t[i] = malloc(nbC*sizeof(char));
    }
    return t;
}


void writingMat(int nbL, int nbC, char **mat, FILE *file){
    int i, j;
    char vide;
    for(i=0; i<nbL; i++){
        for(j=0; j<nbC; j++){
            fscanf(file,"%c", &mat[i][j]);
        }
        //mat[i][j]='\0';
        fscanf(file, "%c", &vide);
    }
}

void printMat(int nbL, int nbC, char **mat){
    int i, j;
    for(i=0; i<nbL; i++){
        for(j=0; j<nbC; j++){
            printf("%c", *(*(mat + i)+j));
        }
        printf("\n");
    }
}


void freeMat(int nbL, char **mat){
    int i;
    for(i=0; i<nbL; i++){
        free(*(mat+i));
    }
}

void replaceMatrixWithAnother(char **mat1, char **mat2){
    int i, j;

    for(i=0; i<nbLineTank; i++){
        for(j=0; j<nbColTank; j++){
            mat2[i][j] = mat1[i][j];
        }
    }
}


void loadTankModel(char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub){

    FILE *ftankH_ts = NULL, *ftankD_ts = NULL, *ftankG_ts = NULL, *ftankB_ts = NULL;
    FILE *ftankH_tb = NULL, *ftankD_tb = NULL, *ftankG_tb = NULL, *ftankB_tb = NULL;

    FILE *ftankH_tub = NULL, *ftankD_tub = NULL, *ftankG_tub = NULL, *ftankB_tub = NULL;


    ftankH_ts = fopen("../models/tanks/deplacement_TS/ts_haut.txt", "r+");
    ftankB_ts = fopen("../models/tanks/deplacement_TS/ts_bas.txt", "r+");
    ftankG_ts = fopen("../models/tanks/deplacement_TS/ts_gauche.txt", "r+");
    ftankD_ts = fopen("../models/tanks/deplacement_TS/ts_droite.txt", "r+");

    ftankH_tb = fopen("../models/tanks/deplacement_TB/tb_haut.txt", "r+");
    ftankB_tb = fopen("../models/tanks/deplacement_TB/tb_bas.txt", "r+");
    ftankG_tb = fopen("../models/tanks/deplacement_TB/tb_gauche.txt", "r+");
    ftankD_tb = fopen("../models/tanks/deplacement_TB/tb_droite.txt", "r+");

    ftankH_tub = fopen("../models/tanks/deplacement_TUB_easyMode/tub_haut.txt", "r+");
    ftankB_tub = fopen("../models/tanks/deplacement_TUB_easyMode/tub_bas.txt", "r+");
    ftankG_tub = fopen("../models/tanks/deplacement_TUB_easyMode/tub_gauche.txt", "r+");
    ftankD_tub = fopen("../models/tanks/deplacement_TUB_easyMode/tub_droite.txt", "r+");

    if(ftankH_ts != NULL && ftankB_ts != NULL && ftankG_ts != NULL && ftankD_ts != NULL
    && ftankH_tb != NULL && ftankB_tb != NULL && ftankG_tb != NULL && ftankD_tb != NULL
    && ftankH_tub != NULL && ftankB_tub != NULL && ftankG_tub != NULL && ftankD_tub != NULL){

        writingMat(nbLineTank, nbColTank, tankH_ts, ftankH_ts);
        writingMat(nbLineTank, nbColTank, tankB_ts, ftankB_ts);
        writingMat(nbLineTank, nbColTank, tankG_ts, ftankG_ts);
        writingMat(nbLineTank, nbColTank, tankD_ts, ftankD_ts);

        writingMat(nbLineTank, nbColTank, tankH_tb, ftankH_tb);
        writingMat(nbLineTank, nbColTank, tankB_tb, ftankB_tb);
        writingMat(nbLineTank, nbColTank, tankG_tb, ftankG_tb);
        writingMat(nbLineTank, nbColTank, tankD_tb, ftankD_tb);

        writingMat(nbLineTank, nbColTank, tankH_tub, ftankH_tub);
        writingMat(nbLineTank, nbColTank, tankB_tub, ftankB_tub);
        writingMat(nbLineTank, nbColTank, tankG_tub, ftankG_tub);
        writingMat(nbLineTank, nbColTank, tankD_tub, ftankD_tub);

        fclose(ftankH_ts);
        fclose(ftankB_ts);
        fclose(ftankG_ts);
        fclose(ftankD_ts);

        fclose(ftankH_tb);
        fclose(ftankB_tb);
        fclose(ftankG_tb);
        fclose(ftankD_tb);

        fclose(ftankH_tub);
        fclose(ftankB_tub);
        fclose(ftankG_tub);
        fclose(ftankD_tub);
    }
    else
        exit(-1);
}
