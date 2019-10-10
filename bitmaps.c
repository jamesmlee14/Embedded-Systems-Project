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


#include <bitmaps.h>


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

const uint8_t DRAW_BITMAP[] = {
    0x38, 0x24, 0x24, 0x24, 0x38
};

const uint8_t LOSS_BITMAP[] = {
    0x10, 0x10, 0x10, 0x10, 0x1C
};

