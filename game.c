/*
* ENCE 260 Embedded Systems Project
* Authors : James Mitchum Lee (47069487), Matthew Hornsby ()
* Date: 4 October 2019
*
* "Rock Paper Scissors BO5"
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
* Repeat 2-4 until Match decided:
*   First player to win 3 games wins match
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

#define PACER_COUNT_RATE 500

int main (void)
{
    //Initialisation
    navswitch_init ();
    system_init ();
    pacer_init (PACER_COUNT_RATE);
    bitmap_reset();
    led_init ();
    ir_uart_init();
    button_init();

    Player_Bitmap bitmap = {0, ARROW, 0, 0, 0, 0, 0, 1, 0, 0, 0};

    while (1) {

        pacer_wait ();
        navswitch_update ();


        // PLAYER ASSIGNMENT
        if (bitmap.in_player_assignment) {

            bitmap = player_assignment(bitmap);

            if (bitmap.player) {
                bitmap_reset();
                bitmap.in_player_assignment = 0;
                bitmap.in_selection_phase = 1;
                bitmap.current_bitmap = ROCK;
            }
        }


        // SELECTION
        if (bitmap.in_selection_phase) {

            bitmap = selection(bitmap);

            if (bitmap.locked_in) {

                bitmap_reset();
                led_set (LED1, 0); // LIGHT OFF
                bitmap.in_selection_phase = 0;
                bitmap.in_transmission_phase = 1;
            }
        }


        // TRANSMISSION
        if (bitmap.in_transmission_phase) {

            bitmap = transmission(bitmap);

            bitmap.in_transmission_phase = 0;
            bitmap.in_outcome_phase = 1;
        }

        // OUTCOME
        if (bitmap.in_outcome_phase) {

            bitmap = outcome(bitmap);

            bitmap.in_selection_phase = 1;
            bitmap.in_transmission_phase = 0;
            bitmap.in_outcome_phase = 0;
            bitmap.in_outcome_phase = 0;
        }
    }
}


