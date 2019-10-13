/** @file   player_assignment.c
    @author James Mitchum Lee
    @date   11 October 2019
    @brief  Rock Paper Scissors BO5 Player Assignment Phase
*/


#include "system.h"
#include "bitmap.h"
#include "led.h"
#include "button.h"
#include "ir_uart.h"
#include "pacer.h"

#include "player_assignment.h"

  /** Executes game.c Player Assignment Phase:

    1. Displays an arrow instructing the player to press the button

    2. Whichever player presses the button first becomes Player 1, and
       Informs the second board it is Player 2 using IR communication

    3. Displays the player's assignment, either 1 or 2.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct   */
Player_Bitmap player_assignment (Player_Bitmap bitmap)
{

    if (!bitmap.player) {

        bitmap = display_bitmap(bitmap);
        led_set (LED1, 1); // LIGHT ON
        button_update ();

        if (button_push_event_p (BUTTON1)) {
            bitmap.player = 1;
            bitmap.current_bitmap = ONE;
            ir_uart_putc(2);  //sending
        }
        if (ir_uart_read_ready_p()) {
            char set_player2 = ir_uart_getc();
            if (set_player2 == 2) {
                bitmap.player = set_player2;
                bitmap.current_bitmap = TWO;
            }
        }
    }


    if (bitmap.player) {
        led_set (LED1, 0); // LIGHT OFF


        uint16_t counter = 0;
        bitmap_reset();
        while (counter < 2500) { //wait 5sec
            pacer_wait ();
            counter++;
            bitmap = display_bitmap(bitmap);
        }
    }

    return bitmap;

}
