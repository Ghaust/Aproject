#include "obus.h"


int main(int argc, char const *argv[])
{
     
    int playerChoice = deployMenu();
    while(playerChoice == 3)
        playerChoice = deployMenu();
    playGame_easyMode(playerChoice);
    
    return 0;
}

