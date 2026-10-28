    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start CutsceneBslExploding
CutsceneBslExploding: @ 0x0809C1C8
	push {r4, r5, r6, lr}
	movs r6, #0
	ldr r4, _0809C1E0 @ =gNonGameplayRam
	ldrh r0, [r4]
	cmp r0, #1
	beq _0809C1F8
	cmp r0, #1
	bgt _0809C1E4
	cmp r0, #0
	beq _0809C1EE
	b _0809C246
	.align 2, 0
_0809C1E0: .4byte gNonGameplayRam
_0809C1E4:
	cmp r0, #2
	beq _0809C220
	cmp r0, #3
	beq _0809C238
	b _0809C246
_0809C1EE:
	movs r0, #1
	strh r0, [r4]
	bl CutsceneBslExplodingInit
	b _0809C246
_0809C1F8:
	ldr r5, _0809C218 @ =gWrittenToBldy
	ldrh r0, [r5]
	cmp r0, #0x10
	bne _0809C206
	ldr r0, _0809C21C @ =0x00000247
	bl SoundPlay_3b1c
_0809C206:
	bl CutsceneFadeIn
	ldrh r0, [r5]
	cmp r0, #0
	bne _0809C246
	ldrh r0, [r4]
	adds r0, #1
	strh r0, [r4]
	b _0809C246
	.align 2, 0
_0809C218: .4byte gWrittenToBldy
_0809C21C: .4byte 0x00000247
_0809C220:
	bl CutsceneBslExplodingProcess
	cmp r0, #0
	beq _0809C246
	movs r0, #3
	strh r0, [r4]
	ldr r1, _0809C234 @ =0x04000050
	movs r0, #0xbf
	strh r0, [r1]
	b _0809C246
	.align 2, 0
_0809C234: .4byte 0x04000050
_0809C238:
	bl CutsceneFadeOut
	ldr r0, _0809C250 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0x10
	bne _0809C246
	movs r6, #1
_0809C246:
	adds r0, r6, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0809C250: .4byte gWrittenToBldy

	thumb_func_start CutsceneBslExplodingInit
