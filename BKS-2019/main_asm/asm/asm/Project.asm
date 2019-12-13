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

L1	 sdword  	3
L2	 sdword  	3
L3	 DB  	'hello'

.DATA

res_pos	 sdword  	?
col_main	 sdword  	?

 consolehandle dd 0h 

.CODE

pos PROC s_pos: dword , a_pos: dword

MOV EBX , 0 
MOV EAX , 0 
PUSH s_pos
PUSH a_pos
POP EBX
POP EAX
MUL EBX 
PUSH EAX 
MOV EAX , 0
POP EAX
MOV res_pos ,  EAX

;-
MOV EAX , res_pos
ret
;-
pos ENDP

main PROC

START:

MOV EBX , 0 
MOV EAX , 0 
PUSH L1
PUSH L2
call pos
 push EAX
MOV EAX , 0
POP EAX
MOV col_main , EAX


;print 
push col_main
 call ConsoleInt 

;print 
push offset L3
 call ConsoleStr 

push 0
call ExitProcess
main ENDP
end main
