1.	Quais as diferenças entre os barramentos de dados e de endereços?

O barramento de dados transmite dados entre as unidades. Ou seja, este barramento é utilizado para transmissão entre as unidades funcionais de um microcontrolador, como o CPU, memória RAM, memória ROM e outras. Este tipo de transmissão é bi-direcional, ou seja, transmite em ambas as direções. Por outro lado temos o barramento de endereço que é utilizado para selecionar a origem ou destino dos sinais transmitidos em um dos outros barramentos ou em uma de suas linhas. Funciona para conduzir endereços e uma função típica é selecionar um registrador em um dos dispositivos do sistema que é usado como fonte ou destino dos dados.

2.  Quais são as diferenças entre as memórias RAM e ROM?

A memória RAM é do tipo volátil, ou seja, quando a energia de alimentação for cortada se perde os dados armazenados. Essa memória é do tipo "Acesso de memória aleatória", ou seja, o sistema operacional em que está conectada pode acessa-la a qualquer momento. Por outro lado temos a memória ROM, sendo uma memória não volátil tende a ser mais lenta que a memória RAM devido a funcionalidade de não perder os dados guardados após o corte da energia de alimentação. E a memória ROM é apenas para leitura e não para escrita, sendo os dados gravados pelo fabricante da memória.

3.  Considere o código abaixo:
```C
#include <stdio.h>

int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n"); return 0; }
```

Para este código, responda: (a) A variável i é armazenada na memória RAM ou ROM? Por quê?

É armazenado na memória RAM. Porque neste programa estamos armazenando a variável i naquele instante em uma memória rápida para eficiência no processo. Como é um dado que estamos recebendo após a compilação do programa temos apenas a memória RAM como resposta correta pois a memória ROM não podemos escrever nada na memória ROM após a fabricação, apenas leitura.

(b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?

É armazenado na memória ROM. Este programa precisa armazenar as operações necessárias em uma memória permanente e não necessariamente rápida. Se ocorrer o corte da energia temos a perda do programa compilado. Devido a este fato a memória RAM se torna inviável pois perde os dados com a perda de energia, efeito que não ocorre na memória ROM.

4. Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?

Na arquitetura de Von Neumann a memória de programa e de dados estão concentradas em apenas um ciclo de clock, tornando a operação mais lenta se existir a necessidade de várias operações ao mesmo tempo. Na arquitetura Harvard, baseado na arquitetura de Von Neumann, se distingue pela existência de barramento e ligação ao processador. Ou seja, acesso da memória é separado em relação à memória de programa. E cria a vantagem que a leitura de instruções e de outros tipos de operando pode ser feita no mesmo ciclo de clock em que a execução das operações, tornando mais rápido que a Arquitetura de von Neumann.

5. Considere a variável inteira i, armazenando o valor 0x8051ABCD. Se i é armazenada na memória a partir do endereço 0x0200, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian;

Endereço = Palavra
0x203 = 0x80
0x202 = 0x51
0x201 = 0xAB
0x200 = 0xCD

(b) Big-endian.

Endereço = Palavra
0x203 = 0xCD
0x202 = 0xAB
0x201 = 0x51
0x200 = 0x80

6. Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?

Considerando o uso de variáveis de 32 bits do tipo int temos:

Registro dos 32 bits de ambos os números em 4 registradores, seguindo a regra de 16 bits LSB em um registrador e 16 bits MSB em outro de uma das variáveis.

Soma dos 16 bits LSB da variável A com os 16 bits LSB da variável B e registro em um registrador de 16 bits.

Registro do carry da soma dos menos signativos e adicionamos a soma dos 16 bits MSB de ambas as variáveis.
