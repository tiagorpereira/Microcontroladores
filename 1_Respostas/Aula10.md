## 1. Projete o hardware necessário para o MSP430 controlar um motor DC de 12V e 4A. Utilize transistores bipolares de junção (TBJ) com Vbe = 0,7 V, beta = 100 e Vce(saturação) = 0,2 V. Além disso, considere que Vcc = 3 V para o MSP430, e que este não pode fornecer mais do que 10 mA por porta digital.

Ib = Ic/beta => Ib = 4/100 = 40mA. Como para o MSP430 não fornece mais que 10mA para cada porta digital será necessário no mínimo 4 transistores bipolares.

Ib = Ic/4*beta => Ib = 4/400 = 10mA.

Rb = (Vcc-Vbe) * 4*beta/Ic
Rb = (3 - 0,7) * 400/4 = 230 Ohms como a resistencia interna para cada transistor

Será necessário utilizar uma interface abaixadora de tensão 12v/3v

Vin = 3V (Voltagem de entrada no MSP)
Vo = 12V (Voltagem de entrada no motor DC)

Vin/Vo = 3/12 = R2/(R1+R2) => R2 = 0.33 R1. Ou seja R1 = 10kOhm e R2 = 3.33 kOhms



## 2. Projete o hardware necessário para o MSP430 controlar um motor DC de 10V e 1A. Utilize transistores bipolares de junção (TBJ) com Vbe = 0,7 V e beta = 120. Além disso, considere que Vcc = 3,5 V para o MSP430, e que este não pode fornecer mais do que 10 mA por porta digital.

Ib = Ic/beta => Ib = 1/120 = 8,33mA. Portanto 1 transistor bipolar diminui a corrente necessária para menos de 10mA (suportado pelo MSP).

Rb = (Vcc-Vbe) * beta/Ic
Rb = (3,5 - 0,7) * 120/1 = 336 Ohms como a resistencia interna para cada transistor

Será necessário utilizar uma interface abaixadora de tensão 10v/3,5v

Vin = 3,5V (Voltagem de entrada no MSP)
Vo = 10V (Voltagem de entrada no motor DC)

Vin/Vo = 3,5/10 = R2/(R1+R2) => R2 =  0,53 R1. Ou seja R1 = 10kOhm e R2 = 5,3 kOhms

## 3. Projete o hardware utilizado para controlar 6 LEDs utilizando charlieplexing. Apresente os pinos utilizados no MSP430 e os LEDs, nomeados L1-L6.

Charlieplexing => Com N pinos controla-se N * (N-1) LEDs.

N * (N-1) = 6 => N**2 - N - 6 = 0 => N = 3.

```      
         C1           C2           C3
         |            |--L1        |--L2
         |            |   |        |   |
R1 -----------------------------------------
         |            |            |
         |--L3        |            |--L4
         |   |        |            |   |
R2 -----------------------------------------
         |            |            |
         |--L5        |--L6        |
         |   |        |   |        |
R3 -----------------------------------------
```


## 4. Defina a função `void main(void){}` para controlar 6 LEDs de uma árvore de natal usando o hardware da questão anterior. Acenda os LEDs de forma que um ser humano veja todos acesos ao mesmo tempo.

```C
#include <msp430fr2433>
#define CPLX0 BIT0
#define CPLX1 BIT1
#define CPLX2 BIT2

void LEDS(void){

  WDTCTL = WDTPW | WDTHOLD; \\Desliga watchdog timer

  BCSCTL1 = CALBC1_1MHZ; \\Seta uma frequência de 1Mhz para o ACLK e SMCLK
  DCOCTL = CALDCO_1MHZ;

\\Liga os leds L1 E L2
  P1DIR = (P1DIR&(~CPLX2)) | (CPLX0 + CPLX1);
  P1OUT = (P1OUT|CPLX0) & (~CPLX1);
  P1OUT = (P1OUT|CPLX0) & (~CPLX1);

\\Liga od leds L3 E L4
  P1DIR = (P1DIR&(~CPLX0)) | (CPLX1 + CPLX2);
  P1OUT = (P1OUT|CPLX1) & (~CPLX2);
  P1OUT = (P1OUT|CPLX2) & (~CPLX1);

\\Liga os leds L5 e L6
  P1DIR = (P1DIR&(~CPLX1)) | (CPLX0 + CPLX2);
  P1OUT = (P1OUT|CPLX0) & (~CPLX2);
  P1OUT = (P1OUT|CPLX2) & (~CPLX0);

}
```

## 5. Defina a função `void main(void){}` para controlar 6 LEDs de uma árvore de natal usando o hardware da questão 3. Acenda os LEDs de forma que um ser humano veja os LEDs L1 e L2 acesos juntos por um tempo, depois os LEDs L3 e L4 juntos, e depois os LEDs L5 e L6 juntos.

  ```C
  #include <msp430fr2433>
  #define CPLX0 BIT0
  #define CPLX1 BIT1
  #define CPLX2 BIT2

  void LEDS(void){

    WDTCTL = WDTPW | WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ; \\Seta uma frequência de 1Mhz para o ACLK
    DCOCTL = CALDCO_1MHZ;

    P1DIR = (P1DIR&(~CPLX2)) | (CPLX0 + CPLX1);
    for (i=30000; i>0; i--)
    {
      P1OUT = (P1OUT|CPLX0) & (~CPLX1);
      P1OUT = (P1OUT|CPLX0) & (~CPLX1);
    }

    P1DIR = (P1DIR&(~CPLX0)) | (CPLX1 + CPLX2);
    for (i=30000; i>0; i--)
    {
      P1OUT = (P1OUT|CPLX1) & (~CPLX2);
      P1OUT = (P1OUT|CPLX2) & (~CPLX1);
    }

    P1DIR = (P1DIR&(~CPLX1)) | (CPLX0 + CPLX2);
    for (i=30000; i>0; i--)
    {
      P1OUT = (P1OUT|CPLX0) & (~CPLX2);
      P1OUT = (P1OUT|CPLX2) & (~CPLX0);
    }

  }
  ```

