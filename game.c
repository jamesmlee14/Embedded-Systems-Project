/*
* ENCE 260 Embedded Systems Project
* Authors : James Lee (47069487), Matthew Hornsby ()
* Date: October 2019
*
* "Rock Paper Scissors"
*
* Flow:
*
* 1. Player Assignment
*
* 2. Selection Phase
*
* 3. Transmission Phase
*
* 4. Outcome Phase
*
* Repeat
*
* REPEAT
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



int get_result(int current, int opponent)
{
    current++;
    opponent++;
    int result = (current - opponent + 3) % 3;
    return result;
}



int main (void)
{
    navswitch_init ();
    system_init ();
    pacer_init (500);
    bitmap_refresh();
    led_init ();
    ir_uart_init();
    button_init();

    Player_Bitmap bitmap = {0, 4, 0, 0, 0};
    uint8_t in_player_assignment = 1;
    uint8_t in_selection_phase = 0;
    uint8_t in_transmission_phase = 0;
    uint8_t in_outcome_phase = 0;


    uint8_t player_score = 0;

    led_set (LED1, 0); // LIGHT OFF


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

            if (bitmap.opponent_bitmap)
            in_transmission_phase = 0;
            in_outcome_phase = 1;

        }

        // OUTCOME


        if (in_outcome_phase) {

            uint16_t counter = 0;
            while (counter < 2500) {    //display both bitmaps for 5 sec
                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);
            }


            int outcome = get_result(bitmap.current_bitmap, bitmap.opponent_bitmap);

            if (outcome == 1) { // WIN
                    player_score++;
                    led_set (LED1, 1); // LIGHT ON
                    bitmap.current_bitmap = 7;

                } else if (outcome == 2) {   // LOSS
                    bitmap.current_bitmap = 8;

                } else if (outcome == 0) {   // DRAW
                    bitmap.current_bitmap = 9;
                }

            counter = 0;
            bitmap_refresh();

            while (counter < 2500) { //display outcome for 5sec

                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);

            }

            if (player_score == 0) {
                    bitmap.current_bitmap = 10;
                } else if (player_score == 1) {
                    bitmap.current_bitmap = 11;
                } else if (player_score == 2) {
                    bitmap.current_bitmap = 12;
                } else if (player_score == 3) {
                    bitmap.current_bitmap = 13;
                }

            counter = 0;
            bitmap_refresh();
            led_set (LED1, 0); // LIGHT OFF
            while (counter < 2500) { //display score for 5sec

                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);

            }



            bitmap_refresh();
            led_set (LED1, 0); // LIGHT OFF


            bitmap.current_column = 0;
            bitmap.current_bitmap = 1;
            bitmap.opponent_bitmap = 0;
            bitmap.locked_in = 0;

            in_selection_phase = 1;
            in_transmission_phase = 0;
            in_outcome_phase = 0;


            in_outcome_phase = 0;
        }







    }




}


