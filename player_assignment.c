/*
 * player_phase.c
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


#include "system.h"
#include "bitmap.h"
#include "led.h"
#include "button.h"
#include "ir_uart.h"
#include "pacer.h"


Bitmap_Info player_assignment (Bitmap_Info bitmap, char is_player1, char is_player2)
{

    if (is_player1 == 'F' && is_player2 == 'F') {

        bitmap = display_bitmap(bitmap);
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

    } else {

        uint16_t counter = 0;
        while (counter < 2500) { //wait 5sec

            if (is_player1 == 'T') {

                bitmap.current_bitmap = 5;

                bitmap = display_bitmap(bitmap);

            } else {

                bitmap.current_bitmap = 6;

                bitmap = display_bitmap(bitmap);

            }
            pacer_wait ();
            counter++;
        }

        counter = 0;
        while (counter < 500) { //wait 1sec
            pacer_wait ();
            counter++;
        }
    }

    return bitmap;

}
