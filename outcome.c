/*
 * outcome.c
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


#include "outcome.h"
#include "bitmap.h"
#include "led.h"




int get_result(int current, int opponent)
{
    current++;
    opponent++;
    int result = (current - opponent + 3) % 3;
    return result;
}

Player_Bitmap outcome(Player_Bitmap bitmap)
{

    uint16_t counter = 0;
    while (counter < 2500) { //display both bitmaps for 5 sec
        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);
    }

    int outcome = get_result(bitmap.current_bitmap, bitmap.opponent_bitmap);

    if (outcome == 1) { // WIN
        bitmap.player_score++;
        led_set (LED1, 1); // LIGHT ON
        bitmap.current_bitmap = 7;

    } else if (outcome == 2) {   // LOSS
        bitmap.current_bitmap = 8;

    } else if (outcome == 0) {   // DRAW
        bitmap.current_bitmap = 9;
    }

    counter = 0;
    bitmap_refresh();

    while (counter < 2500) { //display outcome for 5sec

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);

    }

    if (bitmap.player_score == 0) {
        bitmap.current_bitmap = 10;
    } else if (bitmap.player_score == 1) {
        bitmap.current_bitmap = 11;
    } else if (bitmap.player_score == 2) {
        bitmap.current_bitmap = 12;
    } else if (bitmap.player_score == 3) {
        bitmap.current_bitmap = 13;
    }

    counter = 0;
    bitmap_refresh();
    led_set (LED1, 0); // LIGHT OFF
    while (counter < 2500) { //display score for 5sec

        pacer_wait ();
        counter++;
        bitmap = display_bitmap(bitmap);

    }

    bitmap_refresh();
    led_set (LED1, 0); // LIGHT OFF
    bitmap.current_column = 0;
    bitmap.current_bitmap = 1;
    bitmap.opponent_bitmap = 0;
    bitmap.locked_in = 0;
    return bitmap;

}
