## 1. Escreva uma função em C que faz o debounce de botões ligados à porta P2.

Questão reformulada para porta P2 com intuito de teste no MSP430FR2433 pois os pushbuttons instalados então localizados nas portas P2.3 e P2.7

```C
#include <msp430fr2433.h>

#define BTN BIT3 //P2.3
#define LED1 BIT0 //P1.0 - GREEN
#define LED2 BIT1 //P1.1 - RED
#define LEDS LED1 + LED2;

int Debounce(){
    if((P2IN & BTN )== 0)
    {
    	__delay_cycles(22000);
    	if((P2IN & BTN) == 0)
    		return 1;
    }
    return 0;
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	P1DIR |= LEDS;
	P2DIR &= ~BTN;
	P2REN |= BTN;
	P2OUT |= BTN;
	while(1)
	{
        if(Debounce() == 1)
            P1OUT |= LEDS;
        else
            P1OUT &= ~LEDS;
	}
	return 0;
}
```


## 2. Escreva um código em C que lê 9 botões multiplexados por 6 pinos, e pisca os LEDs da placa Launchpad de acordo com os botões. Por exemplo, se o primeiro botão é pressionado, os LEDs piscam uma vez; se o segundo botão é pressionado, os LEDs piscam duas vezes; e assim por diante. Se mais de um botão é pressionado, os LEDs não piscam.



```c
//Testado e pode ser carregado no msp430fr2433

#include <msp430fr2433.h>

#define ROW1 BIT0 //P2.0
#define ROW2 BIT1 //P2.1
#define ROW3 BIT2 //P2.2

//não se usa o P2.3 e P2.7 pois são 2 botões de push instalados no msp430fr2433

#define COL1 BIT4 //P2.4
#define COL2 BIT5 //P2.5
#define COL3 BIT6 //P2.6

#define LED1 BIT0 //P1.0 - REDLED
#define LED2 BIT1 //P1.1 - GREENLED

#define LEDS (LED1|LED2)

void pisca();
void atraso(volatile unsigned int T_u);
int numPos(long unsigned int i, long unsigned int j);

void main(void)
{
    int coord[3][3]; // [ROW][COL]
    long unsigned int i, j;
    int button_press, num;

    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LEDS;
    P2DIR &= ~(ROW1 + ROW2 + ROW3); // seta e zera entradas iniciais para evitar bugs
    P2DIR |= (COL1 + COL2 + COL3);  // saidas para botoes

    P2REN |= (ROW1 + ROW2 + ROW3); // ativa resistores internos nas entradas
    P2OUT |= (ROW1 + ROW2 + ROW3); // seta como resistores do tipo pull-up

    while(1)
    {
        button_press = 0;

        int i,j = 0;

        // 1 estágio: ROWs são entradas, COLs são saídas
        P1DIR |= LEDS;
        P2DIR &= ~(ROW1 + ROW2 + ROW3); // seta e zera entradas iniciais para evitar bugs
        P2DIR |= (COL1 + COL2 + COL3);  // saidas para botoes

        P2REN |= (ROW1 + ROW2 + ROW3); // ativa resistores internos nas entradas
        P2OUT |= (ROW1 + ROW2 + ROW3); // seta como resistores do tipo pull-up
        P2OUT &= ~(COL1 + COL2 + COL3);

        for (i = 1000; i <= 10000; i*= 10)
            if ((P2IN & i) == 0 )
                for (j = 0; j < 3; j++)
                    coord[i][j] = 1;

        // 2 estágio: ROWs são saídas, COLs são entradas
        P2DIR |= (ROW1 + ROW2 + ROW3);  // saidas para botoes
        P2DIR &= ~(COL1 + COL2 + COL3); // seta e zera entradas iniciais para evitar bugs

        P2REN |= (COL1 + COL2 + COL3); // ativa resistores internos nas entradas
        P2OUT |= (COL1 + COL2 + COL3); // seta como resistores do tipo pull-up
        P2OUT &= ~(ROW1 + ROW2 + ROW3);

        for (i = 100000; i <= 10000000; i*= 10)
            if ((P2IN & i) == 0)
                for (j = 0; j < 3; j++)
                    coord[j][i] = 1;

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if(coord[i][j] == 2)
                    button_press++;
                              num = coord[i][j] == 2 ? numPos(i,j) : num;
            }
        }
        if (button_press == 1)
            for(i=0; i < num; i++)
                pisca();
    }
}

// Função para piscar os LEDS vermelho e verde.
void pisca()
{
    P1OUT |= LEDS;
  atraso(1000);
    P1OUT &= ~LEDS;
}

// Função atraso timer
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

// Retorna pos do botão pressionado
int numPos(long unsigned int i, long unsigned int j)
{
    return (int) 3*j+i+1;
}
```
