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


const uint8_t ARROW_BITMAP[] = {
    0x04, 0x0E, 0x15, 0x04, 0x04
};

const uint8_t P1_BITMAP[] = {
    0x02, 0x06, 0x02, 0x02, 0x07
};

const uint8_t DRAW_BITMAP[] = {
    0x38, 0x24, 0x24, 0x24, 0x38
};

/*
0000 0010
0000 0110
0000 0010
0000 0010
0000 0111
*/

const uint8_t P2_BITMAP[] = {
    0x07, 0x09, 0x02, 0x04, 0x0f
};

/*
0000 0111
0000 1001
0000 0010
0000 0100
0000 1111
*/




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

    Bitmap_Info bitmap = {0, 1, 0, 0};

    navswitch_init ();
    system_init ();
    pacer_init (500);
    led_matrix_refresh();
    led_init ();
    ir_uart_init();
    button_init();


    uint8_t in_player_phase = 1;
    uint8_t in_selection_phase = 0;
    uint8_t in_transmission_phase = 0;
    uint8_t in_outcome_phase = 0;

    uint8_t sent = 0;
    char recieved = 0;

    char is_player1 = 'F';
    char is_player2 = 'F';
    uint8_t player_score = 0;

    led_set (LED1, 0); // LIGHT OFF

    uint8_t current_column = 0;



    while (1) {

        pacer_wait ();
        navswitch_update ();

        if (in_player_phase) {

            display_column (ARROW_BITMAP[current_column], current_column);

            current_column++;

            if (current_column > (LEDMAT_COLS_NUM - 1)) {
                current_column = 0;
            }

            led_set (LED1, 1); // LIGHT ON

            button_update ();

            if (button_push_event_p (BUTTON1)) {
                is_player1 = 'T';
                ir_uart_putc('T');  //sending
            }
            if (ir_uart_read_ready_p()) {
                char set_player2 = ir_uart_getc();
                if (set_player2 == 'T') {
                    is_player2 = set_player2;
                }
            }

        }

        if (in_player_phase && (is_player1 == 'T' || is_player2 == 'T')) {

            uint16_t counter = 0;
            while (counter < 2500) { //wait 5sec

                if (is_player1 == 'T') {
                    display_column (P1_BITMAP[current_column], current_column);

                    current_column++;

                    if (current_column > (LEDMAT_COLS_NUM - 1)) {
                        current_column = 0;
                    }

                } else {

                    display_column (P2_BITMAP[current_column], current_column);

                    current_column++;

                    if (current_column > (LEDMAT_COLS_NUM - 1)) {
                        current_column = 0;
                    }
                }


                pacer_wait ();
                navswitch_update ();

                counter++;
            }

            counter = 0;
            while (counter < 500) { //wait 1sec
                counter++;
            }

            in_player_phase = 0;
            led_matrix_refresh();
            in_selection_phase = 1;
        }




        if (in_selection_phase && !bitmap.locked_in) {
            led_matrix_refresh();
            led_set (LED1, 0); // LIGHT OFF
            bitmap = display_bitmap(bitmap.current_column, bitmap.current_bitmap, bitmap.opponent_bitmap, bitmap.locked_in);
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
                bitmap = display_bitmap(bitmap.current_column, bitmap.current_bitmap, bitmap.opponent_bitmap, bitmap.locked_in);
            }

            in_outcome_phase = 0;

            char outcome = 'D';

/*
            if (bitmap.current_bitmap == bitmap.opponent_bitmap) { // draw
                outcome = 'D';
            }
*/
            counter = 0;
            while (counter < 2500) { //wait 5sec
                led_set (LED1, 1); // LIGHT ON
                pacer_wait ();
                counter++;

                led_matrix_refresh();
                display_column (DRAW_BITMAP[current_column], current_column);

                current_column++;

                if (current_column > (LEDMAT_COLS_NUM - 1)) {
                    current_column = 0;
                }



            }



        led_matrix_refresh();
        }






    }




}


