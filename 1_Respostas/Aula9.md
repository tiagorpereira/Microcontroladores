## 1. Escreva uma função em C que faz o debounce de botões ligados à porta P1.

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
