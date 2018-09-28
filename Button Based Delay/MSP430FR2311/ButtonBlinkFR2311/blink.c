
#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P1DIR &= ~BIT1;                         // configure P1.1 as input


    volatile unsigned int i;                // volatile to prevent optimization
    int k = 1;                              // blink speed state: 0 - off, 1 - slow, 2 - medium, 3 - fast
    int j = 0;                              // counter to set blink interval - waits to reach x
    int x = 8;                              // blink interval - the higher the slower the blink
    int p;
    while(1)
    {
        p = (P1IN & BIT1);
        if (j >= x){                        // waits for j to reach x (blink delay)
        if (k != 0) P1OUT ^= 0x01;          // toggle P1.0(LED)
        if (k == 0) P1OUT = 0x00;           // turn off P1.0(LED)
        j = 0;                              // resets j for next blink
        } else {
            j++;                            // counts up for j to be used for blink delay
        }
        if (k > 3) k = 0;                   // resets k to 0 once highest state is reached
        if (k == 1) x = 32;                 // set delay time slow
        if (k == 2) x = 16;                 // set delay time medium
        if (k == 3) x = 8;                  // set delay time fast
        if((P1IN & BIT1)){                  // checks P1.3 (BUTTON)
            k++;                            // if button is pressed the blink interval goes up
            while ((P1IN & BIT1));          // waits until button is leg go before continuing
        }
        for(i=(1000); i>0; i--);            // delay
    }
}
