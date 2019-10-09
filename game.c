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
*
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
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "button.h"



#include "navswitch.h"

#include "ir_uart.h"


typedef struct bitmap_info_s Bitmap_Info;

struct bitmap_info_s {
    uint8_t current_column;
    uint8_t current_bitmap;
    uint8_t opponent_bitmap;
    uint8_t locked_in;
};


/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

static const uint8_t ROCK_INVERSE_BITMAP[] = {
    0x00, 0x07, 0x07, 0x07, 0x00
};

static const uint8_t PAPER_INVERSE_BITMAP[] = {
    0x07, 0x07, 0x07, 0x07, 0x07
};

static const uint8_t SCISSORS_INVERSE_BITMAP[] = {
    0x05, 0x05, 0x02, 0x07, 0x07
};

static const uint8_t ROCK_BITMAP[] = {
    0x00, 0x70, 0x70, 0x70, 0x00
};

static const uint8_t PAPER_BITMAP[] = {
    0x70, 0x70, 0x70, 0x70, 0x70
};

static const uint8_t SCISSORS_BITMAP[] = {
    0x50, 0x50, 0x20, 0x70, 0x70
};

static const uint8_t ROCK_ROCK_BITMAP[] = {
    0x00, 0x77, 0x77, 0x77, 0x00
};

static const uint8_t ROCK_PAPER_BITMAP[] = {
    0x07, 0x77, 0x77, 0x77, 0x07
};

static const uint8_t ROCK_SCISSORS_BITMAP[] = {
    0x05, 0x75, 0x72, 0x77, 0x07
};


static const uint8_t PAPER_ROCK_BITMAP[] = {
    0x70, 0x77, 0x77, 0x77, 0x70
};

static const uint8_t PAPER_PAPER_BITMAP[] = {
    0x77, 0x77, 0x77, 0x77, 0x77
};

static const uint8_t PAPER_SCISSORS_BITMAP[] = {
    0x75, 0x75, 0x72, 0x77, 0x77
};


static const uint8_t SCISSORS_ROCK_BITMAP[] = {
    0x50, 0x57, 0x27, 0x77, 0x70
};

static const uint8_t SCISSORS_PAPER_BITMAP[] = {
    0x57, 0x57, 0x27, 0x77, 0x77
};

static const uint8_t SCISSORS_SCISSORS_BITMAP[] = {
    0x55, 0x55, 0x22, 0x77, 0x77
};




static const uint8_t WIN_BITMAP[] = {
    0x22, 0x22, 0x2A, 0x2A, 0x14
};

static const uint8_t DRAW_BITMAP[] = {
    0x38, 0x24, 0x24, 0x24, 0x38
};

static const uint8_t LOSS_BITMAP[] = {
    0x10, 0x10, 0x10, 0x10, 0x1C
};



static void display_column (uint8_t row_pattern, uint8_t current_column)
{

    static uint8_t prev_column = 0;

    pio_output_high (cols[prev_column]);

    for (uint8_t i = 0; i < 7; i++) { //7 times
        if (row_pattern >> i & 1) {
            pio_output_low (rows[i]);
        } else {
            pio_output_high (rows[i]);
        }
    }

    pio_output_low (cols[current_column]);
    prev_column = current_column;



}


void led_matrix_init(void)
{

    /*Initialise LED matrix pins.  */
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


Bitmap_Info display_bitmap(uint8_t current_column, uint8_t current_bitmap, uint8_t opponent_bitmap, uint8_t locked_in)
{

    // Code for Selection Phase


    if (!locked_in) {

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            current_bitmap++;
            if (current_bitmap > 3) {
                current_bitmap = 1;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            current_bitmap--;
            if (current_bitmap < 1) {
                current_bitmap = 3;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            locked_in = 1;
        }

        if (opponent_bitmap == 0) {

            if (current_bitmap == 1) {
                display_column (ROCK_BITMAP[current_column], current_column);
            } else if (current_bitmap == 2) {
                display_column (PAPER_BITMAP[current_column], current_column);
            } else if (current_bitmap == 3) {
                display_column (SCISSORS_BITMAP[current_column], current_column);
            }


        }


    }


    if (opponent_bitmap != 0) {

        // rock and rock
        if (current_bitmap == 1 && opponent_bitmap == 1) {
            display_column (ROCK_ROCK_BITMAP[current_column], current_column);
        }
        // rock and paper
        if (current_bitmap == 1 && opponent_bitmap == 2) {
            display_column (ROCK_PAPER_BITMAP[current_column], current_column);
        }
        //rock and scissors
        if (current_bitmap == 1 && opponent_bitmap == 3) {
            display_column (ROCK_SCISSORS_BITMAP[current_column], current_column);
        }

        //paper and rock
        if (current_bitmap == 2 && opponent_bitmap == 1) {
            display_column (PAPER_ROCK_BITMAP[current_column], current_column);
        }
        //paper and paper
        if (current_bitmap == 2 && opponent_bitmap == 2) {
            display_column (PAPER_PAPER_BITMAP[current_column], current_column);
        }
        //paper and scissors
        if (current_bitmap == 2 && opponent_bitmap == 3) {
            display_column (PAPER_SCISSORS_BITMAP[current_column], current_column);
        }

        //scissors and rock
        if (current_bitmap == 3 && opponent_bitmap == 1) {
            display_column (SCISSORS_ROCK_BITMAP[current_column], current_column);
        }
        //scissors and paper
        if (current_bitmap == 3 && opponent_bitmap == 2) {
            display_column (SCISSORS_PAPER_BITMAP[current_column], current_column);
        }
        //scissors and scissors
        if (current_bitmap == 3 && opponent_bitmap == 3) {
            display_column (SCISSORS_SCISSORS_BITMAP[current_column], current_column);
        }
    }


    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1)) {
        current_column = 0;
    }

    Bitmap_Info update = {current_column, current_bitmap, opponent_bitmap, locked_in};
    return update;

}





int main (void)
{

    Bitmap_Info bitmap = {0, 1, 0, 0};

    navswitch_init ();
    system_init ();
    pacer_init (500);
    led_matrix_init();
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

    led_set (LED1, 0); // LIGHT OFF





    while (1) {

        pacer_wait ();
        navswitch_update ();
        led_matrix_init();




        if (in_player_phase) {

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
            in_player_phase = 0;
            in_selection_phase = 1;
        }


        if (in_selection_phase && !bitmap.locked_in) {
            bitmap = display_bitmap(bitmap.current_column, bitmap.current_bitmap, bitmap.opponent_bitmap, bitmap.locked_in);
            if (bitmap.locked_in) {
                in_transmission_phase = 1;
                led_matrix_init();
                in_selection_phase = 0;
            }
        }


        if (in_transmission_phase && !sent) {

            led_set (LED1, 1); // LIGHT ON

            ir_uart_putc(bitmap.current_bitmap);  //sending
            sent = 1;
        }



        if (ir_uart_read_ready_p() && sent) {
            recieved = ir_uart_getc();

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
            bitmap = display_bitmap(bitmap.current_column, bitmap.current_bitmap, bitmap.opponent_bitmap, bitmap.locked_in);
        }





    }
}
