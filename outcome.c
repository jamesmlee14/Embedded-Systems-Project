/*
 * outcome.c
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 *
 *
 */


#include "outcome.h"
#include "bitmap.h"
#include "led.h"
#include "pacer.h"



/*
* Takes two integers current and opponent, corresponding to
* a player's locked in selection (Rock, Paper, or Scissors)
* and their opponent's one.

* Returns an integer result representing the game's outcome,
* with 0 representing a Draw, 1 a Win, and 2 a Loss
*/
int get_result(int current, int opponent)
{
    current++;
    opponent++;
    int result = (current - opponent + 3) % 3;
    return result;
}



void flash_led(int counter)
{
    if ((counter % 250) == 0) {
        if (((counter / 250) % 2) == 0) {
            led_set (LED1, 0); // LIGHT OFF
        }
        if (((counter / 250) % 2) == 1) {
            led_set (LED1, 1); // LIGHT ON
        }


    }

}

/*
* Executes the outcome phase:
*
* 1. Displays the players and their opponents' selections for 5 seconds
*
* 2. Displays a letter representing the players outcome in the game
*       Flashes the LED if the player won a game
*
* 3. Displays the player's current score accross the match for 5 seconds
*
* 4. If the match is decided, Displays the players outcome in the match
*       Flashes the LED if the player won the match
*       Continues until board is reset.
*/
Player_Bitmap outcome(Player_Bitmap bitmap)
{

    uint16_t counter = 0;
    while (counter < 2500) {
        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);
    }

    int outcome = get_result(bitmap.current_bitmap, bitmap.opponent_bitmap);

    if (outcome == 1) {
        bitmap.player_score++;
        bitmap.current_bitmap = 7; // WIN

    } else if (outcome == 2) {
        bitmap.opponent_score++;
        bitmap.current_bitmap = 8; // LOSS

    } else if (outcome == 0) {
        bitmap.current_bitmap = 9; // DRAW
    }

    counter = 0;
    bitmap_refresh();

    while (counter < 2500) {

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);
        if (outcome == 1) {
            flash_led(counter);

        }

    }

    if (bitmap.player_score == 0) {
        bitmap.current_bitmap = 10; //ZERO
    } else if (bitmap.player_score == 1) {
        bitmap.current_bitmap = 11; //ONE
    } else if (bitmap.player_score == 2) {
        bitmap.current_bitmap = 12; //TWO
    } else if (bitmap.player_score == 3) {
        bitmap.current_bitmap = 13; //THREE
    }

    counter = 0;
    bitmap_refresh();
    led_set (LED1, 0); // LIGHT OFF
    while (counter < 2500) {

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);

    }
    if (bitmap.player_score == 3 || bitmap.opponent_score == 3) {
        if (bitmap.player_score == 3) {
            bitmap.current_bitmap = 7;
        } else {
            bitmap.current_bitmap = 8;
        }

        counter = 1;
        bitmap_refresh();
        while (counter) {  //FOREVER

            counter++;
            pacer_wait ();
            bitmap = display_bitmap(bitmap);

            if (bitmap.player_score == 3) {

                flash_led(counter);

            }

        }
    }

    bitmap_refresh();
    led_set (LED1, 0); // LIGHT OFF
    bitmap.current_column = 0;
    bitmap.current_bitmap = 1;
    bitmap.opponent_bitmap = 0;
    bitmap.locked_in = 0;
    return bitmap;

}
