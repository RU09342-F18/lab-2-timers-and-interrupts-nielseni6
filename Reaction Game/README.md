# Reaction Game

## Board Used

* MSP430F5529

## Rules of The Game/Functionality

When the program starts both players should be ready with their fingers on the button. Both the green and the red LED start in the off state. The players then need to wait for both LEDs to turn on. The LEDs should turn on after around  The person who presses the button fastest wins the round and the LED on their side stays on while the other LED turns off. If a player presses their button before the LEDs turn on they lose the round and the other player's LED turns on. Then the next round then starts and the players wait until both LEDs turn back on.

## Explination

This program begins by stopping the watchdog timer. After this the red and green LEDs at P1.1 and P4.7 are set to output. Next the button interrupts for the buttons at P1.1 and P2.1 are initiated. Next the timer is set to ACLK and set to up. After this the interrupt is set and CCR0 is set to the max value that it can be set to. When the timer interrupt occurs there is an if statement that checks how many timer cycles have occured. If 8 timer cyles have occured then the LEDs turn on. When the button interrupts are enabled they check whether the LED is on. If the LED is on then the win condition is enabled, if not the opposite player's win condition is enabled. There are also two debounces for the button in each of the button interrupts. The first interrupt uses a for loop a delay that fixes the bounce for the down press. The second debounce is to fix the bounce that occurs when you let go of the button. That debounce works by toggling the hi/lo edge of the interrupt and also using an if statement that checks which hi/lo edge is set so that the code only runs when the button is depressed. I do not want the win state to be enabled when the button is released so this is necessary. Comments in the code show specifics.
