/** @file   transmission.c
    @author James Mitchum Lee (jml184)
    @date   12 October 2019
    @brief  Rock Paper Scissors BO5 Transmission Phase

    The Transmission Phase for game.c "Rock Paper Scissors Best of 5"
*/

#include "system.h"
#include "bitmap.h"
#include "ir_uart.h"
#include "led.h"
#include "pacer.h"


/** Executes game.c Transmission Phase:

    1. Player 1 sends their selection.

    2. Player 2 recieves and stores player 1's selection.

    3. Player 2 sends their selection.

    4. Player 1 recieves and stores player 2's selection.

    @param  bitmap the player's Player_Bitmap struct
    @return the player's updated Player_Bitmap struct
*/
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
            ir_uart_putc(bitmap.current_bitmap);  // Player 1 sending
            sent = 1;
        }

        if (bitmap.player == 2 && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();              // Player 2 Recieving
            if (recieved == ROCK || recieved == PAPER || recieved == SCISSORS) {
                bitmap.opponent_bitmap = recieved;
            } else {
                recieved = 0;
            }
        }

        if (bitmap.player == 2 && recieved && !sent) {
            ir_uart_putc(bitmap.current_bitmap);  // Player 2 Sending
            sent = 1;
        }

        if (bitmap.player == 1 && sent && ir_uart_read_ready_p() && !recieved) {
            recieved = ir_uart_getc();   // Player 1 Recieving
            if (recieved == ROCK || recieved == PAPER || recieved == SCISSORS) {
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
