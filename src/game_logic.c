#include "../include/game_logic.h"
#include <stdlib.h>
#include <time.h>

//Some base definitions
#define DECK_SIZE 52
#define BLACKJACK 21

// Global variables
int nextCardIndex = 0;
int playerScore;
int dealerScore;
Card playerHand[11];
Card dealerHand[11];
int playerHandSize=0;
int dealerHandSize=0;

void swap(Card* a, Card* b){
    Card temp;
    temp =*a;
    *a=*b;
    *b=temp;
}
void shuffleCards(Card deck[52]){
    srand (time(NULL));
    for(int i=DECK_SIZE; i>0;i--){
        int swap_index = rand()%DECK_SIZE;
        for (int i = DECK_SIZE-1; i > 0; i--){
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&deck[i], &deck[j]);
        }

    }
}

void playerHit(Card deck[52]){
    playerHand[playerHandSize] = cardDraw(deck, &nextCardIndex);
    playerHandSize++;
}
void dealerHit(Card deck[52]){
    dealerHand[dealerHandSize] = cardDraw(deck, &nextCardIndex);
    dealerHandSize++;
}
Card cardDraw(Card deck[52], int* nextCardIndex){
    return deck[(*nextCardIndex)++];
}
void dealInitialCards(Card deck[52]){
    playerHit(deck);
    playerHit(deck);
    dealerHit(deck);
    dealerHit(deck);
}
void initGame(Card deck[52], int* playerScore, int* dealerScore){
    
    int a=4;
    int b=14;
    int z=0;
    *dealerScore =0;
    *playerScore =0;
    for(int i=0;i<a;i++){
        for(int k=1;k<b;k++){
            deck[z].rank=k;
            deck[z].suite=i;
            deck[z].unused =true;
            z++;
        }
    }

}


