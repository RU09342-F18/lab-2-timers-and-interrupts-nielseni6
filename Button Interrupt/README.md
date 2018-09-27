## Button Interrupt

# Functionality

This program utilizes an interrupt to enable an LED when a button is pressed. This program is noticably smoother than a similar program which utilizes polling. Since the processor is waiting for the posedge and negedge of the button rather than checking the button at different intervals it does not have the problem of the button not working when in between polls. The button is on when the button is pressed and off when not.

# Explination

This program begins by stopping the watchdog timer.
