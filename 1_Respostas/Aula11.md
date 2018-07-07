## 1. Defina a função `void Atraso(volatile unsigned int x);` que fornece um atraso de `x` milissegundos. Utilize o Timer_A para a contagem de tempo, e assuma que o SMCLK já foi configurado para funcionar a 1 MHz. Esta função poderá ser utilizada diretamente nas outras questões desta prova.

```C
#include <msp430fr2433.h>

CSCTL1 = 0xF1;       //MCLK e SMCLK @ 1MHz
CSCTL0 = 0x00;       //MCLK e SMCLK @ 1MHz
WDTCTL = WDTPW + WDTHOLD; // Stop WDT
PM5CTL0 &= ~LOCKLPM5;

void atraso(volatile unsigned int T_u)
{
    TA1CCR0 = 999;
    TA1CTL = TACLR;
    TA1CTL = TASSEL_2 + ID_0 + MC_1;
    while(T_u>0)
    {
        while((TA1CTL&TAIFG)==0);
        T_u--;
        TA1CTL &= ~TAIFG;
    }
    TA1CTL = MC_0;
}
```

## 2. Pisque os LEDs da Launchpad numa frequência de 100 Hz.

```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1) {
        P1OUT ^= LED1;          // Toggle P1.0 using exclusive-OR
        atraso(5);             // Delay 10ms = 100hz para acender e desligar

    }
}

void atraso(volatile unsigned int T_u)
{
    TA0CCR0 = 999;
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    while(T_u>0)
    {
        while((TA0CTL&TAIFG)==0);
        T_u--;
        TA0CTL &= ~TAIFG;
    }
    TA0CTL = MC_0;
}
```

## 3. Pisque os LEDs da Launchpad numa frequência de 20 Hz.

```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1) {
        P1OUT ^= LED1;          // Toggle P1.0 using exclusive-OR
        atraso(25);             // Delay 25ms = 20hz para acender e desligar

    }
}

void atraso(volatile unsigned int T_u)
{
    TA0CCR0 = 999;
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    while(T_u>0)
    {
        while((TA0CTL&TAIFG)==0);
        T_u--;
        TA0CTL &= ~TAIFG;
    }
    TA0CTL = MC_0;
}
```


## 4. Pisque os LEDs da Launchpad numa frequência de 1 Hz.
```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1) {
        P1OUT ^= LED1;          // Toggle P1.0 using exclusive-OR
        atraso(500);             // Delay 1000ms = 1hz

    }
}

void atraso(volatile unsigned int T_u)
{
    TA0CCR0 = 999;
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    while(T_u>0)
    {
        while((TA0CTL&TAIFG)==0);
        T_u--;
        TA0CTL &= ~TAIFG;
    }
    TA0CTL = MC_0;
}
```

## 5. Pisque os LEDs da Launchpad numa frequência de 0,5 Hz.
```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    while(1) {
        P1OUT ^= LED1;          // Toggle P1.0 using exclusive-OR
        atraso(1000);             // Delay 1000ms = 0,5hz para acender e desligar

    }
}

void atraso(volatile unsigned int T_u)
{
    TA0CCR0 = 999;
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + ID_0 + MC_1;
    while(T_u>0)
    {
        while((TA0CTL&TAIFG)==0);
        T_u--;
        TA0CTL &= ~TAIFG;
    }
    TA0CTL = MC_0;
}
```
## 6. Repita as questões 2 a 5 usando a interrupção do Timer A para acender ou apagar os LEDs.

### Para 100Hz

```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction
    TA0CCR0 = 4999;             // Delay 5ms = 100Hz para ligar e desligar o LED
    TA0CTL = TASSEL_2 + ID_0 + MC_1 + TAIE;

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM0 w/ interrupts
    __no_operation();                             // For debug
}

//TimerA0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= LED1;
    TA0CTL &= ~TAIFG;
}
```

### Para 20Hz
```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;               // Set P1.0 to output direction
    TA0CCR0 = 24999;             // Delay 25ms = 20Hz para ligar e desligar o LED
    TA0CTL = TASSEL_2 + ID_0 + MC_1 + TAIE;

    __bis_SR_register(LPM0_bits | GIE);  // Enter LPM0 w/ interrupts
    __no_operation();                    // For debug
}

//TimerA0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= LED1;
    TA0CTL &= ~TAIFG;
}
```

