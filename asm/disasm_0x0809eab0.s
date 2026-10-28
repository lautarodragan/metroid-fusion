    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start FileSelectInput
FileSelectInput: @ 0x0809EAB0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	movs r7, #0
	bl FileSelectProcessOam
	ldr r0, _0809EAD4 @ =gNonGameplayRam
	movs r1, #0xa
	ldrsh r0, [r0, r1]
	cmp r0, #0x22
	bls _0809EAC8
	bl _0809F50A
_0809EAC8:
	lsls r0, r0, #2
	ldr r1, _0809EAD8 @ =_0809EADC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0809EAD4: .4byte gNonGameplayRam
_0809EAD8: .4byte _0809EADC
_0809EADC: @ jump table
	.4byte _0809EB68 @ case 0
	.4byte _0809EBB0 @ case 1
	.4byte _0809EC88 @ case 2
	.4byte _0809ECF8 @ case 3
	.4byte _0809ECC8 @ case 4
	.4byte _0809ED9A @ case 5
	.4byte _0809EF3C @ case 6
	.4byte _0809EDB8 @ case 7
	.4byte _0809EF24 @ case 8
	.4byte _0809EDD4 @ case 9
	.4byte _0809EE42 @ case 10
	.4byte _0809EE82 @ case 11
	.4byte _0809EEA0 @ case 12
	.4byte _0809EEDE @ case 13
	.4byte _0809EF24 @ case 14
	.4byte _0809EF3C @ case 15
	.4byte _0809EF54 @ case 16
	.4byte _0809EFE0 @ case 17
	.4byte _0809F042 @ case 18
	.4byte _0809F068 @ case 19
	.4byte _0809F0E4 @ case 20
	.4byte _0809F124 @ case 21
	.4byte _0809F162 @ case 22
	.4byte _0809F1A2 @ case 23
	.4byte _0809F1EC @ case 24
	.4byte _0809F24A @ case 25
	.4byte _0809F2B6 @ case 26
	.4byte _0809F2E4 @ case 27
	.4byte _0809F374 @ case 28
	.4byte _0809F3B2 @ case 29
	.4byte _0809F3EA @ case 30
	.4byte _0809F418 @ case 31
	.4byte _0809F446 @ case 32
	.4byte _0809F4AA @ case 33
	.4byte _0809F508 @ case 34
