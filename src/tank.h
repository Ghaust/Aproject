#include "headers.h"
#include "dispFunc.h"
#define moveToPosXY(x, y) printf("\033[%d;%dH", (x), (y))

typedef struct Tank Tank;

struct Tank
{
   
    char direction;   //B vers le bas, H vers le haut, G vers la gauche , Droite vers la droite
    int posX;
    int posY;

    int armor; // 0 => pas de blindage, 1 => tank blindé, 2 => tank ultra blindé

    //int blindage_orig;
    
    char **bodyWork; //Servira pour l'affichage du tank

    char type; //P player, E enemy

    int condition; //3 on décrémente ensuite
    //int Mise_a_jour;

    int id;

    Tank *next;

};

typedef struct Obus Obus;

struct Obus {

    char caractere;
    int posX;
    int posY;
    int id;

    char direction;
    int type;
    Obus *next;
};

typedef struct TankList TankList;

struct TankList{

    Tank *firstTank;
    int id;
};

typedef struct ObusList ObusList;

struct ObusList{

    Obus *firstObus;
    int id;
};




/** Fonctions liées à tout ce qui touche aux tanks **/
Tank *initTankPlayer(Tank *tank);
Tank *initTankEnemy(Tank *tank);
void moveTank(Tank *tank, char **map);
int isFree(char **map, Tank *tank);
void deleteTank(Tank *tank, char **map);
void moveTankEnemy(Tank *e,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map);


void moveTankPlayer(Tank *tankJ,
char **tankH_ts, char **tankB_ts, char **tankG_ts, char **tankD_ts,
char **tankH_tb, char **tankB_tb, char **tankG_tb, char **tankD_tb,
char **tankH_tub, char **tankB_tub, char **tankG_tub, char **tankD_tub,
char **map, int c);

/** Fonctions liées à tout ce qui touche aux obus **/
Obus *initObus(Obus *o);
Obus *generateObus(Tank *t, char **map);
void moveObus(Obus *o, char **map);



int key_pressed();
