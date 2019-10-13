/** @file   bitmap.h
    @author James Mitchum Lee
    @date   10 October 2019
    @brief  Rock Paper Scissors BO5 Player Assignment Phase

    Bitmap functionality for game.c
*/

#ifndef BITMAP_H
#define BITMAP_H

#include "system.h"
#include "navswitch.h"

typedef struct player_bitmap_s Player_Bitmap;

struct player_bitmap_s {
    uint8_t current_column;
    uint8_t current_bitmap;
    uint8_t opponent_bitmap;
    uint8_t locked_in;
    uint8_t player;
    uint8_t player_score;
    uint8_t opponent_score;
};

/** sets led matrix to all high  */
void bitmap_refresh(void);

/** displays columns  */
void display_column (uint8_t row_pattern, uint8_t current_column);

/** displays bitmap by calling display_column  */
Player_Bitmap display_bitmap(Player_Bitmap bitmap);


#endif


