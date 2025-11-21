#include "../includes/game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../includes/peripherals/lcd.h"
int main(){
    Card deck[52];
    int playerScoreLocal;
    int dealerScoreLocal;
    initGame(deck, &playerScoreLocal, &dealerScoreLocal);

    lcd_handle_t lcd = {0};
    printf("starting lcd ");

    if(lcd_init(&lcd) !=0){
        printf("Failed to init LCD");
        return -1;

    }
    while (true) {
        int hit = 0;
        int hit2 = 0;
        printf("Your cards are:\n");
	lcd_write_text(&lcd,0,0,"Hello, dealing hand now");
	sleep(2);
	lcd_clear(&lcd);
        printPlayerCard(&lcd);
	sleep(3);
	lcd_clear(&lcd);
        lcd_write_text(&lcd, 0, 0, "Would you like");
        lcd_write_text(&lcd, 0, 10, "to hit, 1 for yes 2 for no");
        fflush(stdout);
        //Replace with logic to take button input from board
        if (scanf("%d", &hit) != 1) {
            // invalid input
			lcd_clear(&lcd);
			lcd_write_text(&lcd, 0, 0, "Invalid input.");
			sleep(2);
			lcd_clear(&lcd);
            break;
        }

        if (hit == 1) {
            while (true) {
		lcd_clear(&lcd);
                hit2 = 0;
                playerHit(deck);
                printf("...");
                sleep(1);
               
                printPlayerCard(&lcd);
		sleep(3);
		lcd_clear(&lcd);
                if (getPlayerScore() < 21) {
                    lcd_write_text(&lcd, 0,0, "Would you like");
                    lcd_write_text(&lcd,0,10,"to hit 1=yes 2=no");
                    
                    fflush(stdout);
                    if (scanf("%d", &hit2) != 1) {
                        lcd_clear(&lcd);
						lcd_write_text(&lcd, 0, 0, "Invalid input.");
						sleep(2);
						lcd_clear(&lcd);
                        break;
                    }
                }

                if (hit2 != 1 || getPlayerScore() >= 21) {
                    	lcd_clear(&lcd);
			break;
                }
            }
        }

        // Run dealer turn and evaluate outcome
	lcd_clear(&lcd);
        printf("Final player score: %d\n", getPlayerScore());
		lcd_write_text(&lcd, 0, 0, "Final player score: ");
        lcd_write_score(&lcd, 0, 20, getPlayerScore());
        //show numbers on hex
        sleep(3);
        lcd_clear(&lcd);
        lcd_write_text(&lcd, 0, 0, "Dealer Plays");
        sleep(2);
        lcd_clear(&lcd);
        dealerPlay(deck,&lcd);
        lcd_write_text(&lcd,0,0,"Dealer's cards:");
	sleep(3);
        printDealerCard(&lcd);
	sleep(3);
	lcd_clear(&lcd);
        lcd_write_text(&lcd, 0, 0, "Dealer score: ");
        lcd_write_score(&lcd, 0, 10, getDealerScore());
        sleep(3);
        lcd_clear(&lcd);
        

        int result = compareScores();
        if (result == 2) {
            lcd_write_text(&lcd, 0, 0, "Tie!");
            sleep(2);
            lcd_clear(&lcd);
        } else if (result == 1) {
            lcd_write_text(&lcd, 0, 0, "You WIN!");
            sleep(2);
            lcd_clear(&lcd);
        } else {
            lcd_write_text(&lcd, 0, 0, "Dealer WINS!");
            sleep(2);
            lcd_clear(&lcd);
        }
        break;
    }

    return 0;
}
