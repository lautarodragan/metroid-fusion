    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start DiedFromSr388CollisionHandler
DiedFromSr388CollisionHandler: @ 0x0809741C
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	ldr r4, _08097438 @ =gSubGameMode1
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #1
	beq _08097468
	cmp r0, #1
	bgt _0809743C
	cmp r0, #0
	beq _08097442
	b _080974B8
	.align 2, 0
_08097438: .4byte gSubGameMode1
_0809743C:
	cmp r0, #2
	beq _08097488
	b _080974B8
_08097442:
	str r5, [sp]
	ldr r1, _0809745C @ =0x040000D4
	mov r2, sp
	str r2, [r1]
	ldr r0, _08097460 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08097464 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #1
	strh r0, [r4]
	b _080974B8
	.align 2, 0
_0809745C: .4byte 0x040000D4
_08097460: .4byte gNonGameplayRam
_08097464: .4byte 0x85000150
_08097468:
	bl DiedOnSr388Collision
	cmp r0, #0
	beq _080974B8
	ldr r0, _08097480 @ =gNonGameplayRam
	ldr r1, _08097484 @ =0x0000020E
	adds r0, r0, r1
	strh r5, [r0]
	movs r0, #2
	strh r0, [r4]
	b _080974B8
	.align 2, 0
_08097480: .4byte gNonGameplayRam
_08097484: .4byte 0x0000020E
_08097488:
	ldr r0, _080974A0 @ =gNonGameplayRam
	ldr r2, _080974A4 @ =0x0000020E
	adds r1, r0, r2
	ldrh r0, [r1]
	cmp r0, #0
	bne _080974B0
	ldr r1, _080974A8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080974AC
	adds r0, #1
	b _080974B2
	.align 2, 0
_080974A0: .4byte gNonGameplayRam
_080974A4: .4byte 0x0000020E
_080974A8: .4byte gWrittenToBldy
_080974AC:
	movs r5, #1
	b _080974B4
_080974B0:
	subs r0, #1
_080974B2:
	strh r0, [r1]
_080974B4:
	bl SpecialCutsceneDrawAllOam
_080974B8:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start DiedOnSr388CollisionInit
DiedOnSr388CollisionInit: @ 0x080974C4
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08097618 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _0809761C @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08097620 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08097624 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08097628 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809762C @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08097630 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08097634 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _08097638 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809763C @ =sSr388CollisionUnk_6238f4
	ldr r1, _08097640 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08097644 @ =sSr388CollisionUnk_636c38
	str r0, [r4]
	ldr r0, _08097648 @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _0809764C @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08097650 @ =sSr388CollisionUnk_62b5f4
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08097654 @ =sSr388CollisionUnk_638c14
	ldr r1, _08097658 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _0809765C @ =sSr388CollisionUnk_639bc4
	ldr r1, _08097660 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08097664 @ =sSr388CollisionUnk_637038
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08097668 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _0809766C @ =gBg1YPosition
	movs r2, #8
	strh r2, [r0]
	ldr r0, _08097670 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08097674 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _08097678 @ =0x03001230
	strh r5, [r0]
	ldr r0, _0809767C @ =0x03001232
	strh r5, [r0]
	ldr r0, _08097680 @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _08097684 @ =0x04000008
	ldr r3, _08097688 @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r3, _0809768C @ =0x00001E01
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #4
	ldr r3, _08097690 @ =0x00001F03
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xbf
	strh r0, [r1]
	ldr r0, _08097694 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08097698 @ =0x04000054
	strh r1, [r0]
	ldr r0, _0809769C @ =gWrittenToBldalpha_Eva
	strh r2, [r0]
	ldr r1, _080976A0 @ =gWrittenToBldalpha_Evb
	movs r0, #0xe
	strh r0, [r1]
	ldr r0, _080976A4 @ =0x0000024D
	bl SoundPlay_3b1c
	movs r0, #2
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	movs r0, #1
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	movs r0, #3
	movs r1, #0x86
	movs r2, #0x3c
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _080976A8 @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _080976AC @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _080976B0 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _080976B4 @ =DiedOnSr388CollisionVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08097618: .4byte 0x04000208
_0809761C: .4byte 0x04000004
_08097620: .4byte 0x0000FFEF
_08097624: .4byte 0x04000200
_08097628: .4byte 0x0000FFFD
_0809762C: .4byte unk_99940
_08097630: .4byte 0x040000D4
_08097634: .4byte gNonGameplayRam
_08097638: .4byte 0x85000150
_0809763C: .4byte sSr388CollisionUnk_6238f4
_08097640: .4byte 0x06010000
_08097644: .4byte sSr388CollisionUnk_636c38
_08097648: .4byte 0x05000200
_0809764C: .4byte 0x84000080
_08097650: .4byte sSr388CollisionUnk_62b5f4
_08097654: .4byte sSr388CollisionUnk_638c14
_08097658: .4byte 0x0600F000
_0809765C: .4byte sSr388CollisionUnk_639bc4
_08097660: .4byte 0x0600F800
_08097664: .4byte sSr388CollisionUnk_637038
_08097668: .4byte gBg1XPosition
_0809766C: .4byte gBg1YPosition
_08097670: .4byte 0x0300122C
_08097674: .4byte 0x0300122E
_08097678: .4byte 0x03001230
_0809767C: .4byte 0x03001232
_08097680: .4byte 0x04000010
_08097684: .4byte 0x04000008
_08097688: .4byte 0x00001C08
_0809768C: .4byte 0x00001E01
_08097690: .4byte 0x00001F03
_08097694: .4byte gWrittenToBldy
_08097698: .4byte 0x04000054
_0809769C: .4byte gWrittenToBldalpha_Eva
_080976A0: .4byte gWrittenToBldalpha_Evb
_080976A4: .4byte 0x0000024D
_080976A8: .4byte sCutsceneTextNone
_080976AC: .4byte 0x0600D000
_080976B0: .4byte 0x85000400
_080976B4: .4byte DiedOnSr388CollisionVblank

	thumb_func_start DiedOnSr388CollisionProcess
DiedOnSr388CollisionProcess: @ 0x080976B8
	push {r4, r5, r6, lr}
	movs r5, #0
	ldr r2, _080976E4 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r0, r2, r4
	ldrb r0, [r0]
	adds r3, r2, #0
	cmp r0, #4
	bls _080976DA
	b _08097862
_080976DA:
	lsls r0, r0, #2
	ldr r1, _080976E8 @ =_080976EC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080976E4: .4byte gNonGameplayRam
_080976E8: .4byte _080976EC
_080976EC: @ jump table
	.4byte _08097700 @ case 0
	.4byte _08097734 @ case 1
	.4byte _08097740 @ case 2
	.4byte _080977A8 @ case 3
	.4byte _08097808 @ case 4
_08097700:
	ldr r1, _08097710 @ =gWrittenToBldy
	ldrh r0, [r1]
	adds r2, r0, #0
	cmp r2, #0
	beq _08097714
	subs r0, #1
	strh r0, [r1]
	b _080977F8
	.align 2, 0
_08097710: .4byte gWrittenToBldy
_08097714:
	ldr r1, _08097730 @ =0x04000050
	movs r6, #0xc4
	lsls r6, r6, #4
	adds r0, r6, #0
	strh r0, [r1]
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r3, r1
	strh r2, [r0]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #1
	b _080977F6
	.align 2, 0
_08097730: .4byte 0x04000050
_08097734:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	b _080977F8
_08097740:
	movs r6, #0x84
	lsls r6, r6, #2
	adds r4, r3, r6
	ldrh r2, [r4]
	cmp r2, #1
	bne _08097774
	ldr r0, _08097768 @ =gWrittenToBldalpha_Eva
	movs r1, #0xa
	strh r1, [r0]
	ldr r0, _0809776C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x88
	lsls r1, r1, #1
	adds r0, r3, r1
	movs r1, #0
	strb r2, [r0]
	ldr r2, _08097770 @ =0x00000111
	adds r0, r3, r2
	strb r1, [r0]
	b _080977F8
	.align 2, 0
_08097768: .4byte gWrittenToBldalpha_Eva
_0809776C: .4byte gWrittenToBldalpha_Evb
_08097770: .4byte 0x00000111
_08097774:
	cmp r2, #2
	bne _080977F8
	ldr r1, _080977A0 @ =0x04000050
	ldr r6, _080977A4 @ =0x00000842
	adds r0, r6, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r6, #0x80
	lsls r6, r6, #2
	adds r1, r6, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #3
	b _080977F6
	.align 2, 0
_080977A0: .4byte 0x04000050
_080977A4: .4byte 0x00000842
_080977A8:
	ldr r1, _080977D4 @ =0x00000111
	adds r4, r3, r1
	ldrb r2, [r4]
	cmp r2, #0xe
	bhi _080977D8
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #4
	bne _080977F8
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r3, r0
	movs r0, #1
	strb r0, [r1]
	adds r0, r2, #1
	strb r0, [r4]
	b _080977F8
	.align 2, 0
_080977D4: .4byte 0x00000111
_080977D8:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	ldrh r0, [r1]
	cmp r0, #0xf
	bne _080977F8
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08097804 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #4
_080977F6:
	strb r0, [r1]
_080977F8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08097862
	.align 2, 0
_08097804: .4byte gWrittenToBldy
_08097808:
	ldr r4, _08097830 @ =gWrittenToBldalpha_Eva
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08097838
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #6
	bne _0809785A
	movs r0, #0
	strh r0, [r1]
	adds r0, r2, #1
	strh r0, [r4]
	ldr r1, _08097834 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	b _0809785A
	.align 2, 0
_08097830: .4byte gWrittenToBldalpha_Eva
_08097834: .4byte gWrittenToBldalpha_Evb
_08097838:
	ldr r0, _0809786C @ =0x04000050
	movs r1, #0xbf
	strh r1, [r0]
	movs r0, #0x84
	lsls r0, r0, #2
	adds r2, r3, r0
	ldrh r0, [r2]
	cmp r0, #0xf
	bne _0809785A
	movs r0, #0
	movs r1, #0
	strh r1, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	strb r0, [r1]
	movs r5, #1
_0809785A:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08097862:
	adds r0, r5, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0809786C: .4byte 0x04000050

	thumb_func_start DiedOnSr388Collision
DiedOnSr388Collision: @ 0x08097870
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08097888 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _0809789C
	cmp r0, #1
	bgt _0809788C
	cmp r0, #0
	beq _08097896
	b _080978F0
	.align 2, 0
_08097888: .4byte gNonGameplayRam
_0809788C:
	cmp r0, #2
	beq _080978B4
	cmp r0, #3
	beq _080978D0
	b _080978F0
_08097896:
	bl DiedOnSr388CollisionInit
	b _080978A8
_0809789C:
	bl SpecialCutsceneFadeIn
	ldr r0, _080978B0 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080978F0
