; Hello Files!

BITS 64     ; Explicitly specify 64-bit mode
DEFAULT REL ; Use RIP-relative addressing by default

%define BUILD_DEBUG 1

;region DSL
%define marg

%define rcounter_32     ecx
%define r8_32           r8d

%define raccumulator    rax
%define rcounter        rcx
%define rdata           rdx
%define rstack_ptr      rsp
%define rstack_base_ptr rbp
;endregion DSL

;region Registers

; Wipes all 64-bit general-purpose registers except for the stack pointer (RSP).
; Zeroing RSP would corrupt the stack and crash the program.
; Zeroing RBP will break the stack frame chain used by debuggers.
%macro wipe_gprs 0
	xor rax, rax
	xor rbx, rbx
	xor rcx, rcx
	xor rdx, rdx
	xor rsi, rsi
	xor rdi, rdi
	; xor rbp, rbp
	xor r8,  r8
	xor r9,  r9
	xor r10, r10
	xor r11, r11
	xor r12, r12
	xor r13, r13
	xor r14, r14
	xor r15, r15
%endmacro
;endregion Registers

;region Debug
%define debug_trap 3

%ifidn BUILD_DEBUG, 1
	%macro assert_not_null 1
		cmp %1, nullptr
		jnz %%.passed
		int debug_trap
	%%.passed: ; macro-unique-prefix (%%) .passed is the label name
	%endmacro
	%macro slice_assert 1
		cmp qword [%1 + Slice.ptr], 0
		jnz %%.ptr_passed
		int debug_trap
	%%.ptr_passed:
		cmp qword [%1 + Slice.len]
		jg  %%.len_passed
		int debug_trap
	%%.len_passed:
	%endmacro
	%define dbg_wipe_gprs wipe_gprs
%else
	%macro assert_not_null 1
	%endmacro
	%macro slice_assert 1
	%endmacro
	%define dbg_wipe_gprs
%endif ; BUILD_DEBUG
;endregion Debug

;region Memory
%define nullptr 0
%define kilo 1024

; Usage: def_array <name: %1> <size: %2>
%macro def_farray 2+
	struc %1
		.ptr: resb %2
	endstruc
%endmacro

def_farray Mem_128k, 128 * kilo

struc Slice
	.ptr: resq 1
	.len: resq 1
endstruc

; Usage: def_Slice %1: <slice_label>
%macro def_Slice 1
	struc Slice_ %+ %1
		.ptr: resq 1
		.len: resq 1
	endstruc
%endmacro

def_Slice Byte
;endregion Memory

;region Strings
def_Slice Str8

; Usage: lit %1: <slice_label>, %2: <utf-8 literal>
; Both the struct and the string data are emitted into the current section.
%macro lit 2
  %%str_data: db %2
  %%str_len:  equ $ - %%str_data
  %1:
    istruc Slice_Str8
        ; Store the ADDRESS of the string data in the ptr field.
        at Slice_Str8.ptr, dq %%str_data
        ; Store the pre-calculated LENGTH in the len field.
        at Slice_Str8.len, dq %%str_len
    iend
%endmacro

; Usage: stack_slice %1: <type>, %2 <slice id>
%macro stack_slice 2
; Gemini finish this definition for me
%endmacro

section .lits progbits noexec nowrite
	lit path_hello_files_asm, `./code/asm/hello_files.asm`
;endregion Strings

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

%define wapi_write_console_written_chars r9
%macro wapi_write_console 2
		mov rcounter,[%1]        ; Console Handle
		lea rdata,   [%2]        ; Slice_Str8.Ptr
		mov r8_32,    %2 %+ _len ; Slice_Str8.Len
		lea r9,   [rstack_ptr + wapi_arg4_offset]    ; Written chars
		mov qword [rstack_ptr + wapi_arg5_offset], 0 ; Reserved (must be 0)
	call WriteConsoleA
%endmacro

section .data
	std_out_hndl dq 0
;endregion WinAPI

struc FileOpInfo
	.content: resb Slice_Byte_size ; gemini is this allowed?
endstruc

;region api_file_read_contents
; Reg allocation:
; result:  rcounter   = [FileOpInfo]
; path:    Slice_Str8 = { .ptr = rdata, .len = r8 }
; backing: r9         = [Slice_Byte] 
%push api_file_read_contents
%define result   rcounter
%define path_ptr rdata
%define path_len r8
%define backing  r9

section .text
api_file_read_contents:
	assert_not_null result
	; slice_assert    path
	; slice_assert    backing
	; local_persist scratch_kilo: [64 * kilo]U8; (api_file_read_contents.scratch_kilo)

		; %define slice_fmem_scratch ;TODO(Ed): figure this out
	; call str8_to_cstr_capped path_c_str, path, slice_fmem_scratch

		; TODO(Ed): Form-fill
	; call CreateFileA

	leave
	ret

section .bss
	api_file_read_contents.scratch_kilo: resb 64 * kilo
	api_file_read_contents.path_cstr:    resq 1
%pop api_file_read_contents
;endregion api_file_read_contents

; Args: result: [FileOpInfo], path: Slice_Str8, backing: [Slice_Byte]
%macro file_read_contents 3
	%push rcounter
	%push rdata
	%push r8
	%push r9
	lea  rcounter, %1
	lea  rdata,   [%2 + Slice.ptr]
	mov  r8,       %2 + Slice.len
	lea  r9,       %3
	call api_file_read_contents
	%pop r9
	%pop r8
	%pop rdata
	%pop rcounter
%endmacro


section .text
global main
	main:
		; dbg_wipe_gprs

		%push calling
			%define stack_alloc (Slice_Byte_size)
			push rstack_base_ptr
			mov  rstack_base_ptr, rstack_ptr
			sub  rstack_ptr, -stack_alloc

			%define local_backing (rstack_base_ptr - stack_alloc)

			mov qword [local_backing + Slice_Byte.ptr], read_mem
			mov qword [local_backing + Slice_Byte.len], Mem_128k_size

			lea  rcounter, file
			lea  rdata,   [path_hello_files_asm + Slice.ptr]
			mov  r8,       path_hello_files_asm + Slice.len
			lea  r9,      [local_backing]
		call api_file_read_contents
		%pop calling

		; file_read_contents file, path_hello_files_asm, read_mem

		mov rstack_ptr, rstack_base_ptr
		pop rstack_base_ptr
		ret

section .bss
read_mem: resb Mem_128k_size

file: resb FileOpInfo_size
