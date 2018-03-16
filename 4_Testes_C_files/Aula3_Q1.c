#include <msp430.h>
#define LED1 BIT0
#define LED2 BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    volatile unsigned int i;            // volatile to prevent optimization

  	P1DIR = LED1 + LED2;
  	P1OUT = ~(LED1 + LED2);
  	i = 32768;

    while(1) {

        P1OUT = ~(LED1 + LED2);
        do i--;
        while(i != 0);
	    P1OUT = LED1 + LED2;
	    do i--;
	    while(i != 0);
    };
}
