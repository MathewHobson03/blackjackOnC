#include "game_logic.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../include/peripherals/lcd.h"
int main(){
    Card deck[52];
    int playerScoreLocal;
    int dealerScoreLocal;
    initGame(deck, &playerScoreLocal, &dealerScoreLocal);

     lcd_handle_t lcd = {0};
    printf("starting lcd activity");

    if(lcd_init(&lcd) !=0){
        printf("Failed to init LCD");
        return -1;

    }
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
                printf("...");
                sleep(1);
               
                printPlayerCard();

                if (getPlayerScore() < 21) {
                    lcd_write_text(&lcd, 0,0, "Would you like to");
                    lcd_write_text(&lcd,0,10,"Hit, 1 for yes 2 for no");
                    
                    fflush(stdout);
                    if (scanf("%d", &hit2) != 1) {
                        lcd_clear(&lcd);
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
        sleep(1);
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