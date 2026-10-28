    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start unk_7b674
unk_7b674: @ 0x0807B674
	push {r4, r5, lr}
	ldr r2, _0807B6AC @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r1, [r0]
	movs r0, #3
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	bne _0807B68C
	b _0807B8C4
_0807B68C:
	ldr r2, _0807B6B0 @ =0x00000252
	adds r0, r4, r2
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldr r1, _0807B6B4 @ =0x00000251
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #8
	bls _0807B6A2
	b _0807B8C4
_0807B6A2:
	lsls r0, r0, #2
	ldr r1, _0807B6B8 @ =_0807B6BC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807B6AC: .4byte gNonGameplayRam
_0807B6B0: .4byte 0x00000252
_0807B6B4: .4byte 0x00000251
_0807B6B8: .4byte _0807B6BC
_0807B6BC: @ jump table
	.4byte _0807B6E0 @ case 0
	.4byte _0807B72C @ case 1
	.4byte _0807B82C @ case 2
	.4byte _0807B780 @ case 3
	.4byte _0807B7BC @ case 4
	.4byte _0807B7D4 @ case 5
	.4byte _0807B82C @ case 6
	.4byte _0807B858 @ case 7
	.4byte _0807B8B0 @ case 8
_0807B6E0:
	movs r2, #0x94
	lsls r2, r2, #2
	adds r0, r4, r2
	ldrb r1, [r0]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0807B700
	ldr r1, _0807B6FC @ =0x00000251
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B710
	.align 2, 0
_0807B6FC: .4byte 0x00000251
_0807B700:
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0807B710
	ldr r2, _0807B720 @ =0x00000251
	adds r1, r4, r2
	movs r0, #4
	strb r0, [r1]
_0807B710:
	ldr r1, _0807B724 @ =gPreviousArea
	movs r0, #0xff
	strb r0, [r1]
	ldr r0, _0807B728 @ =0x00000252
	adds r1, r4, r0
	movs r0, #0
	strb r0, [r1]
	b _0807B8C4
	.align 2, 0
_0807B720: .4byte 0x00000251
_0807B724: .4byte gPreviousArea
_0807B728: .4byte 0x00000252
_0807B72C:
	ldr r1, _0807B770 @ =0x00000252
	adds r2, r4, r1
	ldrb r1, [r2]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _0807B73C
	b _0807B8C4
_0807B73C:
	ldr r0, _0807B774 @ =gWrittenToMosaic_L
	ldrh r1, [r0]
	adds r1, #0x11
	strh r1, [r0]
	ldr r0, _0807B778 @ =sUnk_576802
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	ldrb r0, [r0]
	cmp r1, r0
	beq _0807B752
	b _0807B8C4
_0807B752:
	movs r0, #0
	strb r0, [r2]
	ldr r2, _0807B77C @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0x94
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r1, [r2]
	movs r0, #4
	orrs r0, r1
	strb r0, [r2]
	b _0807B8C4
	.align 2, 0
_0807B770: .4byte 0x00000252
_0807B774: .4byte gWrittenToMosaic_L
_0807B778: .4byte sUnk_576802
_0807B77C: .4byte 0x00000251
_0807B780:
	ldr r0, _0807B7B0 @ =0x00000252
	adds r2, r4, r0
	ldrb r1, [r2]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _0807B790
	b _0807B8C4
_0807B790:
	ldr r1, _0807B7B4 @ =gWrittenToMosaic_L
	ldrh r0, [r1]
	subs r0, #0x11
	strh r0, [r1]
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, #0
	beq _0807B7A2
	b _0807B8C4
_0807B7A2:
	ldr r0, _0807B7B8 @ =0x00000251
	adds r1, r4, r0
	movs r0, #8
	strb r0, [r1]
	strb r3, [r2]
	b _0807B8C4
	.align 2, 0