CutsceneBslExplodingInit: @ 0x0809C254
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	ldr r3, _0809C360 @ =0x04000208
	movs r5, #0
	strh r5, [r3]
	ldr r2, _0809C364 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _0809C368 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _0809C36C @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809C370 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809C374 @ =unk_9c92c
	bl CallbackSetVBlank
	movs r0, #0x80
	lsls r0, r0, #0x13
	mov r8, r0
	strh r5, [r0]
	ldr r0, _0809C378 @ =sCutsceneUnk_67d7cc
	ldr r1, _0809C37C @ =0x06010000
	bl LZ77UncompVram
	ldr r4, _0809C380 @ =0x040000D4
	ldr r0, _0809C384 @ =sCutsceneUnk_68121c
	str r0, [r4]
	ldr r0, _0809C388 @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _0809C38C @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809C390 @ =sCutsceneUnk_679420
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _0809C394 @ =sCutsceneUnk_681a1c
	ldr r1, _0809C398 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _0809C39C @ =sCutsceneUnk_6820a4
	ldr r1, _0809C3A0 @ =0x0600E800
	bl LZ77UncompVram
	ldr r0, _0809C3A4 @ =sCutsceneUnk_6827a8
	ldr r1, _0809C3A8 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _0809C3AC @ =sCutsceneUnk_682bfc
	ldr r1, _0809C3B0 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _0809C3B4 @ =sCutsceneUnk_68259c
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r1, [r4, #8]
	strh r5, [r0]
	ldr r1, _0809C3B8 @ =0x04000008
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0809C3BC @ =0x00001D03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	adds r2, #0xfd
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0809C3C0 @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r1, #0
	mov r2, r8
	strh r0, [r2]
	ldr r0, _0809C3C4 @ =gWrittenToBldy
	movs r2, #0x10
	strh r2, [r0]
	ldr r1, _0809C3C8 @ =gWrittenToBldalpha_Eva
	movs r0, #8
	strh r0, [r1]
	ldr r0, _0809C3CC @ =gWrittenToBldalpha_Evb
	strh r2, [r0]
	movs r0, #1
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	movs r0, #0x14
	movs r1, #0x70
	movs r2, #0x58
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	ldr r0, _0809C3D0 @ =gNonGameplayRam
	movs r1, #0
	strh r1, [r0, #0xa]
	strh r1, [r0, #0xc]
	movs r1, #0xc
	ldrsh r0, [r0, r1]
	lsls r0, r0, #5
	ldr r1, _0809C3D4 @ =sCutsceneUnk_68101c
	adds r0, r0, r1
	str r0, [r4]
	ldr r0, _0809C3D8 @ =0x05000120
	str r0, [r4, #4]
	ldr r0, _0809C3DC @ =0x84000008
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	bl CutsceneDrawAllOam
	ldr r0, _0809C3E0 @ =CutsceneBslExplodingVblank
	bl CallbackSetVBlank
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809C360: .4byte 0x04000208
_0809C364: .4byte 0x04000004
_0809C368: .4byte 0x0000FFEF
_0809C36C: .4byte 0x04000200
_0809C370: .4byte 0x0000FFFD
_0809C374: .4byte unk_9c92c
_0809C378: .4byte sCutsceneUnk_67d7cc
_0809C37C: .4byte 0x06010000
_0809C380: .4byte 0x040000D4
_0809C384: .4byte sCutsceneUnk_68121c
_0809C388: .4byte 0x05000200
_0809C38C: .4byte 0x84000080
_0809C390: .4byte sCutsceneUnk_679420
_0809C394: .4byte sCutsceneUnk_681a1c
_0809C398: .4byte 0x0600E000
_0809C39C: .4byte sCutsceneUnk_6820a4
_0809C3A0: .4byte 0x0600E800
_0809C3A4: .4byte sCutsceneUnk_6827a8
_0809C3A8: .4byte 0x0600F000
_0809C3AC: .4byte sCutsceneUnk_682bfc
_0809C3B0: .4byte 0x0600F800
_0809C3B4: .4byte sCutsceneUnk_68259c
_0809C3B8: .4byte 0x04000008
_0809C3BC: .4byte 0x00001D03
_0809C3C0: .4byte 0x00001F03
_0809C3C4: .4byte gWrittenToBldy
_0809C3C8: .4byte gWrittenToBldalpha_Eva
_0809C3CC: .4byte gWrittenToBldalpha_Evb
_0809C3D0: .4byte gNonGameplayRam
_0809C3D4: .4byte sCutsceneUnk_68101c
_0809C3D8: .4byte 0x05000120
_0809C3DC: .4byte 0x84000008
_0809C3E0: .4byte CutsceneBslExplodingVblank

	thumb_func_start CutsceneBslExplodingProcess
CutsceneBslExplodingProcess: @ 0x0809C3E4
	push {r4, r5, lr}
	movs r5, #0
	ldr r1, _0809C404 @ =gNonGameplayRam
	ldrh r0, [r1, #8]
	adds r0, #1
	strh r0, [r1, #8]
	ldrb r0, [r1, #0x10]
	adds r4, r1, #0
	cmp r0, #6
	bls _0809C3FA
	b _0809C5E2
_0809C3FA:
	lsls r0, r0, #2
	ldr r1, _0809C408 @ =_0809C40C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0809C404: .4byte gNonGameplayRam
_0809C408: .4byte _0809C40C
_0809C40C: @ jump table
	.4byte _0809C428 @ case 0
	.4byte _0809C432 @ case 1
	.4byte _0809C464 @ case 2
	.4byte _0809C4CC @ case 3
	.4byte _0809C4FC @ case 4
	.4byte _0809C52C @ case 5
	.4byte _0809C5B4 @ case 6
_0809C428:
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #1
	strb r0, [r4, #0x10]
	b _0809C5E2
_0809C432:
	ldrh r0, [r4, #8]
	cmp r0, #0xf
	beq _0809C43A
	b _0809C5E2
_0809C43A:
	ldr r1, _0809C45C @ =0x04000050
	ldr r2, _0809C460 @ =0x00001C44
	adds r0, r2, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #2
	strb r0, [r4, #0x10]
	b _0809C5E2
	.align 2, 0
_0809C45C: .4byte 0x04000050
_0809C460: .4byte 0x00001C44
_0809C464:
	ldr r2, _0809C484 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #0xf
	bhi _0809C48C
	ldrh r0, [r4, #8]
	cmp r0, #1
	bne _0809C47A
	movs r0, #0
	strh r0, [r4, #8]
	adds r0, r1, #2
	strh r0, [r2]
_0809C47A:
	ldr r1, _0809C488 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	b _0809C5E2
	.align 2, 0
_0809C484: .4byte gWrittenToBldalpha_Eva
_0809C488: .4byte gWrittenToBldy
_0809C48C:
	ldrh r0, [r4, #8]
	cmp r0, #0x28
	beq _0809C494
	b _0809C5E2
_0809C494:
	ldr r1, _0809C4C8 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	subs r1, #0x50
	movs r2, #0x90
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	movs r0, #1
	bl CutsceneDestroyOamOfType
	movs r0, #0x14
	bl CutsceneDestroyOamOfType
	movs r0, #0x15
	movs r1, #0x78
	movs r2, #0x5a
	movs r3, #1
	bl CutsceneBslExplodingSetupOam
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #3
	strb r0, [r4, #0x10]
	b _0809C5E2
	.align 2, 0
_0809C4C8: .4byte 0x04000050
_0809C4CC:
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _0809C4D4
	b _0809C5E2
_0809C4D4:
	ldr r1, _0809C4F0 @ =gWrittenToBldy
	movs r0, #0
	strh r0, [r1]
	ldr r0, _0809C4F4 @ =gWrittenToBldalpha_Eva
	movs r1, #0xa
	strh r1, [r0]
	ldr r0, _0809C4F8 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #4
	strb r0, [r4, #0x10]
	b _0809C5E2
	.align 2, 0
_0809C4F0: .4byte gWrittenToBldy
_0809C4F4: .4byte gWrittenToBldalpha_Eva
_0809C4F8: .4byte gWrittenToBldalpha_Evb
_0809C4FC:
	ldrh r0, [r4, #8]
	cmp r0, #0x3c
	bne _0809C5E2
	ldr r1, _0809C524 @ =0x04000050
	ldr r3, _0809C528 @ =0x00001E41
	adds r0, r3, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #5
	strb r0, [r4, #0x10]
	b _0809C5E2
	.align 2, 0
_0809C524: .4byte 0x04000050
_0809C528: .4byte 0x00001E41
_0809C52C:
	ldrh r1, [r4, #0xc]
	movs r2, #0xc
	ldrsh r0, [r4, r2]
	cmp r0, #0xe
	bgt _0809C59A
	ldrh r0, [r4, #8]
	cmp r0, #4
	bne _0809C5E2
	movs r0, #0
	strh r0, [r4, #8]
	movs r0, #1
	strh r0, [r4, #0xa]
	adds r0, r1, #1
	strh r0, [r4, #0xc]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #1
	bne _0809C570
	movs r0, #0x16
	movs r1, #0x78
	movs r2, #0x60
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	movs r0, #0x16
	movs r1, #0x5f
	movs r2, #0x50
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	movs r0, #0x16
	movs r1, #0x8c
	movs r2, #0x69
	b _0809C592
_0809C570:
	cmp r0, #2
	bne _0809C588
	movs r0, #0x16
	movs r1, #0x78
	movs r2, #0x54
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	movs r0, #0x16
	movs r1, #0x91
	movs r2, #0x55
	b _0809C592
_0809C588:
	cmp r0, #3
	bne _0809C5E2
	movs r0, #0x16
	movs r1, #0x60
	movs r2, #0x6a
_0809C592:
	movs r3, #0
	bl CutsceneBslExplodingSetupOam
	b _0809C5E2
_0809C59A:
	ldrh r0, [r4, #8]
	cmp r0, #0xf
	bne _0809C5E2
	movs r0, #0
	strh r0, [r4, #8]
	ldr r1, _0809C5B0 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r0, #6
	strb r0, [r4, #0x10]
	b _0809C5E2
	.align 2, 0
_0809C5B0: .4byte gWrittenToBldy
_0809C5B4:
	ldr r2, _0809C5CC @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	cmp r1, #0xf
	bhi _0809C5D0
	ldrh r0, [r4, #8]
	cmp r0, #6
	bne _0809C5E2
	movs r0, #0
	strh r0, [r4, #8]
	adds r0, r1, #1
	strh r0, [r2]
	b _0809C5E2
	.align 2, 0
_0809C5CC: .4byte gWrittenToBldalpha_Eva
_0809C5D0:
	ldr r0, _0809C5F4 @ =0x04000050
	movs r1, #0xbf
	strh r1, [r0]
	ldrh r0, [r4, #8]
	cmp r0, #0x10
	bne _0809C5E2
	movs r0, #0
	strh r0, [r4, #8]
	movs r5, #1
_0809C5E2:
	bl CutsceneProcessOam
	bl CutsceneDrawAllOam
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_0809C5F4: .4byte 0x04000050

	thumb_func_start CutsceneBslExplodingProcessScrolling
CutsceneBslExplodingProcessScrolling: @ 0x0809C5F8
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1e
	bne _0809C614
	movs r0, #0
	strb r0, [r2, #0x13]
	ldrh r0, [r2]
	subs r0, #1
	strh r0, [r2]
_0809C614:
	ldr r1, _0809C620 @ =0x0400001C
	ldrh r0, [r2]
	strh r0, [r1]
	pop {r0}
	bx r0
	.align 2, 0
_0809C620: .4byte 0x0400001C

	thumb_func_start CutsceneBslExplodingProcessBslFar
CutsceneBslExplodingProcessBslFar: @ 0x0809C624
	push {r4, lr}
	adds r2, r0, #0
	ldrb r1, [r2, #0x14]
	cmp r1, #0
	bne _0809C654
	ldr r3, _0809C64C @ =gNonGameplayRam
	ldrb r0, [r3, #0x10]
	cmp r0, #5
	bne _0809C67A
	movs r4, #0xc
	ldrsh r0, [r3, r4]
	cmp r0, #5
	bne _0809C67A
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _0809C650 @ =sCutsceneUnk_680ecc
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
	b _0809C67A
	.align 2, 0
_0809C64C: .4byte gNonGameplayRam
_0809C650: .4byte sCutsceneUnk_680ecc
_0809C654:
	cmp r1, #1
	bne _0809C67A
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _0809C67A
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809C67A
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x16]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x16]
_0809C67A:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start CutsceneBslExplodingProcessExplosions
CutsceneBslExplodingProcessExplosions: @ 0x0809C680
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _0809C6A6
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809C6A6
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x16]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x16]
_0809C6A6:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneBslExplodingSetupOam
CutsceneBslExplodingSetupOam: @ 0x0809C6AC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov r8, r1
	lsls r2, r2, #0x10
	lsrs r7, r2, #0x10
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _0809C708
	movs r2, #0
	ldr r1, _0809C704 @ =gNonGameplayRam
	adds r0, r1, #0
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809C6F8
	adds r3, r1, #0
_0809C6D8:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0xf
	bgt _0809C742
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809C6D8
_0809C6F8:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	adds r6, r0, #0
	cmp r1, #0xf
	ble _0809C74C
	b _0809C742
	.align 2, 0
_0809C704: .4byte gNonGameplayRam
_0809C708:
	movs r2, #0xf
	ldr r1, _0809C748 @ =gNonGameplayRam
	movs r3, #0x91
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809C73A
	adds r3, r1, #0
_0809C71A:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _0809C742
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809C71A
_0809C73A:
	lsls r0, r2, #0x18
	adds r6, r0, #0
	cmp r6, #0
	bge _0809C74C
_0809C742:
	movs r0, #0x10
	b _0809C83A
	.align 2, 0
_0809C748: .4byte gNonGameplayRam
_0809C74C:
	movs r0, #0
	str r0, [sp]
	ldr r2, _0809C7A0 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	asrs r1, r6, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r4, r0, #2
	ldr r0, _0809C7A4 @ =0x0300149C
	mov ip, r0
	adds r0, r4, r0
	str r0, [r2, #4]
	ldr r0, _0809C7A8 @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	mov r0, ip
	subs r0, #0x18
	adds r2, r4, r0
	mov r1, r8
	strh r1, [r2, #0x18]
	strh r7, [r2, #0x1a]
	adds r0, r2, #0
	adds r0, #0x28
	strb r5, [r0]
	adds r3, r2, #0
	adds r3, #0x2e
	ldrb r1, [r3]
	movs r0, #1
	orrs r1, r0
	strb r1, [r3]
	cmp r5, #1
	bne _0809C7B0
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r3]
	mov r0, ip
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809C7AC @ =CutsceneBslExplodingProcessScrolling
	b _0809C836
	.align 2, 0
_0809C7A0: .4byte 0x040000D4
_0809C7A4: .4byte 0x0300149C
_0809C7A8: .4byte 0x85000009
_0809C7AC: .4byte CutsceneBslExplodingProcessScrolling
_0809C7B0:
	cmp r5, #0x14
	bne _0809C7E0
	adds r2, #0x30
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _0809C7D8 @ =sCutsceneUnk_680ffc
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809C7DC @ =unk_9db70
	b _0809C836
	.align 2, 0
_0809C7D8: .4byte sCutsceneUnk_680ffc
_0809C7DC: .4byte unk_9db70
_0809C7E0:
	cmp r5, #0x15
	bne _0809C810
	adds r2, #0x30
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _0809C808 @ =sCutsceneUnk_68100c
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809C80C @ =CutsceneBslExplodingProcessBslFar
	b _0809C836
	.align 2, 0
_0809C808: .4byte sCutsceneUnk_68100c
_0809C80C: .4byte CutsceneBslExplodingProcessBslFar
_0809C810:
	cmp r5, #0x16
	bne _0809C838
	adds r2, #0x30
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _0809C848 @ =sCutsceneUnk_680ecc
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809C84C @ =CutsceneBslExplodingProcessExplosions
_0809C836:
	str r1, [r0]
_0809C838:
	lsrs r0, r6, #0x18
_0809C83A:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809C848: .4byte sCutsceneUnk_680ecc
_0809C84C: .4byte CutsceneBslExplodingProcessExplosions

	thumb_func_start CutsceneBslExplodingGetOamInfoByType
CutsceneBslExplodingGetOamInfoByType: @ 0x0809C850
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	adds r5, r2, #0
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r2, #0
	ldr r7, _0809C880 @ =gNonGameplayRam
_0809C85E:
	lsls r0, r2, #3
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r1, r0, r7
	adds r0, r1, #0
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, r6
	bne _0809C884
	ldrh r0, [r1, #0x18]
	strh r0, [r4]
	ldrh r0, [r1, #0x1a]
	strh r0, [r5]
	ldrh r0, [r1, #0x1c]
	strh r0, [r3]
	adds r0, r2, #0
	b _0809C8A2
	.align 2, 0
_0809C880: .4byte gNonGameplayRam
_0809C884:
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0xf
	bls _0809C85E
	movs r1, #0x96
	lsls r1, r1, #1
	adds r0, r1, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r5]
	subs r1, #0x2c
	adds r0, r1, #0
	strh r0, [r3]
	movs r0, #0
_0809C8A2:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start CutsceneBslExplodingVblank
CutsceneBslExplodingVblank: @ 0x0809C8A8
	push {lr}
	ldr r3, _0809C8FC @ =0x040000D4
	ldr r0, _0809C900 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _0809C904 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _0809C908 @ =0x04000052
	ldr r0, _0809C90C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _0809C910 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _0809C914 @ =0x04000054
	ldr r0, _0809C918 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0809C91C @ =gNonGameplayRam
	movs r2, #0xa
	ldrsh r0, [r1, r2]
	cmp r0, #1
	bne _0809C8F8
	movs r0, #0
	strh r0, [r1, #0xa]
	movs r2, #0xc
	ldrsh r0, [r1, r2]
	lsls r0, r0, #5
	ldr r1, _0809C920 @ =sCutsceneUnk_68101c
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _0809C924 @ =0x05000120
	str r0, [r3, #4]
	ldr r0, _0809C928 @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_0809C8F8:
	pop {r0}
	bx r0
	.align 2, 0
_0809C8FC: .4byte 0x040000D4
_0809C900: .4byte gOamData
_0809C904: .4byte 0x84000100
_0809C908: .4byte 0x04000052
_0809C90C: .4byte gWrittenToBldalpha_Evb
_0809C910: .4byte gWrittenToBldalpha_Eva
_0809C914: .4byte 0x04000054
_0809C918: .4byte gWrittenToBldy
_0809C91C: .4byte gNonGameplayRam
_0809C920: .4byte sCutsceneUnk_68101c
_0809C924: .4byte 0x05000120
_0809C928: .4byte 0x84000008

	thumb_func_start unk_9c92c
unk_9c92c: @ 0x0809C92C
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start CutsceneMonologueProcessCursor
CutsceneMonologueProcessCursor: @ 0x0809C938
	push {lr}
	adds r2, r0, #0
	ldr r3, _0809C954 @ =gNonGameplayRam
	ldr r0, [r3, #0xc]
	ldrh r1, [r0]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809C958
	movs r0, #0
	strb r0, [r2, #4]
	strb r0, [r2, #5]
	b _0809C9F4
	.align 2, 0
_0809C954: .4byte gNonGameplayRam
_0809C958:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	beq _0809C9E0
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	beq _0809C9C2
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809C9E0
	ldrb r1, [r2, #9]
	cmp r1, #0
	bne _0809C9B4
	ldr r0, _0809C990 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0809C994
	movs r1, #0
	movs r0, #0x91
	lsls r0, r0, #1
	strh r0, [r2]
	strb r1, [r2, #7]
	strb r1, [r2, #6]
	b _0809C9F4
	.align 2, 0
_0809C990: .4byte gChangedInput
_0809C994:
	ldr r0, _0809C9B0 @ =sCutsceneUnk_663e74
	str r0, [r2, #0x10]
	movs r1, #0
	movs r0, #0x76
	strh r0, [r2]
	ldrh r0, [r3, #2]
	lsls r0, r0, #3
	adds r0, #0x18
	strh r0, [r2, #2]
	strb r1, [r2, #7]
	strb r1, [r2, #6]
	movs r0, #1
	strb r0, [r2, #9]
	b _0809C9F4
	.align 2, 0
_0809C9B0: .4byte sCutsceneUnk_663e74
_0809C9B4:
	cmp r1, #1
	bne _0809C9F4
	ldr r0, _0809C9D8 @ =gChangedInput
	ldrh r0, [r0]
	ands r1, r0
	cmp r1, #0
	beq _0809C9F4
_0809C9C2:
	ldr r0, _0809C9DC @ =sCutsceneUnk_663e5c
	str r0, [r2, #0x10]
	movs r1, #0
	movs r0, #0x91
	lsls r0, r0, #1
	strh r0, [r2]
	strb r1, [r2, #7]
	strb r1, [r2, #6]
	strb r1, [r2, #9]
	b _0809C9F4
	.align 2, 0
_0809C9D8: .4byte gChangedInput
_0809C9DC: .4byte sCutsceneUnk_663e5c
_0809C9E0:
	ldrh r0, [r3]
	lsls r0, r0, #3
	ldrb r1, [r3, #0x18]
	adds r1, #0xc
	adds r0, r0, r1
	strh r0, [r2]
	ldrh r0, [r3, #2]
	lsls r0, r0, #3
	adds r0, #0xc
	strh r0, [r2, #2]
_0809C9F4:
	pop {r0}
	bx r0

	thumb_func_start CutsceneMonologueProcessSpecialTextCharacters
CutsceneMonologueProcessSpecialTextCharacters: @ 0x0809C9F8
	push {r4, r5, r6, lr}
	movs r6, #0
	ldr r0, _0809CA10 @ =gButtonInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0809CA18
	ldr r1, _0809CA14 @ =gNonGameplayRam
	ldrh r0, [r1, #0x10]
	adds r0, #2
	b _0809CA1E
	.align 2, 0
_0809CA10: .4byte gButtonInput
_0809CA14: .4byte gNonGameplayRam
_0809CA18:
	ldr r1, _0809CA40 @ =gNonGameplayRam
	ldrh r0, [r1, #0x10]
	adds r0, #1
_0809CA1E:
	strh r0, [r1, #0x10]
	adds r5, r1, #0
	adds r3, r5, #0
	ldr r0, [r3, #0xc]
	ldrh r2, [r0]
	adds r1, r2, #0
	movs r4, #0xff
	lsls r4, r4, #8
	cmp r1, r4
	bne _0809CA44
	movs r0, #0
	strh r0, [r3, #0x10]
	movs r0, #0x64
	strb r0, [r3, #0x17]
	movs r6, #1
	b _0809CA92
	.align 2, 0
_0809CA40: .4byte gNonGameplayRam
_0809CA44:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809CA64
	ldr r0, _0809CA60 @ =gChangedInput
	ldrh r0, [r0]
	movs r1, #1
	ands r1, r0
	cmp r1, #0
	beq _0809CA80
	movs r1, #0
	movs r0, #1
	b _0809CA7E
	.align 2, 0
_0809CA60: .4byte gChangedInput
_0809CA64:
	adds r0, r4, #0
	ands r0, r2
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809CA84
	movs r0, #0xff
	ands r0, r2
	ldrh r1, [r3, #0x10]
	cmp r0, r1
	bhi _0809CA92
	movs r1, #0
	movs r0, #1
_0809CA7E:
	strb r0, [r3, #0x17]
_0809CA80:
	strh r1, [r3, #0x10]
	b _0809CA92
_0809CA84:
	ldrh r0, [r5, #0x10]
	cmp r0, #2
	bls _0809CA92
	movs r1, #0
	movs r0, #1
	strb r0, [r5, #0x17]
	strh r1, [r5, #0x10]
_0809CA92:
	adds r0, r6, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start CutsceneMonologueProcessText
CutsceneMonologueProcessText: @ 0x0809CA9C
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r5, _0809CB04 @ =gNonGameplayRam
	ldr r2, [r5, #0xc]
	ldrh r3, [r2]
	adds r1, r3, #0
	movs r6, #0xff
	lsls r6, r6, #8
	adds r4, r5, #0
	cmp r1, r6
	bne _0809CAB4
	b _0809CC3A
_0809CAB4:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809CB08
	ldrh r0, [r4]
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0x1b
	bhi _0809CAEC
	adds r6, r4, #0
	adds r5, #0x1c
	movs r3, #0xff
_0809CACE:
	ldrh r1, [r6, #2]
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
	bls _0809CACE
_0809CAEC:
	movs r1, #0
	movs r0, #0
	strh r0, [r4]
	ldrh r0, [r4, #2]
	adds r0, #2
	strh r0, [r4, #2]
	ldr r0, [r4, #0xc]
	adds r0, #2
	str r0, [r4, #0xc]
	strb r1, [r4, #0x18]
	b _0809CC3A
	.align 2, 0
_0809CB04: .4byte gNonGameplayRam
_0809CB08:
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809CB84
	movs r2, #0
	str r2, [sp, #4]
	ldr r1, _0809CB6C @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _0809CB70 @ =0x06008000
	str r0, [r1, #4]
	ldr r0, _0809CB74 @ =0x85001200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r3, #0
	strh r2, [r4, #6]
	strh r2, [r4, #4]
	strh r2, [r4, #2]
	strh r2, [r4]
	ldr r0, [r4, #0xc]
	adds r0, #2
	str r0, [r4, #0xc]
	strb r3, [r4, #0x18]
	str r2, [sp, #4]
	add r0, sp, #4
	str r0, [r1]
	adds r0, r4, #0
	adds r0, #0x1c
	str r0, [r1, #4]
	ldr r3, _0809CB78 @ =0x8500003F
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	str r2, [sp, #4]
	add r2, sp, #4
	str r2, [r1]
	movs r2, #0x8c
	lsls r2, r2, #1
	adds r0, r4, r2
	str r0, [r1, #4]
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0x80
	lsls r0, r0, #0x12
	str r0, [r1]
	ldr r0, _0809CB7C @ =0x0600C800
	str r0, [r1, #4]
	ldr r0, _0809CB80 @ =0x84000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _0809CC3A
	.align 2, 0
_0809CB6C: .4byte 0x040000D4
_0809CB70: .4byte 0x06008000
_0809CB74: .4byte 0x85001200
_0809CB78: .4byte 0x8500003F
_0809CB7C: .4byte 0x0600C800
_0809CB80: .4byte 0x84000200
_0809CB84:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	beq _0809CB98
	adds r0, r6, #0
	ands r0, r3
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809CB9E
_0809CB98:
	adds r0, r2, #2
	str r0, [r4, #0xc]
	b _0809CC3A
_0809CB9E:
	ldrh r4, [r5]
	lsls r4, r4, #5
	ldrh r0, [r5, #2]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r0, _0809CC44 @ =0x06008000
	adds r4, r4, r0
	ldrh r0, [r2]
	bl TextGetCharacterWidth
	adds r6, r0, #0
	ldr r0, [r5, #0xc]
	ldrh r0, [r0]
	lsls r2, r6, #0x18
	lsrs r2, r2, #0x18
	ldrb r3, [r5, #0x18]
	movs r1, #0
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrh r0, [r5]
	cmp r0, #0x1b
	bhi _0809CC32
	ldrh r1, [r5, #2]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	ldrh r1, [r5]
	adds r0, r0, r1
	adds r1, r5, #0
	adds r1, #0x1c
	adds r0, r0, r1
	movs r1, #4
	strb r1, [r0]
	ldrb r0, [r5, #0x18]
	adds r0, r0, r6
	strb r0, [r5, #0x18]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r4, r5, #0
	cmp r0, #7
	bls _0809CC32
	adds r2, r4, #0
_0809CBF8:
	ldrb r0, [r2, #0x18]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2, #0x18]
	ldrh r0, [r2]
	adds r0, #1
	strh r0, [r2]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1b
	bhi _0809CC32
	lsls r0, r1, #0x18
	cmp r0, #0
	beq _0809CC2C
	ldrh r1, [r2, #2]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	ldrh r1, [r2]
	adds r0, r0, r1
	adds r1, r2, #0
	adds r1, #0x1c
	adds r0, r0, r1
	movs r1, #4
	strb r1, [r0]
_0809CC2C:
	ldrb r0, [r2, #0x18]
	cmp r0, #7
	bhi _0809CBF8
_0809CC32:
	ldr r1, _0809CC48 @ =gNonGameplayRam
	ldr r0, [r1, #0xc]
	adds r0, #2
	str r0, [r1, #0xc]
_0809CC3A:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809CC44: .4byte 0x06008000
_0809CC48: .4byte gNonGameplayRam

	thumb_func_start unk_9cc4c
unk_9cc4c: @ 0x0809CC4C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	ldr r1, _0809CC8C @ =gNonGameplayRam
	ldrh r6, [r1, #4]
	ldrh r0, [r1, #6]
	lsrs r7, r0, #1
	ldrh r0, [r1, #2]
	lsrs r0, r0, #1
	str r1, [sp, #4]
	cmp r7, r0
	bls _0809CC6C
	b _0809CD70
_0809CC6C:
	str r1, [sp]
_0809CC6E:
	ldr r2, [sp]
	ldr r0, [r2, #0xc]
	ldrh r0, [r0]
	movs r3, #0xfc
	lsls r3, r3, #8
	cmp r0, r3
	bne _0809CC90
	ldrh r0, [r1]
	cmp r0, #0x1b
	bhi _0809CCAA
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov ip, r0
	b _0809CCAE
	.align 2, 0
_0809CC8C: .4byte gNonGameplayRam
_0809CC90:
	ldrh r0, [r1, #2]
	lsrs r0, r0, #1
	cmp r7, r0
	bne _0809CCAA
	ldr r1, [sp]
	ldrh r0, [r1]
	movs r2, #0x1c
	mov ip, r2
	cmp r0, #0x1b
	bhi _0809CCAE
	adds r3, r0, #0
	mov ip, r3
	b _0809CCAE
_0809CCAA:
	movs r5, #0x1c
	mov ip, r5
_0809CCAE:
	adds r0, r7, #1
	str r0, [sp, #8]
	cmp r6, ip
	bhs _0809CD5C
	ldr r1, _0809CD24 @ =gNonGameplayRam
	mov r8, r1
	lsls r0, r7, #3
	subs r0, r0, r7
	lsls r0, r0, #2
	mov sl, r0
	ldr r2, _0809CD28 @ =0x00000FFF
	mov sb, r2
_0809CCC6:
	mov r3, sl
	adds r2, r6, r3
	ldr r5, _0809CD2C @ =0x0300159C
	adds r1, r2, r5
	ldrb r0, [r1]
	cmp r0, #5
	bne _0809CD4E
	movs r0, #0
	strb r0, [r1]
	ldr r0, [sp, #4]
	adds r0, #0x1c
	adds r2, r2, r0
	ldrb r0, [r2]
	subs r1, r0, #1
	strb r1, [r2]
	lsls r0, r1, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0
	ble _0809CD38
	lsls r2, r6, #1
	lsls r0, r7, #7
	adds r2, r2, r0
	ldr r0, _0809CD30 @ =0x0600C842
	adds r0, r2, r0
	str r0, [sp, #0xc]
	ldr r1, _0809CD34 @ =0x0600C882
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
	b _0809CD52
	.align 2, 0
_0809CD24: .4byte gNonGameplayRam
_0809CD28: .4byte 0x00000FFF
_0809CD2C: .4byte 0x0300159C
_0809CD30: .4byte 0x0600C842
_0809CD34: .4byte 0x0600C882
_0809CD38:
	cmp r0, #0
	bne _0809CD46
	lsls r0, r7, #1
	mov r5, r8
	strh r0, [r5, #6]
	strh r6, [r5, #4]
	b _0809CD52
_0809CD46:
	movs r0, #0xff
	orrs r1, r0
	strb r1, [r2]
	b _0809CD5C
_0809CD4E:
	adds r0, #1
	strb r0, [r1]
_0809CD52:
	adds r0, r6, #1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, ip
	blo _0809CCC6
_0809CD5C:
	movs r6, #0
	ldr r1, [sp, #8]
	lsls r0, r1, #0x10
	lsrs r7, r0, #0x10
	ldr r1, [sp, #4]
	ldrh r0, [r1, #2]
	lsrs r0, r0, #1
	cmp r7, r0
	bhi _0809CD70
	b _0809CC6E
_0809CD70:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start CutsceneMonologueFadeIn
CutsceneMonologueFadeIn: @ 0x0809CD80
	push {lr}
	bl CutsceneMonologueProcessOam
	bl CutsceneMonologueDrawAllOam
	ldr r3, _0809CDAC @ =gWrittenToBldy
	ldrh r2, [r3]
	adds r0, r2, #0
	cmp r0, #0
	beq _0809CDD0
	cmp r0, #0xb
	bls _0809CDB4
	ldr r1, _0809CDB0 @ =gNonGameplayRam
	ldrb r0, [r1, #0x16]
	adds r0, #1
	strb r0, [r1, #0x16]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _0809CDD0
	b _0809CDC8
	.align 2, 0
_0809CDAC: .4byte gWrittenToBldy
_0809CDB0: .4byte gNonGameplayRam
_0809CDB4:
	cmp r0, #6
	bls _0809CDCC
	ldr r1, _0809CDD4 @ =gNonGameplayRam
	ldrb r0, [r1, #0x16]
	adds r0, #1
	strb r0, [r1, #0x16]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _0809CDD0
_0809CDC8:
	movs r0, #0
	strb r0, [r1, #0x16]
_0809CDCC:
	subs r0, r2, #1
	strh r0, [r3]
_0809CDD0:
	pop {r0}
	bx r0
	.align 2, 0
_0809CDD4: .4byte gNonGameplayRam

	thumb_func_start CutsceneMonologueFadeOut
CutsceneMonologueFadeOut: @ 0x0809CDD8
	push {lr}
	bl CutsceneMonologueProcessOam
	bl CutsceneMonologueDrawAllOam
	ldr r3, _0809CE04 @ =gWrittenToBldy
	ldrh r2, [r3]
	adds r0, r2, #0
	cmp r0, #0xf
	bhi _0809CE28
	cmp r0, #5
	bhi _0809CE0C
	ldr r1, _0809CE08 @ =gNonGameplayRam
	ldrb r0, [r1, #0x16]
	adds r0, #1
	strb r0, [r1, #0x16]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _0809CE28
	b _0809CE20
	.align 2, 0
_0809CE04: .4byte gWrittenToBldy
_0809CE08: .4byte gNonGameplayRam
_0809CE0C:
	cmp r0, #0xa
	bhi _0809CE24
	ldr r1, _0809CE2C @ =gNonGameplayRam
	ldrb r0, [r1, #0x16]
	adds r0, #1
	strb r0, [r1, #0x16]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _0809CE28
_0809CE20:
	movs r0, #0
	strb r0, [r1, #0x16]
_0809CE24:
	adds r0, r2, #1
	strh r0, [r3]
_0809CE28:
	pop {r0}
	bx r0
	.align 2, 0
_0809CE2C: .4byte gNonGameplayRam

	thumb_func_start CutsceneMonologueProcessOam
CutsceneMonologueProcessOam: @ 0x0809CE30
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _0809CE70 @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r6, r5, r0
_0809CE3C:
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r2, r0, #3
	adds r0, r2, r5
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809CE60
	movs r0, #0x8a
	lsls r0, r0, #2
	adds r1, r5, r0
	adds r1, r2, r1
	adds r0, r2, r6
	ldr r1, [r1]
	bl _call_via_r1
_0809CE60:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #4
	bls _0809CE3C
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809CE70: .4byte gNonGameplayRam

	thumb_func_start CutsceneMonologueDrawAllOam
CutsceneMonologueDrawAllOam: @ 0x0809CE74
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _0809CEB4 @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r6, r5, r0
_0809CE80:
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r1, r0, #3
	adds r0, r1, r5
	ldr r2, _0809CEB8 @ =0x00000219
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809CE98
	adds r0, r1, r6
	bl CutsceneMnologueDrawOam
_0809CE98:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #4
	bls _0809CE80
	bl ResetFreeOam
	ldr r1, _0809CEBC @ =gNextOamSlot
	movs r0, #0
	strb r0, [r1]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809CEB4: .4byte gNonGameplayRam
_0809CEB8: .4byte 0x00000219
_0809CEBC: .4byte gNextOamSlot

	thumb_func_start CutsceneMnologueDrawOam
CutsceneMnologueDrawOam: @ 0x0809CEC0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r5, r0, #0
	ldr r2, _0809CF80 @ =gNextOamSlot
	ldrb r0, [r2]
	lsls r0, r0, #3
	ldr r1, _0809CF84 @ =gOamData
	adds r7, r0, r1
	ldrb r4, [r5, #6]
	lsls r1, r4, #3
	ldr r0, [r5, #0x10]
	adds r3, r0, r1
	ldrb r0, [r3, #4]
	ldrb r2, [r5, #7]
	cmp r0, r2
	bne _0809CEF0
	adds r0, r4, #1
	movs r1, #0
	strb r0, [r5, #6]
	strb r1, [r5, #7]
	adds r3, #8
_0809CEF0:
	ldrb r1, [r3, #4]
	cmp r1, #0
	bne _0809CEFE
	ldrb r0, [r5, #6]
	lsls r0, r0, #3
	subs r3, r3, r0
	strb r1, [r5, #6]
_0809CEFE:
	ldr r6, [r3]
	ldrh r3, [r6]
	mov sl, r3
	adds r6, #2
	movs r4, #0
	mov sb, r4
	cmp sb, sl
	blt _0809CF10
	b _0809D014
_0809CF10:
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
	ldr r2, _0809CF80 @ =gNextOamSlot
	ldrb r0, [r2]
	mov r4, sb
	adds r3, r0, r4
	ldrb r1, [r5, #0xc]
	cmp r1, #1
	bne _0809CF90
	lsls r4, r3, #3
	ldr r0, _0809CF84 @ =gOamData
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
	ldr r2, _0809CF88 @ =sCutsceneUnk_68279c
	adds r1, r1, r2
	ldrb r0, [r1]
	lsls r0, r0, #3
	add r0, ip
	ldrh r1, [r5]
	subs r2, r1, r0
	ldr r3, _0809CF8C @ =0x000001FF
	ands r2, r3
	ldrh r0, [r5, #2]
	mov r3, r8
	adds r1, r3, r0
	movs r0, #0xff
	ands r1, r0
	b _0809CFA6
	.align 2, 0
_0809CF80: .4byte gNextOamSlot
_0809CF84: .4byte gOamData
_0809CF88: .4byte sCutsceneUnk_68279c
_0809CF8C: .4byte 0x000001FF
_0809CF90:
	ldrh r0, [r5, #2]
	mov r4, r8
	adds r1, r4, r0
	movs r0, #0xff
	ands r1, r0
	ldrh r0, [r5]
	mov r4, ip
	adds r2, r4, r0
	ldr r0, _0809D030 @ =0x000001FF
	ands r2, r0
	lsls r4, r3, #3
_0809CFA6:
	ldr r0, _0809D034 @ =gOamData
	adds r3, r4, r0
	strb r1, [r3]
	ldr r1, _0809D030 @ =0x000001FF
	ands r2, r1
	ldrh r1, [r3, #2]
	ldr r0, _0809D038 @ =0xFFFFFE00
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
	ldr r4, _0809D03C @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _0809D040 @ =0xFFFFFC00
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
	bge _0809D014
	b _0809CF10
_0809D014:
	ldr r2, _0809D044 @ =gNextOamSlot
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
_0809D030: .4byte 0x000001FF
_0809D034: .4byte gOamData
_0809D038: .4byte 0xFFFFFE00
_0809D03C: .4byte 0x000003FF
_0809D040: .4byte 0xFFFFFC00
_0809D044: .4byte gNextOamSlot

	thumb_func_start CutsceneMonologueResetOam
CutsceneMonologueResetOam: @ 0x0809D048
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r2, _0809D08C @ =gNonGameplayRam
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	adds r1, r1, r2
	ldr r2, _0809D090 @ =0x0000021A
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _0809D094 @ =0x0000021B
	adds r0, r1, r3
	strb r2, [r0]
	adds r3, #2
	adds r0, r1, r3
	strb r2, [r0]
	adds r3, #1
	adds r0, r1, r3
	strb r2, [r0]
	adds r3, #1
	adds r0, r1, r3
	strb r2, [r0]
	adds r3, #1
	adds r0, r1, r3
	strb r2, [r0]
	adds r3, #1
	adds r0, r1, r3
	strb r2, [r0]
	ldr r0, _0809D098 @ =0x00000222
	adds r1, r1, r0
	strh r2, [r1]
	bx lr
	.align 2, 0
_0809D08C: .4byte gNonGameplayRam
_0809D090: .4byte 0x0000021A
_0809D094: .4byte 0x0000021B
_0809D098: .4byte 0x00000222

	thumb_func_start unk_9d09c
unk_9d09c: @ 0x0809D09C
	bx lr
	.align 2, 0

	thumb_func_start unk_9d0a0
unk_9d0a0: @ 0x0809D0A0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	ldr r1, _0809D0E4 @ =0x040000D4
	ldr r0, _0809D0E8 @ =0x02001000
	str r0, [r1]
	ldr r0, _0809D0EC @ =0x02002000
	str r0, [r1, #4]
	ldr r0, _0809D0F0 @ =0x84000054
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r3, _0809D0F4 @ =gNonGameplayRam
	ldrh r0, [r3, #0xe]
	ldrh r2, [r3, #0xa]
	subs r1, r0, r2
	lsls r1, r1, #0x10
	adds r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r7, r0, #0x10
	lsrs r2, r1, #0x10
	asrs r0, r1, #0x10
	cmp r0, #0
	bge _0809D0F8
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	movs r1, #0xa
	ldrsh r0, [r3, r1]
	lsls r0, r0, #1
	movs r2, #0
	cmp r5, r0
	ble _0809D0FA
	movs r2, #0xa1
	b _0809D0FA
	.align 2, 0
_0809D0E4: .4byte 0x040000D4
_0809D0E8: .4byte 0x02001000
_0809D0EC: .4byte 0x02002000
_0809D0F0: .4byte 0x84000054
_0809D0F4: .4byte gNonGameplayRam
_0809D0F8:
	movs r5, #0
_0809D0FA:
	lsls r0, r7, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x9f
	ble _0809D104
	movs r7, #0xa0
_0809D104:
	ldr r0, _0809D1B8 @ =sHaze_PowerBomb_WindowValuesPointers
	movs r4, #0xa
	ldrsh r1, [r3, r4]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	mov ip, r1
	ldr r4, _0809D1BC @ =0x02001000
	movs r6, #0
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	lsls r2, r7, #0x10
	cmp r6, r0
	bge _0809D138
	movs r7, #0
	adds r1, r0, #0
_0809D124:
	strh r7, [r4]
	adds r4, #2
	lsls r0, r6, #0x10
	movs r3, #0x80
	lsls r3, r3, #9
	adds r0, r0, r3
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r1
	blt _0809D124
_0809D138:
	lsls r0, r6, #0x10
	asrs r1, r2, #0x10
	cmp r0, r2
	bgt _0809D192
	ldr r0, _0809D1C0 @ =gNonGameplayRam
	mov r8, r0
	adds r7, r1, #0
_0809D146:
	lsls r0, r5, #2
	add r0, ip
	mov r2, r8
	ldrh r1, [r2, #0xc]
	ldrh r2, [r0, #2]
	adds r2, r1, r2
	lsls r2, r2, #0x10
	ldrh r0, [r0]
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r3, r1, #0x10
	lsrs r1, r2, #0x10
	cmp r2, #0
	bge _0809D164
	movs r1, #0
_0809D164:
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf0
	ble _0809D16E
	movs r3, #0xf0
_0809D16E:
	lsls r1, r1, #0x10
	asrs r1, r1, #8
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	orrs r0, r1
	strh r0, [r4]
	adds r4, #2
	adds r0, r5, #1
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsls r0, r6, #0x10
	movs r3, #0x80
	lsls r3, r3, #9
	adds r0, r0, r3
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r7
	ble _0809D146
_0809D192:
	lsls r1, r6, #0x10
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	bgt _0809D1AC
	movs r2, #0
_0809D19C:
	strh r2, [r4]
	adds r4, #2
	movs r0, #0x80
	lsls r0, r0, #9
	adds r1, r1, r0
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	ble _0809D19C
_0809D1AC:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809D1B8: .4byte sHaze_PowerBomb_WindowValuesPointers
_0809D1BC: .4byte 0x02001000
_0809D1C0: .4byte gNonGameplayRam

	thumb_func_start unk_9d1c4
unk_9d1c4: @ 0x0809D1C4
	ldr r0, _0809D1D8 @ =0x04000006
	ldrh r0, [r0]
	ldr r1, _0809D1DC @ =0x04000040
	lsls r0, r0, #0x10
	asrs r0, r0, #0xf
	ldr r2, _0809D1E0 @ =0x02002000
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_0809D1D8: .4byte 0x04000006
_0809D1DC: .4byte 0x04000040
_0809D1E0: .4byte 0x02002000

	thumb_func_start CutsceneMonologueDestroyOamOfType
CutsceneMonologueDestroyOamOfType: @ 0x0809D1E4
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r3, #0
	ldr r6, _0809D214 @ =gNonGameplayRam
	movs r7, #2
	rsbs r7, r7, #0
	movs r5, #0
_0809D1F4:
	lsls r0, r3, #3
	adds r0, r0, r3
	lsls r0, r0, #2
	adds r2, r0, r6
	adds r1, r2, #0
	adds r1, #0x28
	ldrb r0, [r1]
	cmp r0, r4
	bne _0809D218
	strb r5, [r1]
	adds r2, #0x2e
	ldrb r1, [r2]
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r2]
	b _0809D222
	.align 2, 0
_0809D214: .4byte gNonGameplayRam
_0809D218:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0xf
	bls _0809D1F4
_0809D222:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start CutsceneFadeIn
CutsceneFadeIn: @ 0x0809D228
	push {lr}
	bl CutsceneProcessOam
	bl CutsceneDrawAllOam
	ldr r1, _0809D244 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _0809D23E
	subs r0, #1
	strh r0, [r1]
_0809D23E:
	pop {r0}
	bx r0
	.align 2, 0
_0809D244: .4byte gWrittenToBldy

	thumb_func_start CutsceneFadeOut
CutsceneFadeOut: @ 0x0809D248
	push {lr}
	bl CutsceneProcessOam
	bl CutsceneDrawAllOam
	ldr r1, _0809D264 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0809D25E
	adds r0, #1
	strh r0, [r1]
_0809D25E:
	pop {r0}
	bx r0
	.align 2, 0
_0809D264: .4byte gWrittenToBldy

	thumb_func_start CutsceneDestroyOamOfType
CutsceneDestroyOamOfType: @ 0x0809D268
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r3, #0
	ldr r6, _0809D298 @ =gNonGameplayRam
	movs r7, #2
	rsbs r7, r7, #0
	movs r5, #0
_0809D278:
	lsls r0, r3, #3
	adds r0, r0, r3
	lsls r0, r0, #2
	adds r2, r0, r6
	adds r1, r2, #0
	adds r1, #0x28
	ldrb r0, [r1]
	cmp r0, r4
	bne _0809D29C
	strb r5, [r1]
	adds r2, #0x2e
	ldrb r1, [r2]
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r2]
	b _0809D2A6
	.align 2, 0
_0809D298: .4byte gNonGameplayRam
_0809D29C:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0xf
	bls _0809D278
_0809D2A6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start CutsceneProcessOam
CutsceneProcessOam: @ 0x0809D2AC
	push {r4, r5, lr}
	ldr r1, _0809D2F0 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0x12]
	movs r5, #0
	adds r4, r1, #0
_0809D2B8:
	lsls r0, r5, #3
	adds r0, r0, r5
	lsls r2, r0, #2
	adds r0, r2, r4
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809D2E0
	adds r1, r4, #0
	adds r1, #0x38
	adds r1, r2, r1
	adds r0, r4, #0
	adds r0, #0x18
	adds r0, r2, r0
	ldr r1, [r1]
	bl _call_via_r1
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
_0809D2E0:
	adds r0, r5, #1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0xf
	bls _0809D2B8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809D2F0: .4byte gNonGameplayRam

	thumb_func_start CutsceneDrawAllOam
CutsceneDrawAllOam: @ 0x0809D2F4
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _0809D334 @ =gNonGameplayRam
	adds r6, r5, #0
	adds r6, #0x18
_0809D2FE:
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r1, r0, #2
	adds r0, r1, r5
	adds r0, #0x2e
	ldrb r0, [r0]
	lsls r0, r0, #0x1f
	cmp r0, #0
	beq _0809D316
	adds r0, r1, r6
	bl CutsceneDrawOam
_0809D316:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0xf
	bls _0809D2FE
	bl ResetFreeOam
	ldr r0, _0809D338 @ =gNextOamSlot
	movs r1, #0
	strb r1, [r0]
	ldr r0, _0809D33C @ =0x03001238
	strb r1, [r0]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809D334: .4byte gNonGameplayRam
_0809D338: .4byte gNextOamSlot
_0809D33C: .4byte 0x03001238

	thumb_func_start CutsceneDrawOam
CutsceneDrawOam: @ 0x0809D340
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x2c
	mov r8, r0
	ldr r3, _0809D438 @ =gNextOamSlot
	ldrb r0, [r3]
	lsls r0, r0, #3
	ldr r2, _0809D43C @ =gOamData
	adds r0, r0, r2
	mov ip, r0
	mov r0, r8
	ldrb r5, [r0, #0x11]
	lsls r1, r5, #3
	ldr r0, [r0, #0x1c]
	adds r4, r0, r1
	ldrb r0, [r4, #4]
	mov r1, r8
	ldrb r1, [r1, #0x12]
	cmp r0, r1
	bne _0809D37A
	adds r0, r5, #1
	movs r1, #0
	mov r2, r8
	strb r0, [r2, #0x11]
	strb r1, [r2, #0x12]
	adds r4, #8
_0809D37A:
	ldrb r1, [r4, #4]
	cmp r1, #0
	bne _0809D38A
	mov r3, r8
	ldrb r0, [r3, #0x11]
	lsls r0, r0, #3
	subs r4, r4, r0
	strb r1, [r3, #0x11]
_0809D38A:
	ldr r4, [r4]
	mov sl, r4
	ldrh r4, [r4]
	str r4, [sp, #0x18]
	movs r0, #2
	add sl, r0
	mov r2, r8
	ldrb r1, [r2, #0x16]
	lsls r0, r1, #0x1d
	lsrs r0, r0, #0x1e
	cmp r0, #0
	beq _0809D3A4
	b _0809D504
_0809D3A4:
	movs r3, #0
	str r3, [sp, #0x14]
	cmp r3, r4
	blt _0809D3AE
	b _0809DB26
_0809D3AE:
	ldr r4, _0809D440 @ =0x000001FF
	adds r6, r4, #0
	movs r0, #3
	mov sb, r0
_0809D3B6:
	mov r1, sl
	ldrh r5, [r1]
	movs r2, #2
	add sl, r2
	mov r3, sl
	ldrh r7, [r3]
	add sl, r2
	mov r4, ip
	strh r5, [r4]
	add ip, r2
	mov r0, ip
	strh r7, [r0]
	add ip, r2
	mov r1, sl
	ldrh r0, [r1]
	mov r2, ip
	strh r0, [r2]
	movs r3, #2
	add sl, r3
	add ip, r3
	ldr r4, _0809D438 @ =gNextOamSlot
	ldrb r0, [r4]
	ldr r1, [sp, #0x14]
	adds r3, r0, r1
	mov r2, r8
	ldrb r0, [r2, #0x16]
	lsls r0, r0, #0x19
	lsrs r1, r0, #0x1f
	cmp r1, #1
	bne _0809D448
	lsls r4, r3, #3
	ldr r3, _0809D43C @ =gOamData
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
	ldr r0, _0809D444 @ =sCutsceneUnk_63a184
	adds r1, r1, r0
	ldrb r0, [r1]
	lsls r0, r0, #3
	adds r0, r7, r0
	mov r2, r8
	ldrh r1, [r2]
	subs r0, r1, r0
	ands r0, r6
	str r0, [sp]
	ldrh r0, [r2, #2]
	adds r5, r5, r0
	movs r0, #0xff
	ands r5, r0
	str r5, [sp, #4]
	b _0809D45E
	.align 2, 0
_0809D438: .4byte gNextOamSlot
_0809D43C: .4byte gOamData
_0809D440: .4byte 0x000001FF
_0809D444: .4byte sCutsceneUnk_63a184
_0809D448:
	mov r4, r8
	ldrh r0, [r4, #2]
	adds r5, r5, r0
	movs r0, #0xff
	ands r5, r0
	str r5, [sp, #4]
	ldrh r0, [r4]
	adds r0, r7, r0
	ands r0, r6
	str r0, [sp]
	lsls r4, r3, #3
_0809D45E:
	ldr r0, _0809D4F4 @ =gOamData
	adds r3, r4, r0
	mov r1, sp
	ldrb r1, [r1, #4]
	strb r1, [r3]
	ldr r2, [sp]
	ands r2, r6
	ldrh r1, [r3, #2]
	ldr r0, _0809D4F8 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r3, #2]
	mov r4, r8
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	mov r1, sb
	ands r0, r1
	lsls r0, r0, #2
	ldrb r2, [r3, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #5]
	lsrs r2, r1, #4
	ldrb r0, [r4, #0x18]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r3, #5]
	ldrh r5, [r3, #4]
	lsls r2, r5, #0x16
	lsrs r2, r2, #0x16
	ldrb r4, [r4, #0x17]
	mov r1, r8
	ldrb r0, [r1, #0x18]
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #8
	orrs r0, r4
	adds r2, r2, r0
	ldr r4, _0809D4FC @ =0x000003FF
	adds r0, r4, #0
	ands r2, r0
	ldr r0, _0809D500 @ =0xFFFFFC00
	ands r0, r5
	orrs r0, r2
	strh r0, [r3, #4]
	mov r0, r8
	ldrb r1, [r0, #0x16]
	lsls r1, r1, #0x1b
	lsrs r1, r1, #0x1e
	mov r2, sb
	ands r1, r2
	lsls r1, r1, #2
	ldrb r2, [r3, #1]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x14]
	adds r4, #1
	str r4, [sp, #0x14]
	ldr r0, [sp, #0x18]
	cmp r4, r0
	bge _0809D4F2
	b _0809D3B6
_0809D4F2:
	b _0809DB26
	.align 2, 0
_0809D4F4: .4byte gOamData
_0809D4F8: .4byte 0xFFFFFE00
_0809D4FC: .4byte 0x000003FF
_0809D500: .4byte 0xFFFFFC00
_0809D504:
	cmp r0, #1
	beq _0809D50A
	b _0809D7D4
_0809D50A:
	mov r2, r8
	ldrh r0, [r2]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r2, #2]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _0809D52C
	ldrh r3, [r2, #4]
	str r3, [sp, #0xc]
	b _0809D538
_0809D52C:
	mov r4, r8
	ldrh r0, [r4, #4]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0xc]
_0809D538:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _0809D544
	mov r0, r8
	ldrh r0, [r0, #4]
	b _0809D54E
_0809D544:
	mov r1, r8
	ldrh r0, [r1, #4]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
_0809D54E:
	str r0, [sp, #0x10]
	movs r2, #0
	b _0809D782
_0809D554:
	mov r4, sl
	ldrh r5, [r4]
	movs r0, #2
	add sl, r0
	mov r1, sl
	ldrh r7, [r1]
	add sl, r0
	mov r2, ip
	strh r5, [r2]
	add ip, r0
	mov r3, ip
	strh r7, [r3]
	add ip, r0
	mov r4, sl
	ldrh r0, [r4]
	mov r1, ip
	strh r0, [r1]
	movs r2, #2
	add sl, r2
	add ip, r2
	ldr r3, _0809D7AC @ =gNextOamSlot
	ldrb r0, [r3]
	ldr r4, [sp, #0x14]
	adds r3, r0, r4
	lsls r0, r3, #3
	ldr r1, _0809D7B0 @ =gOamData
	adds r6, r0, r1
	ldrb r2, [r6, #3]
	mov sb, r2
	mov r3, sb
	lsrs r1, r3, #6
	ldrb r0, [r6, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r4, _0809D7B4 @ =sCutsceneUnk_63a184
	adds r0, r1, r4
	ldrb r2, [r0]
	ldr r0, _0809D7B8 @ =sCutsceneUnk_63a190
	adds r1, r1, r0
	ldrb r3, [r1]
	ldr r1, [sp, #4]
	adds r5, r5, r1
	movs r0, #0xff
	ands r5, r0
	ldr r0, [sp]
	adds r4, r7, r0
	ldr r1, _0809D7BC @ =0x000001FF
	adds r0, r1, #0
	ands r4, r0
	ldr r0, [sp]
	subs r1, r4, r0
	lsls r2, r2, #2
	str r2, [sp, #0x1c]
	adds r1, r2, r1
	ldr r0, [sp, #4]
	subs r2, r5, r0
	lsls r3, r3, #2
	str r3, [sp, #0x20]
	adds r2, r3, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0xc]
	lsls r0, r3, #0x10
	asrs r3, r0, #0x10
	adds r0, r1, #0
	muls r0, r3, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #8]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r1, [sp, #0x10]
	lsls r0, r1, #0x10
	asrs r7, r0, #0x10
	adds r0, r2, #0
	muls r0, r7, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	mov r1, sb
	lsls r0, r1, #0x1b
	cmp r0, #0
	bge _0809D612
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r6, #3]
	rsbs r0, r3, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0xc]
_0809D612:
	ldrb r1, [r6, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _0809D62A
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r6, #3]
	rsbs r0, r7, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
_0809D62A:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #8]
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r5, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r5, r1, #0x10
	ldr r0, [sp]
	subs r4, r4, r0
	ldr r1, [sp, #0x1c]
	adds r4, r1, r4
	ldr r2, [sp, #4]
	subs r3, r5, r2
	ldr r0, [sp, #0x20]
	adds r3, r0, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r2, r8
	ldrb r1, [r2, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _0809D7C0 @ =sSineTable
	adds r0, r0, r2
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _0809D7C0 @ =sSineTable
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
	ldr r1, [sp, #0x1c]
	subs r2, r2, r1
	asrs r0, r0, #0x10
	ldr r3, [sp, #0x20]
	subs r0, r0, r3
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	ldr r4, [sp, #4]
	adds r0, r5, r4
	subs r0, #0x40
	strb r0, [r6]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r0, [sp]
	adds r2, r2, r0
	subs r2, #0x40
	ldr r0, _0809D7BC @ =0x000001FF
	ands r2, r0
	ldrh r1, [r6, #2]
	ldr r0, _0809D7C4 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r6, #2]
	ldrb r1, [r6, #1]
	movs r0, #4
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r6, #1]
	ldr r2, _0809D7C8 @ =0x03001238
	ldrb r1, [r2]
	movs r2, #0x10
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0809D6E8
	ldrb r0, [r6, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r6, #3]
_0809D6E8:
	ldr r3, _0809D7C8 @ =0x03001238
	ldrb r1, [r3]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0809D6FA
	ldrb r0, [r6, #3]
	orrs r0, r2
	strb r0, [r6, #3]
_0809D6FA:
	ldr r4, _0809D7C8 @ =0x03001238
	ldrb r0, [r4]
	movs r1, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r6, #3]
	movs r0, #0xf
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r6, #3]
	mov r1, r8
	ldrb r0, [r1, #0x18]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	movs r2, #3
	ands r0, r2
	lsls r0, r0, #2
	ldrb r2, [r6, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r6, #5]
	lsrs r2, r1, #4
	mov r3, r8
	ldrb r0, [r3, #0x18]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r6, #5]
	ldrh r4, [r6, #4]
	lsls r2, r4, #0x16
	lsrs r2, r2, #0x16
	ldrb r3, [r3, #0x17]
	mov r1, r8
	ldrb r0, [r1, #0x18]
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #8
	orrs r0, r3
	adds r2, r2, r0
	ldr r3, _0809D7CC @ =0x000003FF
	adds r0, r3, #0
	ands r2, r0
	ldr r0, _0809D7D0 @ =0xFFFFFC00
	ands r0, r4
	orrs r0, r2
	strh r0, [r6, #4]
	mov r4, r8
	ldrb r1, [r4, #0x16]
	lsls r1, r1, #0x1b
	lsrs r1, r1, #0x1e
	movs r0, #3
	ands r1, r0
	lsls r1, r1, #2
	ldrb r2, [r6, #1]
	subs r0, #0x10
	ands r0, r2
	orrs r0, r1
	strb r0, [r6, #1]
	movs r1, #2
	add ip, r1
	ldr r2, [sp, #0x14]
	adds r2, #1
_0809D782:
	str r2, [sp, #0x14]
	ldr r3, [sp, #0x18]
	cmp r2, r3
	bge _0809D78C
	b _0809D554
_0809D78C:
	ldr r4, _0809D7C8 @ =0x03001238
	ldrb r0, [r4]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r1, r8
	ldrb r0, [r1, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _0809D7C0 @ =sSineTable
	adds r0, r0, r2
	movs r3, #0
	ldrsh r5, [r0, r3]
	ldr r0, [sp, #0xc]
	lsls r4, r0, #0x10
	b _0809DA7E
	.align 2, 0
_0809D7AC: .4byte gNextOamSlot
_0809D7B0: .4byte gOamData
_0809D7B4: .4byte sCutsceneUnk_63a184
_0809D7B8: .4byte sCutsceneUnk_63a190
_0809D7BC: .4byte 0x000001FF
_0809D7C0: .4byte sSineTable
_0809D7C4: .4byte 0xFFFFFE00
_0809D7C8: .4byte 0x03001238
_0809D7CC: .4byte 0x000003FF
_0809D7D0: .4byte 0xFFFFFC00
_0809D7D4:
	cmp r0, #3
	beq _0809D7DA
	b _0809DB26
_0809D7DA:
	mov r3, r8
	ldrh r0, [r3]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r3, #2]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _0809D7FC
	ldrh r4, [r3, #4]
	str r4, [sp, #0xc]
	b _0809D808
_0809D7FC:
	mov r2, r8
	ldrh r0, [r2, #4]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0xc]
_0809D808:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _0809D816
	mov r3, r8
	ldrh r3, [r3, #4]
	str r3, [sp, #0x10]
	b _0809D822
_0809D816:
	mov r4, r8
	ldrh r0, [r4, #4]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
_0809D822:
	movs r0, #0
	str r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	cmp r0, r1
	blt _0809D82E
	b _0809DA62
_0809D82E:
	mov r2, sl
	ldrh r5, [r2]
	movs r3, #2
	add sl, r3
	mov r4, sl
	ldrh r7, [r4]
	add sl, r3
	mov r0, ip
	strh r5, [r0]
	add ip, r3
	mov r1, ip
	strh r7, [r1]
	add ip, r3
	mov r2, sl
	ldrh r0, [r2]
	mov r3, ip
	strh r0, [r3]
	movs r4, #2
	add sl, r4
	add ip, r4
	ldr r1, _0809DB48 @ =gNextOamSlot
	ldrb r0, [r1]
	ldr r2, [sp, #0x14]
	adds r3, r0, r2
	lsls r0, r3, #3
	ldr r3, _0809DB4C @ =gOamData
	adds r6, r0, r3
	ldrb r4, [r6, #3]
	mov sb, r4
	mov r0, sb
	lsrs r1, r0, #6
	ldrb r0, [r6, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r2, _0809DB50 @ =sCutsceneUnk_63a184
	adds r0, r1, r2
	ldrb r2, [r0]
	ldr r3, _0809DB54 @ =sCutsceneUnk_63a190
	adds r1, r1, r3
	ldrb r3, [r1]
	ldr r4, [sp, #4]
	adds r5, r5, r4
	movs r0, #0xff
	ands r5, r0
	ldr r0, [sp]
	adds r4, r7, r0
	ldr r1, _0809DB58 @ =0x000001FF
	adds r0, r1, #0
	ands r4, r0
	ldr r0, [sp]
	subs r1, r4, r0
	lsls r2, r2, #2
	str r2, [sp, #0x24]
	adds r1, r2, r1
	ldr r0, [sp, #4]
	subs r2, r5, r0
	lsls r3, r3, #2
	str r3, [sp, #0x28]
	adds r2, r3, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0xc]
	lsls r0, r3, #0x10
	asrs r3, r0, #0x10
	adds r0, r1, #0
	muls r0, r3, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #8]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r1, [sp, #0x10]
	lsls r0, r1, #0x10
	asrs r7, r0, #0x10
	adds r0, r2, #0
	muls r0, r7, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	mov r1, sb
	lsls r0, r1, #0x1b
	cmp r0, #0
	bge _0809D8EC
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r6, #3]
	rsbs r0, r3, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0xc]
_0809D8EC:
	ldrb r1, [r6, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _0809D904
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r6, #3]
	rsbs r0, r7, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
_0809D904:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #8]
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r5, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r5, r1, #0x10
	ldr r0, [sp]
	subs r4, r4, r0
	ldr r1, [sp, #0x24]
	adds r4, r1, r4
	ldr r2, [sp, #4]
	subs r3, r5, r2
	ldr r0, [sp, #0x28]
	adds r3, r0, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r2, r8
	ldrb r1, [r2, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _0809DB5C @ =sSineTable
	adds r0, r0, r2
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _0809DB5C @ =sSineTable
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
	ldr r3, [sp, #0x24]
	lsls r1, r3, #1
	asrs r2, r2, #0x10
	subs r2, r2, r1
	ldr r4, [sp, #0x28]
	lsls r1, r4, #1
	asrs r0, r0, #0x10
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	ldr r1, [sp, #4]
	adds r0, r5, r1
	subs r0, #0x40
	strb r0, [r6]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r3, [sp]
	adds r2, r2, r3
	subs r2, #0x40
	ldr r0, _0809DB58 @ =0x000001FF
	ands r2, r0
	ldrh r1, [r6, #2]
	ldr r0, _0809DB60 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r6, #2]
	ldrb r0, [r6, #1]
	movs r5, #3
	orrs r0, r5
	strb r0, [r6, #1]
	ldr r4, _0809DB64 @ =0x03001238
	ldrb r1, [r4]
	movs r2, #0x10
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0809D9C0
	ldrb r0, [r6, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r6, #3]
_0809D9C0:
	ldr r0, _0809DB64 @ =0x03001238
	ldrb r1, [r0]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0809D9D2
	ldrb r0, [r6, #3]
	orrs r0, r2
	strb r0, [r6, #3]
_0809D9D2:
	ldr r1, _0809DB64 @ =0x03001238
	ldrb r0, [r1]
	movs r1, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r6, #3]
	movs r0, #0xf
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r6, #3]
	mov r2, r8
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	ands r0, r5
	lsls r0, r0, #2
	ldrb r2, [r6, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r6, #5]
	lsrs r2, r1, #4
	mov r3, r8
	ldrb r0, [r3, #0x18]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r6, #5]
	ldrh r4, [r6, #4]
	lsls r2, r4, #0x16
	lsrs r2, r2, #0x16
	ldrb r3, [r3, #0x17]
	mov r1, r8
	ldrb r0, [r1, #0x18]
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #8
	orrs r0, r3
	adds r2, r2, r0
	ldr r3, _0809DB68 @ =0x000003FF
	adds r0, r3, #0
	ands r2, r0
	ldr r0, _0809DB6C @ =0xFFFFFC00
	ands r0, r4
	orrs r0, r2
	strh r0, [r6, #4]
	mov r4, r8
	ldrb r1, [r4, #0x16]
	lsls r1, r1, #0x1b
	lsrs r1, r1, #0x1e
	ands r1, r5
	lsls r1, r1, #2
	ldrb r2, [r6, #1]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r6, #1]
	movs r0, #2
	add ip, r0
	ldr r1, [sp, #0x14]
	adds r1, #1
	str r1, [sp, #0x14]
	ldr r2, [sp, #0x18]
	cmp r1, r2
	bge _0809DA62
	b _0809D82E
_0809DA62:
	ldr r3, _0809DB64 @ =0x03001238
	ldrb r0, [r3]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r4, r8
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r1, _0809DB5C @ =sSineTable
	adds r0, r0, r1
	movs r2, #0
	ldrsh r5, [r0, r2]
	ldr r3, [sp, #0xc]
	lsls r4, r3, #0x10
_0809DA7E:
	asrs r4, r4, #0x10
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	ldr r6, _0809DB4C @ =gOamData
	lsls r1, r7, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r1, r8
	ldrb r0, [r1, #0x15]
	lsls r0, r0, #1
	ldr r2, _0809DB5C @ =sSineTable
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
	mov r4, r8
	ldrb r0, [r4, #0x15]
	lsls r0, r0, #1
	ldr r1, _0809DB5C @ =sSineTable
	adds r0, r0, r1
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	ldr r2, [sp, #0x10]
	lsls r5, r2, #0x10
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
	mov r3, r8
	ldrb r0, [r3, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r4, _0809DB5C @ =sSineTable
	adds r0, r0, r4
	movs r1, #0
	ldrsh r4, [r0, r1]
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
	ldr r2, _0809DB64 @ =0x03001238
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
_0809DB26:
	ldr r0, _0809DB48 @ =gNextOamSlot
	ldrb r1, [r0]
	ldr r3, [sp, #0x18]
	adds r1, r1, r3
	strb r1, [r0]
	mov r4, r8
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	add sp, #0x2c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809DB48: .4byte gNextOamSlot
_0809DB4C: .4byte gOamData
_0809DB50: .4byte sCutsceneUnk_63a184
_0809DB54: .4byte sCutsceneUnk_63a190
_0809DB58: .4byte 0x000001FF
_0809DB5C: .4byte sSineTable
_0809DB60: .4byte 0xFFFFFE00
_0809DB64: .4byte 0x03001238
_0809DB68: .4byte 0x000003FF
_0809DB6C: .4byte 0xFFFFFC00

	thumb_func_start unk_9db70
unk_9db70: @ 0x0809DB70
	bx lr
	.align 2, 0
