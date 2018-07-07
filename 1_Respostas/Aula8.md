### Para todas as questões, utilize os LEDs e/ou os botões da placa Launchpad do MSP430.

## 1. Escreva um código em C que pisca os LEDs ininterruptamente.

```C
#include <msp430fr2433.h>

#define LED1 BIT0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1){
      P1OUT ^= LED1;
      __delay_cycles(100000); //100ms = 100000us
    }
}
```

## 2. Escreva um código em C que pisca os LEDs ininterruptamente. No ciclo que pisca os LEDs, o tempo que os LEDs ficam ligados deve ser duas vezes maior do que o tempo que eles ficam desligados.

```C
#include <msp430fr2433.h>

#define LED1 BIT0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1){
      P1OUT |= LED1;
      __delay_cycles(1000000); //1000ms = 1000000us
      P1OUT &= ~LED1;
      __delay_cycles(500000); //500ms = 500000us
    }
}
```

## 3. Escreva um código em C que acende os LEDs quando o botão é pressionado.
```C
#include <msp430fr2433.h>

#define LED1 BIT0
#define BTN BIT3

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    P1DIR |= LED1;              // Set P1.0 to output direction
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;

    while(1){
      if((P2IN & BTN)==0)
      {
          P1OUT |= LED1;
      }
      else
          P1OUT &= ~LED1;
    }
}
```

## 4. Escreva um código em C que pisca os LEDs ininterruptamente somente se o botão for pressionado.
```C
#include <msp430fr2433.h>

#define LED1 BIT0
#define BTN BIT3

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    P1DIR |= LED1;              // Set P1.0 to output direction
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;

    while(1){
      if((P2IN & BTN)==0)
      {
          P1OUT ^= LED1;
          __delay_cycles(100000); //100ms = 100000us
      }
      else
          P1OUT &= ~LED1;
    }
}
```
## 5. Escreva um código em C que acende os LEDs quando o botão é pressionado. Deixe o MSP430 em modo de baixo consumo, e habilite a interrupção do botão.

```C
#include <msp430fr2433.h>

#define LED1 BIT0
#define BTN BIT3

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    P1DIR |= LED1;              // Set P1.0 to output direction
    P2DIR &= ~BTN;
    P2REN |= BTN;
    P2OUT |= BTN;
    P2IES |= BTN;
    P2IE |= BTN;
    __bis_SR_register(GIE + LPM0);

    while(1){
        P1OUT &= ~LED1;
    }

}

#pragma vector=PORT2_VECTOR
__interrupt void Interrupcao_P2(void)
{
    P1OUT |= LED1;
    while((P2IN&BTN)==0);
    P2IFG &= ~BTN;
}
```
