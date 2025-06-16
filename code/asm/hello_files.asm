; Hello Files!

BITS 64     ; Explicitly specify 64-bit mode
DEFAULT REL ; Use RIP-relative addressing by default

;region DSL
%define marg

%define rcounter_32 ecx

%define r8_32           r8d

%define raccumulator    rax
%define rcounter        rcx
%define rdata           rdx
%define rstack_ptr      rsp
%define rstack_base_ptr rbp

%define reg9 r9
;endregion

;region debug
%define debug_trap 3
;endregion

;region Memory
%define kilo 1024

%define nullptr 0

%macro assert_not_null 1
	cmp %1, nullptr
	jnz %%+.passed
	int debug_trap
%%+.passed ; macro-unique-prefix (%%) + internal expansion .passed is the label name
%endmacro

; Usage: def_Slice %1: <slice_label>
%macro def_Slice 1
	struc Slice_ %+ %1
		.ptr: resq 1
		.len: resq 1
	endstruc
%endmacro

def_Slice Byte
def_Slice Str8
;endregion Memory

;region Str8 Table
; Usage: lit %1: <slice_label>, %2: <utf-8 literal>
%macro lit 2
	lit_ %+ %1: db %2
	lit_ %+ %1 %+ _len: equ $ - (lit_ %+ %1)
%endmacro

; Usage: stack_slice %1: <type>, %2 <slice id>
%macro stack_slice %2

%endmacro

section .lits progbits noexec nowrite
	lit path_hello_files_asm, `./code/asm/hello_files.asm`
;endregion Str8 Table

;region WinAPI
; kernel32.lib
; Console IO
extern GetStdHandle
extern WriteConsoleA
; File API
extern CreateFileA
extern GetFileSizeEx
extern GetLastError
extern ReadFile

%define MS_STD_OUTPUT_HANDLE 11

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
		mov r8_32,    %2 %+ _len ; Slice_Str8.Len
		lea reg9, [rstack_ptr + wapi_arg4_offset]    ; Written chars
		mov qword [rstack_ptr + wapi_arg5_offset], 0 ; Reserved (must be 0)
	call WriteConsoleA
%endmacro

section .data
	std_out_hndl dq 0
;endregion

api_file_read_contents:
	section .text
		%define result  ;TODO(Ed): figure out the convention
		%define path    ;TODO(Ed): figure out the convention
		%define backing ;TODO(Ed): figure out the convention

		assert_not_null result
		slice_assert    path
		slice_assert    backing
		; local_persist scratch_kilo: [64 * kilo]U8; (api_file_read_contents.scratch_kilo)

			%define slice_fmem_scratch ;TODO(Ed): figure this out
		call str8_to_cstr_capped path_c_str, path, slice_fmem_scratch

			; TODO(Ed): Form-fill
		call CreateFileA

		leave
		ret

	section .bss
		api_file_read_contents.scratch_kilo: resb 64 * kilo
		api_file_read_contents.path_cstr:    resq 1

section .text
global main

main:
	wapi_shadow_space

		; TODO(Ed): Form-fill
	call api_file_read_contents

	leave
	ret
