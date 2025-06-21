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
%define rdstindex       rdi
%define rsrcindex       rsi
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

; Resets the Floating-Point Unit (FPU), which also clears all MMX registers
; (MM0-MM7) and FPU stack registers (ST0-ST7).
%macro wipe_fpu_mmxs 0
    finit
%endmacro

; Wipes the 128-bit XMM registers. Requires a CPU with at least SSE.
%macro wipe_xmms 0
    vxorps  xmm0,  xmm0,  xmm0
    vxorps  xmm1,  xmm1,  xmm1
    vxorps  xmm2,  xmm2,  xmm2
    vxorps  xmm3,  xmm3,  xmm3
    vxorps  xmm4,  xmm4,  xmm4
    vxorps  xmm5,  xmm5,  xmm5
    vxorps  xmm6,  xmm6,  xmm6
    vxorps  xmm7,  xmm7,  xmm7
    vxorps  xmm8,  xmm8,  xmm8
    vxorps  xmm9,  xmm9,  xmm9
    vxorps  xmm10, xmm10, xmm10
    vxorps  xmm11, xmm11, xmm11
    vxorps  xmm12, xmm12, xmm12
    vxorps  xmm13, xmm13, xmm13
    vxorps  xmm14, xmm14, xmm14
    vxorps  xmm15, xmm15, xmm15
%endmacro

; =============================================================================
; AVX Registers (YMM0-YMM15)
; =============================================================================
; Wipes the 256-bit YMM registers. Requires a CPU with AVX support.
; This also wipes the lower 128 bits (the XMM registers), so you don't
; need to call WIPE_XMM_REGS if you call this one.
%macro wipe_ymms 0
    vzeroupper                ; Clears upper 128 bits of all YMM registers
    vxorps  ymm0,  ymm0,  ymm0  ; Clears the full YMM0 (including lower XMM0)
    vxorps  ymm1,  ymm1,  ymm1
    vxorps  ymm2,  ymm2,  ymm2
    vxorps  ymm3,  ymm3,  ymm3
    vxorps  ymm4,  ymm4,  ymm4
    vxorps  ymm5,  ymm5,  ymm5
    vxorps  ymm6,  ymm6,  ymm6
    vxorps  ymm7,  ymm7,  ymm7
    vxorps  ymm8,  ymm8,  ymm8
    vxorps  ymm9,  ymm9,  ymm9
    vxorps  ymm10, ymm10, ymm10
    vxorps  ymm11, ymm11, ymm11
    vxorps  ymm12, ymm12, ymm12
    vxorps  ymm13, ymm13, ymm13
    vxorps  ymm14, ymm14, ymm14
    vxorps  ymm15, ymm15, ymm15
%endmacro

