/*
 * transmission.c
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
#include "ir_uart.h"
#include "led.h"

Player_Bitmap transmission(Player_Bitmap bitmap)
{
    uint8_t sent = 0;
    char recieved = 0;
    ir_uart_init();

    led_set (LED1, 1); // LIGHT ON

    int finished = 0;
    while (!finished) {

        if (!sent) {

            ir_uart_putc(bitmap.current_bitmap);  //sending
            sent = 1;
        }

        if (ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();
        }

        if (sent && recieved) {
            if (recieved == 1 || recieved == 2 || recieved == 3) {
                bitmap.opponent_bitmap = recieved; //recieving
                finished = 1;
            } else {
                recieved = 0;
            }
        }

    }
    led_set (LED1, 0); // LIGHT OFF
    return bitmap;



}
