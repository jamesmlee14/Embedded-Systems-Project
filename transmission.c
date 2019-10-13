/** @file   transmission.c
    @author James Mitchum Lee
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Transmission Phase
*/

#include "system.h"
#include "bitmap.h"
#include "ir_uart.h"
#include "led.h"
#include "pacer.h"


  /** Executes game.c Transmission Phase:

    1. Player 1 sends their selection

    2. Player 2 recieves and stores player 1's selection

    3. Player 2 sends their selection

    4. Player 1 recieves and stores player 2's selection.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct   */
Player_Bitmap transmission(Player_Bitmap bitmap)
{
    uint8_t sent = 0;
    char recieved = 0;
    ir_uart_init();

    led_set (LED1, 0); // LIGHT OFF

    int finished = 0;
    while (!finished) {

        pacer_wait();

        if (bitmap.player == 1 && !sent) {
            ir_uart_putc(bitmap.current_bitmap);  // 1sending
            sent = 1;
        }

        if (bitmap.player == 2 && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();              // 2recieving
            if (recieved == 1 || recieved == 2 || recieved == 3) {
                bitmap.opponent_bitmap = recieved;
            } else {
                recieved = 0;
            }
        }

        if (bitmap.player == 2 && recieved && !sent) {
            ir_uart_putc(bitmap.current_bitmap);  // 2sending
            sent = 1;
        }

        if (bitmap.player == 1 && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();   // 1recieving
            if (recieved == 1 || recieved == 2 || recieved == 3) {
                bitmap.opponent_bitmap = recieved;
            } else {
                recieved = 0;
            }
        }
        if (sent && recieved) {
            finished = 1;
        }


    }

    led_set (LED1, 0); // LIGHT OFF
    return bitmap;



}
