#include <msp430fr2433.h>
#include <msp430.h>

#define LED 0x06
#define PERIODO 10000

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    CSCTL1 = 0xF1;      //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;       //MCLK e SMCLK @ 1MHz
    P1DIR |= LED;
    P1SEL0 |= LED;
    P1SEL1 &= ~LED;
    TA0CCR0 = PERIODO-1;
    TA0CCR1 = 0;
    TA0CCTL0 = OUTMOD_7;
    TA0CTL = TASSEL_2 + ID_0 + MC_2 + TAIE;
    _BIS_SR(LPM0_bits + GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR

__interrupt void TA0_ISR(void)
{
    static int direcao = 0, cont = 0;
    // Aumentar o ciclo de trabalho ate o maximo
    if(direcao==0)
    {
        cont++;
        TA0CCR0 = cont*cont;
        if(cont>=100)
            direcao = 1;
    }
    // Diminuir o ciclo de trabalho ate o minimo
    else if(direcao==1)
    {
        cont--;
        TA0CCR0 = cont*cont;
        if(cont<=12)
            direcao = 0;
    }
    TA0CTL &= ~TAIFG;
}