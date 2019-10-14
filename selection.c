/** @file   selection.c
    @author James Mitchum Lee
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Selection Phase

    The Selection Phase for game.c "Rock Paper Scissors Best of 5"
*/


#include "bitmap.h"
#include "led.h"
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
Player_Bitmap selection(Player_Bitmap bitmap)
{
    if (bitmap.player == 1) {
        led_set (LED1, 1); // LIGHT ON
    }


    if (!bitmap.locked_in) {

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {

            bitmap.current_bitmap++;

            if (bitmap.current_bitmap > SCISSORS) {
                bitmap.current_bitmap = ROCK;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {

            bitmap.current_bitmap--;

            if (bitmap.current_bitmap < ROCK) {
                bitmap.current_bitmap = SCISSORS;
            }
        }

        button_update ();

        if (button_push_event_p (BUTTON1)) {
            bitmap.locked_in = 1;
        }
    }

    bitmap = display_bitmap(bitmap);
    return bitmap;
}
