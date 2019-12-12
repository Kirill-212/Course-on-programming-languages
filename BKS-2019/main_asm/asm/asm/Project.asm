.586P
.MODEL FLAT,STDCALL

includelib kernel32.lib
includelib libucrt.lib

EXTERN getmin :proc
EXTERN getmax :proc
EXTERN stringtoint :proc
EXTERN strlen1 :proc



ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD


SetConsoleTitleA PROTO :DWORD
GetStdHandle     PROTO :DWORD
WriteConsoleA    PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD


.STACK 4096

.CONST
	arr DD 10,22,4,6,1,9,45,7,5,10
	consoletitle db 'console title',0
	
.DATA
   movall dword 'fffr'
	movall1 dword '122'
consolehandle dd 0h
	f DD ?
	a DD ?
	resul DD ?
	result1 byte 40 dup(0)
	strstr  db 'getmax-getmin=',0
.CODE
;преобр int->char
int_to_char PROC uses eax ebx ecx edi esi,
                       pstr: dword,
					   intfield: dword
	mov edi,pstr
	mov esi,0
	mov eax,intfield
	cdq
	mov ebx,10
	idiv ebx
	test eax, 80000000h
	jz plus
	neg eax
	neg edx
	mov cl,'-'
	mov [edi],cl
	inc edi
plus:
	push dx
	inc esi
	test eax,eax
	jz fin
	cdq
	idiv ebx
	jmp plus
fin:
	mov ecx,esi
write:
	pop bx
	add bl,'0'
	mov [edi],bl
	inc edi
	loop write

	ret



int_to_char ENDP


main PROC
START:

mov EBX,0
mov EBX, OFFSET arr
mov EAX, 0
mov EAX,lengthof arr
push EAX
push EBX
call getmin
mov a,EAX

mov EBX,0
mov EBX, OFFSET arr
mov EAX, 0
mov EAX,lengthof arr
push EAX
push EBX
call getmax
mov f,EAX

push offset movall
call strlen1
pop EAX



mov EAX,f
sub EAX,a
mov resul,EAX

push resul
push offset result1
call int_to_char


push -11
call GetStdHandle
mov consolehandle,eax

push 0
push 0
push sizeof strstr
push offset strstr
push consolehandle
call WriteConsoleA

push -11
call GetStdHandle
mov consolehandle,eax

push 0
push 0
push sizeof result1
push offset result1
push consolehandle
call WriteConsoleA




push 0    							;  
call ExitProcess					; 
main ENDP							; 
end main