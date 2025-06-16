; hello.asm - Hello World with debug symbols for YASM
BITS 64                         ; Explicitly specify 64-bit mode
DEFAULT REL                     ; Use RIP-relative addressing by default

extern ExitProcess            ; Import Windows API functions
extern GetStdHandle
extern WriteConsoleA

; Data section
section .data
    message db "Hello, NASM!", 13, 10, 0  ; String with CRLF and null terminator
    message_len equ $ - message	                 ; Calculate string length

; Code section
section .text
global main                    ; Export main symbol for linker

main:
	; Function prologue
	push    rbp
	mov     rbp, rsp
	sub     rsp, 32              ; Shadow space for Windows API calls

	; Get stdout handle
	mov     ecx, -11            ; STD_OUTPUT_HANDLE
	call    GetStdHandle
	mov     rbx, rax            ; Save handle for WriteConsole

	; Write message
	mov     rcx,  rbx              ; Console handle
	lea     rdx,  [message]        ; Message buffer
	mov     r8d,  message_len      ; Message length
	lea     r9,   [rsp+28]         ; Written chars (unused)
	mov     qword [rsp+20],    0   ; Reserved (must be 0)
	call    WriteConsoleA

	; Exit program
	xor     ecx, ecx            ; Exit code 0
	call    ExitProcess

	; Function epilogue (not reached due to ExitProcess)
	leave
	ret
