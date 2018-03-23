## 1. Dada uma variável `a` do tipo `char` (um byte), escreva os trechos de código em C para:
### (a) Somente setar o bit menos significativo de `a`.

	#include <stdio.h>

	int main(void){
	char a;
	a |= 0x01;
	}

### (b) Somente setar dois bits de `a`: o menos significativo e o segundo menos significativo.

	#include <stdio.h>
	int main(void){
		char a;
		a |= 0x03;
	}

### (c) Somente zerar o terceiro bit menos significativo de `a`.

	#include <stdio.h>
	int main(void){
		char a;
		a &= 0x04; // 0x04 = (0000 0100);
	}

### (d) Somente zerar o terceiro e o quarto bits menos significativo de `a`.

	#include <stdio.h>
	int main(void){
		char a;
		a &= 0x0B; //0x0B = (0000 1100)
	}

### (e) Somente inverter o bit mais significativo de `a`.

	#include <stdio.h>
	int main(void){
		char a;
		a ^= 0x80;
	}

### (f) Inverter o nibble mais significativo de `a`, e setar o nibble menos significativo de `a`.

	#include <stdio.h>
	int main(void){
		char a;
		a ^= 0xF0;
		a |= 0x0F;
	}

## 2. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar os dois LEDs ininterruptamente.

	#include <msp430fr2433>
	#define LED1 BIT0
	#define LED2 BIT6

	void main(void)
	{
		int count = 0;
		WDTCTL = WDTPW | WDTHOLD;
		PIDIR = LED1 + LED2;
		PIOUT = 0;
		for(;;)
				{
					PIOUT ^= (LED1 + LED2);
					for(count = 0, count < "valor", count++){
					}

				}


	}



## 3. Considerando a placa Launchpad do MSP430, escreva o código em C para piscar duas vezes os dois LEDs sempre que o usuário pressionar o botão.

	#include <msp430fr2433>
	#define LED1 BIT0
	#define LED2 BIT6
	#define BTN BIT2
	void main(void)
	{
		WDTCTL = WDTPW | WDTHOLD;
		P1DIR = LED1 + LED2;
		P1OUT = ~(LED1 + LED2);
		P2DIR |= BTN;
		P2OUT |= BTN;  |  

		while(1);
			{
				if ((P1DIR&BTN)==0)
					P1OUT = (LED1 + LED2) + BTN;
				else
					P1OUT = ~(LED1 + LED2);
			}
	}

## 4. Considerando a placa Launchpad do MSP430, faça uma função em C que pisca os dois LEDs uma vez.

	#include <msp430fr2433>
	#define LED1 BIT0
	#define LED2 BIT6

	void main(void)
	{
		int count = 0;
		WDTCTL = WDTPW | WDTHOLD;
		PIDIR = LED1 + LED2;
		PIOUT = 0;
		for(;;)
				{
					int i;
					if(i = 0, int < 2, int++){
						PIOUT ^= (LED1 + LED2);
						for(count = 0, count < "valor", count++){}

					}
				}
	}


## 5. Reescreva o código da questão 2 usando a função da questão 4.

## 6. Reescreva o código da questão 3 usando a função da questão 4.
