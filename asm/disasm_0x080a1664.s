    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start EndingImageLoadTextOam
EndingImageLoadTextOam: @ 0x080A1664
	push {r4, r5, r6, r7, lr}
	adds r1, r0, #0
	ldr r0, _080A1680 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _080A175C
	cmp r0, #4
	bgt _080A1684
	cmp r0, #3
	beq _080A1692
	b _080A1A28
	.align 2, 0
_080A1680: .4byte 0x03000011
_080A1684:
	cmp r0, #5
	bne _080A168A
	b _080A1828
_080A168A:
	cmp r0, #6
	bne _080A1690
	b _080A195C
_080A1690:
	b _080A1A28
_080A1692:
	cmp r1, #0
	bne _080A16F8
	ldr r1, _080A16F0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x13
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A16F4 @ =sEndingUnk_74de94
	movs r0, #0x95
	lsls r0, r0, #1
	adds r4, r5, r0
	movs r1, #0xb3
	lsls r1, r1, #1
	adds r6, r5, r1
	adds r0, #0x60
	adds r0, r0, r5
	mov ip, r0
_080A16BA:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xc
	ble _080A16BA
	b _080A1B50
	.align 2, 0
_080A16F0: .4byte gNonGameplayRam
_080A16F4: .4byte sEndingUnk_74de94
_080A16F8:
	ldr r1, _080A1754 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x14
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1758 @ =sEndingUnk_74df30
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A171C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xd
	ble _080A171C
	b _080A1B50
	.align 2, 0
_080A1754: .4byte gNonGameplayRam
_080A1758: .4byte sEndingUnk_74df30
_080A175C:
	cmp r1, #0
	bne _080A17C4
	ldr r1, _080A17BC @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x16
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A17C0 @ =sEndingUnk_74e020
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1784:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xf
	ble _080A1784
	b _080A1B50
	.align 2, 0
_080A17BC: .4byte gNonGameplayRam
_080A17C0: .4byte sEndingUnk_74e020
_080A17C4:
	ldr r1, _080A1820 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x1a
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1824 @ =sEndingUnk_74e0e0
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A17E8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x13
	ble _080A17E8
	b _080A1B50
	.align 2, 0
_080A1820: .4byte gNonGameplayRam
_080A1824: .4byte sEndingUnk_74e0e0
_080A1828:
	cmp r1, #0
	bne _080A1890
	ldr r1, _080A1888 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x18
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A188C @ =sEndingUnk_74e218
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1850:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x11
	ble _080A1850
	b _080A1B50
	.align 2, 0
_080A1888: .4byte gNonGameplayRam
_080A188C: .4byte sEndingUnk_74e218
_080A1890:
	cmp r1, #1
	bne _080A18F8
	ldr r1, _080A18F0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x11
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A18F4 @ =sEndingUnk_74e2f0
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A18B8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xa
	ble _080A18B8
	b _080A1B50
	.align 2, 0
_080A18F0: .4byte gNonGameplayRam
_080A18F4: .4byte sEndingUnk_74e2f0
_080A18F8:
	ldr r1, _080A1954 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x17
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1958 @ =sEndingUnk_74e374
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A191C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x10
	ble _080A191C
	b _080A1B50
	.align 2, 0
_080A1954: .4byte gNonGameplayRam
_080A1958: .4byte sEndingUnk_74e374
_080A195C:
	cmp r1, #0
	bne _080A19C4
	ldr r1, _080A19BC @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x15
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A19C0 @ =sEndingUnk_74e488
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1984:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xe
	ble _080A1984
	b _080A1B50
	.align 2, 0
_080A19BC: .4byte gNonGameplayRam
_080A19C0: .4byte sEndingUnk_74e488
_080A19C4:
	ldr r1, _080A1A20 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x19
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1A24 @ =sEndingUnk_74e53c
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A19E8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x12
	ble _080A19E8
	b _080A1B50
	.align 2, 0
_080A1A20: .4byte gNonGameplayRam
_080A1A24: .4byte sEndingUnk_74e53c
_080A1A28:
	cmp r1, #0
	bne _080A1A90
	ldr r1, _080A1A88 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0xf
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1A8C @ =sEndingUnk_74dc90
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1A50:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #8
	ble _080A1A50
	b _080A1B50
	.align 2, 0
_080A1A88: .4byte gNonGameplayRam
_080A1A8C: .4byte sEndingUnk_74dc90
_080A1A90:
	cmp r1, #1
	bne _080A1AF8
	ldr r1, _080A1AF0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x11
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1AF4 @ =sEndingUnk_74dcfc
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1AB8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xa
	ble _080A1AB8
	b _080A1B50
	.align 2, 0
_080A1AF0: .4byte gNonGameplayRam
_080A1AF4: .4byte sEndingUnk_74dcfc
_080A1AF8:
	ldr r1, _080A1B58 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x17
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1B5C @ =sEndingUnk_74dd80
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1B1C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x10
	ble _080A1B1C
_080A1B50:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1B58: .4byte gNonGameplayRam
_080A1B5C: .4byte sEndingUnk_74dd80
