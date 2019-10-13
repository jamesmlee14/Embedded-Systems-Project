/*
* ENCE 260 Embedded Systems Project
* Authors : James Mitchum Lee (47069487), Matthew Hornsby ()
* Date: 4 October 2019
*
* "Rock Paper Scissors"
*
* Match Flow:
*
* 1. Player Assignment
*
* Game:
*
* 2. Selection Phase
*
* 3. Transmission Phase
*
* 4. Outcome Phase
*
* Repeat 2-4 until Match decided.
*
*
*
*
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "timer.h"
#include "led.h"

#include "button.h"



#include "navswitch.h"

#include "ir_uart.h"



#include "bitmap.h"
#include "player_assignment.h"
#include "selection.h"
#include "transmission.h"
#include "outcome.h"

int main (void)
{
    navswitch_init ();
    system_init ();
    pacer_init (500);
    bitmap_refresh();
    led_init ();
    ir_uart_init();
    button_init();

    Player_Bitmap bitmap = {0, 4, 0, 0, 0, 0, 0};
    uint8_t in_player_assignment = 1;
    uint8_t in_selection_phase = 0;
    uint8_t in_transmission_phase = 0;
    uint8_t in_outcome_phase = 0;


    while (1) {

        pacer_wait ();
        navswitch_update ();


        // PLAYER ASSIGNMENT
        if (in_player_assignment) {

            bitmap = player_assignment(bitmap);

            if (bitmap.player) {
                bitmap_refresh();
                bitmap.current_bitmap = 1;
                in_player_assignment = 0;
                in_selection_phase = 1;
            }
        }


        // SELECTION
        if (in_selection_phase) {

            bitmap = selection(bitmap);

            if (bitmap.locked_in) {

                bitmap_refresh();
                led_set (LED1, 0); // LIGHT OFF
                in_selection_phase = 0;
                in_transmission_phase = 1;
            }
        }


        // TRANSMISSION
        if (in_transmission_phase) {

            bitmap = transmission(bitmap);

            in_transmission_phase = 0;
            in_outcome_phase = 1;
        }

        // OUTCOME
        if (in_outcome_phase) {

            bitmap = outcome(bitmap);

            in_selection_phase = 1;
            in_transmission_phase = 0;
            in_outcome_phase = 0;
            in_outcome_phase = 0;
        }
    }
}


