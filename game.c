/*
* ENCE 260 Embedded Systems Project
* Authors : James Lee (47069487), Matthew Hornsby ()
* Date: October 2019
*
* "Rock Paper Scissors"
*
* Flow:
*
* Loop 1: (Finished)
*
* Both players can toggle between the 3 bitmaps
* using navswitch east/west.
*
* pressing (Button1)navswitch push locks player to the current bitmap.
*
*
*
* Loop 2: (Not Finished)
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
#include "button.h"

#include "navswitch.h"


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


static const uint8_t ROCK_BITMAP[] = {
    0x00, 0x07, 0x07, 0x07, 0x00
};

static const uint8_t PAPER_BITMAP[] = {
    0x07, 0x07, 0x07, 0x07, 0x07
};

static const uint8_t SCISSORS_BITMAP[] = {
    0x05, 0x05, 0x02, 0x07, 0x07
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

    /* TODO */
    for (int i = 0; i < 7; i++) { //7 times
        if (row_pattern >> i & 1) {
            pio_output_low (rows[i]);
        } else {
            pio_output_high (rows[i]);
        }
    }

    pio_output_low (cols[current_column]);
    prev_column = current_column;



}


void led_matrix_init()
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

int main (void)
{


    uint8_t current_bitmap = 1;


    uint8_t current_column = 0;

    navswitch_init ();
    system_init ();
    pacer_init (500);
    led_matrix_init();
    button_init ();

    int locked_in = 0;


    while (1) {
        pacer_wait ();

        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_EAST) && !locked_in) {
            current_bitmap++;
            if (current_bitmap > 3) {
                current_bitmap = 1;
            }


        }

        if (navswitch_push_event_p (NAVSWITCH_WEST) && !locked_in) {
            current_bitmap--;
            if (current_bitmap < 1) {
                current_bitmap = 3;
            }

        }
        if (current_bitmap == 1) {
            display_column (ROCK_BITMAP[current_column], current_column);
        } else if (current_bitmap == 2) {
            display_column (PAPER_BITMAP[current_column], current_column);
        } else if (current_bitmap == 3) {
            display_column (SCISSORS_BITMAP[current_column], current_column);
        }


        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1)) {
            current_column = 0;
        }

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) { // TO DO: Implement button functionality, button1 will be used here
            locked_in = 1;
        }

    }
}
