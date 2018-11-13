#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#define nbLineTank 5
#define nbColTank 9 //on fait +1 pour le '\0'
#define UP 'z'
#define DOWN 's'
#define LEFT 'q'
#define RIGHT 'd'
#define BANG 'g'
#define nbLineMap 53
#define nbColMap 186