_0807B7B0: .4byte 0x00000252
_0807B7B4: .4byte gWrittenToMosaic_L
_0807B7B8: .4byte 0x00000251
_0807B7BC:
	ldr r1, _0807B7CC @ =0x00000253
	adds r0, r4, r1
	movs r2, #0
	strb r2, [r0]
	ldr r0, _0807B7D0 @ =0x00000251
	adds r1, r4, r0
	movs r0, #5
	b _0807B846
	.align 2, 0
_0807B7CC: .4byte 0x00000253
_0807B7D0: .4byte 0x00000251
_0807B7D4:
	ldr r2, _0807B81C @ =0x00000253
	adds r5, r4, r2
	ldrb r1, [r5]
	movs r2, #0x50
	subs r0, r2, r1
	asrs r0, r0, #4
	cmp r0, #3
	bgt _0807B7E6
	movs r0, #4
_0807B7E6:
	adds r0, r1, r0
	strb r0, [r5]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x50
	bls _0807B814
	strb r2, [r5]
	ldr r0, _0807B820 @ =0x00000252
	adds r1, r4, r0
	movs r0, #0
	strb r0, [r1]
	ldr r2, _0807B824 @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0x94
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r0, [r2]
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
_0807B814:
	ldr r3, _0807B828 @ =0x04000046
	ldrb r2, [r5]
	b _0807B89A
	.align 2, 0
_0807B81C: .4byte 0x00000253
_0807B820: .4byte 0x00000252
_0807B824: .4byte 0x00000251
_0807B828: .4byte 0x04000046
_0807B82C:
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r1, [r0]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807B8C4
	ldr r2, _0807B850 @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
_0807B846:
	strb r0, [r1]
	ldr r1, _0807B854 @ =0x00000252
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B8C4
	.align 2, 0
_0807B850: .4byte 0x00000251
_0807B854: .4byte 0x00000252
_0807B858:
	ldr r2, _0807B884 @ =0x00000253
	adds r3, r4, r2
	ldrb r1, [r3]
	movs r0, #0x50
	subs r0, r0, r1
	asrs r0, r0, #4
	cmp r0, #3
	bgt _0807B86A
	movs r0, #4
_0807B86A:
	subs r0, r1, r0
	cmp r0, #0
	bge _0807B890
	movs r2, #0
	strb r2, [r3]
	ldr r0, _0807B888 @ =0x00000251
	adds r1, r4, r0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _0807B88C @ =0x00000252
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B892
	.align 2, 0
_0807B884: .4byte 0x00000253
_0807B888: .4byte 0x00000251
_0807B88C: .4byte 0x00000252
_0807B890:
	strb r0, [r3]
_0807B892:
	ldr r3, _0807B8A8 @ =0x04000046
	ldr r2, _0807B8AC @ =0x00000253
	adds r0, r4, r2
	ldrb r2, [r0]
_0807B89A:
	lsls r1, r2, #8
	movs r0, #0xa0
	subs r0, r0, r2
	orrs r1, r0
	strh r1, [r3]
	b _0807B8C4
	.align 2, 0
_0807B8A8: .4byte 0x04000046
_0807B8AC: .4byte 0x00000253
_0807B8B0:
	ldr r1, _0807B8CC @ =0x00000252
	adds r0, r4, r1
	movs r1, #0
	strb r1, [r0]
	ldr r2, _0807B8D0 @ =0x00000251
	adds r0, r4, r2
	strb r1, [r0]
	subs r2, #1
	adds r0, r4, r2
	strb r1, [r0]
_0807B8C4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807B8CC: .4byte 0x00000252
_0807B8D0: .4byte 0x00000251


	thumb_func_start ProcessPauseScreenText
ProcessPauseScreenText: @ 0x0807B8D4
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	ldr r4, _0807B93C @ =0x0200C000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	movs r1, #0
	adds r2, r4, #0
	bl BitFill
	movs r6, #0
	ldr r2, _0807B940 @ =sPauseScreenTextPointers
	ldr r0, _0807B944 @ =0x03000011
	movs r1, #0
	ldrsb r1, [r0, r1]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r0, _0807B948 @ =gEventCounter
	ldrb r0, [r0]
	ldr r1, [r1]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r7, [r0]
	ldrh r2, [r7]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r0
	beq _0807B9D8
	movs r5, #0x80
	lsls r5, r5, #8
	mov sl, r5
	movs r1, #0xfe
	lsls r1, r1, #8
	mov sb, r1
