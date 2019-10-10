/*
 * bitmaps.c
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "bitmap.h"
#include "navswitch.h"
#include "pio.h"


const uint8_t ROCK_INVERSE_BITMAP[] = {
    0x00, 0x07, 0x07, 0x07, 0x00
};

const uint8_t PAPER_INVERSE_BITMAP[] = {
    0x07, 0x07, 0x07, 0x07, 0x07
};

const uint8_t SCISSORS_INVERSE_BITMAP[] = {
    0x05, 0x05, 0x02, 0x07, 0x07
};

const uint8_t ROCK_BITMAP[] = {
    0x00, 0x70, 0x70, 0x70, 0x00
};

const uint8_t PAPER_BITMAP[] = {
    0x70, 0x70, 0x70, 0x70, 0x70
};

const uint8_t SCISSORS_BITMAP[] = {
    0x50, 0x50, 0x20, 0x70, 0x70
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




const uint8_t WIN_BITMAP[] = {
    0x22, 0x22, 0x2A, 0x2A, 0x14
};

const uint8_t LOSS_BITMAP[] = {
    0x10, 0x10, 0x10, 0x10, 0x1C
};



/** Define PIO pins driving LED matrix rows.  */
const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};



void display_column (uint8_t row_pattern, uint8_t current_column)
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
