/** @file   player_assignment.h
    @author James Mitchum Lee (jml184)
    @date   11 October 2019
    @brief  Rock Paper Scissors BO5 Player Assignment Phase

    The Player Assignment Phase for game.c "Rock Paper Scissors Best of 5"
*/


#ifndef PLAYER_ASSIGNMENT_H
#define PLAYER_ASSIGNMENT_H

#include "system.h"
#include "bitmap.h"


/** Executes game.c Player Assignment Phase:

    1. Displays an arrow instructing the player to press the button

    2. Whichever player presses the button first becomes Player 1, and
       Informs the second board it is Player 2 using IR communication.

    3. Displays the player's assignment, either 1 or 2.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap player_assignment (Player_Bitmap bitmap);
#endif