_0809EB68:
	ldr r0, _0809EB8C @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	beq _0809EB94
	ldr r1, _0809EB90 @ =gNonGameplayRam
	ldrb r0, [r1, #0xd]
	cmp r0, #3
	bne _0809EB80
	bl _0809F50A
_0809EB80:
	cmp r0, #4
	beq _0809EBA2
	movs r0, #1
	strh r0, [r1, #0xa]
	bl _0809F50A
	.align 2, 0
_0809EB8C: .4byte gChangedInput
_0809EB90: .4byte gNonGameplayRam
_0809EB94:
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0809EBA0
	bl _0809F50A
_0809EBA0:
	ldr r1, _0809EBAC @ =gNonGameplayRam
_0809EBA2:
	movs r0, #0x22
	strh r0, [r1, #0xa]
	bl _0809F50A
	.align 2, 0
_0809EBAC: .4byte gNonGameplayRam
_0809EBB0:
	ldr r1, _0809EBE8 @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r4, r1, #0
	cmp r0, #1
	bne _0809EBF4
	strh r0, [r4, #8]
	ldr r1, _0809EBEC @ =sFileSelectUnk_79ec68
	ldr r0, _0809EBF0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #4]
	movs r0, #2
	bl FileSelectDrawText
	movs r0, #0xb
	movs r1, #0x52
	movs r2, #0x76
	b _0809F2FC
	.align 2, 0
_0809EBE8: .4byte gNonGameplayRam
_0809EBEC: .4byte sFileSelectUnk_79ec68
_0809EBF0: .4byte 0x03000011
_0809EBF4:
	cmp r0, #0xc
	beq _0809EBFC
	bl _0809F50A
_0809EBFC:
	ldr r2, _0809EC34 @ =0x03000B94
	ldrb r1, [r4, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r2
	movs r0, #0x10
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _0809EC1E
	movs r0, #0x11
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _0809EC1E
	ldrb r0, [r1]
	cmp r0, #1
	bne _0809EC48
_0809EC1E:
	ldr r1, _0809EC38 @ =0x040000D4
	ldr r0, _0809EC3C @ =0x02000340
	str r0, [r1]
	ldr r0, _0809EC40 @ =0x0600EB40
	str r0, [r1, #4]
	ldr r0, _0809EC44 @ =0x84000040
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #3
	b _0809EC5A
	.align 2, 0
_0809EC34: .4byte 0x03000B94
_0809EC38: .4byte 0x040000D4
_0809EC3C: .4byte 0x02000340
_0809EC40: .4byte 0x0600EB40
_0809EC44: .4byte 0x84000040
_0809EC48:
	ldr r1, _0809EC78 @ =0x040000D4
	ldr r0, _0809EC7C @ =0x02000800
	str r0, [r1]
	ldr r0, _0809EC80 @ =0x0600EB40
	str r0, [r1, #4]
	ldr r0, _0809EC84 @ =0x84000040
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #2
_0809EC5A:
	strh r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xc]
	strb r0, [r4, #0xe]
	movs r0, #2
	movs r1, #0x16
	movs r2, #0x67
	movs r3, #1
	bl FileSelectSetupOam
	movs r0, #3
	strb r0, [r4, #0x11]
	bl _0809F50A
	.align 2, 0
_0809EC78: .4byte 0x040000D4
_0809EC7C: .4byte 0x02000800
_0809EC80: .4byte 0x0600EB40
_0809EC84: .4byte 0x84000040
_0809EC88:
	ldr r0, _0809ECBC @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0809ED04
	movs r4, #9
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _0809ECA2
	bl _0809F50A
_0809ECA2:
	ldr r2, _0809ECC0 @ =0x03000B94
	ldr r3, _0809ECC4 @ =gNonGameplayRam
	ldrb r1, [r3, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldrb r0, [r0, #0x10]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	beq _0809ED74
	b _0809ED54
	.align 2, 0
_0809ECBC: .4byte gChangedInput
_0809ECC0: .4byte 0x03000B94
_0809ECC4: .4byte gNonGameplayRam
_0809ECC8:
	ldr r4, _0809ECE8 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809ECEC
	movs r0, #2
	bl FileSelectDestroyOamOfType
	movs r0, #4
	strb r0, [r4, #0x11]
	bl _0809F50A
	.align 2, 0
_0809ECE8: .4byte gNonGameplayRam
_0809ECEC:
	cmp r0, #0xc
	beq _0809ECF4
	bl _0809F50A
_0809ECF4:
	bl _0809F502
_0809ECF8:
	ldr r0, _0809ED10 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0809ED18
_0809ED04:
	ldr r1, _0809ED14 @ =gNonGameplayRam
	movs r0, #4
	strh r0, [r1, #0xa]
	bl _0809F50A
	.align 2, 0
_0809ED10: .4byte gChangedInput
_0809ED14: .4byte gNonGameplayRam
_0809ED18:
	movs r4, #9
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _0809ED26
	bl _0809F50A
_0809ED26:
	ldr r3, _0809ED5C @ =gNonGameplayRam
	ldrb r0, [r3, #0xe]
	cmp r0, #0
	bne _0809ED82
	ldr r2, _0809ED60 @ =0x03000B94
	ldrb r1, [r3, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r2
	ldrb r0, [r1]
	cmp r0, #0
	bne _0809ED64
	movs r0, #0x10
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _0809ED74
	movs r0, #0x11
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _0809ED54
	bl _0809F50A
_0809ED54:
	movs r0, #5
	strh r0, [r3, #0xa]
	bl _0809F50A
	.align 2, 0
_0809ED5C: .4byte gNonGameplayRam
_0809ED60: .4byte 0x03000B94
_0809ED64:
	cmp r0, #1
	beq _0809ED6C
	bl _0809F50A
_0809ED6C:
	movs r0, #0x10
	ldrsb r0, [r1, r0]
	cmp r0, #1
	bne _0809ED7A
_0809ED74:
	strh r4, [r3, #0xa]
	bl _0809F50A
_0809ED7A:
	movs r0, #7
	strh r0, [r3, #0xa]
	bl _0809F50A
_0809ED82:
	cmp r0, #1
	bne _0809ED8C
	movs r1, #0
	movs r0, #0x10
	b _0809EF1E
_0809ED8C:
	cmp r0, #2
	beq _0809ED94
	bl _0809F50A
_0809ED94:
	movs r0, #0x1b
	strh r0, [r3, #0xa]
	b _0809F50A
_0809ED9A:
	ldr r2, _0809EDB4 @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x2a
	beq _0809EDAC
	b _0809F50A
_0809EDAC:
	movs r1, #0
	movs r0, #6
	b _0809F4A4
	.align 2, 0
_0809EDB4: .4byte gNonGameplayRam
_0809EDB8:
	ldr r2, _0809EDD0 @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x2a
	beq _0809EDCA
	b _0809F50A
_0809EDCA:
	movs r1, #0
	movs r0, #8
	b _0809F4A4
	.align 2, 0
_0809EDD0: .4byte gNonGameplayRam
_0809EDD4:
	ldr r4, _0809EDF4 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809EDF8
	movs r0, #0x17
	movs r1, #0x9c
	movs r2, #0x78
	movs r3, #1
	bl FileSelectSetupOam
	b _0809F3CA
	.align 2, 0
_0809EDF4: .4byte gNonGameplayRam
_0809EDF8:
	cmp r0, #2
	bne _0809EDFE
	b _0809F4D8
_0809EDFE:
	cmp r0, #3
	bne _0809EE24
	movs r0, #0x18
	strh r0, [r4, #8]
	ldr r1, _0809EE1C @ =sFileSelectUnk_79ec68
	ldr r0, _0809EE20 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #0x60]
	str r0, [r4, #4]
	b _0809F32C
	.align 2, 0
_0809EE1C: .4byte sFileSelectUnk_79ec68
_0809EE20: .4byte 0x03000011
_0809EE24:
	cmp r0, #0xc
	beq _0809EE2A
	b _0809F50A
_0809EE2A:
	strb r1, [r4, #0xc]
	movs r0, #0xa
	strh r0, [r4, #0xa]
	movs r0, #0x18
	movs r1, #0x66
	movs r2, #0x69
	movs r3, #1
	bl FileSelectSetupOam
	movs r0, #1
	strb r0, [r4, #0x11]
	b _0809F50A
_0809EE42:
	ldr r0, _0809EE58 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0809EE60
	ldr r1, _0809EE5C @ =gNonGameplayRam
	movs r0, #0xb
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809EE58: .4byte gChangedInput
_0809EE5C: .4byte gNonGameplayRam
_0809EE60:
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	bne _0809EE6A
	b _0809F50A
_0809EE6A:
	ldr r1, _0809EE78 @ =gNonGameplayRam
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _0809EE7C
	movs r0, #0xc
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809EE78: .4byte gNonGameplayRam
_0809EE7C:
	movs r0, #0xd
	strh r0, [r1, #0xa]
	b _0809F50A
_0809EE82:
	ldr r4, _0809EE9C @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	beq _0809EE96
	b _0809F3DA
_0809EE96:
	movs r0, #0x18
	b _0809F3C6
	.align 2, 0
_0809EE9C: .4byte gNonGameplayRam
_0809EEA0:
	ldr r3, _0809EED0 @ =gNonGameplayRam
	ldrb r0, [r3, #0xc]
	adds r0, #1
	strb r0, [r3, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x2a
	beq _0809EEB2
	b _0809F50A
_0809EEB2:
	movs r0, #0
	strb r0, [r3, #0xc]
	ldr r2, _0809EED4 @ =0x03000B94
	ldrb r1, [r3, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #1
	bne _0809EED8
	movs r0, #0xe
	strh r0, [r3, #0xa]
	b _0809F50A
	.align 2, 0
_0809EED0: .4byte gNonGameplayRam
_0809EED4: .4byte 0x03000B94
_0809EED8:
	movs r0, #0xf
	strh r0, [r3, #0xa]
	b _0809F50A
_0809EEDE:
	ldr r3, _0809EF0C @ =gNonGameplayRam
	ldrb r0, [r3, #0xc]
	adds r0, #1
	movs r4, #0
	strb r0, [r3, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809EF14
	ldr r2, _0809EF10 @ =0x03000B94
	ldrb r1, [r3, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	strb r4, [r0]
	ldrb r1, [r3, #0xd]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	strb r4, [r0, #0x11]
	b _0809F50A
	.align 2, 0
_0809EF0C: .4byte gNonGameplayRam
_0809EF10: .4byte 0x03000B94
_0809EF14:
	cmp r0, #0x2a
	beq _0809EF1A
	b _0809F50A
_0809EF1A:
	movs r1, #0
	movs r0, #0xf
_0809EF1E:
	strh r0, [r3, #0xa]
	strb r1, [r3, #0xc]
	b _0809F50A
_0809EF24:
	ldr r0, _0809EF34 @ =0x03000B8D
	ldr r1, _0809EF38 @ =gNonGameplayRam
	ldrb r1, [r1, #0xd]
	strb r1, [r0]
	bl Sram_CheckLoadSaveFile
	movs r7, #2
	b _0809F50A
	.align 2, 0
_0809EF34: .4byte 0x03000B8D
_0809EF38: .4byte gNonGameplayRam
_0809EF3C:
	ldr r0, _0809EF4C @ =0x03000B8D
	ldr r1, _0809EF50 @ =gNonGameplayRam
	ldrb r1, [r1, #0xd]
	strb r1, [r0]
	bl Sram_CheckLoadSaveFile
	movs r7, #1
	b _0809F50A
	.align 2, 0
_0809EF4C: .4byte 0x03000B8D
_0809EF50: .4byte gNonGameplayRam
_0809EF54:
	ldr r2, _0809EF6C @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809EF70
	movs r0, #2
	strb r0, [r2, #0x11]
	movs r0, #0xc
	b _0809F2F8
	.align 2, 0
_0809EF6C: .4byte gNonGameplayRam
_0809EF70:
	cmp r0, #2
	bne _0809EF7A
	movs r0, #0
	str r0, [sp]
	b _0809F4DA
_0809EF7A:
	cmp r0, #3
	bne _0809EFA0
	movs r0, #2
	strh r0, [r2, #8]
	ldr r1, _0809EF98 @ =sFileSelectUnk_79ec68
	ldr r0, _0809EF9C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #4]
	b _0809F32C
	.align 2, 0
_0809EF98: .4byte sFileSelectUnk_79ec68
_0809EF9C: .4byte 0x03000011
_0809EFA0:
	cmp r0, #0xc
	beq _0809EFA6
	b _0809F50A
_0809EFA6:
	movs r0, #0
	movs r1, #0x11
	strh r1, [r2, #0xa]
	strb r0, [r2, #0xc]
	strb r0, [r2, #0xf]
	ldrb r0, [r2, #0xd]
	cmp r0, #0
	bne _0809EFC8
	movs r0, #1
	strb r0, [r2, #0xf]
	movs r0, #3
	movs r1, #0x84
	movs r2, #0x30
	movs r3, #1
	bl FileSelectSetupOam
	b _0809EFD4
_0809EFC8:
	movs r0, #3
	movs r1, #0x84
	movs r2, #0x30
	movs r3, #1
	bl FileSelectSetupOam
_0809EFD4:
	ldr r1, _0809EFDC @ =gNonGameplayRam
	movs r0, #1
	strb r0, [r1, #0x11]
	b _0809F50A
	.align 2, 0
_0809EFDC: .4byte gNonGameplayRam
_0809EFE0:
	ldr r0, _0809EFF4 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0809EFFC
	ldr r1, _0809EFF8 @ =gNonGameplayRam
	movs r0, #0x12
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809EFF4: .4byte gChangedInput
_0809EFF8: .4byte gNonGameplayRam
_0809EFFC:
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	bne _0809F006
	b _0809F50A
_0809F006:
	ldr r2, _0809F034 @ =0x03000B94
	ldr r3, _0809F038 @ =gNonGameplayRam
	ldrb r1, [r3, #0xf]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r2
	movs r0, #0x10
	ldrsb r0, [r1, r0]
	adds r4, r3, #0
	cmp r0, #1
	beq _0809F02C
	movs r0, #0x11
	ldrsb r0, [r1, r0]
	cmp r0, #1
	beq _0809F02C
	ldrb r0, [r1]
	cmp r0, #1
	bne _0809F03C
_0809F02C:
	movs r0, #0x13
	strh r0, [r4, #0xa]
	b _0809F50A
	.align 2, 0
_0809F034: .4byte 0x03000B94
_0809F038: .4byte gNonGameplayRam
_0809F03C:
	movs r0, #0x14
	strh r0, [r3, #0xa]
	b _0809F50A
_0809F042:
	ldr r4, _0809F058 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F05C
	movs r0, #3
	b _0809F3C6
	.align 2, 0
_0809F058: .4byte gNonGameplayRam
_0809F05C:
	cmp r0, #0xc
	beq _0809F062
	b _0809F50A
_0809F062:
	movs r0, #0
	strb r0, [r4, #0xc]
	b _0809F3E4
_0809F068:
	ldr r2, _0809F084 @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	movs r3, #0
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F088
	movs r0, #2
	strb r0, [r2, #0x11]
	str r3, [sp]
	b _0809F4DA
	.align 2, 0
_0809F084: .4byte gNonGameplayRam
_0809F088:
	cmp r0, #2
	bne _0809F0B0
	movs r0, #3
	strh r0, [r2, #8]
	ldr r1, _0809F0A8 @ =sFileSelectUnk_79ec68
	ldr r0, _0809F0AC @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #4]
	b _0809F32C
	.align 2, 0
_0809F0A8: .4byte sFileSelectUnk_79ec68
_0809F0AC: .4byte 0x03000011
_0809F0B0:
	cmp r0, #4
	beq _0809F0B6
	b _0809F50A
_0809F0B6:
	movs r1, #1
	strb r1, [r2, #0x11]
	strb r3, [r2, #0xc]
	movs r0, #0x16
	strh r0, [r2, #0xa]
	strb r1, [r2, #0x10]
	ldr r1, _0809F0DC @ =sFileSelectUnk_73dbb0
	ldr r0, _0809F0E0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r1, #1
	adds r0, r0, r1
	ldrb r1, [r0]
	movs r0, #4
	movs r2, #0x91
	b _0809F2FC
	.align 2, 0
_0809F0DC: .4byte sFileSelectUnk_73dbb0
_0809F0E0: .4byte 0x03000011
_0809F0E4:
	ldr r2, _0809F120 @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F0F6
	b _0809F25A
_0809F0F6:
	cmp r0, #2
	bne _0809F0FC
	b _0809F278
_0809F0FC:
	cmp r0, #3
	bne _0809F102
	b _0809F286
_0809F102:
	cmp r0, #4
	bne _0809F108
	b _0809F294
_0809F108:
	cmp r0, #6
	bne _0809F10E
	b _0809F2A2
_0809F10E:
	cmp r0, #0xc
	beq _0809F114
	b _0809F50A
_0809F114:
	movs r0, #0
	strb r0, [r2, #0xc]
	movs r0, #0x15
	strh r0, [r2, #0xa]
	b _0809F50A
	.align 2, 0
_0809F120: .4byte gNonGameplayRam
_0809F124:
	ldr r1, _0809F148 @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	movs r2, #0
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F14C
	movs r0, #5
	strb r0, [r1, #0x11]
	movs r0, #2
	bl FileSelectDestroyOamOfType
	movs r0, #3
	bl FileSelectDestroyOamOfType
	b _0809F50A
	.align 2, 0
_0809F148: .4byte gNonGameplayRam
_0809F14C:
	cmp r0, #4
	bne _0809F152
	b _0809F50A
_0809F152:
	cmp r0, #0xc
	beq _0809F158
	b _0809F50A
_0809F158:
	strb r2, [r1, #0xf]
	strb r2, [r1, #0xe]
	strb r2, [r1, #0xc]
	strh r2, [r1, #0xa]
	b _0809F50A
_0809F162:
	ldr r0, _0809F178 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0809F180
	ldr r1, _0809F17C @ =gNonGameplayRam
	movs r0, #0x17
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809F178: .4byte gChangedInput
_0809F17C: .4byte gNonGameplayRam
_0809F180:
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	bne _0809F18A
	b _0809F50A
_0809F18A:
	ldr r1, _0809F198 @ =gNonGameplayRam
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _0809F19C
	movs r0, #0x19
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809F198: .4byte gNonGameplayRam
_0809F19C:
	movs r0, #0x18
	strh r0, [r1, #0xa]
	b _0809F50A
_0809F1A2:
	ldr r4, _0809F1B8 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F1BC
	movs r0, #4
	b _0809F3C6
	.align 2, 0
_0809F1B8: .4byte gNonGameplayRam
_0809F1BC:
	cmp r0, #2
	bne _0809F1C6
	movs r0, #0
	str r0, [sp]
	b _0809F4DA
_0809F1C6:
	cmp r0, #3
	bne _0809F234
	movs r0, #2
	strh r0, [r4, #8]
	ldr r1, _0809F1E4 @ =sFileSelectUnk_79ec68
	ldr r0, _0809F1E8 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #4]
	b _0809F32C
	.align 2, 0
_0809F1E4: .4byte sFileSelectUnk_79ec68
_0809F1E8: .4byte 0x03000011
_0809F1EC:
	ldr r4, _0809F200 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #9
	bne _0809F204
	movs r0, #4
	b _0809F3C6
	.align 2, 0
_0809F200: .4byte gNonGameplayRam
_0809F204:
	cmp r0, #0xa
	bne _0809F20E
	movs r0, #0
	str r0, [sp]
	b _0809F4DA
_0809F20E:
	cmp r0, #0xb
	bne _0809F234
	movs r0, #2
	strh r0, [r4, #8]
	ldr r1, _0809F22C @ =sFileSelectUnk_79ec68
	ldr r0, _0809F230 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #4]
	b _0809F32C
	.align 2, 0
_0809F22C: .4byte sFileSelectUnk_79ec68
_0809F230: .4byte 0x03000011
_0809F234:
	cmp r0, #0xc
	beq _0809F23A
	b _0809F50A
_0809F23A:
	movs r0, #1
	strb r0, [r4, #0x11]
	movs r1, #0
	movs r0, #0x11
	strh r0, [r4, #0xa]
	strb r1, [r4, #0xc]
	strb r1, [r4, #0x10]
	b _0809F50A
_0809F24A:
	ldr r2, _0809F26C @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F274
_0809F25A:
	ldr r0, _0809F270 @ =0x03000B8D
	ldrb r1, [r2, #0xd]
	strb r1, [r0]
	ldrb r0, [r2, #0xf]
	movs r1, #0
	bl Sram_CopyFile
	b _0809F50A
	.align 2, 0
_0809F26C: .4byte gNonGameplayRam
_0809F270: .4byte 0x03000B8D
_0809F274:
	cmp r0, #2
	bne _0809F282
_0809F278:
	ldrb r0, [r2, #0xf]
	movs r1, #1
	bl Sram_CopyFile
	b _0809F50A
_0809F282:
	cmp r0, #3
	bne _0809F290
_0809F286:
	ldrb r0, [r2, #0xf]
	movs r1, #2
	bl Sram_CopyFile
	b _0809F50A
_0809F290:
	cmp r0, #4
	bne _0809F29E
_0809F294:
	ldrb r0, [r2, #0xf]
	movs r1, #3
	bl Sram_CopyFile
	b _0809F50A
_0809F29E:
	cmp r0, #0xb
	bne _0809F2AA
_0809F2A2:
	ldrb r0, [r2, #0xf]
	bl FileSelectDrawFileInfo
	b _0809F50A
_0809F2AA:
	cmp r0, #0xc
	beq _0809F2B0
	b _0809F50A
_0809F2B0:
	movs r1, #0
	movs r0, #0x1a
	b _0809F4A4
_0809F2B6:
	ldr r4, _0809F2D8 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F2DC
	movs r0, #2
	bl FileSelectDestroyOamOfType
	movs r0, #3
	bl FileSelectDestroyOamOfType
	movs r0, #4
	b _0809F4C4
	.align 2, 0
_0809F2D8: .4byte gNonGameplayRam
_0809F2DC:
	cmp r0, #2
	bne _0809F2E2
	b _0809F4D8
_0809F2E2:
	b _0809F4F8
_0809F2E4:
	ldr r5, _0809F304 @ =gNonGameplayRam
	ldrb r0, [r5, #0xc]
	adds r0, #1
	movs r6, #0
	strb r0, [r5, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F308
	movs r0, #0xd
_0809F2F8:
	movs r1, #0x9c
	movs r2, #0x78
_0809F2FC:
	movs r3, #1
	bl FileSelectSetupOam
	b _0809F50A
	.align 2, 0
_0809F304: .4byte gNonGameplayRam
_0809F308:
	cmp r0, #2
	bne _0809F310
	str r6, [sp]
	b _0809F4DA
_0809F310:
	cmp r0, #3
	bne _0809F33C
	movs r0, #4
	strh r0, [r5, #8]
	ldr r1, _0809F334 @ =sFileSelectUnk_79ec68
	ldr r0, _0809F338 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #4]
_0809F32C:
	movs r0, #3
	bl FileSelectDrawText
	b _0809F50A
	.align 2, 0
_0809F334: .4byte sFileSelectUnk_79ec68
_0809F338: .4byte 0x03000011
_0809F33C:
	cmp r0, #0xc
	beq _0809F342
	b _0809F50A
_0809F342:
	movs r4, #1
	strb r4, [r5, #0x10]
	ldr r1, _0809F36C @ =sFileSelectUnk_73dbbe
	ldr r0, _0809F370 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #1
	adds r1, #1
	adds r0, r0, r1
	ldrb r1, [r0]
	movs r0, #5
	movs r2, #0x91
	movs r3, #1
	bl FileSelectSetupOam
	strb r4, [r5, #0x11]
	strb r6, [r5, #0xc]
	movs r0, #0x1c
	strh r0, [r5, #0xa]
	b _0809F50A
	.align 2, 0
_0809F36C: .4byte sFileSelectUnk_73dbbe
_0809F370: .4byte 0x03000011
_0809F374:
	ldr r0, _0809F388 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0809F390
	ldr r1, _0809F38C @ =gNonGameplayRam
	movs r0, #0x1d
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809F388: .4byte gChangedInput
_0809F38C: .4byte gNonGameplayRam
_0809F390:
	movs r0, #9
	ands r0, r1
	cmp r0, #0
	bne _0809F39A
	b _0809F50A
_0809F39A:
	ldr r1, _0809F3A8 @ =gNonGameplayRam
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	bne _0809F3AC
	movs r0, #0x20
	strh r0, [r1, #0xa]
	b _0809F50A
	.align 2, 0
_0809F3A8: .4byte gNonGameplayRam
_0809F3AC:
	movs r0, #0x1e
	strh r0, [r1, #0xa]
	b _0809F50A
_0809F3B2:
	ldr r4, _0809F3D0 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F3D4
	movs r0, #5
_0809F3C6:
	bl FileSelectDestroyOamOfType
_0809F3CA:
	movs r0, #2
	strb r0, [r4, #0x11]
	b _0809F50A
	.align 2, 0
_0809F3D0: .4byte gNonGameplayRam
_0809F3D4:
	cmp r0, #2
	bne _0809F3DA
	b _0809F4D8
_0809F3DA:
	cmp r0, #0xc
	beq _0809F3E0
	b _0809F50A
_0809F3E0:
	strb r1, [r4, #0xc]
	strb r1, [r4, #0x10]
_0809F3E4:
	movs r0, #3
	strh r0, [r4, #0xa]
	b _0809F50A
_0809F3EA:
	ldr r4, _0809F414 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r5, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #8
	beq _0809F3FE
	b _0809F50A
_0809F3FE:
	movs r0, #5
	bl FileSelectDestroyOamOfType
	movs r0, #2
	strb r0, [r4, #0x11]
	strb r5, [r4, #0xc]
	strb r5, [r4, #0x10]
	movs r0, #0x1f
	strh r0, [r4, #0xa]
	b _0809F50A
	.align 2, 0
_0809F414: .4byte gNonGameplayRam
_0809F418:
	ldr r1, _0809F434 @ =gNonGameplayRam
	ldrb r0, [r1, #0xc]
	adds r0, #1
	movs r2, #0
	strb r0, [r1, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #6
	beq _0809F50A
	cmp r0, #0xb
	bne _0809F438
	str r2, [sp]
	b _0809F4DA
	.align 2, 0
_0809F434: .4byte gNonGameplayRam
_0809F438:
	cmp r0, #0xc
	bne _0809F50A
	strb r2, [r1, #0xc]
	strb r2, [r1, #0x10]
	movs r0, #3
	strh r0, [r1, #0xa]
	b _0809F50A
_0809F446:
	ldr r2, _0809F464 @ =gNonGameplayRam
	ldrb r0, [r2, #0xc]
	adds r0, #1
	strb r0, [r2, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F46C
	ldr r1, _0809F468 @ =0x03000B8D
	ldrb r0, [r2, #0xd]
	strb r0, [r1]
	movs r0, #0
	bl Sram_EraseFile
	b _0809F50A
	.align 2, 0
_0809F464: .4byte gNonGameplayRam
_0809F468: .4byte 0x03000B8D
_0809F46C:
	cmp r0, #2
	bne _0809F478
	movs r0, #1
	bl Sram_EraseFile
	b _0809F50A
_0809F478:
	cmp r0, #3
	bne _0809F484
	movs r0, #2
	bl Sram_EraseFile
	b _0809F50A
_0809F484:
	cmp r0, #4
	bne _0809F490
	movs r0, #3
	bl Sram_EraseFile
	b _0809F50A
_0809F490:
	cmp r0, #0xb
	bne _0809F49C
	ldrb r0, [r2, #0xd]
	bl FileSelectDrawFileInfo
	b _0809F50A
_0809F49C:
	cmp r0, #0xc
	bne _0809F50A
	movs r1, #0
	movs r0, #0x21
_0809F4A4:
	strh r0, [r2, #0xa]
	strb r1, [r2, #0xc]
	b _0809F50A
_0809F4AA:
	ldr r4, _0809F4D0 @ =gNonGameplayRam
	ldrb r0, [r4, #0xc]
	adds r0, #1
	movs r1, #0
	strb r0, [r4, #0xc]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0809F4D4
	movs r0, #2
	bl FileSelectDestroyOamOfType
	movs r0, #5
_0809F4C4:
	bl FileSelectDestroyOamOfType
	movs r0, #5
	strb r0, [r4, #0x11]
	b _0809F50A
	.align 2, 0
_0809F4D0: .4byte gNonGameplayRam
_0809F4D4:
	cmp r0, #2
	bne _0809F4F8
_0809F4D8:
	str r1, [sp]
_0809F4DA:
	ldr r1, _0809F4EC @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _0809F4F0 @ =0x0600C800
	str r0, [r1, #4]
	ldr r0, _0809F4F4 @ =0x85000600
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _0809F50A
	.align 2, 0
_0809F4EC: .4byte 0x040000D4
_0809F4F0: .4byte 0x0600C800
_0809F4F4: .4byte 0x85000600
_0809F4F8:
	cmp r0, #0xc
	bne _0809F50A
	strb r1, [r4, #0x10]
	strb r1, [r4, #0xf]
	strb r1, [r4, #0xe]
_0809F502:
	strb r1, [r4, #0xc]
	strh r1, [r4, #0xa]
	b _0809F50A
_0809F508:
	movs r7, #3
_0809F50A:
	bl FileSelectDrawAllOam
	adds r0, r7, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start FileSelectSetupOam
FileSelectSetupOam: @ 0x0809F518
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov sb, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov r8, r2
	movs r4, #0x16
	ldr r1, _0809F574 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r0, r1, r2
	ldrb r0, [r0, #0x1c]
	adds r5, r1, #0
	cmp r0, #0
	beq _0809F564
	adds r6, r5, #0
_0809F546:
	lsls r0, r4, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r4, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _0809F56E
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r0, [r0, #0x1c]
	cmp r0, #0
	bne _0809F546
_0809F564:
	lsls r0, r4, #0x18
	asrs r2, r0, #0x18
	adds r6, r0, #0
	cmp r2, #0
	bge _0809F578
_0809F56E:
	movs r0, #0x17
	b _0809F91A
	.align 2, 0
_0809F574: .4byte gNonGameplayRam
_0809F578:
	movs r0, #0
	str r0, [sp]
	ldr r1, _0809F5C4 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	lsls r0, r2, #3
	subs r0, r0, r2
	lsls r4, r0, #2
	ldr r2, _0809F5C8 @ =0x0300149C
	mov ip, r2
	adds r0, r4, r2
	str r0, [r1, #4]
	ldr r0, _0809F5CC @ =0x85000007
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r0, ip
	subs r0, #0x18
	adds r1, r4, r0
	movs r7, #0
	mov r0, sb
	strh r0, [r1, #0x18]
	mov r2, r8
	strh r2, [r1, #0x1a]
	strb r3, [r1, #0x1c]
	movs r2, #1
	strb r2, [r1, #0x1d]
	cmp r3, #1
	bne _0809F5D8
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F5D0 @ =sFileSelectUnk_740a48
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F5D4 @ =FileSelectProcessSamusHead
	b _0809F916
	.align 2, 0
_0809F5C4: .4byte 0x040000D4
_0809F5C8: .4byte 0x0300149C
_0809F5CC: .4byte 0x85000007
_0809F5D0: .4byte sFileSelectUnk_740a48
_0809F5D4: .4byte FileSelectProcessSamusHead
_0809F5D8:
	cmp r3, #2
	bne _0809F5F8
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F5F0 @ =sFileSelectUnk_740b48
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F5F4 @ =FileSelectProcessCursor
	b _0809F916
	.align 2, 0
_0809F5F0: .4byte sFileSelectUnk_740b48
_0809F5F4: .4byte FileSelectProcessCursor
_0809F5F8:
	cmp r3, #3
	bne _0809F620
	adds r0, r1, #0
	adds r0, #0x23
	strb r2, [r0]
	strb r7, [r1, #0x1d]
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F618 @ =sFileSelectUnk_740ab8
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F61C @ =FileSelectProcessDeleteArrow
	b _0809F916
	.align 2, 0
_0809F618: .4byte sFileSelectUnk_740ab8
_0809F61C: .4byte FileSelectProcessDeleteArrow
_0809F620:
	cmp r3, #4
	bne _0809F640
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F638 @ =sFileSelectUnk_740b48
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F63C @ =unk_9fddc
	b _0809F916
	.align 2, 0
_0809F638: .4byte sFileSelectUnk_740b48
_0809F63C: .4byte unk_9fddc
_0809F640:
	cmp r3, #5
	bne _0809F660
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F658 @ =sFileSelectUnk_740b48
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F65C @ =unk_9ff00
	b _0809F916
	.align 2, 0
_0809F658: .4byte sFileSelectUnk_740b48
_0809F65C: .4byte unk_9ff00
_0809F660:
	cmp r3, #6
	bne _0809F688
	adds r1, #0x23
	movs r0, #3
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F680 @ =sFileSelectUnk_7407e0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F684 @ =FileSelectProcessAudioLogos
	b _0809F916
	.align 2, 0
_0809F680: .4byte sFileSelectUnk_7407e0
_0809F684: .4byte FileSelectProcessAudioLogos
_0809F688:
	cmp r3, #7
	bne _0809F6BC
	adds r1, #0x23
	movs r0, #2
	strb r0, [r1]
	mov r1, ip
	adds r1, #0x14
	adds r1, r4, r1
	ldr r2, _0809F6B0 @ =sFileSelectUnk_79e890
	ldr r0, _0809F6B4 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	str r0, [r1]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F6B8 @ =FileSelectProcessFileOverlay
	b _0809F916
	.align 2, 0
_0809F6B0: .4byte sFileSelectUnk_79e890
_0809F6B4: .4byte 0x03000B8D
_0809F6B8: .4byte FileSelectProcessFileOverlay
_0809F6BC:
	cmp r3, #8
	bne _0809F6E4
	adds r1, #0x23
	movs r0, #2
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F6DC @ =sFileSelectUnk_7408e0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F6E0 @ =unk_a016c
	b _0809F916
	.align 2, 0
_0809F6DC: .4byte sFileSelectUnk_7408e0
_0809F6E0: .4byte unk_a016c
_0809F6E4:
	cmp r3, #9
	bne _0809F70C
	strb r7, [r1, #0x1d]
	adds r1, #0x23
	movs r0, #3
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F704 @ =sFileSelectUnk_7408f0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F708 @ =FileSelectProcessAudioSelect
	b _0809F916
	.align 2, 0
_0809F704: .4byte sFileSelectUnk_7408f0
_0809F708: .4byte FileSelectProcessAudioSelect
_0809F70C:
	cmp r3, #0xa
	bne _0809F72C
	mov r0, ip
	adds r0, #0x14
	adds r0, r4, r0
	ldr r1, _0809F724 @ =sFileSelectUnk_740880
	str r1, [r0]
	mov r0, ip
	adds r0, #0x18
	adds r0, r4, r0
	ldr r1, _0809F728 @ =unk_a01cc
	b _0809F916
	.align 2, 0
_0809F724: .4byte sFileSelectUnk_740880
_0809F728: .4byte unk_a01cc
_0809F72C:
	cmp r3, #0xb
	bne _0809F76C
	movs r0, #0xfe
	lsls r0, r0, #1
	bl SoundPlay
	ldr r3, _0809F760 @ =gNonGameplayRam
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r3
	adds r0, #0x23
	movs r2, #2
	strb r2, [r0]
	adds r0, r3, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F764 @ =sFileSelectUnk_740918
	str r2, [r0]
	adds r3, #0x30
	adds r1, r1, r3
	ldr r0, _0809F768 @ =FileSelectProcessFileActionPanel
	str r0, [r1]
	b _0809F918
	.align 2, 0
_0809F760: .4byte gNonGameplayRam
_0809F764: .4byte sFileSelectUnk_740918
_0809F768: .4byte FileSelectProcessFileActionPanel
_0809F76C:
	cmp r3, #0xc
	bne _0809F7AC
	movs r0, #0xfe
	lsls r0, r0, #1
	bl SoundPlay
	ldr r3, _0809F7A0 @ =gNonGameplayRam
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r3
	adds r0, #0x23
	movs r2, #1
	strb r2, [r0]
	adds r0, r3, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F7A4 @ =sFileSelectUnk_740978
	str r2, [r0]
	adds r3, #0x30
	adds r1, r1, r3
	ldr r0, _0809F7A8 @ =FileSelectProcessCopyFilePanel
	str r0, [r1]
	b _0809F918
	.align 2, 0
_0809F7A0: .4byte gNonGameplayRam
_0809F7A4: .4byte sFileSelectUnk_740978
_0809F7A8: .4byte FileSelectProcessCopyFilePanel
_0809F7AC:
	cmp r3, #0xd
	bne _0809F7EC
	movs r0, #0xfe
	lsls r0, r0, #1
	bl SoundPlay
	ldr r3, _0809F7E0 @ =gNonGameplayRam
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r3
	adds r0, #0x23
	movs r2, #1
	strb r2, [r0]
	adds r0, r3, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F7E4 @ =sFileSelectUnk_740978
	str r2, [r0]
	adds r3, #0x30
	adds r1, r1, r3
	ldr r0, _0809F7E8 @ =FileSelectProcessEraseFilePanel
	str r0, [r1]
	b _0809F918
	.align 2, 0
_0809F7E0: .4byte gNonGameplayRam
_0809F7E4: .4byte sFileSelectUnk_740978
_0809F7E8: .4byte FileSelectProcessEraseFilePanel
_0809F7EC:
	cmp r3, #0xe
	bne _0809F810
	asrs r1, r6, #0x18
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r5
	adds r1, #0x23
	movs r2, #3
	strb r2, [r1]
	adds r1, r5, #0
	adds r1, #0x30
	adds r0, r0, r1
	ldr r1, _0809F80C @ =unk_a0518
	b _0809F916
	.align 2, 0
_0809F80C: .4byte unk_a0518
_0809F810:
	cmp r3, #0xf
	bne _0809F834
	asrs r1, r6, #0x18
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r5
	adds r1, #0x23
	movs r2, #3
	strb r2, [r1]
	adds r1, r5, #0
	adds r1, #0x30
	adds r0, r0, r1
	ldr r1, _0809F830 @ =unk_a0518
	b _0809F916
	.align 2, 0
_0809F830: .4byte unk_a0518
_0809F834:
	cmp r3, #0x10
	bne _0809F858
	asrs r1, r6, #0x18
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r1, r0, r5
	adds r1, #0x23
	movs r2, #3
	strb r2, [r1]
	adds r1, r5, #0
	adds r1, #0x30
	adds r0, r0, r1
	ldr r1, _0809F854 @ =unk_a0518
	b _0809F916
	.align 2, 0
_0809F854: .4byte unk_a0518
_0809F858:
	cmp r3, #0x11
	bne _0809F87C
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r5
	adds r0, #0x23
	movs r2, #2
	strb r2, [r0]
	adds r0, r5, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F878 @ =sFileSelectUnk_7409a0
	b _0809F8A0
	.align 2, 0
_0809F878: .4byte sFileSelectUnk_7409a0
_0809F87C:
	cmp r3, #0x14
	beq _0809F888
	cmp r3, #0x15
	beq _0809F888
	cmp r3, #0x16
	bne _0809F8B8
_0809F888:
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r5
	adds r0, #0x23
	movs r2, #3
	strb r2, [r0]
	adds r0, r5, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F8B0 @ =sFileSelectUnk_740b98
_0809F8A0:
	str r2, [r0]
	adds r0, r5, #0
	adds r0, #0x30
	adds r1, r1, r0
	ldr r0, _0809F8B4 @ =unk_a0518
	str r0, [r1]
	b _0809F918
	.align 2, 0
_0809F8B0: .4byte sFileSelectUnk_740b98
_0809F8B4: .4byte unk_a0518
_0809F8B8:
	cmp r3, #0x17
	bne _0809F8F8
	movs r0, #0xfe
	lsls r0, r0, #1
	bl SoundPlay
	ldr r3, _0809F8EC @ =gNonGameplayRam
	asrs r0, r6, #0x18
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	adds r0, r1, r3
	adds r0, #0x23
	movs r2, #1
	strb r2, [r0]
	adds r0, r3, #0
	adds r0, #0x2c
	adds r0, r1, r0
	ldr r2, _0809F8F0 @ =sFileSelectUnk_740978
	str r2, [r0]
	adds r3, #0x30
	adds r1, r1, r3
	ldr r0, _0809F8F4 @ =unk_a039c
	str r0, [r1]
	b _0809F918
	.align 2, 0
_0809F8EC: .4byte gNonGameplayRam
_0809F8F0: .4byte sFileSelectUnk_740978
_0809F8F4: .4byte unk_a039c
_0809F8F8:
	cmp r3, #0x18
	bne _0809F918
	asrs r1, r6, #0x18
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r1, r5, #0
	adds r1, #0x2c
	adds r1, r0, r1
	ldr r2, _0809F928 @ =sFileSelectUnk_740b48
	str r2, [r1]
	adds r1, r5, #0
	adds r1, #0x30
	adds r0, r0, r1
	ldr r1, _0809F92C @ =unk_a0424
_0809F916:
	str r1, [r0]
_0809F918:
	lsrs r0, r6, #0x18
_0809F91A:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809F928: .4byte sFileSelectUnk_740b48
_0809F92C: .4byte unk_a0424