## 6. Defina a função `void EscreveDigito(volatile char dig);` que escreve um dos dígitos 0x0-0xF em um único display de 7 segmentos via porta P1, baseado na figura abaixo. Considere que em outra parte do código os pinos P1.0-P1.6 já foram configurados para corresponderem aos LEDs A-G, e que estes LEDs possuem resistores externos para limitar a corrente.

```
        ---  ==> A
       |   |
 F <== |   | ==> B
       |   |
        ---  ==> G
       |   |
 E <== |   | ==> C
       |   |
        ---  ==> D
```

```C
  #include <msp430fr2433>
  #define SEG_A BIT0
  #define SEG_B BIT1
  #define SEG_C BIT2
  #define SEG_D BIT3
  #define SEG_E BIT4
  #define SEG_F BIT5
  #define SEG_G BIT6

  #define ZERO   (OITO - SEG_G)
  #define UM     (SEG_B + SEG_C)
  #define DOIS   (OITO - SEG_F - SEG_C)
  #define TRES   (OITO - SEG_F - SEG_E)
  #define QUATRO (OITO - SEG_A - SEG_E - SEG_D)
  #define CINCO  (OITO - SEG_B - SEG_E)
  #define SEIS   (OITO - SEG_B)
  #define SETE   (TRES - SEG_D)
  #define OITO   (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
  #define NOVE   (OITO - SEG_E - SEG_D)
  #define DEZ    (OITO - SEG_D)
  #define ONZE   (OITO - SEG_A - SEG_B)
  #define DOZE   (SEIS - SEG_F - SEG_C)
  #define TREZE  (OITO - SEG_A - SEG_F)
  #define QUAT   (OITO - SEG_B - SEG_C)
  #define QUINZE (OITO - SEG_B - SEG_C - SEG_D)

void EscreveDigito(volatile char dig){

  P1DIR |= OITO;

  volatile char num[] = {ZERO, UM, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO,
                          DEZ, ONZE, DOZE, TREZE, QUAT, QUINZE};

  if (dig > 0x0F)
  {
    P1OUT |= num[0];
  }
  else
  {
    P1OUT |= num[dig];
  }

}

```


## 7. Multiplexe 2 displays de 7 segmentos para apresentar a seguinte sequência em loop:
```
00 - 11 - 22 - 33 - 44 - 55 - 66 - 77 - 88 - 99 - AA - BB - CC - DD - EE - FF
```

```C
  #include <msp430fr2433>

  #define DSP_1 BIT0
  #define DSP_2 BIT1

  #define SEG_A BIT0
  #define SEG_B BIT1
  #define SEG_C BIT2
  #define SEG_D BIT3
  #define SEG_E BIT4
  #define SEG_F BIT5
  #define SEG_G BIT6

  #define ZERO   (OITO - SEG_G)
  #define UM     (SEG_B + SEG_C)
  #define DOIS   (OITO - SEG_F - SEG_C)
  #define TRES   (OITO - SEG_F - SEG_E)
  #define QUATRO (OITO - SEG_A - SEG_E - SEG_D)
  #define CINCO  (OITO - SEG_B - SEG_E)
  #define SEIS   (OITO - SEG_B)
  #define SETE   (TRES - SEG_D)
  #define OITO   (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
  #define NOVE   (OITO - SEG_E - SEG_D)
  #define DEZ    (OITO - SEG_D)
  #define ONZE   (OITO - SEG_A - SEG_B)
  #define DOZE   (SEIS - SEG_F - SEG_C)
  #define TREZE  (OITO - SEG_A - SEG_F)
  #define QUAT   (OITO - SEG_B - SEG_C)
  #define QUINZE (OITO - SEG_B - SEG_C - SEG_D)


void main(void){

  WDTCTL = WDTPW | WDTHOLD;

  BCSCTL1 = CALBC1_1MHZ; \\Seta uma frequência de 1Mhz para o ACLK
  DCOCTL = CALDCO_1MHZ;

  P1DIR |= DSP_1 + DSP2;
  P2DIR |= OITO;

  volatile char j, i;
  volatile char num[] = {ZERO, UM, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO,
                          DEZ, ONZE, DOZE, TREZE, QUAT, QUINZE};

 for (i = 0; i < 16; i++)
 {
   for (j=0, j<2, j++)
   {
     P2OUT |= num[i];
     P1OUT = (P1OUT|DSP_1)& (~DSP_2);
     P1OUT = (P1OUT|DSP_2)& (~DSP_1);
   }
 }


}

```
