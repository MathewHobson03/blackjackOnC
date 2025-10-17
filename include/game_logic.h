#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma once 

enum CardRank {Ace = 1,Two =2, Three, Four, Five, Six,
Seven, Eight, Nine,Ten=10, Jack, Queen, King};
enum CardSuite {Hearts, Clubs, Diamonds, Spades};

typedef struct{
    enum CardRank rank;
    enum CardSuite suite;
    bool unused;
}Card;

void initGame(Card deck[52],int*,int*); //Sets up a Deck, scores, and state Variables //?Done 
void dealInitialCards(Card deck[52]); //Deals two cards to the player and to the dealer
Card cardDraw(Card deck[52], int*); //Draws a card from the deck //?Done
void shuffleCards(Card deck[52]); //Takes in a deck and shuffles the order, may not need if we just pick a random num from the deck, once taken set to zero, if zero it has already been chose pick again //?Done
void playerHit(); //Draws a card and deals it to the player, adding to his total
void dealerHit();//Draws a card and deals it to the dealer, adding it to their total
void playerStand();// Ends the turn of the player
void dealerBust();// Check total of dealer, if over 21 they lose
void playerBust();// Check total of player, if over 21 they lose
int getPlayerScore();// Getter for player score
int getDealerScore();// Getter for dealer score
int compareScores();// Comparator for dealer and player score

void resetGame(); // Re Initializes game





