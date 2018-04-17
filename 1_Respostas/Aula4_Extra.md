### Para todas as questões, considere que as variáveis `f`, `g`, `h`, `i` e `j` são do tipo inteiro (16 bits na arquitetura do MSP430), e que o vetor `A[]` é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores:

- f: R4
- g: R5
- h: R6
- i: R7
- j: R8
- A: R9

### Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

## 1. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w e sub.w.

### (a) `f = 0;`
```assembly
  mov.w #0,R4;
```
### (b) `g++;`
```assembly
  add.w #1,R5;
```
### (c) `h--;`
```
  sub.w #1,R6;
```
### (d) `i += 2;`
```
  add.w #2,R7;
```
### (e) `j -= 2;`
```
  sub.w #2,R8;
```
## 2. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w, sub.w, clr.w, dec.w, decd.w, inc.w e incd.w.

### (a) `f = 0;`
```
  clr.w R4;
```
### (b) `g++;`
```
  inc.w R5;
```
### (c) `h--;`
```
  dec.w R6;
```
### (d) `i += 2;`
```
  incd.w R7;
```
### (e) `j -= 2;`
```
  decd.w R8;
```
## 3. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w, sub.w, clr.w, dec.w, decd.w, inc.w e incd.w.

### (a) `f *= 2;` => f = f * 2 = f + f

```
add.w R4,R4 ;f = f + f = 2 * f
```

### (b) `g *= 3;`=> g = g*3 = (g + g) + g;

```assembly
mov.w R5,R11 ;Move g para registrador temporario R11
add.w R5,R5; ;g + g
add.w R11,R5 ;g + (g+g)
```

### (c) `h *= 4;` h = h * 4 = ((h + h) + h) + h
```assembly
add.w R6,R6 ;h + h = h * 2
add.w R6,R6 ;(2 * h) + (2 * h) = 4 * h
```
### (d) `A[2] = A[1] + A[0];`
```
mov 2(R9),4(R9)   ;A[1] => A[2]
add.w 0(R9),4(R9) ;A[2] = A[1] + A[0]
```
### (e) `A[3] = 2*f - 4*h;`
```
add.w R4,R4     ;f = f + f => 2*f
mov.w R4,6(R9)  ;f => A[3]
add.w R6,R6     ;h = h + h => h*2
add.w R6,R6     ;h = (2*h) + (2*h) => 4*h
sub.w R6,6(R9)  ;A[3] = (2*f) - 4*h
```

### (f) `A[3] = 2*(f - 2*h);`
```
add.w R6,R6     ;h = h + h => 2 * h
sub.w R6,R4     ;f - 2*h = h
mov.w R4,R11    ;f - 2*h => R11
add.w R11,R11   ;2 * (f - 2*h)
mov.w R11,6(R9) ;A[3] = 2 * (f - 2*h)
```
