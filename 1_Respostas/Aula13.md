### Para todas as questões abaixo, utilize o modo de comparação do Timer A.

## 1. Para os itens abaixo, confira a diferença no brilho do LED.
### (a) Pisque o LED no pino P1.6 (msp430fr2433 é P1.1) numa frequência de 100 Hz e ciclo de trabalho de 25%.

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 = LED1;             // select TA0.1 option - P1.1 LED


    TA0CCR0 = 4999;             // Delay 5ms = 100Hz para ligar e desligar o LED
    TA0CCR1 = 1249;             // 25% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_0 + MC_1;
}
```

### (b) Pisque o LED no pino P1.1 numa frequência de 100 Hz e ciclo de trabalho de 50%.

#include <msp430fr2433.h>

#define LED1 BIT1

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 = LED1;             // select TA0.1 option - P1.1 LED


    TA0CCR0 = 4999;             // Delay 5ms = 100Hz para ligar e desligar o LED
    TA0CCR1 = 2499;             // 50% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_0 + MC_1;
}
```


### (c) Pisque o LED no pino P1.1 numa frequência de 100 Hz e ciclo de trabalho de 75%.

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 |= LED1;             // select TA0.1 option - P1.1 LED


    TA0CCR0 = 4999;             // Delay 5ms = 100Hz para ligar e desligar o LED
    TA0CCR1 = 3749;             // 75% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_0 + MC_1;
}
```

## 2. Pisque o LED no pino P1.1 numa frequência de 1 Hz e ciclo de trabalho de 25%.

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 |= LED1;             // select TA0.1 option - P1.1 LED   

    TA0CCR0 = 64499;            //Delay criado de 0,25seg para ligar/desligar = 0,5Hz
    TA0CCR1 = 16124;            //25% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_3 + MC_1;
}
```

## 3. Pisque o LED no pino P1.1 numa frequência de 1 Hz e ciclo de trabalho de 50%.

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 |= LED1;             // select TA0.1 option - P1.1 LED   

    TA0CCR0 = 64499;            //Delay criado de 0,25seg para ligar/desligar = 0,5Hz
    TA0CCR1 = 32249;             //50% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_3 + MC_1;
}
```

## 4. Pisque o LED no pino P1.1 numa frequência de 1 Hz e ciclo de trabalho de 75%.

```C
#include <msp430fr2433.h>

#define LED1 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    P1OUT &= ~LED1;             // Clear all outputs P1
    P1SEL1 |= LED1;             // select TA0.1 option - P1.1 LED   

    TA0CCR0 = 64499;            //Delay criado de 0,25seg para ligar/desligar = 0,5Hz
    TA0CCR1 = 48374;             //75% of the TA0CCR0 to compare mode
    TA0CCTL1 = OUTMOD_7;        // Set/reset Mode

    TA0CTL = TASSEL_2 + ID_3 + MC_1;
}
```
