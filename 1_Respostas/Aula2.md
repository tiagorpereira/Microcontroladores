1.  Quais as diferenças entre os barramentos de dados e de endereços?




2.  Quais são as diferenças entre as memórias RAM e ROM?
	A memória RAM é do tipo volátil, ou seja, quando a energia de alimentação for cortada se perde os dados armazenados. Essa memória é do tipo "Acesso de memória aleatória", ou seja, o sistema operacional em que está conectada pode acessa-la a qualquer momento. Por outro lado temos a memória ROM, sendo uma memória não volátil tende a ser mais lenta que a memória RAM devido a funcionalidade de não perder os dados guardados após o corte da energia de alimentação.



3.  Considere o código abaixo:

#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}

Para este código, responda: (a) A variável i é armazenada na memória RAM ou ROM? Por quê? (b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?

4.  Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?

	Na arquitetura de Von Neumann a memória de programa e de dados estão concentradas em apenas uma. 

5.  Considere a variável inteira i, armazenando o valor 0x8051ABCD. Se i é armazenada na memória a partir do endereço 0x0200, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian; (b) Big-endian.

6.  Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?
