#include <msp430fr2433.h>

#define LED 0x06

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    CSCTL1 = 0xF1;      //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;

    P1DIR |= LED;
    P1SEL0 |= LED;
    P1SEL1 &= ~(LED);
    TA0CCR0 = 62500-1;
    TA0CCR1 = 62500/2;
    TA0CCR2 = 62500/4;
    TA0CCTL1 = OUTMOD_7;
    TA0CCTL2 = OUTMOD_7;
    TA0CTL = TASSEL_2 + ID_3 + MC_2;
    while(1)
    {
        while((TA0CTL & TAIFG)==0);
        P1OUT ^= LED;
        TA0CTL &= ~TAIFG;
    }
}
