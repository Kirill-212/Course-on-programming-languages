.586P


.MODEL FLAT,STDCALL

includelib kernel32.lib
includelib libucrt.lib

EXTERN strlen1 :proc
EXTERN ConsoleInt :proc
EXTERN ConsoleStr :proc
EXTERN ConsoleBool :proc
EXTERN stringtoint :proc

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096


.CONST

L1	 sword  	10
L2	 DB  	'frts' , 0
L3	 sword  	5
L4	 sword  	2
L5	 sword  	1
L6	 DB  	'1234' , 0
L7	 sword  	-1000
L8	 sword  	1162
L9	 sword  	1
L10	 DB  	'3df' , 0
L11	 sword  	1
L12	 sword  	1
L13	 sword  	3
L14	 DB  	'frr' , 0
L15	 sword  	59
L16	 sword  	6
L17	 sword  	10
L18	 sword  	-1
L19	 sword  	10
L20	 sword  	4
L21	 sword  	10
L22	 sword  	2
L23	 sword  	3
L24	 sword  	2
L25	 DB  	'hello' , 0
L26	 word  	1
L27	 DB  	'hello' , 0
L28	 word  	1
L29	 DB  	'hello world' , 0
L30	 sword  	10
L31	 sword  	-9
L32	 sword  	2
L33	 sword  	40

.DATA

res_pos	 sword  	?
res2_pow	 sword  	?
str1_main	 DD  	?
col1_main	 sword  	?
num_main	 sword  	?
col_main	 sword  	?

 bks word 0

 consolehandle dd 0h 

.CODE

pos PROC sss_pos: sword , qqq_pos: sword

MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH sss_pos 
 push bks 
PUSH L1 
POP BX
POP AX
POP AX
MUL BX 
 push bks 
PUSH AX 
 push bks 
PUSH qqq_pos 
POP BX
POP AX
POP AX
ADD AX , BX 
 push bks 
PUSH AX 
 MOV AX , 0
POP AX
MOV res_pos , AX

;-
MOV AX , res_pos
ret
;-
pos ENDP

pow PROC sss1_pow: sword , qqq1_pow: sword , res1_pow: sword

MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH sss1_pow 
 push bks 
PUSH qqq1_pow 
POP BX
POP AX
POP AX
ADD AX , BX 
 push bks 
PUSH AX 
  push bks 
PUSH res1_pow 
POP BX
POP AX
POP AX
MUL BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV res2_pow , AX

;-
MOV AX , res2_pow
ret
;-
pow ENDP

main PROC

START:

mov str1_main , offset L2

;print 
push  str1_main
  call ConsoleStr 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L3 
 push bks 
PUSH L4 
 push bks 
PUSH L5 
call pow
 push AX 
 MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH offset L6 
call stringtoint
 push AX 
  push bks 
PUSH L7 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L8 
MOV AX , 0
POP AX
MOV num_main , AX

MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH num_main 
 push bks 
PUSH L9 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV col1_main , AX


;print 
push num_main
 call ConsoleInt 

;print 
push col1_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH offset L10 
call strlen1
 push AX 
  push bks 
PUSH L11 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L12 
 push bks 
PUSH L13 
call pos
 push AX 
 MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH offset L14 
call strlen1
 push AX 
 MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L15 
 push bks 
PUSH L16 
POP BX
POP AX
POP AX
CDQ 
IDIV BX 
MOV AX,DX 
 push bks 
PUSH AX  
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L17 
 push bks 
PUSH L18 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L19 
 push bks 
PUSH L20 
POP BX
POP AX
POP AX
MUL BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L21 
 push bks 
PUSH L22 
POP BX
POP AX
POP AX
CDQ 
DIV BX 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L23 
 push bks 
PUSH L24 
call pos
 push AX 
 MOV AX , 0
POP AX
MOV col_main , AX


;print 
push col_main
 call ConsoleInt 

;print 
push offset L25
 call ConsoleStr 
MOV BX , 1
MOV AX , L26
cmp AX , BX
jz f243
 jnz f0243
 f243:

;print 
push offset L27
 call ConsoleStr 
f0243:MOV BX , 1
MOV AX , L28
cmp AX , BX
jz f255
 jnz f0255
 f255:

;print 
push offset L29
 call ConsoleStr 
f0255:MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L30 
 push bks 
PUSH L31 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
 push bks 
PUSH L32 
POP BX
POP AX
POP AX
MUL BX 
 push bks 
PUSH AX 
 push bks 
PUSH L33 
POP BX
POP AX
POP AX
SUB AX , BX 
 push bks 
PUSH AX 
MOV AX , 0
POP AX
MOV num_main , AX


;print 
push num_main
 call ConsoleInt 

push 0
call ExitProcess
main ENDP
end main
