; Hello Slices!

%define marg

%define rcounter_32 ecx

%define reg8_32         r8d

%define raccumulator    rax
%define rcounter        rcx
%define rdata           rdx
%define rstack_ptr      rsp
%define rstack_base_ptr rbp

%define reg9 r9

%define MS_STD_OUTPUT_HANDLE 11

struc Slice_Byte
	.ptr: resq 1
	.len: resq 1
endstruc

struc Slice_Str8
	.ptr: resq 1
	.len: resq 1
endstruc

; Usage: lit %1: <slice_label> %2: <utf-8 literal>
%macro lit 2
	lit_ %+ %1: db %2
	lit_ %+ %1 %+ _len: equ $ - (lit_ %+ %1)
%endmacro

BITS 64     ; Explicitly specify 64-bit mode
DEFAULT REL ; Use RIP-relative addressing by default

; kernel32.lib
extern GetStdHandle
extern WriteConsoleA

section .data
	std_out_hndl dq 0

section .lits progbits noexec nowrite
	lit hello_msg, `Hello Slices\n`

section .text
global main

%define wapi_shadow_width 48
%macro wapi_shadow_space 0
	push rstack_base_ptr
	mov  rstack_base_ptr, rstack_ptr
	sub  rstack_ptr,      wapi_shadow_width
%endmacro
%define wapi_arg4_offset 28
%define wapi_arg5_offset 32

%define wapi_write_console_written_chars reg9
%macro wapi_write_console 2
		mov rcounter,[%1]        ; Console Handle
		lea rdata,   [%2]        ; Slice_Str8.Ptr
		mov reg8_32,  %2 %+ _len ; Slice_Str8.Len
		lea reg9, [rstack_ptr + wapi_arg4_offset]    ; Written chars
		mov qword [rstack_ptr + wapi_arg5_offset], 0 ; Reserved (must be 0)
	call WriteConsoleA
%endmacro

main:
	wapi_shadow_space

; Setup stdout handle
	mov rcounter_32, -MS_STD_OUTPUT_HANDLE
	call GetStdHandle
	mov [std_out_hndl], raccumulator

	wapi_write_console std_out_hndl, lit_hello_msg

	leave
	ret
