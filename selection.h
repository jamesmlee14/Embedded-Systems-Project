/** @file   selection.h
    @author James Mitchum Lee (jml184)
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Selection Phase

    The Selection Phase for game.c "Rock Paper Scissors Best of 5"
*/


#ifndef SELECTION_H
#define SELECTION_H

#include "system.h"
#include "bitmap.h"
#include "button.h"

/** Executes game.c Selection Phase:

    1. -Allows the Player to select from Rock, Paper and Scissors
        using Navswitch East and West,
        -Displays the current selection.

    2. -Upon a Navswitch Push, locks in the Player's current selection
        -Immediately begins Transmission Phase

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap selection(Player_Bitmap bitmap);
#endif

