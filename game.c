/*
* ENCE 260 Embedded Systems Project
* Authors : James Lee (47069487), Matthew Hornsby ()
* Date: October 2019
*
* "Rock Paper Scissors"
*
* Flow:
*
* Loop 1: (Not Finished)
*
* Both players can toggle between the 3 bitmaps
* using navswitch east/west.
*
* pressing navswitch push locks player to the current bitmap.
*
* Loop 2: (Not Finished)
*
* the symbol (Rock/Paper/Scissors) that each player selected
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


/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


static const uint8_t rock_bitmap[] =
{
    0x00, 0x07, 0x07, 0x07, 0x00
};


static const uint8_t paper_bitmap[] =
{
    0x07, 0x07, 0x07, 0x07, 0x07
};


static const uint8_t scissors_bitmap[] =
{
    0x05, 0x05, 0x02, 0x07, 0x07
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


void led_matrix_init() {

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
    uint8_t current_column = 0;

    system_init ();
    pacer_init (500);

    led_matrix_init();


    while (1)
    {
        pacer_wait ();

        display_column (scissors_bitmap[current_column], current_column);

        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }
    }
}
