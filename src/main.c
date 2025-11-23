#include "../includes/game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../includes/peripherals/lcd.h"
#include "../includes/input.h"

int main() {
    Card deck[52];
    int playerScoreLocal;
    int dealerScoreLocal;
    initGame(deck, &playerScoreLocal, &dealerScoreLocal);

    lcd_handle_t lcd = {0};
    printf("starting lcd ");
    button_handle_t button = {0};
    if (button_init(&button) != 0) {
        printf("Failed to init button");
        return -1;
    }
    if (lcd_init(&lcd) != 0) {
        printf("Failed to init LCD");
        return -1;
    }

    while (true) {
    lcd_clear(&lcd);
    lcd_write_text(&lcd, 0, 0, "Your cards are:");
    sleep(3);
    printPlayerCard(&lcd);
    sleep(3);
    lcd_clear(&lcd);

    // Player turn
    bool player_done = false;
    while (!player_done) {
        lcd_write_text(&lcd, 0, 0, "Would you like to hit?");
        lcd_write_text(&lcd, 0, 40, "KEY0=Yes KEY1=No");

        int hit = -1;

        // Poll buttons until KEY0 or KEY1 is pressed
        while (hit == -1) {
            int value = button_read(&button);

            if (value & 0x1) {        // KEY0 pressed
                hit = 1;
            } else if (value & 0x2) { // KEY1 pressed
                hit = 0;
            }

            usleep(10000); // 10ms delay
        }

        if (hit == 1) {
            // Player chose to hit
            lcd_clear(&lcd);
            playerHit(deck);
            printPlayerCard(&lcd);
            sleep(5);

            // Automatically stop if player busts
            if (getPlayerScore() >= 21)
                player_done = true;
        } else {
            // Player chose not to hit
            player_done = true;
        }

        lcd_clear(&lcd);
    }

    // Dealer turn
    lcd_clear(&lcd);
    lcd_write_text(&lcd, 0, 0, "Dealer plays...");
    sleep(2);
    lcd_clear(&lcd);
    dealerPlay(deck, &lcd);
    printDealerCard(&lcd);
    sleep(2);
    lcd_clear(&lcd);
    lcd_write_text(&lcd, 0, 0, "Dealer score:");
    lcd_write_score(&lcd, 0, 40, getDealerScore());
    sleep(3);
    lcd_clear(&lcd);

    // Compare scores
    int result = compareScores();
    if (result == 2) {
        lcd_write_text(&lcd, 0, 0, "Tie!");
    } else if (result == 1) {
        lcd_write_text(&lcd, 0, 0, "You WIN!");
    } else {
        lcd_write_text(&lcd, 0, 0, "Dealer WINS!");
    }
    sleep(3);
    lcd_clear(&lcd);

    break; // End game loop
}


    return 0;
}