; =============================================================================
; AVX-512 Registers (ZMM0-ZMM31 and K0-K7)
; =============================================================================
; Wipes the 512-bit ZMM registers and the 8 mask registers (k0-k7).
; Requires a CPU with AVX-512F support. This is the most comprehensive
; vector register wipe and makes WIPE_XMM_REGS and WIPE_YMM_REGS redundant.
%macro wipe_avx512s 0
    ; Wipe Mask Registers (k0-k7)
    kxorb   k0, k0, k0
    kxorb   k1, k1, k1
    kxorb   k2, k2, k2
    kxorb   k3, k3, k3
    kxorb   k4, k4, k4
    kxorb   k5, k5, k5
    kxorb   k6, k6, k6
    kxorb   k7, k7, k7

    ; Wipe ZMM registers (zmm0-zmm31)
    vpxord  zmm0, zmm0, zmm0
    vpxord  zmm1, zmm1, zmm1
    vpxord  zmm2, zmm2, zmm2
    vpxord  zmm3, zmm3, zmm3
    vpxord  zmm4, zmm4, zmm4
    vpxord  zmm5, zmm5, zmm5
    vpxord  zmm6, zmm6, zmm6
    vpxord  zmm7, zmm7, zmm7
    vpxord  zmm8, zmm8, zmm8
    vpxord  zmm9, zmm9, zmm9
    vpxord  zmm10, zmm10, zmm10
    vpxord  zmm11, zmm11, zmm11
    vpxord  zmm12, zmm12, zmm12
    vpxord  zmm13, zmm13, zmm13
    vpxord  zmm14, zmm14, zmm14
    vpxord  zmm15, zmm15, zmm15
    vpxord  zmm16, zmm16, zmm16
    vpxord  zmm17, zmm17, zmm17
    vpxord  zmm18, zmm18, zmm18
    vpxord  zmm19, zmm19, zmm19
    vpxord  zmm20, zmm20, zmm20
    vpxord  zmm21, zmm21, zmm21
    vpxord  zmm22, zmm22, zmm22
    vpxord  zmm23, zmm23, zmm23
    vpxord  zmm24, zmm24, zmm24
    vpxord  zmm25, zmm25, zmm25
    vpxord  zmm26, zmm26, zmm26
    vpxord  zmm27, zmm27, zmm27
    vpxord  zmm28, zmm28, zmm28
    vpxord  zmm29, zmm29, zmm29
    vpxord  zmm30, zmm30, zmm30
    vpxord  zmm31, zmm31, zmm31
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
	%define dbg_wipe_gprs     wipe_gprs
	%define dbg_wipe_fpu_mmxs wipe_fpu_mmxs
	%define dbg_wipe_xmms     wipe_xmms
	%define dbg_wipe_ymms     wipe_ymms
	%define dbg_wipe_avx512s  wipe_avx512s
%else
	%macro assert_not_null 1
	%endmacro
	%macro slice_assert 1
	%endmacro
	%define dbg_wipe_gprs
	%define dbg_wipe_fpu_mmxs
	%define dbg_wipe_xmms
	%define dbg_wipe_ymms
	%define dbg_wipe_avx512s
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

;region memory_copy

;endregion memory_copy

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


; struc Slice_Byte
; 	.ptr: resq 1 (Byte*)
; 	.len: resq 1 
; endstruc
def_Slice Byte

; Usage: stack_slice %1: <type>, %2 <slice id>, %3 <stack_offset>
; Requires a `stack_offset` variable to be %assign'd to 0 at the start of a scope.
; The user must then `sub rsp, stack_offset` to allocate the space.
%macro stack_slice 2
	%assign stack_offset stack_offset + %1 %+ _size
	%define %2 (rstack_base_ptr - stack_offset)
%endmacro

; Usage: slice_assert %1: Slice_<type> { .ptr = Slice.ptr, .len = Slice.len }
%macro slice_assert 1
	%ifidn BUILD_DEBUG, 1
			cmp qword [%1 + Slice.len], nullptr
			jnz %%.ptr_passed
			int debug_trap
		%%.ptr_passed: ; macro-unique-prefix (%%) .passed is the label name
			cmp qword [%1 + Slice.len], 0
			jg  %%.len_passed
			int debug_trap
		%%.len_passed:
	%endif
%endmacro

; Usage slice_assert %1: ptr, %2: len
%macro slice_assert 2
	%ifidn BUILD_DEBUG, 1
		cmp %1, nullptr
		jnz %%.ptr_passed
		int debug_trap
	%%.ptr_passed:
		cmp %2, 0
		jg  %%.len_passed
		int debug_trap
	%%.len_passed:
	%endif
%endmacro

; Usage stac_alloc %1: <stack_offset>
%macro stack_push 1
	push rstack_base_ptr
	mov  rstack_base_ptr, rstack_ptr
	sub  rstack_ptr, %1
%endmacro
%macro stack_pop 0
	mov rstack_ptr, rstack_base_ptr
	pop rstack_base_ptr
%endmacro
;endregion Memory

;region Math

; returns: raccumulator = U64
; Usage 
%macro min_U64 2
	mov   raccumulator, %1
	cmp   raccumulator, %2
	cmovg raccumulator, %2 ; ConditionalMoveIfGreater
