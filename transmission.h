/** @file   transmission.h
    @author James Mitchum Lee
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Transmission Phase

    The Transmission Phase for game.c "Rock Paper Scissors Best of 5"
*/


#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "system.h"
#include "bitmap.h"
#include "ir_uart.h"


/** Executes game.c Transmission Phase:

    1. Player 1 sends their selection

    2. Player 2 recieves and stores player 1's selection

    3. Player 2 sends their selection

    4. Player 1 recieves and stores player 2's selection.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap transmission(Player_Bitmap bitmap);


#endif
