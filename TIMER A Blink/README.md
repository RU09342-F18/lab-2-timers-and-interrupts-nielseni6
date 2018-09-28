# Timer A Blink (Timer B Blink on MSP430FR2311)

## Boards Used

  * MSP430G2553
  
  * MSP430FR2311
  
  * MSP432P401R

## Functionality

This program blinks two LEDs at two different rates. The way that it is set up now has the green LED toggling at 5 Hz and the red LED toggling at 3 Hz. This speed can be set in Hz using the conversion function found within the project file.

## Explanation

This program begins by stopping the watchdog timer. After this the LED is set to output (P1.0) and turned off to start. Next the timer (Timer_B on MSP430FR2311 and Timer_A on MSP430G2553 and MSP432P401) is set to be an interrupt. There are two interrupts so that means that Timer_0 and Timer_1 are initiated as interrupts each with their own CCR0 values. The timer control is then set to ACLK/BCLK and is set to up. After this interrupt is enabled. The interrupt function that is called when the interrupt defined at the button press occurs toggles the LED. Since the interrupts are triggered at different times the LEDs blink at different intervals.

### ERRATA:

The MSP432 functions differently than the MSP430 series so the LEDs do not blink at even intervals. This might be caused by something in the clock not being connected correctly. Time to fix this issue has ran out sadly but in other labs it will need to be addressed in order to complete.
