================================================================================================================================

                +@@@@@@@@@+                                                        @@@@@@@@,     @@@@@@@@@@
              *@&        .(@@*                       #@@@@@&                    @@.      (@.  @@,         @@
              /@.            @@   @@@@@             %@     &@                   @%       &@   @(          /@.
              /@.            *@@@@(,,,(@@@ &@&@@@@(&@(     (&@/     @@@@%%%%%@@@@/     (@@(   @,          &@.
              /@.     @%     *@,         (@%                 @&   &@(          @,        @&  .@.     %&@@@%
              /@.           /@            *         @        @%  %@.            #       .@&  ,@           &@*
              /@.            ,     @@@           @@@@(     &@.   &@     ,@@     /#     @@,   ,@,           @@
              /@.     @&.                 .@         (     &@    &@     /@@     *#     @&      @@@@@@%     %@
              /@.                   ,,...(@  %@@     (     (%@#  &@      @.     %#     @&    &@,  .((      %@
              /@.            ,%     /#      @          &       %@  .@@           *@#     @&    @#           @
              /@#          (@@%@&.       %@%       %@@@.     @@    #@@       *@@@@    ,@&    %@(        %@@
                &@@@@@@@@@&/    ,&@@@@@@&/ (@@@@@@@/  ,@@@@@@,       ,@@@@@@@%   (@@@@@.       (@@@@@@@&*


                                             A Game by Jimmy Lee and Matthew Hornsby
                                                       (47069483)       (48081532)

                                                                16/10/2019

================================================================================================================================

        Best of 5 is a game created for the University of Canterbury fun kit 4 (UCfk4) platform. It is a recreation
        of the popular game; Rock, Paper, Scissors, in which the players will compete until a player has won 3 games.

================================================================================================================================

                 The Board                                                Action Choices

               X X X | X X X                                                  O O O            O   O
               X X X | X X X                                O O O             O O O            O   O
               X X X | X X X                                O O O             O O O              O
               X X X | X X X                                O O O             O O O            O O O
               X X X | X X X                                                  O O O            O O O
                 ^   ^   ^                                    ^                 ^                ^
                 |   |   |                                    |                 |                |
                 |   |   |                                   Rock             Paper           Scissors
    Your Play Area   |   Opponents Play Area
                     |
                   Divider



================================================================================================================================

                                                                                            @@@@*
      @@@@@@,  @@@@@@*                                  @@@@                              @&    @%
     @&    ,@ @%    .@                                @@.  *@/                            @*    @%
     @&    ,@ @%    .@.@@@@@@@@@@@@@@@%@@@@@%@@@@@/  #@*    @@%&@@@@@@@@.     ,@@@@@@@@@@&@*    @&@@@@@@@@@&@@@@@@%@@@@@&
     @&    ,@@@%    .@&         @     @     @    .@  @       .@         &@.   @          .@*    @@         /,    #@     @.
     @&             .&           ,    (     (    &@  @*      (           #@   @.          **    @@,         &     .    #@
     @&             .*    &@*    %               @.   @.    @%    .@%     @   @,    %@     *    @@% @@@     %%        /@.
     @&    ,@@@%    ./    #@,    &%             &@    @.    @%     @#    .@   @,    %@     *    @,          %@        @&
     @&    ,@ @%    .@           @@      *     ,@,    @,      .          &@   @,          %/    %     @     #@@      @@
     @&    ,@ @%    .@@.       *@(@%     @     @@     @@      @#       .@@    @,         &@@    %           *@@(    ,@
      &@@@@@   @@@@@@. &@@@@@@@%   &@@@@@(@@@@@%        @@@@@@#(@@@@@@@&      @,    %@@@@,  @@@@@@@@@@@@@@@@@#@     @#
                                                                              @,    %&                       @*    &@
                                                                              ,@@@@@@                        *@@@@@@

Note: This game is designed to be played on two University of Canterbury FunKit Microcontrollers.

Installation:

1. Clone the repositiory for the game somewhere to your local machine.

2. In the file browser, navigate to the assignment/group219 folder.

3. Open the terminal in the group 219 folder.

4. Ensure both ucfunkits are plugged into the computer.

5. Enter the command 'make program' (no quotes). Reset the Microcontrollers, using the button labelled 'S2' if there are problems.

6. When the command has finished executing, repeat the command to start the second Microcontroller.


     -  Set the two boards down approximately 2cm away from one another, with the IR Reciever (Labelled U1) of each board aligned
        with the opposing board's IR Transmitter (Labelled IR1)

     -  Play starts when one of the players presses the button next to the LED matrix display, indicated by the large arrow.
        The first to press this button is designated as Player 1, and the other as Player 2.

     -  After each player is informed of their player number, the selection phase will begin.

     -  Player 2 must avert their eyes while Player 1 makes their selection first.

     -  Move the Navigational Switch up and down to toggle your selection between Rock Paper and Scissors.
        To lock in your selection, at any time press the white button located above the board.

     -  Once Player 1 has locked in a selection, it will disappear, allowing for Player 2 to open their eyes and make their selection.


     -  After both selections are made, all will be revealed, with both screens displaying both player's selections.

     -  After

     -  The game continues until one player gains three points. This is the required score to win the majority of five games.
    Once this has been reached, the boards will display the winner with a W on their board and a L on the losers board.

     -  In order to play another game, the reset switch on the boards is pressed once the final winner / loser is displayed.

================================================================================================================================
