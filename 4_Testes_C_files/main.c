
#include "io430.h"

int main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    
    // Disable the GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;                   
    // volatile to prevent optimization                                          
    volatile unsigned int i;            

  	P1DIR = LED1 + LED2;
  	P1OUT = ~(LED1 + LED2);
  	i = 32768;

    while(1) {

        P1OUT = ~(LED1 + LED2);
        do i--;
        while(i != 0) {
	    P1OUT = LED1 + LED2;
	    do i--;
	    while(i != 0) {};
        }
    return 0;
    }
 }
