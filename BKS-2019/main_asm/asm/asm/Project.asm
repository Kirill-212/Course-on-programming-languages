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

L1	 sword  	3
L2	 sword  	3
L3	 DB  	'32' , 0
L4	 sword  	2
L5	 sword  	59
L6	 sword  	6
L7	 DB  	'3' , 0
L8	 sword  	20000
L9	 sword  	2000000
L10	 DB  	'3ed' , 0
L11	 DB  	'end' , 0

.DATA

res1_posin1	 sword  	?
col_main	 sword  	?

 bks word 0

 consolehandle dd 0h 

.CODE

posin1 PROC sms1_posin1: dword , qqq1_posin1: sword

MOV BX , L2
MOV AX , L1
cmp AX , BX
jz f17
jnz f017
 f17:

;print 
push  sms1_posin1
  call  ConsoleStr 
f017:MOV BX , 0 
MOV AX , 0 
PUSH offset L3 
call stringtoint
 push AX 
  push bks 
PUSH L4 
POP BX
POP AX
POP AX
CDQ 
DIV BX 
PUSH AX 
MOV AX , 0
POP AX
MOV res1_posin1 , AX


;print 
push res1_posin1
  call  ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L5 
 push bks 
PUSH qqq1_posin1 
POP BX
POP AX
POP AX
CDQ 
IDIV BX 
MOV AX,DX 
PUSH AX  
MOV AX , 0
POP AX
MOV res1_posin1 , AX


;print 
push res1_posin1
  call  ConsoleInt 
;-
MOV AX , res1_posin1
ret
;-
posin1 ENDP

main PROC

START:

MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L6 
PUSH offset L7 
call posin1
 push AX 
 MOV AX , 0
POP AX
MOV col_main , AX


;print 
push col_main
  call  ConsoleInt 
MOV BX , 0 
MOV AX , 0 
 push bks 
PUSH L8 
 push bks 
PUSH L9 
POP BX
POP AX
POP AX
ADD AX , BX 
PUSH AX 
 MOV AX , 0
POP AX
MOV col_main , AX


;print 
push col_main
  call  ConsoleInt 
MOV BX , 0 
MOV AX , 0 
PUSH offset L10 
call strlen1
 push AX 
 MOV AX , 0
POP AX
MOV col_main , AX


;print 
push col_main
  call  ConsoleInt 

;print 
push offset L11
   call  ConsoleStr 

push 0
call ExitProcess
main ENDP
end main
