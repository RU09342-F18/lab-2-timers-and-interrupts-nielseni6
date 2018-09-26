#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output
  P1IE |=  BIT3;                            // P1.3 (Switch2) interrupt enabled
  P1IES |= BIT3;                            // P1.3 set to high/low edge
  P1IFG &= ~BIT3;                           // P1.3 IFG (interrupt flag) cleared
  P1OUT &= ~BIT0;                           // P1.0 green LED set to off

  __enable_interrupt();                     // Enable the interrupt to be used
}
#pragma vector=PORT1_VECTOR                 // Interrupt when button is pressed and released
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;                          // P1.0 green LED toggle
    P1IFG &= ~BIT3;                         // P1.3 IFG (interrupt flag) cleared
    P1IES ^= BIT3;                          // Toggle High/low edge
}
