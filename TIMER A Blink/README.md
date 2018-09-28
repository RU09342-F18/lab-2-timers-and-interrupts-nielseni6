# Timer A Blink (Timer B Blink on MSP430FR2311)

## Boards Used

  * MSP430G2553
  
  * MSP430FR2311

## Functionality

This program blinks two LEDs at two different rates. The way that it is set up now has the green LED toggling at 5 Hz and the red LED toggling at 3 Hz. This speed can be set in Hz using the conversion function found within the project file.

## Explanation

This program begins by stopping the watchdog timer. After this the LED is set to output (P1.0 on G2553 and FR2311) and turned off to start. Next the timer (Timer_B on FR2311 and Timer_A on G2553) is set to be an interrupt. There are two interrupts so that means that Timer_0 and Timer_1 are initiated as interrupts each with their own CCR0 values. After this interrupt is enabled. The interrupt function that is called when the interrupt defined at the button press occurs toggles the LED, clears the flag, then toggles the high/low edge trigger so that the interrupt will be triggered again when the button is released.