_0807B926:
	movs r5, #1
	adds r1, r0, #0
	ands r1, r2
	cmp r1, sl
	bne _0807B94C
	movs r5, #0xff
	mov r8, r5
	mov r0, r8
	ands r0, r2
	mov r8, r0
	b _0807B9C2
	.align 2, 0
_0807B93C: .4byte 0x0200C000
_0807B940: .4byte sPauseScreenTextPointers
_0807B944: .4byte 0x03000011
_0807B948: .4byte gEventCounter
_0807B94C:
	movs r0, #0x83
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807B95E
	movs r1, #0
	mov r8, r1
	movs r6, #0xff
	ands r6, r2
	b _0807B9C2
_0807B95E:
	cmp r2, sb
	bne _0807B96E
	movs r2, #0
	mov r8, r2
	cmp r6, #0xe0
	bgt _0807B9D8
	movs r6, #0xe0
	movs r5, #0
_0807B96E:
	cmp r5, #0
	beq _0807B9C2
	ldrh r0, [r7]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r6, r0
	cmp r5, #0xe0
	ble _0807B988
	cmp r6, #0xdf
	bgt _0807B988
	movs r6, #0xe0
	b _0807B990
_0807B988:
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807B9D8
_0807B990:
	cmp r6, #0xdf
	ble _0807B99E
	movs r5, #0x80
	lsls r5, r5, #4
	adds r4, r6, #0
	subs r4, #0xe0
	b _0807B9A2
_0807B99E:
	movs r5, #0
	adds r4, r6, #0
_0807B9A2:
	asrs r0, r4, #3
	lsls r0, r0, #5
	adds r5, r5, r0
	movs r3, #7
	ldrh r0, [r7]
	ldr r2, _0807B9E8 @ =0x0200C000
	adds r1, r2, r5
	mov r5, r8
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ands r4, r3
	movs r3, #0
	str r3, [sp]
	adds r3, r4, #0
	bl TextDrawCharacter
_0807B9C2:
	adds r7, #2
	add r6, r8
	ldr r0, _0807B9EC @ =0x000001BF
	cmp r6, r0
	bgt _0807B9D8
	ldrh r2, [r7]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r0
	bne _0807B926
_0807B9D8:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807B9E8: .4byte 0x0200C000
_0807B9EC: .4byte 0x000001BF

	thumb_func_start ProcessEasySleepText
ProcessEasySleepText: @ 0x0807B9F0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	ldr r2, _0807BA80 @ =0x0200D000
	movs r5, #0x80
	lsls r5, r5, #5
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	adds r3, r5, #0
	bl BitFill
	ldr r2, _0807BA84 @ =0x0200E000
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	adds r3, r5, #0
	bl BitFill
	ldr r2, _0807BA88 @ =0x0200F000
	movs r3, #0x80
	lsls r3, r3, #4
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	bl BitFill
	movs r3, #0
_0807BA30:
	ldr r0, _0807BA84 @ =0x0200E000
	mov sl, r0
	cmp r3, #0
	bne _0807BA3C
	ldr r1, _0807BA80 @ =0x0200D000
	mov sl, r1
_0807BA3C:
	ldr r1, _0807BA8C @ =sMessageTextPointers
	ldr r0, _0807BA90 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	adds r0, #0xb4
	ldr r6, [r0]
	movs r7, #0
	ldrh r2, [r6]
	movs r4, #0xff
	lsls r4, r4, #8
	adds r0, r4, #0
	adds r3, #1
	mov sb, r3
	cmp r2, r4
	beq _0807BB24
