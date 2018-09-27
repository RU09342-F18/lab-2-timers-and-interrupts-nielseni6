#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output (red LED)
  P2REN |= BIT1;                            // Set pull up resistor on 2.1
  P2IE |=  BIT1;                            // P2.1 (SwitchRight) interrupt enabled
  P2IES |= BIT1;                            // P2.1 set to high/low edge
  P2IFG &= ~BIT1;                           // P2.1 IFG (interrupt flag) cleared
  P1OUT &= ~BIT0;                           // P1.0 red LED set to off

  __enable_interrupt();                     // Enable the interrupt to be used
}
#pragma vector=PORT2_VECTOR                 // Interrupt when button is pressed and released
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;                          // P1.0 red LED toggle
    P2IFG &= ~BIT1;                         // P1.1 IFG (interrupt flag) cleared
    P2IES ^= BIT1;                          // Toggle High/low edge
}
