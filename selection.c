/*
 * selection.c
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 *
 *
 */


#include "bitmap.h"
#include "led.h"


Player_Bitmap selection(Player_Bitmap bitmap)
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
