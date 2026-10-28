    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start FileSelectProcessDeleteArrow
FileSelectProcessDeleteArrow: @ 0x0809FC90
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	movs r7, #0
	movs r6, #0
	ldrb r0, [r4, #9]
	cmp r0, #0
	bne _0809FD7C
	movs r0, #1
	strb r0, [r4, #5]
	ldr r1, _0809FCD0 @ =gChangedInput
	ldrh r2, [r1]
	movs r0, #0x40
	ands r0, r2
	mov ip, r1
	cmp r0, #0
	beq _0809FCDC
	ldr r0, _0809FCD4 @ =gNonGameplayRam
	ldrb r1, [r0, #0xf]
	adds r5, r0, #0
	cmp r1, #0
	beq _0809FCC0
	subs r0, r1, #1
	strb r0, [r5, #0xf]
	movs r6, #1
_0809FCC0:
	ldrb r0, [r5, #0xf]
	ldrb r1, [r5, #0xd]
	cmp r1, r0
	bne _0809FD12
	cmp r1, #0
	bne _0809FCD8
	adds r0, #1
	b _0809FD00
	.align 2, 0
_0809FCD0: .4byte gChangedInput
_0809FCD4: .4byte gNonGameplayRam
_0809FCD8:
	subs r0, #1
	b _0809FD0E
_0809FCDC:
	movs r0, #0x80
	ands r0, r2
	ldr r5, _0809FD08 @ =gNonGameplayRam
	cmp r0, #0
	beq _0809FD12
	ldrb r0, [r5, #0xf]
	cmp r0, #1
	bhi _0809FCF2
	adds r0, #1
	strb r0, [r5, #0xf]
	movs r6, #1
_0809FCF2:
	ldrb r0, [r5, #0xf]
	ldrb r1, [r5, #0xd]
	cmp r1, r0
	bne _0809FD12
	cmp r1, #2
	bne _0809FD0C
	subs r0, #1
_0809FD00:
	strb r0, [r5, #0xf]
	movs r6, #0
	b _0809FD12
	.align 2, 0
_0809FD08: .4byte gNonGameplayRam
_0809FD0C:
	adds r0, #1
_0809FD0E:
	strb r0, [r5, #0xf]
	movs r6, #1
_0809FD12:
	ldr r3, _0809FD70 @ =sFileSelectUnk_79e8a4
	adds r2, r5, #0
	ldrb r1, [r2, #0xd]
	lsls r0, r1, #1
	adds r0, r0, r1
	ldrb r2, [r2, #0xf]
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r0, r0, r3
	ldr r0, [r0]
	str r0, [r4, #0x14]
	mov r0, ip
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	bne _0809FD88
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	beq _0809FDA4
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	movs r0, #1
	strb r0, [r4, #9]
	ldr r2, _0809FD74 @ =0x03000B94
	ldrb r1, [r5, #0xf]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r2, r0, r2
	movs r0, #0x10
	ldrsb r0, [r2, r0]
	cmp r0, #1
	beq _0809FD6A
	movs r0, #0x11
	ldrsb r0, [r2, r0]
	cmp r0, #1
	beq _0809FD6A
	ldrb r0, [r2]
	cmp r0, #1
	bne _0809FD78
_0809FD6A:
	movs r7, #1
	b _0809FDA4
	.align 2, 0
_0809FD70: .4byte sFileSelectUnk_79e8a4
_0809FD74: .4byte 0x03000B94
_0809FD78:
	movs r7, #2
	b _0809FDA4
_0809FD7C:
	cmp r0, #1
	bne _0809FD94
	ldr r0, _0809FD90 @ =gNonGameplayRam
	ldrb r0, [r0, #0xc]
	cmp r0, #0xb
	bne _0809FDA4
_0809FD88:
	movs r0, #0x64
	strb r0, [r4, #9]
	b _0809FDA4
	.align 2, 0
_0809FD90: .4byte gNonGameplayRam
_0809FD94:
	ldr r0, _0809FDBC @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0x11
	bne _0809FDA4
	strb r7, [r4, #7]
	strb r7, [r4, #6]
	strb r7, [r4, #9]
_0809FDA4:
	cmp r6, #0
	beq _0809FDAE
	ldr r0, _0809FDC0 @ =0x000001F9
	bl SoundPlay
_0809FDAE:
	cmp r7, #1
	bne _0809FDC8
	ldr r0, _0809FDC4 @ =0x000001FB
	bl SoundPlay
	b _0809FDD2
	.align 2, 0
_0809FDBC: .4byte gNonGameplayRam
_0809FDC0: .4byte 0x000001F9
_0809FDC4: .4byte 0x000001FB
_0809FDC8:
	cmp r7, #2
	bne _0809FDD2
	ldr r0, _0809FDD8 @ =0x00000207
	bl SoundPlay
_0809FDD2:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809FDD8: .4byte 0x00000207

	thumb_func_start unk_9fddc
unk_9fddc: @ 0x0809FDDC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _0809FEAC
	ldr r3, _0809FE1C @ =gNonGameplayRam
	ldrb r0, [r3, #0x10]
	cmp r0, #0
	bne _0809FE2C
	ldr r0, _0809FE20 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0809FE58
	movs r0, #1
	strb r0, [r3, #0x10]
	ldr r1, _0809FE24 @ =sFileSelectUnk_73dbb0
	ldr r0, _0809FE28 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r1, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	strh r0, [r4]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _0809FE58
	.align 2, 0
_0809FE1C: .4byte gNonGameplayRam
_0809FE20: .4byte gChangedInput
_0809FE24: .4byte sFileSelectUnk_73dbb0
_0809FE28: .4byte 0x03000011
_0809FE2C:
	cmp r0, #1
	bne _0809FE58
	ldr r0, _0809FE80 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _0809FE58
	strb r2, [r3, #0x10]
	ldr r1, _0809FE84 @ =sFileSelectUnk_73dbb0
	ldr r0, _0809FE88 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	strh r0, [r4]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
_0809FE58:
	ldr r0, _0809FE80 @ =gChangedInput
	ldrh r2, [r0]
	movs r0, #2
	ands r0, r2
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _0809FED6
	movs r0, #9
	ands r0, r2
	cmp r0, #0
	beq _0809FEF8
	strb r1, [r4, #7]
	strb r1, [r4, #6]
	ldr r0, _0809FE8C @ =gNonGameplayRam
	ldrb r0, [r0, #0x10]
	cmp r0, #0
	bne _0809FE94
	ldr r0, _0809FE90 @ =0x00000207
	b _0809FE96
	.align 2, 0
_0809FE80: .4byte gChangedInput
_0809FE84: .4byte sFileSelectUnk_73dbb0
_0809FE88: .4byte 0x03000011
_0809FE8C: .4byte gNonGameplayRam
_0809FE90: .4byte 0x00000207
_0809FE94:
	ldr r0, _0809FEA4 @ =0x000001FB
_0809FE96:
	bl SoundPlay
	ldr r0, _0809FEA8 @ =sFileSelectUnk_740b70
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _0809FEF8
	.align 2, 0
_0809FEA4: .4byte 0x000001FB
_0809FEA8: .4byte sFileSelectUnk_740b70
_0809FEAC:
	cmp r2, #1
	bne _0809FEE0
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _0809FEC8
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809FEC8
	strb r1, [r4, #7]
_0809FEC8:
	ldr r0, _0809FEDC @ =gNonGameplayRam
	ldrb r0, [r0, #0xc]
	cmp r0, #0xb
	bne _0809FEF8
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
_0809FED6:
	movs r0, #0x64
	strb r0, [r4, #9]
	b _0809FEF8
	.align 2, 0
_0809FEDC: .4byte gNonGameplayRam
_0809FEE0:
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _0809FEF8
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809FEF8
	strb r1, [r4, #7]
_0809FEF8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_9ff00
unk_9ff00: @ 0x0809FF00
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _0809FFD0
	ldr r3, _0809FF40 @ =gNonGameplayRam
	ldrb r0, [r3, #0x10]
	cmp r0, #0
	bne _0809FF50
	ldr r0, _0809FF44 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0809FF7C
	movs r0, #1
	strb r0, [r3, #0x10]
	ldr r1, _0809FF48 @ =sFileSelectUnk_73dbbe
	ldr r0, _0809FF4C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r1, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	strh r0, [r4]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _0809FF7C
	.align 2, 0
_0809FF40: .4byte gNonGameplayRam
_0809FF44: .4byte gChangedInput
_0809FF48: .4byte sFileSelectUnk_73dbbe
_0809FF4C: .4byte 0x03000011
_0809FF50:
	cmp r0, #1
	bne _0809FF7C
	ldr r0, _0809FFA8 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _0809FF7C
	strb r2, [r3, #0x10]
	ldr r1, _0809FFAC @ =sFileSelectUnk_73dbbe
	ldr r0, _0809FFB0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	strh r0, [r4]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
_0809FF7C:
	ldr r0, _0809FFA8 @ =gChangedInput
	ldrh r2, [r0]
	movs r0, #2
	ands r0, r2
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _0809FFFA
	movs r0, #9
	ands r0, r2
	cmp r0, #0
	beq _080A001C
	strb r1, [r4, #7]
	strb r1, [r4, #6]
	ldr r0, _0809FFB4 @ =gNonGameplayRam
	ldrb r0, [r0, #0x10]
	cmp r0, #0
	bne _0809FFB8
	movs r0, #0x82
	lsls r0, r0, #2
	b _0809FFBA
	.align 2, 0
_0809FFA8: .4byte gChangedInput
_0809FFAC: .4byte sFileSelectUnk_73dbbe
_0809FFB0: .4byte 0x03000011
_0809FFB4: .4byte gNonGameplayRam
_0809FFB8:
	ldr r0, _0809FFC8 @ =0x000001FB
_0809FFBA:
	bl SoundPlay
	ldr r0, _0809FFCC @ =sFileSelectUnk_740b70
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _080A001C
	.align 2, 0
_0809FFC8: .4byte 0x000001FB
_0809FFCC: .4byte sFileSelectUnk_740b70
_0809FFD0:
	cmp r2, #1
	bne _080A0004
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _0809FFEC
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809FFEC
	strb r1, [r4, #7]
_0809FFEC:
	ldr r0, _080A0000 @ =gNonGameplayRam
	ldrb r0, [r0, #0xc]
	cmp r0, #0xb
	bne _080A001C
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
_0809FFFA:
	movs r0, #0x64
	strb r0, [r4, #9]
	b _080A001C
	.align 2, 0
_080A0000: .4byte gNonGameplayRam
_080A0004:
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A001C
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A001C
	strb r1, [r4, #7]
_080A001C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FileSelectProcessAudioLogos
FileSelectProcessAudioLogos: @ 0x080A0024
	push {lr}
	adds r2, r0, #0
	ldr r0, _080A0064 @ =gNonGameplayRam
	ldrb r0, [r0, #0xd]
	cmp r0, #3
	bne _080A00B8
	ldrb r3, [r2, #9]
	cmp r3, #0
	bne _080A0078
	ldr r0, _080A0068 @ =sFileSelectUnk_7407c0
	str r0, [r2, #0x14]
	ldr r0, _080A006C @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A00DA
	movs r0, #1
	strb r0, [r2, #9]
	ldr r0, _080A0070 @ =sFileSelectUnk_7407d0
	str r0, [r2, #0x14]
	strb r3, [r2, #7]
	strb r3, [r2, #6]
	movs r0, #0x80
	lsls r0, r0, #0x12
	bl DoSoundAction
	ldr r0, _080A0074 @ =0x00000206
	bl SoundPlay
	b _080A00DA
	.align 2, 0
_080A0064: .4byte gNonGameplayRam
_080A0068: .4byte sFileSelectUnk_7407c0
_080A006C: .4byte gChangedInput
_080A0070: .4byte sFileSelectUnk_7407d0
_080A0074: .4byte 0x00000206
_080A0078:
	cmp r3, #1
	bne _080A00DA
	ldr r0, _080A00AC @ =sFileSelectUnk_7407d0
	str r0, [r2, #0x14]
	ldr r0, _080A00B0 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080A00DA
	movs r1, #0
	strb r1, [r2, #9]
	ldr r0, _080A00B4 @ =sFileSelectUnk_7407c0
	str r0, [r2, #0x14]
	strb r1, [r2, #7]
	strb r1, [r2, #6]
	movs r0, #0x80
	lsls r0, r0, #0x11
	bl DoSoundAction
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _080A00DA
	.align 2, 0
_080A00AC: .4byte sFileSelectUnk_7407d0
_080A00B0: .4byte gChangedInput
_080A00B4: .4byte sFileSelectUnk_7407c0
_080A00B8:
	ldrb r1, [r2, #9]
	cmp r1, #0
	bne _080A00CC
	ldr r0, _080A00C8 @ =sFileSelectUnk_7407e0
	str r0, [r2, #0x14]
	strb r1, [r2, #7]
	strb r1, [r2, #6]
	b _080A00DA
	.align 2, 0
_080A00C8: .4byte sFileSelectUnk_7407e0
_080A00CC:
	cmp r1, #1
	bne _080A00DA
	ldr r0, _080A00E0 @ =sFileSelectUnk_7407f0
	str r0, [r2, #0x14]
	movs r0, #0
	strb r0, [r2, #7]
	strb r0, [r2, #6]
_080A00DA:
	pop {r0}
	bx r0
	.align 2, 0
_080A00E0: .4byte sFileSelectUnk_7407f0

	thumb_func_start FileSelectProcessAudioSelect
FileSelectProcessAudioSelect: @ 0x080A00E4
	push {lr}
	adds r2, r0, #0
	ldr r0, _080A0110 @ =gNonGameplayRam
	ldrb r0, [r0, #0xd]
	cmp r0, #3
	bne _080A0138
	movs r3, #1
	strb r3, [r2, #5]
	ldrb r0, [r2, #9]
	cmp r0, #0
	bne _080A0118
	ldr r0, _080A0114 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A0140
	strb r3, [r2, #9]
	movs r0, #0xaa
	strh r0, [r2]
	b _080A0140
	.align 2, 0
_080A0110: .4byte gNonGameplayRam
_080A0114: .4byte gChangedInput
_080A0118:
	cmp r0, #1
	bne _080A0140
	ldr r0, _080A0134 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080A0140
	movs r0, #0
	strb r0, [r2, #9]
	movs r0, #0x66
	strh r0, [r2]
	b _080A0140
	.align 2, 0
_080A0134: .4byte gChangedInput
_080A0138:
	movs r0, #0
	strb r0, [r2, #7]
	strb r0, [r2, #6]
	strb r0, [r2, #5]
_080A0140:
	pop {r0}
	bx r0

	thumb_func_start FileSelectProcessFileOverlay
FileSelectProcessFileOverlay: @ 0x080A0144
	push {lr}
	adds r2, r0, #0
	ldr r1, _080A0164 @ =gNonGameplayRam
	movs r3, #0xa
	ldrsh r0, [r1, r3]
	cmp r0, #0
	bne _080A015E
	ldr r0, _080A0168 @ =sFileSelectUnk_79e890
	ldrb r1, [r1, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r2, #0x14]
_080A015E:
	pop {r0}
	bx r0
	.align 2, 0
_080A0164: .4byte gNonGameplayRam
_080A0168: .4byte sFileSelectUnk_79e890

	thumb_func_start unk_a016c
unk_a016c: @ 0x080A016C
	push {lr}
	adds r2, r0, #0
	ldr r1, _080A0190 @ =gNonGameplayRam
	movs r0, #0xa
	ldrsh r3, [r1, r0]
	cmp r3, #0
	bne _080A01C6
	ldr r0, _080A0194 @ =sFileSelectUnk_7408e0
	str r0, [r2, #0x14]
	ldrb r1, [r1, #0xd]
	cmp r1, #2
	bhi _080A01C4
	movs r0, #1
	strb r0, [r2, #5]
	cmp r1, #0
	bne _080A0198
	movs r0, #0x31
	b _080A01A6
	.align 2, 0
_080A0190: .4byte gNonGameplayRam
_080A0194: .4byte sFileSelectUnk_7408e0
_080A0198:
	cmp r1, #1
	bne _080A01A0
	movs r0, #0x41
	b _080A01A6
_080A01A0:
	cmp r1, #2
	bne _080A01A8
	movs r0, #0x51
_080A01A6:
	strh r0, [r2, #2]
_080A01A8:
	ldr r0, _080A01BC @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	beq _080A01C6
	ldr r0, _080A01C0 @ =sUnk_7408d0
	str r0, [r2, #0x14]
	b _080A01C6
	.align 2, 0
_080A01BC: .4byte gChangedInput
_080A01C0: .4byte sUnk_7408d0
_080A01C4:
	strb r3, [r2, #5]
_080A01C6:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_a01cc
unk_a01cc: @ 0x080A01CC
	bx lr
	.align 2, 0

	thumb_func_start FileSelectProcessFileActionPanel
FileSelectProcessFileActionPanel: @ 0x080A01D0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _080A0204
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #7]
	cmp r0, r3
	bne _080A0266
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080A0266
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _080A0200 @ =sFileSelectUnk_740940
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _080A0266
	.align 2, 0
_080A0200: .4byte sFileSelectUnk_740940
_080A0204:
	cmp r2, #1
	bne _080A0248
	ldr r0, _080A021C @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0x15
	beq _080A0228
	cmp r0, #0x15
	bgt _080A0220
	cmp r0, #4
	beq _080A0228
	b _080A0266
	.align 2, 0
_080A021C: .4byte gNonGameplayRam
_080A0220:
	cmp r0, #0x1a
	beq _080A0228
	cmp r0, #0x21
	bne _080A0266
_080A0228:
	ldr r0, _080A0240 @ =0x000001FD
	bl SoundPlay
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
	ldr r0, _080A0244 @ =sFileSelectUnk_740950
	str r0, [r4, #0x14]
	movs r0, #2
	strb r0, [r4, #9]
	b _080A0266
	.align 2, 0
_080A0240: .4byte 0x000001FD
_080A0244: .4byte sFileSelectUnk_740950
_080A0248:
	cmp r2, #2
	bne _080A0266
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A0266
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A0266
	strb r1, [r4, #4]
	strb r1, [r4, #5]
_080A0266:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FileSelectProcessCopyFilePanel
FileSelectProcessCopyFilePanel: @ 0x080A026C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _080A02A0
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #7]
	cmp r0, r3
	bne _080A02FE
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080A02FE
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _080A029C @ =sFileSelectUnk_7409a0
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _080A02FE
	.align 2, 0
_080A029C: .4byte sFileSelectUnk_7409a0
_080A02A0:
	cmp r2, #1
	bne _080A02E0
	ldr r0, _080A02B8 @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0x15
	beq _080A02C0
	cmp r0, #0x15
	bgt _080A02BC
	cmp r0, #0x12
	beq _080A02C0
	b _080A02FE
	.align 2, 0
_080A02B8: .4byte gNonGameplayRam
_080A02BC:
	cmp r0, #0x1a
	bne _080A02FE
_080A02C0:
	ldr r0, _080A02D8 @ =0x000001FD
	bl SoundPlay
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
	ldr r0, _080A02DC @ =sFileSelectUnk_7409b0
	str r0, [r4, #0x14]
	movs r0, #2
	strb r0, [r4, #9]
	b _080A02FE
	.align 2, 0
_080A02D8: .4byte 0x000001FD
_080A02DC: .4byte sFileSelectUnk_7409b0
_080A02E0:
	cmp r2, #2
	bne _080A02FE
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A02FE
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A02FE
	strb r1, [r4, #4]
	strb r1, [r4, #5]
_080A02FE:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FileSelectProcessEraseFilePanel
FileSelectProcessEraseFilePanel: @ 0x080A0304
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _080A0338
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #7]
	cmp r0, r3
	bne _080A0396
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080A0396
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _080A0334 @ =sFileSelectUnk_7409a0
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _080A0396
	.align 2, 0
_080A0334: .4byte sFileSelectUnk_7409a0
_080A0338:
	cmp r2, #1
	bne _080A0378
	ldr r0, _080A0350 @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0x1f
	beq _080A0358
	cmp r0, #0x1f
	bgt _080A0354
	cmp r0, #0x1d
	beq _080A0358
	b _080A0396
	.align 2, 0
_080A0350: .4byte gNonGameplayRam
_080A0354:
	cmp r0, #0x21
	bne _080A0396
_080A0358:
	ldr r0, _080A0370 @ =0x000001FD
	bl SoundPlay
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
	ldr r0, _080A0374 @ =sFileSelectUnk_7409b0
	str r0, [r4, #0x14]
	movs r0, #2
	strb r0, [r4, #9]
	b _080A0396
	.align 2, 0
_080A0370: .4byte 0x000001FD
_080A0374: .4byte sFileSelectUnk_7409b0
_080A0378:
	cmp r2, #2
	bne _080A0396
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A0396
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A0396
	strb r1, [r4, #4]
	strb r1, [r4, #5]
_080A0396:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_a039c
unk_a039c: @ 0x080A039C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _080A03D0
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #7]
	cmp r0, r3
	bne _080A041E
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080A041E
	strb r2, [r4, #7]
	strb r2, [r4, #6]
	ldr r0, _080A03CC @ =sFileSelectUnk_7409a0
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #9]
	b _080A041E
	.align 2, 0
_080A03CC: .4byte sFileSelectUnk_7409a0
_080A03D0:
	cmp r2, #1
	bne _080A0400
	ldr r0, _080A03F4 @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0xb
	bne _080A041E
	ldr r0, _080A03F8 @ =0x000001FD
	bl SoundPlay
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
	ldr r0, _080A03FC @ =sFileSelectUnk_7409b0
	str r0, [r4, #0x14]
	movs r0, #2
	strb r0, [r4, #9]
	b _080A041E
	.align 2, 0
_080A03F4: .4byte gNonGameplayRam
_080A03F8: .4byte 0x000001FD
_080A03FC: .4byte sFileSelectUnk_7409b0
_080A0400:
	cmp r2, #2
	bne _080A041E
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A041E
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A041E
	strb r1, [r4, #4]
	strb r1, [r4, #5]
_080A041E:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_a0424
unk_a0424: @ 0x080A0424
	push {r4, lr}
	adds r4, r0, #0
	ldrb r2, [r4, #9]
	cmp r2, #0
	bne _080A04C4
	ldr r3, _080A0454 @ =gNonGameplayRam
	ldrb r0, [r3, #0x10]
	cmp r0, #0
	bne _080A045C
	ldr r0, _080A0458 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _080A047A
	movs r0, #1
	strb r0, [r3, #0x10]
	movs r0, #0x79
	strh r0, [r4, #2]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _080A047A
	.align 2, 0
_080A0454: .4byte gNonGameplayRam
_080A0458: .4byte gChangedInput
_080A045C:
	cmp r0, #1
	bne _080A047A
	ldr r0, _080A04AC @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _080A047A
	strb r2, [r3, #0x10]
	movs r0, #0x69
	strh r0, [r4, #2]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
_080A047A:
	ldr r0, _080A04AC @ =gChangedInput
	ldrh r2, [r0]
	movs r0, #2
	ands r0, r2
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _080A04EE
	movs r0, #9
	ands r0, r2
	cmp r0, #0
	beq _080A0510
	strb r1, [r4, #7]
	strb r1, [r4, #6]
	movs r0, #0xff
	lsls r0, r0, #1
	bl SoundPlay
	ldr r0, _080A04B0 @ =gNonGameplayRam
	ldrb r0, [r0, #0x10]
	cmp r0, #0
	bne _080A04B8
	ldr r0, _080A04B4 @ =sFileSelectUnk_740b70
	str r0, [r4, #0x14]
	b _080A04EE
	.align 2, 0
_080A04AC: .4byte gChangedInput
_080A04B0: .4byte gNonGameplayRam
_080A04B4: .4byte sFileSelectUnk_740b70
_080A04B8:
	ldr r0, _080A04C0 @ =sFileSelectUnk_740b70
	str r0, [r4, #0x14]
	b _080A04EE
	.align 2, 0
_080A04C0: .4byte sFileSelectUnk_740b70
_080A04C4:
	cmp r2, #1
	bne _080A04F8
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A04E0
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A04E0
	strb r1, [r4, #7]
_080A04E0:
	ldr r0, _080A04F4 @ =gNonGameplayRam
	ldrb r0, [r0, #0xc]
	cmp r0, #0xb
	bne _080A0510
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
_080A04EE:
	movs r0, #0x64
	strb r0, [r4, #9]
	b _080A0510
	.align 2, 0
_080A04F4: .4byte gNonGameplayRam
_080A04F8:
	ldrb r0, [r4, #6]
	lsls r0, r0, #3
	ldr r1, [r4, #0x14]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #7]
	cmp r0, r2
	bne _080A0510
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080A0510
	strb r1, [r4, #7]
_080A0510:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_a0518
unk_a0518: @ 0x080A0518
	bx lr
	.align 2, 0

	thumb_func_start FileSelectDrawFileInfo
FileSelectDrawFileInfo: @ 0x080A051C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x50
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov sl, r0
	lsls r0, r0, #2
	add r0, sl
	lsls r0, r0, #2
	ldr r1, _080A0548 @ =0x03000B94
	adds r0, r0, r1
	mov sb, r0
	adds r2, r1, #0
	mov r0, sl
	cmp r0, #0
	bne _080A0550
	ldr r7, _080A054C @ =0x060088C0
	b _080A0562
	.align 2, 0
_080A0548: .4byte 0x03000B94
_080A054C: .4byte 0x060088C0
_080A0550:
	mov r1, sl
	cmp r1, #1
	bne _080A0560
	ldr r7, _080A055C @ =0x060090C0
	b _080A0562
	.align 2, 0
_080A055C: .4byte 0x060090C0
_080A0560:
	ldr r7, _080A05A8 @ =0x060098C0
_080A0562:
	str r7, [sp, #0x38]
	ldr r5, _080A05AC @ =gNonGameplayRam
	movs r1, #0
	movs r0, #0
	strh r0, [r5]
	strb r1, [r5, #0x13]
	mov r3, sb
	ldrb r4, [r3]
	mov r0, sl
	lsls r0, r0, #2
	str r0, [sp, #0x40]
	cmp r4, #0
	beq _080A057E
	b _080A0694
_080A057E:
	add r0, sl
	lsls r0, r0, #2
	adds r1, r0, r2
	movs r0, #0x10
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _080A0594
	movs r0, #0x11
	ldrsb r0, [r1, r0]
	cmp r0, #1
	bne _080A05B0
_080A0594:
	movs r2, #0xa8
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0x63
	strh r0, [r1]
	movs r3, #0xa7
	lsls r3, r3, #2
	adds r3, r3, r5
	mov sb, r3
	b _080A0694
	.align 2, 0
_080A05A8: .4byte 0x060098C0
_080A05AC: .4byte gNonGameplayRam
_080A05B0:
	mov r0, sl
	adds r0, #0xe
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	bl FileSelectDestroyOamOfType
	mov r0, sl
	adds r0, #0x14
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	bl FileSelectDestroyOamOfType
	str r4, [sp, #0x34]
	ldr r0, _080A061C @ =0x040000D4
	add r1, sp, #0x34
	str r1, [r0]
	str r7, [r0, #4]
	ldr r2, _080A0620 @ =0x850000C0
	str r2, [r0, #8]
	ldr r3, [r0, #8]
	str r4, [sp, #0x34]
	str r1, [r0]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r1, r7, r3
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	ldr r1, _080A0624 @ =sFileSelectUnk_79ec84
	ldr r0, _080A0628 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r4, [r0]
	movs r0, #8
	strh r0, [r5]
	ldrh r0, [r4]
	movs r1, #0xff
	lsls r1, r1, #8
	cmp r0, r1
	bne _080A060A
	b _080A0A08
_080A060A:
	mov r8, r5
	mov sb, r1
_080A060E:
	cmp r0, #0x5a
	bne _080A062C
	ldrh r0, [r4]
	bl TextGetCharacterWidth
	adds r5, r0, #2
	b _080A063C
	.align 2, 0
_080A061C: .4byte 0x040000D4
_080A0620: .4byte 0x850000C0
_080A0624: .4byte sFileSelectUnk_79ec84
_080A0628: .4byte 0x03000011
_080A062C:
	cmp r0, #0x40
	bne _080A063A
	mov r0, r8
	ldrb r1, [r0, #0x13]
	movs r0, #8
	subs r5, r0, r1
	b _080A063C
_080A063A:
	movs r5, #8
_080A063C:
	mov r1, r8
	ldrh r0, [r1]
	lsls r0, r0, #5
	ldr r2, [sp, #0x38]
	adds r7, r0, r2
	ldrh r0, [r4]
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r1, #0x13]
	movs r1, #0
	str r1, [sp]
	adds r1, r7, #0
	bl TextDrawCharacter
	mov r3, r8
	ldrb r0, [r3, #0x13]
	adds r0, r0, r5
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r6, r4, #2
	cmp r0, #7
	bls _080A0686
	ldr r5, _080A0690 @ =gNonGameplayRam
	ldrb r4, [r5, #0x13]
	ldrh r3, [r5]
_080A0670:
	adds r2, r4, #0
	subs r2, #8
	adds r4, r2, #0
	adds r1, r3, #1
	adds r3, r1, #0
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A0670
	strh r1, [r5]
	strb r2, [r5, #0x13]
_080A0686:
	adds r4, r6, #0
	ldrh r0, [r4]
	cmp r0, sb
	bne _080A060E
	b _080A0A08
	.align 2, 0
_080A0690: .4byte gNonGameplayRam
_080A0694:
	ldr r0, _080A07F4 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	movs r0, #0xfa
	lsls r0, r0, #2
	mov r2, sb
	ldrh r1, [r2, #4]
	bl DivArmDiv
	add r4, sp, #0x14
	str r0, [sp, #0x14]
	mov r3, sb
	ldrh r1, [r3, #4]
	movs r0, #0x64
	bl DivArmDiv
	add r5, sp, #0x24
	str r0, [r4, #4]
	str r0, [sp, #0x24]
	ldr r1, [r4, #4]
	movs r0, #0xa
	bl DivArmMod
	str r0, [r4, #4]
	str r0, [r5, #4]
	mov r0, sb
	ldrh r1, [r0, #4]
	movs r0, #0xa
	bl DivArmDiv
	adds r1, r0, #0
	str r1, [r4, #8]
	movs r0, #0xa
	bl DivArmMod
	str r0, [r4, #8]
	mov r2, sb
	ldrh r1, [r2, #4]
	str r1, [r4, #0xc]
	movs r0, #0xa
	bl DivArmMod
	str r0, [r4, #0xc]
	movs r6, #2
	mov r3, sl
	adds r3, #0xe
	str r3, [sp, #0x44]
	mov r0, sl
	adds r0, #0x14
	str r0, [sp, #0x4c]
	add r1, sp, #0x34
	mov ip, r1
	mov r8, r5
	mov r2, sl
	lsls r2, r2, #4
	str r2, [sp, #0x48]
	ldr r1, _080A07F8 @ =0x040000D4
	ldr r4, _080A07FC @ =0x84000008
	movs r2, #0x80
	lsls r2, r2, #3
	ldr r5, _080A0800 @ =sCharactersGfx
_080A0710:
	lsls r0, r6, #2
	add r0, sp
	adds r0, #0x14
	ldr r0, [r0]
	adds r0, #0x50
	lsls r0, r0, #5
	adds r3, r0, r5
	str r3, [r1]
	str r7, [r1, #4]
	str r4, [r1, #8]
	ldr r0, [r1, #8]
	adds r0, r3, r2
	str r0, [r1]
	adds r0, r7, r2
	str r0, [r1, #4]
	str r4, [r1, #8]
	ldr r0, [r1, #8]
	adds r7, #0x20
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #3
	bls _080A0710
	movs r1, #0
	str r1, [sp, #0x34]
	ldr r5, _080A07F8 @ =0x040000D4
	mov r3, ip
	str r3, [r5]
	str r7, [r5, #4]
	ldr r0, _080A0804 @ =0x85000080
	str r0, [r5, #8]
	ldr r2, [r5, #8]
	str r1, [sp, #0x34]
	str r3, [r5]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r4, r7, r1
	str r4, [r5, #4]
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	mov r2, r8
	ldr r1, [r2, #4]
	movs r0, #2
	bl DivArmMod
	mov r3, r8
	str r0, [r3, #4]
	mov r0, sb
	ldrh r1, [r0, #6]
	movs r0, #0x64
	bl DivArmDiv
	adds r1, r0, #0
	mov r2, r8
	str r1, [r2, #8]
	movs r0, #0xa
	bl DivArmMod
	adds r1, r0, #0
	mov r3, r8
	str r1, [r3, #0xc]
	movs r0, #2
	bl DivArmMod
	mov r1, r8
	str r0, [r1, #0xc]
	adds r3, r7, #0
	adds r7, r4, #0
	movs r6, #0
	ldr r0, [sp, #0x24]
	ldr r1, [r1, #4]
	subs r0, r0, r1
	cmp r6, r0
	bge _080A07D2
	adds r2, r5, #0
	mov r4, r8
	ldr r0, _080A0808 @ =sFileSelectUnk_73db64
	mov ip, r0
	ldr r5, _080A07FC @ =0x84000008
_080A07AE:
	cmp r6, #0xa
	bne _080A07B6
	ldr r1, _080A080C @ =0xFFFFFB60
	adds r7, r7, r1
_080A07B6:
	mov r0, ip
	str r0, [r2]
	str r7, [r2, #4]
	str r5, [r2, #8]
	ldr r0, [r2, #8]
	adds r7, #0x20
	adds r0, r6, #2
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r0, [sp, #0x24]
	ldr r1, [r4, #4]
	subs r0, r0, r1
	cmp r6, r0
	blt _080A07AE
_080A07D2:
	mov r1, r8
	ldr r0, [r1, #4]
	cmp r0, #1
	bne _080A082A
	cmp r6, #0xa
	bne _080A07E2
	ldr r2, _080A080C @ =0xFFFFFB60
	adds r7, r7, r2
_080A07E2:
	mov r0, r8
	ldr r1, [r0, #8]
	ldr r0, [sp, #0x24]
	cmp r1, r0
	bne _080A0814
	ldr r1, _080A07F8 @ =0x040000D4
	ldr r0, _080A0810 @ =sFileSelectUnk_73db04
	b _080A0818
	.align 2, 0
_080A07F4: .4byte 0x03000011
_080A07F8: .4byte 0x040000D4
_080A07FC: .4byte 0x84000008
_080A0800: .4byte sCharactersGfx
_080A0804: .4byte 0x85000080
_080A0808: .4byte sFileSelectUnk_73db64
_080A080C: .4byte 0xFFFFFB60
_080A0810: .4byte sFileSelectUnk_73db04
_080A0814:
	ldr r1, _080A0A18 @ =0x040000D4
	ldr r0, _080A0A1C @ =sFileSelectUnk_73db44
_080A0818:
	str r0, [r1]
	str r7, [r1, #4]
	ldr r0, _080A0A20 @ =0x84000008
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	adds r0, r6, #2
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	adds r7, #0x20
_080A082A:
	mov r1, r8
	ldr r0, [r1, #8]
	ldr r1, [r1, #0xc]
	subs r0, r0, r1
	adds r3, #0xc0
	str r3, [sp, #0x3c]
	cmp r6, r0
	bge _080A0866
	ldr r2, _080A0A24 @ =0xFFFFFB60
	mov ip, r2
	ldr r2, _080A0A18 @ =0x040000D4
	mov r3, r8
	ldr r5, _080A0A28 @ =sFileSelectUnk_73db24
	ldr r4, _080A0A20 @ =0x84000008
_080A0846:
	cmp r6, #0xa
	bne _080A084C
	add r7, ip
_080A084C:
	str r5, [r2]
	str r7, [r2, #4]
	str r4, [r2, #8]
	ldr r0, [r2, #8]
	adds r7, #0x20
	adds r0, r6, #2
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r0, [r3, #8]
	ldr r1, [r3, #0xc]
	subs r0, r0, r1
	cmp r6, r0
	blt _080A0846
_080A0866:
	mov r3, r8
	ldr r0, [r3, #0xc]
	cmp r0, #1
	bne _080A088A
	ldr r0, [r3, #8]
	cmp r6, r0
	bge _080A088A
	cmp r6, #0xa
	bne _080A087C
	ldr r0, _080A0A24 @ =0xFFFFFB60
	adds r7, r7, r0
_080A087C:
	ldr r1, _080A0A18 @ =0x040000D4
	ldr r0, _080A0A2C @ =sFileSelectUnk_73dae4
	str r0, [r1]
	str r7, [r1, #4]
	ldr r0, _080A0A20 @ =0x84000008
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_080A088A:
	ldr r7, [sp, #0x3c]
	mov r2, sb
	ldrb r1, [r2, #0xd]
	movs r0, #0xa
	bl DivArmDiv
	adds r1, r0, #0
	str r1, [sp, #4]
	movs r0, #0xa
	bl DivArmMod
	str r0, [sp, #4]
	mov r3, sb
	ldrb r1, [r3, #0xd]
	str r1, [sp, #8]
	movs r0, #0xa
	bl DivArmMod
	str r0, [sp, #8]
	movs r6, #0
	ldr r5, _080A0A30 @ =sCharactersGfx
	ldr r1, _080A0A18 @ =0x040000D4
	ldr r4, _080A0A20 @ =0x84000008
	movs r2, #0x80
	lsls r2, r2, #3
_080A08BC:
	lsls r0, r6, #2
	add r0, sp
	adds r0, #4
	ldr r0, [r0]
	adds r0, #0x50
	lsls r0, r0, #5
	adds r3, r0, r5
	str r3, [r1]
	str r7, [r1, #4]
	str r4, [r1, #8]
	ldr r0, [r1, #8]
	adds r0, r3, r2
	str r0, [r1]
	adds r0, r7, r2
	str r0, [r1, #4]
	str r4, [r1, #8]
	ldr r0, [r1, #8]
	adds r7, #0x20
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #1
	bls _080A08BC
	ldr r6, _080A0A34 @ =gNonGameplayRam
	movs r4, #0
	movs r0, #0xa
	strh r0, [r6]
	lsls r0, r0, #5
	ldr r1, [sp, #0x38]
	adds r7, r1, r0
	movs r0, #0x5a
	bl TextGetCharacterWidth
	adds r5, r0, #3
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r6, #0x13]
	str r4, [sp]
	movs r0, #0x5a
	adds r1, r7, #0
	bl TextDrawCharacter
	ldrb r0, [r6, #0x13]
	adds r2, r0, r5
	strb r2, [r6, #0x13]
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _080A0938
	adds r5, r6, #0
	ldrh r4, [r5]
_080A0922:
	adds r3, r2, #0
	subs r3, #8
	adds r2, r3, #0
	adds r1, r4, #1
	adds r4, r1, #0
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A0922
	strh r1, [r5]
	strb r3, [r5, #0x13]
_080A0938:
	mov r2, sb
	ldrb r1, [r2, #0xe]
	movs r0, #0xa
	bl DivArmDiv
	adds r1, r0, #0
	str r1, [sp, #4]
	movs r0, #0xa
	bl DivArmMod
	str r0, [sp, #4]
	mov r3, sb
	ldrb r1, [r3, #0xe]
	str r1, [sp, #8]
	movs r0, #0xa
	bl DivArmMod
	str r0, [sp, #8]
	movs r6, #0
	ldr r0, _080A0A34 @ =gNonGameplayRam
	mov r8, r0
_080A0962:
	mov r1, r8
	ldrh r0, [r1]
	lsls r0, r0, #5
	ldr r2, [sp, #0x38]
	adds r7, r0, r2
	lsls r0, r6, #2
	add r0, sp
	adds r0, #4
	ldr r0, [r0]
	adds r0, #0x50
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	ldrb r3, [r1, #0x13]
	movs r1, #0
	str r1, [sp]
	adds r1, r7, #0
	movs r2, #8
	bl TextDrawCharacter
	mov r3, r8
	ldrb r0, [r3, #0x13]
	adds r0, #8
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r6, #1
	cmp r0, #7
	bls _080A09B6
	ldr r5, _080A0A34 @ =gNonGameplayRam
	ldrb r4, [r5, #0x13]
	ldrh r3, [r5]
_080A09A0:
	adds r2, r4, #0
	subs r2, #8
	adds r4, r2, #0
	adds r1, r3, #1
	adds r3, r1, #0
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A09A0
	strh r1, [r5]
	strb r2, [r5, #0x13]
_080A09B6:
	lsls r0, r6, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #1
	bls _080A0962
	ldr r0, [sp, #0x44]
	lsls r4, r0, #0x18
	lsrs r4, r4, #0x18
	adds r0, r4, #0
	bl FileSelectDestroyOamOfType
	ldr r2, [sp, #0x48]
	adds r2, #0x20
	mov r1, sb
	ldrb r3, [r1, #2]
	adds r0, r4, #0
	movs r1, #0x9d
	bl FileSelectSetUpAreaNameOam
	ldr r2, [sp, #0x4c]
	lsls r0, r2, #0x18
	lsrs r4, r0, #0x18
	adds r0, r4, #0
	bl FileSelectDestroyOamOfType
	ldr r1, _080A0A38 @ =0x03000B94
	ldr r0, [sp, #0x40]
	add r0, sl
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrb r0, [r0, #0x10]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bne _080A0A08
	ldr r2, [sp, #0x48]
	adds r2, #0x28
	adds r0, r4, #0
	movs r1, #0xdc
	movs r3, #1
	bl FileSelectSetupOam
_080A0A08:
	add sp, #0x50
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0A18: .4byte 0x040000D4
_080A0A1C: .4byte sFileSelectUnk_73db44
_080A0A20: .4byte 0x84000008
_080A0A24: .4byte 0xFFFFFB60
_080A0A28: .4byte sFileSelectUnk_73db24
_080A0A2C: .4byte sFileSelectUnk_73dae4
_080A0A30: .4byte sCharactersGfx
_080A0A34: .4byte gNonGameplayRam
_080A0A38: .4byte 0x03000B94

	thumb_func_start FileSelectDrawText
FileSelectDrawText: @ 0x080A0A3C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	ldr r0, _080A0A74 @ =gNonGameplayRam
	movs r2, #0
	movs r1, #0
	strh r1, [r0, #2]
	strh r1, [r0]
	strb r2, [r0, #0x13]
	ldrh r1, [r0, #8]
	adds r2, r0, #0
	cmp r1, #0x18
	bne _080A0A80
	ldr r1, _080A0A78 @ =sFileSelectUnk_79e928
	ldr r0, _080A0A7C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r7, [r0, #0x14]
	b _080A0A98
	.align 2, 0
_080A0A74: .4byte gNonGameplayRam
_080A0A78: .4byte sFileSelectUnk_79e928
_080A0A7C: .4byte 0x03000011
_080A0A80:
	ldr r1, _080A0AA4 @ =sFileSelectUnk_79e928
	ldr r0, _080A0AA8 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrh r1, [r2, #8]
	ldr r0, [r0]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r7, [r1]
_080A0A98:
	cmp r3, #1
	bne _080A0AB0
	ldr r0, _080A0AAC @ =0x06008000
	mov sb, r0
	movs r4, #6
	b _080A0AC6
	.align 2, 0
_080A0AA4: .4byte sFileSelectUnk_79e928
_080A0AA8: .4byte 0x03000011
_080A0AAC: .4byte 0x06008000
_080A0AB0:
	cmp r3, #2
	bne _080A0ABC
	ldr r0, _080A0AB8 @ =0x0600B000
	b _080A0AC2
	.align 2, 0
_080A0AB8: .4byte 0x0600B000
_080A0ABC:
	cmp r3, #3
	bne _080A0AC8
	ldr r0, _080A0AFC @ =0x0600C800
_080A0AC2:
	mov sb, r0
	movs r4, #0
_080A0AC6:
	mov r8, r4
_080A0AC8:
	adds r6, r2, #0
	ldr r0, [r6, #4]
	ldrh r0, [r0]
	movs r1, #0xff
	lsls r1, r1, #8
	cmp r0, r1
	beq _080A0B6E
	mov sl, r1
_080A0AD8:
	ldr r1, [r6, #4]
	ldrh r0, [r1]
	movs r2, #0xfe
	lsls r2, r2, #8
	cmp r0, r2
	bne _080A0B00
	movs r1, #0
	movs r0, #0
	strh r0, [r6]
	ldrh r0, [r6, #2]
	adds r0, #2
	strh r0, [r6, #2]
	strb r1, [r6, #0x13]
	adds r7, #2
	movs r4, #0
	mov r8, r4
	b _080A0B5E
	.align 2, 0
_080A0AFC: .4byte 0x0600C800
_080A0B00:
	ldrh r4, [r6]
	lsls r4, r4, #5
	ldrh r0, [r6, #2]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	add r4, sb
	ldrh r0, [r7]
	lsls r0, r0, #5
	adds r4, r4, r0
	str r4, [sp, #4]
	ldrh r0, [r1]
	bl TextGetCharacterWidth
	adds r5, r0, #0
	ldr r0, [r6, #4]
	ldrh r0, [r0]
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r6, #0x13]
	mov r4, r8
	lsls r1, r4, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	ldr r1, [sp, #4]
	bl TextDrawCharacter
	ldrb r0, [r6, #0x13]
	adds r0, r0, r5
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _080A0B5E
	ldr r5, _080A0B80 @ =gNonGameplayRam
	ldrb r4, [r5, #0x13]
	ldrh r3, [r5]
_080A0B48:
	adds r2, r4, #0
	subs r2, #8
	adds r4, r2, #0
	adds r1, r3, #1
	adds r3, r1, #0
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A0B48
	strh r1, [r5]
	strb r2, [r5, #0x13]
_080A0B5E:
	ldr r1, _080A0B80 @ =gNonGameplayRam
	ldr r2, [r1, #4]
	adds r0, r2, #2
	str r0, [r1, #4]
	adds r6, r1, #0
	ldrh r0, [r2, #2]
	cmp r0, sl
	bne _080A0AD8
_080A0B6E:
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0B80: .4byte gNonGameplayRam

	thumb_func_start FileSelectProcessCorruptedFile
FileSelectProcessCorruptedFile: @ 0x080A0B84
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	bl FileSelectProcessOam
	ldr r0, _080A0BA4 @ =gNonGameplayRam
	ldrb r0, [r0, #0x14]
	cmp r0, #7
	bls _080A0B98
	b _080A0DF0
_080A0B98:
	lsls r0, r0, #2
	ldr r1, _080A0BA8 @ =_080A0BAC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A0BA4: .4byte gNonGameplayRam
_080A0BA8: .4byte _080A0BAC
_080A0BAC: @ jump table
	.4byte _080A0BCC @ case 0
	.4byte _080A0C64 @ case 1
	.4byte _080A0C8A @ case 2
	.4byte _080A0CCC @ case 3
	.4byte _080A0CF8 @ case 4
	.4byte _080A0D60 @ case 5
	.4byte _080A0DA4 @ case 6
	.4byte _080A0DE8 @ case 7
_080A0BCC:
	ldr r1, _080A0BE4 @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _080A0BE8
	movs r0, #1
	bl FileSelectDrawText
	b _080A0DF0
	.align 2, 0
_080A0BE4: .4byte gNonGameplayRam
_080A0BE8:
	cmp r0, #2
	bne _080A0C08
	ldr r0, _080A0BFC @ =0x03000B94
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _080A0C00
	movs r0, #0
	bl FileSelectDrawFileInfo
	b _080A0DF0
	.align 2, 0
_080A0BFC: .4byte 0x03000B94
_080A0C00:
	movs r0, #0
	bl FileSelectDrawFileCorruptedText
	b _080A0DF0
_080A0C08:
	cmp r0, #3
	bne _080A0C28
	ldr r0, _080A0C1C @ =0x03000B94
	ldrb r0, [r0, #0x15]
	cmp r0, #0
	bne _080A0C20
	movs r0, #1
	bl FileSelectDrawFileInfo
	b _080A0DF0
	.align 2, 0
_080A0C1C: .4byte 0x03000B94
_080A0C20:
	movs r0, #1
	bl FileSelectDrawFileCorruptedText
	b _080A0DF0
_080A0C28:
	cmp r0, #4
	beq _080A0C2E
	b _080A0DF0
_080A0C2E:
	ldr r0, _080A0C40 @ =0x03000B94
	adds r0, #0x29
	ldrb r0, [r0]
	cmp r0, #0
	bne _080A0C44
	movs r0, #2
	bl FileSelectDrawFileInfo
	b _080A0C4A
	.align 2, 0
_080A0C40: .4byte 0x03000B94
_080A0C44:
	movs r0, #2
	bl FileSelectDrawFileCorruptedText
_080A0C4A:
	ldr r2, _080A0C5C @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r2, #0xc]
	ldr r1, _080A0C60 @ =gWrittenToBldy
	movs r0, #0xe
	strh r0, [r1]
	movs r0, #1
	strb r0, [r2, #0x14]
	b _080A0DF0
	.align 2, 0
_080A0C5C: .4byte gNonGameplayRam
_080A0C60: .4byte gWrittenToBldy
_080A0C64:
	ldr r1, _080A0C74 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _080A0C78
	subs r0, #1
	strh r0, [r1]
	b _080A0DF0
	.align 2, 0
_080A0C74: .4byte gWrittenToBldy
_080A0C78:
	ldr r1, _080A0C80 @ =gNonGameplayRam
	movs r0, #2
	strb r0, [r1, #0x14]
	b _080A0DF0
	.align 2, 0
_080A0C80: .4byte gNonGameplayRam
_080A0C84:
	movs r0, #3
	strb r0, [r4, #0x14]
	b _080A0CB4
_080A0C8A:
	ldr r0, _080A0CC4 @ =gNonGameplayRam
	ldrb r1, [r0, #0x15]
	adds r4, r0, #0
	cmp r1, #2
	bhi _080A0CB4
	ldr r3, _080A0CC8 @ =0x03000B94
	adds r2, r4, #0
_080A0C98:
	ldrb r1, [r2, #0x15]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	ldrb r0, [r0, #1]
	cmp r0, #0
	bne _080A0C84
	adds r0, r1, #1
	strb r0, [r4, #0x15]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bls _080A0C98
_080A0CB4:
	ldrb r0, [r4, #0x15]
	cmp r0, #3
	beq _080A0CBC
	b _080A0DF0
_080A0CBC:
	movs r0, #7
	strb r0, [r4, #0x14]
	b _080A0DF0
	.align 2, 0
_080A0CC4: .4byte gNonGameplayRam
_080A0CC8: .4byte 0x03000B94
_080A0CCC:
	ldr r1, _080A0CF4 @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xa
	beq _080A0CDE
	b _080A0DF0
_080A0CDE:
	movs r0, #4
	strb r0, [r1, #0x14]
	movs r0, #0
	strb r0, [r1, #0xc]
	movs r0, #0x11
	movs r1, #0x7a
	movs r2, #0x44
	movs r3, #0
	bl FileSelectSetupOam
	b _080A0DF0
	.align 2, 0
_080A0CF4: .4byte gNonGameplayRam
_080A0CF8:
	ldr r2, _080A0D14 @ =0x03000B94
	ldr r1, _080A0D18 @ =gNonGameplayRam
	ldrb r3, [r1, #0x15]
	lsls r0, r3, #2
	adds r0, r0, r3
	lsls r0, r0, #2
	adds r0, r0, r2
	ldrb r0, [r0, #1]
	adds r4, r1, #0
	cmp r0, #1
	bne _080A0D1C
	adds r0, r3, #5
	b _080A0D20
	.align 2, 0
_080A0D14: .4byte 0x03000B94
_080A0D18: .4byte gNonGameplayRam
_080A0D1C:
	adds r0, r3, #0
	adds r0, #8
_080A0D20:
	strh r0, [r4, #8]
	ldr r1, _080A0D58 @ =sFileSelectUnk_79ec68
	ldr r0, _080A0D5C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrh r1, [r4, #8]
	ldr r0, [r0]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r4, #4]
	movs r0, #2
	bl FileSelectDrawCorruptionText
	movs r0, #0xa
	movs r1, #0x78
	movs r2, #0x64
	movs r3, #0
	bl FileSelectSetupOam
	movs r0, #3
	strb r0, [r4, #0x11]
	movs r0, #5
	strb r0, [r4, #0x14]
	b _080A0DF0
	.align 2, 0
_080A0D58: .4byte sFileSelectUnk_79ec68
_080A0D5C: .4byte 0x03000011
_080A0D60:
	ldr r0, _080A0D98 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	beq _080A0DF0
	movs r0, #0xa
	bl FileSelectDestroyOamOfType
	movs r0, #0x11
	bl FileSelectDestroyOamOfType
	ldr r0, _080A0D9C @ =0x000001FB
	bl SoundPlay
	ldr r4, _080A0DA0 @ =gNonGameplayRam
	movs r0, #4
	strb r0, [r4, #0x11]
	ldrb r0, [r4, #0x15]
	bl Sram_SetCurrentFile
	ldrb r0, [r4, #0x15]
	bl FileSelectDrawFileInfo
	movs r0, #6
	strb r0, [r4, #0x14]
	b _080A0DF0
	.align 2, 0
_080A0D98: .4byte gChangedInput
_080A0D9C: .4byte 0x000001FB
_080A0DA0: .4byte gNonGameplayRam
_080A0DA4:
	ldr r1, _080A0DCC @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	movs r2, #0
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _080A0DDC
	str r2, [sp]
	ldr r1, _080A0DD0 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _080A0DD4 @ =0x0600B000
	str r0, [r1, #4]
	ldr r0, _080A0DD8 @ =0x85000600
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _080A0DF0
	.align 2, 0
_080A0DCC: .4byte gNonGameplayRam
_080A0DD0: .4byte 0x040000D4
_080A0DD4: .4byte 0x0600B000
_080A0DD8: .4byte 0x85000600
_080A0DDC:
	cmp r0, #0xa
	bne _080A0DF0
	movs r0, #2
	strb r0, [r1, #0x14]
	strb r2, [r1, #0xc]
	b _080A0DF0
_080A0DE8:
	ldr r1, _080A0E00 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0xc]
	movs r5, #1
_080A0DF0:
	bl FileSelectDrawAllOam
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080A0E00: .4byte gNonGameplayRam

	thumb_func_start FileSelectDrawFileCorruptedText
FileSelectDrawFileCorruptedText: @ 0x080A0E04
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _080A0E20
	ldr r6, _080A0E1C @ =0x060088C0
	b _080A0E2E
	.align 2, 0
_080A0E1C: .4byte 0x060088C0
_080A0E20:
	cmp r0, #1
	bne _080A0E2C
	ldr r6, _080A0E28 @ =0x060090C0
	b _080A0E2E
	.align 2, 0
_080A0E28: .4byte 0x060090C0
_080A0E2C:
	ldr r6, _080A0E90 @ =0x060098C0
_080A0E2E:
	mov r8, r6
	ldr r4, _080A0E94 @ =gNonGameplayRam
	movs r0, #0
	movs r1, #0
	strh r1, [r4]
	strb r0, [r4, #0x13]
	str r1, [sp, #4]
	ldr r0, _080A0E98 @ =0x040000D4
	add r2, sp, #4
	str r2, [r0]
	str r6, [r0, #4]
	ldr r2, _080A0E9C @ =0x850000C0
	str r2, [r0, #8]
	ldr r3, [r0, #8]
	str r1, [sp, #4]
	add r3, sp, #4
	str r3, [r0]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r1, r6, r3
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	ldr r1, _080A0EA0 @ =sFileSelectUnk_79ec84
	ldr r0, _080A0EA4 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r5, [r0]
	movs r0, #8
	strh r0, [r4]
	ldrh r0, [r5]
	movs r1, #0xff
	lsls r1, r1, #8
	cmp r0, r1
	beq _080A0F04
	adds r7, r4, #0
	mov sb, r1
_080A0E80:
	cmp r0, #0x5a
	bne _080A0EA8
	ldrh r0, [r5]
	bl TextGetCharacterWidth
	adds r4, r0, #3
	b _080A0EB6
	.align 2, 0
_080A0E90: .4byte 0x060098C0
_080A0E94: .4byte gNonGameplayRam
_080A0E98: .4byte 0x040000D4
_080A0E9C: .4byte 0x850000C0
_080A0EA0: .4byte sFileSelectUnk_79ec84
_080A0EA4: .4byte 0x03000011
_080A0EA8:
	cmp r0, #0x40
	bne _080A0EB4
	ldrb r1, [r7, #0x13]
	movs r0, #8
	subs r4, r0, r1
	b _080A0EB6
_080A0EB4:
	movs r4, #8
_080A0EB6:
	ldrh r0, [r7]
	lsls r0, r0, #5
	mov r1, r8
	adds r6, r0, r1
	ldrh r0, [r5]
	lsls r2, r4, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r7, #0x13]
	movs r1, #0
	str r1, [sp]
	adds r1, r6, #0
	bl TextDrawCharacter
	ldrb r0, [r7, #0x13]
	adds r0, r0, r4
	strb r0, [r7, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r6, r5, #2
	cmp r0, #7
	bls _080A0EFC
	ldr r5, _080A0F14 @ =gNonGameplayRam
	ldrb r4, [r5, #0x13]
	ldrh r3, [r5]
_080A0EE6:
	adds r2, r4, #0
	subs r2, #8
	adds r4, r2, #0
	adds r1, r3, #1
	adds r3, r1, #0
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A0EE6
	strh r1, [r5]
	strb r2, [r5, #0x13]
_080A0EFC:
	adds r5, r6, #0
	ldrh r0, [r5]
	cmp r0, sb
	bne _080A0E80
_080A0F04:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A0F14: .4byte gNonGameplayRam

	thumb_func_start FileSelectDrawCorruptionText
FileSelectDrawCorruptionText: @ 0x080A0F18
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	adds r4, r3, #0
	ldr r0, _080A0F40 @ =gNonGameplayRam
	movs r2, #0
	movs r1, #0
	strh r1, [r0, #2]
	strh r1, [r0]
	strb r2, [r0, #0x13]
	cmp r3, #1
	bne _080A0F48
	ldr r7, _080A0F44 @ =0x06008000
	b _080A0F5A
	.align 2, 0
_080A0F40: .4byte gNonGameplayRam
_080A0F44: .4byte 0x06008000
_080A0F48:
	cmp r3, #2
	bne _080A0F54
	ldr r7, _080A0F50 @ =0x0600B000
	b _080A0F5A
	.align 2, 0
_080A0F50: .4byte 0x0600B000
_080A0F54:
	cmp r4, #3
	bne _080A0F5A
	ldr r7, _080A0F8C @ =0x0600C800
_080A0F5A:
	adds r6, r0, #0
	ldr r0, [r6, #4]
	ldrh r0, [r0]
	movs r1, #0xff
	lsls r1, r1, #8
	cmp r0, r1
	beq _080A0FF2
	movs r0, #0xfe
	lsls r0, r0, #8
	mov sl, r0
	movs r0, #0
	mov sb, r0
	mov r8, r1
_080A0F74:
	ldr r1, [r6, #4]
	ldrh r0, [r1]
	cmp r0, sl
	bne _080A0F90
	movs r0, #0
	strh r0, [r6]
	ldrh r0, [r6, #2]
	adds r0, #2
	strh r0, [r6, #2]
	mov r0, sb
	strb r0, [r6, #0x13]
	b _080A0FE2
	.align 2, 0
_080A0F8C: .4byte 0x0600C800
_080A0F90:
	ldrh r4, [r6]
	lsls r4, r4, #5
	ldrh r0, [r6, #2]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	adds r4, r4, r7
	ldrh r0, [r1]
	bl TextGetCharacterWidth
	adds r5, r0, #0
	ldr r0, [r6, #4]
	ldrh r0, [r0]
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r6, #0x13]
	movs r1, #0
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrb r0, [r6, #0x13]
	adds r0, r0, r5
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _080A0FE2
	ldr r5, _080A1004 @ =gNonGameplayRam
	ldrb r4, [r5, #0x13]
	ldrh r3, [r5]
_080A0FCC:
	adds r2, r4, #0
	subs r2, #8
	adds r4, r2, #0
	adds r1, r3, #1
	adds r3, r1, #0
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080A0FCC
	strh r1, [r5]
	strb r2, [r5, #0x13]
_080A0FE2:
	ldr r1, _080A1004 @ =gNonGameplayRam
	ldr r2, [r1, #4]
	adds r0, r2, #2
	str r0, [r1, #4]
	adds r6, r1, #0
	ldrh r0, [r2, #2]
	cmp r0, r8
	bne _080A0F74
_080A0FF2:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1004: .4byte gNonGameplayRam

	thumb_func_start FileSelectDestroyOamOfType
FileSelectDestroyOamOfType: @ 0x080A1008
	push {r4, r5, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r2, #0
	ldr r5, _080A1028 @ =gNonGameplayRam
	movs r3, #0
_080A1014:
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r1, r0, r5
	ldrb r0, [r1, #0x1c]
	cmp r0, r4
	bne _080A102C
	strb r3, [r1, #0x1c]
	strb r3, [r1, #0x1d]
	b _080A1036
	.align 2, 0
_080A1028: .4byte gNonGameplayRam
_080A102C:
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0x16
	bls _080A1014
_080A1036:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start FileSelectSetUpAreaNameOam
FileSelectSetUpAreaNameOam: @ 0x080A103C
	push {r4, lr}
	adds r4, r3, #0
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsls r4, r4, #0x10
	lsrs r4, r4, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	movs r3, #1
	bl FileSelectSetupOam
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	lsls r4, r4, #0x10
	asrs r0, r4, #0x10
	cmp r0, #6
	bls _080A1064
	b _080A1198
_080A1064:
	lsls r0, r0, #2
	ldr r1, _080A1070 @ =_080A1074
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A1070: .4byte _080A1074
_080A1074: @ jump table
	.4byte _080A1198 @ case 0
	.4byte _080A1090 @ case 1
	.4byte _080A10BC @ case 2
	.4byte _080A10E8 @ case 3
	.4byte _080A1114 @ case 4
	.4byte _080A1140 @ case 5
	.4byte _080A116C @ case 6
_080A1090:
	ldr r0, _080A10B0 @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A10B4 @ =sFileSelectUnk_79e944
	ldr r0, _080A10B8 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #4
	b _080A11B2
	.align 2, 0
_080A10B0: .4byte gNonGameplayRam
_080A10B4: .4byte sFileSelectUnk_79e944
_080A10B8: .4byte 0x03000011
_080A10BC:
	ldr r0, _080A10DC @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A10E0 @ =sFileSelectUnk_79e944
	ldr r0, _080A10E4 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #8
	b _080A11B2
	.align 2, 0
_080A10DC: .4byte gNonGameplayRam
_080A10E0: .4byte sFileSelectUnk_79e944
_080A10E4: .4byte 0x03000011
_080A10E8:
	ldr r0, _080A1108 @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A110C @ =sFileSelectUnk_79e944
	ldr r0, _080A1110 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #0xc
	b _080A11B2
	.align 2, 0
_080A1108: .4byte gNonGameplayRam
_080A110C: .4byte sFileSelectUnk_79e944
_080A1110: .4byte 0x03000011
_080A1114:
	ldr r0, _080A1134 @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A1138 @ =sFileSelectUnk_79e944
	ldr r0, _080A113C @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #0x10
	b _080A11B2
	.align 2, 0
_080A1134: .4byte gNonGameplayRam
_080A1138: .4byte sFileSelectUnk_79e944
_080A113C: .4byte 0x03000011
_080A1140:
	ldr r0, _080A1160 @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A1164 @ =sFileSelectUnk_79e944
	ldr r0, _080A1168 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #0x14
	b _080A11B2
	.align 2, 0
_080A1160: .4byte gNonGameplayRam
_080A1164: .4byte sFileSelectUnk_79e944
_080A1168: .4byte 0x03000011
_080A116C:
	ldr r0, _080A118C @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A1190 @ =sFileSelectUnk_79e944
	ldr r0, _080A1194 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
	adds r3, #0x18
	b _080A11B2
	.align 2, 0
_080A118C: .4byte gNonGameplayRam
_080A1190: .4byte sFileSelectUnk_79e944
_080A1194: .4byte 0x03000011
_080A1198:
	ldr r0, _080A11C0 @ =gNonGameplayRam
	lsls r1, r2, #3
	subs r1, r1, r2
	lsls r1, r1, #2
	adds r0, #0x2c
	adds r1, r1, r0
	ldr r3, _080A11C4 @ =sFileSelectUnk_79e944
	ldr r0, _080A11C8 @ =0x03000011
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r0, r0, #2
_080A11B2:
	adds r0, r0, r3
	ldr r0, [r0]
	str r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A11C0: .4byte gNonGameplayRam
_080A11C4: .4byte sFileSelectUnk_79e944
_080A11C8: .4byte 0x03000011

	thumb_func_start FileSelectProcessOam
FileSelectProcessOam: @ 0x080A11CC
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _080A1204 @ =gNonGameplayRam
	adds r6, r5, #0
	adds r6, #0x18
_080A11D6:
	lsls r0, r4, #3
	subs r0, r0, r4
	lsls r2, r0, #2
	adds r0, r2, r5
	ldrb r0, [r0, #0x1c]
	cmp r0, #0
	beq _080A11F2
	adds r1, r5, #0
	adds r1, #0x30
	adds r1, r2, r1
	adds r0, r2, r6
	ldr r1, [r1]
	bl _call_via_r1
_080A11F2:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x16
	bls _080A11D6
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1204: .4byte gNonGameplayRam

	thumb_func_start FileSelectDrawAllOam
FileSelectDrawAllOam: @ 0x080A1208
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _080A1240 @ =gNonGameplayRam
	adds r6, r5, #0
	adds r6, #0x18
_080A1212:
	lsls r0, r4, #3
	subs r0, r0, r4
	lsls r1, r0, #2
	adds r0, r1, r5
	ldrb r0, [r0, #0x1d]
	cmp r0, #0
	beq _080A1226
	adds r0, r1, r6
	bl FileSelectDrawOam
_080A1226:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x16
	bls _080A1212
	bl ResetFreeOam
	ldr r1, _080A1244 @ =gNextOamSlot
	movs r0, #0
	strb r0, [r1]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1240: .4byte gNonGameplayRam
_080A1244: .4byte gNextOamSlot

	thumb_func_start FileSelectDrawOam
FileSelectDrawOam: @ 0x080A1248
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r5, r0, #0
	ldr r2, _080A1308 @ =gNextOamSlot
	ldrb r0, [r2]
	lsls r0, r0, #3
	ldr r1, _080A130C @ =gOamData
	adds r7, r0, r1
	ldrb r4, [r5, #6]
	lsls r1, r4, #3
	ldr r0, [r5, #0x14]
	adds r3, r0, r1
	ldrb r0, [r3, #4]
	ldrb r2, [r5, #7]
	cmp r0, r2
	bne _080A1278
	adds r0, r4, #1
	movs r1, #0
	strb r0, [r5, #6]
	strb r1, [r5, #7]
	adds r3, #8
_080A1278:
	ldrb r1, [r3, #4]
	cmp r1, #0
	bne _080A1286
	ldrb r0, [r5, #6]
	lsls r0, r0, #3
	subs r3, r3, r0
	strb r1, [r5, #6]
_080A1286:
	ldr r6, [r3]
	ldrh r3, [r6]
	mov sl, r3
	adds r6, #2
	movs r4, #0
	mov sb, r4
	cmp sb, sl
	blt _080A1298
	b _080A139C
_080A1298:
	ldrh r0, [r6]
	mov r8, r0
	adds r6, #2
	ldrh r1, [r6]
	mov ip, r1
	adds r6, #2
	strh r0, [r7]
	adds r7, #2
	strh r1, [r7]
	adds r7, #2
	ldrh r0, [r6]
	strh r0, [r7]
	adds r6, #2
	adds r7, #2
	ldr r2, _080A1308 @ =gNextOamSlot
	ldrb r0, [r2]
	mov r4, sb
	adds r3, r0, r4
	ldrb r1, [r5, #0xc]
	cmp r1, #1
	bne _080A1318
	lsls r4, r3, #3
	ldr r0, _080A130C @ =gOamData
	adds r2, r4, r0
	ldrb r3, [r2, #3]
	lsls r0, r3, #0x1b
	lsrs r0, r0, #0x1f
	eors r0, r1
	movs r1, #1
	ands r0, r1
	lsls r0, r0, #4
	movs r1, #0x11
	rsbs r1, r1, #0
	ands r1, r3
	orrs r1, r0
	strb r1, [r2, #3]
	lsrs r1, r1, #6
	ldrb r0, [r2, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r2, _080A1310 @ =sFileSelectUnk_73dba4
	adds r1, r1, r2
	ldrb r0, [r1]
	lsls r0, r0, #3
	add r0, ip
	ldrh r1, [r5]
	subs r2, r1, r0
	ldr r3, _080A1314 @ =0x000001FF
	ands r2, r3
	ldrh r0, [r5, #2]
	mov r3, r8
	adds r1, r3, r0
	movs r0, #0xff
	ands r1, r0
	b _080A132E
	.align 2, 0
_080A1308: .4byte gNextOamSlot
_080A130C: .4byte gOamData
_080A1310: .4byte sFileSelectUnk_73dba4
_080A1314: .4byte 0x000001FF
_080A1318:
	ldrh r0, [r5, #2]
	mov r4, r8
	adds r1, r4, r0
	movs r0, #0xff
	ands r1, r0
	ldrh r0, [r5]
	mov r4, ip
	adds r2, r4, r0
	ldr r0, _080A13B8 @ =0x000001FF
	ands r2, r0
	lsls r4, r3, #3
_080A132E:
	ldr r0, _080A13BC @ =gOamData
	adds r3, r4, r0
	strb r1, [r3]
	ldr r1, _080A13B8 @ =0x000001FF
	ands r2, r1
	ldrh r1, [r3, #2]
	ldr r0, _080A13C0 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r3, #2]
	ldrb r1, [r5, #0xb]
	movs r2, #3
	ands r1, r2
	lsls r1, r1, #2
	ldrb r2, [r3, #5]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3, #5]
	lsrs r2, r0, #4
	ldrb r4, [r5, #0xd]
	adds r2, r2, r4
	lsls r2, r2, #4
	movs r1, #0xf
	ands r0, r1
	orrs r0, r2
	strb r0, [r3, #5]
	ldrh r2, [r3, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldrh r0, [r5, #0xe]
	adds r1, r1, r0
	ldr r4, _080A13C4 @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _080A13C8 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r3, #4]
	ldrb r1, [r5, #0xa]
	movs r0, #3
	ands r1, r0
	lsls r1, r1, #2
	ldrb r2, [r3, #1]
	subs r0, #0x10
	ands r0, r2
	orrs r0, r1
	strb r0, [r3, #1]
	adds r7, #2
	movs r1, #1
	add sb, r1
	cmp sb, sl
	bge _080A139C
	b _080A1298
_080A139C:
	ldr r2, _080A13CC @ =gNextOamSlot
	ldrb r0, [r2]
	add r0, sl
	strb r0, [r2]
	ldrb r0, [r5, #7]
	adds r0, #1
	strb r0, [r5, #7]
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A13B8: .4byte 0x000001FF
_080A13BC: .4byte gOamData
_080A13C0: .4byte 0xFFFFFE00
_080A13C4: .4byte 0x000003FF
_080A13C8: .4byte 0xFFFFFC00
_080A13CC: .4byte gNextOamSlot

	thumb_func_start SetLanguage
SetLanguage: @ 0x080A13D0
	ldr r1, _080A13DC @ =0x03000011
	movs r0, #2
	strb r0, [r1]
	movs r0, #1
	bx lr
	.align 2, 0
_080A13DC: .4byte 0x03000011

	thumb_func_start unk_a13e0
unk_a13e0: @ 0x080A13E0
	push {r4, lr}
	ldr r4, _080A1454 @ =0x04000208
	movs r1, #0
	strh r1, [r4]
	ldr r3, _080A1458 @ =0x04000004
	ldrh r2, [r3]
	ldr r0, _080A145C @ =0x0000FFEF
	ands r0, r2
	strh r0, [r3]
	ldr r3, _080A1460 @ =0x04000200
	ldrh r2, [r3]
	ldr r0, _080A1464 @ =0x0000FFFD
	ands r0, r2
	strh r0, [r3]
	movs r0, #1
	strh r0, [r4]
	movs r3, #0x80
	lsls r3, r3, #0x13
	strh r1, [r3]
	ldr r2, _080A1468 @ =0x04000050
	movs r0, #0xff
	strh r0, [r2]
	ldr r0, _080A146C @ =gWrittenToBldy
	movs r2, #0x10
	strh r2, [r0]
	ldr r0, _080A1470 @ =0x04000054
	strh r2, [r0]
	subs r0, #0x46
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	adds r0, #8
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	strh r1, [r3]
	ldr r0, _080A1474 @ =unk_a1478
	bl CallbackSetVBlank
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A1454: .4byte 0x04000208
_080A1458: .4byte 0x04000004
_080A145C: .4byte 0x0000FFEF
_080A1460: .4byte 0x04000200
_080A1464: .4byte 0x0000FFFD
_080A1468: .4byte 0x04000050
_080A146C: .4byte gWrittenToBldy
_080A1470: .4byte 0x04000054
_080A1474: .4byte unk_a1478

	thumb_func_start unk_a1478
unk_a1478: @ 0x080A1478
	bx lr
	.align 2, 0

	thumb_func_start unk_a147c
unk_a147c: @ 0x080A147C
	movs r0, #1
	bx lr

	thumb_func_start EndingDrawIgtAndCompletionPercentage
EndingDrawIgtAndCompletionPercentage: @ 0x080A1480
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	movs r1, #0
	ldr r0, _080A1548 @ =gInGameTimer
	ldrb r4, [r0]
	ldr r7, _080A154C @ =sEndingUnk_74e650
	ldr r2, _080A1550 @ =sEndingUnk_74e8d0
	mov ip, r2
	ldr r5, _080A1554 @ =gNonGameplayRam
	mov r8, r5
	cmp r4, #9
	ble _080A14A4
_080A149C:
	subs r4, #0xa
	adds r1, #1
	cmp r4, #9
	bgt _080A149C
_080A14A4:
	movs r6, #0
	ldrb r5, [r0, #1]
	lsls r4, r4, #6
	mov sb, r4
	cmp r5, #9
	ble _080A14B8
_080A14B0:
	subs r5, #0xa
	adds r6, #1
	cmp r5, #9
	bgt _080A14B0
_080A14B8:
	cmp r1, #0
	beq _080A14DC
	lsls r3, r1, #6
	ldr r0, _080A1558 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A155C @ =0x06010000
	str r1, [r0, #4]
	ldr r2, _080A1560 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A1564 @ =0x06010400
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
_080A14DC:
	mov r3, sb
	ldr r0, _080A1558 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1568 @ =0x06010040
	str r1, [r0, #4]
	ldr r2, _080A1560 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A156C @ =0x06010440
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	lsls r3, r6, #6
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1570 @ =0x060100A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A1574 @ =0x060104A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	lsls r3, r5, #6
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1578 @ =0x060100E0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A157C @ =0x060104E0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	movs r1, #0
	movs r4, #0
	mov r0, r8
	adds r0, #0x9a
	ldrb r6, [r0]
	cmp r6, #0x63
	ble _080A1584
_080A153E:
	subs r6, #0x64
	adds r1, #1
	cmp r6, #0x63
	bgt _080A153E
	b _080A1584
	.align 2, 0
_080A1548: .4byte gInGameTimer
_080A154C: .4byte sEndingUnk_74e650
_080A1550: .4byte sEndingUnk_74e8d0
_080A1554: .4byte gNonGameplayRam
_080A1558: .4byte 0x040000D4
_080A155C: .4byte 0x06010000
_080A1560: .4byte 0x80000020
_080A1564: .4byte 0x06010400
_080A1568: .4byte 0x06010040
_080A156C: .4byte 0x06010440
_080A1570: .4byte 0x060100A0
_080A1574: .4byte 0x060104A0
_080A1578: .4byte 0x060100E0
_080A157C: .4byte 0x060104E0
_080A1580:
	subs r6, #0xa
	adds r4, #1
_080A1584:
	cmp r6, #9
	bgt _080A1580
	cmp r1, #0
	beq _080A15C0
	lsls r3, r1, #6
	ldr r0, _080A15B0 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A15B4 @ =0x06010120
	str r1, [r0, #4]
	ldr r2, _080A15B8 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r5, ip
	adds r1, r3, r5
	str r1, [r0]
	ldr r1, _080A15BC @ =0x06010520
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	b _080A15C4
	.align 2, 0
_080A15B0: .4byte 0x040000D4
_080A15B4: .4byte 0x06010120
_080A15B8: .4byte 0x80000020
_080A15BC: .4byte 0x06010520
_080A15C0:
	cmp r4, #0
	beq _080A15E4
_080A15C4:
	lsls r3, r4, #6
	ldr r0, _080A1610 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1614 @ =0x06010160
	str r1, [r0, #4]
	ldr r2, _080A1618 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A161C @ =0x06010560
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
_080A15E4:
	lsls r3, r6, #6
	ldr r0, _080A1610 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1620 @ =0x060101A0
	str r1, [r0, #4]
	ldr r2, _080A1618 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r5, ip
	adds r1, r3, r5
	str r1, [r0]
	ldr r1, _080A1624 @ =0x060105A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1610: .4byte 0x040000D4
_080A1614: .4byte 0x06010160
_080A1618: .4byte 0x80000020
_080A161C: .4byte 0x06010560
_080A1620: .4byte 0x060101A0
_080A1624: .4byte 0x060105A0

	thumb_func_start EndingImageUpdateLettersSpawnDelay
EndingImageUpdateLettersSpawnDelay: @ 0x080A1628
	push {r4, lr}
	adds r3, r0, #0
	ldr r1, _080A1660 @ =gNonGameplayRam
	movs r2, #0x92
	lsls r2, r2, #1
	adds r0, r1, r2
	adds r2, r3, r0
	ldrb r0, [r2]
	cmp r0, #0
	beq _080A165A
	movs r4, #0xa1
	lsls r4, r4, #1
	adds r0, r1, r4
	adds r1, r3, r0
	ldrb r0, [r1]
	cmp r0, #0
	beq _080A165A
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A165A
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
_080A165A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A1660: .4byte gNonGameplayRam

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

	thumb_func_start EndingImageDisplayLinePermanently
EndingImageDisplayLinePermanently: @ 0x080A1B60
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r0, _080A1B7C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _080A1BA4
	cmp r0, #4
	bgt _080A1B80
	cmp r0, #3
	beq _080A1B8A
	b _080A1BEC
	.align 2, 0
_080A1B7C: .4byte 0x03000011
_080A1B80:
	cmp r0, #5
	beq _080A1BBC
	cmp r0, #6
	beq _080A1BD4
	b _080A1BEC
_080A1B8A:
	ldr r0, _080A1B9C @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BA0 @ =sEndingUnk_74de4c
	b _080A1BFA
	.align 2, 0
_080A1B9C: .4byte gNonGameplayRam
_080A1BA0: .4byte sEndingUnk_74de4c
_080A1BA4:
	ldr r0, _080A1BB4 @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BB8 @ =sEndingUnk_74dfd8
	b _080A1BFA
	.align 2, 0
_080A1BB4: .4byte gNonGameplayRam
_080A1BB8: .4byte sEndingUnk_74dfd8
_080A1BBC:
	ldr r0, _080A1BCC @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BD0 @ =sEndingUnk_74e1d0
	b _080A1BFA
	.align 2, 0
_080A1BCC: .4byte gNonGameplayRam
_080A1BD0: .4byte sEndingUnk_74e1d0
_080A1BD4:
	ldr r0, _080A1BE4 @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BE8 @ =sEndingUnk_74e440
	b _080A1BFA
	.align 2, 0
_080A1BE4: .4byte gNonGameplayRam
_080A1BE8: .4byte sEndingUnk_74e440
_080A1BEC:
	ldr r0, _080A1C7C @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1C80 @ =sEndingUnk_74dc48
_080A1BFA:
	lsls r3, r6, #1
	adds r4, r3, r6
	lsls r4, r4, #2
	adds r2, r4, r5
	ldrb r0, [r2]
	strb r0, [r1]
	movs r0, #0xa1
	lsls r0, r0, #1
	add r0, ip
	adds r0, r6, r0
	ldrb r1, [r2, #1]
	strb r1, [r0]
	movs r0, #0xb0
	lsls r0, r0, #1
	add r0, ip
	adds r0, r6, r0
	ldrb r1, [r2, #2]
	strb r1, [r0]
	movs r0, #0xbf
	lsls r0, r0, #1
	add r0, ip
	adds r0, r3, r0
	ldrh r1, [r2, #4]
	strh r1, [r0]
	movs r0, #0xdd
	lsls r0, r0, #1
	add r0, ip
	adds r3, r3, r0
	ldrh r0, [r2, #6]
	strh r0, [r3]
	lsls r1, r6, #2
	movs r0, #0xfc
	lsls r0, r0, #1
	add r0, ip
	adds r1, r1, r0
	adds r5, #8
	adds r4, r4, r5
	ldr r0, [r4]
	str r0, [r1]
	mov r1, ip
	movs r3, #0
	adds r2, r1, #0
	adds r2, #0x9b
	ldrb r0, [r2]
	subs r0, #6
	cmp r3, r0
	bge _080A1C70
	movs r5, #0
	adds r4, r2, #0
	movs r0, #0x95
	lsls r0, r0, #1
	adds r2, r1, r0
_080A1C62:
	strb r5, [r2]
	adds r2, #1
	adds r3, #1
	ldrb r0, [r4]
	subs r0, #6
	cmp r3, r0
	blt _080A1C62
_080A1C70:
	adds r1, #0x9b
	movs r0, #6
	strb r0, [r1]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1C7C: .4byte gNonGameplayRam
_080A1C80: .4byte sEndingUnk_74dc48

