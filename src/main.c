#include "game_logic.c"
#include "../include/input.h"
#include "../include/display.h"
int main(){
    Card deck[52];
    int playerScore;
    int dealerScore;
    initGame(deck,&playerScore, &dealerScore);
    
    printf("%d\n%d\n", playerHand[1].rank,playerHand[1].suite);
    printf("%d\n%d\n", playerHand[1].rank,playerHand[1].suite);
    return 0;
}