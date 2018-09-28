#include <msp430.h>

volatile unsigned int x = 0;                    // used to keep track of button press up/down

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                       // unlocks the GPIO pins
    P1IE |=  BIT1;                              // P1.1 (Switch2) interrupt enabled
    P1IES |= BIT1;                              // P1.1 high/low edge set
    P1IFG &= ~BIT1;                             // P1.1 interrupt flag cleared
    P1OUT &= ~BIT0;                             // green LED off to sTBrt
    P1DIR |= (BIT0);                            // Set LED1 output
    P1REN |= BIT1;                              // Set pull up resistor
    P1OUT |= BIT1;                              // Enable button

    TB0CCTL0 = CCIE;                            // TB0CCR0 interrupt enabled
    TB0CCR0 = 5000;                             // Sets TB0CCR0 interrupt value
    TB0CTL = TBSSEL_1 + MC_1 + ID_3;            // enable ACLK

    __enable_interrupt();                       // Enable the interrupt to be used
    while(1);
}

#pragma vector=PORT1_VECTOR                     // Interrupt when button is pressed and released
__interrupt void Port_1(void)
{
    P1IFG &= ~BIT1;                             // P1.3 IFG cleared
    if(!x)                                      // true when button is pressed
    {
        TBCTL = TBCLR;                          // clears the clock
        TBCTL = TBSSEL_1 + MC_2 + ID_3;         // BCLK set to continuous and divided by 8
    }
    else                                        // else when button is released
    {
        TBCCR0 = TB0R;                          // Clock set to time since button press
        TBCTL = TBSSEL_1 + MC_1 + ID_3;         // BCLK set to up and divided by 8
    }
    P1IES ^= BIT1;                              // Toggle High/low edge
    x ^= 1;                                     // Toggle x to keep track of button up/down
}

#pragma vector=TIMER0_B0_VECTOR                 // Interrupt when Timer hits TB0CCR0
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;                              // P1.0 LED toggle
}
