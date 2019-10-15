/** @file   outcome.h
    @author James Mitchum Lee (jml184)
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Outcome Phase

    The Outcome Phase for game.c "Rock Paper Scissors Best of 5"
*/


#ifndef outcome_H
#define outcome_H

#include "outcome.h"
#include "bitmap.h"
#include "led.h"


/** Return outcome of Rock Paper Scissors Game.
    @param  current the players selection, 1 if Rock, 2 if Paper,
    3 if scissors.
    @param opponent the opponents selection, 1 if Rock, 2 if Paper,
    3 if scissors.
    @return game result 1 if Win, 2 if Loss, 0 if Draw
*/
uint8_t get_result(uint8_t current, uint8_t opponent);


/** Flashes the LED periodically
    @param  counter the current value of the loop counter
*/
void flash_led(int counter);


/** Executes game.c Outcome Phase:

    1. Displays the players and their opponents selections for 5 seconds.

    2. Displays a letter representing the players outcome in the game.
        -Flashes the LED if the player won a game.

    3. Displays the player's current score accross the match for 5 seconds.

    4. If the match is decided, Displays the players outcome.
        -Flashes the LED if the player won the match.
        -Continues until board is reset.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap outcome(Player_Bitmap bitmap);
#endif


