/*
 * selection.c
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
#include "led.h"


Bitmap_Info selection(Bitmap_Info bitmap)
{
    led_set (LED1, 1); // LIGHT ON

    if (!bitmap.locked_in) {

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            bitmap.current_bitmap++;
            if (bitmap.current_bitmap > 3) {
                bitmap.current_bitmap = 1;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            bitmap.current_bitmap--;
            if (bitmap.current_bitmap < 1) {
                bitmap.current_bitmap = 3;
            }
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            bitmap.locked_in = 1;
        }

    }
    bitmap = display_bitmap(bitmap);
    return bitmap;

}
