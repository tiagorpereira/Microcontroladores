#include <msp430fr2433>
#define LED1 BIT0
#define LED2 BIT6
#define BTN BIT2
void main(void)
{
	int count = 0;
	WDTCTL = WDTPW | WDTHOLD;
	PIDIR = LED1 + LED2;
	PIOUT = 0;
	for(;;)
			{
        if(PIOUT & BTN == 0){
          for(count = 0, count < "valor", count++){};
          PIOUT = 0;
          for(count = 0, count < "valor", count++){};
          PIOUT = LED1 + LED2;
          for(count = 0, count < "valor", count++){};
          PIOUT = 0;
          for(count = 0, count < "valor", count++){};
          PIOUT = LED1 + LED2;
        };
			};
}
