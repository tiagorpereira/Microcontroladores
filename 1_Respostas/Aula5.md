### Para as questões 2 a 5, considere que as variáveis `f`, `g`, `h`, `i` e `j` são do tipo inteiro (16 bits na arquitetura do MSP430), e que o vetor `A[]` é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores:
- f: R4
- g: R5
- h: R6
- i: R7
- j: R8
- A: R9
### Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

## 1. Escreva os trechos de código assembly do MSP430 para:
###	(a) Somente setar o bit menos significativo de R5.
```
BIS #1,R5
```
###	(b) Somente setar dois bits de R6: o menos significativo e o segundo menos significativo.
```
BIS #3,R6
```
###	(c) Somente zerar o terceiro bit menos significativo de R7.
```
AND.W #4,R7
```
###	(d) Somente zerar o terceiro e o quarto bits menos significativo de R8.
```
AND.W #C,R8
```
###	(e) Somente inverter o bit mais significativo de R9.
```
XOR #8000,R9
```
###	(f) Inverter o nibble mais significativo de R10, e setar o nibble menos significativo de R10.
```
XOR #F000,R10
BIS #F,R10
```
## 2. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
if(i>j) f = g+h+10;
else f = g-h-10;
```
```assembly
cmp R7,R8   ;R7=i, R8=j
jl TRUE     ;j<i pula para label TRUE
mov.w R5,R4  ;R4=f, R5=g
sub.w R6,R4  ;R4=f=g, R6=h
sub.w #A,R4  ;R4=f=g-h-10
TRUE:        ;Label True
mov.w R5,R4  ;R4=f, R5=g
add.w R6,R4  ;R4=f=g, R6=h
add.w #10,R4 ;R4=f=g+h+10
```


## 3. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
while(save[i]!=k) i++;
```

```assembly
LOOP:mov.w R7,R11 ;R7=i, R11 = temporario
rla R11           ;R11 = 2*i
add.w R12,R11     ;R12 = save, R11 = save + 2*i = &sabe[i]
cmp 0(R11),R10    ;Compara save[i] com k (R10)
jeq EXIT          ;save[i] == k? Se sim pula para label EXIT
inc.w R7          ;i++ = i+= 1 => i = i + 1
jmp LOOP

EXIT:
...
```

## 4. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
for(i=0; i<100; i++) A[i] = i*2;
```
```assembly
clr.w R7

FOR:mov.w R7,R11 ;R7=i, R11 = Temporario
rla R11          ;R11 = i*2
mov.w R11,0(R9)  ;R9 = A, R11 = 2*i;
inc.w R7         ;i++
cmp #64,R7       ;Compara i com 100
jl EXIT         ;Se i<100 pula para label final
jmp FOR          ;Volta para o começo

EXIT: ...
```


## 5. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
for(i=99; i>=0; i--) A[i] = i*2;
```

```assembly
mov.w #63,R7;

FOR:mov.w R7,R11 ;R7=i, R11 = Temporario
rla R11          ;R11 = i*2
mov.w R11,0(R9)  ;R9 = A, R11 = 2*i;
dec.w R7         ;i--
cmp #0,R7        ;Compara i com 0
jge EXIT          ;Se i>=0 pula para label final
jmp FOR          ;Volta para o começo

EXIT:
...
```
