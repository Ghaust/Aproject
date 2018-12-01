#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#define nbLineTank 5
#define nbColTank 9 //on fait +1 pour le '\0'
#define UP 'A'
#define DOWN 'B'
#define LEFT 'D'
#define RIGHT 'C'
#define BANG 'g'
#define nbLineMap 53
#define nbColMap 186

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
    int timer;
    int condition; //3 on décrémente ensuite
    int sameDir;

    int id;

    Tank *next;

};

typedef struct Obus Obus;

struct Obus {

    int posX;
    int posY;
    int id;

    char direction;
    int type; //E
    int timer;
    int provenance;
    
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