_080978A8:
	movs r0, #2
	strh r0, [r4, #8]
	b _080978F0
	.align 2, 0
_080978B0: .4byte gWrittenToBldy
_080978B4:
	bl DiedOnSr388CollisionProcess
	cmp r0, #0
	beq _080978F0
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080978F0
_080978D0:
	ldr r1, _080978E0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080978E4
	adds r0, #1
	strh r0, [r1]
	b _080978E8
	.align 2, 0
_080978E0: .4byte gWrittenToBldy
_080978E4:
	strh r5, [r4, #8]
	movs r5, #1
_080978E8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080978F0:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start DiedOnSr388CollisionProcessFallingBsl
DiedOnSr388CollisionProcessFallingBsl: @ 0x080978F8
	push {r4, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #0xa]
	adds r0, #1
	movs r2, #0
	strh r0, [r4, #0xa]
	ldrb r1, [r4, #0x14]
	cmp r1, #0
	bne _0809791A
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strh r1, [r4, #0xa]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _080979CA
_0809791A:
	cmp r1, #1
	bne _08097978
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08097936
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08097936
	strb r2, [r4, #0x12]
_08097936:
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4]
	subs r1, r1, r0
	strh r1, [r4, #0xc]
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4, #2]
	adds r1, r1, r0
	strh r1, [r4, #0xe]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #0x50
	ble _08097962
	movs r0, #0
	strh r0, [r4, #0xa]
	movs r0, #2
	strb r0, [r4, #0x14]
_08097962:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _08097970
	ldrh r0, [r4, #6]
	subs r0, #1
	strh r0, [r4, #6]
	b _080979CA
_08097970:
	ldrh r0, [r4, #6]
	subs r0, #2
	strh r0, [r4, #6]
	b _080979CA
_08097978:
	cmp r1, #2
	bne _080979A4
	movs r0, #3
	strb r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _080979BE
	ldr r0, _0809799C @ =sSr388CollisionUnk_6362b8
	str r0, [r4, #0x1c]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _080979A0 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	strb r1, [r0]
	b _080979CA
	.align 2, 0
_0809799C: .4byte sSr388CollisionUnk_6362b8
_080979A0: .4byte gNonGameplayRam
_080979A4:
	cmp r1, #3
	bne _080979CA
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _080979CA
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080979CA
_080979BE:
	strb r2, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_080979CA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_979d0
unk_979d0: @ 0x080979D0
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080979FC
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _080979FC
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080979FC
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x18]
_080979FC:
	pop {r0}
	bx r0

	thumb_func_start DiedOnSr388CollisionSetupOam
DiedOnSr388CollisionSetupOam: @ 0x08097A00
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov r8, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sb, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _08097A64
	movs r2, #0
	ldr r1, _08097A60 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08097A52
	adds r4, r1, #0
_08097A32:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08097AA2
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08097A32
_08097A52:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	mov ip, r0
	cmp r1, #0x13
	ble _08097AAC
	b _08097AA2
	.align 2, 0
_08097A60: .4byte gNonGameplayRam
_08097A64:
	movs r2, #0x13
	ldr r1, _08097AA8 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08097A9A
	adds r4, r1, #0
	movs r3, #0x8b
	lsls r3, r3, #2
_08097A7A:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08097AA2
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08097A7A
_08097A9A:
	lsls r0, r2, #0x18
	mov ip, r0
	cmp r0, #0
	bge _08097AAC
_08097AA2:
	movs r0, #0x14
	b _08097BE6
	.align 2, 0
_08097AA8: .4byte gNonGameplayRam
_08097AAC:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08097B3C @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	mov r0, ip
	asrs r1, r0, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r5, r0, #2
	ldr r6, _08097B40 @ =0x030016A0
	adds r0, r5, r6
	str r0, [r2, #4]
	ldr r0, _08097B44 @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _08097B48 @ =0xFFFFFDE4
	adds r0, r6, r1
	adds r2, r5, r0
	movs r3, #0x8a
	lsls r3, r3, #2
	adds r0, r2, r3
	mov r1, r8
	strh r1, [r0]
	adds r3, #2
	adds r0, r2, r3
	mov r1, sb
	strh r1, [r0]
	adds r3, #2
	adds r0, r2, r3
	strb r7, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r4, r2, r0
	ldrb r0, [r4]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4]
	cmp r7, #1
	bne _08097B58
	subs r3, #0xa
	adds r1, r2, r3
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r0, _08097B4C @ =0x00000236
	adds r2, r2, r0
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
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097B50 @ =sSr388CollisionUnk_636020
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097B54 @ =DiedOnSr388CollisionProcessFallingBsl
	b _08097BE0
	.align 2, 0
_08097B3C: .4byte 0x040000D4
_08097B40: .4byte 0x030016A0
_08097B44: .4byte 0x85000009
_08097B48: .4byte 0xFFFFFDE4
_08097B4C: .4byte 0x00000236
_08097B50: .4byte sSr388CollisionUnk_636020
_08097B54: .4byte DiedOnSr388CollisionProcessFallingBsl
_08097B58:
	cmp r7, #2
	bne _08097BB8
	ldr r3, _08097BA8 @ =0x00000222
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
	ldr r0, _08097BAC @ =0x00000236
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
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097BB0 @ =sSr388CollisionUnk_636038
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097BB4 @ =DiedOnSr388CollisionProcessFallingBsl
	b _08097BE0
	.align 2, 0
_08097BA8: .4byte 0x00000222
_08097BAC: .4byte 0x00000236
_08097BB0: .4byte sSr388CollisionUnk_636038
_08097BB4: .4byte DiedOnSr388CollisionProcessFallingBsl
_08097BB8:
	cmp r7, #3
	bne _08097BE2
	ldr r1, _08097BF4 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097BF8 @ =sSr388CollisionUnk_636050
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097BFC @ =unk_979d0
_08097BE0:
	str r1, [r0]
_08097BE2:
	mov r3, ip
	lsrs r0, r3, #0x18
_08097BE6:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097BF4: .4byte 0x00000236
_08097BF8: .4byte sSr388CollisionUnk_636050
_08097BFC: .4byte unk_979d0

	thumb_func_start DiedOnSr388CollisionVblank
DiedOnSr388CollisionVblank: @ 0x08097C00
	push {lr}
	ldr r3, _08097C8C @ =0x040000D4
	ldr r0, _08097C90 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _08097C94 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _08097C98 @ =0x04000052
	ldr r0, _08097C9C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097CA0 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097CA4 @ =0x04000054
	ldr r0, _08097CA8 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08097CAC @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB0 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB4 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB8 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CBC @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CC0 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _08097CC4 @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r2, r1, r0
	ldrb r0, [r2]
	cmp r0, #1
	bne _08097C86
	movs r0, #0
	strb r0, [r2]
	ldr r2, _08097CC8 @ =0x00000111
	adds r0, r1, r2
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08097CCC @ =sSr388CollisionUnk_636a38
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08097CD0 @ =0x05000120
	str r0, [r3, #4]
	ldr r0, _08097CD4 @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08097C86:
	pop {r0}
	bx r0
	.align 2, 0
_08097C8C: .4byte 0x040000D4
_08097C90: .4byte gOamData
_08097C94: .4byte 0x84000100
_08097C98: .4byte 0x04000052
_08097C9C: .4byte gWrittenToBldalpha_Evb
_08097CA0: .4byte gWrittenToBldalpha_Eva
_08097CA4: .4byte 0x04000054
_08097CA8: .4byte gWrittenToBldy
_08097CAC: .4byte gBg1XPosition
_08097CB0: .4byte gBg1YPosition
_08097CB4: .4byte 0x0300122C
_08097CB8: .4byte 0x0300122E
_08097CBC: .4byte 0x03001230
_08097CC0: .4byte 0x03001232
_08097CC4: .4byte gNonGameplayRam
_08097CC8: .4byte 0x00000111
_08097CCC: .4byte sSr388CollisionUnk_636a38
_08097CD0: .4byte 0x05000120
_08097CD4: .4byte 0x84000008

	thumb_func_start DiedOnSr388CollisionVblank_Unused
DiedOnSr388CollisionVblank_Unused: @ 0x08097CD8
	ldr r1, _08097D34 @ =0x040000D4
	ldr r0, _08097D38 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08097D3C @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08097D40 @ =0x04000052
	ldr r0, _08097D44 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097D48 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097D4C @ =0x04000054
	ldr r0, _08097D50 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08097D54 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D58 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D5C @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D60 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D64 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D68 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08097D34: .4byte 0x040000D4
_08097D38: .4byte gOamData
_08097D3C: .4byte 0x84000100
_08097D40: .4byte 0x04000052
_08097D44: .4byte gWrittenToBldalpha_Evb
_08097D48: .4byte gWrittenToBldalpha_Eva
_08097D4C: .4byte 0x04000054
_08097D50: .4byte gWrittenToBldy
_08097D54: .4byte gBg1XPosition
_08097D58: .4byte gBg1YPosition
_08097D5C: .4byte 0x0300122C
_08097D60: .4byte 0x0300122E
_08097D64: .4byte 0x03001230
_08097D68: .4byte 0x03001232

	thumb_func_start DiedOnSr388CollisionGetPositionAndSlotOfOamByType
DiedOnSr388CollisionGetPositionAndSlotOfOamByType: @ 0x08097D6C
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _08097DA4 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_08097D7C:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _08097DAC
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _08097DA8 @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08097DC4
	.align 2, 0
_08097DA4: .4byte gNonGameplayRam
_08097DA8: .4byte 0x0000022A
_08097DAC:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _08097D7C
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08097DC4:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_97dcc
unk_97dcc: @ 0x08097DCC
	bx lr
	.align 2, 0

	thumb_func_start NewFileIntroCheckMonologueEnded
NewFileIntroCheckMonologueEnded: @ 0x08097DD0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	movs r0, #0
	mov r8, r0
	ldr r6, _08097E0C @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r7, r6, r0
	ldrh r0, [r7]
	adds r4, r0, #1
	strh r4, [r7]
	ldr r3, [r6]
	ldrh r2, [r3]
	adds r5, r2, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r5, ip
	bne _08097E14
	mov r0, r8
	strh r0, [r7]
	ldr r7, _08097E10 @ =0x00000213
	adds r1, r6, r7
	movs r0, #0x64
	strb r0, [r1]
	movs r0, #1
	mov r8, r0
	b _08097E96
	.align 2, 0
_08097E0C: .4byte gNonGameplayRam
_08097E10: .4byte 0x00000213
_08097E14:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r5, r0
	bne _08097E68
	mov r0, r8
	strh r0, [r7]
	movs r7, #0x86
	lsls r7, r7, #2
	adds r4, r6, r7
	ldrb r1, [r4]
	cmp r1, #1
	bne _08097E96
	adds r2, r3, #2
	str r2, [r6]
	subs r7, #5
	adds r0, r6, r7
	strb r1, [r0]
	ldrh r1, [r3, #2]
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097E46
	movs r0, #2
	strb r0, [r4]
	b _08097E96
_08097E46:
	cmp r1, ip
	beq _08097E5C
	cmp r1, r5
	bne _08097E62
	movs r0, #4
	strb r0, [r4]
	adds r0, r2, #2
	str r0, [r6]
	ldrh r0, [r2, #2]
	cmp r0, ip
	bne _08097E96
_08097E5C:
	movs r0, #3
	strb r0, [r4]
	b _08097E96
_08097E62:
	movs r0, #0
	strb r0, [r4]
	b _08097E96
_08097E68:
	mov r0, ip
	ands r0, r2
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _08097E82
	movs r1, #0xff
	ands r1, r2
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08097E96
	b _08097E8A
_08097E82:
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _08097E96
_08097E8A:
	ldr r0, _08097EA4 @ =0x00000213
	adds r1, r6, r0
	movs r0, #1
	strb r0, [r1]
	mov r0, r8
	strh r0, [r7]
_08097E96:
	mov r0, r8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097EA4: .4byte 0x00000213

	thumb_func_start EndingCheckMonologueEnded
EndingCheckMonologueEnded: @ 0x08097EA8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	movs r0, #0
	mov r8, r0
	ldr r6, _08097EE4 @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r7, r6, r0
	ldrh r0, [r7]
	adds r4, r0, #1
	strh r4, [r7]
	ldr r3, [r6]
	ldrh r2, [r3]
	adds r5, r2, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r5, ip
	bne _08097EEC
	mov r0, r8
	strh r0, [r7]
	ldr r7, _08097EE8 @ =0x00000213
	adds r1, r6, r7
	movs r0, #0x64
	strb r0, [r1]
	movs r0, #1
	mov r8, r0
	b _08097F6E
	.align 2, 0
_08097EE4: .4byte gNonGameplayRam
_08097EE8: .4byte 0x00000213
_08097EEC:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r5, r0
	bne _08097F40
	mov r0, r8
	strh r0, [r7]
	movs r7, #0x86
	lsls r7, r7, #2
	adds r4, r6, r7
	ldrb r1, [r4]
	cmp r1, #1
	bne _08097F6E
	adds r2, r3, #2
	str r2, [r6]
	subs r7, #5
	adds r0, r6, r7
	strb r1, [r0]
	ldrh r1, [r3, #2]
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097F1E
	movs r0, #2
	strb r0, [r4]
	b _08097F6E
_08097F1E:
	cmp r1, ip
	beq _08097F34
	cmp r1, r5
	bne _08097F3A
	movs r0, #4
	strb r0, [r4]
	adds r0, r2, #2
	str r0, [r6]
	ldrh r0, [r2, #2]
	cmp r0, ip
	bne _08097F6E
_08097F34:
	movs r0, #3
	strb r0, [r4]
	b _08097F6E
_08097F3A:
	movs r0, #0
	strb r0, [r4]
	b _08097F6E
_08097F40:
	mov r0, ip
	ands r0, r2
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _08097F5A
	movs r1, #0xff
	ands r1, r2
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08097F6E
	b _08097F62
_08097F5A:
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #3
	bls _08097F6E
_08097F62:
	ldr r0, _08097F7C @ =0x00000213
	adds r1, r6, r0
	movs r0, #1
	strb r0, [r1]
	mov r0, r8
	strh r0, [r7]
_08097F6E:
	mov r0, r8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097F7C: .4byte 0x00000213

	thumb_func_start SpecialCutsceneProcessMonologue
SpecialCutsceneProcessMonologue: @ 0x08097F80
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	ldr r5, _08097FF0 @ =gNonGameplayRam
	ldr r2, [r5]
	ldrh r3, [r2]
	adds r1, r3, #0
	movs r6, #0xff
	lsls r6, r6, #8
	adds r4, r5, #0
	cmp r1, r6
	bne _08097F9C
	b _08098142
_08097F9C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097FF8
	ldrh r0, [r4, #0xc]
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0x1b
	bhi _08097FD4
	adds r6, r4, #0
	adds r5, #0x14
	movs r3, #0xff
_08097FB6:
	ldrh r1, [r6, #0xe]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r2, r0
	adds r0, r0, r5
	ldrb r1, [r0]
	orrs r1, r3
	strb r1, [r0]
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0x1b
	bls _08097FB6
_08097FD4:
	movs r1, #0
	movs r0, #0
	strh r0, [r4, #0xc]
	ldrh r0, [r4, #0xe]
	adds r0, #2
	strh r0, [r4, #0xe]
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
	ldr r2, _08097FF4 @ =0x00000212
	adds r0, r4, r2
	strb r1, [r0]
	b _08098142
	.align 2, 0
_08097FF0: .4byte gNonGameplayRam
_08097FF4: .4byte 0x00000212
_08097FF8:
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809807C
	movs r2, #0
	str r2, [sp, #4]
	ldr r1, _08098064 @ =0x040000D4
	add r5, sp, #4
	str r5, [r1]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08098068 @ =0x85001200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r3, #0
	strh r2, [r4, #0x12]
	strh r2, [r4, #0x10]
	strh r2, [r4, #0xe]
	strh r2, [r4, #0xc]
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
	ldr r5, _0809806C @ =0x00000212
	adds r0, r4, r5
	strb r3, [r0]
	str r2, [sp, #4]
	add r0, sp, #4
	str r0, [r1]
	adds r0, r4, #0
	adds r0, #0x14
	str r0, [r1, #4]
	ldr r3, _08098070 @ =0x8500003F
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	str r2, [sp, #4]
	add r2, sp, #4
	str r2, [r1]
	movs r5, #0x88
	lsls r5, r5, #1
	adds r0, r4, r5
	str r0, [r1, #4]
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0x80
	lsls r0, r0, #0x12
	str r0, [r1]
	ldr r0, _08098074 @ =0x06004800
	str r0, [r1, #4]
	ldr r0, _08098078 @ =0x84000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098142
	.align 2, 0
_08098064: .4byte 0x040000D4
_08098068: .4byte 0x85001200
_0809806C: .4byte 0x00000212
_08098070: .4byte 0x8500003F
_08098074: .4byte 0x06004800
_08098078: .4byte 0x84000200
_0809807C:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809808C
	ldrh r0, [r4, #0xc]
	adds r0, #1
	strh r0, [r4, #0xc]
	b _08098142
_0809808C:
	adds r0, r6, #0
	ands r0, r3
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809809E
	adds r0, r2, #2
	str r0, [r4]
	b _08098142
_0809809E:
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r4, r4, r0
	ldrh r0, [r2]
	bl TextGetCharacterWidth
	mov r8, r0
	ldr r0, [r5]
	ldrh r0, [r0]
	mov r1, r8
	lsls r2, r1, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _08098150 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	movs r1, #0
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrh r0, [r5, #0xc]
	cmp r0, #0x1b
	bhi _0809813A
	ldrh r1, [r5, #0xe]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	ldrh r2, [r5, #0xc]
	adds r0, r0, r2
	adds r7, r5, #0
	adds r7, #0x14
	adds r0, r0, r7
	movs r1, #4
	strb r1, [r0]
	ldrb r0, [r6]
	add r0, r8
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r4, r5, #0
	cmp r0, #7
	bls _0809813A
	adds r2, r4, #0
	adds r3, r6, #0
	adds r4, r7, #0
_08098104:
	ldrb r0, [r3]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r3]
	ldrh r0, [r2, #0xc]
	adds r0, #1
	strh r0, [r2, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1b
	bhi _0809813A
	lsls r0, r1, #0x18
	cmp r0, #0
	beq _08098134
	ldrh r0, [r2, #0xe]
	lsrs r0, r0, #1
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	ldrh r5, [r2, #0xc]
	adds r1, r1, r5
	adds r1, r1, r4
	movs r0, #4
	strb r0, [r1]
_08098134:
	ldrb r0, [r3]
	cmp r0, #7
	bhi _08098104
_0809813A:
	ldr r1, _08098154 @ =gNonGameplayRam
	ldr r0, [r1]
	adds r0, #2
	str r0, [r1]
_08098142:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098150: .4byte 0x00000212
_08098154: .4byte gNonGameplayRam

	thumb_func_start unk_98158
unk_98158: @ 0x08098158
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	ldr r1, _08098198 @ =gNonGameplayRam
	ldrh r6, [r1, #0x10]
	ldrh r0, [r1, #0x12]
	lsrs r7, r0, #1
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	str r1, [sp, #8]
	cmp r7, r0
	bls _08098178
	b _0809827C
_08098178:
	str r1, [sp]
_0809817A:
	ldr r2, [sp]
	ldr r0, [r2]
	ldrh r0, [r0]
	movs r3, #0xfc
	lsls r3, r3, #8
	cmp r0, r3
	bne _0809819C
	ldrh r0, [r1, #0xc]
	cmp r0, #0x1b
	bhi _080981B6
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov ip, r0
	b _080981BA
	.align 2, 0
_08098198: .4byte gNonGameplayRam
_0809819C:
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	cmp r7, r0
	bne _080981B6
	ldr r1, [sp]
	ldrh r0, [r1, #0xc]
	movs r2, #0x1c
	mov ip, r2
	cmp r0, #0x1b
	bhi _080981BA
	adds r3, r0, #0
	mov ip, r3
	b _080981BA
_080981B6:
	movs r5, #0x1c
	mov ip, r5
_080981BA:
	adds r0, r7, #1
	str r0, [sp, #4]
	cmp r6, ip
	bhs _08098268
	ldr r1, _08098230 @ =gNonGameplayRam
	mov r8, r1
	lsls r0, r7, #3
	subs r0, r0, r7
	lsls r0, r0, #2
	mov sl, r0
	ldr r2, _08098234 @ =0x00000FFF
	mov sb, r2
_080981D2:
	mov r3, sl
	adds r2, r6, r3
	ldr r5, _08098238 @ =0x03001594
	adds r1, r2, r5
	ldrb r0, [r1]
	cmp r0, #5
	bne _0809825A
	movs r0, #0
	strb r0, [r1]
	ldr r0, [sp, #8]
	adds r0, #0x14
	adds r2, r2, r0
	ldrb r0, [r2]
	subs r1, r0, #1
	strb r1, [r2]
	lsls r0, r1, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0
	ble _08098244
	lsls r2, r6, #1
	lsls r0, r7, #7
	adds r2, r2, r0
	ldr r0, _0809823C @ =0x06004842
	adds r0, r2, r0
	str r0, [sp, #0xc]
	ldr r1, _08098240 @ =0x06004882
	adds r2, r2, r1
	ldrh r3, [r0]
	ldrh r4, [r2]
	lsrs r0, r3, #0xc
	lsrs r1, r4, #0xc
	subs r0, #1
	lsls r0, r0, #0x10
	subs r1, #1
	lsls r1, r1, #0x10
	lsrs r0, r0, #4
	mov r5, sb
	ands r3, r5
	orrs r0, r3
	ldr r3, [sp, #0xc]
	strh r0, [r3]
	lsrs r1, r1, #4
	ands r4, r5
	orrs r1, r4
	strh r1, [r2]
	b _0809825E
	.align 2, 0
_08098230: .4byte gNonGameplayRam
_08098234: .4byte 0x00000FFF
_08098238: .4byte 0x03001594
_0809823C: .4byte 0x06004842
_08098240: .4byte 0x06004882
_08098244:
	cmp r0, #0
	bne _08098252
	mov r5, r8
	strh r6, [r5, #0x10]
	lsls r0, r7, #1
	strh r0, [r5, #0x12]
	b _0809825E
_08098252:
	movs r0, #0xff
	orrs r1, r0
	strb r1, [r2]
	b _08098268
_0809825A:
	adds r0, #1
	strb r0, [r1]
_0809825E:
	adds r0, r6, #1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, ip
	blo _080981D2
_08098268:
	movs r6, #0
	ldr r1, [sp, #4]
	lsls r0, r1, #0x10
	lsrs r7, r0, #0x10
	ldr r1, [sp, #8]
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	cmp r7, r0
	bhi _0809827C
	b _0809817A
_0809827C:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessAdamText
EndingProcessAdamText: @ 0x0809828C
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	movs r7, #0
	ldr r5, _080982E8 @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r6, r5, r0
	ldrh r0, [r6]
	adds r2, r0, #1
	movs r1, #0
	mov sb, r1
	strh r2, [r6]
	ldr r3, [r5]
	ldrh r4, [r3]
	adds r1, r4, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r1, ip
	bne _080982FC
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf
	bhi _080982C4
	b _08098492
_080982C4:
	strh r7, [r6]
	str r7, [sp, #4]
	ldr r1, _080982EC @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080982F0 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080982F4 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _080982F8 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	movs r7, #1
	b _08098492
	.align 2, 0
_080982E8: .4byte gNonGameplayRam
_080982EC: .4byte 0x040000D4
_080982F0: .4byte 0x0600D000
_080982F4: .4byte 0x85000400
_080982F8: .4byte 0x00000212
_080982FC:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809836C
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _0809832C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #5
	bhi _08098314
	b _08098492
_08098314:
	strh r7, [r6]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _08098328 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	b _08098408
	.align 2, 0
_08098328: .4byte 0x00000212
_0809832C:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7d
	bhi _08098336
	b _08098492
_08098336:
	strh r7, [r6]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _0809835C @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	adds r0, r3, #2
	str r0, [r5]
	str r7, [sp, #4]
	ldr r1, _08098360 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098364 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098368 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098492
	.align 2, 0
_0809835C: .4byte 0x00000212
_08098360: .4byte 0x040000D4
_08098364: .4byte 0x0600D000
_08098368: .4byte 0x85000400
_0809836C:
	movs r0, #0xfd
	lsls r0, r0, #8
	mov r8, r0
	cmp r1, r8
	bne _080983B8
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf
	bhi _08098380
	b _08098492
_08098380:
	strh r7, [r6]
	str r7, [sp, #4]
	ldr r1, _080983A8 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080983AC @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080983B0 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	adds r0, r3, #2
	str r0, [r5]
	ldr r1, _080983B4 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	b _08098492
	.align 2, 0
_080983A8: .4byte 0x040000D4
_080983AC: .4byte 0x0600D000
_080983B0: .4byte 0x85000400
_080983B4: .4byte 0x00000212
_080983B8:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080983EE
	strh r7, [r6]
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	cmp r0, #1
	bne _08098492
	adds r0, r3, #2
	str r0, [r5]
	ldrh r0, [r3, #2]
	cmp r0, r8
	bne _080983DE
	movs r0, #2
	strb r0, [r1]
	b _08098492
_080983DE:
	cmp r0, ip
	bne _080983E8
	movs r0, #3
	strb r0, [r1]
	b _08098492
_080983E8:
	mov r0, sb
	strb r0, [r1]
	b _08098492
_080983EE:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809840E
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08098492
	strh r7, [r6]
_08098408:
	adds r0, r3, #2
	str r0, [r5]
	b _08098492
_0809840E:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #5
	bls _08098492
	strh r7, [r6]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _080984A4 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r3]
	bl TextGetCharacterWidth
	mov r8, r0
	ldr r0, [r5]
	ldrh r0, [r0]
	mov r1, r8
	lsls r2, r1, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _080984A8 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	str r7, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldr r1, [r5]
	ldrh r0, [r1]
	cmp r0, #0x40
	beq _08098454
	movs r1, #1
	bl PlayCharacterAppearingSound
_08098454:
	ldrh r0, [r5, #0xc]
	adds r4, r5, #0
	cmp r0, #0x1f
	bhi _0809848C
	ldrb r0, [r6]
	add r0, r8
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0809848C
	adds r3, r4, #0
	adds r2, r6, #0
_0809846E:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _0809848C
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _0809846E
_0809848C:
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
_08098492:
	adds r0, r7, #0
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080984A4: .4byte 0x0600D000
_080984A8: .4byte 0x00000212

	thumb_func_start IntroProcessText
IntroProcessText: @ 0x080984AC
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	movs r0, #0
	mov r8, r0
	ldr r5, _08098514 @ =gNonGameplayRam
	movs r1, #0x83
	lsls r1, r1, #2
	adds r7, r5, r1
	ldrh r0, [r7]
	adds r2, r0, #1
	movs r0, #0
	mov sl, r0
	strh r2, [r7]
	ldr r6, [r5]
	ldrh r4, [r6]
	adds r3, r4, #0
	movs r1, #0xff
	lsls r1, r1, #8
	mov ip, r1
	cmp r3, ip
	bne _08098528
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080984E8
	b _080986D2
_080984E8:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _08098518 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _0809851C @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098520 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098524 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	movs r0, #1
	mov r8, r0
	b _080986D2
	.align 2, 0
_08098514: .4byte gNonGameplayRam
_08098518: .4byte 0x040000D4
_0809851C: .4byte 0x0600D000
_08098520: .4byte 0x85000400
_08098524: .4byte 0x00000212
_08098528:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r3, r0
	bne _0809859C
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _08098558
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bhi _08098540
	b _080986D2
_08098540:
	mov r1, r8
	strh r1, [r7]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098554 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098654
	.align 2, 0
_08098554: .4byte 0x00000212
_08098558:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7a
	bhi _08098562
	b _080986D2
_08098562:
	mov r0, r8
	strh r0, [r7]
	strh r0, [r5, #0xe]
	strh r0, [r5, #0xc]
	ldr r1, _0809858C @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	adds r0, r6, #2
	str r0, [r5]
	mov r0, r8
	str r0, [sp, #4]
	ldr r1, _08098590 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098594 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098598 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _080986D2
	.align 2, 0
_0809858C: .4byte 0x00000212
_08098590: .4byte 0x040000D4
_08098594: .4byte 0x0600D000
_08098598: .4byte 0x85000400
_0809859C:
	movs r1, #0xfd
	lsls r1, r1, #8
	mov sb, r1
	cmp r3, sb
	bne _080985EC
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080985B0
	b _080986D2
_080985B0:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _080985DC @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080985E0 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080985E4 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	adds r0, r6, #2
	str r0, [r5]
	ldr r1, _080985E8 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _080986D2
	.align 2, 0
_080985DC: .4byte 0x040000D4
_080985E0: .4byte 0x0600D000
_080985E4: .4byte 0x85000400
_080985E8: .4byte 0x00000212
_080985EC:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r3, r0
	bne _08098638
	mov r0, r8
	strh r0, [r7]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrb r0, [r2]
	cmp r0, #1
	bne _080986D2
	adds r1, r6, #2
	str r1, [r5]
	ldrh r0, [r6, #2]
	cmp r0, sb
	bne _08098614
	movs r0, #2
	strb r0, [r2]
	b _080986D2
_08098614:
	cmp r0, ip
	beq _08098626
	cmp r0, r3
	bne _08098632
	adds r0, r1, #2
	str r0, [r5]
	ldrh r0, [r1, #2]
	cmp r0, ip
	bne _0809862C
_08098626:
	movs r0, #3
	strb r0, [r2]
	b _080986D2
_0809862C:
	movs r0, #4
	strb r0, [r2]
	b _080986D2
_08098632:
	mov r0, sl
	strb r0, [r2]
	b _080986D2
_08098638:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809865A
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _080986D2
	mov r1, r8
	strh r1, [r7]
_08098654:
	adds r0, r6, #2
	str r0, [r5]
	b _080986D2
_0809865A:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _080986D2
	mov r0, r8
	strh r0, [r7]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _080986E4 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	adds r7, r0, #0
	ldr r0, [r5]
	ldrh r0, [r0]
	lsls r2, r7, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _080986E8 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	mov r1, r8
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrh r0, [r5, #0xc]
	cmp r0, #0x1f
	bhi _080986CA
	ldrb r0, [r6]
	adds r0, r0, r7
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _080986CA
	adds r3, r5, #0
	adds r2, r6, #0
_080986AC:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _080986CA
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080986AC
_080986CA:
	ldr r1, _080986EC @ =gNonGameplayRam
	ldr r0, [r1]
	adds r0, #2
	str r0, [r1]
_080986D2:
	mov r0, r8
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080986E4: .4byte 0x0600D000
_080986E8: .4byte 0x00000212
_080986EC: .4byte gNonGameplayRam

	thumb_func_start NewFileIntroProcessAdamText
NewFileIntroProcessAdamText: @ 0x080986F0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	movs r0, #0
	mov r8, r0
	ldr r5, _08098758 @ =gNonGameplayRam
	movs r1, #0x83
	lsls r1, r1, #2
	adds r7, r5, r1
	ldrh r0, [r7]
	adds r2, r0, #1
	movs r0, #0
	mov sl, r0
	strh r2, [r7]
	ldr r6, [r5]
	ldrh r4, [r6]
	adds r3, r4, #0
	movs r1, #0xff
	lsls r1, r1, #8
	mov ip, r1
	cmp r3, ip
	bne _0809876C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _0809872C
	b _08098924
_0809872C:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _0809875C @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098760 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098764 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098768 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	movs r0, #1
	mov r8, r0
	b _08098924
	.align 2, 0
_08098758: .4byte gNonGameplayRam
_0809875C: .4byte 0x040000D4
_08098760: .4byte 0x0600D000
_08098764: .4byte 0x85000400
_08098768: .4byte 0x00000212
_0809876C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r3, r0
	bne _080987E0
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _0809879C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bhi _08098784
	b _08098924
_08098784:
	mov r1, r8
	strh r1, [r7]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098798 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098898
	.align 2, 0
_08098798: .4byte 0x00000212
_0809879C:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7a
	bhi _080987A6
	b _08098924
_080987A6:
	mov r0, r8
	strh r0, [r7]
	strh r0, [r5, #0xe]
	strh r0, [r5, #0xc]
	ldr r1, _080987D0 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	adds r0, r6, #2
	str r0, [r5]
	mov r0, r8
	str r0, [sp, #4]
	ldr r1, _080987D4 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080987D8 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080987DC @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098924
	.align 2, 0
_080987D0: .4byte 0x00000212
_080987D4: .4byte 0x040000D4
_080987D8: .4byte 0x0600D000
_080987DC: .4byte 0x85000400
_080987E0:
	movs r1, #0xfd
	lsls r1, r1, #8
	mov sb, r1
	cmp r3, sb
	bne _08098830
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080987F4
	b _08098924
_080987F4:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _08098820 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098824 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098828 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	adds r0, r6, #2
	str r0, [r5]
	ldr r1, _0809882C @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098924
	.align 2, 0
_08098820: .4byte 0x040000D4
_08098824: .4byte 0x0600D000
_08098828: .4byte 0x85000400
_0809882C: .4byte 0x00000212
_08098830:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r3, r0
	bne _0809887C
	mov r0, r8
	strh r0, [r7]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrb r0, [r2]
	cmp r0, #1
	bne _08098924
	adds r1, r6, #2
	str r1, [r5]
	ldrh r0, [r6, #2]
	cmp r0, sb
	bne _08098858
	movs r0, #2
	strb r0, [r2]
	b _08098924
_08098858:
	cmp r0, ip
	beq _0809886A
	cmp r0, r3
	bne _08098876
	adds r0, r1, #2
	str r0, [r5]
	ldrh r0, [r1, #2]
	cmp r0, ip
	bne _08098870
_0809886A:
	movs r0, #3
	strb r0, [r2]
	b _08098924
_08098870:
	movs r0, #4
	strb r0, [r2]
	b _08098924
_08098876:
	mov r0, sl
	strb r0, [r2]
	b _08098924
_0809887C:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809889E
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08098924
	mov r1, r8
	strh r1, [r7]
_08098898:
	adds r0, r6, #2
	str r0, [r5]
	b _08098924
_0809889E:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _08098924
	mov r0, r8
	strh r0, [r7]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _08098938 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	adds r7, r0, #0
	ldr r0, [r5]
	ldrh r0, [r0]
	lsls r2, r7, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _0809893C @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	mov r1, r8
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldr r1, [r5]
	ldrh r0, [r1]
	cmp r0, #0x40
	beq _080988E6
	movs r1, #1
	bl PlayCharacterAppearingSound
_080988E6:
	ldrh r0, [r5, #0xc]
	adds r4, r5, #0
	cmp r0, #0x1f
	bhi _0809891E
	ldrb r0, [r6]
	adds r0, r0, r7
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0809891E
	adds r3, r4, #0
	adds r2, r6, #0
_08098900:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _0809891E
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _08098900
_0809891E:
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
_08098924:
	mov r0, r8
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08098938: .4byte 0x0600D000
_0809893C: .4byte 0x00000212

	thumb_func_start Dma3Transfer_Unused1
Dma3Transfer_Unused1: @ 0x08098940
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	lsls r3, r3, #0x10
	lsrs r7, r3, #0x10
	lsls r2, r2, #0x15
	movs r3, #0
	cmp r3, r7
	bhs _08098976
	ldr r1, _0809897C @ =0x040000D4
	lsrs r2, r2, #0x12
	movs r0, #0x84
	lsls r0, r0, #0x18
	orrs r2, r0
	movs r6, #0x80
	lsls r6, r6, #3
_08098960:
	str r5, [r1]
	str r4, [r1, #4]
	str r2, [r1, #8]
	ldr r0, [r1, #8]
	adds r5, r5, r6
	adds r4, r4, r6
	adds r0, r3, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, r7
	blo _08098960
_08098976:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809897C: .4byte 0x040000D4

	thumb_func_start Dma3Transfer_Unused2
Dma3Transfer_Unused2: @ 0x08098980
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	lsls r3, r3, #0x10
	lsrs r6, r3, #0x10
	lsls r2, r2, #0x11
	movs r3, #0
	cmp r3, r6
	bhs _080989B2
	ldr r1, _080989B8 @ =0x040000D4
	lsrs r2, r2, #0x11
	movs r0, #0x80
	lsls r0, r0, #0x18
	orrs r2, r0
_0809899C:
	str r5, [r1]
	str r4, [r1, #4]
	str r2, [r1, #8]
	ldr r0, [r1, #8]
	adds r5, #0x40
	adds r4, #0x40
	adds r0, r3, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, r6
	blo _0809899C
_080989B2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080989B8: .4byte 0x040000D4

	thumb_func_start Dma3Clear_Unused
Dma3Clear_Unused: @ 0x080989BC
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r4, r0, #0
	lsls r2, r2, #0x10
	lsrs r5, r2, #0x10
	lsls r1, r1, #0x15
	movs r2, #0
	cmp r2, r5
	bhs _080989F6
	movs r7, #0
	ldr r3, _08098A00 @ =0x040000D4
	lsrs r1, r1, #0x12
	movs r0, #0x85
	lsls r0, r0, #0x18
	orrs r1, r0
	movs r6, #0x80
	lsls r6, r6, #3
_080989DE:
	str r7, [sp]
	mov r0, sp
	str r0, [r3]
	str r4, [r3, #4]
	str r1, [r3, #8]
	ldr r0, [r3, #8]
	adds r4, r4, r6
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, r5
	blo _080989DE
_080989F6:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098A00: .4byte 0x040000D4

	thumb_func_start unk_98a04
unk_98a04: @ 0x08098A04
	push {r4, r5, r6, r7, lr}
	movs r3, #0
	ldr r0, _08098A48 @ =gNonGameplayRam
	mov ip, r0
	movs r7, #0x88
	lsls r7, r7, #1
	add r7, ip
	movs r6, #0x96
	lsls r6, r6, #1
	add r6, ip
	movs r5, #0xb2
	lsls r5, r5, #1
	add r5, ip
	movs r4, #0xa4
	lsls r4, r4, #1
	add r4, ip
_08098A24:
	adds r0, r3, r7
	adds r1, r3, r6
	ldrb r2, [r1]
	ldrb r0, [r0]
	cmp r0, r2
	bhi _08098A50
	movs r2, #0
	strb r2, [r1]
	adds r1, r3, r5
	movs r0, #1
	strb r0, [r1]
	adds r1, r3, r4
	ldrb r0, [r1]
	cmp r0, #0x25
	bhi _08098A4C
	adds r0, #1
	b _08098A52
	.align 2, 0
_08098A48: .4byte gNonGameplayRam
_08098A4C:
	strb r2, [r1]
	b _08098A54
_08098A50:
	adds r0, r2, #1
_08098A52:
	strb r0, [r1]
_08098A54:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #3
	bls _08098A24
	movs r0, #0x8d
	lsls r0, r0, #1
	add r0, ip
	movs r2, #0x9b
	lsls r2, r2, #1
	add r2, ip
	ldrb r1, [r2]
	ldrb r0, [r0]
	cmp r0, r1
	bhi _08098A96
	movs r3, #0
	strb r3, [r2]
	movs r1, #0xb7
	lsls r1, r1, #1
	add r1, ip
	movs r0, #1
	strb r0, [r1]
	movs r1, #0xa9
	lsls r1, r1, #1
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #0xe
	bhi _08098A92
	adds r0, #1
	strb r0, [r1]
	b _08098A9A
_08098A92:
	strb r3, [r1]
	b _08098A9A
_08098A96:
	adds r0, r1, #1
	strb r0, [r2]
_08098A9A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start NewFileIntroSamusGettingCuredSetupWindow
NewFileIntroSamusGettingCuredSetupWindow: @ 0x08098AA0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	ldr r1, _08098AE4 @ =0x040000D4
	ldr r0, _08098AE8 @ =0x02001000
	str r0, [r1]
	ldr r0, _08098AEC @ =0x02002000
	str r0, [r1, #4]
	ldr r0, _08098AF0 @ =0x84000058
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r1, _08098AF4 @ =gNonGameplayRam
	ldr r2, _08098AF8 @ =0x000001F5
	adds r0, r1, r2
	ldrb r2, [r0]
	ldr r3, _08098AFC @ =0x000001F3
	adds r0, r1, r3
	ldrb r3, [r0]
	subs r0, r2, r3
	lsls r0, r0, #0x10
	adds r7, r2, r3
	lsrs r2, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0
	bge _08098B00
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsls r0, r3, #1
	movs r2, #0
	cmp r5, r0
	ble _08098B02
	movs r2, #0xa1
	b _08098B02
	.align 2, 0
_08098AE4: .4byte 0x040000D4
_08098AE8: .4byte 0x02001000
_08098AEC: .4byte 0x02002000
_08098AF0: .4byte 0x84000058
_08098AF4: .4byte gNonGameplayRam
_08098AF8: .4byte 0x000001F5
_08098AFC: .4byte 0x000001F3
_08098B00:
	movs r5, #0
_08098B02:
	cmp r7, #0x9f
	ble _08098B08
	movs r7, #0xa0
_08098B08:
	ldr r0, _08098BBC @ =sHaze_PowerBomb_WindowValuesPointers
	ldr r6, _08098BC0 @ =0x000001F3
	adds r1, r1, r6
	ldrb r1, [r1]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	mov ip, r1
	ldr r4, _08098BC4 @ =0x02001000
	movs r6, #0
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	lsls r1, r7, #0x10
	cmp r6, r0
	bge _08098B3E
	movs r2, #0
	adds r3, r0, #0
_08098B2A:
	strh r2, [r4]
	adds r4, #2
	lsls r0, r6, #0x10
	movs r6, #0x80
	lsls r6, r6, #9
	adds r0, r0, r6
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r3
	blt _08098B2A
_08098B3E:
	lsls r0, r6, #0x10
	asrs r3, r1, #0x10
	cmp r0, r1
	bgt _08098B98
	ldr r0, _08098BC8 @ =0x03001678
	mov r8, r0
	adds r7, r3, #0
_08098B4C:
	mov r1, r8
	ldrb r2, [r1]
	lsls r0, r5, #2
	add r0, ip
	ldrh r1, [r0, #2]
	adds r1, r2, r1
	lsls r1, r1, #0x10
	ldrh r0, [r0]
	adds r2, r2, r0
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	lsrs r3, r1, #0x10
	cmp r1, #0
	bge _08098B6A
	movs r3, #0
_08098B6A:
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf0
	ble _08098B74
	movs r2, #0xf0
_08098B74:
	lsls r1, r3, #0x10
	asrs r1, r1, #8
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	orrs r0, r1
	strh r0, [r4]
	adds r4, #2
	adds r0, r5, #1
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsls r0, r6, #0x10
	movs r2, #0x80
	lsls r2, r2, #9
	adds r0, r0, r2
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r7
	ble _08098B4C
_08098B98:
	lsls r1, r6, #0x10
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	bgt _08098BB2
	movs r2, #0
_08098BA2:
	strh r2, [r4]
	adds r4, #2
	movs r3, #0x80
	lsls r3, r3, #9
	adds r1, r1, r3
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	ble _08098BA2
_08098BB2:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098BBC: .4byte sHaze_PowerBomb_WindowValuesPointers
_08098BC0: .4byte 0x000001F3
_08098BC4: .4byte 0x02001000
_08098BC8: .4byte 0x03001678

	thumb_func_start SpecialCutsceneFadeIn
SpecialCutsceneFadeIn: @ 0x08098BCC
	push {lr}
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08098BE8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _08098BE2
	subs r0, #1
	strh r0, [r1]
_08098BE2:
	pop {r0}
	bx r0
	.align 2, 0
_08098BE8: .4byte gWrittenToBldy

	thumb_func_start SpecialCutsceneFadOut
SpecialCutsceneFadOut: @ 0x08098BEC
	push {lr}
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08098C08 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08098C02
	adds r0, #1
	strh r0, [r1]
_08098C02:
	pop {r0}
	bx r0
	.align 2, 0
_08098C08: .4byte gWrittenToBldy

	thumb_func_start NewFileIntroProcessTextCursor
NewFileIntroProcessTextCursor: @ 0x08098C0C
	push {lr}
	adds r2, r0, #0
	ldr r0, _08098C28 @ =gNonGameplayRam
	ldr r0, [r0]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08098C2C
	movs r0, #0xeb
	strh r0, [r2, #0xc]
	movs r0, #0x98
	strh r0, [r2, #0xe]
	b _08098C32
	.align 2, 0
_08098C28: .4byte gNonGameplayRam
_08098C2C:
	movs r0, #0x82
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
_08098C32:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start SpecialCutsceneClearOam
SpecialCutsceneClearOam: @ 0x08098C38
	push {r4, r5, r6, lr}
	movs r3, #0
	ldr r6, _08098C68 @ =gNonGameplayRam
	movs r4, #0x8d
	lsls r4, r4, #2
	movs r5, #2
	rsbs r5, r5, #0
_08098C46:
	lsls r1, r3, #3
	adds r1, r1, r3
	lsls r1, r1, #2
	adds r1, r1, r6
	adds r1, r1, r4
	ldrb r2, [r1]
	adds r0, r5, #0
	ands r0, r2
	strb r0, [r1]
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0x13
	bls _08098C46
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098C68: .4byte gNonGameplayRam

	thumb_func_start SpecialCutsceneEnableOam
SpecialCutsceneEnableOam: @ 0x08098C6C
	push {r4, r5, r6, lr}
	movs r2, #0
	ldr r6, _08098CA4 @ =gNonGameplayRam
	movs r5, #0x8b
	lsls r5, r5, #2
	movs r4, #0x8d
	lsls r4, r4, #2
	movs r3, #1
_08098C7C:
	lsls r0, r2, #3
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r1, r0, r6
	adds r0, r1, r5
	ldrb r0, [r0]
	cmp r0, #0
	beq _08098C94
	adds r1, r1, r4
	ldrb r0, [r1]
	orrs r0, r3
	strb r0, [r1]
_08098C94:
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0x13
	bls _08098C7C
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098CA4: .4byte gNonGameplayRam

	thumb_func_start SpecialCutsceneDestroyOamOfType
SpecialCutsceneDestroyOamOfType: @ 0x08098CA8
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r3, #0
	ldr r6, _08098CE0 @ =gNonGameplayRam
	movs r7, #2
	rsbs r7, r7, #0
	movs r5, #0x8b
	lsls r5, r5, #2
_08098CBA:
	lsls r0, r3, #3
	adds r0, r0, r3
	lsls r0, r0, #2
	adds r2, r0, r6
	adds r1, r2, r5
	ldrb r0, [r1]
	cmp r0, r4
	bne _08098CE4
	movs r0, #0
	strb r0, [r1]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r2, r2, r0
	ldrb r1, [r2]
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r2]
	b _08098CEE
	.align 2, 0
_08098CE0: .4byte gNonGameplayRam
_08098CE4:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0x13
	bls _08098CBA
_08098CEE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start SpecialCutsceneProcessOam
SpecialCutsceneProcessOam: @ 0x08098CF4
	push {r4, r5, r6, lr}
	ldr r0, _08098D44 @ =gNonGameplayRam
	ldr r1, _08098D48 @ =0x00000215
	adds r2, r0, r1
	movs r1, #0
	strb r1, [r2]
	movs r4, #0
	adds r5, r0, #0
	adds r6, r2, #0
_08098D06:
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r2, r0, #2
	adds r0, r2, r5
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08098D34
	movs r0, #0x8f
	lsls r0, r0, #2
	adds r1, r5, r0
	adds r1, r2, r1
	subs r3, #0x10
	adds r0, r5, r3
	adds r0, r2, r0
	ldr r1, [r1]
	bl _call_via_r1
	ldrb r0, [r6]
	adds r0, #1
	strb r0, [r6]
_08098D34:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x13
	bls _08098D06
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098D44: .4byte gNonGameplayRam
_08098D48: .4byte 0x00000215

	thumb_func_start SpecialCutsceneDrawAllOam
SpecialCutsceneDrawAllOam: @ 0x08098D4C
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _08098D94 @ =gNonGameplayRam
	movs r0, #0x87
	lsls r0, r0, #2
	adds r6, r5, r0
_08098D58:
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r1, r0, #2
	adds r0, r1, r5
	movs r2, #0x8d
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	lsls r0, r0, #0x1f
	cmp r0, #0
	beq _08098D74
	adds r0, r1, r6
	bl SpecialCutsceneDrawOam
_08098D74:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x13
	bls _08098D58
	bl ResetFreeOam
	ldr r0, _08098D98 @ =gNextOamSlot
	movs r1, #0
	strb r1, [r0]
	ldr r0, _08098D9C @ =0x03001238
	strb r1, [r0]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098D94: .4byte gNonGameplayRam
_08098D98: .4byte gNextOamSlot
_08098D9C: .4byte 0x03001238

	thumb_func_start SpecialCutsceneDrawOam
SpecialCutsceneDrawOam: @ 0x08098DA0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x38
	mov sb, r0
	ldr r3, _08098E9C @ =gNextOamSlot
	ldrb r0, [r3]
	lsls r0, r0, #3
	ldr r2, _08098EA0 @ =gOamData
	adds r0, r0, r2
	mov ip, r0
	mov r0, sb
	ldrb r5, [r0, #0x11]
	lsls r1, r5, #3
	ldr r0, [r0, #0x1c]
	adds r4, r0, r1
	ldrb r0, [r4, #4]
	mov r1, sb
	ldrb r1, [r1, #0x12]
	cmp r0, r1
	bne _08098DDA
	adds r0, r5, #1
	movs r1, #0
	mov r2, sb
	strb r0, [r2, #0x11]
	strb r1, [r2, #0x12]
	adds r4, #8
_08098DDA:
	ldrb r1, [r4, #4]
	cmp r1, #0
	bne _08098DEA
	mov r3, sb
	ldrb r0, [r3, #0x11]
	lsls r0, r0, #3
	subs r4, r4, r0
	strb r1, [r3, #0x11]
_08098DEA:
	ldr r4, [r4]
	mov sl, r4
	ldrh r4, [r4]
	str r4, [sp, #0x20]
	movs r5, #2
	add sl, r5
	mov r0, sb
	ldrb r1, [r0, #0x18]
	lsls r0, r1, #0x1d
	lsrs r0, r0, #0x1e
	cmp r0, #0
	beq _08098E04
	b _08098F78
_08098E04:
	movs r1, #0
	str r1, [sp, #0x1c]
	cmp r1, r4
	blt _08098E10
	bl _0809975A
_08098E10:
	ldr r2, _08098EA4 @ =0x000001FF
	adds r7, r2, #0
	movs r3, #3
	mov r8, r3
_08098E18:
	mov r4, sl
	ldrh r6, [r4]
	movs r5, #2
	add sl, r5
	mov r0, sl
	ldrh r5, [r0]
	movs r1, #2
	add sl, r1
	mov r2, ip
	strh r6, [r2]
	add ip, r1
	mov r3, ip
	strh r5, [r3]
	add ip, r1
	mov r4, sl
	ldrh r0, [r4]
	mov r1, ip
	strh r0, [r1]
	movs r2, #2
	add sl, r2
	add ip, r2
	ldr r3, _08098E9C @ =gNextOamSlot
	ldrb r0, [r3]
	ldr r4, [sp, #0x1c]
	adds r3, r0, r4
	mov r1, sb
	ldrb r0, [r1, #0x18]
	lsls r0, r0, #0x19
	lsrs r1, r0, #0x1f
	cmp r1, #1
	bne _08098EAC
	lsls r4, r3, #3
	ldr r3, _08098EA0 @ =gOamData
	adds r2, r4, r3
	ldrb r3, [r2, #3]
	lsls r0, r3, #0x1b
	lsrs r0, r0, #0x1f
	eors r0, r1
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
	ldr r0, _08098EA8 @ =sCutsceneUnk_63a184
	adds r1, r1, r0
	ldrb r0, [r1]
	lsls r0, r0, #3
	adds r0, r5, r0
	mov r2, sb
	ldrh r1, [r2, #0xc]
	subs r0, r1, r0
	ands r0, r7
	str r0, [sp]
	ldrh r0, [r2, #0xe]
	adds r6, r6, r0
	movs r0, #0xff
	ands r6, r0
	str r6, [sp, #4]
	b _08098EC2
	.align 2, 0
_08098E9C: .4byte gNextOamSlot
_08098EA0: .4byte gOamData
_08098EA4: .4byte 0x000001FF
_08098EA8: .4byte sCutsceneUnk_63a184
_08098EAC:
	mov r4, sb
	ldrh r0, [r4, #0xe]
	adds r6, r6, r0
	movs r0, #0xff
	ands r6, r0
	str r6, [sp, #4]
	ldrh r0, [r4, #0xc]
	adds r5, r5, r0
	ands r5, r7
	str r5, [sp]
	lsls r4, r3, #3
_08098EC2:
	ldr r5, _08098F68 @ =gOamData
	adds r3, r4, r5
	mov r0, sp
	ldrb r0, [r0, #4]
	strb r0, [r3]
	ldr r1, [sp]
	ands r1, r7
	str r1, [sp]
	ldrh r1, [r3, #2]
	ldr r0, _08098F6C @ =0xFFFFFE00
	ands r0, r1
	ldr r2, [sp]
	orrs r0, r2
	strh r0, [r3, #2]
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	mov r5, r8
	ands r0, r5
	lsls r0, r0, #2
	ldrb r2, [r3, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #5]
	lsrs r2, r1, #4
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r3, #5]
	ldrh r2, [r3, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r4, _08098F70 @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _08098F74 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r3, #4]
	mov r5, sb
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	mov r1, r8
	ands r0, r1
	lsls r0, r0, #2
	ldrb r2, [r3, #1]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #1]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _08098F64
	b _08098E18
_08098F64:
	b _0809975A
	.align 2, 0
_08098F68: .4byte gOamData
_08098F6C: .4byte 0xFFFFFE00
_08098F70: .4byte 0x000003FF
_08098F74: .4byte 0xFFFFFC00
_08098F78:
	cmp r0, #1
	beq _08098F7E
	b _08099400
_08098F7E:
	mov r2, sb
	ldrh r0, [r2, #0xc]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r2, #0xe]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _08098FA0
	ldrh r3, [r2, #6]
	str r3, [sp, #0x14]
	b _08098FAC
_08098FA0:
	mov r4, sb
	ldrh r0, [r4, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08098FAC:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _08098FBA
	mov r5, sb
	ldrh r5, [r5, #6]
	str r5, [sp, #0x18]
	b _08098FC6
_08098FBA:
	mov r1, sb
	ldrh r0, [r1, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_08098FC6:
	movs r2, #0
	str r2, [sp, #0x28]
	movs r3, #0
	str r3, [sp, #0x1c]
	ldr r4, [sp, #0x14]
	lsls r4, r4, #0x10
	str r4, [sp, #0x34]
	ldr r5, [sp, #0x20]
	cmp r3, r5
	blt _08098FDC
	b _0809925C
_08098FDC:
	mov r0, sl
	ldrh r6, [r0]
	movs r1, #2
	add sl, r1
	mov r2, sl
	ldrh r5, [r2]
	add sl, r1
	mov r3, ip
	strh r6, [r3]
	add ip, r1
	mov r4, ip
	strh r5, [r4]
	add ip, r1
	mov r1, sl
	ldrh r0, [r1]
	mov r2, ip
	strh r0, [r2]
	movs r3, #2
	add sl, r3
	add ip, r3
	ldr r4, _08099098 @ =gNextOamSlot
	ldrb r0, [r4]
	ldr r1, [sp, #0x1c]
	adds r3, r0, r1
	lsls r0, r3, #3
	ldr r2, _0809909C @ =gOamData
	adds r0, r0, r2
	mov r8, r0
	ldrb r7, [r0, #3]
	lsrs r1, r7, #6
	ldrb r0, [r0, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r4, _080990A0 @ =sCutsceneUnk_63a184
	adds r0, r1, r4
	ldrb r0, [r0]
	lsls r0, r0, #2
	str r0, [sp, #8]
	ldr r0, _080990A4 @ =sCutsceneUnk_63a190
	adds r1, r1, r0
	ldrb r0, [r1]
	lsls r0, r0, #2
	str r0, [sp, #0xc]
	ldr r1, [sp, #4]
	adds r6, r6, r1
	movs r0, #0xff
	ands r6, r0
	ldr r2, [sp]
	adds r4, r5, r2
	ldr r5, _080990A8 @ =0x000001FF
	adds r0, r5, #0
	ands r4, r0
	subs r1, r4, r2
	ldr r0, [sp, #8]
	adds r1, r0, r1
	ldr r5, [sp, #4]
	subs r2, r6, r5
	ldr r0, [sp, #0xc]
	adds r2, r0, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r5, [sp, #0x34]
	asrs r0, r5, #0x10
	muls r0, r1, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r1, [sp, #0x18]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	muls r0, r2, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	lsls r0, r7, #0x1b
	cmp r0, #0
	bge _080990AC
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r7
	mov r5, r8
	strb r0, [r5, #3]
	movs r0, #1
	str r0, [sp, #0x28]
	movs r1, #1
	str r1, [sp, #0x24]
	b _080990B0
	.align 2, 0
_08099098: .4byte gNextOamSlot
_0809909C: .4byte gOamData
_080990A0: .4byte sCutsceneUnk_63a184
_080990A4: .4byte sCutsceneUnk_63a190
_080990A8: .4byte 0x000001FF
_080990AC:
	movs r5, #0
	str r5, [sp, #0x24]
_080990B0:
	lsls r0, r3, #3
	ldr r1, _080993E4 @ =gOamData
	adds r7, r0, r1
	ldrb r1, [r7, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _080990D0
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	ldr r3, [sp, #0x18]
	lsls r0, r3, #0x10
	rsbs r0, r0, #0
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_080990D0:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r4, [sp, #0x10]
	lsls r0, r4, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r6, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	ldr r5, [sp]
	subs r4, r4, r5
	ldr r0, [sp, #8]
	mov r8, r0
	add r4, r8
	ldr r1, [sp, #4]
	subs r3, r6, r1
	ldr r6, [sp, #0xc]
	adds r3, r6, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r2, sb
	ldrb r1, [r2, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =sSineTable
	adds r0, r0, r5
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _080993E8 @ =sSineTable
	adds r1, r1, r0
	movs r0, #0
	ldrsh r1, [r1, r0]
	adds r0, r3, #0
	muls r0, r1, r0
	subs r2, r2, r0
	lsls r2, r2, #8
	adds r0, r4, #0
	muls r0, r1, r0
	adds r1, r3, #0
	muls r1, r5, r1
	adds r0, r0, r1
	lsls r0, r0, #8
	asrs r2, r2, #0x10
	mov r1, r8
	subs r2, r2, r1
	asrs r0, r0, #0x10
	subs r0, r0, r6
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	ldr r3, [sp, #4]
	adds r0, r6, r3
	subs r0, #0x40
	strb r0, [r7]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r4, [sp]
	adds r2, r2, r4
	subs r2, #0x40
	ldr r4, _080993EC @ =0x000001FF
	ands r2, r4
	ldrh r0, [r7, #2]
	ldr r1, _080993F0 @ =0xFFFFFE00
	adds r3, r1, #0
	ands r3, r0
	orrs r3, r2
	strh r3, [r7, #2]
	ldr r5, [sp, #0x24]
	cmp r5, #1
	bne _08099180
	lsls r0, r3, #0x17
	lsrs r0, r0, #0x17
	subs r0, #1
	ands r0, r4
	ands r3, r1
	orrs r3, r0
	strh r3, [r7, #2]
_08099180:
	ldrb r1, [r7, #1]
	movs r0, #4
	rsbs r0, r0, #0
	ands r0, r1
	movs r3, #1
	orrs r0, r3
	strb r0, [r7, #1]
	ldr r1, _080993F4 @ =0x03001238
	ldrb r0, [r1]
	ldr r2, [sp, #0x24]
	adds r0, r0, r2
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080991A6
	ldrb r0, [r7, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r7, #3]
_080991A6:
	ldr r4, _080993F4 @ =0x03001238
	ldrb r0, [r4]
	ldr r5, [sp, #0x24]
	adds r0, r0, r5
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _080991BE
	ldrb r0, [r7, #3]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r7, #3]
_080991BE:
	ldr r0, _080993F4 @ =0x03001238
	ldrb r1, [r0]
	ldr r2, [sp, #0x24]
	adds r1, r1, r2
	movs r0, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r7, #3]
	subs r0, #0x16
	ands r0, r2
	orrs r0, r1
	strb r0, [r7, #3]
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	movs r5, #3
	ands r0, r5
	lsls r0, r0, #2
	ldrb r2, [r7, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #5]
	lsrs r2, r1, #4
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r7, #5]
	ldrh r2, [r7, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r4, _080993F8 @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _080993FC @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r7, #4]
	mov r5, sb
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #2
	ldrb r2, [r7, #1]
	subs r1, #0x10
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	ands r0, r3
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _0809925C
	b _08098FDC
_0809925C:
	ldr r1, _080993F4 @ =0x03001238
	ldrb r0, [r1]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r2, sb
	ldrb r0, [r2, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =sSineTable
	adds r0, r0, r3
	movs r5, #0
	ldrsh r4, [r0, r5]
	ldr r0, [sp, #0x34]
	asrs r0, r0, #0x10
	mov sl, r0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	ldr r1, _080993E4 @ =gOamData
	mov r8, r1
	lsls r1, r7, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r2, sb
	ldrb r0, [r2, #0x15]
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =sSineTable
	adds r0, r0, r3
	movs r5, #0
	ldrsh r4, [r0, r5]
	mov r0, sl
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	lsls r0, r0, #1
	ldr r2, _080993E8 @ =sSineTable
	adds r0, r0, r2
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	ldr r3, [sp, #0x18]
	lsls r0, r3, #0x10
	asrs r6, r0, #0x10
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =sSineTable
	adds r0, r0, r5
	movs r1, #0
	ldrsh r4, [r0, r1]
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	ldr r2, _080993F4 @ =0x03001238
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r3, [sp, #0x28]
	cmp r3, #1
	beq _08099328
	b _0809975A
_08099328:
	ldrb r0, [r2]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r1, #0
	ldrsh r5, [r0, r1]
	mov r2, sl
	rsbs r4, r2, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	lsls r1, r7, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r3, sb
	ldrb r0, [r3, #0x15]
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =sSineTable
	adds r0, r0, r5
	movs r1, #0
	ldrsh r5, [r0, r1]
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r2, sb
	ldrb r0, [r2, #0x15]
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =sSineTable
	adds r0, r0, r3
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =sSineTable
	adds r0, r0, r5
	movs r1, #0
	ldrsh r4, [r0, r1]
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	ldr r2, _080993F4 @ =0x03001238
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	b _0809975A
	.align 2, 0
_080993E4: .4byte gOamData
_080993E8: .4byte sSineTable
_080993EC: .4byte 0x000001FF
_080993F0: .4byte 0xFFFFFE00
_080993F4: .4byte 0x03001238
_080993F8: .4byte 0x000003FF
_080993FC: .4byte 0xFFFFFC00
_08099400:
	cmp r0, #3
	beq _08099406
	b _0809975A
_08099406:
	mov r3, sb
	ldrh r0, [r3, #0xc]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r3, #0xe]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _08099428
	ldrh r4, [r3, #6]
	str r4, [sp, #0x14]
	b _08099434
_08099428:
	mov r5, sb
	ldrh r0, [r5, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08099434:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _08099440
	mov r0, sb
	ldrh r0, [r0, #6]
	b _0809944A
_08099440:
	mov r1, sb
	ldrh r0, [r1, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
_0809944A:
	str r0, [sp, #0x18]
	movs r2, #0
	str r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	cmp r2, r3
	blt _08099458
	b _08099696
_08099458:
	mov r4, sl
	ldrh r6, [r4]
	movs r5, #2
	add sl, r5
	mov r0, sl
	ldrh r5, [r0]
	movs r1, #2
	add sl, r1
	mov r2, ip
	strh r6, [r2]
	add ip, r1
	mov r3, ip
	strh r5, [r3]
	add ip, r1
	mov r4, sl
	ldrh r0, [r4]
	mov r1, ip
	strh r0, [r1]
	movs r2, #2
	add sl, r2
	add ip, r2
	ldr r3, _0809977C @ =gNextOamSlot
	ldrb r0, [r3]
	ldr r4, [sp, #0x1c]
	adds r3, r0, r4
	lsls r0, r3, #3
	ldr r1, _08099780 @ =gOamData
	adds r7, r0, r1
	ldrb r2, [r7, #3]
	mov r8, r2
	mov r3, r8
	lsrs r1, r3, #6
	ldrb r0, [r7, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r4, _08099784 @ =sCutsceneUnk_63a184
	adds r0, r1, r4
	ldrb r2, [r0]
	ldr r0, _08099788 @ =sCutsceneUnk_63a190
	adds r1, r1, r0
	ldrb r3, [r1]
	ldr r1, [sp, #4]
	adds r6, r6, r1
	movs r0, #0xff
	ands r6, r0
	ldr r0, [sp]
	adds r4, r5, r0
	ldr r1, _0809978C @ =0x000001FF
	adds r0, r1, #0
	ands r4, r0
	ldr r5, [sp]
	subs r1, r4, r5
	lsls r2, r2, #2
	str r2, [sp, #0x2c]
	adds r1, r2, r1
	ldr r0, [sp, #4]
	subs r2, r6, r0
	lsls r3, r3, #2
	str r3, [sp, #0x30]
	adds r2, r3, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0x14]
	lsls r0, r3, #0x10
	asrs r3, r0, #0x10
	adds r0, r1, #0
	muls r0, r3, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r5, [sp, #0x18]
	lsls r0, r5, #0x10
	asrs r5, r0, #0x10
	adds r0, r2, #0
	muls r0, r5, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	mov r1, r8
	lsls r0, r1, #0x1b
	cmp r0, #0
	bge _08099518
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	rsbs r0, r3, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08099518:
	ldrb r1, [r7, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _08099530
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	rsbs r0, r5, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_08099530:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0x10]
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r6, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	ldr r5, [sp]
	subs r4, r4, r5
	ldr r0, [sp, #0x2c]
	adds r4, r0, r4
	ldr r1, [sp, #4]
	subs r3, r6, r1
	ldr r2, [sp, #0x30]
	adds r3, r2, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r5, sb
	ldrb r1, [r5, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _08099790 @ =sSineTable
	adds r0, r0, r2
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _08099790 @ =sSineTable
	adds r1, r1, r0
	movs r0, #0
	ldrsh r1, [r1, r0]
	adds r0, r3, #0
	muls r0, r1, r0
	subs r2, r2, r0
	lsls r2, r2, #8
	adds r0, r4, #0
	muls r0, r1, r0
	adds r1, r3, #0
	muls r1, r5, r1
	adds r0, r0, r1
	lsls r0, r0, #8
	ldr r3, [sp, #0x2c]
	lsls r1, r3, #1
	asrs r2, r2, #0x10
	subs r2, r2, r1
	ldr r4, [sp, #0x30]
	lsls r1, r4, #1
	asrs r0, r0, #0x10
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	ldr r5, [sp, #4]
	adds r0, r6, r5
	subs r0, #0x40
	strb r0, [r7]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r0, [sp]
	adds r2, r2, r0
	subs r2, #0x40
	ldr r0, _0809978C @ =0x000001FF
	ands r2, r0
	ldrh r1, [r7, #2]
	ldr r0, _08099794 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r7, #2]
	ldrb r0, [r7, #1]
	movs r3, #3
	orrs r0, r3
	strb r0, [r7, #1]
	ldr r2, _08099798 @ =0x03001238
	ldrb r1, [r2]
	movs r2, #0x10
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080995EC
	ldrb r0, [r7, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r7, #3]
_080995EC:
	ldr r4, _08099798 @ =0x03001238
	ldrb r1, [r4]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080995FE
	ldrb r0, [r7, #3]
	orrs r0, r2
	strb r0, [r7, #3]
_080995FE:
	ldr r5, _08099798 @ =0x03001238
	ldrb r0, [r5]
	movs r1, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r7, #3]
	movs r0, #0xf
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r7, #3]
	mov r1, sb
	ldrb r0, [r1, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	ands r0, r3
	lsls r0, r0, #2
	ldrb r2, [r7, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #5]
	lsrs r2, r1, #4
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r7, #5]
	ldrh r2, [r7, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r5, _0809979C @ =0x000003FF
	adds r0, r5, #0
	ands r1, r0
	ldr r0, _080997A0 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r7, #4]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	ands r0, r3
	lsls r0, r0, #2
	ldrb r2, [r7, #1]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _08099696
	b _08099458
_08099696:
	ldr r1, _08099798 @ =0x03001238
	ldrb r0, [r1]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r2, sb
	ldrb r0, [r2, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r3, _08099790 @ =sSineTable
	adds r0, r0, r3
	movs r4, #0
	ldrsh r5, [r0, r4]
	ldr r0, [sp, #0x14]
	lsls r4, r0, #0x10
	asrs r4, r4, #0x10
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	ldr r6, _08099780 @ =gOamData
	lsls r1, r7, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	lsls r0, r0, #1
	ldr r2, _08099790 @ =sSineTable
	adds r0, r0, r2
	movs r3, #0
	ldrsh r5, [r0, r3]
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	lsls r0, r0, #1
	ldr r5, _08099790 @ =sSineTable
	adds r0, r0, r5
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	ldr r0, [sp, #0x18]
	lsls r5, r0, #0x10
	asrs r5, r5, #0x10
	adds r0, r5, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _08099790 @ =sSineTable
	adds r0, r0, r2
	movs r3, #0
	ldrsh r4, [r0, r3]
	adds r0, r5, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	ldr r4, _08099798 @ =0x03001238
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
_0809975A:
	ldr r0, _0809977C @ =gNextOamSlot
	ldrb r1, [r0]
	ldr r5, [sp, #0x20]
	adds r1, r1, r5
	strb r1, [r0]
	mov r1, sb
	ldrb r0, [r1, #0x12]
	adds r0, #1
	strb r0, [r1, #0x12]
	add sp, #0x38
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809977C: .4byte gNextOamSlot
_08099780: .4byte gOamData
_08099784: .4byte sCutsceneUnk_63a184
_08099788: .4byte sCutsceneUnk_63a190
_0809978C: .4byte 0x000001FF
_08099790: .4byte sSineTable
_08099794: .4byte 0xFFFFFE00
_08099798: .4byte 0x03001238
_0809979C: .4byte 0x000003FF
_080997A0: .4byte 0xFFFFFC00

	thumb_func_start NewFileIntroInit
NewFileIntroInit: @ 0x080997A4
	push {r4, lr}
	sub sp, #4
	ldr r3, _08099864 @ =0x04000208
	movs r4, #0
	strh r4, [r3]
	ldr r2, _08099868 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _0809986C @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08099870 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08099874 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08099878 @ =unk_99940
	bl CallbackSetVBlank
	ldr r1, _0809987C @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08099880 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08099884 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08099888 @ =gNextOamSlot
	strb r4, [r0]
	bl ResetFreeOam
	movs r2, #0
	str r2, [sp]
	ldr r1, _0809988C @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _08099890 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08099894 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08099898 @ =0x00007FFF
	str r0, [sp]
	mov r0, sp
	str r0, [r1]
	movs r3, #0xa0
	lsls r3, r3, #0x13
	str r3, [r1, #4]
	ldr r0, _0809989C @ =0x85000080
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r2, [r3]
	str r2, [sp]
	mov r0, sp
	str r0, [r1]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _080998A0 @ =0x85004000
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _080998A4 @ =0x0400000E
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	adds r0, #8
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	subs r0, #0x1e
	strh r2, [r0]
	ldr r0, _080998A8 @ =NewFileIntroVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08099864: .4byte 0x04000208
_08099868: .4byte 0x04000004
_0809986C: .4byte 0x0000FFEF
_08099870: .4byte 0x04000200
_08099874: .4byte 0x0000FFFD
_08099878: .4byte unk_99940
_0809987C: .4byte 0x04000050
_08099880: .4byte gWrittenToBldy
_08099884: .4byte 0x04000054
_08099888: .4byte gNextOamSlot
_0809988C: .4byte 0x040000D4
_08099890: .4byte gNonGameplayRam
_08099894: .4byte 0x85000150
_08099898: .4byte 0x00007FFF
_0809989C: .4byte 0x85000080
_080998A0: .4byte 0x85004000
_080998A4: .4byte 0x0400000E
_080998A8: .4byte NewFileIntroVblank

	thumb_func_start SpecialCutsceneGetRandomNumber
SpecialCutsceneGetRandomNumber: @ 0x080998AC
	push {r4, lr}
	ldr r3, _080998E0 @ =0x03005404
	ldrh r1, [r3]
	lsls r0, r1, #2
	adds r1, r1, r0
	ldr r2, _080998E4 @ =gFrameCounter8Bit
	ldr r4, _080998E8 @ =0x00003573
	adds r0, r4, #0
	ldrb r2, [r2]
	adds r0, r0, r2
	adds r1, r1, r0
	strh r1, [r3]
	ldr r2, _080998EC @ =sRandomNumberTable
	ldr r0, _080998F0 @ =gFrameCounter16Bit
	ldrh r1, [r0]
	movs r0, #0x1f
	ands r0, r1
	adds r0, r0, r2
	ldrb r0, [r0]
	ldrb r1, [r3, #1]
	adds r0, r0, r1
	strb r0, [r3, #1]
	ldrb r0, [r3, #1]
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080998E0: .4byte 0x03005404
_080998E4: .4byte gFrameCounter8Bit
_080998E8: .4byte 0x00003573
_080998EC: .4byte sRandomNumberTable
_080998F0: .4byte gFrameCounter16Bit

	thumb_func_start NewFileIntroVblank
NewFileIntroVblank: @ 0x080998F4
	ldr r1, _08099920 @ =0x040000D4
	ldr r0, _08099924 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08099928 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _0809992C @ =0x04000052
	ldr r0, _08099930 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08099934 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08099938 @ =0x04000054
	ldr r0, _0809993C @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08099920: .4byte 0x040000D4
_08099924: .4byte gOamData
_08099928: .4byte 0x84000100
_0809992C: .4byte 0x04000052
_08099930: .4byte gWrittenToBldalpha_Evb
_08099934: .4byte gWrittenToBldalpha_Eva
_08099938: .4byte 0x04000054
_0809993C: .4byte gWrittenToBldy

	thumb_func_start unk_99940
unk_99940: @ 0x08099940
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneHandler
CutsceneHandler: @ 0x0809994C
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08099964 @ =gSubGameMode1
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #1
	beq _0809997A
	cmp r0, #1
	bgt _08099968
	cmp r0, #0
	beq _08099972
	b _080999BA
	.align 2, 0
_08099964: .4byte gSubGameMode1
_08099968:
	cmp r0, #2
	beq _08099992
	cmp r0, #3
	beq _080999A0
	b _080999BA
_08099972:
	bl CutsceneInit
	movs r0, #2
	b _080999B8
_0809997A:
	ldr r1, _08099988 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _0809998C
	subs r0, #1
	strh r0, [r1]
	b _080999BA
	.align 2, 0
_08099988: .4byte gWrittenToBldy
_0809998C:
	ldrh r0, [r4]
	adds r0, #1
	b _080999B8
_08099992:
	bl CutsceneProcess
	cmp r0, #0
	beq _080999BA
	ldrh r0, [r4]
	adds r0, #1
	b _080999B8
_080999A0:
	ldr r1, _080999B0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080999B4
	adds r0, #1
	strh r0, [r1]
	b _080999BA
	.align 2, 0
_080999B0: .4byte gWrittenToBldy
_080999B4:
	movs r5, #1
	movs r0, #0
_080999B8:
	strh r0, [r4]
_080999BA:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start CutsceneInit
CutsceneInit: @ 0x080999C4
	push {r4, r5, lr}
	sub sp, #4
	ldr r3, _08099A90 @ =0x04000208
	movs r5, #0
	strh r5, [r3]
	ldr r2, _08099A94 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08099A98 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08099A9C @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08099AA0 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08099AA4 @ =unk_99af8
	bl CallbackSetVBlank
	ldr r1, _08099AA8 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08099AAC @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08099AB0 @ =0x04000054
	strh r1, [r0]
	ldr r4, _08099AB4 @ =0x040000D4
	ldr r0, _08099AB8 @ =0x06010000
	str r0, [r4]
	ldr r0, _08099ABC @ =0x0201C000
	str r0, [r4, #4]
	ldr r0, _08099AC0 @ =0x84002000
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08099AC4 @ =gNextOamSlot
	strb r5, [r0]
	bl ResetFreeOam
	movs r1, #0
	str r1, [sp]
	mov r0, sp
	str r0, [r4]
	ldr r0, _08099AC8 @ =gNonGameplayRam
	str r0, [r4, #4]
	ldr r0, _08099ACC @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08099AD0 @ =0x00007FFF
	str r0, [sp]
	mov r0, sp
	str r0, [r4]
	movs r2, #0xa0
	lsls r2, r2, #0x13
	str r2, [r4, #4]
	ldr r0, _08099AD4 @ =0x85000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	strh r1, [r2]
	str r1, [sp]
	mov r0, sp
	str r0, [r4]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _08099AD8 @ =0x85004000
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08099ADC @ =0x0400000E
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
	subs r0, #0x1e
	strh r1, [r0]
	ldr r0, _08099AE0 @ =CutsceneVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08099A90: .4byte 0x04000208
_08099A94: .4byte 0x04000004
_08099A98: .4byte 0x0000FFEF
_08099A9C: .4byte 0x04000200
_08099AA0: .4byte 0x0000FFFD
_08099AA4: .4byte unk_99af8
_08099AA8: .4byte 0x04000050
_08099AAC: .4byte gWrittenToBldy
_08099AB0: .4byte 0x04000054
_08099AB4: .4byte 0x040000D4
_08099AB8: .4byte 0x06010000
_08099ABC: .4byte 0x0201C000
_08099AC0: .4byte 0x84002000
_08099AC4: .4byte gNextOamSlot
_08099AC8: .4byte gNonGameplayRam
_08099ACC: .4byte 0x85000150
_08099AD0: .4byte 0x00007FFF
_08099AD4: .4byte 0x85000080
_08099AD8: .4byte 0x85004000
_08099ADC: .4byte 0x0400000E
_08099AE0: .4byte CutsceneVblank

	thumb_func_start CutsceneVblank
CutsceneVblank: @ 0x08099AE4
	ldr r0, _08099AF0 @ =0x04000054
	ldr r1, _08099AF4 @ =gWrittenToBldy
	ldrh r1, [r1]
	strh r1, [r0]
	bx lr
	.align 2, 0
_08099AF0: .4byte 0x04000054
_08099AF4: .4byte gWrittenToBldy

	thumb_func_start unk_99af8
unk_99af8: @ 0x08099AF8
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneProcess
CutsceneProcess: @ 0x08099B04
	push {r4, lr}
	movs r4, #0
	ldr r0, _08099B1C @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	cmp r0, #0xb
	bhi _08099BA0
	lsls r0, r0, #2
	ldr r1, _08099B20 @ =_08099B24
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08099B1C: .4byte gCurrentCutscene
_08099B20: .4byte _08099B24
_08099B24: @ jump table
	.4byte _08099B54 @ case 0
	.4byte _08099B5C @ case 1
	.4byte _08099B64 @ case 2
	.4byte _08099B6C @ case 3
	.4byte _08099B74 @ case 4
	.4byte _08099B7C @ case 5
	.4byte _08099B84 @ case 6
	.4byte _08099B54 @ case 7
	.4byte _08099B8C @ case 8
	.4byte _08099B92 @ case 9
	.4byte _08099B92 @ case 10
	.4byte _08099B98 @ case 11
_08099B54:
	movs r0, #0
	bl CutsceneInternalMonologue
	b _08099B9C
_08099B5C:
	movs r0, #0
	bl CutsceneElevatorMonologue
	b _08099B9C
_08099B64:
	movs r0, #0
	bl CutsceneElevatorMonologue
	b _08099B9C
_08099B6C:
	movs r0, #0
	bl CutsceneElevatorMonologue
	b _08099B9C
_08099B74:
	movs r0, #1
	bl CutsceneElevatorMonologue
	b _08099B9C
_08099B7C:
	movs r0, #0
	bl CutsceneElevatorMonologue
	b _08099B9C
_08099B84:
	movs r0, #0
	bl CutsceneFederationMonologue
	b _08099B9C
_08099B8C:
	bl CutsceneSecretConversation
	b _08099B9C
_08099B92:
	bl CutsceneRestrictedLabDetaching
	b _08099B9C
_08099B98:
	bl CutsceneBslExploding
_08099B9C:
	cmp r0, #0
	beq _08099BA2
_08099BA0:
	movs r4, #1
_08099BA2:
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start CutsceneElevatorMonologue
CutsceneElevatorMonologue: @ 0x08099BAC
	push {r4, r5, lr}
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	movs r5, #0
	ldr r4, _08099BC8 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _08099BE2
	cmp r0, #1
	bgt _08099BCC
	cmp r0, #0
	beq _08099BD6
	b _08099C2A
	.align 2, 0
_08099BC8: .4byte gNonGameplayRam
_08099BCC:
	cmp r0, #2
	beq _08099BFC
	cmp r0, #3
	beq _08099C1C
	b _08099C2A
_08099BD6:
	movs r0, #1
	strh r0, [r4, #8]
	adds r0, r1, #0
	bl CutsceneElevatorMonologueInit
	b _08099C2A
_08099BE2:
	bl CutsceneMonologueFadeIn
	ldr r0, _08099BF8 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _08099C2A
	ldrh r0, [r4, #8]
	adds r0, #1
	strh r0, [r4, #8]
	b _08099C2A
	.align 2, 0
_08099BF8: .4byte gWrittenToBldy
_08099BFC:
	bl CutsceneElevatorMonologueProcess
	cmp r0, #0
	beq _08099C2A
	movs r0, #3
	strh r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xa8
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x50
	movs r0, #0xff
	strh r0, [r1]
	b _08099C2A
_08099C1C:
	bl CutsceneMonologueFadeOut
	ldr r0, _08099C34 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0x10
	bne _08099C2A
	movs r5, #1
_08099C2A:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08099C34: .4byte gWrittenToBldy

	thumb_func_start CutsceneElevatorMonologueInit
CutsceneElevatorMonologueInit: @ 0x08099C38
	push {r4, r5, r6, lr}
	mov r6, sb
	mov r5, r8
	push {r5, r6}
	mov r8, r0
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov r8, r0
	ldr r3, _08099D84 @ =0x04000208
	movs r4, #0
	strh r4, [r3]
	ldr r2, _08099D88 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08099D8C @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08099D90 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08099D94 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08099D98 @ =unk_9a31c
	bl CallbackSetVBlank
	movs r1, #0x80
	lsls r1, r1, #0x13
	mov sb, r1
	strh r4, [r1]
	ldr r1, _08099D9C @ =sCutsceneUnk_79c514
	ldr r6, _08099DA0 @ =gCurrentCutscene
	ldrb r0, [r6]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r1, _08099DA4 @ =0x06012000
	bl LZ77UncompVram
	ldr r0, _08099DA8 @ =sCutsceneUnk_65fb5c
	ldr r1, _08099DAC @ =0x06017C00
	bl LZ77UncompVram
	ldr r4, _08099DB0 @ =0x040000D4
	ldr r0, _08099DB4 @ =sCutsceneUnk_6638a0
	str r0, [r4]
	ldr r0, _08099DB8 @ =0x050003E0
	str r0, [r4, #4]
	ldr r0, _08099DBC @ =0x84000008
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r1, _08099DC0 @ =sCutsceneUnk_79c4cc
	ldrb r0, [r6]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r4]
	ldr r0, _08099DC4 @ =0x05000200
	str r0, [r4, #4]
	ldr r0, _08099DC8 @ =0x84000030
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r1, _08099DCC @ =sCutsceneUnk_79c4f0
	ldrb r0, [r6]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r1, _08099DD0 @ =sCutsceneUnk_79c538
	ldrb r0, [r6]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r1, _08099DD4 @ =0x0600D000
	bl LZ77UncompVram
	ldr r0, _08099DD8 @ =sIntroTilemap_662804
	movs r5, #0x80
	lsls r5, r5, #0x12
	adds r1, r5, #0
	bl LZ77UncompWram
	ldr r0, _08099DDC @ =sCutsceneUnk_663598
	ldr r1, _08099DE0 @ =0x0600D800
	bl LZ77UncompVram
	str r5, [r4]
	ldr r0, _08099DE4 @ =0x0600C800
	str r0, [r4, #4]
	ldr r0, _08099DE8 @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08099DEC @ =sCutsceneUnk_6636a0
	str r0, [r4]
	movs r2, #0xa0
	lsls r2, r2, #0x13
	str r2, [r4, #4]
	ldr r0, _08099DF0 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r1, _08099DF4 @ =sCutsceneUnk_79c4a8
	ldrb r0, [r6]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r4]
	str r2, [r4, #4]
	ldr r0, _08099DF8 @ =0x84000058
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r1, _08099DFC @ =0x04000012
	movs r0, #4
	strh r0, [r1]
	subs r1, #0xa
	ldr r2, _08099E00 @ =0x00001908
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08099E04 @ =0x00001B01
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	subs r2, #0xfe
	adds r0, r2, #0
	strh r0, [r1]
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r1, #0
	mov r2, sb
	strh r0, [r2]
	ldr r1, _08099E08 @ =gWrittenToBldy
	ldrh r0, [r1]
	subs r0, #1
	strh r0, [r1]
	movs r0, #1
	movs r1, #0xc
	movs r2, #0x10
	bl CutsceneElevatorMonologueSetupOam
	movs r0, #2
	movs r1, #0x78
	movs r2, #0x78
	bl CutsceneElevatorMonologueSetupOam
	movs r0, #3
	movs r1, #0x78
	movs r2, #0x78
	bl CutsceneElevatorMonologueSetupOam
	mov r0, r8
	cmp r0, #0
	bne _08099E0C
	movs r0, #4
	movs r1, #0x78
	movs r2, #0x68
	bl CutsceneElevatorMonologueSetupOam
	b _08099E16
	.align 2, 0
_08099D84: .4byte 0x04000208
_08099D88: .4byte 0x04000004
_08099D8C: .4byte 0x0000FFEF
_08099D90: .4byte 0x04000200
_08099D94: .4byte 0x0000FFFD
_08099D98: .4byte unk_9a31c
_08099D9C: .4byte sCutsceneUnk_79c514
_08099DA0: .4byte gCurrentCutscene
_08099DA4: .4byte 0x06012000
_08099DA8: .4byte sCutsceneUnk_65fb5c
_08099DAC: .4byte 0x06017C00
_08099DB0: .4byte 0x040000D4
_08099DB4: .4byte sCutsceneUnk_6638a0
_08099DB8: .4byte 0x050003E0
_08099DBC: .4byte 0x84000008
_08099DC0: .4byte sCutsceneUnk_79c4cc
_08099DC4: .4byte 0x05000200
_08099DC8: .4byte 0x84000030
_08099DCC: .4byte sCutsceneUnk_79c4f0
_08099DD0: .4byte sCutsceneUnk_79c538
_08099DD4: .4byte 0x0600D000
_08099DD8: .4byte sIntroTilemap_662804
_08099DDC: .4byte sCutsceneUnk_663598
_08099DE0: .4byte 0x0600D800
_08099DE4: .4byte 0x0600C800
_08099DE8: .4byte 0x84000200
_08099DEC: .4byte sCutsceneUnk_6636a0
_08099DF0: .4byte 0x84000080
_08099DF4: .4byte sCutsceneUnk_79c4a8
_08099DF8: .4byte 0x84000058
_08099DFC: .4byte 0x04000012
_08099E00: .4byte 0x00001908
_08099E04: .4byte 0x00001B01
_08099E08: .4byte gWrittenToBldy
_08099E0C:
	movs r0, #5
	movs r1, #0x78
	movs r2, #0x68
	bl CutsceneElevatorMonologueSetupOam
_08099E16:
	ldr r2, _08099E50 @ =gNonGameplayRam
	ldr r0, _08099E54 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	strh r0, [r2, #0xa]
	ldr r1, _08099E58 @ =sMonologueTextPointers
	ldr r0, _08099E5C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrh r1, [r2, #0xa]
	ldr r0, [r0]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r2, #0xc]
	bl CutsceneMonologueDrawAllOam
	ldr r0, _08099E60 @ =CutsceneElevatorMonologueVblank
	bl CallbackSetVBlank
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08099E50: .4byte gNonGameplayRam
_08099E54: .4byte gCurrentCutscene
_08099E58: .4byte sMonologueTextPointers
_08099E5C: .4byte 0x03000011
_08099E60: .4byte CutsceneElevatorMonologueVblank

	thumb_func_start CutsceneElevatorMonologueProcess
CutsceneElevatorMonologueProcess: @ 0x08099E64
	push {r4, lr}
	bl CutsceneMonologueProcessSpecialTextCharacters
	adds r4, r0, #0
	ldr r1, _08099E7C @ =gNonGameplayRam
	ldrb r0, [r1, #0x17]
	cmp r0, #0
	beq _08099E80
	cmp r0, #1
	beq _08099E86
	b _08099E8E
	.align 2, 0
_08099E7C: .4byte gNonGameplayRam
_08099E80:
	movs r0, #0x64
	strb r0, [r1, #0x17]
	b _08099E8E
_08099E86:
	movs r0, #0x64
	strb r0, [r1, #0x17]
	bl CutsceneMonologueProcessText
_08099E8E:
	bl CutsceneMonologueProcessOam
	bl CutsceneMonologueDrawAllOam
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start CutsceneElevatorMonologueSetupOam
CutsceneElevatorMonologueSetupOam: @ 0x08099EA0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r7, r1, #0x10
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov r8, r2
	movs r6, #0
	ldr r1, _08099EEC @ =gNonGameplayRam
	movs r2, #0x86
	lsls r2, r2, #2
	adds r0, r1, r2
	ldrb r0, [r0]
	cmp r0, #0
	beq _08099EE2
	adds r3, r1, #0
	adds r1, r2, #0
_08099EC8:
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #4
	bhi _08099EE6
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #3
	adds r0, r0, r3
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	bne _08099EC8
_08099EE2:
	cmp r6, #4
	bls _08099EF0
_08099EE6:
	movs r0, #5
	b _0809A06C
	.align 2, 0
_08099EEC: .4byte gNonGameplayRam
_08099EF0:
	adds r0, r6, #0
	bl CutsceneMonologueResetOam
	ldr r3, _08099F50 @ =gNonGameplayRam
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r5, r0, #3
	adds r2, r5, r3
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r2, r1
	strh r7, [r0]
	adds r1, #2
	adds r0, r2, r1
	mov r1, r8
	strh r1, [r0]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r4, [r0]
	ldr r0, _08099F54 @ =0x00000219
	adds r1, r2, r0
	movs r0, #1
	strb r0, [r1]
	cmp r4, #1
	bne _08099F68
	ldr r0, _08099F58 @ =0x00000221
	adds r1, r2, r0
	movs r0, #0xf
	strb r0, [r1]
	ldr r0, _08099F5C @ =0x00000222
	adds r1, r2, r0
	movs r0, #0xf8
	lsls r0, r0, #2
	strh r0, [r1]
	movs r1, #0x89
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _08099F60 @ =sCutsceneUnk_663e5c
	str r1, [r0]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _08099F64 @ =CutsceneMonologueProcessCursor
	b _0809A068
	.align 2, 0
_08099F50: .4byte gNonGameplayRam
_08099F54: .4byte 0x00000219
_08099F58: .4byte 0x00000221
_08099F5C: .4byte 0x00000222
_08099F60: .4byte sCutsceneUnk_663e5c
_08099F64: .4byte CutsceneMonologueProcessCursor
_08099F68:
	cmp r4, #2
	bne _08099FA8
	ldr r0, _08099F98 @ =0x0000021F
	adds r1, r2, r0
	movs r0, #3
	strb r0, [r1]
	movs r0, #0x89
	lsls r0, r0, #2
	adds r1, r3, r0
	adds r1, r5, r1
	ldr r2, _08099F9C @ =sCutsceneUnk_79c55c
	ldr r0, _08099FA0 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #3
	adds r0, r0, r2
	ldr r0, [r0]
	str r0, [r1]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _08099FA4 @ =unk_9d09c
	b _0809A068
	.align 2, 0
_08099F98: .4byte 0x0000021F
_08099F9C: .4byte sCutsceneUnk_79c55c
_08099FA0: .4byte gCurrentCutscene
_08099FA4: .4byte unk_9d09c
_08099FA8:
	cmp r4, #3
	bne _08099FF4
	ldr r0, _08099FE0 @ =0x0000021E
	adds r1, r2, r0
	movs r0, #2
	strb r0, [r1]
	ldr r1, _08099FE4 @ =0x0000021F
	adds r0, r2, r1
	strb r4, [r0]
	movs r0, #0x89
	lsls r0, r0, #2
	adds r1, r3, r0
	adds r1, r5, r1
	ldr r2, _08099FE8 @ =sCutsceneUnk_79c55c
	ldr r0, _08099FEC @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #3
	adds r0, r0, r2
	ldr r0, [r0]
	str r0, [r1]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _08099FF0 @ =unk_9d09c
	b _0809A068
	.align 2, 0
_08099FE0: .4byte 0x0000021E
_08099FE4: .4byte 0x0000021F
_08099FE8: .4byte sCutsceneUnk_79c55c
_08099FEC: .4byte gCurrentCutscene
_08099FF0: .4byte unk_9d09c
_08099FF4:
	cmp r4, #4
	bne _0809A038
	ldr r0, _0809A028 @ =0x0000021F
	adds r1, r2, r0
	movs r0, #3
	strb r0, [r1]
	movs r1, #0x89
	lsls r1, r1, #2
	adds r2, r3, r1
	adds r2, r5, r2
	ldr r1, _0809A02C @ =sCutsceneUnk_79c55c
	ldr r0, _0809A030 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #3
	adds r1, #4
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r2]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _0809A034 @ =CutsceneProcessElevatorScrolling
	b _0809A068
	.align 2, 0
_0809A028: .4byte 0x0000021F
_0809A02C: .4byte sCutsceneUnk_79c55c
_0809A030: .4byte gCurrentCutscene
_0809A034: .4byte CutsceneProcessElevatorScrolling
_0809A038:
	cmp r4, #5
	bne _0809A06A
	ldr r0, _0809A078 @ =0x0000021F
	adds r1, r2, r0
	movs r0, #3
	strb r0, [r1]
	movs r1, #0x89
	lsls r1, r1, #2
	adds r2, r3, r1
	adds r2, r5, r2
	ldr r1, _0809A07C @ =sCutsceneUnk_79c55c
	ldr r0, _0809A080 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	lsls r0, r0, #3
	adds r1, #4
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r2]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r3, r1
	adds r0, r5, r0
	ldr r1, _0809A084 @ =unk_9a1a8
_0809A068:
	str r1, [r0]
_0809A06A:
	adds r0, r6, #0
_0809A06C:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809A078: .4byte 0x0000021F
_0809A07C: .4byte sCutsceneUnk_79c55c
_0809A080: .4byte gCurrentCutscene
_0809A084: .4byte unk_9a1a8

	thumb_func_start CutsceneProcessElevatorScrolling
CutsceneProcessElevatorScrolling: @ 0x0809A088
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #2]
	adds r0, #2
	movs r5, #0
	strh r0, [r4, #2]
	ldr r3, _0809A0F8 @ =0x0400001A
	ldr r2, _0809A0FC @ =gNonGameplayRam
	ldrh r0, [r2, #0x12]
	subs r0, #1
	strh r0, [r2, #0x12]
	ldr r6, _0809A100 @ =0x0000FFFF
	adds r1, r6, #0
	ands r0, r1
	strh r0, [r3]
	ldrb r3, [r4, #9]
	adds r6, r2, #0
	cmp r3, #0
	bne _0809A124
	ldr r0, _0809A104 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _0809A19A
	ldr r0, _0809A108 @ =gWrittenToBldalpha_Eva
	strh r3, [r0]
	ldr r0, _0809A10C @ =gWrittenToBldalpha_Evb
	movs r2, #0x10
	strh r2, [r0]
	ldr r0, _0809A110 @ =0x04000048
	strh r3, [r0]
	ldr r1, _0809A114 @ =0x0400004A
	ldr r5, _0809A118 @ =0x0000331D
	adds r0, r5, #0
	strh r0, [r1]
	ldr r0, _0809A11C @ =0x04000016
	strh r3, [r6, #0x14]
	strh r3, [r0]
	adds r0, #0x3c
	lsls r2, r2, #8
	strh r2, [r0]
	adds r1, #6
	ldr r6, _0809A120 @ =0x00001042
	adds r0, r6, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r3, #0x82
	lsls r3, r3, #8
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #1
	strb r0, [r4, #9]
	b _0809A19A
	.align 2, 0
_0809A0F8: .4byte 0x0400001A
_0809A0FC: .4byte gNonGameplayRam
_0809A100: .4byte 0x0000FFFF
_0809A104: .4byte gWrittenToBldy
_0809A108: .4byte gWrittenToBldalpha_Eva
_0809A10C: .4byte gWrittenToBldalpha_Evb
_0809A110: .4byte 0x04000048
_0809A114: .4byte 0x0400004A
_0809A118: .4byte 0x0000331D
_0809A11C: .4byte 0x04000016
_0809A120: .4byte 0x00001042
_0809A124:
	cmp r3, #1
	bne _0809A164
	ldr r2, _0809A138 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #0xa
	bne _0809A13C
	movs r0, #2
	strb r0, [r4, #9]
	strb r5, [r4, #8]
	b _0809A14E
	.align 2, 0
_0809A138: .4byte gWrittenToBldalpha_Eva
_0809A13C:
	ldrb r0, [r4, #8]
	cmp r0, #3
	bls _0809A14A
	strb r5, [r4, #8]
	adds r0, r1, #1
	strh r0, [r2]
	b _0809A14E
_0809A14A:
	adds r0, #1
	strb r0, [r4, #8]
_0809A14E:
	ldr r0, _0809A15C @ =0x04000016
	ldrh r1, [r6, #0x14]
	subs r1, #3
	strh r1, [r6, #0x14]
	ldr r5, _0809A160 @ =0x0000FFFF
	adds r2, r5, #0
	b _0809A196
	.align 2, 0
_0809A15C: .4byte 0x04000016
_0809A160: .4byte 0x0000FFFF
_0809A164:
	ldr r2, _0809A174 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #4
	bne _0809A178
	movs r0, #1
	strb r0, [r4, #9]
	strb r5, [r4, #8]
	b _0809A18A
	.align 2, 0
_0809A174: .4byte gWrittenToBldalpha_Eva
_0809A178:
	ldrb r0, [r4, #8]
	cmp r0, #3
	bls _0809A186
	strb r5, [r4, #8]
	subs r0, r1, #1
	strh r0, [r2]
	b _0809A18A
_0809A186:
	adds r0, #1
	strb r0, [r4, #8]
_0809A18A:
	ldr r0, _0809A1A0 @ =0x04000016
	ldrh r1, [r6, #0x14]
	subs r1, #3
	strh r1, [r6, #0x14]
	ldr r6, _0809A1A4 @ =0x0000FFFF
	adds r2, r6, #0
_0809A196:
	ands r1, r2
	strh r1, [r0]
_0809A19A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A1A0: .4byte 0x04000016
_0809A1A4: .4byte 0x0000FFFF

	thumb_func_start unk_9a1a8
unk_9a1a8: @ 0x0809A1A8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #2]
	subs r0, #2
	movs r5, #0
	strh r0, [r4, #2]
	ldr r3, _0809A218 @ =0x0400001A
	ldr r2, _0809A21C @ =gNonGameplayRam
	ldrh r0, [r2, #0x12]
	adds r0, #1
	strh r0, [r2, #0x12]
	ldr r6, _0809A220 @ =0x0000FFFF
	adds r1, r6, #0
	ands r0, r1
	strh r0, [r3]
	ldrb r3, [r4, #9]
	adds r6, r2, #0
	cmp r3, #0
	bne _0809A244
	ldr r0, _0809A224 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _0809A2BA
	ldr r0, _0809A228 @ =gWrittenToBldalpha_Eva
	strh r3, [r0]
	ldr r0, _0809A22C @ =gWrittenToBldalpha_Evb
	movs r2, #0x10
	strh r2, [r0]
	ldr r0, _0809A230 @ =0x04000048
	strh r3, [r0]
	ldr r1, _0809A234 @ =0x0400004A
	ldr r5, _0809A238 @ =0x0000331D
	adds r0, r5, #0
	strh r0, [r1]
	ldr r0, _0809A23C @ =0x04000016
	strh r3, [r6, #0x14]
	strh r3, [r0]
	adds r0, #0x3c
	lsls r2, r2, #8
	strh r2, [r0]
	adds r1, #6
	ldr r6, _0809A240 @ =0x00001042
	adds r0, r6, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r3, #0x82
	lsls r3, r3, #8
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #1
	strb r0, [r4, #9]
	b _0809A2BA
	.align 2, 0
_0809A218: .4byte 0x0400001A
_0809A21C: .4byte gNonGameplayRam
_0809A220: .4byte 0x0000FFFF
_0809A224: .4byte gWrittenToBldy
_0809A228: .4byte gWrittenToBldalpha_Eva
_0809A22C: .4byte gWrittenToBldalpha_Evb
_0809A230: .4byte 0x04000048
_0809A234: .4byte 0x0400004A
_0809A238: .4byte 0x0000331D
_0809A23C: .4byte 0x04000016
_0809A240: .4byte 0x00001042
_0809A244:
	cmp r3, #1
	bne _0809A284
	ldr r2, _0809A258 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #0xa
	bne _0809A25C
	movs r0, #2
	strb r0, [r4, #9]
	strb r5, [r4, #8]
	b _0809A26E
	.align 2, 0
_0809A258: .4byte gWrittenToBldalpha_Eva
_0809A25C:
	ldrb r0, [r4, #8]
	cmp r0, #3
	bls _0809A26A
	strb r5, [r4, #8]
	adds r0, r1, #1
	strh r0, [r2]
	b _0809A26E
_0809A26A:
	adds r0, #1
	strb r0, [r4, #8]
_0809A26E:
	ldr r0, _0809A27C @ =0x04000016
	ldrh r1, [r6, #0x14]
	adds r1, #3
	strh r1, [r6, #0x14]
	ldr r5, _0809A280 @ =0x0000FFFF
	adds r2, r5, #0
	b _0809A2B6
	.align 2, 0
_0809A27C: .4byte 0x04000016
_0809A280: .4byte 0x0000FFFF
_0809A284:
	ldr r2, _0809A294 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #4
	bne _0809A298
	movs r0, #1
	strb r0, [r4, #9]
	strb r5, [r4, #8]
	b _0809A2AA
	.align 2, 0
_0809A294: .4byte gWrittenToBldalpha_Eva
_0809A298:
	ldrb r0, [r4, #8]
	cmp r0, #3
	bls _0809A2A6
	strb r5, [r4, #8]
	subs r0, r1, #1
	strh r0, [r2]
	b _0809A2AA
_0809A2A6:
	adds r0, #1
	strb r0, [r4, #8]
_0809A2AA:
	ldr r0, _0809A2C0 @ =0x04000016
	ldrh r1, [r6, #0x14]
	adds r1, #3
	strh r1, [r6, #0x14]
	ldr r6, _0809A2C4 @ =0x0000FFFF
	adds r2, r6, #0
_0809A2B6:
	ands r1, r2
	strh r1, [r0]
_0809A2BA:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A2C0: .4byte 0x04000016
_0809A2C4: .4byte 0x0000FFFF

	thumb_func_start CutsceneElevatorMonologueVblank
CutsceneElevatorMonologueVblank: @ 0x0809A2C8
	push {lr}
	ldr r1, _0809A2FC @ =0x040000D4
	ldr r0, _0809A300 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0809A304 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	bl unk_9cc4c
	ldr r2, _0809A308 @ =0x04000052
	ldr r0, _0809A30C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _0809A310 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _0809A314 @ =0x04000054
	ldr r0, _0809A318 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	pop {r0}
	bx r0
	.align 2, 0
_0809A2FC: .4byte 0x040000D4
_0809A300: .4byte gOamData
_0809A304: .4byte 0x84000100
_0809A308: .4byte 0x04000052
_0809A30C: .4byte gWrittenToBldalpha_Evb
_0809A310: .4byte gWrittenToBldalpha_Eva
_0809A314: .4byte 0x04000054
_0809A318: .4byte gWrittenToBldy

	thumb_func_start unk_9a31c
unk_9a31c: @ 0x0809A31C
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneInternalMonologue
CutsceneInternalMonologue: @ 0x0809A328
	push {r4, r5, lr}
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	movs r5, #0
	ldr r4, _0809A344 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _0809A35E
	cmp r0, #1
	bgt _0809A348
	cmp r0, #0
	beq _0809A352
	b _0809A39E
	.align 2, 0
_0809A344: .4byte gNonGameplayRam
_0809A348:
	cmp r0, #2
	beq _0809A378
	cmp r0, #3
	beq _0809A390
	b _0809A39E
_0809A352:
	movs r0, #1
	strh r0, [r4, #8]
	adds r0, r1, #0
	bl CutsceneInternalMonologueInit
	b _0809A39E
_0809A35E:
	bl CutsceneMonologueFadeIn
	ldr r0, _0809A374 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _0809A39E
	ldrh r0, [r4, #8]
	adds r0, #1
	strh r0, [r4, #8]
	b _0809A39E
	.align 2, 0
_0809A374: .4byte gWrittenToBldy
_0809A378:
	bl CutsceneInternalMonologueProcess
	cmp r0, #0
	beq _0809A39E
	movs r0, #3
	strh r0, [r4, #8]
	ldr r1, _0809A38C @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	b _0809A39E
	.align 2, 0
_0809A38C: .4byte 0x04000050
_0809A390:
	bl CutsceneMonologueFadeOut
	ldr r0, _0809A3A8 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0x10
	bne _0809A39E
	movs r5, #1
_0809A39E:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_0809A3A8: .4byte gWrittenToBldy

	thumb_func_start CutsceneInternalMonologueInit
CutsceneInternalMonologueInit: @ 0x0809A3AC
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	ldr r3, _0809A484 @ =0x04000208
	movs r6, #0
	strh r6, [r3]
	ldr r2, _0809A488 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _0809A48C @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _0809A490 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809A494 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809A498 @ =unk_9a63c
	bl CallbackSetVBlank
	movs r0, #0x80
	lsls r0, r0, #0x13
	mov r8, r0
	strh r6, [r0]
	ldr r0, _0809A49C @ =sCutsceneUnk_65fb5c
	ldr r1, _0809A4A0 @ =0x06017C00
	bl LZ77UncompVram
	ldr r4, _0809A4A4 @ =0x040000D4
	ldr r0, _0809A4A8 @ =sCutsceneUnk_6638a0
	str r0, [r4]
	ldr r0, _0809A4AC @ =0x050003E0
	str r0, [r4, #4]
	ldr r0, _0809A4B0 @ =0x84000008
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809A4B4 @ =sIntroTilemap_662804
	movs r5, #0x80
	lsls r5, r5, #0x12
	adds r1, r5, #0
	bl LZ77UncompWram
	str r5, [r4]
	ldr r0, _0809A4B8 @ =0x0600C800
	str r0, [r4, #4]
	ldr r0, _0809A4BC @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809A4C0 @ =sCutsceneUnk_6636a0
	str r0, [r4]
	movs r1, #0xa0
	lsls r1, r1, #0x13
	str r1, [r4, #4]
	ldr r0, _0809A4C4 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	strh r6, [r1]
	ldr r1, _0809A4C8 @ =0x04000012
	movs r0, #4
	strh r0, [r1]
	subs r1, #0xa
	ldr r2, _0809A4CC @ =0x00001908
	adds r0, r2, #0
	strh r0, [r1]
	movs r1, #0x88
	lsls r1, r1, #5
	adds r0, r1, #0
	mov r2, r8
	strh r0, [r2]
	ldr r1, _0809A4D0 @ =gWrittenToBldy
	ldrh r0, [r1]
	subs r0, #1
	strh r0, [r1]
	movs r0, #1
	movs r1, #0xc
	movs r2, #0x10
	bl CutsceneInternalMonologueSetupOam
	ldr r2, _0809A4D4 @ =gNonGameplayRam
	ldr r0, _0809A4D8 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	strh r0, [r2, #0xa]
	ldr r1, _0809A4DC @ =sMonologueTextPointers
	ldr r0, _0809A4E0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrh r1, [r2, #0xa]
	ldr r0, [r0]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r2, #0xc]
	bl CutsceneMonologueDrawAllOam
	ldr r0, _0809A4E4 @ =CutsceneInternalMonologueVblank
	bl CallbackSetVBlank
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A484: .4byte 0x04000208
_0809A488: .4byte 0x04000004
_0809A48C: .4byte 0x0000FFEF
_0809A490: .4byte 0x04000200
_0809A494: .4byte 0x0000FFFD
_0809A498: .4byte unk_9a63c
_0809A49C: .4byte sCutsceneUnk_65fb5c
_0809A4A0: .4byte 0x06017C00
_0809A4A4: .4byte 0x040000D4
_0809A4A8: .4byte sCutsceneUnk_6638a0
_0809A4AC: .4byte 0x050003E0
_0809A4B0: .4byte 0x84000008
_0809A4B4: .4byte sIntroTilemap_662804
_0809A4B8: .4byte 0x0600C800
_0809A4BC: .4byte 0x84000200
_0809A4C0: .4byte sCutsceneUnk_6636a0
_0809A4C4: .4byte 0x84000080
_0809A4C8: .4byte 0x04000012
_0809A4CC: .4byte 0x00001908
_0809A4D0: .4byte gWrittenToBldy
_0809A4D4: .4byte gNonGameplayRam
_0809A4D8: .4byte gCurrentCutscene
_0809A4DC: .4byte sMonologueTextPointers
_0809A4E0: .4byte 0x03000011
_0809A4E4: .4byte CutsceneInternalMonologueVblank

	thumb_func_start CutsceneInternalMonologueProcess
CutsceneInternalMonologueProcess: @ 0x0809A4E8
	push {r4, lr}
	bl CutsceneMonologueProcessSpecialTextCharacters
	adds r4, r0, #0
	ldr r1, _0809A500 @ =gNonGameplayRam
	ldrb r0, [r1, #0x17]
	cmp r0, #0
	beq _0809A504
	cmp r0, #1
	beq _0809A50A
	b _0809A512
	.align 2, 0
_0809A500: .4byte gNonGameplayRam
_0809A504:
	movs r0, #0x64
	strb r0, [r1, #0x17]
	b _0809A512
_0809A50A:
	movs r0, #0x64
	strb r0, [r1, #0x17]
	bl CutsceneMonologueProcessText
_0809A512:
	bl CutsceneMonologueProcessOam
	bl CutsceneMonologueDrawAllOam
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start CutsceneInternalMonologueSetupOam
CutsceneInternalMonologueSetupOam: @ 0x0809A524
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r7, r1, #0x10
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov r8, r2
	movs r4, #0
	ldr r1, _0809A570 @ =gNonGameplayRam
	movs r2, #0x86
	lsls r2, r2, #2
	adds r0, r1, r2
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A566
	adds r3, r1, #0
	adds r1, r2, #0
_0809A54C:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #4
	bhi _0809A56A
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #3
	adds r0, r0, r3
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809A54C
_0809A566:
	cmp r4, #4
	bls _0809A574
_0809A56A:
	movs r0, #5
	b _0809A5DC
	.align 2, 0
_0809A570: .4byte gNonGameplayRam
_0809A574:
	adds r0, r4, #0
	bl CutsceneMonologueResetOam
	ldr r5, _0809A5E8 @ =gNonGameplayRam
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r3, r0, #3
	adds r2, r3, r5
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r2, r1
	strh r7, [r0]
	adds r1, #2
	adds r0, r2, r1
	mov r1, r8
	strh r1, [r0]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r6, [r0]
	ldr r0, _0809A5EC @ =0x00000219
	adds r1, r2, r0
	movs r0, #1
	strb r0, [r1]
	cmp r6, #1
	bne _0809A5DA
	ldr r0, _0809A5F0 @ =0x0000021F
	adds r1, r2, r0
	movs r0, #2
	strb r0, [r1]
	ldr r0, _0809A5F4 @ =0x00000221
	adds r1, r2, r0
	movs r0, #0xf
	strb r0, [r1]
	ldr r0, _0809A5F8 @ =0x00000222
	adds r1, r2, r0
	movs r0, #0xf8
	lsls r0, r0, #2
	strh r0, [r1]
	movs r1, #0x89
	lsls r1, r1, #2
	adds r0, r5, r1
	adds r0, r3, r0
	ldr r1, _0809A5FC @ =sCutsceneUnk_663e5c
	str r1, [r0]
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r5, r1
	adds r0, r3, r0
	ldr r1, _0809A600 @ =CutsceneMonologueProcessCursor
	str r1, [r0]
_0809A5DA:
	adds r0, r4, #0
_0809A5DC:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809A5E8: .4byte gNonGameplayRam
_0809A5EC: .4byte 0x00000219
_0809A5F0: .4byte 0x0000021F
_0809A5F4: .4byte 0x00000221
_0809A5F8: .4byte 0x00000222
_0809A5FC: .4byte sCutsceneUnk_663e5c
_0809A600: .4byte CutsceneMonologueProcessCursor

	thumb_func_start CutsceneInternalMonologueVblank
CutsceneInternalMonologueVblank: @ 0x0809A604
	push {lr}
	ldr r1, _0809A628 @ =0x040000D4
	ldr r0, _0809A62C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0809A630 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	bl unk_9cc4c
	ldr r1, _0809A634 @ =0x04000054
	ldr r0, _0809A638 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	pop {r0}
	bx r0
	.align 2, 0
_0809A628: .4byte 0x040000D4
_0809A62C: .4byte gOamData
_0809A630: .4byte 0x84000100
_0809A634: .4byte 0x04000054
_0809A638: .4byte gWrittenToBldy

	thumb_func_start unk_9a63c
unk_9a63c: @ 0x0809A63C
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneFederationMonologue
CutsceneFederationMonologue: @ 0x0809A648
	push {r4, r5, lr}
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	movs r5, #0
	ldr r4, _0809A664 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _0809A67E
	cmp r0, #1
	bgt _0809A668
	cmp r0, #0
	beq _0809A672
	b _0809A6BE
	.align 2, 0
_0809A664: .4byte gNonGameplayRam
_0809A668:
	cmp r0, #2
	beq _0809A698
	cmp r0, #3
	beq _0809A6B0
	b _0809A6BE
_0809A672:
	movs r0, #1
	strh r0, [r4, #8]
	adds r0, r1, #0
	bl CutsceneFederationMonologueInit
	b _0809A6BE
_0809A67E:
	bl CutsceneMonologueFadeIn
	ldr r0, _0809A694 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _0809A6BE
	ldrh r0, [r4, #8]
	adds r0, #1
	strh r0, [r4, #8]
	b _0809A6BE
	.align 2, 0
_0809A694: .4byte gWrittenToBldy
_0809A698:
	bl CutsceneFederationMonologueProcess
	cmp r0, #0
	beq _0809A6BE
	movs r0, #3
	strh r0, [r4, #8]
	ldr r1, _0809A6AC @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	b _0809A6BE
	.align 2, 0
_0809A6AC: .4byte 0x04000050
_0809A6B0:
	bl CutsceneMonologueFadeOut
	ldr r0, _0809A6C8 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0x10
	bne _0809A6BE
	movs r5, #1
_0809A6BE:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_0809A6C8: .4byte gWrittenToBldy

	thumb_func_start CutsceneFederationMonologueInit
CutsceneFederationMonologueInit: @ 0x0809A6CC
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	ldr r3, _0809A7CC @ =0x04000208
	movs r6, #0
	strh r6, [r3]
	ldr r2, _0809A7D0 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _0809A7D4 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _0809A7D8 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809A7DC @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809A7E0 @ =unk_9a99c
	bl CallbackSetVBlank
	movs r0, #0x80
	lsls r0, r0, #0x13
	mov r8, r0
	strh r6, [r0]
	ldr r0, _0809A7E4 @ =sCutsceneUnk_65fb5c
	ldr r1, _0809A7E8 @ =0x06017C00
	bl LZ77UncompVram
	ldr r4, _0809A7EC @ =0x040000D4
	ldr r0, _0809A7F0 @ =sCutsceneUnk_6638a0
	str r0, [r4]
	ldr r0, _0809A7F4 @ =0x050003E0
	str r0, [r4, #4]
	ldr r0, _0809A7F8 @ =0x84000008
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809A7FC @ =sCutsceneUnk_6724c0
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _0809A800 @ =sCutsceneUnk_674ad8
	ldr r1, _0809A804 @ =0x0600D000
	bl LZ77UncompVram
	ldr r0, _0809A808 @ =sIntroTilemap_662804
	movs r5, #0x80
	lsls r5, r5, #0x12
	adds r1, r5, #0
	bl LZ77UncompWram
	str r5, [r4]
	ldr r0, _0809A80C @ =0x0600C800
	str r0, [r4, #4]
	ldr r0, _0809A810 @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809A814 @ =sCutsceneUnk_674958
	str r0, [r4]
	movs r1, #0xa0
	lsls r1, r1, #0x13
	str r1, [r4, #4]
	ldr r0, _0809A818 @ =0x84000060
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809A81C @ =sIntroPal_663820
	str r0, [r4]
	ldr r0, _0809A820 @ =0x05000180
	str r0, [r4, #4]
	ldr r0, _0809A824 @ =0x84000020
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	strh r6, [r1]
	ldr r1, _0809A828 @ =0x04000012
	movs r0, #4
	strh r0, [r1]
	subs r1, #0xa
	ldr r2, _0809A82C @ =0x00001908
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	adds r2, #0xfb
	adds r0, r2, #0
	strh r0, [r1]
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r1, #0
	mov r2, r8
	strh r0, [r2]
	ldr r1, _0809A830 @ =gWrittenToBldy
	ldrh r0, [r1]
	subs r0, #1
	strh r0, [r1]
	movs r0, #1
	movs r1, #0xc
	movs r2, #0x10
	bl CutsceneFederationMonologueSetupOam
	ldr r2, _0809A834 @ =gNonGameplayRam
	ldr r0, _0809A838 @ =gCurrentCutscene
	ldrb r0, [r0]
	subs r0, #1
	strh r0, [r2, #0xa]
	ldr r1, _0809A83C @ =sMonologueTextPointers
	ldr r0, _0809A840 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldrh r1, [r2, #0xa]
	ldr r0, [r0]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r2, #0xc]
	bl CutsceneMonologueDrawAllOam
	ldr r0, _0809A844 @ =CutsceneFederationMonologueVblank
	bl CallbackSetVBlank
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A7CC: .4byte 0x04000208
_0809A7D0: .4byte 0x04000004
_0809A7D4: .4byte 0x0000FFEF
_0809A7D8: .4byte 0x04000200
_0809A7DC: .4byte 0x0000FFFD
_0809A7E0: .4byte unk_9a99c
_0809A7E4: .4byte sCutsceneUnk_65fb5c
_0809A7E8: .4byte 0x06017C00
_0809A7EC: .4byte 0x040000D4
_0809A7F0: .4byte sCutsceneUnk_6638a0
_0809A7F4: .4byte 0x050003E0
_0809A7F8: .4byte 0x84000008
_0809A7FC: .4byte sCutsceneUnk_6724c0
_0809A800: .4byte sCutsceneUnk_674ad8
_0809A804: .4byte 0x0600D000
_0809A808: .4byte sIntroTilemap_662804
_0809A80C: .4byte 0x0600C800
_0809A810: .4byte 0x84000200
_0809A814: .4byte sCutsceneUnk_674958
_0809A818: .4byte 0x84000060
_0809A81C: .4byte sIntroPal_663820
_0809A820: .4byte 0x05000180
_0809A824: .4byte 0x84000020
_0809A828: .4byte 0x04000012
_0809A82C: .4byte 0x00001908
_0809A830: .4byte gWrittenToBldy
_0809A834: .4byte gNonGameplayRam
_0809A838: .4byte gCurrentCutscene
_0809A83C: .4byte sMonologueTextPointers
_0809A840: .4byte 0x03000011
_0809A844: .4byte CutsceneFederationMonologueVblank
