#include "msp.h"

int conversion(int Hz)
{
    return ((32768/(Hz*3))-1);      // returns CCR0 value based on Hz entered using formula
}
