#include <msp430fr2433.h>

#define LED 0x06
#define PERIODO 10000

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    CSCTL1 = 0xF1;      //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;

    P1DIR |= 0x06;
    TA0CCR0 = 62500-1;
    TA0CTL = TASSEL_2 + ID_3 + MC_1;

    for(;;)
    {
        while((TA0CTL&TAIFG)==0);
        P1OUT ^= 0x06;
        TA0CTL &= ~TAIFG;
    }
}
