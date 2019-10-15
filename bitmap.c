/** @file   bitmap.h
    @author James Mitchum Lee, Matthew Hornsby
    @date   10 October 2019
    @brief  Rock Paper Scissors BO5 Bitmap functionality

    The Bitmap module for use in game.c "Rock Paper Scissors Best of 5"
    and it's modules.
*/


#include "bitmap.h"
#include "navswitch.h"
#include "pio.h"


/** Define led matrix bitmap patterns for use in the
    display_bitmap function.
*/
const uint8_t ROCK_BITMAP[] = {
    0x00, 0x70, 0x70, 0x70, 0x00
};

const uint8_t PAPER_BITMAP[] = {
    0x70, 0x70, 0x70, 0x70, 0x70
};

const uint8_t SCISSORS_BITMAP[] = {
    0x50, 0x50, 0x20, 0x70, 0x70
};

const uint8_t ROCK_INVERSE_BITMAP[] = {
    0x00, 0x07, 0x07, 0x07, 0x00
};

const uint8_t PAPER_INVERSE_BITMAP[] = {
    0x07, 0x07, 0x07, 0x07, 0x07
};

const uint8_t SCISSORS_INVERSE_BITMAP[] = {
    0x05, 0x05, 0x02, 0x07, 0x07
};

const uint8_t ROCK_ROCK_BITMAP[] = {
    0x00, 0x77, 0x77, 0x77, 0x00
};

const uint8_t ROCK_PAPER_BITMAP[] = {
    0x07, 0x77, 0x77, 0x77, 0x07
};

const uint8_t ROCK_SCISSORS_BITMAP[] = {
    0x05, 0x75, 0x72, 0x77, 0x07
};

const uint8_t PAPER_ROCK_BITMAP[] = {
    0x70, 0x77, 0x77, 0x77, 0x70
};

const uint8_t PAPER_PAPER_BITMAP[] = {
    0x77, 0x77, 0x77, 0x77, 0x77
};

const uint8_t PAPER_SCISSORS_BITMAP[] = {
    0x75, 0x75, 0x72, 0x77, 0x77
};

const uint8_t SCISSORS_ROCK_BITMAP[] = {
    0x50, 0x57, 0x27, 0x77, 0x70
};

const uint8_t SCISSORS_PAPER_BITMAP[] = {
    0x57, 0x57, 0x27, 0x77, 0x77
};

const uint8_t SCISSORS_SCISSORS_BITMAP[] = {
    0x55, 0x55, 0x22, 0x77, 0x77
};

const uint8_t ARROW_BITMAP[] = {
    0x04, 0x0E, 0x15, 0x04, 0x04
};

const uint8_t ZERO_BITMAP[] = {
    0x06, 0x09, 0x09, 0x09, 0x06
};

const uint8_t ONE_BITMAP[] = {
    0x02, 0x06, 0x02, 0x02, 0x07
};

const uint8_t TWO_BITMAP[] = {
    0x07, 0x09, 0x02, 0x04, 0x0f
};

const uint8_t THREE_BITMAP[] = {
    0x0E, 0x01, 0x06, 0x01, 0x0E
};

const uint8_t DRAW_BITMAP[] = {
    0x38, 0x24, 0x24, 0x24, 0x38
};

const uint8_t WIN_BITMAP[] = {
    0x22, 0x22, 0x2A, 0x2A, 0x14
};

const uint8_t LOSS_BITMAP[] = {
    0x10, 0x10, 0x10, 0x10, 0x1C
};


/** Define PIO pins driving LED matrix rows.
*/
const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.
*/
const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


/** Updates the current_column to display the correct pattern.

    @param  pattern the hex value of the current column in
    the desired pattern
    @param  current_column the column to update
*/
void display_column (uint8_t pattern, uint8_t current_column)
{
    static uint8_t prev_column = 0;
    pio_output_high (cols[prev_column]);

    for (uint8_t i = 0; i < N_ROWS; i++) {
        if (pattern >> i & 1) {
            pio_output_low (rows[i]);
        } else {
            pio_output_high (rows[i]);
        }
    }
    pio_output_low (cols[current_column]);
    prev_column = current_column;

}


/** Resets the bitmap to blank by setting all pins to HIGH.
*/
void bitmap_reset(void)
{

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


/** Displays the desired bitmap using the display_column function.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
Player_Bitmap display_bitmap(Player_Bitmap bitmap)
{

    if (bitmap.in_player_assignment) {

        if (bitmap.current_bitmap == ARROW) {

            display_column (ARROW_BITMAP[bitmap.current_column], bitmap.current_column);

        } else if (bitmap.current_bitmap == ONE) {

            display_column (ONE_BITMAP[bitmap.current_column], bitmap.current_column);

        } else if (bitmap.current_bitmap == TWO) {

            display_column (TWO_BITMAP[bitmap.current_column], bitmap.current_column);
        }

    } else if (bitmap.in_selection_phase) {

        if (bitmap.current_bitmap == ROCK) {

            display_column (ROCK_BITMAP[bitmap.current_column], bitmap.current_column);

        } else if (bitmap.current_bitmap == PAPER) {

            display_column (PAPER_BITMAP[bitmap.current_column], bitmap.current_column);

        } else if (bitmap.current_bitmap == SCISSORS) {

            display_column (SCISSORS_BITMAP[bitmap.current_column], bitmap.current_column);
        }

    } else if (bitmap.in_outcome_phase) {

        if (bitmap.current_bitmap == ROCK) {

            if (bitmap.opponent_bitmap == ROCK) {

                display_column (ROCK_ROCK_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == PAPER) {

                display_column (ROCK_PAPER_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == SCISSORS) {

                display_column (ROCK_SCISSORS_BITMAP[bitmap.current_column], bitmap.current_column);
            }

        } else if (bitmap.current_bitmap == PAPER) {

            if (bitmap.opponent_bitmap == ROCK) {

                display_column (PAPER_ROCK_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == PAPER) {

                display_column (PAPER_PAPER_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == SCISSORS) {

                display_column (PAPER_SCISSORS_BITMAP[bitmap.current_column], bitmap.current_column);
            }

        } else if (bitmap.current_bitmap == SCISSORS) {

            if (bitmap.opponent_bitmap == ROCK) {

                display_column (SCISSORS_ROCK_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == PAPER) {

                display_column (SCISSORS_PAPER_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.opponent_bitmap == SCISSORS) {

                display_column (SCISSORS_SCISSORS_BITMAP[bitmap.current_column], bitmap.current_column);
            }

        } else {

            if (bitmap.current_bitmap == WIN) {

                display_column (WIN_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == LOSS) {

                display_column (LOSS_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == DRAW) {

                display_column (DRAW_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == ZERO) {

                display_column (ZERO_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == ONE) {

                display_column (ONE_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == TWO) {

                display_column (TWO_BITMAP[bitmap.current_column], bitmap.current_column);

            } else if (bitmap.current_bitmap == THREE) {

                display_column (THREE_BITMAP[bitmap.current_column], bitmap.current_column);
            }
        }
    }

    bitmap.current_column++;

    if (bitmap.current_column > (LEDMAT_COLS_NUM - 1)) {
        bitmap.current_column = 0;
    }

    return bitmap;

}
