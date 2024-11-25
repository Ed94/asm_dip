include 'fasm2.inc'

format PE64 console
entry main

section '.data' data readable writeable
	message       db 'Hello World!', 13, 10
	message_len = $ - message
	written       dq ?

section '.text' code readable executable
main:
	sub		rsp, 40                     ; 32 + 8 for alignment

	mov		ecx, -11                    ; STD_OUTPUT_HANDLE
	call	[GetStdHandle]

	mov		rcx, rax                    ; Handle
	lea		rdx, [message]              ; Buffer
	mov		r8,  message_len            ; Length
	lea		r9,  [written]              ; Bytes written
	push	0                           ; Reserved parameter
	sub		rsp, 32                     ; Shadow space
	call	[WriteConsoleA]
	add		rsp, 40                     ; Cleanup stack + reserved param

	xor		ecx, ecx                    ; Exit code 0
	call	[ExitProcess]

section '.idata' import data readable
	library kernel32,'KERNEL32.DLL'

include 'win64a.inc'

import kernel32,\
	GetStdHandle,'GetStdHandle',\
	WriteConsoleA,'WriteConsoleA',\
	ExitProcess,'ExitProcess'
