#include <msp430fr2433.h>
#include <stdio.h>
#include <stdlib.h>

//P1.x
#define TrigPin1 BIT7
#define EchoPin1 BIT6

//P2.x
#define TrigPin2 BIT5
#define EchoPin2 BIT6

//P1.1
#define PORTA1 BIT1

//P1.2
#define PORTA2 BIT2

//P1.4
#define PORTA3 BIT4

//Ultrasensors
int miliseconds1, miliseconds2;
int distance1, distance2;
long sensor1, sensor2;

//Force Sensor
unsigned int ADC_Result;
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3220.0; // Measured resistance of 3.3k resistor



//Functions
void atraso(volatile unsigned int T_u);
void servo1(volatile int graus);
void servo1(volatile int graus);
void StopServo();
void movimento(volatile int graus);
void movimento90(volatile int graus);
void initUart();
void sendData(unsigned char c);
void sendInt(unsigned int n);
void sendString(char str[]);
void sendFloat(float f);
void Init_servos();
void Init_UltraSensors();
void Init_ForceSensor();
void ForceSensorMeasure(unsigned int ADC_Result);

void main(void)


{
  CSCTL1 = 0xF1;      //MCLK e SMCLK @ 1MHz
  CSCTL0 = 0x00;       //MCLK e SMCLK @ 1MHz
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT]
  PM5CTL0 &= ~LOCKLPM5;

  TA2CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA3CCTL0 = CCIE;
  TA2CCR0 = 1000;                  // 1ms at 1mhz
  TA3CCR0 = 1000;
  TA2CTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
  TA3CTL = TASSEL_2 + MC_1;

  P1IFG  = 0x00;                //clear all interrupt flags
  P2IFG  = 0x00;
  P1DIR |= 0x01;                            // P1.0 as output for LED
  P1OUT &= ~0x01;                           // turn LED off

  //Configure Force Sensor
  Init_ForceSensor();


  _BIS_SR(GIE);                         // global interrupt enable

  volatile int fechado = 0;
  while(1)
  {
      ADCCTL0 |= ADCENC | ADCSC;       // Sampling and conversion start
      __bis_SR_register(GIE);          //ADC_ISR will force exit

      //Configure Serial UART
      initUart();

      ForceSensorMeasure(ADC_Result);
      Init_UltraSensors();
      atraso(1000);
      if(fechado == 0){ //Mao aberta
          if(distance1<= 7 && distance2 <= 4)
          {
              P1OUT |= 0x01;
              movimento(110);
              movimento90(70);
              atraso(2000); //2seg
              P1OUT &= ~0x01;
              fechado = 1;
          }
          else if(distance1 > 7 && distance2 > 4){
              StopServo();
          }
      }else{ //Mao fechada
          if(distance1<= 7 && distance2 <= 4){

            P1OUT |= 0x01;
            movimento(0);
            movimento90(0);
            atraso(2000);  //2seg
            P1OUT &= ~0x01;
            fechado = 0;
          }
          else if(distance1 > 7 && distance2 > 4){
              movimento(110);
              movimento90(70);
          }
      }
  }
}

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


void servo1(volatile int graus){
    if(graus <= 180 && graus >= 0)
        TA0CCR1 = 730 + 12*graus;
}

void servo2(volatile int graus){
    if(graus <= 180 && graus >= 0)
        TA0CCR2 = 730 + 12*graus;
}

void StopServo(){
    TA0CTL = MC_0;
  //  TA1CTL = MC_0;
}



volatile int posAnt=0;
void movimento(volatile int graus){
    volatile int i;
    Init_servos();
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + MC_1;                // SMCLK, up mode
 //   TA1CTL = TACLR;
 //   TA1CTL = TASSEL_3 + MC_1;
    if(graus <= 180 && graus >= 0){
        if(posAnt > graus){
            for(i=posAnt;i >= graus; i=i-10){
                servo1(i);
                atraso(90);
            }
        }else
            if(posAnt < graus){
                for(i=posAnt;i <= graus; i=i+10){
                    servo1(i);
                    atraso(90);
                }
            }
            posAnt = graus;
    }
  //   StopServo();
}

