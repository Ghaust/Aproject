#include "obus.h"


int main(int argc, char const *argv[])
{
     
    int playerChoice = deployMenu();
    playGame_easyMode(playerChoice);
    
    return 0;
}

/* 
FILE *tb_bas = NULL, *tub_hardmode = NULL, *tub_easyMode = NULL;

    tb_bas = fopen("../models/tanks/deplacement_TB/tb_bas.txt", "r+");
    tub_easyMode = fopen("../models/tanks/deplacement_TUB_easyMode/tub_haut.txt", "r+");
    tub_hardmode = fopen("../models/tanks/deplacement_TUB_hardMode/tub_haut.txt", "r+");
    char **mat1 = matrixAlloc(nbLineTank, nbColTank), **mat2 = matrixAlloc(nbLineTank, nbColTank), **mat3 = matrixAlloc(nbLineTank, 11);
    writingMat(nbLineTank, nbColTank, mat1, tb_bas);
    writingMat(nbLineTank, nbColTank, mat2, tub_easyMode); 
	writingMat(nbLineTank, 11, mat3, tub_easyMode); 

    fclose(tb_bas);
    fclose(tub_easyMode);
    fclose(tub_hardmode);
    system("clear");
     printf("\n\n");
    dispMatrix(nbLineTank, nbColTank, mat1);
    printf("\n\n");
    dispMatrix(nbLineTank, nbColTank, mat2);
     printf("\n\n");
    dispMatrix(nbLineTank, 11, mat3);

    freeMat(nbLineTank, mat1);
    freeMat(nbLineTank, mat2);
    freeMat(nbLineTank, mat3);*/