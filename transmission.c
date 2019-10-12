/*
 * transmission.c
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *

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

        if (bitmap.player == 1 && !sent) {
            ir_uart_putc(bitmap.current_bitmap);  //1sending
            sent = 1;
        }
        if (bitmap.player == 2 && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();              //2recieving
            ir_uart_putc(bitmap.current_bitmap);  //2sending
            sent = 1;
        }
        if (bitmap.player == 1 && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();   //1recieving
            sent = 1;
        }
        if (sent && recieved) {
            bitmap.opponent_bitmap = recieved;
            finished = 1;
        }


    }

/*
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
*/
    led_set (LED1, 0); // LIGHT OFF
    return bitmap;



}