%endmacro min_U64

;endregion Math

;region Strings
def_Slice UTF8
%define Str8 Slice_UTF8

; Usage: lit %1: <slice_label>, %2: <utf-8 literal>
%macro lit 2
  %%str_data: db %2
  %%str_len:  equ $ - %%str_data
  %1:
    istruc Str8
        at Str8.ptr, dq %%str_data
        at Str8.len, dq %%str_len
    iend
%endmacro

section .lits progbits noexec nowrite
	lit path_hello_files_asm, `./code/asm/hello_files.asm`
;endregion Strings

;region String Ops

;region str8_to_cstr_capped
%push proc_scope
; result:  rcounter  = [UTF8]
; content: Str8       = { .ptr = rdata, .len = r8 }
; mem:     r9         = [Slice_Byte]
%define result      rcounter
%define content_ptr rdata
%define content_len r8
%define mem

section .text
api_str8_to_cstr_capped:
	%push raccumulator
	%push rsrcindex
	; U64 raccumulator = min(content.len, mem.len - 1);
		mov rsrcindex, qword [mem + Slice_Byte.len]
		sub rsrcindex, 1
		min_U64 content_len, rsrcindex ; raccumulator has result
	; memory_copy(mem.ptr, content.ptr, copy_len);

	; mem.ptr[copy_len] = '\0';
	; return cast(char*, mem.ptr);
	%pop rsrcindex
	%pop raccumulator
	leave
	ret
%pop_proc_scope

; Returns via rcounter
; Usage: str8_to_cstr_capped content, mem
%macro str8_to_cstr_capped 2
	%push rdata
	%push r8
	%push r9
	lea  rdata,    [%2 + Str8.ptr]
	mov  r8,        %2 + Str8.len
	leat r9,        %3
	call api_str8_to_cstr_capped
	%pop r9
	%pop r8
	%pop rdata
%endmacro
;endregion str8_to_cstr_capped

section .data

;endregion String Ops

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

;region file_read_contents

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
%push proc_scope
	assert_not_null result

	slice_assert backing
	slice_assert path_ptr, path_len

		; %define slice_fmem_scratch ;TODO(Ed): figure this out
	; call str8_to_cstr_capped path_c_str, path, slice_fmem_scratch

		; TODO(Ed): Form-fill
	; call CreateFileA

	leave
	ret
%pop proc_scope

section .bss
	api_file_read_contents.scratch_kilo: resb 64 * kilo
	api_file_read_contents.path_cstr:    resq 1
%pop api_file_read_contents

; Args: result: [FileOpInfo], path: Str8, backing: [Slice_Byte]
%macro file_read_contents 3
	%push rcounter
	%push rdata
	%push r8
	%push r9
	lea  rcounter, %1
	lea  rdata,   [%2 + Str8.ptr]
	mov  r8,       %2 + Str8.len
	lea  r9,       %3
	call api_file_read_contents
	%pop r9
	%pop r8
	%pop rdata
	%pop rcounter
%endmacro
;endregion file_read_contents

section .text
global main
	main:
	%push proc_scope
		; dbg_wipe_gprs

		%push calling
			; Allocate stack for file_read_contents args
			%assign stack_offset 0
			stack_slice Slice_Byte, local_backing
			stack_push  stack_offset
			mov qword [local_backing + Slice_Byte.ptr], read_mem
			mov qword [local_backing + Slice_Byte.len], Mem_128k_size
			; Allocate registers with args
			lea  rcounter, file
			lea  rdata,   [path_hello_files_asm + Str8.ptr]
			mov  r8,       path_hello_files_asm + Str8.len
			lea  r9,      [local_backing]
		call api_file_read_contents
			stack_pop
		%pop calling

		; file_read_contents file, path_hello_files_asm, read_mem
	%pop proc_scope
		ret

section .bss
read_mem: resb Mem_128k_size

file: resb FileOpInfo_size
