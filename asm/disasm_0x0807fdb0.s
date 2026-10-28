    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start unk_7fdb0
unk_7fdb0: @ 0x0807FDB0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	movs r5, #0
	movs r7, #0
	cmp r0, #0
	bne _0807FDC8
	ldr r1, _0807FDC4 @ =sSaveDataEwramPointers
	b _0807FDCA
	.align 2, 0
_0807FDC4: .4byte sSaveDataEwramPointers
_0807FDC8:
	ldr r1, _0807FE50 @ =sSaveDataEwramBackupPointers
_0807FDCA:
	ldr r0, _0807FE54 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r4, [r0]
	adds r3, r4, #0
	movs r1, #0
	ldr r6, [r4, #0x10]
	movs r2, #0x8f
_0807FDDC:
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	subs r2, #1
	cmp r2, #0
	bge _0807FDDC
	cmp r6, r1
	bne _0807FE0E
	ldr r0, [r4, #0x14]
	mvns r0, r0
	cmp r6, r0
	beq _0807FE12
_0807FE0E:
	movs r0, #1
	orrs r5, r0
_0807FE12:
	movs r2, #0
	ldr r6, _0807FE58 @ =sSramUnk_582200
	movs r3, #1
_0807FE18:
	adds r0, r2, r6
	adds r1, r4, r2
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0807FE26
	orrs r7, r3
_0807FE26:
	adds r2, #1
	cmp r2, #0xf
	ble _0807FE18
	adds r0, r7, #0
	adds r5, r5, r0
	cmp r5, #1
	ble _0807FE46
	ldr r1, _0807FE5C @ =0x0000FFFF
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	adds r2, r4, #0
	bl BitFill
_0807FE46:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807FE50: .4byte sSaveDataEwramBackupPointers
_0807FE54: .4byte 0x03000B8D
_0807FE58: .4byte sSramUnk_582200
_0807FE5C: .4byte 0x0000FFFF

