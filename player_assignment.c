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

#include "player_assignment.h"


Player_Info player_assignment (Player_Info player)
{

    if (player.is_player1 == 'F' && player.is_player2 == 'F') {

        player.bitmap = display_bitmap(player.bitmap);
        led_set (LED1, 1); // LIGHT ON
        button_update ();

        if (button_push_event_p (BUTTON1)) {
            player.is_player1 = 'T';
            ir_uart_putc('T');  //sending
        }
        if (ir_uart_read_ready_p()) {
            char set_player2 = ir_uart_getc();
            if (set_player2 == 'T') {
                player.is_player2 = set_player2;
            }
        }
    }


    if (player.is_player1 == 'T' || player.is_player2 == 'T') {
        led_set (LED1, 0); // LIGHT OFF

        if (player.is_player1 == 'T') {
                player.bitmap.current_bitmap = 5;
            } else {
                player.bitmap.current_bitmap = 6;
            }

        uint16_t counter = 0;
        while (counter < 2500) { //wait 5sec
            pacer_wait ();
            counter++;
            player.bitmap = display_bitmap(player.bitmap);
        }

        counter = 0;
        while (counter < 500) { //wait 1sec
            pacer_wait ();
            counter++;
        }
    }

    return player;

}
