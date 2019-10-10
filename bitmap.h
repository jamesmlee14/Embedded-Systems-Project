/*
 * bitmaps.h
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


#ifndef BITMAP_H
#define BITMAP_H

#include "system.h"
#include "navswitch.h"

typedef struct bitmap_info_s Bitmap_Info;

struct bitmap_info_s {
    uint8_t current_column;
    uint8_t current_bitmap;
    uint8_t opponent_bitmap;
    uint8_t locked_in;
};

/** displays columns  */
void display_column (uint8_t row_pattern, uint8_t current_column);

/** displays bitmap by calling display_column  */
Bitmap_Info display_bitmap(uint8_t current_column, uint8_t current_bitmap, uint8_t opponent_bitmap, uint8_t locked_in);

/** declares bitmap variables  */
void bitmaps_init(void);

#endif


