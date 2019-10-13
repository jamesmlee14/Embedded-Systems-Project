/** @file   outcome.c
    @author James Mitchum Lee
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Outcome Phase
*/


#include "outcome.h"
#include "bitmap.h"
#include "led.h"
#include "pacer.h"

#define HALF_SECOND 250
#define FIVE_SECONDS 2500


 /** Return outcome of Rock Paper Scissors Game.
    @param  current the players selection, 1 if Rock, 2 if Paper,
    3 if scissors.
    @param opponent the opponents selection, 1 if Rock, 2 if Paper,
    3 if scissors.
    @return game result 1 if Win, 2 if Loss, 0 if Draw   */
uint8_t get_result(uint8_t current, uint8_t opponent)
{
    current++;
    opponent++;
    uint8_t game_result = (current - opponent + 3) % 3;
    return game_result;
}


  /** Flashes the LED periodically
    @param  counter the current value of the loop counter*/
void flash_led(int counter)
{
    if ((counter % HALF_SECOND) == 0) {
        if (((counter / HALF_SECOND) % 2) == 0) {
            led_set (LED1, 0); // LIGHT OFF
        }
        if (((counter / HALF_SECOND) % 2) == 1) {
            led_set (LED1, 1); // LIGHT ON
        }


    }

}


  /** Executes game.c Outcome Phase:

    1. Displays the players and their opponents selections for 5 seconds

    2. Displays a letter representing the players outcome in the game
        -Flashes the LED if the player won a game

    3. Displays the player's current score accross the match for 5 seconds

    4. If the match is decided, Displays the players outcome
        -Flashes the LED if the player won the match
        -Continues until board is reset.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct   */
Player_Bitmap outcome(Player_Bitmap bitmap)
{

    int counter = 0;
    while (counter < FIVE_SECONDS) {
        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);
    }

    uint8_t outcome = get_result(bitmap.current_bitmap, bitmap.opponent_bitmap);

    if (outcome == 1) {
        bitmap.player_score++;
        bitmap.current_bitmap = WIN;

    } else if (outcome == 2) {
        bitmap.opponent_score++;
        bitmap.current_bitmap = LOSS;

    } else if (outcome == 0) {
        bitmap.current_bitmap = DRAW;
    }

    counter = 0;
    bitmap_reset();

    while (counter < FIVE_SECONDS) {

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);
        if (outcome == 1) {
            flash_led(counter);

        }

    }

    if (bitmap.player_score == 0) {
        bitmap.current_bitmap = ZERO;
    } else if (bitmap.player_score == 1) {
        bitmap.current_bitmap = ONE;
    } else if (bitmap.player_score == 2) {
        bitmap.current_bitmap = TWO;
    } else if (bitmap.player_score == 3) {
        bitmap.current_bitmap = THREE;
    }

    counter = 0;
    bitmap_reset();
    led_set (LED1, 0); // LIGHT OFF
    while (counter < FIVE_SECONDS) {

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);

    }
    if (bitmap.player_score == 3 || bitmap.opponent_score == 3) {
        if (bitmap.player_score == 3) {
            bitmap.current_bitmap = WIN;
        } else {
            bitmap.current_bitmap = LOSS;
        }

        counter = 0;
        bitmap_reset();
        while (1) {

            counter++;
            pacer_wait ();
            bitmap = display_bitmap(bitmap);

            if (bitmap.player_score == 3) {

                flash_led(counter);

            }

        }
    }

    bitmap_reset();
    led_set (LED1, 0); // LIGHT OFF
    bitmap.current_column = 0;
    bitmap.current_bitmap = ROCK;
    bitmap.opponent_bitmap = 0;
    bitmap.locked_in = 0;
    return bitmap;

}
