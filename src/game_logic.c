#include "../includes/game_logic.h"
#include "unistd.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "../includes/peripherals/lcd.h"

//Some base definitions
#define DECK_SIZE 52
#define BLACKJACK 21

static const char *suit_names[] = { "Hearts", "Clubs", "Diamonds", "Spades" };
static const char *rank_names[] = { "?", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

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
    /* Fisher–Yates shuffle */
    srand((unsigned)time(NULL));
    for (int i = DECK_SIZE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(&deck[i], &deck[j]);
    }
}

void playerHit(Card deck[52]){
    playerHand[playerHandSize] = cardDraw(deck, &nextCardIndex);
    playerScore = playerScore + playerHand[playerHandSize].rank;
    playerHandSize++;
}
void dealerHit(Card deck[52]){
    dealerHand[dealerHandSize] = cardDraw(deck, &nextCardIndex);
    dealerScore = dealerScore + dealerHand[dealerHandSize].rank;
    dealerHandSize++;
}
void playerStand()
{
    
}
void dealerBust()
{
}
void playerBust()
{
}
void printPlayerCard(lcd_handle_t* lcd){
	int line =0;
	lcd_clear(lcd);
    for (int i = 0; i < playerHandSize; ++i) {
        int r = (int)playerHand[i].rank;
        int s = (int)playerHand[i].suite;
        if (r < 1 || r > 13) {
            printf("Invalid rank at hand index %d\n", i);
            continue;
        }
        if (s < 0 || s >= 4) {
            printf("Invalid suit at hand index %d\n", i);
            continue;
        }
        lcd_write_text(lcd, 0,line,rank_names[r]);
        lcd_write_text(lcd,40,line,suit_names[s]);
        printf("%s of %s\n", rank_names[r], suit_names[s]);
        line = line+10;
    }
}
int getPlayerScore()
{
    return playerScore;
}
int getDealerScore()
{
    return dealerScore;
}
int compareScores()
{
    // Handle busts first
    if (playerScore > BLACKJACK && dealerScore > BLACKJACK) {
        // both busted -> dealer wins by house rule (could be tie)
        return 0;
    }
    if (playerScore > BLACKJACK) {
        return 0; // player busted -> dealer wins
    }
    if (dealerScore > BLACKJACK) {
        return 1; // dealer busted -> player wins
    }

    if (playerScore == dealerScore) {
        return 2; // tie
    }
    else if ((playerScore > dealerScore) && playerScore <= BLACKJACK) {
        return 1; // player wins
    }
    else {
        return 0; // dealer wins
    }
    
}
Card cardDraw(Card deck[52], int *nextCardIndex)
{
    return deck[(*nextCardIndex)++];
}
void dealInitialCards(Card deck[52]){
    playerHit(deck);
    playerHit(deck);
    dealerHit(deck);
    dealerHit(deck);
}

void printDealerCard(lcd_handle_t* lcd){
	int line = 0;
	lcd_clear(lcd);
    for (int i = 0; i < dealerHandSize; ++i) {
        int r = (int)dealerHand[i].rank;
        int s = (int)dealerHand[i].suite;
	
	
        if (r < 1 || r > 13) {
            printf("Invalid rank at dealer hand index %d\n", i);
            continue;
        }
        if (s < 0 || s >= 4) {
            printf("Invalid suit at dealer hand index %d\n", i);
            continue;
        }
	lcd_write_text(lcd, 0,line,rank_names[r]);
	lcd_write_text(lcd,40,line,suit_names[s]);
        printf("%s of %s\n", rank_names[r], suit_names[s]);
	line =line+10;
    }
}

// Simple dealer AI: hit until reaching 17 or higher.
void dealerPlay(Card deck[52],lcd_handle_t* lcd){
	int line = 0;
    while (dealerScore < 17) {
	lcd_write_text(lcd,0,line,"Dealer hits again");
        dealerHit(deck);
	sleep(3);
	line = line +20;
	
    }
	lcd_clear(lcd);
}
void initGame(Card deck[52], int* playerScoreOut, int* dealerScoreOut){
    int a = 4;
    int b = 14;
    int z = 0;
    /* Initialize global state */
    nextCardIndex = 0;
    playerScore = 0;
    dealerScore = 0;
    playerHandSize = 0;
    dealerHandSize = 0;

    if (playerScoreOut) *playerScoreOut = 0;
    if (dealerScoreOut) *dealerScoreOut = 0;
    for(int i=0;i<a;i++){
        for(int k=1;k<b;k++){
            deck[z].rank=k;
            deck[z].suite=i;
            deck[z].unused =true;
            z++;
        }
    }
    shuffleCards(deck);
    dealInitialCards(deck);

}


