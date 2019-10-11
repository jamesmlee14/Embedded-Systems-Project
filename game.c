/*
* ENCE 260 Embedded Systems Project
* Authors : James Lee (47069487), Matthew Hornsby ()
* Date: October 2019
*
* "Rock Paper Scissors"
*
* Flow:
*
* Stage 1: (Not Finished)
* Establish player 1 and player 2 using IR.
*
* Stage 2: (Finished)
*
* Both players can toggle between the 3 bitmaps
* using navswitch east/west.
*
* pressing Button1 locks player to the current bitmap.
*
*
*
* Stag 3: (Not Finished)
*
* When both players are ready, they will press navswitch push
*
*  the symbol (Rock/Paper/Scissors) that each player selected
* is transferred to the other players screen using ir_uart module
*
* after a 3 second delay, one of three messages (W, L, T) is displayed
* depending on if the player WON, LOST, or TIED
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
    uint8_t in_player_assignment = 1;
    uint8_t in_selection_phase = 0;
    uint8_t in_transmission_phase = 0;
    uint8_t in_outcome_phase = 0;

    uint8_t sent = 0;
    char recieved = 0;

    char is_player1 = 'F';
    char is_player2 = 'F';
    uint8_t player_score = 0;

    led_set (LED1, 0); // LIGHT OFF


    while (1) {

        pacer_wait ();
        navswitch_update ();



        //PLAYER ASSIGNMENT
        if (in_player_assignment) {
            player_assignment (bitmap, is_player1, is_player2);
            led_matrix_refresh();

            if (is_player1 == 'T' || is_player2 == 'T') {
                led_matrix_refresh();
                bitmap.current_bitmap = 1;
                in_player_assignment = 0;
                in_selection_phase = 1;
            }
        }


        if (in_selection_phase && !bitmap.locked_in) {
            led_matrix_refresh();
            led_set (LED1, 0); // LIGHT OFF
            bitmap = display_bitmap(bitmap);
            if (bitmap.locked_in) {
                in_transmission_phase = 1;
                led_matrix_refresh();
                in_selection_phase = 0;
            }
        }


        if (in_transmission_phase && !sent) {

            led_set (LED1, 1); // LIGHT ON

            ir_uart_putc(bitmap.current_bitmap);  //sending
            sent = 1;
        }

        if (ir_uart_read_ready_p() && recieved == 0) {
            recieved = ir_uart_getc();

        }

        if (sent) {
            if (recieved == 1 || recieved == 2 || recieved == 3) {
                bitmap.opponent_bitmap = recieved; //recieving
            } else {
                recieved = 0;
            }
        }


        if (in_transmission_phase && recieved != 0) { //have recieved
            in_transmission_phase = 0;
            in_outcome_phase = 1;
        }

        if (in_outcome_phase) {
            led_set (LED1, 0); // LIGHT OFF

            uint16_t counter = 0;
            while (counter < 2500) { //wait 5sec
                pacer_wait ();
                counter++;
                bitmap = display_bitmap(bitmap);
            }

            in_outcome_phase = 0;

            char outcome = 'X';

            // win

            // loss

            if (bitmap.current_bitmap == bitmap.opponent_bitmap) { // draw
                outcome = 'D';
            }

            counter = 0;
            while (counter < 2500) { //wait 5sec
                pacer_wait ();
                counter++;

                led_matrix_refresh();

                if (outcome == 'W') {
                    led_set (LED1, 1); // LIGHT ON
                    bitmap.current_bitmap = 7;

                } else if (outcome == 'L') {
                    bitmap.current_bitmap = 8;

                } else if (outcome == 'D') {
                    bitmap.current_bitmap = 9;
                }
                bitmap = display_bitmap(bitmap);

            }


            counter = 0;
            while (counter < 2500) { //wait 5sec
                pacer_wait ();
                counter++;

                led_matrix_refresh();

                if (player_score == 0) {
                    bitmap.current_bitmap = 13;
                } else if (player_score == 1) {
                    bitmap.current_bitmap = 11;
                } else if (player_score == 2) {
                    bitmap.current_bitmap = 12;
                } else if (player_score == 3) {
                    bitmap.current_bitmap = 13;
                }
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
            sent = 0;
            recieved = 0;

        }






    }




}