volatile int posAnt1=0;
void movimento90(volatile int graus){
    volatile int i;
    Init_servos();
    TA0CTL = TACLR;
    TA0CTL = TASSEL_2 + MC_1;                // SMCLK, up mode
 //   TA1CTL = TACLR;
 //   TA1CTL = TASSEL_3 + MC_1;
    if(graus <= 180 && graus >= 0){
        if(posAnt1 > graus){
            for(i=posAnt1;i >= graus; i=i-10){
                servo2(i);
                atraso(90);
            }
        }else
            if(posAnt1 < graus){
                for(i=posAnt1;i <= graus; i=i+10){
                    servo2(i);
                    atraso(90);
                }
            }
            posAnt1 = graus;
    }
//    StopServo();
}

void initUart() // 9600 Baudrate
{
    // Configure UART
    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    // Baud Rate calculation
    UCA0BR0 = 6;
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x20 | UCOS16 | UCBRF_8;

    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA0IE |= UCRXIE;                // Enable USCI_A0 RX interrupt

    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function
}

void Init_servos(){
    P1DIR |= PORTA1 + PORTA2 /*+ PORTA3*/;                          // P1.6/TA0.1 is used for PWM, thus also an output -> servo 1

    P1OUT &= ~(PORTA1 + PORTA2 /*+ PORTA3*/);                              // Clear all outputs P1
    P1SEL1 |= PORTA1 + PORTA2 /*+ PORTA3*/;                          // P1.6 select TA0.1 option
    // if SMCLK is about 1MHz (or 1000000Hz),
    // and 1000ms are the equivalent of 1 Hz,
    // then, by setting CCR0 to 20000 (1000000 / 1000 * 20)
    // we get a period of 20ms
    TA0CCR0 = 20000-1;                           // PWM Period TA0.1
//    TA1CCR0 = 20000-1;
    // setting 1500 is 1.5ms is 0deg. servo pos
    TA0CCR1 = 00;                            // CCR1 PWM duty cycle
    TA0CCR2 = 00;
//    TA1CCR2 = 00;
    TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set
    TA0CCTL2 = OUTMOD_7;
//    TA1CCTL2 = OUTMOD_7;
}

void Init_UltraSensors(){
//    __bis_SR_register(LPM0_bits | GIE);

    P1SEL0 &= 0x00;
    P1SEL1 &= 0x00;
    P1IE &= ~0x01;          // disable interupt
    P2IE &= ~0x01;          // disable interupt
    P1DIR |= TrigPin1;          // trigger pin as output
    P2DIR |= TrigPin2;          // trigger pin as output
    P1OUT |= TrigPin1;          // generate pulse
    P2OUT |= TrigPin2;          // generate pulse
    __delay_cycles(10);             // for 10us
    P1OUT &= ~TrigPin1;                 // stop pulse
    P2OUT &= ~TrigPin2;                 // stop pulse
    P1DIR &= ~EchoPin1;         // make pin P1.x input (ECHO)
    P2DIR &= ~EchoPin2;         // make pin P2.x input (ECHO)

    P1IFG = 0x00;                   // clear flag just in case anything happened before
    P2IFG = 0x00;                   // clear flag just in case anything happened before
    P1IE |= EchoPin1;           // enable interupt on ECHO pin
    P2IE |= EchoPin2;           // enable interupt on ECHO pin
    P1IES &= ~EchoPin1;         // rising edge on ECHO pin
    P2IES &= ~EchoPin2;         // rising edge on ECHO pin

    atraso(30);          // delay for 30ms (after this time echo times out if there is no object detected)
    distance1 = sensor1/74;           // converting ECHO lenght into cm
    distance2 = sensor2/66;           // converting ECHO lenght into cm
}

void Init_ForceSensor(){
    // Configure ADC A3 pin
    SYSCFG2 |= ADCPCTL3;

    // Configure ADC10
    ADCCTL0 |= ADCSHT_4 | ADCON;                             // ADCON, S&H=16 ADC clks
    ADCCTL1 |= ADCSHS_0 | ADCSHP | ADCSSEL_0;                // ADCCLK = MODOSC; sampling timer
    ADCCTL2 |= ADCRES;                                       // 10-bit conversion results
    ADCMCTL0 |= ADCINCH_3 | ADCSREF_0;                       // A3 ADC input select; Vref=AVCC
    ADCIE |= ADCIE0;                                         // Enable ADC conv complete interrupt
}

