@ OPTIMIZE_IWRAM builds only (linked from linker.ld under OPTIMIZE_IWRAM):
@ the _call_via_rX stubs of libgcc, for the functions copied to IWRAM.
@ Files with IWRAM functions are compiled with -mlong-calls, so their calls
@ go through "bl _call_via_rX", but a bl from IWRAM cannot reach the stubs in
@ ROM; tools/iwram_calls.py renames the calls made from the .iwram_code
@ section to these copies.

	.section .iwram_code, "ax", %progbits
	.code 16
	.align 2, 0

	.macro iwram_call_via reg
	.globl _iwram_call_via_\reg
	.thumb_func
_iwram_call_via_\reg:
	bx \reg
	nop
	.endm

	iwram_call_via r0
	iwram_call_via r1
	iwram_call_via r2
	iwram_call_via r3
	iwram_call_via r4
	iwram_call_via r5
	iwram_call_via r6
	iwram_call_via r7
	iwram_call_via r8
	iwram_call_via r9
	iwram_call_via sb
	iwram_call_via sl
	iwram_call_via fp
	iwram_call_via ip
	iwram_call_via lr