### Para 1Hz
```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    //Delay criado de 0,5seg para ligar/desligar = 1Hz
    TA0CCR0 = 64499;     
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM0 w/ interrupts
    __no_operation();                             // For debug
}

//TimerA0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= LED1;
    TA0CTL &= ~TAIFG;
}
```

### Para 0,5Hz
```C
#include <msp430fr2433.h>

#define LED1 BIT0

void atraso(volatile unsigned int T_u);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    CSCTL1 = 0xF1;              //MCLK e SMCLK @ 1MHz
    CSCTL0 = 0x00;              //MCLK e SMCLK @ 1MHz
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED1;              // Set P1.0 to output direction

    //Delay criado de 0,25seg para ligar/desligar = 0,5Hz
    TA0CCR0 = 64499;     
    TA0CTL = TASSEL_2 + ID_3 + MC_3 + TAIE; //modo up/down (metade que o modo up)

    __bis_SR_register(LPM0_bits | GIE);           // Enter LPM0 w/ interrupts
    __no_operation();                             // For debug
}

//TimerA0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A0(void)
{
    P1OUT ^= LED1;
    TA0CTL &= ~TAIFG;
}
```


## 7. Defina a função `void paralelo_para_serial(void);` que lê o byte de entrada via porta P1 e transmite os bits serialmente via pino P2.0. Comece com um bit em nivel alto, depois os bits na ordem P1.0 - P1.1 - … - P1.7 e termine com um bit em nível baixo. Considere um período de 1 ms entre os bits.

```C
#define SaidaSerial P2OUT
#define EntParalela P1IN

void paralelo_para_serial(void)
{

  P2DIR |= BIT0; //Configura como saída serial

	char seq[] = {BIT0, BIT1, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};

	SaidaSerial |= BIT0;
	for(int i = 0; i < 8; i++)
	{
		if((EntParalela & seq[i]) == 1)
      P1DIR &= ~seq[i]; //Configura como entrada no P1
			SaidaSerial |= BIT0;
		else
			SaidaSerial &= ~BIT0;
		atraso(1);
	}
	SaidaSerial &= ~BIT0;
}
```


## 8. Faça o programa completo que lê um byte de entrada serialmente via pino P2.0 e transmite este byte via porta P1. O sinal serial começa com um bit em nivel alto, depois os bits na ordem 0-7 e termina com um bit em nível baixo. Os pinos P1.0-P1.7 deverão corresponder aos bits 0-7, respectivamente. Considere um período de 1 ms entre os bits.

```C
#define SaidaParalela P1OUT
#define EntSerial P2IN

void serial_para_paralelo(void)
{

  P2DIR |= ~BIT0; //Configura como entrada serial

	char seq[] = {BIT0, BIT1, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};

	while((EntSerial & BIT0) == 0);
	atraso();
	for(int i = 0; i < 8; i++)
	{
		if((EntSerial & seq[i]) == 1)
      P1DIR |= seq[i]; //Configura como saída no P1
			SaidaParalela |= seq[i];
		else
			SaidaParalela &= ~seq[i];
		atraso(1);
	}
	while((EntSerial & BIT0) == 1);
}
```


## 9. Defina a função `void ConfigPWM(volatile unsigned int freqs, volatile unsigned char ciclo_de_trabalho);` para configurar e ligar o Timer_A em modo de comparação. Considere que o pino P1.6 já foi anteriormente configurado como saída do canal 1 de comparação do Timer_A, que somente os valores {100, 200, 300, …, 1000} Hz são válidos para a frequência, que somente os valores {0, 25, 50, 75, 100} % são válidos para o ciclo de trabalho, e que o sinal de clock SMCLK do MSP430 está operando a 1 MHz.

```c
void ConfigPWM(volatile unsigned int freqs, volatile unsigned char ciclo_de_trabalho)
{
  unsigned volatile int T;

  //Calcula o período da frequência no limite de frequência imposto
  if ((freqs/100 < 11) && (freqs % 100 = 0)) T = 50000/freqs;

  //Configura o timer A0 máximo para comparação no upmode
  TA0CCR0 = T-1;

  //Configura o canal 1 de comparação do timer A0
  unsigned volatile char T1;

  if ((ciclo_de_trabalho/25 < 5) && (ciclo_de_trabalho % 25 = 0)) T1 = ciclo_de_trabalho*T/100;

  TA0CCR1 = T1-1;
  TA0CCTL1 = OUTMOD_7; //Modo reset/set

  //Configuração do timer A0 como upmode
  TA0CTL = TASSEL_2 + ID_0 + MC_1;
}
```
