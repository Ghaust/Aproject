#include "tank.h"

/** Fonctions liées à tout ce qui touche aux matrices. **/
char **matrixAlloc(int nbL, int nbC);
void writingMat(int nbL, int nbC, char **mat, FILE *file);
void printMat(int nbL, int nbC, char **mat);
void freeMat(int nbL, char **mat);
void loadTankInMatrix(char **mat, Tank *tank);
void replaceMatrixWithAnother(char **mat1, char **mat2);
void loadTankModel(char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub);
