#include <stdlib.h>
#include <stdbool.h>
#pragma once 

enum CardRank {Ace = 1,Two , Three, Four, Five, Six,
Seven, Eight, Nine,Ten=10, Jack, Queen, King};
enum CardSuite {Hearts, Clubs, Diamonds, Spades};

typedef struct{
    enum CardRank rank;
    enum CardSuite suite;
    bool unused;
}Card;

// initGame: sets up a deck, initializes global score/state and also writes
// the initial player and dealer scores into the provided output pointers.
void initGame(Card deck[52], int* playerScoreOut, int* dealerScoreOut); // Sets up a Deck, scores, and state Variables
void dealInitialCards(Card deck[52]); //Deals two cards to the player and to the dealer
Card cardDraw(Card deck[52], int*); //Draws a card from the deck //?Done
void shuffleCards(Card deck[52]); //Takes in a deck and shuffles the order, may not need if we just pick a random num from the deck, once taken set to zero, if zero it has already been chose pick again //?Done
void playerHit(Card deck[52]); //Draws a card and deals it to the player, adding to his total //Done
void dealerHit(Card deck[52]);//Draws a card and deals it to the dealer, adding it to their total //Done
void playerStand();// Ends the turn of the player
void dealerBust();// Check total of dealer, if over 21 they lose
void playerBust();// Check total of player, if over 21 they lose
int getPlayerScore();// Getter for player score
int getDealerScore();// Getter for dealer score
int compareScores();// Comparator for dealer and player score

// Dealer logic: run the dealer's turn (hits until reaching 17 or higher)
void dealerPlay(Card deck[52]);

// Print dealer's hand to stdout (for debugging/console output)
void printDealerCard();

void resetGame(); // Re Initializes game





