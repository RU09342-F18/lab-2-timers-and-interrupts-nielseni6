# Button Based Delay

## Boards Used

  * MSP430G2553
  
  * MSP430FR2311

## Functionality

This program blinks an LED at a rate determined by the time that a button is depressed. The longer the button is held, the lower the frequency of the LED blink and the quicker the button is pressed the higher the frequency of the LED.

## Explanation

This program begins by stopping the watchdog timer. After this the LED is set to output (P1.0 on G2553 and F5529LP) and turned off to start. Next the Timer_A is set to be an interrupt. There are two interrupts so that means that Timer_0 and Timer_1 are initiated as interrupts each with their own CCR0 values. After this interrupt is enabled. The interrupt function that is called when the interrupt defined at the button press occurs clears the flag, clears the clock, sets timer to continuous, then toggles the high/low edge trigger as well as x, which keeps track of whether the button is depressed or not. Then when the button is released the same interrupt is triggered but this time, since x is 1, CCR0 is set to the current timer value (TA0R) and the timer is set back to up. 