void ForceSensorMeasure(unsigned int ADC_Result){
    if (ADC_Result != 0) // If the analog reading is non-zero
    {


 /*     sendString("\n Resultado ADC: ");
      sendInt(ADC_Result);
      sendString("\n");
  */
      // Use ADC reading to calculate voltage:
      float fsrV = ADC_Result * VCC / 1023.0;
      // Use voltage and static resistor value to
      // calculate FSR resistance:
      float fsrR = R_DIV * (VCC / fsrV - 1.0);
      // Guesstimate force based on slopes in figure 3 of
      // FSR datasheet:

      sendString("\b Resistência: ");
      sendFloat(fsrR);
      sendString(" ohms\n");

      float force;
      float fsrG = 1.0 / fsrR; // Calculate conductance
      // Break parabolic curve down into two linear slopes:
      if (fsrR <= 600)
        force = (fsrG - 0.00075) / 0.00000032639;
      else
        force =  fsrG / 0.000000642857;

      sendString("Força - float: ");
      sendFloat(force);
      sendString(" g\n");
      sendString("Força - int: ");
      sendInt((unsigned int)force);
      sendString(" g\n");

      char str[12];
      sprintf(str, "%d", (int)force);
      sendString("Força - String:");
      sendString(str);
      sendString(" g\n");

      __delay_cycles(5000);
    }
    else
    {
    }
}


void sendData(unsigned char c)
{
    while(!(UCA0IFG&UCTXIFG));
    UCA0TXBUF = c;
}

void sendInt(unsigned int n)
{
    int num[] = {10000,1000,100,10,1};
    int pos, posI = 0, cnt, i;

    if(n==0)
        sendData('0');
    else
    {
        for (i = 4; i >= 0; i--)
            posI = n >= num[i] ? i : posI;

        for (pos = posI; pos < 5; pos++)
        {
          cnt = 0;
          while (n >= num[pos]) {
            cnt++;
            n -= num[pos];
          }
          sendData(cnt+'0');
        }
    }
}

void sendString(char str[])
{
    unsigned int i;
    for(i=0; str[i]!= '\0'; i++)
        sendData(str[i]);
}

void sendFloat(float f)
{
    int fInteger, fIntegerFract;
    float fFract;

    if(f < 0)
    {
        sendData('-');
        f = -1*f;
    }

    fInteger = (int) f;
    fFract = f -fInteger;
    fFract = 100*fFract;
    fIntegerFract = (int) fFract;
    sendInt((unsigned int) fInteger);
    sendData('.');
    sendInt((unsigned int) fIntegerFract);
}





//P1 interrupt for Ultrasensor 1 distance calculation
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG&EchoPin1)  //is there interrupt pending?
        {
          if(!(P1IES&EchoPin1)) // is this the rising edge?
          {

     //       __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            TA2CTL|=TACLR;   // clears timer A
            miliseconds1 = 0;
            P1IES |= EchoPin1;  //falling edge
          }
          else
          {

    //        __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            sensor1 = (long)miliseconds1*1000 + (long)TA2R;    //calculating ECHO lenght

          }
    P1IFG &= ~EchoPin1;             //clear flag
    }
}

//P2 interrupt for Ultrasensor 2 distance calculation
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if(P2IFG&EchoPin2)  //is there interrupt pending?
        {
          if(!(P2IES&EchoPin2)) // is this the rising edge?
          {

     //       __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            TA3CTL|=TACLR;   // clears timer A
            miliseconds2 = 0;
            P2IES |= EchoPin2;  //falling edge
          }
          else
          {

    //        __bic_SR_register_on_exit(LPM0_bits);            // Clear CPUOFF bit from LPM0
            sensor2 = (long)miliseconds2*1000 + (long)TA3R;    //calculating ECHO lenght

          }
    P2IFG &= ~EchoPin2;             //clear flag
    }
}

//TimerA2 interrupt service routine
#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer_A0(void)
{
  miliseconds1++;
}

// TimerA3 interrupt service routine
#pragma vector=TIMER3_A0_VECTOR
__interrupt void Timer_A1(void)
{
  miliseconds2++;
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:
            break;
        case ADCIV_ADCLOIFG:
            break;
        case ADCIV_ADCINIFG:
            break;
        case ADCIV_ADCIFG:
            ADC_Result = ADCMEM0;
            break;
        default:
            break;
    }
}

// UART interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA0IFG&UCTXIFG));
      UCA0TXBUF = UCA0RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}

