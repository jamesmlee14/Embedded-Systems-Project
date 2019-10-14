/** @file   bitmap.h
    @author James Mitchum Lee
    @date   10 October 2019
    @brief  Rock Paper Scissors BO5 Player Assignment Phase

    The Bitmap module for use in game.c "Rock Paper Scissors Best of 5"
    and it's modules.
*/

#ifndef BITMAP_H
#define BITMAP_H

#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define ARROW 4
#define WIN 7
#define LOSS 8
#define DRAW 9
#define ZERO 10
#define ONE 11
#define TWO 12
#define THREE 13

#define N_ROWS 7

#include "system.h"
#include "navswitch.h"

/* Player's Bitmap information structure type
*/
typedef struct player_bitmap_s Player_Bitmap;


/* Player's Bitmap information structure
*/
struct player_bitmap_s {
    uint8_t current_column;
    uint8_t current_bitmap;
    uint8_t opponent_bitmap;
    uint8_t locked_in;
    uint8_t player;
    uint8_t player_score;
    uint8_t opponent_score;
    uint8_t in_player_assignment;
    uint8_t in_selection_phase;
    uint8_t in_transmission_phase;
    uint8_t in_outcome_phase;
};


/** Resets the bitmap to blank by setting all pins to HIGH.
*/
void bitmap_reset(void);


/** Updates the current_column to display the correct pattern.
    @param  pattern the hex value of the current column in
    the desired pattern
    @param  current_column the column to update
*/
void display_column (uint8_t pattern, uint8_t current_column);


/** Displays the desired bitmap using the display_column function.
    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap display_bitmap(Player_Bitmap bitmap);


#endif


