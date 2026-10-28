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