_0807BA66:
	movs r5, #1
	adds r1, r0, #0
	ands r1, r2
	movs r0, #0x80
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BA94
	movs r1, #0xff
	mov r8, r1
	mov r4, r8
	ands r4, r2
	mov r8, r4
	b _0807BB0E
	.align 2, 0
_0807BA80: .4byte 0x0200D000
_0807BA84: .4byte 0x0200E000
_0807BA88: .4byte 0x0200F000
_0807BA8C: .4byte sMessageTextPointers
_0807BA90: .4byte 0x03000011
_0807BA94:
	movs r0, #0x83
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BAA6
	movs r5, #0
	mov r8, r5
	movs r7, #0xff
	ands r7, r2
	b _0807BB0E
_0807BAA6:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r2, r0
	bne _0807BABA
	movs r1, #0
	mov r8, r1
	cmp r7, #0xe0
	bgt _0807BB24
	movs r7, #0xe0
	movs r5, #0
_0807BABA:
	cmp r5, #0
	beq _0807BB0E
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r7, r0
	cmp r5, #0xe0
	ble _0807BAD4
	cmp r7, #0xdf
	bgt _0807BAD4
	movs r7, #0xe0
	b _0807BADC
_0807BAD4:
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807BB24
_0807BADC:
	cmp r7, #0xdf
	ble _0807BAEA
	movs r5, #0x80
	lsls r5, r5, #4
	adds r4, r7, #0
	subs r4, #0xe0
	b _0807BAEE
_0807BAEA:
	movs r5, #0
	adds r4, r7, #0
_0807BAEE:
	asrs r0, r4, #3
	lsls r0, r0, #5
	adds r5, r5, r0
	movs r3, #7
	ldrh r0, [r6]
	mov r2, sl
	adds r1, r2, r5
	mov r5, r8
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ands r4, r3
	movs r3, #0
	str r3, [sp]
	adds r3, r4, #0
	bl TextDrawCharacter
_0807BB0E:
	adds r6, #2
	add r7, r8
	ldr r0, _0807BB60 @ =0x000001BF
	cmp r7, r0
	bgt _0807BB24
	ldrh r2, [r6]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r1
	bne _0807BA66
_0807BB24:
	mov r3, sb
	cmp r3, #1
	ble _0807BA30
	ldr r2, _0807BB64 @ =0x0200F000
	mov sl, r2
	ldr r1, _0807BB68 @ =sMessageTextPointers
	ldr r0, _0807BB6C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	adds r0, #0xbc
	ldr r6, [r0]
	movs r7, #0
	ldrh r1, [r6]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	beq _0807BBE0
	movs r5, #1
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BB70
	movs r4, #0
	mov r8, r4
	movs r7, #0x70
	b _0807BBB2
	.align 2, 0
_0807BB60: .4byte 0x000001BF
_0807BB64: .4byte 0x0200F000
_0807BB68: .4byte sMessageTextPointers
_0807BB6C: .4byte 0x03000011
_0807BB70:
	ldrh r1, [r6]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807BB80
	movs r5, #0
	mov r8, r5
_0807BB80:
	cmp r5, #0
	beq _0807BBB2
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r7, r0
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807BBE0
	asrs r0, r7, #3
	lsls r5, r0, #5
	movs r3, #7
	ldrh r0, [r6]
	mov r2, sl
	adds r1, r2, r5
	mov r4, r8
	lsls r2, r4, #0x18
	lsrs r2, r2, #0x18
	ands r3, r7
	movs r4, #0
	str r4, [sp]
	bl TextDrawCharacter
_0807BBB2:
	adds r6, #2
	add r7, r8
	ldr r0, _0807BBDC @ =0x000001BF
	cmp r7, r0
	bgt _0807BBE0
	ldrh r1, [r6]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	beq _0807BBE0
	movs r5, #1
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BB70
	movs r5, #0
	mov r8, r5
	cmp r7, #0x70
	bgt _0807BBE0
	movs r7, #0x70
	b _0807BBB2
	.align 2, 0
_0807BBDC: .4byte 0x000001BF
_0807BBE0:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
