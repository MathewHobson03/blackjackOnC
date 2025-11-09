#include "game_logic.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    Card deck[52];
    int playerScoreLocal;
    int dealerScoreLocal;
    initGame(deck, &playerScoreLocal, &dealerScoreLocal);

    while (true) {
        int hit = 0;
        int hit2 = 0;
        printf("Your cards are:\n");
        printPlayerCard();

        printf("Would you like to hit? 1 for yes or 2 for no: ");
        fflush(stdout);
        //Replace with logic to take button input from board
        if (scanf("%d", &hit) != 1) {
            // invalid input
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (hit == 1) {
            while (true) {
                hit2 = 0;
                playerHit(deck);
                printPlayerCard();

                if (getPlayerScore() < 21) {
                    printf("Would you like to hit again? 1 for yes or 2 for no: ");
                    fflush(stdout);
                    if (scanf("%d", &hit2) != 1) {
                        printf("Invalid input. Stopping hits.\n");
                        break;
                    }
                }

                if (hit2 != 1 || getPlayerScore() >= 21) {
                    break;
                }
            }
        }

        // Run dealer turn and evaluate outcome
        printf("Final player score: %d\n", getPlayerScore());
        printf("Dealer plays...\n");
        dealerPlay(deck);
        printf("Dealer's cards:\n");
        printDealerCard();
        printf("Dealer final score: %d\n", getDealerScore());

        int result = compareScores();
        if (result == 2) {
            printf("Tie!\n");
        } else if (result == 1) {
            printf("You win!\n");
        } else {
            printf("Dealer wins.\n");
        }
        break;
    }

    return 0;
}