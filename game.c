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


void led_matrix_refresh(void)
{
    /*Refresh LED matrix pins.  */
    pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);

    pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
}


int main (void)
{
    navswitch_init ();
    system_init ();
    pacer_init (500);
    led_matrix_refresh();
    led_init ();
    ir_uart_init();
    button_init();

    Bitmap_Info bitmap = {0, 4, 0, 0};
    Player_Info player = {bitmap, 'F', 'F'};
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

            player = player_assignment(player);

            if (player.is_player1 == 'T' || player.is_player2 == 'T') {
                led_matrix_refresh();
                bitmap.current_bitmap = 1;
                in_player_assignment = 0;
                in_selection_phase = 1;
            }
        }


        // SELECTION
        if (in_selection_phase) {

            led_matrix_refresh();
            bitmap = selection(bitmap);

            if (bitmap.locked_in) {

                led_matrix_refresh();
                led_set (LED1, 0); // LIGHT OFF
                in_transmission_phase = 1;
                in_selection_phase = 0;
            }
        }


        // TRANSMISSION
        if (in_transmission_phase) {

            bitmap = transmission(bitmap);
            in_transmission_phase = 0;
            in_outcome_phase = 1;

        }


        if (in_outcome_phase) {


            uint16_t counter = 0;
            while (counter < 2500) { //display both bitmaps for 5 sec
                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);
            }


            char outcome = 'X';

            if ((bitmap.current_bitmap == 1 && bitmap.opponent_bitmap == 3) || (bitmap.current_bitmap == 2 && bitmap.opponent_bitmap == 1) || (bitmap.current_bitmap == 3 && bitmap.opponent_bitmap == 2)) { // win
                outcome = 'W';
            }
            if ((bitmap.current_bitmap == 1 && bitmap.opponent_bitmap == 2) || (bitmap.current_bitmap == 2 && bitmap.opponent_bitmap == 3) || (bitmap.current_bitmap == 3 && bitmap.opponent_bitmap == 1)) { // loss
                outcome = 'L';
            }
            if (bitmap.current_bitmap == bitmap.opponent_bitmap) {  // draw
                outcome = 'D';
            }


            if (outcome == 'W') {
                    player_score++;
                    led_set (LED1, 1); // LIGHT ON
                    bitmap.current_bitmap = 7;

                } else if (outcome == 'L') {
                    bitmap.current_bitmap = 8;

                } else if (outcome == 'D') {
                    bitmap.current_bitmap = 9;
                }

            counter = 0;
            led_matrix_refresh();

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
            led_matrix_refresh();
            led_set (LED1, 0); // LIGHT OFF
            while (counter < 2500) { //display score for 5sec

                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);

            }



            led_matrix_refresh();
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


