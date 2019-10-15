/*
* ENCE 260 Embedded Systems Project
* Group 219 - James Mitchum Lee (jml184), Matthew Hornsby (mlh136)
* Filename: game.c
* Author: James Mitchum Lee (jml184)
* Date: 4 October 2019
* 
* "Rock Paper Scissors Best of 5"
*
* Match Flow:
*
* 1. Player Assignment
*
* 2. Selection Phase
*
* 3. Transmission Phase
*
* 4. Outcome Phase
*
* Repeats 2-4 until Match decided-First player to win 3 games wins match
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
    pacer_init(PACER_COUNT_RATE);
    navswitch_init();
    system_init();
    led_init();
    ir_uart_init();
    button_init();
    bitmap_reset();

    Player_Bitmap bitmap = {0, ARROW, 0, 0, 0, 0, 0, 1, 0, 0, 0};

    while (1) {

        pacer_wait();
        navswitch_update();


        if (bitmap.in_player_assignment) {

            bitmap = player_assignment(bitmap);

            if (bitmap.player) {

                bitmap.in_player_assignment = 0;

                bitmap_reset();
                bitmap.current_bitmap = ROCK;
                bitmap.in_player_assignment = 0;
                bitmap.in_selection_phase = 1;
            }
        }


        if (bitmap.in_selection_phase) {

            bitmap = selection(bitmap);

            if (bitmap.locked_in) {

                bitmap.in_selection_phase = 0;
                bitmap_reset();
                led_set (LED1, 0);
                bitmap.in_transmission_phase = 1;
            }
        }


        if (bitmap.in_transmission_phase) {

            bitmap = transmission(bitmap);

            bitmap.in_transmission_phase = 0;
            bitmap.in_outcome_phase = 1;
        }


        if (bitmap.in_outcome_phase) {

            bitmap = outcome(bitmap);

            bitmap.in_outcome_phase = 0;
            bitmap.in_selection_phase = 1;
        }
    }
}


