    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NavigationConversationHandler
NavigationConversationHandler: @ 0x0807A3A4
	push {r4, r5, r6, r7, lr}
	bl unk_7b674
	bl NavigationConversionScrollToTarget
	bl unk_7b56c
	bl NavConversationUpdateBottomTextBoxOam
	bl NavConversationUpdateTopTextBoxOam
	movs r7, #0
	ldr r0, _0807A3D4 @ =gNonGameplayRam
	ldrb r0, [r0, #7]
	cmp r0, #0x15
	bls _0807A3C8
	bl _0807AE42
_0807A3C8:
	lsls r0, r0, #2
	ldr r1, _0807A3D8 @ =_0807A3DC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807A3D4: .4byte gNonGameplayRam
_0807A3D8: .4byte _0807A3DC
_0807A3DC: @ jump table
	.4byte _0807A434 @ case 0
	.4byte _0807A468 @ case 1
	.4byte _0807A51A @ case 2
	.4byte _0807A6C0 @ case 3
	.4byte _0807A700 @ case 4
	.4byte _0807A718 @ case 5
	.4byte _0807A76C @ case 6
	.4byte _0807A79E @ case 7
	.4byte _0807A7B0 @ case 8
	.4byte _0807A890 @ case 9
	.4byte _0807A938 @ case 10
	.4byte _0807AA2A @ case 11
	.4byte _0807AA48 @ case 12
	.4byte _0807AA84 @ case 13
	.4byte _0807AAE0 @ case 14
	.4byte _0807AB14 @ case 15
	.4byte _0807AB40 @ case 16
	.4byte _0807ABB4 @ case 17
	.4byte _0807AC28 @ case 18
	.4byte _0807ACAE @ case 19
	.4byte _0807AD6C @ case 20
	.4byte _0807ADE8 @ case 21
_0807A434:
	ldr r4, _0807A454 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r4, #6]
	bl NavigationConversationSetupOam
	ldr r1, _0807A458 @ =0x00000221
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A45C
	movs r0, #4
	strb r0, [r4, #0x1c]
	movs r0, #0x11
	strb r0, [r4, #7]
	bl _0807AE42
	.align 2, 0
_0807A454: .4byte gNonGameplayRam
_0807A458: .4byte 0x00000221
_0807A45C:
	strb r0, [r4, #0x1c]
	ldrb r0, [r4, #7]
	adds r0, #1
	strb r0, [r4, #7]
	bl _0807AE42
_0807A468:
	ldr r1, _0807A4D4 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r3, r1, r2
	ldrh r2, [r3]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r0, r4, #0
	movs r5, #0
	orrs r0, r2
	strh r0, [r3]
	movs r2, #1
	strb r2, [r1, #9]
	strb r2, [r1, #0xb]
	movs r0, #8
	strb r0, [r1, #0x1d]
	strb r5, [r1, #0x1e]
	strb r5, [r1, #0x1f]
	movs r3, #0x88
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	subs r0, #1
	lsls r3, r0, #1
	ldr r4, _0807A4D8 @ =0x00000221
	adds r0, r1, r4
	ldrb r0, [r0]
	adds r4, r1, #0
	cmp r0, #0
	beq _0807A4A6
	adds r3, #1
_0807A4A6:
	ldr r1, _0807A4DC @ =sNavConversationTextPointers
	ldr r0, _0807A4E0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldrh r3, [r0]
	ldr r0, _0807A4E4 @ =0x0000E201
	cmp r3, r0
	bne _0807A4E8
	ldrh r0, [r4, #4]
	movs r1, #2
	orrs r0, r1
	strh r0, [r4, #4]
	strb r2, [r4, #0x18]
	strb r1, [r4, #0x19]
	strb r2, [r4, #0x17]
	b _0807A512
	.align 2, 0
_0807A4D4: .4byte gNonGameplayRam
_0807A4D8: .4byte 0x00000221
_0807A4DC: .4byte sNavConversationTextPointers
_0807A4E0: .4byte 0x03000011
_0807A4E4: .4byte 0x0000E201
_0807A4E8:
	ldr r0, _0807A500 @ =0x0000E202
	cmp r3, r0
	bne _0807A504
	ldrh r0, [r4, #4]
	movs r1, #4
	orrs r0, r1
	strh r0, [r4, #4]
	strb r2, [r4, #0x18]
	movs r0, #2
	strb r0, [r4, #0x19]
	strb r0, [r4, #0x17]
	b _0807A512
	.align 2, 0
_0807A500: .4byte 0x0000E202
_0807A504:
	ldrh r0, [r4, #4]
	movs r1, #1
	orrs r0, r1
	strh r0, [r4, #4]
	strb r5, [r4, #0x18]
	strb r1, [r4, #0x19]
	strb r5, [r4, #0x17]
_0807A512:
	ldrb r0, [r4, #7]
	adds r0, #1
	movs r1, #0
	b _0807AC3E
_0807A51A:
	ldr r1, _0807A584 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0x1b]
	ldrb r0, [r1, #0x1c]
	adds r4, r1, #0
	cmp r0, #1
	bne _0807A5B8
	ldr r0, _0807A588 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	beq _0807A590
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0807A59C
	ldr r1, _0807A58C @ =0x00000241
	adds r0, r4, r1
	ldrb r5, [r0]
	cmp r5, #0
	bne _0807A590
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r5, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r5, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r5, [r0]
	movs r0, #0
	bl TextClearGraphics
	movs r0, #3
	strb r0, [r4, #7]
	strb r5, [r4, #6]
	bl _0807AE42
	.align 2, 0
_0807A584: .4byte gNonGameplayRam
_0807A588: .4byte gChangedInput
_0807A58C: .4byte 0x00000241
_0807A590:
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0807A5F2
_0807A59C:
	ldrh r1, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0807A5AE
	bl _0807AE42
_0807A5AE:
	adds r0, r2, #0
	orrs r0, r1
	strh r0, [r4, #4]
	bl _0807AE42
_0807A5B8:
	cmp r0, #2
	bne _0807A5E6
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _0807A5F2
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r2, r4, #0
	adds r2, #0x25
	movs r0, #1
	strb r0, [r2]
	strb r0, [r4, #0x1a]
	strb r1, [r4, #0x1b]
	movs r0, #8
	strb r0, [r4, #7]
	strb r1, [r4, #6]
	b _0807A5F2
_0807A5E6:
	cmp r0, #6
	bne _0807A5EE
	movs r7, #1
	b _0807A5F2
_0807A5EE:
	bl NavigationConversationProcessText
_0807A5F2:
	ldr r3, _0807A628 @ =gNonGameplayRam
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	adds r0, r1, #0
	adds r0, #0x36
	ldrb r0, [r0]
	cmp r0, #3
	bne _0807A630
	movs r0, #0x74
	strh r0, [r1, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	ldr r2, _0807A62C @ =sNavConversationTextBoxCursorYPositions
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r2, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	bl _0807AE42
	.align 2, 0
_0807A628: .4byte gNonGameplayRam
_0807A62C: .4byte sNavConversationTextBoxCursorYPositions
_0807A630:
	movs r2, #0
	strh r2, [r1, #0x2e]
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	strh r2, [r0, #0x2c]
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r1, r3, #0
	adds r1, #0x12
	adds r0, r0, r1
	ldrh r2, [r0]
	cmp r2, #0xdf
	bls _0807A68C
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	ldr r4, _0807A684 @ =0x0000FF28
	adds r1, r2, r4
	ldrh r2, [r0, #0x2e]
	adds r1, r1, r2
	strh r1, [r0, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	ldr r2, _0807A688 @ =sNavConversationTextBoxCursorYPositions
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	adds r0, #0x10
	ldrh r3, [r1, #0x2c]
	adds r0, r0, r3
	strh r0, [r1, #0x2c]
	bl _0807AE42
	.align 2, 0
_0807A684: .4byte 0x0000FF28
_0807A688: .4byte sNavConversationTextBoxCursorYPositions
_0807A68C:
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	adds r1, r2, #0
	adds r1, #8
	ldrh r4, [r0, #0x2e]
	adds r1, r1, r4
	strh r1, [r0, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r2, r0, #1
	adds r2, r2, r0
	lsls r2, r2, #2
	adds r2, r2, r3
	ldr r0, _0807A6BC @ =sNavConversationTextBoxCursorYPositions
	ldrb r1, [r3, #0x18]
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r0, [r2, #0x2c]
	ldrb r1, [r1]
	adds r0, r0, r1
	strh r0, [r2, #0x2c]
	b _0807AE42
	.align 2, 0
_0807A6BC: .4byte sNavConversationTextBoxCursorYPositions
_0807A6C0:
	ldr r1, _0807A6F4 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0x1b]
	movs r2, #0x88
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r2, _0807A6F8 @ =gPreviousNavigationConversation
	ldrb r0, [r0]
	ldrb r3, [r2]
	cmp r0, r3
	beq _0807A6E6
	strb r0, [r2]
	ldr r4, _0807A6FC @ =0x00000221
	adds r0, r1, r4
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807A6E6
	bl SoundEventUpdateForNavConversation
_0807A6E6:
	ldr r0, _0807A6F4 @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r1, #1
	movs r2, #0
	strb r1, [r0, #7]
	strb r2, [r0, #6]
	b _0807AE42
	.align 2, 0
_0807A6F4: .4byte gNonGameplayRam
_0807A6F8: .4byte gPreviousNavigationConversation
_0807A6FC: .4byte 0x00000221
_0807A700:
	ldr r2, _0807A714 @ =gNonGameplayRam
	ldrb r0, [r2, #6]
	cmp r0, #8
	bhi _0807A70A
	b _0807AE42
_0807A70A:
	ldrb r0, [r2, #7]
	adds r0, #1
	movs r1, #0
	b _0807A798
	.align 2, 0
_0807A714: .4byte gNonGameplayRam
_0807A718:
	ldr r3, _0807A768 @ =gNonGameplayRam
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r3, r0
	ldrh r0, [r2]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r1, r4, #0
	eors r0, r1
	strh r0, [r2]
	ldrh r1, [r3, #4]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0807A73C
	movs r0, #0x40
	eors r0, r1
	strh r0, [r3, #4]
_0807A73C:
	ldrh r1, [r3, #4]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807A74C
	movs r0, #8
	eors r0, r1
	strh r0, [r3, #4]
_0807A74C:
	ldrh r1, [r3, #4]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807A75C
	movs r0, #0x10
	eors r0, r1
	strh r0, [r3, #4]
_0807A75C:
	ldrb r0, [r3, #7]
	adds r0, #1
	strb r0, [r3, #7]
	movs r0, #0
	strb r0, [r3, #6]
	b _0807AE42
	.align 2, 0
_0807A768: .4byte gNonGameplayRam
_0807A76C:
	ldr r2, _0807A790 @ =gNonGameplayRam
	ldrh r1, [r2, #4]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _0807A78C
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0807A78C
	movs r0, #4
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _0807A794
_0807A78C:
	movs r0, #0
	b _0807AE44
	.align 2, 0
_0807A790: .4byte gNonGameplayRam
_0807A794:
	ldrb r0, [r2, #7]
	adds r0, #1
_0807A798:
	strb r0, [r2, #7]
	strb r1, [r2, #6]
	b _0807AE42
_0807A79E:
	movs r7, #1
	ldr r1, _0807A7AC @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #7]
	strb r0, [r1, #6]
	b _0807AE42
	.align 2, 0
_0807A7AC: .4byte gNonGameplayRam
_0807A7B0:
	ldr r5, _0807A818 @ =gNonGameplayRam
	adds r6, r5, #0
	adds r6, #0x24
	ldrb r4, [r6]
	cmp r4, #0
	bne _0807A824
	ldr r0, _0807A81C @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	bne _0807A7CA
	b _0807AE42
_0807A7CA:
	ldr r0, _0807A820 @ =0x00000203
	bl SoundPlay
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	strb r4, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r4, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r4, [r0]
	movs r0, #1
	bl TextClearGraphics
	movs r0, #1
	strb r0, [r6]
	movs r0, #3
	strb r0, [r5, #0x1c]
	adds r0, r5, #0
	adds r0, #0x20
	strb r4, [r0]
	adds r0, #1
	strb r4, [r0]
	strh r4, [r5, #0x22]
	b _0807AE42
	.align 2, 0
_0807A818: .4byte gNonGameplayRam
_0807A81C: .4byte gChangedInput
_0807A820: .4byte 0x00000203
_0807A824:
	cmp r4, #2
	bne _0807A832
	movs r1, #0
	movs r0, #9
	strb r0, [r5, #7]
	strb r1, [r5, #6]
	b _0807AE42
_0807A832:
	movs r0, #0
	bl unk_7a0fc
	cmp r0, #0
	bne _0807A83E
	b _0807AE42
_0807A83E:
	movs r3, #0
	movs r2, #2
	strb r2, [r6]
	movs r0, #1
	strb r0, [r5, #0x1a]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r3, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	movs r1, #0x34
	strh r1, [r0, #0x2e]
	b _0807AE42
_0807A890:
	movs r3, #0
	ldr r2, _0807A8C8 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r5, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldr r0, _0807A8CC @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	beq _0807A8D0
	adds r5, r4, #0
	adds r5, #0x25
	ldrb r0, [r5]
	movs r2, #1
	eors r0, r2
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r3, r1, #0x1f
	strb r2, [r5]
	b _0807A8F8
	.align 2, 0
_0807A8C8: .4byte gNonGameplayRam
_0807A8CC: .4byte gChangedInput
_0807A8D0:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807A8E8
	adds r1, r4, #0
	adds r1, #0x25
	ldrb r0, [r1]
	cmp r0, #0
	beq _0807A8E4
	movs r3, #1
_0807A8E4:
	strb r5, [r1]
	b _0807A8F8
_0807A8E8:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807A8F8
	movs r3, #2
	movs r0, #0xa
	strb r0, [r4, #7]
	strb r5, [r4, #6]
_0807A8F8:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A910
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x34
	b _0807A91C
_0807A910:
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x84
_0807A91C:
	strh r0, [r1, #0x2e]
	cmp r3, #1
	bne _0807A924
	b _0807AD3E
_0807A924:
	cmp r3, #2
	beq _0807A92A
	b _0807AE42
_0807A92A:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A936
	b _0807AD56
_0807A936:
	b _0807AD60
_0807A938:
	ldr r2, _0807A994 @ =gNonGameplayRam
	ldrh r1, [r2, #4]
	movs r0, #0xc0
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	bne _0807AA18
	movs r0, #0x10
	strb r0, [r4, #7]
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r2, [r0]
	cmp r2, #0
	bne _0807A9DA
	ldr r0, _0807A998 @ =0x03000031
	ldrb r1, [r0]
	movs r3, #0x84
	lsls r3, r3, #2
	adds r0, r4, r3
	strb r1, [r0]
	ldr r0, _0807A99C @ =0x03000032
	ldrb r1, [r0]
	adds r3, #1
	adds r0, r4, r3
	strb r1, [r0]
	ldr r1, _0807A9A0 @ =0x00000212
	adds r0, r4, r1
	ldr r1, _0807A9A4 @ =gCurrentArea
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0807A9A8
	movs r0, #0xb
	strb r0, [r4, #7]
	subs r3, #0x5b
	adds r0, r4, r3
	strb r2, [r0]
	movs r1, #0xda
	lsls r1, r1, #1
	adds r0, r4, r1
	strb r2, [r0]
	subs r3, #1
	adds r0, r4, r3
	strb r2, [r0]
	b _0807A9B8
	.align 2, 0
_0807A994: .4byte gNonGameplayRam
_0807A998: .4byte 0x03000031
_0807A99C: .4byte 0x03000032
_0807A9A0: .4byte 0x00000212
_0807A9A4: .4byte gCurrentArea
_0807A9A8:
	movs r1, #0xd5
	lsls r1, r1, #1
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A9B8
	movs r0, #0xf
	strb r0, [r4, #7]
_0807A9B8:
	movs r2, #0xd5
	lsls r2, r2, #1
	adds r0, r4, r2
	movs r1, #0
	strb r1, [r0]
	movs r3, #0xd4
	lsls r3, r3, #1
	adds r0, r4, r3
	strb r1, [r0]
	subs r2, #1
	adds r0, r4, r2
	strb r1, [r0]
	movs r2, #0
	strh r1, [r4, #0xc]
	adds r3, #0x71
	adds r0, r4, r3
	strb r2, [r0]
_0807A9DA:
	movs r0, #1
	bl TextClearGraphics
	ldr r2, _0807AA14 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x36
	movs r3, #0
	strb r3, [r0]
	movs r0, #1
	strb r0, [r2, #0x1a]
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	adds r1, r2, #0
	adds r1, #0x12
	adds r0, r0, r1
	movs r4, #0
	strh r3, [r0]
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	subs r1, #4
	adds r0, r0, r1
	strh r3, [r0]
	strb r4, [r2, #0x1c]
	b _0807AE40
	.align 2, 0
_0807AA14: .4byte gNonGameplayRam
_0807AA18:
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _0807AA22
	b _0807AE42
_0807AA22:
	movs r0, #0x40
	eors r0, r1
	strh r0, [r4, #4]
	b _0807AE42
_0807AA2A:
	ldr r1, _0807AA44 @ =gNonGameplayRam
	movs r0, #0x94
	lsls r0, r0, #2
	adds r4, r1, r0
	ldrb r2, [r4]
	movs r0, #1
	movs r3, #0
	orrs r0, r2
	strb r0, [r4]
	strb r3, [r1, #6]
	movs r0, #0xc
	strb r0, [r1, #7]
	b _0807AE42
	.align 2, 0
_0807AA44: .4byte gNonGameplayRam
_0807AA48:
	ldr r5, _0807AA78 @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r1, [r0]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _0807AA5C
	b _0807AE42
_0807AA5C:
	ldr r0, _0807AA7C @ =gCurrentArea
	ldrb r1, [r0]
	ldr r2, _0807AA80 @ =0x00000212
	adds r0, r5, r2
	movs r4, #0
	strb r1, [r0]
	movs r0, #1
	bl unk_75988
	strb r4, [r5, #6]
	movs r0, #0xd
	strb r0, [r5, #7]
	b _0807AE42
	.align 2, 0
_0807AA78: .4byte gNonGameplayRam
_0807AA7C: .4byte gCurrentArea
_0807AA80: .4byte 0x00000212
_0807AA84:
	ldr r6, _0807AAC8 @ =gNonGameplayRam
	ldrb r0, [r6, #6]
	cmp r0, #4
	bhi _0807AA8E
	b _0807AE42
_0807AA8E:
	ldr r3, _0807AACC @ =0x00000212
	adds r4, r6, r3
	ldrb r0, [r4]
	ldr r5, _0807AAD0 @ =0x02034000
	adds r1, r5, #0
	bl MinimapGetData
	ldrb r0, [r4]
	bl MinimapSetVisitedTilesAndCollectedItems
	ldr r1, _0807AAD4 @ =0x040000D4
	str r5, [r1]
	ldr r0, _0807AAD8 @ =0x0600E000
	str r0, [r1, #4]
	ldr r0, _0807AADC @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r1, #0
	movs r0, #0xe
	strb r0, [r6, #7]
	strb r1, [r6, #6]
	movs r4, #0x94
	lsls r4, r4, #2
	adds r2, r6, r4
	ldrb r1, [r2]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2]
	b _0807AE42
	.align 2, 0
_0807AAC8: .4byte gNonGameplayRam
_0807AACC: .4byte 0x00000212
_0807AAD0: .4byte 0x02034000
_0807AAD4: .4byte 0x040000D4
_0807AAD8: .4byte 0x0600E000
_0807AADC: .4byte 0x80000400
_0807AAE0:
	ldr r2, _0807AB10 @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r1, [r0]
	cmp r1, #0
	beq _0807AAF0
	b _0807AE42
_0807AAF0:
	movs r4, #0xdb
	lsls r4, r4, #1
	adds r3, r2, r4
	movs r0, #1
	strb r0, [r3]
	movs r3, #0xda
	lsls r3, r3, #1
	adds r0, r2, r3
	strb r1, [r0]
	subs r4, #1
	adds r0, r2, r4
	strb r1, [r0]
	strb r1, [r2, #6]
	movs r0, #0x10
	strb r0, [r2, #7]
	b _0807AE42
	.align 2, 0
_0807AB10: .4byte gNonGameplayRam
_0807AB14:
	ldr r4, _0807AB38 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r0, [r0]
	ldr r2, _0807AB3C @ =0x00000211
	adds r1, r4, r2
	ldrb r1, [r1]
	bl NavigationConversationScrollMapToDestination
	cmp r0, #0
	bne _0807AB2E
	b _0807AE42
_0807AB2E:
	movs r0, #0
	strb r0, [r4, #6]
	movs r0, #0x10
	strb r0, [r4, #7]
	b _0807AE42
	.align 2, 0
_0807AB38: .4byte gNonGameplayRam
_0807AB3C: .4byte 0x00000211
_0807AB40:
	ldr r4, _0807ABAC @ =gNonGameplayRam
	ldrb r0, [r4, #6]
	cmp r0, #0x10
	bhi _0807AB4A
	b _0807AE42
_0807AB4A:
	movs r0, #0
	bl NavigationConversationUpdateTarget
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r3, #0
	movs r1, #8
	strh r1, [r0, #0x2e]
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	ldr r2, _0807ABB0 @ =sNavConversationTextBoxCursorYPositions
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r3, [r0]
	movs r0, #1
	strb r0, [r4, #7]
	strb r3, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807ABAC: .4byte gNonGameplayRam
_0807ABB0: .4byte sNavConversationTextBoxCursorYPositions
_0807ABB4:
	ldr r5, _0807AC24 @ =gNonGameplayRam
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r1, r5, r3
	ldrh r3, [r1]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r0, r4, #0
	movs r2, #0
	movs r4, #0
	orrs r0, r3
	strh r0, [r1]
	movs r0, #8
	strb r0, [r5, #0x1d]
	strb r2, [r5, #0x1e]
	strb r2, [r5, #0x1f]
	ldrh r0, [r5, #4]
	movs r1, #1
	orrs r0, r1
	strh r0, [r5, #4]
	strb r2, [r5, #0x18]
	strb r1, [r5, #0x19]
	strb r2, [r5, #0x17]
	adds r0, r5, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r0, #0x1e
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r2, [r0]
	adds r0, r5, #0
	adds r0, #0x20
	strb r2, [r0]
	adds r0, #1
	strb r2, [r0]
	strh r4, [r5, #0x22]
	movs r0, #5
	strb r0, [r5, #0x1c]
	ldrb r0, [r5, #7]
	adds r0, #1
	strb r0, [r5, #7]
	strb r2, [r5, #6]
	b _0807AE42
	.align 2, 0
_0807AC24: .4byte gNonGameplayRam
_0807AC28:
	ldr r4, _0807AC44 @ =gNonGameplayRam
	adds r5, r4, #0
	adds r5, #0x24
	ldrb r0, [r5]
	cmp r0, #0
	bne _0807AC36
	b _0807AE42
_0807AC36:
	cmp r0, #2
	bne _0807AC48
	movs r1, #0
	movs r0, #0x13
_0807AC3E:
	strb r0, [r4, #7]
	strb r1, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807AC44: .4byte gNonGameplayRam
_0807AC48:
	movs r0, #1
	bl unk_7a0fc
	cmp r0, #0
	bne _0807AC54
	b _0807AE42
_0807AC54:
	movs r3, #0
	movs r2, #2
	strb r2, [r5]
	movs r0, #1
	strb r0, [r4, #0x1a]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r2, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r1, #0x84
	strh r1, [r0, #0x2e]
	adds r0, r4, #0
	adds r0, #0x25
	strb r2, [r0]
	b _0807AE42
_0807ACAE:
	movs r3, #0
	ldr r2, _0807ACE4 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r5, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldr r0, _0807ACE8 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	beq _0807ACEC
	adds r5, r4, #0
	adds r5, #0x25
	ldrb r0, [r5]
	movs r2, #1
	eors r0, r2
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r3, r1, #0x1f
	strb r2, [r5]
	b _0807AD14
	.align 2, 0
_0807ACE4: .4byte gNonGameplayRam
_0807ACE8: .4byte gChangedInput
_0807ACEC:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807AD04
	adds r1, r4, #0
	adds r1, #0x25
	ldrb r0, [r1]
	cmp r0, #0
	beq _0807AD00
	movs r3, #1
_0807AD00:
	strb r5, [r1]
	b _0807AD14
_0807AD04:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807AD14
	movs r3, #2
	movs r0, #0x14
	strb r0, [r4, #7]
	strb r5, [r4, #6]
_0807AD14:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807AD2C
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x34
	b _0807AD38
_0807AD2C:
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x84
_0807AD38:
	strh r0, [r1, #0x2e]
	cmp r3, #1
	bne _0807AD48
_0807AD3E:
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _0807AE42
_0807AD48:
	cmp r3, #2
	bne _0807AE42
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807AD60
_0807AD56:
	movs r0, #0x81
	lsls r0, r0, #2
	bl SoundPlay
	b _0807AE42
_0807AD60:
	ldr r0, _0807AD68 @ =0x00000205
	bl SoundPlay
	b _0807AE42
	.align 2, 0
_0807AD68: .4byte 0x00000205
_0807AD6C:
	ldr r4, _0807ADDC @ =gNonGameplayRam
	movs r5, #0
	movs r0, #0x15
	strb r0, [r4, #7]
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807ADA4
	ldr r1, _0807ADE0 @ =gPreviousNavigationConversation
	movs r0, #0xff
	strb r0, [r1]
	movs r1, #0xd5
	lsls r1, r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r2, #0xd4
	lsls r2, r2, #1
	adds r0, r4, r2
	strb r5, [r0]
	ldr r3, _0807ADE4 @ =0x000001A9
	adds r0, r4, r3
	strb r5, [r0]
	movs r1, #0
	strh r5, [r4, #0xc]
	adds r2, #0x71
	adds r0, r4, r2
	strb r1, [r0]
_0807ADA4:
	movs r0, #1
	bl TextClearGraphics
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r5, [r0]
	movs r0, #1
	strb r0, [r4, #0x1a]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r1, r4, #0
	adds r1, #0x12
	adds r0, r0, r1
	movs r2, #0
	strh r5, [r0]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	subs r1, #4
	adds r0, r0, r1
	strh r5, [r0]
	strb r2, [r4, #0x1c]
	strb r2, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807ADDC: .4byte gNonGameplayRam
_0807ADE0: .4byte gPreviousNavigationConversation
_0807ADE4: .4byte 0x000001A9
_0807ADE8:
	ldr r2, _0807AE4C @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r4, #0
	movs r1, #8
	strh r1, [r0, #0x2e]
	ldrb r0, [r2, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r3, _0807AE50 @ =sNavConversationTextBoxCursorYPositions
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r3
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x34
	strb r4, [r0]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x35
	strb r4, [r0]
	movs r0, #1
	strb r0, [r2, #7]
_0807AE40:
	strb r4, [r2, #6]
_0807AE42:
	adds r0, r7, #0
_0807AE44:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807AE4C: .4byte gNonGameplayRam
_0807AE50: .4byte sNavConversationTextBoxCursorYPositions
