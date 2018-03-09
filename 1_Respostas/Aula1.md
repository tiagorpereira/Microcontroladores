1. O que são sistemas embarcados?

	Os sistemas embarcados são sistemas computacionais destinados a funcionalidades específicas e limitadas. Diferentemente dos sistemas gerais estes são projetados para atender um conjunto específico de requisitos e realizam determinadas funções condizentes com tais.

2. O que são sistemas microprocessados?

	Os sistemas microprocessados são sistemas eletrônicos constituídos de microcontroladores. Estes são desenvolvidos com um código próprio de funcionamento, ou seja, não rodam um sistema operacional mas um programa com funções específicas.

3. Apresente aplicações de sistemas embarcados:

(a) para a indústria automotiva: Controle dos faróis diurnos, de indicação e de ré. Controle dos sistemas de amortecimento, frenagem e Airbag do carro. Monitoramento dos sensores de temperatura, pressão de pneu, líquido de arrefecimento dos carros.

(b) para eletrodomésticos: Controle de todo o sistema de lavagem de uma máquina de lavar, como fluxo de água quente e fria, acionamento e velocidade dos motores de giro do tambor, acionamento das bombas de sucção de água suja.

(c) para automação industrial: Em uma linha de montagem de carros automatizado cada robô possui um sistema embarcado de controle individual de cada um dos motores que realizam sua movimentação, em conformidade com as peças a serem montadas e ajustadas.


4. Cite arquiteturas possíveis e as diferenças entre elas.
Uma das arquiteturas mais comuns são os computadores completos. São sistemas embarcados que possuem um sistema operacional executando os programas necessárias para determinada aplicação. Devido o grande número de possíveis aplicações que essa arquitetura possui normalmente são grandes, como os Desktops, mas, atualmente, existem vários de pequena escala, como o Raspberry Pi.

Outra arquitetura existente é a ASICS, application-specific integrated circuits, que é uma arquitetura de extrema especificidade com o intuito de criar um circuito específico para aquela determinada aplicação. Normalmente a maior vantagem é na velocidade superior para execução das aplicações projetadas para este circuito comparado a outras arquiteturas. Porém tendem a ter um custo maior para realização de atualizações pois devem ser fabricados novas unidades com as alterações necessárias.

Em seguida temos a arquitetura de FPGA, Field Programmable Gate Array, que são os mais versáteis. Está arquitetura exige um tempo maior para projeto pois exige a programação em VHDL, de como o hardware deve se comportar, e, se necessário, o software embarcado em C que executa as operações necessárias no sistema.

Por fim temos os microcontroladores que são circuitos integrados onde especificamos via software o funcionamento do circuito, sendo reconfigurável, se houver necessidade, das funcionalidades em software.

5. Por que usamos o MSP430 na disciplina, ao invés de outro microcontrolador?

O microcontrolador MSP430, desenvolvido e fabricado pela empresa Texas Instruments, é uma solução mais técnica e barata que a utilização de outro microcontrolador como o Arduino. É fabricado por uma empresa internacionamente conhecida pelo desenvolvimento e venda de componentes eletrônicos e possui um SDK para desenvolvimento de aplicações mais detalhadas e específicas. Mesmo a plataforma Arduino sendo mais difundida e mais fácil devido as inúmeras bibliotecas o microcontrolador MSP430 com seu SDK fornece ao aluno graduando de Engenharia Eletrônica um conhecimento melhor no desenvolvimento de microcontroladores desenvolvidos no mercado. Esse fato ocorre pois no mercado de trabalho a criação de bibliotecas e programação bem mais complexa que as necessárias para o Arduino é uma exigência normal para um engenheiro.
