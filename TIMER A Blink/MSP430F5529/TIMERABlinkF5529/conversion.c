#include <msp430.h>

int conversion(int Hz)
{
    return ((32768/(Hz))-1);      // returns CCR0 value based on Hz entered using formula
}
