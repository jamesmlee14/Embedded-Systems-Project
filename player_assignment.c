/*
 * player_phase.c
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 */


#include "system.h"
#include "bitmap.h"
#include "led.h"
#include "button.h"
#include "ir_uart.h"
#include "pacer.h"

#include "player_assignment.h"


Player_Bitmap player_assignment (Player_Bitmap bitmap)
{

    if (!bitmap.player) {

        bitmap = display_bitmap(bitmap);
        led_set (LED1, 1); // LIGHT ON
        button_update ();

        if (button_push_event_p (BUTTON1)) {
            bitmap.player = 1;
            bitmap.current_bitmap = 5;
            ir_uart_putc(2);  //sending
        }
        if (ir_uart_read_ready_p()) {
            char set_player2 = ir_uart_getc();
            if (set_player2 == 2) {
                bitmap.player = set_player2;
                bitmap.current_bitmap = 6;
            }
        }
    }


    if (bitmap.player) {
        led_set (LED1, 0); // LIGHT OFF


        uint16_t counter = 0;
        bitmap_refresh();
        while (counter < 2500) { //wait 5sec
            pacer_wait ();
            counter++;
            bitmap = display_bitmap(bitmap);
        }
    }

    return bitmap;

}
