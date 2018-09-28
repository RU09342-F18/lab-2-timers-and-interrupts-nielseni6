# Timer A Blink (Timer B Blink on MSP430FR2311)

## Boards Used

  *MSP430G2553
  
  *MSP430FR2311

## Functionality

This program utilizes an interrupt to enable an LED when a button is pressed. This program is noticably smoother than a similar program which utilizes polling. Since the processor is waiting for the high/low of the button rather than checking the button at different intervals it does not have the problem of the button not working when in between polls. The button is on when the button is pressed and off when not.

## Explanation

This program begins by stopping the watchdog timer. After this the LED is set to output (P1.0 on G2553 and F2559) and turned off to start. Next the button (P2.1 on F2559 and P1.6 of G2553) is set to be an interrupt, is set to high edge interrupt and the interrupt flag is cleared. After this interrupt is enabled. The interrupt function that is called when the interrupt defined at the button press occurs toggles the LED, clears the flag, then toggles the high/low edge trigger so that the interrupt will be triggered again when the button is released.
