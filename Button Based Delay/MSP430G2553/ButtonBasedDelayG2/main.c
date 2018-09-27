#include <msp430.h>

volatile unsigned int time1 = 0;                // used to record timer at button press
volatile unsigned int time2 = 1000;             // used to record timer at button release
volatile unsigned int cycle1 = 0;               // used to record cycle number at button press
volatile unsigned int cycle2 = 0;               // used to record cycle number at button release
volatile unsigned int cycleCount = 0;           // used to count every cycle of the timer in up mode
volatile unsigned int x = 0;                    // used to keep track of button press up/down

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer
    BCSCTL3 = LFXT1S_2;                         // Makes ACKL use internal oscillator
    P1DIR &= ~BIT3;                             // configure P1.3 as input
    P1IE |=  BIT3;                              // P1.3 (Switch2) interrupt enabled
    P1IES |= BIT3;                              // P1.3 high/low edge set
    P1IFG &= ~BIT3;                             // P1.3 interrupt flag cleared
    P1OUT &= ~BIT0;                             // green LED off to start
    P1DIR |= (BIT0 + BIT6);                     // Set green and red LED output
    TA0CCTL0 = CCIE;                            // TA0CCR0 interrupt enabled
    TA0CCR0 = 5000;                             // Sets TA0CCR0 interrupt value
    TA0CTL = TASSEL_1 + MC_1;                   // enable ACLK

  __enable_interrupt();                         // Enable the interrupt to be used
}

#pragma vector=PORT1_VECTOR                     // Interrupt when button is pressed and released
__interrupt void Port_1(void)
{
    P1IFG &= ~BIT3;                             // P1.3 IFG cleared
    if(!x)                                      // true when button is pressed
    {
        time1 = TA0R;                           // record timer at button press
        cycle1 = cycleCount;                    // record cycle number at button press
    }
    else                                        // else when button is released
    {
        time2 = TA0R;                           // record timer at button release
        cycle2 = cycleCount;                    // record cycle number at button release
        TA0CCR0 = ((time2 + ((cycle2 - cycle1)*TA0CCR0)) - time1);  // set CCR0 = dT + (dCycles * (Current CCR0))
    }                                           // dT = Duration of Button Press : d = Delta
    P1IES ^= BIT3;                              // Toggle High/low edge
    x ^= 1;                                     // Toggle x to keep track of button up/down
}

#pragma vector=TIMER0_A0_VECTOR                 // Interrupt when Timer hits TA0CCR0
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT0;                              // P1.0 LED toggle
    cycleCount++;                               // Counts Number timer cycles since start
}