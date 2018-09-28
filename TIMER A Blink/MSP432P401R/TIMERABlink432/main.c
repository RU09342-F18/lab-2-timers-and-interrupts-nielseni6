#include "msp.h"

int conversion(int Hz);                         // Function that converts Hz to a CCR0 value

int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    P1DIR |= BIT0;                              // Set red LED output
    P2DIR |= BIT1;                              // Set green LED output
    TA0CCTL0 = CCIE;                            // TA0CCR0 interrupt enabled
    TA1CCTL0 = CCIE;                            // TA1CCR1 interrupt enabled
    TA0CCR0 = conversion(5);                    // Sets TA0CCR0 interrupt with parameter in Hz
    TA1CCR0 = conversion(3);                    // Sets TA1CCR0 interrupt with parameter in Hz
    TA0CTL = TASSEL_1 + MC_1;                   // ACLK, ACLK
    TA1CTL = TASSEL_1 + MC_1;                   // ACLK, ACLK

    __enable_interrupt();                       // Enable the interrupt to be used
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // Set TimerA0_0 as interrupt
    NVIC->ISER[0] = 1 << ((TA1_0_IRQn) & 31);   // Set TimerA1_0 as interrupt
    while(1);
}

void TA1_0_IRQHandler(void)                     // Interrupt when Timer hits TA1CCR0
{
   TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;   // clear interrupt flag
    P1OUT ^= BIT0;                              // P1.0 red LED toggle
}

void TA0_0_IRQHandler(void)                     // Interrupt when Timer hits TA0CCR0
{
    TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  // clear interrupt flag
    P2OUT ^= BIT1;                              // P2.1 green LED toggle
}


