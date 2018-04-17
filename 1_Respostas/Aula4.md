## Para todas as questões, considere que as variáveis `f`, `g`, `h`, `i` e `j` são do tipo inteiro (16 bits na arquitetura do MSP430), e que o vetor `A[]` é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores:

- f: R4
- g: R5
- h: R6
- i: R7
- j: R8
- A: R9

## Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

## 1. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w, sub.w, clr.w, dec.w, decd.w, inc.w e incd.w.

### (a) `f *= 5;` => f = f * 5 = (f + f) + (f + f) + f;
```
add.w R4, R4    ; f = f + f
mov.w R4, R11   ; f + f > R11
add.w R11, R11  ; (f + f) + (f + f) = f * 4
add.w R11, R4   ; (f * 4 + f) = f * 5
```
### (b) `g *= 6;`

```
mov.w R5, R11 ; (f => R11 temp)
add.w R5, R5  ; g*2
add.w R11, R5 ; g*3
add.w R5, R5  ; g*6
```

### (d) `A[2] = 6*A[1] + 5*A[0];`

```
mov.w 0(R9),R11    ; R11 = A[0]
mov.w 2(R9),R12    ; R12 = A[1]
add.w 0(R9),0(R9)  ; 2 * A[0]
add.w 0(R9),0(R9)  ; 4 * A[0]
add.w R11,0(R9)    ; 5 * A[0]
mov.w 0(R9),4(R9)  ; A[2] = 5 * A[0]
add.w 2(R9),2(R9)  ; 2 * A[1]
add.w R12, 2(R9)   ; 3 * A[1]
add.w 2(R9),2(R9)  ; 2 * (3 * A[1])
add.w 2(R9),4(R9)  ; A[2] = 5 * A[0] + 6 * A[1]
```

### (e) `A[3] = 3*f - 5*h;`

```
mov.w R4,R11    ;R11 = f
add.w R4,R4     ;f + f = f * 2
add.w R11,R4    ;(f * 2) + f = f * 3
mov.w R4,6(R9)  ;A[3] = f * 3
mov.w R6,R12    ;R12 = h
add.w R6,R6     ;h + h = h * 2
add.w R6,R6     ;(h + h) + (h + h) = h * 4
add.w R12,R6    ;(h * 4) + h = h * 5
sub.w R6,6(R9)  ;A[3] = (3 * f) - (h * 5)
```


### (f) `A[5] = 6*(f - 2*h);`
```
add.w R6,R6      ;h + h = h*2
sub.w R6,R4      ;f - h*2 = R4
mov.w R4,R11     ;f - h*2 = R11
add.w R4,R4      ;(f - h*2) + (f - h*2) = (f - h*2) * 2
add.w R11,R4     ;2*(f - h*2) + (f - h*2) = 3 * (f - h*2)
add.w R4,R4      ;2 * (3 * (f - h*2)) = 6 * (f - h*2)
mov.w R4,10(R9)  ;A[5] = 6 * (f - h*2)
```
