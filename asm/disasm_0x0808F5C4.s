    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start EndingBslCrashingSetupOam
EndingBslCrashingSetupOam: @ 0x08095958
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov r8, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sb, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _080959BC
	movs r2, #0
	ldr r1, _080959B8 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _080959AA
	adds r4, r1, #0
_0809598A:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _080959FA
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809598A
_080959AA:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	adds r7, r0, #0
	cmp r1, #0x13
	ble _08095A04
	b _080959FA
	.align 2, 0
_080959B8: .4byte gNonGameplayRam
_080959BC:
	movs r2, #0x13
	ldr r1, _08095A00 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _080959F2
	adds r4, r1, #0
	movs r3, #0x8b
	lsls r3, r3, #2
_080959D2:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _080959FA
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _080959D2
_080959F2:
	lsls r0, r2, #0x18
	adds r7, r0, #0
	cmp r7, #0
	bge _08095A04
_080959FA:
	movs r0, #0x14
	b _08095C3E
	.align 2, 0
_08095A00: .4byte gNonGameplayRam
_08095A04:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08095A94 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	asrs r1, r7, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r5, r0, #2
	ldr r0, _08095A98 @ =0x030016A0
	mov ip, r0
	adds r0, r5, r0
	str r0, [r2, #4]
	ldr r0, _08095A9C @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r0, _08095AA0 @ =0xFFFFFDE4
	add r0, ip
	adds r2, r5, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	mov r3, r8
	strh r3, [r0]
	adds r1, #2
	adds r0, r2, r1
	mov r3, sb
	strh r3, [r0]
	adds r1, #2
	adds r0, r2, r1
	strb r6, [r0]
	movs r3, #0x8d
	lsls r3, r3, #2
	adds r4, r2, r3
	ldrb r1, [r4]
	movs r0, #1
	orrs r1, r0
	strb r1, [r4]
	cmp r6, #1
	bne _08095AB4
	ldr r0, _08095AA4 @ =0x00000222
	adds r1, r2, r0
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r1, _08095AA8 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095AAC @ =sSr388CollisionUnk_636020
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095AB0 @ =EndingProcessFallingBsl
	b _08095C3A
	.align 2, 0
_08095A94: .4byte 0x040000D4
_08095A98: .4byte 0x030016A0
_08095A9C: .4byte 0x85000009
_08095AA0: .4byte 0xFFFFFDE4
_08095AA4: .4byte 0x00000222
_08095AA8: .4byte 0x00000236
_08095AAC: .4byte sSr388CollisionUnk_636020
_08095AB0: .4byte EndingProcessFallingBsl
_08095AB4:
	cmp r6, #2
	bne _08095B14
	ldr r3, _08095B04 @ =0x00000222
	adds r1, r2, r3
	movs r0, #0x80
	lsls r0, r0, #2
	strh r0, [r1]
	ldrb r1, [r4]
	movs r0, #0x19
	rsbs r0, r0, #0
	ands r0, r1
	movs r3, #8
	orrs r0, r3
	strb r0, [r4]
	ldr r0, _08095B08 @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r3
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B0C @ =sSr388CollisionUnk_636038
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B10 @ =EndingProcessFallingBsl
	b _08095C3A
	.align 2, 0
_08095B04: .4byte 0x00000222
_08095B08: .4byte 0x00000236
_08095B0C: .4byte sSr388CollisionUnk_636038
_08095B10: .4byte EndingProcessFallingBsl
_08095B14:
	cmp r6, #3
	bne _08095B4C
	ldr r1, _08095B40 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B44 @ =sSr388CollisionUnk_636050
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B48 @ =unk_9579c
	b _08095C3A
	.align 2, 0
_08095B40: .4byte 0x00000236
_08095B44: .4byte sSr388CollisionUnk_636050
_08095B48: .4byte unk_9579c
_08095B4C:
	cmp r6, #4
	bne _08095B88
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	ldr r3, _08095B7C @ =0x00000236
	adds r2, r2, r3
	ldrb r1, [r2]
	subs r0, #0xb
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B80 @ =sEndingUnk_636288
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B84 @ =EndingProcessLeavingSmallShip
	b _08095C3A
	.align 2, 0
_08095B7C: .4byte 0x00000236
_08095B80: .4byte sEndingUnk_636288
_08095B84: .4byte EndingProcessLeavingSmallShip
_08095B88:
	cmp r6, #5
	bne _08095BB0
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095BA8 @ =sEndingUnk_6362a0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095BAC @ =EndingProcessLeavingBigShip
	b _08095C3A
	.align 2, 0
_08095BA8: .4byte sEndingUnk_6362a0
_08095BAC: .4byte EndingProcessLeavingBigShip
_08095BB0:
	cmp r6, #0xa
	bne _08095BEC
	movs r0, #0x19
	rsbs r0, r0, #0
	ands r1, r0
	movs r0, #8
	orrs r1, r0
	strb r1, [r4]
	ldr r0, _08095BE0 @ =0x00000236
	adds r2, r2, r0
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095BE4 @ =sEndingUnk_6363a0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095BE8 @ =unk_95e20
	b _08095C3A
	.align 2, 0
_08095BE0: .4byte 0x00000236
_08095BE4: .4byte sEndingUnk_6363a0
_08095BE8: .4byte unk_95e20
_08095BEC:
	cmp r6, #0xb
	bne _08095C1C
	ldr r1, _08095C10 @ =0x00000236
	adds r2, r2, r1
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095C14 @ =sEndingUnk_6363b8
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095C18 @ =EndingProcessFrontFacingShipThrusters
	b _08095C3A
	.align 2, 0
_08095C10: .4byte 0x00000236
_08095C14: .4byte sEndingUnk_6363b8
_08095C18: .4byte EndingProcessFrontFacingShipThrusters
_08095C1C:
	cmp r6, #0xc
	bne _08095C3C
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095C4C @ =sEndingUnk_6363a0
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095C50 @ =EndingProcessFrontFacingShip
_08095C3A:
	str r1, [r0]
_08095C3C:
	lsrs r0, r7, #0x18
_08095C3E:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08095C4C: .4byte sEndingUnk_6363a0
_08095C50: .4byte EndingProcessFrontFacingShip

	thumb_func_start EndingBslCrashingVblank
EndingBslCrashingVblank: @ 0x08095C54
	push {lr}
	ldr r3, _08095CE0 @ =0x040000D4
	ldr r0, _08095CE4 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _08095CE8 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _08095CEC @ =0x04000052
	ldr r0, _08095CF0 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08095CF4 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08095CF8 @ =0x04000054
	ldr r0, _08095CFC @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08095D00 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D04 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D08 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D0C @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D10 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D14 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _08095D18 @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r2, r1, r0
	ldrb r0, [r2]
	cmp r0, #1
	bne _08095CDA
	movs r0, #0
	strb r0, [r2]
	ldr r2, _08095D1C @ =0x00000111
	adds r0, r1, r2
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08095D20 @ =sSr388CollisionUnk_636a38
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08095D24 @ =0x05000120
	str r0, [r3, #4]
	ldr r0, _08095D28 @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08095CDA:
	pop {r0}
	bx r0
	.align 2, 0
_08095CE0: .4byte 0x040000D4
_08095CE4: .4byte gOamData
_08095CE8: .4byte 0x84000100
_08095CEC: .4byte 0x04000052
_08095CF0: .4byte gWrittenToBldalpha_Evb
_08095CF4: .4byte gWrittenToBldalpha_Eva
_08095CF8: .4byte 0x04000054
_08095CFC: .4byte gWrittenToBldy
_08095D00: .4byte gBg1XPosition
_08095D04: .4byte gBg1YPosition
_08095D08: .4byte 0x0300122C
_08095D0C: .4byte 0x0300122E
_08095D10: .4byte 0x03001230
_08095D14: .4byte 0x03001232
_08095D18: .4byte gNonGameplayRam
_08095D1C: .4byte 0x00000111
_08095D20: .4byte sSr388CollisionUnk_636a38
_08095D24: .4byte 0x05000120
_08095D28: .4byte 0x84000008

	thumb_func_start EndingShipFrontViewVblank
EndingShipFrontViewVblank: @ 0x08095D2C
	ldr r1, _08095D88 @ =0x040000D4
	ldr r0, _08095D8C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08095D90 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08095D94 @ =0x04000052
	ldr r0, _08095D98 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08095D9C @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08095DA0 @ =0x04000054
	ldr r0, _08095DA4 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08095DA8 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DAC @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB0 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB4 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB8 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DBC @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08095D88: .4byte 0x040000D4
_08095D8C: .4byte gOamData
_08095D90: .4byte 0x84000100
_08095D94: .4byte 0x04000052
_08095D98: .4byte gWrittenToBldalpha_Evb
_08095D9C: .4byte gWrittenToBldalpha_Eva
_08095DA0: .4byte 0x04000054
_08095DA4: .4byte gWrittenToBldy
_08095DA8: .4byte gBg1XPosition
_08095DAC: .4byte gBg1YPosition
_08095DB0: .4byte 0x0300122C
_08095DB4: .4byte 0x0300122E
_08095DB8: .4byte 0x03001230
_08095DBC: .4byte 0x03001232

	thumb_func_start EndingGetPositionAndSlotOfOamByType
EndingGetPositionAndSlotOfOamByType: @ 0x08095DC0
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _08095DF8 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_08095DD0:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _08095E00
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _08095DFC @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08095E18
	.align 2, 0
_08095DF8: .4byte gNonGameplayRam
_08095DFC: .4byte 0x0000022A
_08095E00:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _08095DD0
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08095E18:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_95e20
unk_95e20: @ 0x08095E20
	bx lr
	.align 2, 0

	thumb_func_start EndingMonologueInit
EndingMonologueInit: @ 0x08095E24
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08095F78 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08095F7C @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08095F80 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08095F84 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08095F88 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08095F8C @ =unk_99940
	bl CallbackSetVBlank
	movs r6, #0
	str r6, [sp]
	ldr r4, _08095F90 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08095F94 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _08095F98 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095F9C @ =sEndingUnk_6150e8
	ldr r1, _08095FA0 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08095FA4 @ =sEndingUnk_636638
	str r0, [r4]
	ldr r0, _08095FA8 @ =0x05000200
	str r0, [r4, #4]
	ldr r5, _08095FAC @ =0x84000080
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FB0 @ =sEndingUnk_6186a4
	ldr r1, _08095FB4 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _08095FB8 @ =sEndingUnk_6377f8
	ldr r1, _08095FBC @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095FC0 @ =sEndingUnk_636438
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FC4 @ =sIntroTilemap_662804
	movs r5, #0x80
	lsls r5, r5, #0x12
	adds r1, r5, #0
	bl LZ77UncompWram
	str r5, [r4]
	ldr r0, _08095FC8 @ =0x06004800
	str r0, [r4, #4]
	ldr r0, _08095FCC @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	str r6, [sp]
	mov r2, sp
	str r2, [r4]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _08095FD0 @ =0x85001200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FD4 @ =sIntroPal_663820
	str r0, [r4]
	ldr r0, _08095FD8 @ =0x05000180
	str r0, [r4, #4]
	ldr r0, _08095FDC @ =0x84000020
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FE0 @ =gBg1XPosition
	strh r6, [r0]
	ldr r0, _08095FE4 @ =gBg1YPosition
	strh r6, [r0]
	ldr r0, _08095FE8 @ =0x0300122C
	strh r6, [r0]
	ldr r0, _08095FEC @ =0x0300122E
	strh r6, [r0]
	ldr r0, _08095FF0 @ =0x03001230
	strh r6, [r0]
	ldr r0, _08095FF4 @ =0x03001232
	strh r6, [r0]
	ldr r0, _08095FF8 @ =0x04000010
	strh r6, [r0]
	ldr r1, _08095FFC @ =0x04000012
	movs r0, #4
	strh r0, [r1]
	ldr r0, _08096000 @ =0x04000014
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	subs r1, #0xa
	movs r2, #0x90
	lsls r2, r2, #4
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08096004 @ =0x00001E01
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08096008 @ =0x00001F0B
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _0809600C @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096010 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096014 @ =gWrittenToBldalpha_Eva
	strh r6, [r0]
	ldr r0, _08096018 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x82
	lsls r1, r1, #1
	movs r0, #1
	movs r2, #0xb4
	movs r3, #0
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _0809601C @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096020 @ =EndingMonologueVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095F78: .4byte 0x04000208
_08095F7C: .4byte 0x04000004
_08095F80: .4byte 0x0000FFEF
_08095F84: .4byte 0x04000200
_08095F88: .4byte 0x0000FFFD
_08095F8C: .4byte unk_99940
_08095F90: .4byte 0x040000D4
_08095F94: .4byte gNonGameplayRam
_08095F98: .4byte 0x85000150
_08095F9C: .4byte sEndingUnk_6150e8
_08095FA0: .4byte 0x06010000
_08095FA4: .4byte sEndingUnk_636638
_08095FA8: .4byte 0x05000200
_08095FAC: .4byte 0x84000080
_08095FB0: .4byte sEndingUnk_6186a4
_08095FB4: .4byte 0x06008000
_08095FB8: .4byte sEndingUnk_6377f8
_08095FBC: .4byte 0x0600F800
_08095FC0: .4byte sEndingUnk_636438
_08095FC4: .4byte sIntroTilemap_662804
_08095FC8: .4byte 0x06004800
_08095FCC: .4byte 0x84000200
_08095FD0: .4byte 0x85001200
_08095FD4: .4byte sIntroPal_663820
_08095FD8: .4byte 0x05000180
_08095FDC: .4byte 0x84000020
_08095FE0: .4byte gBg1XPosition
_08095FE4: .4byte gBg1YPosition
_08095FE8: .4byte 0x0300122C
_08095FEC: .4byte 0x0300122E
_08095FF0: .4byte 0x03001230
_08095FF4: .4byte 0x03001232
_08095FF8: .4byte 0x04000010
_08095FFC: .4byte 0x04000012
_08096000: .4byte 0x04000014
_08096004: .4byte 0x00001E01
_08096008: .4byte 0x00001F0B
_0809600C: .4byte gWrittenToBldy
_08096010: .4byte 0x04000054
_08096014: .4byte gWrittenToBldalpha_Eva
_08096018: .4byte gWrittenToBldalpha_Evb
_0809601C: .4byte sCutsceneTextNone
_08096020: .4byte EndingMonologueVblank

	thumb_func_start EndingAdamConversationInit
EndingAdamConversationInit: @ 0x08096024
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, _0809617C @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08096180 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08096184 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08096188 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809618C @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08096190 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08096194 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r6, _08096198 @ =0x030016A0
	str r6, [r4, #4]
	ldr r0, _0809619C @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r1, sp, #4
	strh r5, [r1]
	str r1, [r4]
	ldr r2, _080961A0 @ =0xFFFFFDF8
	adds r0, r6, r2
	str r0, [r4, #4]
	ldr r2, _080961A4 @ =0x8100007E
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r1]
	str r1, [r4]
	ldr r1, _080961A8 @ =0xFFFFFEF4
	adds r0, r6, r1
	str r0, [r4, #4]
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080961AC @ =sEndingUnk_6131c8
	ldr r1, _080961B0 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _080961B4 @ =sEndingUnk_637238
	ldr r1, _080961B8 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080961BC @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _080961C0 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _080961C4 @ =sEndingUnk_636438
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080961C8 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080961CC @ =0x03001224
	ldr r1, _080961D0 @ =0x0000FFF8
	adds r2, r1, #0
	strh r2, [r0]
	ldr r0, _080961D4 @ =0x03001226
	movs r1, #8
	strh r1, [r0]
	ldr r0, _080961D8 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _080961DC @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _080961E0 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _080961E4 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _080961E8 @ =0x03001230
	strh r5, [r0]
	ldr r0, _080961EC @ =0x03001232
	strh r5, [r0]
	ldr r0, _080961F0 @ =0x04000010
	strh r2, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _080961F4 @ =0x04000008
	ldr r2, _080961F8 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #6
	ldr r2, _080961FC @ =0x00001F0B
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08096200 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096204 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096208 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809620C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08096210 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #2
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	movs r0, #3
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	movs r0, #4
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08096214 @ =0xFFFFFDE4
	adds r6, r6, r0
	ldr r0, _08096218 @ =sCutsceneTextNone
	str r0, [r6]
	str r5, [sp]
	mov r1, sp
	str r1, [r4]
	ldr r0, _0809621C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08096220 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc8
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096224 @ =EndingConversationAndAnimalsVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809617C: .4byte 0x04000208
_08096180: .4byte 0x04000004
_08096184: .4byte 0x0000FFEF
_08096188: .4byte 0x04000200
_0809618C: .4byte 0x0000FFFD
_08096190: .4byte unk_99940
_08096194: .4byte 0x040000D4
_08096198: .4byte 0x030016A0
_0809619C: .4byte 0x850000B4
_080961A0: .4byte 0xFFFFFDF8
_080961A4: .4byte 0x8100007E
_080961A8: .4byte 0xFFFFFEF4
_080961AC: .4byte sEndingUnk_6131c8
_080961B0: .4byte 0x06008000
_080961B4: .4byte sEndingUnk_637238
_080961B8: .4byte 0x0600F800
_080961BC: .4byte sIntroSamusShipFlyingTextTilemap
_080961C0: .4byte 0x0600E000
_080961C4: .4byte sEndingUnk_636438
_080961C8: .4byte 0x84000080
_080961CC: .4byte 0x03001224
_080961D0: .4byte 0x0000FFF8
_080961D4: .4byte 0x03001226
_080961D8: .4byte gBg1XPosition
_080961DC: .4byte gBg1YPosition
_080961E0: .4byte 0x0300122C
_080961E4: .4byte 0x0300122E
_080961E8: .4byte 0x03001230
_080961EC: .4byte 0x03001232
_080961F0: .4byte 0x04000010
_080961F4: .4byte 0x04000008
_080961F8: .4byte 0x00001C08
_080961FC: .4byte 0x00001F0B
_08096200: .4byte gWrittenToBldy
_08096204: .4byte 0x04000054
_08096208: .4byte gWrittenToBldalpha_Eva
_0809620C: .4byte gWrittenToBldalpha_Evb
_08096210: .4byte 0x04000052
_08096214: .4byte 0xFFFFFDE4
_08096218: .4byte sCutsceneTextNone
_0809621C: .4byte 0x0600D000
_08096220: .4byte 0x85000400
_08096224: .4byte EndingConversationAndAnimalsVblank

	thumb_func_start EndingAnimalsInit
EndingAnimalsInit: @ 0x08096228
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #8
	ldr r3, _08096390 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08096394 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08096398 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _0809639C @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080963A0 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080963A4 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080963A8 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _080963AC @ =0x030016A0
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _080963B0 @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r6, sp, #4
	strh r5, [r6]
	str r6, [r4]
	ldr r0, _080963B4 @ =0xFFFFFDF8
	add r0, r8
	str r0, [r4, #4]
	ldr r1, _080963B8 @ =0x8100007E
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r6]
	str r6, [r4]
	ldr r0, _080963BC @ =0xFFFFFEF4
	add r0, r8
	str r0, [r4, #4]
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080963C0 @ =sEndingUnk_61b89c
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _080963C4 @ =sEndingUnk_6217a8
	ldr r1, _080963C8 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _080963CC @ =sEndingUnk_638654
	ldr r1, _080963D0 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _080963D4 @ =sEndingUnk_637db8
	ldr r1, _080963D8 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080963DC @ =sEndingUnk_636838
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080963E0 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r2, _080963E4 @ =0x000002FF
	adds r0, r2, #0
	strh r0, [r6]
	str r6, [r4]
	ldr r0, _080963E8 @ =0x0600F500
	str r0, [r4, #4]
	ldr r0, _080963EC @ =0x81000180
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080963F0 @ =0x03001224
	strh r5, [r0]
	ldr r0, _080963F4 @ =0x03001226
	strh r5, [r0]
	ldr r0, _080963F8 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _080963FC @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _08096400 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08096404 @ =0x03001230
	strh r5, [r0]
	ldr r1, _08096408 @ =0x0300122E
	ldr r2, _0809640C @ =0x0000FFE2
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096410 @ =0x03001232
	movs r1, #0xe2
	strh r1, [r0]
	ldr r0, _08096414 @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r1, [r0]
	ldr r1, _08096418 @ =0x0400000C
	ldr r2, _0809641C @ =0x00001E0A
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	adds r2, #0xf9
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08096420 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096424 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096428 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809642C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08096430 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0x14
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08096434 @ =0xFFFFFDE4
	add r8, r0
	ldr r0, _08096438 @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809643C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08096440 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096444 @ =EndingConversationAndAnimalsVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08096390: .4byte 0x04000208
_08096394: .4byte 0x04000004
_08096398: .4byte 0x0000FFEF
_0809639C: .4byte 0x04000200
_080963A0: .4byte 0x0000FFFD
_080963A4: .4byte unk_99940
_080963A8: .4byte 0x040000D4
_080963AC: .4byte 0x030016A0
_080963B0: .4byte 0x850000B4
_080963B4: .4byte 0xFFFFFDF8
_080963B8: .4byte 0x8100007E
_080963BC: .4byte 0xFFFFFEF4
_080963C0: .4byte sEndingUnk_61b89c
_080963C4: .4byte sEndingUnk_6217a8
_080963C8: .4byte 0x06008000
_080963CC: .4byte sEndingUnk_638654
_080963D0: .4byte 0x0600F000
_080963D4: .4byte sEndingUnk_637db8
_080963D8: .4byte 0x0600F800
_080963DC: .4byte sEndingUnk_636838
_080963E0: .4byte 0x84000080
_080963E4: .4byte 0x000002FF
_080963E8: .4byte 0x0600F500
_080963EC: .4byte 0x81000180
_080963F0: .4byte 0x03001224
_080963F4: .4byte 0x03001226
_080963F8: .4byte gBg1XPosition
_080963FC: .4byte gBg1YPosition
_08096400: .4byte 0x0300122C
_08096404: .4byte 0x03001230
_08096408: .4byte 0x0300122E
_0809640C: .4byte 0x0000FFE2
_08096410: .4byte 0x03001232
_08096414: .4byte 0x04000010
_08096418: .4byte 0x0400000C
_0809641C: .4byte 0x00001E0A
_08096420: .4byte gWrittenToBldy
_08096424: .4byte 0x04000054
_08096428: .4byte gWrittenToBldalpha_Eva
_0809642C: .4byte gWrittenToBldalpha_Evb
_08096430: .4byte 0x04000052
_08096434: .4byte 0xFFFFFDE4
_08096438: .4byte sCutsceneTextNone
_0809643C: .4byte 0x0600D000
_08096440: .4byte 0x85000400
_08096444: .4byte EndingConversationAndAnimalsVblank

	thumb_func_start EndingInShipProcess
EndingInShipProcess: @ 0x08096448
	push {r4, r5, r6, r7, lr}
	movs r6, #0
	ldr r2, _08096474 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r0, r2, r7
	ldrb r0, [r0]
	adds r5, r2, #0
	cmp r0, #0xf
	bls _0809646A
	b _08096920
_0809646A:
	lsls r0, r0, #2
	ldr r1, _08096478 @ =_0809647C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08096474: .4byte gNonGameplayRam
_08096478: .4byte _0809647C
_0809647C: @ jump table
	.4byte _080964BC @ case 0
	.4byte _080964F2 @ case 1
	.4byte _08096550 @ case 2
	.4byte _080965F4 @ case 3
	.4byte _0809663C @ case 4
	.4byte _08096698 @ case 5
	.4byte _080966E0 @ case 6
	.4byte _080966FC @ case 7
	.4byte _08096716 @ case 8
	.4byte _0809673C @ case 9
	.4byte _0809678A @ case 10
	.4byte _0809681C @ case 11
	.4byte _08096828 @ case 12
	.4byte _08096878 @ case 13
	.4byte _080968A0 @ case 14
	.4byte _080968E8 @ case 15
_080964BC:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #7
	beq _080964CA
	b _080968D8
_080964CA:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080964DC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _080964E0
	subs r0, #1
	strh r0, [r1]
	b _080968D8
	.align 2, 0
_080964DC: .4byte gWrittenToBldy
_080964E0:
	movs r0, #0x56
	movs r1, #0xe
	bl PlayMusic
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #1
	b _080968D6
_080964F2:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #0x46
	beq _08096500
	b _080968D8
_08096500:
	movs r4, #0
	movs r2, #0
	strh r2, [r1]
	movs r3, #0x80
	lsls r3, r3, #0x13
	ldrh r0, [r3]
	movs r7, #0x80
	lsls r7, r7, #1
	adds r1, r7, #0
	orrs r0, r1
	strh r0, [r3]
	strh r2, [r5, #0x12]
	strh r2, [r5, #0x10]
	strh r2, [r5, #0xe]
	strh r2, [r5, #0xc]
	ldr r1, _08096544 @ =0x00000212
	adds r0, r5, r1
	strb r4, [r0]
	ldr r1, _08096548 @ =sMonologueTextPointers
	ldr r0, _0809654C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #0x1c]
	str r0, [r5]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #2
	b _080968D6
	.align 2, 0
_08096544: .4byte 0x00000212
_08096548: .4byte sMonologueTextPointers
_0809654C: .4byte 0x03000011
_08096550:
	ldr r0, [r5]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096578
	ldr r0, _08096598 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08096578
	movs r7, #0x86
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrb r0, [r1]
	cmp r0, #0
	bne _08096578
	movs r0, #1
	strb r0, [r1]
_08096578:
	ldr r3, _0809659C @ =gNonGameplayRam
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r4, #0
	movs r0, #0
	strh r0, [r1]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r3, r1
	ldrb r2, [r0]
	cmp r2, #2
	bne _080965A0
	strb r4, [r0]
	b _080965AE
	.align 2, 0
_08096598: .4byte gChangedInput
_0809659C: .4byte gNonGameplayRam
_080965A0:
	cmp r2, #3
	bne _080965AE
	strb r4, [r0]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r0, r3, r7
	strb r2, [r0]
_080965AE:
	bl EndingCheckMonologueEnded
	cmp r0, #0
	beq _080965CC
	ldr r3, _080965DC @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r2, #0
	movs r0, #3
	strb r0, [r1]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r3, r1
	strb r2, [r0]
_080965CC:
	ldr r0, _080965DC @ =gNonGameplayRam
	ldr r2, _080965E0 @ =0x00000213
	adds r1, r0, r2
	ldrb r0, [r1]
	cmp r0, #0
	bne _080965E4
	movs r0, #0x64
	b _080968D6
	.align 2, 0
_080965DC: .4byte gNonGameplayRam
_080965E0: .4byte 0x00000213
_080965E4:
	cmp r0, #1
	beq _080965EA
	b _080968D8
_080965EA:
	movs r0, #0x64
	strb r0, [r1]
	bl SpecialCutsceneProcessMonologue
	b _080968D8
_080965F4:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #1
	bne _08096618
	ldr r1, _08096610 @ =gWrittenToBldalpha_Evb
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096614 @ =gWrittenToBldalpha_Eva
_08096608:
	movs r0, #0x10
	strh r0, [r1]
	b _080968D8
	.align 2, 0
_08096610: .4byte gWrittenToBldalpha_Evb
_08096614: .4byte gWrittenToBldalpha_Eva
_08096618:
	cmp r0, #0x14
	beq _0809661E
	b _080968D8
_0809661E:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096634 @ =0x04000050
	ldr r2, _08096638 @ =0x00001841
	adds r0, r2, #0
	strh r0, [r1]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #4
	b _080968D6
	.align 2, 0
_08096634: .4byte 0x04000050
_08096638: .4byte 0x00001841
_0809663C:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #4
	beq _0809664A
	b _080968D8
_0809664A:
	movs r0, #0
	strh r0, [r1]
	ldr r2, _0809668C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r2]
	cmp r0, #0xf
	bhi _0809665A
	adds r0, #1
	strh r0, [r2]
_0809665A:
	ldr r1, _08096690 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	cmp r0, #0
	beq _08096666
	subs r0, #1
	strh r0, [r1]
_08096666:
	ldrh r0, [r2]
	cmp r0, #0x10
	beq _0809666E
	b _080968D8
_0809666E:
	ldrh r0, [r1]
	cmp r0, #0
	beq _08096676
	b _080968D8
_08096676:
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _08096694 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #5
	b _080968D6
	.align 2, 0
_0809668C: .4byte gWrittenToBldalpha_Evb
_08096690: .4byte gWrittenToBldalpha_Eva
_08096694: .4byte 0x0000FEFF
_08096698:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r2, r5, r7
	ldrh r0, [r2]
	cmp r0, #0xa
	bne _080966B2
	movs r0, #0x1e
	movs r1, #0x78
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	b _080968D8
_080966B2:
	cmp r0, #0x27
	bne _080966C0
	ldr r1, _080966BC @ =gWrittenToBldy
	b _08096608
	.align 2, 0
_080966BC: .4byte gWrittenToBldy
_080966C0:
	cmp r0, #0x28
	beq _080966C6
	b _080968D8
_080966C6:
	ldr r1, _080966DC @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	movs r0, #0
	strh r0, [r2]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #6
	b _080968D6
	.align 2, 0
_080966DC: .4byte 0x04000050
_080966E0:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r5, r2
	ldrh r0, [r1]
	cmp r0, #1
	beq _080966EE
	b _080968D8
_080966EE:
	movs r0, #0
	strh r0, [r1]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #7
	b _080968D6
_080966FC:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #0
	strh r0, [r1]
	bl EndingAdamConversationInit
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #8
	strb r0, [r1]
	b _08096920
_08096716:
	ldr r1, _08096738 @ =gWrittenToBldy
	movs r0, #0
	strh r0, [r1]
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x93
	lsls r0, r0, #2
	bl SoundPlay
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #9
	b _080968D6
	.align 2, 0
_08096738: .4byte gWrittenToBldy
_0809673C:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r4, r5, r1
	ldrh r0, [r4]
	cmp r0, #0xa
	beq _08096806
	cmp r0, #0x28
	bne _08096806
	movs r0, #0xff
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #6
	movs r1, #0x14
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #7
	movs r1, #0x80
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #9
	movs r1, #0x80
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #0
	strh r0, [r4]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xa
	b _08096804
_0809678A:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	ldr r0, [r5]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080967BC
	ldr r0, _080967D4 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080967BC
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	cmp r0, #0
	bne _080967BC
	movs r0, #1
	strb r0, [r1]
_080967BC:
	movs r1, #0x86
	lsls r1, r1, #2
	adds r3, r5, r1
	ldrb r0, [r3]
	cmp r0, #2
	bne _080967DC
	movs r0, #0
	strb r0, [r3]
	ldr r0, _080967D8 @ =0x00000203
	bl SoundPlay
	b _08096806
	.align 2, 0
_080967D4: .4byte gChangedInput
_080967D8: .4byte 0x00000203
_080967DC:
	cmp r0, #3
	bne _08096806
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _08096814 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #0
	strb r0, [r3]
	ldr r0, _08096818 @ =0x00000203
	bl SoundPlay
	movs r0, #0xa
	bl FadeMusic
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xb
_08096804:
	strb r0, [r1]
_08096806:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	bl EndingProcessAdamText
	b _08096920
	.align 2, 0
_08096814: .4byte 0x0000FEFF
_08096818: .4byte 0x00000203
_0809681C:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	b _080968D8
_08096828:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #1
	bne _0809685C
	ldr r2, _08096850 @ =sMusicTrackDataRom
	ldr r0, _08096854 @ =sSoundDataEntries
	ldr r1, _08096858 @ =0x00001264
	adds r0, r0, r1
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0
	bl ApplyMusicSoundFading
	b _080968D8
	.align 2, 0
_08096850: .4byte sMusicTrackDataRom
_08096854: .4byte sSoundDataEntries
_08096858: .4byte 0x00001264
_0809685C:
	cmp r0, #0xa
	bne _080968D8
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096874 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xd
	b _080968D6
	.align 2, 0
_08096874: .4byte gWrittenToBldy
_08096878:
	bl EndingAnimalsInit
	ldr r2, _08096898 @ =gNonGameplayRam
	movs r7, #0x84
	lsls r7, r7, #2
	adds r0, r2, r7
	movs r1, #0
	strh r1, [r0]
	ldr r0, _0809689C @ =gWrittenToBldy
	strh r1, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r2, r0
	movs r0, #0xe
	strb r0, [r1]
	b _08096920
	.align 2, 0
_08096898: .4byte gNonGameplayRam
_0809689C: .4byte gWrittenToBldy
_080968A0:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrh r1, [r2]
	cmp r1, #1
	bne _080968B6
	movs r0, #0x53
	movs r1, #0xe
	bl PlayMusic
	b _080968D8
_080968B6:
	movs r0, #0xa0
	lsls r0, r0, #2
	cmp r1, r0
	bne _080968D8
	movs r0, #0
	strh r0, [r2]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _080968E4 @ =0x0000FBFF
	ands r0, r1
	strh r0, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xf
_080968D6:
	strb r0, [r1]
_080968D8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08096920
	.align 2, 0
_080968E4: .4byte 0x0000FBFF
_080968E8:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #2
	bne _08096918
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096908 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0809690C
	adds r0, #1
	strh r0, [r1]
	b _08096918
	.align 2, 0
_08096908: .4byte gWrittenToBldy
_0809690C:
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #0
	strb r0, [r1]
	movs r6, #1
_08096918:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08096920:
	adds r0, r6, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start EndingInShip
EndingInShip: @ 0x08096928
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08096940 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _08096954
	cmp r0, #1
	bgt _08096944
	cmp r0, #0
	beq _0809694E
	b _080969A8
	.align 2, 0
_08096940: .4byte gNonGameplayRam
_08096944:
	cmp r0, #2
	beq _0809696C
	cmp r0, #3
	beq _08096988
	b _080969A8
_0809694E:
	bl EndingMonologueInit
	b _08096960
_08096954:
	bl SpecialCutsceneFadeIn
	ldr r0, _08096968 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080969A8
_08096960:
	movs r0, #2
	strh r0, [r4, #8]
	b _080969A8
	.align 2, 0
_08096968: .4byte gWrittenToBldy
_0809696C:
	bl EndingInShipProcess
	cmp r0, #0
	beq _080969A8
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080969A8
_08096988:
	ldr r1, _08096998 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0809699C
	adds r0, #1
	strh r0, [r1]
	b _080969A0
	.align 2, 0
_08096998: .4byte gWrittenToBldy
_0809699C:
	strh r5, [r4, #8]
	movs r5, #1
_080969A0:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080969A8:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingProcessMonologueCursor
EndingProcessMonologueCursor: @ 0x080969B0
	push {lr}
	adds r2, r0, #0
	ldr r3, _080969D0 @ =gNonGameplayRam
	ldr r0, [r3]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080969D4
	movs r0, #0x76
	strh r0, [r2, #0xc]
	ldrh r0, [r3, #0xe]
	lsls r0, r0, #3
	adds r0, #0x18
	strh r0, [r2, #0xe]
	b _080969DA
	.align 2, 0
_080969D0: .4byte gNonGameplayRam
_080969D4:
	movs r0, #0x82
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
_080969DA:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_969e0
unk_969e0: @ 0x080969E0
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A02
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A02
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A02
	strb r1, [r2, #0x12]
_08096A02:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EndingProcessSr388RadarView
EndingProcessSr388RadarView: @ 0x08096A08
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A34
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A34
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A34
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _08096A38 @ =sEndingUnk_633ec4
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
_08096A34:
	pop {r0}
	bx r0
	.align 2, 0
_08096A38: .4byte sEndingUnk_633ec4

	thumb_func_start EndingProcessSamusViewRadarView
EndingProcessSamusViewRadarView: @ 0x08096A3C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A68
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A68
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A68
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _08096A6C @ =sEndingUnk_633f0c
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
_08096A68:
	pop {r0}
	bx r0
	.align 2, 0
_08096A6C: .4byte sEndingUnk_633f0c

	thumb_func_start unk_96a70
unk_96a70: @ 0x08096A70
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r6, r1, r0
	ldrb r5, [r4, #0x14]
	cmp r5, #0
	bne _08096AB4
	ldr r0, [r4, #0x10]
	ldr r1, _08096AAC @ =0x00FFFF00
	ands r0, r1
	ldr r1, _08096AB0 @ =0x00010100
	cmp r0, r1
	bne _08096A96
	movs r0, #0x8e
	lsls r0, r0, #1
	bl SoundPlay
_08096A96:
	ldrb r0, [r6, #4]
	ldrb r1, [r4, #0x12]
	cmp r0, r1
	bne _08096B06
	ldrb r0, [r6, #0xc]
	cmp r0, #0
	bne _08096B06
	strb r5, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08096B06
	.align 2, 0
_08096AAC: .4byte 0x00FFFF00
_08096AB0: .4byte 0x00010100
_08096AB4:
	cmp r5, #1
	bne _08096AE8
	movs r1, #0
	strb r1, [r4, #0x12]
	ldr r0, _08096ADC @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #0xb
	bne _08096B06
	strb r1, [r4, #0x11]
	ldr r0, _08096AE0 @ =sUnk_633244
	str r0, [r4, #0x1c]
	ldr r0, _08096AE4 @ =0x0000011D
	bl SoundPlay
	movs r0, #2
	strb r0, [r4, #0x14]
	b _08096B06
	.align 2, 0
_08096ADC: .4byte gNonGameplayRam
_08096AE0: .4byte sUnk_633244
_08096AE4: .4byte 0x0000011D
_08096AE8:
	cmp r5, #2
	bne _08096B06
	ldrb r0, [r6, #4]
	ldrb r1, [r4, #0x12]
	cmp r0, r1
	bne _08096B06
	ldrb r1, [r6, #0xc]
	cmp r1, #0
	bne _08096B06
	strb r1, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_08096B06:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessAdamTextCursor
EndingProcessAdamTextCursor: @ 0x08096B0C
	push {r4, lr}
	adds r2, r0, #0
	ldr r3, _08096B28 @ =gNonGameplayRam
	ldr r0, [r3]
	ldrh r1, [r0]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B2C
	movs r0, #0x91
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
	b _08096B8E
	.align 2, 0
_08096B28: .4byte gNonGameplayRam
_08096B2C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	beq _08096B70
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B54
	movs r0, #0
	movs r1, #0x91
	lsls r1, r1, #1
	strh r1, [r2, #0xc]
	strb r0, [r2, #0x12]
	strb r0, [r2, #0x11]
	ldr r0, _08096B50 @ =sEndingUnk_633e8c
	str r0, [r2, #0x1c]
	b _08096B8E
	.align 2, 0
_08096B50: .4byte sEndingUnk_633e8c
_08096B54:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B70
	movs r0, #0x78
	strh r0, [r2, #0xc]
	movs r0, #0x9a
	strh r0, [r2, #0xe]
	ldr r0, _08096B6C @ =sEndingUnk_633e64
	str r0, [r2, #0x1c]
	b _08096B8E
	.align 2, 0
_08096B6C: .4byte sEndingUnk_633e64
_08096B70:
	ldrh r0, [r3, #0xc]
	ldr r4, _08096B94 @ =0x00000212
	adds r1, r3, r4
	lsls r0, r0, #3
	ldrb r1, [r1]
	adds r0, r0, r1
	adds r0, #0xe
	movs r1, #0
	strh r0, [r2, #0xc]
	ldrh r0, [r3, #0xe]
	lsls r0, r0, #3
	adds r0, #0x84
	strh r0, [r2, #0xe]
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
_08096B8E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08096B94: .4byte 0x00000212
