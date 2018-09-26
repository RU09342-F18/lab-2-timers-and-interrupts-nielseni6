#include <msp430.h>

int conversion(int Hz);                         // Function that converts Hz to a CCR0 value

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer
  BCSCTL3 = LFXT1S_2;                           // Makes ACKL use internal oscillator
  P1DIR |= (BIT0 + BIT6);                       // Set green and red LED output
  TA0CCTL0 = CCIE;                              // TA0CCR0 interrupt enabled
  TA1CCTL0 = CCIE;                              // TA1CCR1 interrupt enabled
  TA0CCR0 = conversion(5);                      // Sets TA0CCR0 interrupt with parameter in Hz
  TA1CCR0 = conversion(3);                      // Sets TA1CCR0 interrupt with parameter in Hz
  TA0CTL = TASSEL_1 + MC_1;                     // ACLK, ACLK
  TA1CTL = TASSEL_1 + MC_1;                     // ACLK, ACLK

  __enable_interrupt();                         // Enable the interrupt to be used
}
#pragma vector=TIMER1_A0_VECTOR                 // Interrupt when Timer hits TA1CCR0
__interrupt void Timer_A1(void)
{
    P1OUT ^= BIT6;                              // P1.6 red LED toggle
}
#pragma vector=TIMER0_A0_VECTOR                 // Interrupt when Timer hits TA0CCR0
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;                              // P1.0 green LED toggle
}


