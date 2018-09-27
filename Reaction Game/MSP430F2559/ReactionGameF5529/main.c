#include <msp430.h>

volatile unsigned int LEDison = 0;          // Keeps track of whether LED is on or off
volatile unsigned int cycles = 0;           // Keeps track of cycles, used to create a delay on blink that is longer than CCR0
volatile unsigned int waitcycles = 5;       // Determines number of cycles that will wait
volatile unsigned int i,j;                  // Used for delays

int main(void)
{
  P1DIR &= ~BIT1;                           // P1.1 (SW1) Output
  P2DIR &= ~BIT1;                           // P2.1 (SW2) Output

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output (red LED)
  P1OUT |= BIT1;                            // Enable pull-up resistor on P1.1
  P4DIR |= BIT7;                            // Set P4.7 to output (green LED)
  P1REN |= BIT1;                            // Set pull up resistor on P1.1
  P1IE |=  BIT1;                            // P1.1 (Switch1) interrupt enabled
  P1IES |= BIT1;                            // P1.1 set to high/low edge
  P1IFG &= ~BIT1;                           // P1.1 IFG (interrupt flag) cleared

  P2REN |= BIT1;                            // Set pull up resistor on P2.1
  P2IE |=  BIT1;                            // P2.1 (Switch2) interrupt enabled
  P2IES |= BIT1;                            // P2.1 set to high/low edge
  P2IFG &= ~BIT1;                           // P2.1 IFG (interrupt flag) cleared
  P1OUT &= ~BIT0;                           // P1.0 red LED set to off
  P4OUT &= ~BIT7;                           // P4.7 green LED set to off

  TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
  TA0CCR0 = 80000;                          // Sets TA0CCR0 interrupt value
  TA0CTL = TASSEL_1 + MC_1;                 // enable ACLK

  __enable_interrupt();                     // Enable the interrupt to be used
}
#pragma vector=PORT1_VECTOR                 // Interrupt when button is pressed and released
__interrupt void Port_1(void)
{
    if(((P1IES) & BIT1)==BIT1){             // Fixes issues with bounce on button release
    if(LEDison){                            // If the LED is on then the player gets win condition, else they lose since they pressed too early
        P1OUT &= ~BIT0;                     // Red LED off
        P4OUT |= BIT7;                      // Green LED on
    }else{
        P1OUT |= BIT0;                      // Red LED off
        P4OUT &= ~BIT7;                     // Green LED on
    }
    LEDison = 0;                            // Turns off LED indicator
    cycles = 0;                             // Resets cycles, essentially resetting the game
    }
    for(i=0;i<5000;i++);                    // Button bounce delay
    P1IFG &= ~BIT1;                         // P1.1 IFG (interrupt flag) cleared
    P1IES ^= BIT1;                          // Toggle Interrupt high/low, used in conjuction w/ if(((P1IES) & BIT1)==BIT1){ to fix button bounce on release
}
#pragma vector=PORT2_VECTOR                 // Interrupt when button is pressed and released
__interrupt void Port_2(void)
{
    if(((P2IES) & BIT1)==BIT1){             // Fixes issues with bounce on button release
    if(LEDison){                            // If the LED is on then the player gets win condition, else they lose since they pressed too early
        P1OUT |= BIT0;                      // Green LED on
        P4OUT &= ~BIT7;                     // Red LED off
    }else{
        P1OUT &= ~BIT0;                     // Red LED off
        P4OUT |= BIT7;                      // Green LED on
    }
    LEDison = 0;                            // Turns off LED indicator
    cycles = 0;                             // Resets cycles, essentially resetting the game
    }
    for(j=0;j<5000;j++);                    // Button bounce delay
    P2IFG &= ~BIT1;                         // P1.1 IFG (interrupt flag) cleared
    P2IES ^= BIT1;                          // Toggle Interrupt high/low, used in conjuction w/ if(((P2IES) & BIT1)==BIT1){ to fix button bounce on release
}
#pragma vector=TIMER0_A0_VECTOR             // Interrupt when Timer hits TA0CCR0
__interrupt void Timer_A(void)
{
    if (waitcycles == cycles){              // Adds delay since CCR0 has an upper limit
        P1OUT |= BIT0;                      // P1.0 LED on
        P4OUT |= BIT7;                      // P4.7 LED on
        LEDison = 1;                        // tracks if LED is on
    }else{
        cycles++;                           // Tracks cycles
    }
}
