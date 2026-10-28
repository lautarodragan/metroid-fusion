    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start unk_9209c
unk_9209c: @ 0x0809209C
	push {r4, r5, lr}
	sub sp, #4
	ldr r3, _080921B4 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080921B8 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080921BC @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080921C0 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080921C4 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080921C8 @ =unk_99940
	bl CallbackSetVBlank
	movs r0, #0
	str r0, [sp]
	ldr r1, _080921CC @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _080921D0 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _080921D4 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r4, #0
	ldr r5, _080921D8 @ =sIntroSamusSittingBgGfxPointers
_080920DC:
	lsls r0, r4, #2
	adds r0, r0, r5
	ldr r0, [r0]
	lsls r1, r4, #0xc
	ldr r2, _080921DC @ =0x06008000
	adds r1, r1, r2
	bl LZ77UncompVram
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #4
	bls _080920DC
	ldr r0, _080921E0 @ =sIntroUnk_658be0
	ldr r1, _080921E4 @ =0x0600E800
	bl LZ77UncompVram
	ldr r0, _080921E8 @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _080921EC @ =0x0600E000
	bl LZ77UncompVram
	ldr r4, _080921CC @ =0x040000D4
	ldr r0, _080921F0 @ =sIntroUnk_6591e4
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080921F4 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080921F8 @ =0x04000010
	movs r3, #0
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	ldr r0, _080921FC @ =0x0300122C
	movs r1, #8
	strh r1, [r0]
	ldr r0, _08092200 @ =0x0300122E
	strh r1, [r0]
	ldr r0, _08092204 @ =0x03001230
	strh r1, [r0]
	ldr r0, _08092208 @ =0x03001232
	strh r1, [r0]
	ldr r1, _0809220C @ =0x04000008
	ldr r2, _08092210 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08092214 @ =0x00001D08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x46
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08092218 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _0809221C @ =0x04000054
	strh r1, [r0]
	ldr r0, _08092220 @ =gWrittenToBldalpha_Eva
	ldr r2, _08092224 @ =gWrittenToBldalpha_Evb
	strh r3, [r0]
	strh r1, [r2]
	ldr r0, _08092228 @ =0x04000052
	lsls r1, r1, #8
	strh r1, [r0]
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _080921D0 @ =gNonGameplayRam
	ldr r0, _0809222C @ =sCutsceneTextNone
	str r0, [r1]
	movs r0, #0
	str r0, [sp]
	mov r0, sp
	str r0, [r4]
	ldr r0, _08092230 @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08092234 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0x98
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08092238 @ =unk_93884
	bl CallbackSetVBlank
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080921B4: .4byte 0x04000208
_080921B8: .4byte 0x04000004
_080921BC: .4byte 0x0000FFEF
_080921C0: .4byte 0x04000200
_080921C4: .4byte 0x0000FFFD
_080921C8: .4byte unk_99940
_080921CC: .4byte 0x040000D4
_080921D0: .4byte gNonGameplayRam
_080921D4: .4byte 0x85000150
_080921D8: .4byte sIntroSamusSittingBgGfxPointers
_080921DC: .4byte 0x06008000
_080921E0: .4byte sIntroUnk_658be0
_080921E4: .4byte 0x0600E800
_080921E8: .4byte sIntroSamusShipFlyingTextTilemap
_080921EC: .4byte 0x0600E000
_080921F0: .4byte sIntroUnk_6591e4
_080921F4: .4byte 0x84000080
_080921F8: .4byte 0x04000010
_080921FC: .4byte 0x0300122C
_08092200: .4byte 0x0300122E
_08092204: .4byte 0x03001230
_08092208: .4byte 0x03001232
_0809220C: .4byte 0x04000008
_08092210: .4byte 0x00001C08
_08092214: .4byte 0x00001D08
_08092218: .4byte gWrittenToBldy
_0809221C: .4byte 0x04000054
_08092220: .4byte gWrittenToBldalpha_Eva
_08092224: .4byte gWrittenToBldalpha_Evb
_08092228: .4byte 0x04000052
_0809222C: .4byte sCutsceneTextNone
_08092230: .4byte 0x0600D000
_08092234: .4byte 0x85000400
_08092238: .4byte unk_93884

	thumb_func_start IntroSamusInShipProcess
IntroSamusInShipProcess: @ 0x0809223C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	movs r7, #0
	ldr r2, _0809226C @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r5, #0x85
	lsls r5, r5, #2
	adds r0, r2, r5
	ldrb r0, [r0]
	adds r3, r2, #0
	cmp r0, #6
	bls _08092260
	b _080924C2
_08092260:
	lsls r0, r0, #2
	ldr r1, _08092270 @ =_08092274
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0809226C: .4byte gNonGameplayRam
_08092270: .4byte _08092274
_08092274: @ jump table
	.4byte _08092290 @ case 0
	.4byte _08092354 @ case 1
	.4byte _080923E8 @ case 2
	.4byte _08092426 @ case 3
	.4byte _0809244C @ case 4
	.4byte _08092460 @ case 5
	.4byte _08092490 @ case 6
_08092290:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r4, r3, r0
	ldrh r0, [r4]
	cmp r0, #5
	bhi _080922BC
	ldr r2, _080922B4 @ =sIntroSamusSittingBgGfxPointers
	adds r1, r0, #0
	subs r1, #1
	lsls r0, r1, #2
	adds r0, r0, r2
	ldr r0, [r0]
	lsls r1, r1, #0xc
	ldr r2, _080922B8 @ =0x06008000
	adds r1, r1, r2
	bl LZ77UncompVram
	b _08092480
	.align 2, 0
_080922B4: .4byte sIntroSamusSittingBgGfxPointers
_080922B8: .4byte 0x06008000
_080922BC:
	cmp r0, #6
	bne _08092320
	ldr r0, _080922F8 @ =sIntroUnk_658be0
	ldr r1, _080922FC @ =0x0600E800
	bl LZ77UncompVram
	ldr r1, _08092300 @ =0x040000D4
	ldr r0, _08092304 @ =sIntroUnk_6591e4
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08092308 @ =0x84000040
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0809230C @ =gWrittenToBldalpha_Eva
	movs r1, #0
	strh r1, [r0]
	ldr r2, _08092310 @ =gWrittenToBldalpha_Evb
	movs r0, #0x10
	strh r0, [r2]
	ldr r0, _08092314 @ =0x04000014
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldr r1, _08092318 @ =0x0400000A
	ldr r5, _0809231C @ =0x00001D08
	adds r0, r5, #0
	strh r0, [r1]
	b _08092480
	.align 2, 0
_080922F8: .4byte sIntroUnk_658be0
_080922FC: .4byte 0x0600E800
_08092300: .4byte 0x040000D4
_08092304: .4byte sIntroUnk_6591e4
_08092308: .4byte 0x84000040
_0809230C: .4byte gWrittenToBldalpha_Eva
_08092310: .4byte gWrittenToBldalpha_Evb
_08092314: .4byte 0x04000014
_08092318: .4byte 0x0400000A
_0809231C: .4byte 0x00001D08
_08092320:
	cmp r0, #7
	beq _08092326
	b _08092480
_08092326:
	ldr r1, _0809234C @ =0x04000050
	ldr r2, _08092350 @ =0x00003842
	adds r0, r2, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r5, #0x80
	lsls r5, r5, #2
	adds r1, r5, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #1
	b _0809247E
	.align 2, 0
_0809234C: .4byte 0x04000050
_08092350: .4byte 0x00003842
_08092354:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	ldrh r0, [r1]
	cmp r0, #1
	beq _08092362
	b _08092480
_08092362:
	movs r0, #0
	strh r0, [r1]
	ldr r6, _080923AC @ =gWrittenToBldalpha_Evb
	ldrh r0, [r6]
	cmp r0, #0
	beq _080923C0
	cmp r0, #0x10
	bne _080923A2
	ldr r5, _080923B0 @ =sMusicTrackDataRom
	ldr r4, _080923B4 @ =sSoundDataEntries
	ldr r1, _080923B8 @ =0x00000F64
	adds r0, r4, r1
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	movs r1, #0xa
	bl ApplyMusicSoundFading
	ldr r2, _080923BC @ =0x00000F6C
	adds r4, r4, r2
	ldrh r1, [r4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	movs r1, #0xa
	bl ApplyMusicSoundFading
_080923A2:
	ldrh r0, [r6]
	subs r0, #2
	strh r0, [r6]
	b _08092480
	.align 2, 0
_080923AC: .4byte gWrittenToBldalpha_Evb
_080923B0: .4byte sMusicTrackDataRom
_080923B4: .4byte sSoundDataEntries
_080923B8: .4byte 0x00000F64
_080923BC: .4byte 0x00000F6C
_080923C0:
	str r0, [sp]
	ldr r1, _080923E0 @ =0x040000D4
	mov r5, sp
	str r5, [r1]
	movs r2, #0x87
	lsls r2, r2, #2
	adds r0, r3, r2
	str r0, [r1, #4]
	ldr r0, _080923E4 @ =0x850000B4
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r5, #0x85
	lsls r5, r5, #2
	adds r1, r3, r5
	movs r0, #2
	b _0809247E
	.align 2, 0
_080923E0: .4byte 0x040000D4
_080923E4: .4byte 0x850000B4
_080923E8:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #1
	bne _08092480
	movs r0, #0
	strh r0, [r1]
	ldr r4, _08092414 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r4]
	cmp r0, #0xf
	bhi _0809241C
	cmp r0, #0
	bne _0809240C
	ldr r0, _08092418 @ =0x000001EB
	movs r1, #0
	bl PlayFadingSound
_0809240C:
	ldrh r0, [r4]
	adds r0, #1
	strh r0, [r4]
	b _08092480
	.align 2, 0
_08092414: .4byte gWrittenToBldalpha_Eva
_08092418: .4byte 0x000001EB
_0809241C:
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #3
	b _0809247E
_08092426:
	movs r5, #0x84
	lsls r5, r5, #2
	adds r1, r3, r5
	ldrh r0, [r1]
	cmp r0, #0x28
	bne _08092480
	movs r2, #0
	strh r2, [r1]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #4
	strb r0, [r1]
	ldr r0, _08092448 @ =gWrittenToBldy
	strh r2, [r0]
	b _08092480
	.align 2, 0
_08092448: .4byte gWrittenToBldy
_0809244C:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #0
	strh r0, [r1]
	movs r5, #0x85
	lsls r5, r5, #2
	adds r1, r3, r5
	movs r0, #5
	b _0809247E
_08092460:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #1
	bne _08092480
	movs r0, #0
	strh r0, [r1]
	ldr r1, _0809248C @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #6
_0809247E:
	strb r0, [r1]
_08092480:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _080924C2
	.align 2, 0
_0809248C: .4byte 0x04000050
_08092490:
	ldr r1, _080924A0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080924A4
	adds r0, #2
	strh r0, [r1]
	b _080924BA
	.align 2, 0
_080924A0: .4byte gWrittenToBldy
_080924A4:
	movs r5, #0x84
	lsls r5, r5, #2
	adds r1, r3, r5
	movs r2, #0
	movs r0, #0
	strh r0, [r1]
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r3, r1
	strb r2, [r0]
	movs r7, #1
_080924BA:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080924C2:
	bl IntroProcessText
	adds r0, r7, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start IntroShipAlertInit
IntroShipAlertInit: @ 0x080924D0
	push {r4, r5, lr}
	sub sp, #4
	ldr r3, _080926A0 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080926A4 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080926A8 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080926AC @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080926B0 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080926B4 @ =unk_99940
	bl CallbackSetVBlank
	movs r0, #0
	str r0, [sp]
	ldr r1, _080926B8 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _080926BC @ =0x030016A0
	str r0, [r1, #4]
	ldr r0, _080926C0 @ =0x850000B4
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r4, #0
	ldr r5, _080926C4 @ =sIntroUnk_79c45c
_08092510:
	lsls r0, r4, #2
	adds r0, r0, r5
	ldr r0, [r0]
	lsls r1, r4, #0xc
	ldr r2, _080926C8 @ =0x06010000
	adds r1, r1, r2
	bl LZ77UncompVram
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #5
	bls _08092510
	ldr r1, _080926B8 @ =0x040000D4
	ldr r0, _080926CC @ =sIntroUnk_65c268
	str r0, [r1]
	ldr r0, _080926D0 @ =0x05000200
	str r0, [r1, #4]
	ldr r0, _080926D4 @ =0x84000080
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r4, #0
	ldr r5, _080926D8 @ =sIntroUnk_79c448
_0809253E:
	lsls r0, r4, #2
	adds r0, r0, r5
	ldr r0, [r0]
	lsls r1, r4, #0xc
	movs r3, #0xc0
	lsls r3, r3, #0x13
	adds r1, r1, r3
	bl LZ77UncompVram
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #4
	bls _0809253E
	ldr r0, _080926DC @ =sIntroUnk_6593e4
	ldr r1, _080926E0 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _080926E4 @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _080926E8 @ =0x0600E000
	bl LZ77UncompVram
	ldr r4, _080926B8 @ =0x040000D4
	ldr r0, _080926EC @ =sIntroUnk_6599a4
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080926F0 @ =0x84000040
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080926F4 @ =0x04000010
	movs r1, #0
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
	ldr r0, _080926F8 @ =0x0300122C
	strh r1, [r0]
	ldr r0, _080926FC @ =0x0300122E
	strh r1, [r0]
	ldr r0, _08092700 @ =0x03001230
	strh r1, [r0]
	ldr r0, _08092704 @ =0x03001232
	strh r1, [r0]
	ldr r2, _08092708 @ =0x04000008
	ldr r3, _0809270C @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r2]
	adds r2, #2
	ldr r3, _08092710 @ =0x00001E01
	adds r0, r3, #0
	strh r0, [r2]
	adds r2, #2
	ldr r3, _08092714 @ =0x00001F02
	adds r0, r3, #0
	strh r0, [r2]
	adds r2, #0x44
	movs r0, #0xff
	strh r0, [r2]
	ldr r0, _08092718 @ =gWrittenToBldy
	movs r2, #0x10
	strh r2, [r0]
	ldr r0, _0809271C @ =0x04000054
	strh r2, [r0]
	ldr r2, _08092720 @ =gWrittenToBldalpha_Eva
	ldr r0, _08092724 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	strh r1, [r2]
	ldr r0, _08092728 @ =0x04000052
	movs r5, #0
	strh r5, [r0]
	movs r0, #0x13
	movs r1, #0x60
	movs r2, #0x80
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0x14
	movs r1, #0x80
	movs r2, #0x60
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0x15
	movs r1, #0x80
	movs r2, #0x80
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0x16
	movs r1, #0xc8
	movs r2, #0x26
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0x17
	movs r1, #0xd2
	movs r2, #0x58
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0x18
	movs r1, #0xd2
	movs r2, #0x58
	movs r3, #0xd2
	bl IntroSetupBigNumberOam
	movs r0, #0x19
	movs r1, #0x43
	movs r2, #0x97
	movs r3, #0xc8
	bl IntroSetupBigNumberOam
	movs r0, #0x1a
	movs r1, #0x2c
	movs r2, #0x98
	movs r3, #0xc8
	bl IntroSetupBigNumberOam
	movs r0, #0x1b
	movs r1, #0x25
	movs r2, #0x98
	movs r3, #0xc8
	bl IntroSetupBigNumberOam
	movs r0, #0x1c
	movs r1, #0x45
	movs r2, #0x7d
	movs r3, #0xc8
	bl IntroSetupBigNumberOam
	movs r0, #0x1d
	movs r1, #0x3e
	movs r2, #0x7d
	movs r3, #0xc8
	bl IntroSetupBigNumberOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _0809272C @ =gNonGameplayRam
	ldr r0, _08092730 @ =sCutsceneTextNone
	str r0, [r1]
	str r5, [sp]
	mov r0, sp
	str r0, [r4]
	ldr r0, _08092734 @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08092738 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0x98
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _0809273C @ =IntroShipAlertAndDraftingVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080926A0: .4byte 0x04000208
_080926A4: .4byte 0x04000004
_080926A8: .4byte 0x0000FFEF
_080926AC: .4byte 0x04000200
_080926B0: .4byte 0x0000FFFD
_080926B4: .4byte unk_99940
_080926B8: .4byte 0x040000D4
_080926BC: .4byte 0x030016A0
_080926C0: .4byte 0x850000B4
_080926C4: .4byte sIntroUnk_79c45c
_080926C8: .4byte 0x06010000
_080926CC: .4byte sIntroUnk_65c268
_080926D0: .4byte 0x05000200
_080926D4: .4byte 0x84000080
_080926D8: .4byte sIntroUnk_79c448
_080926DC: .4byte sIntroUnk_6593e4
_080926E0: .4byte 0x0600F000
_080926E4: .4byte sIntroSamusShipFlyingTextTilemap
_080926E8: .4byte 0x0600E000
_080926EC: .4byte sIntroUnk_6599a4
_080926F0: .4byte 0x84000040
_080926F4: .4byte 0x04000010
_080926F8: .4byte 0x0300122C
_080926FC: .4byte 0x0300122E
_08092700: .4byte 0x03001230
_08092704: .4byte 0x03001232
_08092708: .4byte 0x04000008
_0809270C: .4byte 0x00001C08
_08092710: .4byte 0x00001E01
_08092714: .4byte 0x00001F02
_08092718: .4byte gWrittenToBldy
_0809271C: .4byte 0x04000054
_08092720: .4byte gWrittenToBldalpha_Eva
_08092724: .4byte gWrittenToBldalpha_Evb
_08092728: .4byte 0x04000052
_0809272C: .4byte gNonGameplayRam
_08092730: .4byte sCutsceneTextNone
_08092734: .4byte 0x0600D000
_08092738: .4byte 0x85000400
_0809273C: .4byte IntroShipAlertAndDraftingVblank

	thumb_func_start IntroShipAlertProcess
IntroShipAlertProcess: @ 0x08092740
	push {r4, r5, r6, r7, lr}
	movs r7, #0
	ldr r1, _08092768 @ =gNonGameplayRam
	movs r0, #0x84
	lsls r0, r0, #2
	adds r5, r1, r0
	ldrh r0, [r5]
	adds r0, #1
	strh r0, [r5]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r6, r1, r2
	ldrb r1, [r6]
	cmp r1, #1
	beq _0809277E
	cmp r1, #1
	bgt _0809276C
	cmp r1, #0
	beq _08092776
	b _08092824
	.align 2, 0
_08092768: .4byte gNonGameplayRam
_0809276C:
	cmp r1, #2
	beq _08092798
	cmp r1, #3
	beq _080927D4
	b _08092824
_08092776:
	bl IntroShipAlertInit
	movs r0, #1
	b _08092792
_0809277E:
	ldr r1, _0809278C @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _08092790
	subs r0, #2
	strh r0, [r1]
	b _080927C4
	.align 2, 0
_0809278C: .4byte gWrittenToBldy
_08092790:
	movs r0, #2
_08092792:
	strb r0, [r6]
	strh r7, [r5]
	b _080927C4
_08092798:
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _080927A8 @ =0x0000018F
	cmp r1, r0
	bne _080927B0
	ldr r0, _080927AC @ =gWrittenToBldy
	strh r7, [r0]
	b _080927C4
	.align 2, 0
_080927A8: .4byte 0x0000018F
_080927AC: .4byte gWrittenToBldy
_080927B0:
	movs r0, #0xc8
	lsls r0, r0, #1
	cmp r1, r0
	bne _080927C4
	strh r7, [r5]
	ldr r0, _080927D0 @ =0x04000050
	movs r1, #0xff
	strh r1, [r0]
	movs r0, #3
	strb r0, [r6]
_080927C4:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08092824
	.align 2, 0
_080927D0: .4byte 0x04000050
_080927D4:
	ldr r4, _08092804 @ =gWrittenToBldy
	ldrh r0, [r4]
	cmp r0, #0xf
	bhi _08092814
	cmp r0, #0
	bne _080927FA
	ldr r2, _08092808 @ =sMusicTrackDataRom
	ldr r0, _0809280C @ =sSoundDataEntries
	ldr r1, _08092810 @ =0x00000F5C
	adds r0, r0, r1
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0xa
	bl ApplyMusicSoundFading
_080927FA:
	ldrh r0, [r4]
	adds r0, #2
	strh r0, [r4]
	b _0809281C
	.align 2, 0
_08092804: .4byte gWrittenToBldy
_08092808: .4byte sMusicTrackDataRom
_0809280C: .4byte sSoundDataEntries
_08092810: .4byte 0x00000F5C
_08092814:
	movs r0, #0
	strb r0, [r6]
	strh r7, [r5]
	movs r7, #1
_0809281C:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08092824:
	bl IntroProcessText
	adds r0, r7, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start IntroSamusDriftingOutInit
IntroSamusDriftingOutInit: @ 0x08092830
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08092968 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _0809296C @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08092970 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08092974 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08092978 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809297C @ =unk_99940
	bl CallbackSetVBlank
	movs r4, #0
	str r4, [sp]
	ldr r5, _08092980 @ =0x040000D4
	mov r0, sp
	str r0, [r5]
	ldr r1, _08092984 @ =0x030016A0
	mov r8, r1
	str r1, [r5, #4]
	ldr r0, _08092988 @ =0x850000B4
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	ldr r0, _0809298C @ =sIntroUnk_6101b8
	ldr r1, _08092990 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08092994 @ =sPal_612f48
	str r0, [r5]
	ldr r0, _08092998 @ =0x05000200
	str r0, [r5, #4]
	ldr r6, _0809299C @ =0x84000080
	str r6, [r5, #8]
	ldr r0, [r5, #8]
	ldr r0, _080929A0 @ =sTitleScreenSpaceBackgroundGfx
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _080929A4 @ =sTitleScreenSpaceBackgroundTilemap
	ldr r1, _080929A8 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080929AC @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _080929B0 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _080929B4 @ =sPal_609020
	str r0, [r5]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r5, #4]
	str r6, [r5, #8]
	ldr r1, [r5, #8]
	strh r4, [r0]
	ldr r0, _080929B8 @ =0x04000010
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	ldr r0, _080929BC @ =0x0300122C
	strh r4, [r0]
	ldr r0, _080929C0 @ =0x0300122E
	strh r4, [r0]
	ldr r0, _080929C4 @ =0x03001230
	strh r4, [r0]
	ldr r0, _080929C8 @ =0x03001232
	strh r4, [r0]
	ldr r1, _080929CC @ =0x04000008
	ldr r2, _080929D0 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #6
	ldr r2, _080929D4 @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _080929D8 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _080929DC @ =0x04000054
	strh r1, [r0]
	ldr r1, _080929E0 @ =gWrittenToBldalpha_Eva
	ldr r0, _080929E4 @ =gWrittenToBldalpha_Evb
	strh r4, [r0]
	strh r4, [r1]
	ldr r0, _080929E8 @ =0x04000052
	strh r4, [r0]
	movs r0, #0xa
	movs r1, #0x91
	movs r2, #0x8c
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0xb
	movs r1, #0x8c
	movs r2, #0x50
	movs r3, #0
	bl IntroSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _080929EC @ =0xFFFFFDE4
	add r8, r0
	ldr r0, _080929F0 @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	str r4, [sp]
	mov r2, sp
	str r2, [r5]
	ldr r0, _080929F4 @ =0x0600D000
	str r0, [r5, #4]
	ldr r0, _080929F8 @ =0x85000400
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _080929FC @ =IntroShipAlertAndDraftingVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08092968: .4byte 0x04000208
_0809296C: .4byte 0x04000004
_08092970: .4byte 0x0000FFEF
_08092974: .4byte 0x04000200
_08092978: .4byte 0x0000FFFD
_0809297C: .4byte unk_99940
_08092980: .4byte 0x040000D4
_08092984: .4byte 0x030016A0
_08092988: .4byte 0x850000B4
_0809298C: .4byte sIntroUnk_6101b8
_08092990: .4byte 0x06010000
_08092994: .4byte sPal_612f48
_08092998: .4byte 0x05000200
_0809299C: .4byte 0x84000080
_080929A0: .4byte sTitleScreenSpaceBackgroundGfx
_080929A4: .4byte sTitleScreenSpaceBackgroundTilemap
_080929A8: .4byte 0x0600F800
_080929AC: .4byte sIntroSamusShipFlyingTextTilemap
_080929B0: .4byte 0x0600E000
_080929B4: .4byte sPal_609020
_080929B8: .4byte 0x04000010
_080929BC: .4byte 0x0300122C
_080929C0: .4byte 0x0300122E
_080929C4: .4byte 0x03001230
_080929C8: .4byte 0x03001232
_080929CC: .4byte 0x04000008
_080929D0: .4byte 0x00001C08
_080929D4: .4byte 0x00001F03
_080929D8: .4byte gWrittenToBldy
_080929DC: .4byte 0x04000054
_080929E0: .4byte gWrittenToBldalpha_Eva
_080929E4: .4byte gWrittenToBldalpha_Evb
_080929E8: .4byte 0x04000052
_080929EC: .4byte 0xFFFFFDE4
_080929F0: .4byte sCutsceneTextNone
_080929F4: .4byte 0x0600D000
_080929F8: .4byte 0x85000400
_080929FC: .4byte IntroShipAlertAndDraftingVblank

	thumb_func_start IntroSamusDriftingOutProcess
IntroSamusDriftingOutProcess: @ 0x08092A00
	push {r4, r5, r6, lr}
	movs r6, #0
	ldr r2, _08092A2C @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	adds r4, r2, #0
	cmp r0, #4
	bls _08092A22
	b _08092BE6
_08092A22:
	lsls r0, r0, #2
	ldr r1, _08092A30 @ =_08092A34
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08092A2C: .4byte gNonGameplayRam
_08092A30: .4byte _08092A34
_08092A34: @ jump table
	.4byte _08092A48 @ case 0
	.4byte _08092A68 @ case 1
	.4byte _08092AC4 @ case 2
	.4byte _08092B10 @ case 3
	.4byte _08092B7C @ case 4
_08092A48:
	bl IntroSamusDriftingOutInit
	ldr r3, _08092A64 @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r3, r1
	strh r2, [r0]
	b _08092B64
	.align 2, 0
_08092A64: .4byte gNonGameplayRam
_08092A68:
	ldr r5, _08092A90 @ =gWrittenToBldy
	ldrh r2, [r5]
	cmp r2, #0
	beq _08092A98
	cmp r2, #0x10
	bne _08092A86
	movs r0, #0xf6
	lsls r0, r0, #1
	movs r1, #0
	bl PlayFadingSound
	ldr r0, _08092A94 @ =0x000001ED
	movs r1, #0
	bl PlayFadingSound
_08092A86:
	ldrh r0, [r5]
	subs r0, #2
	strh r0, [r5]
	b _08092AAA
	.align 2, 0
_08092A90: .4byte gWrittenToBldy
_08092A94: .4byte 0x000001ED
_08092A98:
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	movs r1, #2
	strb r1, [r0]
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r4, r1
	strh r2, [r0]
_08092AAA:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	blt _08092B64
	ldr r0, _08092ABC @ =gNonGameplayRam
	ldr r1, _08092AC0 @ =0x00000215
	adds r0, r0, r1
	b _08092AE6
	.align 2, 0
_08092ABC: .4byte gNonGameplayRam
_08092AC0: .4byte 0x00000215
_08092AC4:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrh r0, [r0]
	cmp r0, #0x8c
	bne _08092AD8
	movs r0, #0x49
	movs r1, #0xf
	bl PlayMusic
_08092AD8:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	blt _08092B64
	ldr r1, _08092B0C @ =0x00000215
	adds r0, r4, r1
_08092AE6:
	ldrb r0, [r0]
	cmp r0, #9
	bhi _08092B64
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	adds r1, r4, #0
	lsrs r2, r2, #0x18
	movs r0, #0x10
	movs r3, #1
	bl IntroSetupOam
	b _08092B64
	.align 2, 0
_08092B0C: .4byte 0x00000215
_08092B10:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	blt _08092B42
	ldr r0, _08092B70 @ =gNonGameplayRam
	ldr r1, _08092B74 @ =0x00000215
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #9
	bhi _08092B42
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	adds r1, r4, #0
	lsrs r2, r2, #0x18
	movs r0, #0x10
	movs r3, #1
	bl IntroSetupOam
_08092B42:
	ldr r2, _08092B70 @ =gNonGameplayRam
	movs r0, #0x84
	lsls r0, r0, #2
	adds r3, r2, r0
	ldrh r0, [r3]
	cmp r0, #1
	bne _08092B64
	ldr r1, _08092B78 @ =0x04000050
	movs r0, #0xbf
	strh r0, [r1]
	movs r0, #0
	strh r0, [r3]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r2, r0
	movs r0, #4
	strb r0, [r1]
_08092B64:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08092BE6
	.align 2, 0
_08092B70: .4byte gNonGameplayRam
_08092B74: .4byte 0x00000215
_08092B78: .4byte 0x04000050
_08092B7C:
	ldr r5, _08092BBC @ =gWrittenToBldy
	ldrh r1, [r5]
	cmp r1, #0xf
	bhi _08092BCC
	movs r0, #0x84
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrh r0, [r2]
	cmp r0, #3
	bne _08092BDE
	movs r0, #0
	strh r0, [r2]
	cmp r1, #0
	bne _08092BB2
	ldr r2, _08092BC0 @ =sMusicTrackDataRom
	ldr r0, _08092BC4 @ =sSoundDataEntries
	ldr r1, _08092BC8 @ =0x00000F64
	adds r0, r0, r1
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0x1e
	bl ApplyMusicSoundFading
_08092BB2:
	ldrh r0, [r5]
	adds r0, #1
	strh r0, [r5]
	b _08092BDE
	.align 2, 0
_08092BBC: .4byte gWrittenToBldy
_08092BC0: .4byte sMusicTrackDataRom
_08092BC4: .4byte sSoundDataEntries
_08092BC8: .4byte 0x00000F64
_08092BCC:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r4, r0
	ldrh r0, [r1]
	cmp r0, #8
	bne _08092BDE
	movs r0, #0
	strh r0, [r1]
	movs r6, #1
_08092BDE:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08092BE6:
	bl IntroProcessText
	adds r0, r6, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start IntroSamusShipCrashing
IntroSamusShipCrashing: @ 0x08092BF4
	push {r4, lr}
	movs r4, #0
	ldr r0, _08092C10 @ =gNonGameplayRam
	ldrh r1, [r0, #8]
	adds r2, r0, #0
	cmp r1, #5
	bls _08092C04
	b _08092D02
_08092C04:
	lsls r0, r1, #2
	ldr r1, _08092C14 @ =_08092C18
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08092C10: .4byte gNonGameplayRam
_08092C14: .4byte _08092C18
_08092C18: @ jump table
	.4byte _08092C30 @ case 0
	.4byte _08092C44 @ case 1
	.4byte _08092C66 @ case 2
	.4byte _08092C90 @ case 3
	.4byte _08092CB8 @ case 4
	.4byte _08092CE0 @ case 5
_08092C30:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08092C40 @ =gNonGameplayRam
	movs r0, #2
	strh r0, [r1, #8]
	b _08092D02
	.align 2, 0
_08092C40: .4byte gNonGameplayRam
_08092C44:
	ldr r1, _08092C54 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _08092C58
	subs r0, #1
	strh r0, [r1]
	b _08092C5C
	.align 2, 0
_08092C54: .4byte gWrittenToBldy
_08092C58:
	movs r0, #2
	strh r0, [r2, #8]
_08092C5C:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08092D02
_08092C66:
	bl IntroSamusInShipProcess
	cmp r0, #0
	beq _08092D02
	ldr r1, _08092C88 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _08092C8C @ =0x00000213
	adds r0, r1, r3
	strb r2, [r0]
	movs r0, #3
	strh r0, [r1, #8]
	b _08092D02
	.align 2, 0
_08092C88: .4byte gNonGameplayRam
_08092C8C: .4byte 0x00000213
_08092C90:
	bl IntroShipAlertProcess
	cmp r0, #0
	beq _08092D02
	ldr r1, _08092CB0 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _08092CB4 @ =0x00000213
	adds r0, r1, r3
	strb r2, [r0]
	movs r0, #4
	strh r0, [r1, #8]
	b _08092D02
	.align 2, 0
_08092CB0: .4byte gNonGameplayRam
_08092CB4: .4byte 0x00000213
_08092CB8:
	bl IntroSamusDriftingOutProcess
	cmp r0, #0
	beq _08092D02
	ldr r1, _08092CD8 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _08092CDC @ =0x00000213
	adds r0, r1, r3
	strb r2, [r0]
	movs r0, #5
	strh r0, [r1, #8]
	b _08092D02
	.align 2, 0
_08092CD8: .4byte gNonGameplayRam
_08092CDC: .4byte 0x00000213
_08092CE0:
	ldr r1, _08092CF0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08092CF4
	adds r0, #1
	strh r0, [r1]
	b _08092CFA
	.align 2, 0
_08092CF0: .4byte gWrittenToBldy
_08092CF4:
	movs r0, #0
	strh r0, [r2, #8]
	movs r4, #1
_08092CFA:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08092D02:
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_92d0c
unk_92d0c: @ 0x08092D0C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r4, _08092D68 @ =sRandomNumberTable
	ldr r2, _08092D6C @ =gFrameCounter16Bit
	ldrh r1, [r2]
	movs r3, #0x1f
	adds r0, r3, #0
	ands r0, r1
	adds r0, r0, r4
	ldrb r0, [r0]
	lsrs r6, r0, #2
	ldrh r0, [r2]
	adds r0, #7
	ands r0, r3
	adds r0, r0, r4
	ldrb r0, [r0]
	lsrs r2, r0, #2
	adds r3, r2, #0
	movs r0, #8
	ldrsh r1, [r5, r0]
	cmp r1, #0
	bne _08092D70
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08092D98
	strb r1, [r5, #0x13]
	ldrh r1, [r5, #0xe]
	movs r3, #0xe
	ldrsh r0, [r5, r3]
	cmp r0, #0xf
	bgt _08092D98
	adds r0, r1, r2
	strh r0, [r5, #0xe]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf
	ble _08092D98
	movs r0, #0x10
	strh r0, [r5, #0xe]
	movs r0, #1
	strh r0, [r5, #8]
	b _08092D98
	.align 2, 0
_08092D68: .4byte sRandomNumberTable
_08092D6C: .4byte gFrameCounter16Bit
_08092D70:
	ldrb r0, [r5, #0x13]
	adds r0, #1
	movs r2, #0
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08092D98
	strb r2, [r5, #0x13]
	ldrh r1, [r5, #0xe]
	movs r4, #0xe
	ldrsh r0, [r5, r4]
	cmp r0, #0
	ble _08092D98
	subs r0, r1, r3
	strh r0, [r5, #0xe]
	lsls r0, r0, #0x10
	cmp r0, #0
	bgt _08092D98
	strh r2, [r5, #0xe]
	strh r2, [r5, #8]
_08092D98:
	movs r0, #4
	ldrsh r1, [r5, r0]
	cmp r1, #0
	bne _08092DCE
	ldrh r0, [r5, #0xa]
	adds r0, #1
	strh r0, [r5, #0xa]
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08092DF6
	strh r1, [r5, #0xa]
	ldrh r1, [r5, #0xc]
	movs r2, #0xc
	ldrsh r0, [r5, r2]
	cmp r0, #0xf
	bgt _08092DF6
	adds r0, r1, r6
	strh r0, [r5, #0xc]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf
	ble _08092DF6
	movs r0, #0x10
	strh r0, [r5, #0xc]
	movs r0, #1
	strh r0, [r5, #4]
	b _08092DF6
_08092DCE:
	ldrh r0, [r5, #0xa]
	adds r0, #1
	movs r2, #0
	strh r0, [r5, #0xa]
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08092DF6
	strh r2, [r5, #0xa]
	ldrh r1, [r5, #0xc]
	movs r3, #0xc
	ldrsh r0, [r5, r3]
	cmp r0, #0
	ble _08092DF6
	subs r0, r1, r6
	strh r0, [r5, #0xc]
	lsls r0, r0, #0x10
	cmp r0, #0
	bgt _08092DF6
	strh r2, [r5, #0xc]
	strh r2, [r5, #4]
_08092DF6:
	ldr r1, _08092E40 @ =0x0300122C
	ldrh r0, [r5, #0xc]
	strh r0, [r1]
	ldr r1, _08092E44 @ =0x0300122E
	ldrh r0, [r5, #0xe]
	strh r0, [r1]
	ldr r0, _08092E48 @ =gNonGameplayRam
	movs r4, #0x85
	lsls r4, r4, #2
	adds r0, r0, r4
	ldrb r0, [r0]
	cmp r0, #4
	bne _08092E3A
	ldrb r0, [r5, #0x15]
	adds r0, #1
	strb r0, [r5, #0x15]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _08092E3A
	movs r0, #0
	strb r0, [r5, #0x15]
	ldr r1, _08092E4C @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	cmp r0, #0
	beq _08092E2E
	subs r0, #1
	strh r0, [r1]
_08092E2E:
	ldr r1, _08092E50 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08092E3A
	adds r0, #1
	strh r0, [r1]
_08092E3A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08092E40: .4byte 0x0300122C
_08092E44: .4byte 0x0300122E
_08092E48: .4byte gNonGameplayRam
_08092E4C: .4byte gWrittenToBldalpha_Eva
_08092E50: .4byte gWrittenToBldalpha_Evb

	thumb_func_start IntroProcessDriftingShip
IntroProcessDriftingShip: @ 0x08092E54
	push {r4, r5, lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r1, r0, #1
	movs r5, #0
	movs r4, #0
	strh r1, [r3, #0xa]
	ldrb r0, [r3, #0x14]
	cmp r0, #0
	bne _08092E78
	strh r0, [r3, #0xa]
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	movs r0, #1
	strb r0, [r3, #0x14]
	b _080930BA
_08092E78:
	cmp r0, #1
	bne _08092F00
	ldrb r1, [r3, #0x13]
	adds r1, #1
	strb r1, [r3, #0x13]
	ldr r2, _08092EFC @ =sSineTable
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x17
	ldrh r2, [r3, #2]
	adds r0, r0, r2
	strh r0, [r3, #0xe]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	cmp r1, #0x34
	bls _08092ED0
	ldrh r0, [r3, #4]
	adds r0, #1
	strh r0, [r3, #4]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xc
	bne _08092EBA
	ldrb r0, [r3, #0x15]
	subs r0, #1
	strb r0, [r3, #0x15]
	ldrh r0, [r3, #0xc]
	subs r0, #1
	strh r0, [r3, #0xc]
	strh r4, [r3, #4]
_08092EBA:
	ldrh r0, [r3, #8]
	adds r0, #1
	strh r0, [r3, #8]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xa
	bne _08092ED0
	strh r4, [r3, #8]
	ldrh r0, [r3, #6]
	subs r0, #1
	strh r0, [r3, #6]
_08092ED0:
	movs r0, #0x13
	ldrsb r0, [r3, r0]
	cmp r0, #0
	blt _08092EDA
	b _080930BA
_08092EDA:
	movs r1, #0
	movs r0, #0
	strh r0, [r3, #8]
	strh r0, [r3, #0xa]
	strh r0, [r3, #4]
	strb r1, [r3, #0x13]
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	movs r0, #2
	strb r0, [r3, #0x14]
	movs r0, #0xf9
	lsls r0, r0, #1
	bl SoundPlay
	b _080930BA
	.align 2, 0
_08092EFC: .4byte sSineTable
_08092F00:
	cmp r0, #2
	bne _08092F7C
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
	lsls r1, r1, #0x10
	lsrs r2, r1, #0x12
	ldrh r0, [r3]
	subs r0, r0, r2
	strh r0, [r3, #0xc]
	lsrs r1, r1, #0x13
	ldrh r2, [r3, #2]
	subs r2, r2, r1
	ldr r1, _08092F78 @ =sSineTable
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x17
	adds r2, r2, r0
	strh r2, [r3, #0xe]
	ldrh r0, [r3, #4]
	adds r0, #1
	strh r0, [r3, #4]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xc
	bne _08092F42
	ldrb r0, [r3, #0x15]
	subs r0, #1
	strb r0, [r3, #0x15]
	strh r4, [r3, #4]
_08092F42:
	ldrh r0, [r3, #8]
	adds r0, #1
	strh r0, [r3, #8]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #2
	bne _08092F58
	strh r4, [r3, #8]
	ldrh r0, [r3, #6]
	subs r0, #1
	strh r0, [r3, #6]
_08092F58:
	ldrb r0, [r3, #0x13]
	cmp r0, #0
	beq _08092F60
	b _080930BA
_08092F60:
	strh r4, [r3, #8]
	strh r4, [r3, #0xa]
	strh r4, [r3, #4]
	strb r5, [r3, #0x13]
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	movs r0, #3
	strb r0, [r3, #0x14]
	b _080930BA
	.align 2, 0
_08092F78: .4byte sSineTable
_08092F7C:
	cmp r0, #3
	bne _08092FE4
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
	lsls r1, r1, #0x10
	lsrs r2, r1, #0x12
	ldrh r0, [r3]
	subs r0, r0, r2
	strh r0, [r3, #0xc]
	lsrs r1, r1, #0x13
	ldrh r0, [r3, #2]
	subs r0, r0, r1
	strh r0, [r3, #0xe]
	ldrh r0, [r3, #4]
	adds r0, #1
	strh r0, [r3, #4]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xc
	bne _08092FAE
	ldrb r0, [r3, #0x15]
	subs r0, #1
	strb r0, [r3, #0x15]
	strh r4, [r3, #4]
_08092FAE:
	ldrh r0, [r3, #8]
	adds r0, #1
	strh r0, [r3, #8]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #1
	bne _08092FC4
	strh r4, [r3, #8]
	ldrh r0, [r3, #6]
	subs r0, #1
	strh r0, [r3, #6]
_08092FC4:
	ldrb r0, [r3, #0x13]
	cmp r0, #0
	bne _08092FDE
	strh r4, [r3, #8]
	strh r4, [r3, #0xa]
	strh r4, [r3, #4]
	strb r5, [r3, #0x13]
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	movs r0, #4
	strb r0, [r3, #0x14]
_08092FDE:
	movs r1, #6
	ldrsh r0, [r3, r1]
	b _08093030
_08092FE4:
	cmp r0, #4
	bne _0809304A
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
	lsls r1, r1, #0x10
	lsrs r2, r1, #0x11
	ldrh r0, [r3]
	subs r0, r0, r2
	strh r0, [r3, #0xc]
	lsrs r1, r1, #0x12
	ldrh r0, [r3, #2]
	subs r0, r0, r1
	strh r0, [r3, #0xe]
	ldrh r0, [r3, #4]
	adds r0, #1
	strh r0, [r3, #4]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xc
	bne _08093016
	ldrb r0, [r3, #0x15]
	subs r0, #1
	strb r0, [r3, #0x15]
	strh r4, [r3, #4]
_08093016:
	ldrh r0, [r3, #8]
	adds r0, #1
	strh r0, [r3, #8]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #1
	bne _0809302C
	strh r4, [r3, #8]
	ldrh r0, [r3, #6]
	subs r0, #1
	strh r0, [r3, #6]
_0809302C:
	movs r2, #6
	ldrsh r0, [r3, r2]
_08093030:
	cmp r0, #2
	bgt _080930BA
	strh r4, [r3, #8]
	strh r4, [r3, #0xa]
	strh r4, [r3, #4]
	strb r5, [r3, #0x13]
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	movs r0, #5
	strb r0, [r3, #0x14]
	b _080930BA
_0809304A:
	cmp r0, #5
	bne _08093094
	strh r4, [r3, #0xa]
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r3, #6]
	strb r5, [r3, #0x12]
	strb r5, [r3, #0x11]
	ldrb r1, [r3, #0x18]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3, #0x18]
	ldr r0, _08093088 @ =sIntroUnk_60ad48
	str r0, [r3, #0x1c]
	movs r0, #6
	strb r0, [r3, #0x14]
	ldr r0, _0809308C @ =0x000001F3
	bl SoundPlay_3b1c
	ldr r1, _08093090 @ =gNonGameplayRam
	movs r2, #0x84
	lsls r2, r2, #2
	adds r0, r1, r2
	strh r4, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r1, r0
	movs r0, #3
	strb r0, [r1]
	b _080930BA
	.align 2, 0
_08093088: .4byte sIntroUnk_60ad48
_0809308C: .4byte 0x000001F3
_08093090: .4byte gNonGameplayRam
_08093094:
	cmp r0, #6
	bne _080930BA
	ldrb r0, [r3, #0x11]
	lsls r0, r0, #3
	ldr r1, [r3, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r3, #0x12]
	cmp r0, r2
	bne _080930BA
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080930BA
	strb r5, [r3, #0x10]
	ldrb r1, [r3, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3, #0x18]
_080930BA:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start IntroProcessBslShipSpawning
IntroProcessBslShipSpawning: @ 0x080930C0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0x14]
	cmp r5, #0
	bne _0809311C
	ldrh r1, [r4, #0xc]
	adds r1, #0x7a
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xc
	movs r3, #0
	bl IntroSetupOam
	ldrh r1, [r4, #0xc]
	adds r1, #0x32
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldrh r2, [r4, #0xe]
	adds r2, #1
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	movs r0, #0xd
	movs r3, #0
	bl IntroSetupOam
	ldrh r1, [r4, #0xc]
	adds r1, #0x24
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xe
	movs r3, #0
	bl IntroSetupOam
	movs r0, #0xc
	ldrsh r1, [r4, r0]
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xf
	movs r3, #0
	bl IntroSetupOam
	strb r5, [r4, #0x10]
_0809311C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessBslShipBack
IntroProcessBslShipBack: @ 0x08093124
	push {r4, lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0x14]
	cmp r3, #0
	bne _0809317E
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _080931F0
	ldrh r0, [r2]
	adds r0, #1
	movs r1, #0
	strh r0, [r2]
	strb r1, [r2, #0x13]
	ldrh r0, [r2, #0xa]
	cmp r0, #4
	bne _0809314E
	strh r3, [r2, #0xa]
_0809314E:
	ldrh r0, [r2, #0xa]
	adds r1, r0, #0
	adds r3, r0, #0
	cmp r1, #1
	bhi _0809315E
	ldrh r0, [r2, #0xe]
	adds r0, #1
	b _08093166
_0809315E:
	cmp r1, #3
	bhi _08093168
	ldrh r0, [r2, #0xe]
	subs r0, #1
_08093166:
	strh r0, [r2, #0xe]
_08093168:
	movs r1, #0
	ldrsh r0, [r2, r1]
	cmp r0, #0x1e
	bne _08093178
	movs r1, #0
	movs r0, #1
	strb r0, [r2, #0x14]
	strb r1, [r2, #0x13]
_08093178:
	adds r0, r3, #1
	strh r0, [r2, #0xa]
	b _080931F0
_0809317E:
	cmp r3, #1
	bne _08093192
	ldrh r0, [r2, #0xc]
	movs r1, #0
	strh r0, [r2]
	ldrh r0, [r2, #0xe]
	strh r0, [r2, #2]
	strh r1, [r2, #0xa]
	movs r0, #2
	b _080931EE
_08093192:
	cmp r3, #2
	bne _080931F0
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _080931AE
	ldrh r0, [r2, #0xa]
	adds r0, #1
	movs r1, #0
	strh r0, [r2, #0xa]
	strb r1, [r2, #0x13]
_080931AE:
	movs r4, #0
	ldrsh r1, [r2, r4]
	movs r0, #0xe1
	lsls r0, r0, #2
	subs r0, r0, r1
	ldrh r1, [r2, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xc
	ldrh r1, [r2]
	adds r3, r0, r1
	strh r3, [r2, #0xc]
	movs r4, #4
	ldrsh r0, [r2, r4]
	movs r4, #2
	ldrsh r1, [r2, r4]
	subs r0, r0, r1
	ldrh r1, [r2, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xb
	ldrh r1, [r2, #2]
	adds r4, r0, r1
	strh r4, [r2, #0xe]
	lsls r1, r3, #0x10
	movs r0, #0xa0
	lsls r0, r0, #0x11
	cmp r1, r0
	ble _080931F0
	movs r0, #0
	strh r0, [r2, #0xa]
	strh r3, [r2]
	strh r4, [r2, #2]
	movs r0, #3
_080931EE:
	strb r0, [r2, #0x14]
_080931F0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessDepthParticle
IntroProcessDepthParticle: @ 0x080931F8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrh r1, [r6, #0xa]
	strh r1, [r6, #4]
	ldrb r0, [r6, #0x14]
	cmp r0, #0
	bne _08093222
	movs r1, #0xc
	ldrsh r0, [r6, r1]
	subs r0, #0x78
	movs r1, #0x64
	muls r0, r1, r0
	strh r0, [r6]
	movs r2, #0xe
	ldrsh r0, [r6, r2]
	subs r0, #0x50
	muls r0, r1, r0
	strh r0, [r6, #2]
	movs r0, #1
	strb r0, [r6, #0x14]
	b _080932AE
_08093222:
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x63
	bgt _080932A0
	cmp r0, #0x19
	bne _08093238
	ldr r0, _08093234 @ =sIntroUnk_60ac18
	b _0809324A
	.align 2, 0
_08093234: .4byte sIntroUnk_60ac18
_08093238:
	cmp r0, #0x32
	bne _08093244
	ldr r0, _08093240 @ =sIntroUnk_60ac28
	b _0809324A
	.align 2, 0
_08093240: .4byte sIntroUnk_60ac28
_08093244:
	cmp r0, #0x46
	bne _0809324C
	ldr r0, _0809329C @ =sIntroUnk_60ac38
_0809324A:
	str r0, [r6, #0x1c]
_0809324C:
	movs r0, #4
	ldrsh r4, [r6, r0]
	rsbs r4, r4, #0
	adds r4, #0x64
	movs r1, #0
	ldrsh r0, [r6, r1]
	adds r1, r4, #0
	bl __divsi3
	adds r5, r0, #0
	adds r0, #0x78
	strh r0, [r6, #0xc]
	movs r2, #2
	ldrsh r0, [r6, r2]
	adds r1, r4, #0
	bl __divsi3
	adds r1, r0, #0
	adds r1, #0x50
	strh r1, [r6, #0xe]
	adds r5, #0x80
	lsls r5, r5, #0x10
	movs r0, #0x80
	lsls r0, r0, #0x11
	cmp r5, r0
	bhi _08093290
	lsls r0, r1, #0x10
	asrs r1, r0, #0x10
	cmp r1, #0xa8
	bgt _08093290
	movs r0, #8
	rsbs r0, r0, #0
	cmp r1, r0
	bge _080932AE
_08093290:
	movs r0, #0
	strb r0, [r6, #0x10]
	ldrb r1, [r6, #0x18]
	subs r0, #2
	b _080932AA
	.align 2, 0
_0809329C: .4byte sIntroUnk_60ac38
_080932A0:
	movs r0, #0
	strb r0, [r6, #0x10]
	ldrb r1, [r6, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
_080932AA:
	ands r0, r1
	strb r0, [r6, #0x18]
_080932AE:
	ldrh r0, [r6, #0xa]
	adds r0, #1
	strh r0, [r6, #0xa]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessTimeAndDistanceOam
IntroProcessTimeAndDistanceOam: @ 0x080932BC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #0
	bne _080932D6
	ldrb r5, [r4, #0x11]
	cmp r5, #1
	bne _080932D6
	movs r0, #0xf7
	lsls r0, r0, #1
	bl SoundPlay
	strb r5, [r4, #0x14]
_080932D6:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start IntroProcessAsteroidsPopUp
IntroProcessAsteroidsPopUp: @ 0x080932DC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #0
	bne _080932F4
	ldrb r5, [r4, #0x11]
	cmp r5, #1
	bne _080932F4
	ldr r0, _080932FC @ =0x000001EF
	bl SoundPlay
	strb r5, [r4, #0x14]
_080932F4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080932FC: .4byte 0x000001EF

	thumb_func_start unk_93300
unk_93300: @ 0x08093300
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _0809332C
	ldrh r0, [r2, #0xa]
	adds r0, #1
	strh r0, [r2, #0xa]
	ldrh r1, [r2, #0xa]
	movs r3, #8
	ldrsh r0, [r2, r3]
	cmp r1, r0
	bne _0809332C
	ldrb r0, [r2, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r2, #0x18]
	movs r0, #1
	strb r0, [r2, #0x14]
	ldr r0, _08093330 @ =0x000001F1
	bl SoundPlay
_0809332C:
	pop {r0}
	bx r0
	.align 2, 0
_08093330: .4byte 0x000001F1

	thumb_func_start unk_93334
unk_93334: @ 0x08093334
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x10]
	ldr r1, _08093374 @ =0x00FFFF00
	ands r0, r1
	ldr r1, _08093378 @ =0x00010100
	cmp r0, r1
	bne _0809334C
	movs r0, #0xf8
	lsls r0, r0, #1
	bl SoundPlay
_0809334C:
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #0x12]
	cmp r0, r2
	bne _0809336E
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _0809336E
	strb r1, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_0809336E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08093374: .4byte 0x00FFFF00
_08093378: .4byte 0x00010100

	thumb_func_start IntroOamProcessBigChangingNumber
IntroOamProcessBigChangingNumber: @ 0x0809337C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080933A2
	ldrh r0, [r2, #0xa]
	adds r0, #1
	strh r0, [r2, #0xa]
	ldrh r1, [r2, #0xa]
	movs r3, #8
	ldrsh r0, [r2, r3]
	cmp r1, r0
	bne _080933A2
	ldrb r0, [r2, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r2, #0x18]
	movs r0, #1
	strb r0, [r2, #0x14]
_080933A2:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroSetupOam
IntroSetupOam: @ 0x080933A8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov sb, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sl, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _08093410
	movs r2, #0
	ldr r0, _0809340C @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r1, r0, r3
	ldrb r1, [r1]
	mov r8, r0
	cmp r1, #0
	beq _080933FE
	mov r4, r8
_080933DE:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08093450
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _080933DE
_080933FE:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	mov ip, r0
	cmp r1, #0x13
	ble _08093458
	b _08093450
	.align 2, 0
_0809340C: .4byte gNonGameplayRam
_08093410:
	movs r2, #0x13
	ldr r0, _08093454 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r1, r0, r3
	ldrb r1, [r1]
	mov r8, r0
	cmp r1, #0
	beq _08093448
	mov r3, r8
	movs r4, #0x8b
	lsls r4, r4, #2
_08093428:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08093450
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	adds r0, r0, r4
	ldrb r0, [r0]
	cmp r0, #0
	bne _08093428
_08093448:
	lsls r0, r2, #0x18
	mov ip, r0
	cmp r0, #0
	bge _08093458
_08093450:
	movs r0, #0x14
	b _0809382E
	.align 2, 0
_08093454: .4byte gNonGameplayRam
_08093458:
	movs r0, #0
	str r0, [sp]
	ldr r2, _080934C0 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	mov r0, ip
	asrs r1, r0, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r4, r0, #2
	ldr r3, _080934C4 @ =0x030016A0
	adds r0, r4, r3
	str r0, [r2, #4]
	ldr r0, _080934C8 @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _080934CC @ =0xFFFFFDE4
	adds r0, r3, r1
	adds r2, r4, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	movs r7, #0
	mov r1, sb
	strh r1, [r0]
	ldr r1, _080934D0 @ =0x0000022A
	adds r0, r2, r1
	mov r1, sl
	strh r1, [r0]
	movs r1, #0x8b
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r5, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r6, r2, r0
	ldrb r1, [r6]
	movs r0, #1
	orrs r1, r0
	strb r1, [r6]
	cmp r5, #1
	bne _080934D8
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r6]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _080934D4 @ =unk_92d0c
	str r1, [r0]
	b _0809382A
	.align 2, 0
_080934C0: .4byte 0x040000D4
_080934C4: .4byte 0x030016A0
_080934C8: .4byte 0x85000009
_080934CC: .4byte 0xFFFFFDE4
_080934D0: .4byte 0x0000022A
_080934D4: .4byte unk_92d0c
_080934D8:
	cmp r5, #0xa
	bne _0809352C
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	mov r1, sb
	strh r1, [r0]
	ldr r1, _0809351C @ =0x0000021E
	adds r0, r2, r1
	mov r1, sl
	strh r1, [r0]
	ldr r0, _08093520 @ =0x00000222
	adds r1, r2, r0
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldrb r1, [r6]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093524 @ =sIntroUnk_60acd0
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08093528 @ =IntroProcessDriftingShip
	str r1, [r0]
	b _0809382A
	.align 2, 0
_0809351C: .4byte 0x0000021E
_08093520: .4byte 0x00000222
_08093524: .4byte sIntroUnk_60acd0
_08093528: .4byte IntroProcessDriftingShip
_0809352C:
	cmp r5, #0xb
	bne _08093558
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r6]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093550 @ =sIntroUnk_60acd0
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08093554 @ =IntroProcessBslShipSpawning
	str r1, [r0]
	b _0809382A
	.align 2, 0
_08093550: .4byte sIntroUnk_60acd0
_08093554: .4byte IntroProcessBslShipSpawning
_08093558:
	cmp r5, #0xc
	bne _08093578
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _08093570 @ =0x0000FFD8
	strh r0, [r1]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093574 @ =sIntroUnk_60ad28
	b _080935CE
	.align 2, 0
_08093570: .4byte 0x0000FFD8
_08093574: .4byte sIntroUnk_60ad28
_08093578:
	cmp r5, #0xd
	bne _08093598
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _08093590 @ =0x0000FFE2
	strh r0, [r1]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093594 @ =sIntroUnk_60ad18
	b _080935CE
	.align 2, 0
_08093590: .4byte 0x0000FFE2
_08093594: .4byte sIntroUnk_60ad18
_08093598:
	cmp r5, #0xe
	bne _080935B8
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _080935B0 @ =0x0000FFEC
	strh r0, [r1]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _080935B4 @ =sIntroUnk_60ad08
	b _080935CE
	.align 2, 0
_080935B0: .4byte 0x0000FFEC
_080935B4: .4byte sIntroUnk_60ad08
_080935B8:
	cmp r5, #0xf
	bne _080935E8
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _080935DC @ =0x0000FFF6
	strh r0, [r1]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _080935E0 @ =sIntroUnk_60acf8
_080935CE:
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _080935E4 @ =IntroProcessBslShipBack
	str r1, [r0]
	b _0809382A
	.align 2, 0
_080935DC: .4byte 0x0000FFF6
_080935E0: .4byte sIntroUnk_60acf8
_080935E4: .4byte IntroProcessBslShipBack
_080935E8:
	cmp r5, #0x10
	bne _0809360C
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093604 @ =sIntroUnk_60ac08
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08093608 @ =IntroProcessDepthParticle
	str r1, [r0]
	b _0809382A
	.align 2, 0
_08093604: .4byte sIntroUnk_60ac08
_08093608: .4byte IntroProcessDepthParticle
_0809360C:
	cmp r5, #0x13
	bne _08093630
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093628 @ =sIntroUnk_65bb38
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809362C @ =IntroProcessTimeAndDistanceOam
	str r1, [r0]
	b _0809382A
	.align 2, 0
_08093628: .4byte sIntroUnk_65bb38
_0809362C: .4byte IntroProcessTimeAndDistanceOam
_08093630:
	cmp r5, #0x14
	bne _0809364C
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08093648 @ =sIntroUnk_65bd00
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	b _0809366E
	.align 2, 0
_08093648: .4byte sIntroUnk_65bd00
_0809364C:
	cmp r5, #0x15
	bne _0809367C
	mov r3, ip
	asrs r1, r3, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	movs r1, #0x8e
	lsls r1, r1, #2
	add r1, r8
	adds r1, r0, r1
	ldr r2, _08093674 @ =sIntroUnk_65bd48
	str r2, [r1]
	movs r1, #0x8f
	lsls r1, r1, #2
	add r1, r8
	adds r0, r0, r1
_0809366E:
	ldr r1, _08093678 @ =unk_9397c
	str r1, [r0]
	b _0809382A
	.align 2, 0
_08093674: .4byte sIntroUnk_65bd48
_08093678: .4byte unk_9397c
_0809367C:
	cmp r5, #0x16
	bne _080936AC
	mov r0, ip
	asrs r1, r0, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	movs r1, #0x8e
	lsls r1, r1, #2
	add r1, r8
	adds r1, r0, r1
	ldr r2, _080936A4 @ =sIntroUnk_65bd60
	str r2, [r1]
	movs r1, #0x8f
	lsls r1, r1, #2
	add r1, r8
	adds r0, r0, r1
	ldr r1, _080936A8 @ =IntroProcessAsteroidsPopUp
	str r1, [r0]
	b _0809382A
	.align 2, 0
_080936A4: .4byte sIntroUnk_65bd60
_080936A8: .4byte IntroProcessAsteroidsPopUp
_080936AC:
	cmp r5, #0x17
	bne _080936DC
	mov r3, ip
	asrs r1, r3, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	movs r1, #0x8e
	lsls r1, r1, #2
	add r1, r8
	adds r1, r0, r1
	ldr r2, _080936D4 @ =sIntroUnk_65be00
	str r2, [r1]
	movs r1, #0x8f
	lsls r1, r1, #2
	add r1, r8
	adds r0, r0, r1
	ldr r1, _080936D8 @ =unk_93334
	str r1, [r0]
	b _0809382A
	.align 2, 0
_080936D4: .4byte sIntroUnk_65be00
_080936D8: .4byte unk_93334
_080936DC:
	cmp r5, #0x18
	bne _08093710
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _0809370C @ =sIntroUnk_65bf10
	b _0809381C
	.align 2, 0
_0809370C: .4byte sIntroUnk_65bf10
_08093710:
	cmp r5, #0x19
	bne _08093754
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _0809374C @ =sIntroUnk_65c0d0
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, r8
	adds r2, r2, r0
	ldr r0, _08093750 @ =unk_93300
	b _08093828
	.align 2, 0
_0809374C: .4byte sIntroUnk_65c0d0
_08093750: .4byte unk_93300
_08093754:
	cmp r5, #0x1a
	bne _08093788
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _08093784 @ =sIntroUnk_65c128
	b _0809381C
	.align 2, 0
_08093784: .4byte sIntroUnk_65c128
_08093788:
	cmp r5, #0x1b
	bne _080937BC
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _080937B8 @ =sIntroUnk_65c180
	b _0809381C
	.align 2, 0
_080937B8: .4byte sIntroUnk_65c180
_080937BC:
	cmp r5, #0x1c
	bne _080937F0
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _080937EC @ =sIntroUnk_65c1d8
	b _0809381C
	.align 2, 0
_080937EC: .4byte sIntroUnk_65c1d8
_080937F0:
	cmp r5, #0x1d
	bne _0809382A
	mov r1, ip
	asrs r0, r1, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r3, r8
	adds r1, r2, r3
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r1, r1, r0
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _08093840 @ =sIntroUnk_65c230
_0809381C:
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, r8
	adds r2, r2, r0
	ldr r0, _08093844 @ =IntroOamProcessBigChangingNumber
_08093828:
	str r0, [r2]
_0809382A:
	mov r1, ip
	lsrs r0, r1, #0x18
_0809382E:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08093840: .4byte sIntroUnk_65c230
_08093844: .4byte IntroOamProcessBigChangingNumber

	thumb_func_start IntroSetupBigNumberOam
IntroSetupBigNumberOam: @ 0x08093848
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
	movs r3, #0
	bl IntroSetupOam
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r2, _08093880 @ =gNonGameplayRam
	lsls r1, r0, #3
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r0, #0x89
	lsls r0, r0, #2
	adds r1, r1, r0
	strh r4, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08093880: .4byte gNonGameplayRam

	thumb_func_start unk_93884
unk_93884: @ 0x08093884
	ldr r1, _080938D0 @ =0x040000D4
	ldr r0, _080938D4 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _080938D8 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _080938DC @ =0x04000052
	ldr r0, _080938E0 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _080938E4 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _080938E8 @ =0x04000054
	ldr r0, _080938EC @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x3c
	ldr r0, _080938F0 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080938F4 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080938F8 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080938FC @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_080938D0: .4byte 0x040000D4
_080938D4: .4byte gOamData
_080938D8: .4byte 0x84000100
_080938DC: .4byte 0x04000052
_080938E0: .4byte gWrittenToBldalpha_Evb
_080938E4: .4byte gWrittenToBldalpha_Eva
_080938E8: .4byte 0x04000054
_080938EC: .4byte gWrittenToBldy
_080938F0: .4byte 0x0300122C
_080938F4: .4byte 0x0300122E
_080938F8: .4byte 0x03001230
_080938FC: .4byte 0x03001232

	thumb_func_start IntroShipAlertAndDraftingVblank
IntroShipAlertAndDraftingVblank: @ 0x08093900
	ldr r1, _0809394C @ =0x040000D4
	ldr r0, _08093950 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08093954 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08093958 @ =0x04000052
	ldr r0, _0809395C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08093960 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08093964 @ =0x04000054
	ldr r0, _08093968 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x3c
	ldr r0, _0809396C @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08093970 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08093974 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08093978 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_0809394C: .4byte 0x040000D4
_08093950: .4byte gOamData
_08093954: .4byte 0x84000100
_08093958: .4byte 0x04000052
_0809395C: .4byte gWrittenToBldalpha_Evb
_08093960: .4byte gWrittenToBldalpha_Eva
_08093964: .4byte 0x04000054
_08093968: .4byte gWrittenToBldy
_0809396C: .4byte 0x0300122C
_08093970: .4byte 0x0300122E
_08093974: .4byte 0x03001230
_08093978: .4byte 0x03001232

	thumb_func_start unk_9397c
unk_9397c: @ 0x0809397C
	bx lr
	.align 2, 0

	thumb_func_start IntroSpaceViewInit
IntroSpaceViewInit: @ 0x08093980
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, _08093B10 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08093B14 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08093B18 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08093B1C @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08093B20 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08093B24 @ =unk_99940
	bl CallbackSetVBlank
	movs r0, #0x80
	lsls r0, r0, #0x11
	bl DoSoundAction
	bl StopAllMusicAndSounds
	movs r6, #0
	str r6, [sp]
	ldr r4, _08093B28 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r0, _08093B2C @ =gNonGameplayRam
	str r0, [r4, #4]
	ldr r0, _08093B30 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08093B34 @ =sIntroUnk_6101b8
	ldr r1, _08093B38 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08093B3C @ =sPal_612f48
	str r0, [r4]
	ldr r0, _08093B40 @ =0x05000200
	str r0, [r4, #4]
	ldr r0, _08093B44 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08093B48 @ =sIntroBslSpaceBgGfx
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08093B4C @ =sIntroBslTilemap
	ldr r5, _08093B50 @ =0x02010000
	adds r1, r5, #0
	bl LZ77UncompWram
	str r5, [r4]
	ldr r0, _08093B54 @ =0x0600E800
	str r0, [r4, #4]
	ldr r0, _08093B58 @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r1, sp, #4
	ldr r2, _08093B5C @ =0x000001FF
	adds r0, r2, #0
	strh r0, [r1]
	str r1, [r4]
	ldr r0, _08093B60 @ =0x0600F000
	str r0, [r4, #4]
	ldr r0, _08093B64 @ =0x81000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08093B68 @ =sIntroSpaceTilemap
	ldr r1, _08093B6C @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08093B70 @ =sIntroBslSpaceBgPal
	str r0, [r4]
	ldr r0, _08093B74 @ =0x05000100
	str r0, [r4, #4]
	ldr r0, _08093B78 @ =0x84000040
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	strh r6, [r0]
	ldr r0, _08093B7C @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _08093B80 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _08093B84 @ =0x04000010
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
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	ldr r0, _08093B88 @ =gBg1XPosition
	strh r6, [r0]
	ldr r0, _08093B8C @ =gBg1YPosition
	strh r6, [r0]
	ldr r0, _08093B90 @ =0x0300122C
	strh r6, [r0]
	ldr r0, _08093B94 @ =0x0300122E
	strh r6, [r0]
	ldr r0, _08093B98 @ =0x03001230
	strh r6, [r0]
	ldr r0, _08093B9C @ =0x03001232
	strh r6, [r0]
	ldr r1, _08093BA0 @ =0x04000008
	ldr r2, _08093BA4 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08093BA8 @ =0x00005D02
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08093BAC @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	movs r0, #1
	movs r1, #0
	movs r2, #0
	movs r3, #1
	bl IntroSpaceViewSetupOam
	movs r1, #0xf0
	rsbs r1, r1, #0
	movs r2, #0x6e
	rsbs r2, r2, #0
	movs r0, #2
	movs r3, #1
	bl IntroSpaceViewSetupOam
	movs r5, #0
_08093AA4:
	bl SpecialCutsceneGetRandomNumber
	adds r4, r0, #0
	lsls r4, r4, #0x18
	lsrs r4, r4, #0x18
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r0, #5
	adds r1, r4, #0
	movs r3, #1
	bl IntroSpaceViewSetupOam
	adds r0, r5, #1
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	cmp r5, #9
	bls _08093AA4
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08093B2C @ =gNonGameplayRam
	ldr r0, _08093BB0 @ =sCutsceneTextNone
	str r0, [r1]
	movs r0, #0
	str r0, [sp]
	ldr r1, _08093B28 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _08093BB4 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08093BB8 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	subs r1, #0xd4
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08093BBC @ =IntroSpaceViewVblank
	bl CallbackSetVBlank
	movs r0, #0x60
	movs r1, #0xf
	bl PlayMusic
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08093B10: .4byte 0x04000208
_08093B14: .4byte 0x04000004
_08093B18: .4byte 0x0000FFEF
_08093B1C: .4byte 0x04000200
_08093B20: .4byte 0x0000FFFD
_08093B24: .4byte unk_99940
_08093B28: .4byte 0x040000D4
_08093B2C: .4byte gNonGameplayRam
_08093B30: .4byte 0x85000150
_08093B34: .4byte sIntroUnk_6101b8
_08093B38: .4byte 0x06010000
_08093B3C: .4byte sPal_612f48
_08093B40: .4byte 0x05000200
_08093B44: .4byte 0x84000080
_08093B48: .4byte sIntroBslSpaceBgGfx
_08093B4C: .4byte sIntroBslTilemap
_08093B50: .4byte 0x02010000
_08093B54: .4byte 0x0600E800
_08093B58: .4byte 0x84000200
_08093B5C: .4byte 0x000001FF
_08093B60: .4byte 0x0600F000
_08093B64: .4byte 0x81000400
_08093B68: .4byte sIntroSpaceTilemap
_08093B6C: .4byte 0x0600F800
_08093B70: .4byte sIntroBslSpaceBgPal
_08093B74: .4byte 0x05000100
_08093B78: .4byte 0x84000040
_08093B7C: .4byte sIntroSamusShipFlyingTextTilemap
_08093B80: .4byte 0x0600E000
_08093B84: .4byte 0x04000010
_08093B88: .4byte gBg1XPosition
_08093B8C: .4byte gBg1YPosition
_08093B90: .4byte 0x0300122C
_08093B94: .4byte 0x0300122E
_08093B98: .4byte 0x03001230
_08093B9C: .4byte 0x03001232
_08093BA0: .4byte 0x04000008
_08093BA4: .4byte 0x00001C08
_08093BA8: .4byte 0x00005D02
_08093BAC: .4byte 0x00001F03
_08093BB0: .4byte sCutsceneTextNone
_08093BB4: .4byte 0x0600D000
_08093BB8: .4byte 0x85000400
_08093BBC: .4byte IntroSpaceViewVblank

	thumb_func_start IntroSpaceViewPartProcess
IntroSpaceViewPartProcess: @ 0x08093BC0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	movs r7, #0
	ldr r2, _08093BF0 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r3, #0x85
	lsls r3, r3, #2
	adds r0, r2, r3
	ldrb r0, [r0]
	adds r4, r2, #0
	cmp r0, #7
	bls _08093BE4
	b _08093F38
_08093BE4:
	lsls r0, r0, #2
	ldr r1, _08093BF4 @ =_08093BF8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08093BF0: .4byte gNonGameplayRam
_08093BF4: .4byte _08093BF8
_08093BF8: @ jump table
	.4byte _08093C18 @ case 0
	.4byte _08093C7C @ case 1
	.4byte _08093CB8 @ case 2
	.4byte _08093CEC @ case 3
	.4byte _08093D54 @ case 4
	.4byte _08093D98 @ case 5
	.4byte _08093E5C @ case 6
	.4byte _08093F18 @ case 7
_08093C18:
	ldr r2, _08093C28 @ =gWrittenToBldy
	ldrh r0, [r2]
	adds r1, r0, #0
	cmp r1, #0
	beq _08093C2C
	subs r0, #1
	strh r0, [r2]
	b _08093C3E
	.align 2, 0
_08093C28: .4byte gWrittenToBldy
_08093C2C:
	movs r5, #0x84
	lsls r5, r5, #2
	adds r0, r4, r5
	strh r1, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #1
	strb r0, [r1]
_08093C3E:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x3f
	bls _08093C4C
	b _08093F00
_08093C4C:
	ldr r0, _08093C74 @ =gNonGameplayRam
	ldr r1, _08093C78 @ =0x00000215
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0xd
	bls _08093C5A
	b _08093F00
_08093C5A:
	bl SpecialCutsceneGetRandomNumber
	adds r4, r0, #0
	lsls r4, r4, #0x18
	lsrs r4, r4, #0x18
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r0, #5
	adds r1, r4, #0
	b _08093D40
	.align 2, 0
_08093C74: .4byte gNonGameplayRam
_08093C78: .4byte 0x00000215
_08093C7C:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r4, r2
	ldrh r0, [r1]
	cmp r0, #0x1e
	bne _08093CA2
	movs r0, #0
	strh r0, [r1]
	movs r0, #4
	movs r1, #0x78
	movs r2, #0x4a
	movs r3, #0
	bl IntroSpaceViewSetupOam
	movs r3, #0x85
	lsls r3, r3, #2
	adds r1, r4, r3
	movs r0, #2
	strb r0, [r1]
_08093CA2:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _08093CAE
	b _08093F00
_08093CAE:
	ldr r5, _08093CB4 @ =0x00000215
	adds r0, r4, r5
	b _08093D2A
	.align 2, 0
_08093CB4: .4byte 0x00000215
_08093CB8:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrh r1, [r2]
	subs r0, #0x30
	cmp r1, r0
	bne _08093CD4
	movs r0, #0
	strh r0, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r0, #3
	strb r0, [r1]
_08093CD4:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _08093CE0
	b _08093F00
_08093CE0:
	ldr r3, _08093CE8 @ =0x00000215
	adds r0, r4, r3
	b _08093D2A
	.align 2, 0
_08093CE8: .4byte 0x00000215
_08093CEC:
	movs r5, #0x84
	lsls r5, r5, #2
	adds r2, r4, r5
	ldrh r1, [r2]
	cmp r1, #0x1e
	bne _08093D04
	ldr r0, _08093D00 @ =0x000001E9
	bl SoundPlay
	b _08093D18
	.align 2, 0
_08093D00: .4byte 0x000001E9
_08093D04:
	ldr r0, _08093D48 @ =0x0000041A
	cmp r1, r0
	bne _08093D18
	movs r0, #0
	strh r0, [r2]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #5
	strb r0, [r1]
_08093D18:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _08093D24
	b _08093F00
_08093D24:
	ldr r0, _08093D4C @ =gNonGameplayRam
	ldr r1, _08093D50 @ =0x00000215
	adds r0, r0, r1
_08093D2A:
	ldrb r0, [r0]
	cmp r0, #0xb
	bls _08093D32
	b _08093F00
_08093D32:
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r0, #5
	movs r1, #0
_08093D40:
	movs r3, #1
	bl IntroSpaceViewSetupOam
	b _08093F00
	.align 2, 0
_08093D48: .4byte 0x0000041A
_08093D4C: .4byte gNonGameplayRam
_08093D50: .4byte 0x00000215
_08093D54:
	ldr r4, _08093D84 @ =gWrittenToBldy
	ldrh r0, [r4]
	cmp r0, #0xf
	bhi _08093D94
	cmp r0, #0
	bne _08093D7A
	ldr r2, _08093D88 @ =sMusicTrackDataRom
	ldr r0, _08093D8C @ =sSoundDataEntries
	ldr r3, _08093D90 @ =0x00000F5C
	adds r0, r0, r3
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0xa
	bl ApplyMusicSoundFading
_08093D7A:
	ldrh r0, [r4]
	adds r0, #2
	strh r0, [r4]
	b _08093F00
	.align 2, 0
_08093D84: .4byte gWrittenToBldy
_08093D88: .4byte sMusicTrackDataRom
_08093D8C: .4byte sSoundDataEntries
_08093D90: .4byte 0x00000F5C
_08093D94:
	movs r7, #1
	b _08093F00
_08093D98:
	movs r5, #0x84
	lsls r5, r5, #2
	adds r3, r4, r5
	ldrh r0, [r3]
	cmp r0, #5
	bhi _08093DC4
	ldr r2, _08093DBC @ =sIntroSamusSittingBgGfxPointers
	adds r1, r0, #0
	subs r1, #1
	lsls r0, r1, #2
	adds r0, r0, r2
	ldr r0, [r0]
	lsls r1, r1, #0xc
	ldr r2, _08093DC0 @ =0x06008000
	adds r1, r1, r2
	bl LZ77UncompVram
	b _08093F00
	.align 2, 0
_08093DBC: .4byte sIntroSamusSittingBgGfxPointers
_08093DC0: .4byte 0x06008000
_08093DC4:
	cmp r0, #6
	bne _08093E28
	ldr r0, _08093E00 @ =sIntroUnk_658be0
	ldr r1, _08093E04 @ =0x0600E000
	bl LZ77UncompVram
	ldr r1, _08093E08 @ =0x040000D4
	ldr r0, _08093E0C @ =sIntroUnk_6591e4
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08093E10 @ =0x84000040
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08093E14 @ =gWrittenToBldalpha_Eva
	movs r1, #0
	strh r1, [r0]
	ldr r2, _08093E18 @ =gWrittenToBldalpha_Evb
	movs r0, #0x10
	strh r0, [r2]
	ldr r0, _08093E1C @ =0x04000014
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	ldr r1, _08093E20 @ =0x0400000A
	ldr r3, _08093E24 @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r1]
	b _08093F00
	.align 2, 0
_08093E00: .4byte sIntroUnk_658be0
_08093E04: .4byte 0x0600E000
_08093E08: .4byte 0x040000D4
_08093E0C: .4byte sIntroUnk_6591e4
_08093E10: .4byte 0x84000040
_08093E14: .4byte gWrittenToBldalpha_Eva
_08093E18: .4byte gWrittenToBldalpha_Evb
_08093E1C: .4byte 0x04000014
_08093E20: .4byte 0x0400000A
_08093E24: .4byte 0x00001C08
_08093E28:
	cmp r0, #7
	bne _08093F00
	ldr r1, _08093E54 @ =0x04000050
	ldr r5, _08093E58 @ =0x00003C42
	adds r0, r5, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r5, #0x80
	lsls r5, r5, #2
	adds r1, r5, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r3]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #6
	strb r0, [r1]
	b _08093F00
	.align 2, 0
_08093E54: .4byte 0x04000050
_08093E58: .4byte 0x00003C42
_08093E5C:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r4, r2
	ldrh r0, [r1]
	cmp r0, #4
	bne _08093F00
	movs r2, #0
	strh r2, [r1]
	ldr r6, _08093EC0 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r6]
	cmp r0, #0xf
	bhi _08093EDC
	cmp r0, #0
	bne _08093EB0
	ldr r5, _08093EC4 @ =sMusicTrackDataRom
	ldr r4, _08093EC8 @ =sSoundDataEntries
	ldr r3, _08093ECC @ =0x00000F4C
	adds r0, r4, r3
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	movs r1, #0x3c
	bl ApplyMusicSoundFading
	ldr r0, _08093ED0 @ =0x00000F54
	adds r4, r4, r0
	ldrh r1, [r4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r0, [r0]
	movs r1, #0x3c
	bl ApplyMusicSoundFading
	ldr r0, _08093ED4 @ =0x000001EB
	movs r1, #0x3c
	bl PlayFadingSound
_08093EB0:
	ldrh r0, [r6]
	adds r0, #1
	strh r0, [r6]
	ldr r1, _08093ED8 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	subs r0, #1
	strh r0, [r1]
	b _08093F00
	.align 2, 0
_08093EC0: .4byte gWrittenToBldalpha_Eva
_08093EC4: .4byte sMusicTrackDataRom
_08093EC8: .4byte sSoundDataEntries
_08093ECC: .4byte 0x00000F4C
_08093ED0: .4byte 0x00000F54
_08093ED4: .4byte 0x000001EB
_08093ED8: .4byte gWrittenToBldalpha_Evb
_08093EDC:
	str r2, [sp]
	ldr r1, _08093F0C @ =0x040000D4
	mov r3, sp
	str r3, [r1]
	movs r5, #0x87
	lsls r5, r5, #2
	adds r0, r4, r5
	str r0, [r1, #4]
	ldr r0, _08093F10 @ =0x850000B4
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #7
	strb r0, [r1]
	ldr r0, _08093F14 @ =gWrittenToBldy
	strh r2, [r0]
_08093F00:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08093F38
	.align 2, 0
_08093F0C: .4byte 0x040000D4
_08093F10: .4byte 0x850000B4
_08093F14: .4byte gWrittenToBldy
_08093F18:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r4, r2
	ldrh r0, [r1]
	cmp r0, #0x96
	bne _08093F38
	movs r0, #0
	strh r0, [r1]
	movs r3, #0x85
	lsls r3, r3, #2
	adds r1, r4, r3
	movs r0, #4
	strb r0, [r1]
	ldr r1, _08093F48 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
_08093F38:
	bl IntroProcessText
	adds r0, r7, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08093F48: .4byte 0x04000050

	thumb_func_start IntroFlyingViewInit
IntroFlyingViewInit: @ 0x08093F4C
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _0809407C @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08094080 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08094084 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08094088 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809408C @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08094090 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08094094 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08094098 @ =0x030016A0
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _0809409C @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080940A0 @ =sIntroUnk_6101b8
	ldr r1, _080940A4 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _080940A8 @ =sPal_612f48
	str r0, [r4]
	ldr r0, _080940AC @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _080940B0 @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080940B4 @ =sTitleScreenSpaceBackgroundGfx
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _080940B8 @ =sTitleScreenSpaceBackgroundTilemap
	ldr r1, _080940BC @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080940C0 @ =sIntroSamusShipFlyingTextTilemap
	ldr r1, _080940C4 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _080940C8 @ =sPal_609020
	str r0, [r4]
	movs r1, #0xa0
	lsls r1, r1, #0x13
	str r1, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080940CC @ =sPal_598a8c
	str r0, [r4]
	ldr r0, _080940D0 @ =0x050001E0
	str r0, [r4, #4]
	ldr r0, _080940D4 @ =0x84000008
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r1]
	ldr r0, _080940D8 @ =0x04000010
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
	strh r5, [r0]
	ldr r0, _080940DC @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _080940E0 @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _080940E4 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _080940E8 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _080940EC @ =0x03001230
	strh r5, [r0]
	ldr r0, _080940F0 @ =0x03001232
	strh r5, [r0]
	ldr r1, _080940F4 @ =0x04000008
	ldr r2, _080940F8 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #6
	ldr r2, _080940FC @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	movs r0, #0xa
	movs r1, #0x91
	movs r2, #0x8c
	movs r3, #0
	bl IntroSpaceViewSetupOam
	movs r0, #0xb
	movs r1, #0x8c
	movs r2, #0x50
	movs r3, #0
	bl IntroSpaceViewSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08094100 @ =0xFFFFFDE4
	add r8, r0
	ldr r0, _08094104 @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _08094108 @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _0809410C @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc8
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08094110 @ =IntroSpaceViewVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809407C: .4byte 0x04000208
_08094080: .4byte 0x04000004
_08094084: .4byte 0x0000FFEF
_08094088: .4byte 0x04000200
_0809408C: .4byte 0x0000FFFD
_08094090: .4byte unk_99940
_08094094: .4byte 0x040000D4
_08094098: .4byte 0x030016A0
_0809409C: .4byte 0x850000B4
_080940A0: .4byte sIntroUnk_6101b8
_080940A4: .4byte 0x06010000
_080940A8: .4byte sPal_612f48
_080940AC: .4byte 0x05000200
_080940B0: .4byte 0x84000080
_080940B4: .4byte sTitleScreenSpaceBackgroundGfx
_080940B8: .4byte sTitleScreenSpaceBackgroundTilemap
_080940BC: .4byte 0x0600F800
_080940C0: .4byte sIntroSamusShipFlyingTextTilemap
_080940C4: .4byte 0x0600E000
_080940C8: .4byte sPal_609020
_080940CC: .4byte sPal_598a8c
_080940D0: .4byte 0x050001E0
_080940D4: .4byte 0x84000008
_080940D8: .4byte 0x04000010
_080940DC: .4byte gBg1XPosition
_080940E0: .4byte gBg1YPosition
_080940E4: .4byte 0x0300122C
_080940E8: .4byte 0x0300122E
_080940EC: .4byte 0x03001230
_080940F0: .4byte 0x03001232
_080940F4: .4byte 0x04000008
_080940F8: .4byte 0x00001C08
_080940FC: .4byte 0x00001F03
_08094100: .4byte 0xFFFFFDE4
_08094104: .4byte sCutsceneTextNone
_08094108: .4byte 0x0600D000
_0809410C: .4byte 0x85000400
_08094110: .4byte IntroSpaceViewVblank

	thumb_func_start IntroFlyingViewProcess
IntroFlyingViewProcess: @ 0x08094114
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _0809413C @ =gNonGameplayRam
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r4, r0
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r0, [r2]
	cmp r0, #1
	beq _0809417C
	cmp r0, #1
	bgt _08094140
	cmp r0, #0
	beq _08094146
	b _080941F6
	.align 2, 0
_0809413C: .4byte gNonGameplayRam
_08094140:
	cmp r0, #2
	beq _080941D8
	b _080941F6
_08094146:
	ldr r4, _0809416C @ =gWrittenToBldy
	ldrh r0, [r4]
	cmp r0, #0
	beq _08094174
	cmp r0, #0x10
	bne _08094164
	movs r0, #0xf6
	lsls r0, r0, #1
	movs r1, #0
	bl PlayFadingSound
	ldr r0, _08094170 @ =0x000001ED
	movs r1, #0
	bl PlayFadingSound
_08094164:
	ldrh r0, [r4]
	subs r0, #2
	strh r0, [r4]
	b _080941C6
	.align 2, 0
_0809416C: .4byte gWrittenToBldy
_08094170: .4byte 0x000001ED
_08094174:
	strh r5, [r1]
	movs r0, #1
	strb r0, [r2]
	b _080941C6
_0809417C:
	bl SpecialCutsceneGetRandomNumber
	lsls r0, r0, #0x18
	cmp r0, #0
	blt _080941AE
	ldr r1, _080941D0 @ =0x00000215
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #9
	bhi _080941AE
	bl SpecialCutsceneGetRandomNumber
	adds r4, r0, #0
	lsls r4, r4, #0x18
	lsrs r4, r4, #0x18
	bl SpecialCutsceneGetRandomNumber
	adds r2, r0, #0
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r0, #0x10
	adds r1, r4, #0
	movs r3, #0
	bl IntroSpaceViewSetupOam
_080941AE:
	ldr r0, _080941D4 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r2, r0, r1
	ldrh r1, [r2]
	movs r0, #0x96
	lsls r0, r0, #1
	cmp r1, r0
	bne _080941C6
	movs r0, #0
	strh r0, [r2]
	movs r5, #1
_080941C6:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _080941F6
	.align 2, 0
_080941D0: .4byte 0x00000215
_080941D4: .4byte gNonGameplayRam
_080941D8:
	ldr r1, _080941E8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080941EC
	adds r0, #1
	strh r0, [r1]
	b _080941EE
	.align 2, 0
_080941E8: .4byte gWrittenToBldy
_080941EC:
	movs r5, #1
_080941EE:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080941F6:
	bl IntroProcessText
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start IntroSpaceView
IntroSpaceView: @ 0x08094204
	push {r4, lr}
	movs r4, #0
	ldr r0, _08094220 @ =gNonGameplayRam
	ldrh r1, [r0, #8]
	adds r2, r0, #0
	cmp r1, #7
	bls _08094214
	b _0809431E
_08094214:
	lsls r0, r1, #2
	ldr r1, _08094224 @ =_08094228
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08094220: .4byte gNonGameplayRam
_08094224: .4byte _08094228
_08094228: @ jump table
	.4byte _08094248 @ case 0
	.4byte _08094258 @ case 1
	.4byte _08094274 @ case 2
	.4byte _0809429C @ case 3
	.4byte _080942BC @ case 4
	.4byte _080942CC @ case 5
	.4byte _080942D2 @ case 6
	.4byte _080942FC @ case 7
_08094248:
	bl IntroSpaceViewInit
	ldr r1, _08094254 @ =gNonGameplayRam
	movs r0, #1
	strh r0, [r1, #8]
	b _0809431E
	.align 2, 0
_08094254: .4byte gNonGameplayRam
_08094258:
	bl SpecialCutsceneFadeIn
	ldr r0, _0809426C @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _0809431E
	ldr r1, _08094270 @ =gNonGameplayRam
	movs r0, #2
	strh r0, [r1, #8]
	b _0809431E
	.align 2, 0
_0809426C: .4byte gWrittenToBldy
_08094270: .4byte gNonGameplayRam
_08094274:
	bl IntroSpaceViewPartProcess
	cmp r0, #0
	beq _0809431E
	ldr r1, _08094294 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _08094298 @ =0x00000213
	adds r0, r1, r3
	strb r2, [r0]
	movs r0, #3
	strh r0, [r1, #8]
	b _0809431E
	.align 2, 0
_08094294: .4byte gNonGameplayRam
_08094298: .4byte 0x00000213
_0809429C:
	ldr r1, _080942AC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080942B0
	adds r0, #1
	strh r0, [r1]
	b _080942B4
	.align 2, 0
_080942AC: .4byte gWrittenToBldy
_080942B0:
	movs r0, #4
	strh r0, [r2, #8]
_080942B4:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080942BC:
	bl IntroFlyingViewInit
	ldr r1, _080942C8 @ =gNonGameplayRam
	movs r0, #6
	strh r0, [r1, #8]
	b _0809431E
	.align 2, 0
_080942C8: .4byte gNonGameplayRam
_080942CC:
	movs r0, #6
	strh r0, [r2, #8]
	b _0809431E
_080942D2:
	bl IntroFlyingViewProcess
	cmp r0, #0
	beq _0809431E
	ldr r2, _080942F4 @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r2, r0
	movs r0, #0
	strb r0, [r1]
	ldr r3, _080942F8 @ =0x00000213
	adds r1, r2, r3
	strb r0, [r1]
	strh r0, [r2, #8]
	movs r4, #1
	b _0809431E
	.align 2, 0
_080942F4: .4byte gNonGameplayRam
_080942F8: .4byte 0x00000213
_080942FC:
	ldr r1, _0809430C @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08094310
	adds r0, #1
	strh r0, [r1]
	b _08094316
	.align 2, 0
_0809430C: .4byte gWrittenToBldy
_08094310:
	movs r0, #0
	strh r0, [r2, #8]
	movs r4, #1
_08094316:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_0809431E:
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start IntroProcessSpaceViewScrolling
IntroProcessSpaceViewScrolling: @ 0x08094328
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0x12]
	adds r0, #1
	strb r0, [r1, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1e
	bne _08094346
	movs r0, #0
	strb r0, [r1, #0x12]
	ldr r1, _0809434C @ =0x03001230
	ldrh r0, [r1]
	subs r0, #1
	strh r0, [r1]
_08094346:
	pop {r0}
	bx r0
	.align 2, 0
_0809434C: .4byte 0x03001230

	thumb_func_start IntroProcessBslShipSideways
IntroProcessBslShipSideways: @ 0x08094350
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrh r1, [r5, #0xc]
	movs r6, #0
	strh r1, [r5, #4]
	ldrb r0, [r5, #0x14]
	cmp r0, #0
	bne _08094380
	strh r1, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	ldr r0, _0809437C @ =gNonGameplayRam
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #3
	beq _08094376
	b _080944D6
_08094376:
	movs r0, #1
	b _080944D4
	.align 2, 0
_0809437C: .4byte gNonGameplayRam
_08094380:
	cmp r0, #1
	bne _080943E2
	ldrh r0, [r5, #0xa]
	adds r0, #1
	strh r0, [r5, #0xa]
	lsls r0, r0, #0x10
	movs r1, #0xc3
	lsls r1, r1, #0x12
	cmp r0, r1
	bne _080943A2
	movs r1, #0x82
	lsls r1, r1, #1
	movs r0, #3
	movs r2, #0x6e
	movs r3, #0
	bl IntroSpaceViewSetupOam
_080943A2:
	movs r2, #0
	ldrsh r0, [r5, r2]
	movs r1, #0x3c
	subs r1, r1, r0
	ldrh r0, [r5, #0xa]
	lsls r0, r0, #1
	muls r0, r1, r0
	asrs r0, r0, #0xb
	ldrh r3, [r5]
	adds r2, r0, r3
	strh r2, [r5, #0xc]
	movs r4, #2
	ldrsh r0, [r5, r4]
	movs r1, #0xa
	subs r1, r1, r0
	ldrh r0, [r5, #0xa]
	lsls r0, r0, #1
	muls r0, r1, r0
	asrs r0, r0, #0xb
	ldrh r7, [r5, #2]
	adds r1, r0, r7
	strh r1, [r5, #0xe]
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x1d
	bgt _080943D8
	b _080944D6
_080943D8:
	strh r6, [r5, #0xa]
	strh r2, [r5]
	strh r1, [r5, #2]
	movs r0, #2
	b _080944D4
_080943E2:
	cmp r0, #2
	bne _08094408
	ldrh r0, [r5, #0xa]
	adds r0, #1
	strh r0, [r5, #0xa]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #1
	bne _080944D6
	strh r6, [r5, #0xa]
	movs r0, #4
	strh r0, [r5, #2]
	strh r1, [r5, #4]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #8]
	movs r0, #0
	strb r0, [r5, #0x13]
	movs r0, #3
	b _080944D4
_08094408:
	cmp r0, #3
	bne _08094480
	movs r0, #0
	ldrsh r3, [r5, r0]
	ldr r2, _08094478 @ =sSineTable
	ldrb r1, [r5, #0x13]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r4, #0
	ldrsh r0, [r0, r4]
	adds r4, r3, #0
	muls r4, r0, r4
	movs r7, #2
	ldrsh r3, [r5, r7]
	lsls r1, r1, #1
	adds r1, r1, r2
	movs r7, #0
	ldrsh r0, [r1, r7]
	muls r3, r0, r3
	movs r1, #0
	ldrsh r0, [r2, r1]
	adds r1, r4, #0
	muls r1, r0, r1
	adds r2, #0x80
	movs r4, #0
	ldrsh r0, [r2, r4]
	muls r0, r3, r0
	adds r1, r1, r0
	ldrh r0, [r5, #0xa]
	lsrs r0, r0, #2
	ldrh r7, [r5]
	adds r0, r0, r7
	strh r0, [r5, #0xc]
	asrs r1, r1, #0x10
	ldrh r0, [r5, #8]
	adds r1, r1, r0
	strh r1, [r5, #0xe]
	ldrb r0, [r5, #0x13]
	adds r0, #1
	strb r0, [r5, #0x13]
	ldrh r0, [r5, #0xa]
	adds r0, #1
	strh r0, [r5, #0xa]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0x3c
	beq _080944D6
	ldr r0, _0809447C @ =0x00007530
	cmp r1, r0
	bne _080944D6
	strh r6, [r5, #0xa]
	movs r0, #4
	b _080944D4
	.align 2, 0
_08094478: .4byte sSineTable
_0809447C: .4byte 0x00007530
_08094480:
	cmp r0, #4
	bne _08094490
	movs r0, #5
	strb r0, [r5, #0x14]
	strh r1, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	b _080944D6
_08094490:
	cmp r0, #5
	bne _080944D6
	ldrh r0, [r5, #0xa]
	adds r0, #1
	strh r0, [r5, #0xa]
	movs r2, #0
	ldrsh r1, [r5, r2]
	movs r0, #0x82
	lsls r0, r0, #2
	subs r0, r0, r1
	ldrh r1, [r5, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xa
	ldrh r3, [r5]
	adds r2, r0, r3
	strh r2, [r5, #0xc]
	movs r4, #2
	ldrsh r1, [r5, r4]
	movs r0, #0x64
	subs r0, r0, r1
	ldrh r1, [r5, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xa
	ldrh r7, [r5, #2]
	adds r3, r0, r7
	strh r3, [r5, #0xe]
	lsls r1, r2, #0x10
	ldr r0, _08094544 @ =0x02070000
	cmp r1, r0
	ble _080944D6
	strh r6, [r5, #0xa]
	strh r2, [r5]
	strh r3, [r5, #2]
	movs r0, #6
_080944D4:
	strb r0, [r5, #0x14]
_080944D6:
	ldr r0, _08094548 @ =0x0300122C
	ldrh r2, [r5, #0xc]
	strh r2, [r0]
	ldr r1, _0809454C @ =0x0300122E
	ldrh r0, [r5, #0xe]
	strh r0, [r1]
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	movs r1, #0x78
	rsbs r1, r1, #0
	cmp r0, r1
	blt _08094584
	ldrb r0, [r5, #4]
	subs r0, r2, r0
	ldrb r2, [r5, #0x11]
	adds r1, r0, r2
	movs r4, #0
	strb r1, [r5, #0x11]
	ldrb r2, [r5, #0x1a]
	lsrs r0, r2, #4
	cmp r0, #0
	bne _08094558
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _08094584
	adds r0, r1, #0
	subs r0, #8
	strb r0, [r5, #0x11]
	ldrb r1, [r5, #0x12]
	lsls r1, r1, #1
	ldr r0, _08094550 @ =0x02010800
	adds r0, r1, r0
	ldr r2, _08094554 @ =0x0600F000
	adds r1, r1, r2
	movs r2, #1
	movs r3, #0x14
	bl Dma3Transfer_Unused2
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x20
	bne _08094584
	strb r4, [r5, #0x12]
	ldrb r0, [r5, #0x1a]
	movs r1, #0xf
	ands r1, r0
	movs r0, #0x10
	orrs r1, r0
	strb r1, [r5, #0x1a]
	b _08094584
	.align 2, 0
_08094544: .4byte 0x02070000
_08094548: .4byte 0x0300122C
_0809454C: .4byte 0x0300122E
_08094550: .4byte 0x02010800
_08094554: .4byte 0x0600F000
_08094558:
	cmp r0, #1
	bne _08094584
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _08094584
	adds r0, r1, #0
	subs r0, #8
	strb r0, [r5, #0x11]
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x20
	bne _08094584
	strb r4, [r5, #0x12]
	movs r0, #0xf
	ands r0, r2
	movs r1, #0xa0
	orrs r0, r1
	strb r0, [r5, #0x1a]
_08094584:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessSamusSHipEntering
IntroProcessSamusSHipEntering: @ 0x0809458C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	movs r4, #0
	ldrb r0, [r6, #0x14]
	cmp r0, #0
	bne _080945BC
	movs r0, #0x64
	strh r0, [r6]
	movs r0, #0x1e
	strh r0, [r6, #2]
	ldrh r0, [r6, #0xc]
	strh r0, [r6, #4]
	ldrh r0, [r6, #0xe]
	subs r0, #0x1e
	strh r0, [r6, #8]
	movs r0, #0x40
	strb r0, [r6, #0x13]
	movs r0, #1
	strb r0, [r6, #0x14]
	movs r0, #0xf5
	lsls r0, r0, #1
	bl SoundPlay
	b _08094676
_080945BC:
	cmp r0, #1
	bne _080945DE
	ldrb r1, [r6, #0x13]
	adds r1, #1
	strb r1, [r6, #0x13]
	ldrh r0, [r6, #6]
	subs r0, #2
	strh r0, [r6, #6]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	cmp r1, #0x80
	bne _08094676
	movs r0, #2
	strb r0, [r6, #0x14]
	adds r0, #0xfe
	strh r0, [r6, #6]
	b _08094676
_080945DE:
	cmp r0, #2
	bne _080945FA
	strh r4, [r6]
	movs r0, #8
	strh r0, [r6, #2]
	ldrh r0, [r6, #0xc]
	strh r0, [r6, #4]
	ldrh r0, [r6, #0xe]
	strh r0, [r6, #8]
	movs r0, #0x80
	strb r0, [r6, #0x13]
	movs r0, #3
	strb r0, [r6, #0x14]
	b _08094676
_080945FA:
	cmp r0, #3
	bne _08094612
	ldrb r0, [r6, #0x13]
	adds r0, #2
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xc0
	bne _08094676
	movs r0, #4
	strb r0, [r6, #0x14]
	b _08094676
_08094612:
	cmp r0, #4
	bne _08094634
	ldrb r0, [r6, #0x13]
	adds r0, #1
	strb r0, [r6, #0x13]
	ldrh r0, [r6, #0xa]
	adds r0, #1
	strh r0, [r6, #0xa]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08094676
	strh r4, [r6, #0xa]
	ldrh r0, [r6, #4]
	subs r0, #1
	strh r0, [r6, #4]
	b _08094676
_08094634:
	cmp r0, #5
	bne _0809465A
	ldrh r2, [r6, #0xc]
	movs r1, #0x8c
	lsls r1, r1, #1
	adds r0, r1, #0
	subs r0, r0, r2
	strh r0, [r6]
	movs r1, #0x3c
	strh r1, [r6, #2]
	adds r2, r2, r0
	strh r2, [r6, #4]
	ldrh r0, [r6, #0xe]
	strh r0, [r6, #8]
	movs r0, #0x80
	strb r0, [r6, #0x13]
	movs r0, #6
	strb r0, [r6, #0x14]
	b _08094676
_0809465A:
	cmp r0, #6
	bne _08094676
	ldrb r0, [r6, #0x13]
	adds r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094676
	strb r4, [r6, #0x10]
	ldrb r1, [r6, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r6, #0x18]
_08094676:
	movs r2, #0
	ldrsh r3, [r6, r2]
	ldr r2, _080946D4 @ =sSineTable
	ldrb r1, [r6, #0x13]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r4, #0
	ldrsh r0, [r0, r4]
	adds r5, r3, #0
	muls r5, r0, r5
	movs r0, #2
	ldrsh r3, [r6, r0]
	lsls r1, r1, #1
	adds r1, r1, r2
	movs r4, #0
	ldrsh r0, [r1, r4]
	adds r4, r3, #0
	muls r4, r0, r4
	adds r0, r2, #0
	adds r0, #0x80
	movs r1, #0
	ldrsh r3, [r0, r1]
	adds r1, r5, #0
	muls r1, r3, r1
	movs r0, #0
	ldrsh r2, [r2, r0]
	adds r0, r4, #0
	muls r0, r2, r0
	subs r1, r1, r0
	adds r0, r5, #0
	muls r0, r2, r0
	adds r2, r4, #0
	muls r2, r3, r2
	adds r0, r0, r2
	asrs r1, r1, #0x10
	ldrh r2, [r6, #4]
	adds r1, r1, r2
	strh r1, [r6, #0xc]
	asrs r0, r0, #0x10
	ldrh r4, [r6, #8]
	adds r0, r0, r4
	strh r0, [r6, #0xe]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080946D4: .4byte sSineTable

	thumb_func_start IntroProcessSplashText
IntroProcessSplashText: @ 0x080946D8
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _080946FE
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080946FE
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x18]
_080946FE:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessSpaceViewParticle
IntroProcessSpaceViewParticle: @ 0x08094704
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #0
	bne _08094740
	bl SpecialCutsceneGetRandomNumber
	movs r1, #7
	ands r1, r0
	adds r1, #1
	strh r1, [r4, #8]
	bl SpecialCutsceneGetRandomNumber
	movs r1, #3
	ands r1, r0
	strh r1, [r4, #4]
	ldr r1, _0809473C @ =sIntroUnk_79c394
	movs r2, #4
	ldrsh r0, [r4, r2]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r4, #0x1c]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08094792
	.align 2, 0
_0809473C: .4byte sIntroUnk_79c394
_08094740:
	cmp r0, #1
	bne _08094792
	ldrh r0, [r4, #0xa]
	adds r0, #1
	strh r0, [r4, #0xa]
	movs r0, #8
	ldrsh r1, [r4, r0]
	ldrh r0, [r4, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #4
	ldrh r1, [r4]
	adds r0, r0, r1
	strh r0, [r4, #0xc]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #8
	bne _08094792
	movs r0, #0
	strb r0, [r4, #0x13]
	ldrh r1, [r4, #4]
	movs r2, #4
	ldrsh r0, [r4, r2]
	cmp r0, #4
	bgt _0809477A
	adds r0, r1, #1
	b _0809477C
_0809477A:
	movs r0, #0
_0809477C:
	strh r0, [r4, #4]
	ldr r1, _080947B4 @ =sIntroUnk_79c394
	movs r2, #4
	ldrsh r0, [r4, r2]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r4, #0x1c]
	movs r0, #0
	strb r0, [r4, #0x12]
	strb r0, [r4, #0x11]
_08094792:
	movs r1, #0xc
	ldrsh r0, [r4, r1]
	cmp r0, #0xef
	bgt _080947A2
	movs r2, #0xe
	ldrsh r0, [r4, r2]
	cmp r0, #0x9f
	ble _080947AE
_080947A2:
	movs r0, #0
	strb r0, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	subs r0, #2
	ands r0, r1
	strb r0, [r4, #0x18]
_080947AE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080947B4: .4byte sIntroUnk_79c394

	thumb_func_start IntroProcessIdleShipBackview
IntroProcessIdleShipBackview: @ 0x080947B8
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080947D2
	strh r0, [r2, #0xa]
	ldrh r0, [r2, #0xc]
	strh r0, [r2]
	ldrh r0, [r2, #0xe]
	strh r0, [r2, #2]
	movs r0, #1
	strb r0, [r2, #0x14]
	b _080947F0
_080947D2:
	cmp r0, #1
	bne _080947F0
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	ldr r1, _080947F4 @ =sSineTable
	ldrb r0, [r2, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x15
	ldrh r1, [r2, #2]
	adds r0, r0, r1
	strh r0, [r2, #0xe]
_080947F0:
	pop {r0}
	bx r0
	.align 2, 0
_080947F4: .4byte sSineTable

	thumb_func_start IntroProcessBslShipSpawning_2
IntroProcessBslShipSpawning_2: @ 0x080947F8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0x14]
	cmp r5, #0
	bne _08094854
	ldrh r1, [r4, #0xc]
	adds r1, #0x7a
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xc
	movs r3, #0
	bl IntroSpaceViewSetupOam
	ldrh r1, [r4, #0xc]
	adds r1, #0x32
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldrh r2, [r4, #0xe]
	adds r2, #1
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	movs r0, #0xd
	movs r3, #0
	bl IntroSpaceViewSetupOam
	ldrh r1, [r4, #0xc]
	adds r1, #0x24
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xe
	movs r3, #0
	bl IntroSpaceViewSetupOam
	movs r0, #0xc
	ldrsh r1, [r4, r0]
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #0xf
	movs r3, #0
	bl IntroSpaceViewSetupOam
	strb r5, [r4, #0x10]
_08094854:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessBslShipBackview
IntroProcessBslShipBackview: @ 0x0809485C
	push {r4, lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0x14]
	cmp r3, #0
	bne _080948BA
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _0809492C
	ldrh r0, [r2]
	adds r0, #1
	movs r1, #0
	strh r0, [r2]
	strb r1, [r2, #0x13]
	ldrh r0, [r2, #0xa]
	cmp r0, #4
	bne _08094886
	strh r3, [r2, #0xa]
_08094886:
	ldrh r0, [r2, #0xa]
	adds r1, r0, #0
	adds r3, r0, #0
	cmp r1, #1
	bhi _08094896
	ldrh r0, [r2, #0xe]
	adds r0, #1
	b _0809489E
_08094896:
	cmp r1, #3
	bhi _080948A0
	ldrh r0, [r2, #0xe]
	subs r0, #1
_0809489E:
	strh r0, [r2, #0xe]
_080948A0:
	movs r0, #0
	ldrsh r1, [r2, r0]
	movs r0, #0x96
	lsls r0, r0, #1
	cmp r1, r0
	bne _080948B4
	movs r1, #0
	movs r0, #1
	strb r0, [r2, #0x14]
	strb r1, [r2, #0x13]
_080948B4:
	adds r0, r3, #1
	strh r0, [r2, #0xa]
	b _0809492C
_080948BA:
	cmp r3, #1
	bne _080948CE
	ldrh r0, [r2, #0xc]
	movs r1, #0
	strh r0, [r2]
	ldrh r0, [r2, #0xe]
	strh r0, [r2, #2]
	strh r1, [r2, #0xa]
	movs r0, #2
	b _0809492A
_080948CE:
	cmp r3, #2
	bne _0809492C
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _080948EA
	ldrh r0, [r2, #0xa]
	adds r0, #1
	movs r1, #0
	strh r0, [r2, #0xa]
	strb r1, [r2, #0x13]
_080948EA:
	movs r4, #0
	ldrsh r1, [r2, r4]
	movs r0, #0xe1
	lsls r0, r0, #2
	subs r0, r0, r1
	ldrh r1, [r2, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xc
	ldrh r1, [r2]
	adds r3, r0, r1
	strh r3, [r2, #0xc]
	movs r4, #4
	ldrsh r0, [r2, r4]
	movs r4, #2
	ldrsh r1, [r2, r4]
	subs r0, r0, r1
	ldrh r1, [r2, #0xa]
	muls r0, r1, r0
	asrs r0, r0, #0xb
	ldrh r1, [r2, #2]
	adds r4, r0, r1
	strh r4, [r2, #0xe]
	lsls r1, r3, #0x10
	movs r0, #0xa0
	lsls r0, r0, #0x11
	cmp r1, r0
	ble _0809492C
	movs r0, #0
	strh r0, [r2, #0xa]
	strh r3, [r2]
	strh r4, [r2, #2]
	movs r0, #3
_0809492A:
	strb r0, [r2, #0x14]
_0809492C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroProcessIdleDepthParticle
IntroProcessIdleDepthParticle: @ 0x08094934
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrh r1, [r6, #0xa]
	strh r1, [r6, #4]
	ldrb r0, [r6, #0x14]
	cmp r0, #0
	bne _0809495E
	movs r1, #0xc
	ldrsh r0, [r6, r1]
	subs r0, #0x78
	movs r1, #0x64
	muls r0, r1, r0
	strh r0, [r6]
	movs r2, #0xe
	ldrsh r0, [r6, r2]
	subs r0, #0x50
	muls r0, r1, r0
	strh r0, [r6, #2]
	movs r0, #1
	strb r0, [r6, #0x14]
	b _080949EA
_0809495E:
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x63
	bgt _080949DC
	cmp r0, #0x19
	bne _08094974
	ldr r0, _08094970 @ =sIntroUnk_60ac18
	b _08094986
	.align 2, 0
_08094970: .4byte sIntroUnk_60ac18
_08094974:
	cmp r0, #0x32
	bne _08094980
	ldr r0, _0809497C @ =sIntroUnk_60ac28
	b _08094986
	.align 2, 0
_0809497C: .4byte sIntroUnk_60ac28
_08094980:
	cmp r0, #0x46
	bne _08094988
	ldr r0, _080949D8 @ =sIntroUnk_60ac38
_08094986:
	str r0, [r6, #0x1c]
_08094988:
	movs r0, #4
	ldrsh r4, [r6, r0]
	rsbs r4, r4, #0
	adds r4, #0x64
	movs r1, #0
	ldrsh r0, [r6, r1]
	adds r1, r4, #0
	bl __divsi3
	adds r5, r0, #0
	adds r0, #0x78
	strh r0, [r6, #0xc]
	movs r2, #2
	ldrsh r0, [r6, r2]
	adds r1, r4, #0
	bl __divsi3
	adds r1, r0, #0
	adds r1, #0x50
	strh r1, [r6, #0xe]
	adds r5, #0x80
	lsls r5, r5, #0x10
	movs r0, #0x80
	lsls r0, r0, #0x11
	cmp r5, r0
	bhi _080949CC
	lsls r0, r1, #0x10
	asrs r1, r0, #0x10
	cmp r1, #0xa8
	bgt _080949CC
	movs r0, #8
	rsbs r0, r0, #0
	cmp r1, r0
	bge _080949EA
_080949CC:
	movs r0, #0
	strb r0, [r6, #0x10]
	ldrb r1, [r6, #0x18]
	subs r0, #2
	b _080949E6
	.align 2, 0
_080949D8: .4byte sIntroUnk_60ac38
_080949DC:
	movs r0, #0
	strb r0, [r6, #0x10]
	ldrb r1, [r6, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
_080949E6:
	ands r0, r1
	strb r0, [r6, #0x18]
_080949EA:
	ldrh r0, [r6, #0xa]
	adds r0, #1
	strh r0, [r6, #0xa]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start IntroSpaceViewSetupOam
IntroSpaceViewSetupOam: @ 0x080949F8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov sb, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sl, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _08094A60
	movs r2, #0
	ldr r0, _08094A5C @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r1, r0, r3
	ldrb r1, [r1]
	mov r8, r0
	cmp r1, #0
	beq _08094A4E
	mov r4, r8
_08094A2E:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08094AA0
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08094A2E
_08094A4E:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	mov ip, r0
	cmp r1, #0x13
	ble _08094AA8
	b _08094AA0
	.align 2, 0
_08094A5C: .4byte gNonGameplayRam
_08094A60:
	movs r2, #0x13
	ldr r0, _08094AA4 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r1, r0, r3
	ldrb r1, [r1]
	mov r8, r0
	cmp r1, #0
	beq _08094A98
	mov r4, r8
	movs r3, #0x8b
	lsls r3, r3, #2
_08094A78:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08094AA0
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08094A78
_08094A98:
	lsls r0, r2, #0x18
	mov ip, r0
	cmp r0, #0
	bge _08094AA8
_08094AA0:
	movs r0, #0x14
	b _08094DD0
	.align 2, 0
_08094AA4: .4byte gNonGameplayRam
_08094AA8:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08094B10 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	mov r0, ip
	asrs r1, r0, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r4, r0, #2
	ldr r3, _08094B14 @ =0x030016A0
	adds r0, r4, r3
	str r0, [r2, #4]
	ldr r0, _08094B18 @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _08094B1C @ =0xFFFFFDE4
	adds r0, r3, r1
	adds r2, r4, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	movs r7, #0
	mov r1, sb
	strh r1, [r0]
	ldr r1, _08094B20 @ =0x0000022A
	adds r0, r2, r1
	mov r1, sl
	strh r1, [r0]
	movs r1, #0x8b
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r6, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r5, r2, r0
	ldrb r1, [r5]
	movs r0, #1
	orrs r1, r0
	strb r1, [r5]
	cmp r6, #1
	bne _08094B28
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r5]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094B24 @ =IntroProcessSpaceViewScrolling
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094B10: .4byte 0x040000D4
_08094B14: .4byte 0x030016A0
_08094B18: .4byte 0x85000009
_08094B1C: .4byte 0xFFFFFDE4
_08094B20: .4byte 0x0000022A
_08094B24: .4byte IntroProcessSpaceViewScrolling
_08094B28:
	cmp r6, #2
	bne _08094B44
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r5]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094B40 @ =IntroProcessBslShipSideways
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094B40: .4byte IntroProcessBslShipSideways
_08094B44:
	cmp r6, #3
	bne _08094B90
	ldr r0, _08094B80 @ =0x00000222
	adds r1, r2, r0
	subs r0, #0xa2
	strh r0, [r1]
	ldr r1, _08094B84 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r5]
	movs r1, #6
	orrs r0, r1
	strb r0, [r5]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094B88 @ =sIntroUnk_60ac98
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094B8C @ =IntroProcessSamusSHipEntering
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094B80: .4byte 0x00000222
_08094B84: .4byte 0x00000236
_08094B88: .4byte sIntroUnk_60ac98
_08094B8C: .4byte IntroProcessSamusSHipEntering
_08094B90:
	cmp r6, #4
	bne _08094BB4
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094BAC @ =sIntroUnk_60af10
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094BB0 @ =IntroProcessSplashText
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094BAC: .4byte sIntroUnk_60af10
_08094BB0: .4byte IntroProcessSplashText
_08094BB4:
	cmp r6, #5
	bne _08094BE8
	ldr r0, _08094BDC @ =0x00000236
	adds r2, r2, r0
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094BE0 @ =sIntroUnk_60ac38
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094BE4 @ =IntroProcessSpaceViewParticle
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094BDC: .4byte 0x00000236
_08094BE0: .4byte sIntroUnk_60ac38
_08094BE4: .4byte IntroProcessSpaceViewParticle
_08094BE8:
	cmp r6, #0xa
	bne _08094C54
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	mov r1, sb
	strh r1, [r0]
	ldr r1, _08094C40 @ =0x0000021E
	adds r0, r2, r1
	mov r1, sl
	strh r1, [r0]
	ldr r0, _08094C44 @ =0x00000222
	adds r1, r2, r0
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r1, _08094C48 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	ldrb r1, [r5]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094C4C @ =sIntroUnk_60acd0
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094C50 @ =IntroProcessIdleShipBackview
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094C40: .4byte 0x0000021E
_08094C44: .4byte 0x00000222
_08094C48: .4byte 0x00000236
_08094C4C: .4byte sIntroUnk_60acd0
_08094C50: .4byte IntroProcessIdleShipBackview
_08094C54:
	cmp r6, #0xb
	bne _08094C80
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r5]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094C78 @ =sIntroUnk_60acd0
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094C7C @ =IntroProcessBslShipSpawning_2
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094C78: .4byte sIntroUnk_60acd0
_08094C7C: .4byte IntroProcessBslShipSpawning_2
_08094C80:
	cmp r6, #0xc
	bne _08094CB8
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _08094CAC @ =0x0000FFD8
	strh r0, [r1]
	ldr r1, _08094CB0 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094CB4 @ =sIntroUnk_60ad28
	b _08094D18
	.align 2, 0
_08094CAC: .4byte 0x0000FFD8
_08094CB0: .4byte 0x00000236
_08094CB4: .4byte sIntroUnk_60ad28
_08094CB8:
	cmp r6, #0xd
	bne _08094CF0
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _08094CE4 @ =0x0000FFE2
	strh r0, [r1]
	ldr r1, _08094CE8 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094CEC @ =sIntroUnk_60ad18
	b _08094D18
	.align 2, 0
_08094CE4: .4byte 0x0000FFE2
_08094CE8: .4byte 0x00000236
_08094CEC: .4byte sIntroUnk_60ad18
_08094CF0:
	cmp r6, #0xe
	bne _08094D38
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _08094D28 @ =0x0000FFEC
	strh r0, [r1]
	ldr r1, _08094D2C @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08094D30 @ =sIntroUnk_60ad08
_08094D18:
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08094D34 @ =IntroProcessBslShipBackview
	str r1, [r0]
	b _08094DCC
	.align 2, 0
_08094D28: .4byte 0x0000FFEC
_08094D2C: .4byte 0x00000236
_08094D30: .4byte sIntroUnk_60ad08
_08094D34: .4byte IntroProcessBslShipBackview
_08094D38:
	cmp r6, #0xf
	bne _08094D90
	mov r3, ip
	asrs r0, r3, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r0, r8
	adds r3, r2, r0
	movs r0, #0x88
	lsls r0, r0, #2
	adds r1, r3, r0
	ldr r0, _08094D80 @ =0x0000FFF6
	strh r0, [r1]
	ldr r1, _08094D84 @ =0x00000236
	adds r3, r3, r1
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _08094D88 @ =sIntroUnk_60acf8
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, r8
	adds r2, r2, r0
	ldr r0, _08094D8C @ =IntroProcessBslShipBackview
	b _08094DCA
	.align 2, 0
_08094D80: .4byte 0x0000FFF6
_08094D84: .4byte 0x00000236
_08094D88: .4byte sIntroUnk_60acf8
_08094D8C: .4byte IntroProcessBslShipBackview
_08094D90:
	cmp r6, #0x10
	bne _08094DCC
	mov r3, ip
	asrs r0, r3, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r0, r8
	adds r3, r2, r0
	ldr r1, _08094DE0 @ =0x00000236
	adds r3, r3, r1
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, r8
	adds r0, r2, r0
	ldr r1, _08094DE4 @ =sIntroUnk_60ac08
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, r8
	adds r2, r2, r0
	ldr r0, _08094DE8 @ =IntroProcessIdleDepthParticle
_08094DCA:
	str r0, [r2]
_08094DCC:
	mov r3, ip
	lsrs r0, r3, #0x18
_08094DD0:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08094DE0: .4byte 0x00000236
_08094DE4: .4byte sIntroUnk_60ac08
_08094DE8: .4byte IntroProcessIdleDepthParticle

	thumb_func_start IntroSpaceViewVblank
IntroSpaceViewVblank: @ 0x08094DEC
	ldr r1, _08094E48 @ =0x040000D4
	ldr r0, _08094E4C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08094E50 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08094E54 @ =0x04000052
	ldr r0, _08094E58 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08094E5C @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08094E60 @ =0x04000054
	ldr r0, _08094E64 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08094E68 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08094E6C @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08094E70 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08094E74 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08094E78 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08094E7C @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08094E48: .4byte 0x040000D4
_08094E4C: .4byte gOamData
_08094E50: .4byte 0x84000100
_08094E54: .4byte 0x04000052
_08094E58: .4byte gWrittenToBldalpha_Evb
_08094E5C: .4byte gWrittenToBldalpha_Eva
_08094E60: .4byte 0x04000054
_08094E64: .4byte gWrittenToBldy
_08094E68: .4byte gBg1XPosition
_08094E6C: .4byte gBg1YPosition
_08094E70: .4byte 0x0300122C
_08094E74: .4byte 0x0300122E
_08094E78: .4byte 0x03001230
_08094E7C: .4byte 0x03001232

	thumb_func_start unk_94e80
unk_94e80: @ 0x08094E80
	bx lr
	.align 2, 0

	thumb_func_start EndingHandler
EndingHandler: @ 0x08094E84
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	ldr r4, _08094EA0 @ =gSubGameMode1
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #1
	beq _08094ED4
	cmp r0, #1
	bgt _08094EA4
	cmp r0, #0
	beq _08094EAE
	b _08094F6A
	.align 2, 0
_08094EA0: .4byte gSubGameMode1
_08094EA4:
	cmp r0, #2
	beq _08094EE2
	cmp r0, #3
	beq _08094F00
	b _08094F6A
_08094EAE:
	str r5, [sp]
	ldr r1, _08094EC8 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _08094ECC @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08094ED0 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #1
	strh r0, [r4]
	b _08094F6A
	.align 2, 0
_08094EC8: .4byte 0x040000D4
_08094ECC: .4byte gNonGameplayRam
_08094ED0: .4byte 0x85000150
_08094ED4:
	bl EndingBslCrashing
	cmp r0, #0
	beq _08094F6A
	movs r0, #2
	strh r0, [r4]
	b _08094F6A
_08094EE2:
	bl EndingInShip
	cmp r0, #0
	beq _08094F6A
	ldr r0, _08094EF8 @ =gNonGameplayRam
	ldr r1, _08094EFC @ =0x0000020E
	adds r0, r0, r1
	strh r5, [r0]
	movs r0, #3
	strh r0, [r4]
	b _08094F6A
	.align 2, 0
_08094EF8: .4byte gNonGameplayRam
_08094EFC: .4byte 0x0000020E
_08094F00:
	ldr r0, _08094F24 @ =gNonGameplayRam
	ldr r1, _08094F28 @ =0x0000020E
	adds r4, r0, r1
	ldrh r0, [r4]
	adds r0, #1
	strh r0, [r4]
	ldr r2, _08094F2C @ =gWrittenToBldy
	ldrh r1, [r2]
	cmp r1, #0xf
	bhi _08094F30
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #1
	bne _08094F66
	strh r5, [r4]
	adds r0, r1, #1
	strh r0, [r2]
	b _08094F66
	.align 2, 0
_08094F24: .4byte gNonGameplayRam
_08094F28: .4byte 0x0000020E
_08094F2C: .4byte gWrittenToBldy
_08094F30:
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #1
	bne _08094F40
	movs r0, #0
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F40:
	cmp r0, #2
	bne _08094F4C
	movs r0, #1
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F4C:
	cmp r0, #3
	bne _08094F58
	movs r0, #2
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F58:
	cmp r0, #4
	bne _08094F66
	movs r0, #3
	bl Sram_ProcessEndingSave
	strh r5, [r4]
	movs r5, #1
_08094F66:
	bl SpecialCutsceneDrawAllOam
_08094F6A:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingBslCrashingInit
EndingBslCrashingInit: @ 0x08094F74
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _080950DC @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080950E0 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080950E4 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080950E8 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080950EC @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080950F0 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080950F4 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _080950F8 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _080950FC @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095100 @ =sSr388CollisionUnk_6238f4
	ldr r1, _08095104 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08095108 @ =sSr388CollisionUnk_636c38
	str r0, [r4]
	ldr r0, _0809510C @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _08095110 @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095114 @ =sSr388CollisionUnk_62b5f4
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08095118 @ =sSr388CollisionUnk_638c14
	ldr r1, _0809511C @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08095120 @ =sSr388CollisionUnk_639bc4
	ldr r1, _08095124 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095128 @ =sSr388CollisionUnk_637038
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809512C @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _08095130 @ =gBg1YPosition
	movs r2, #8
	strh r2, [r0]
	ldr r0, _08095134 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08095138 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _0809513C @ =0x03001230
	strh r5, [r0]
	ldr r0, _08095140 @ =0x03001232
	strh r5, [r0]
	ldr r0, _08095144 @ =0x04000010
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
	ldr r1, _08095148 @ =0x04000008
	ldr r3, _0809514C @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r3, _08095150 @ =0x00001E01
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #4
	ldr r3, _08095154 @ =0x00001F03
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08095158 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _0809515C @ =0x04000054
	strh r1, [r0]
	ldr r0, _08095160 @ =gWrittenToBldalpha_Eva
	strh r2, [r0]
	ldr r1, _08095164 @ =gWrittenToBldalpha_Evb
	movs r0, #0xe
	strh r0, [r1]
	movs r1, #0x28
	rsbs r1, r1, #0
	movs r0, #5
	movs r2, #0xc8
	movs r3, #0
	bl EndingBslCrashingSetupOam
	movs r0, #4
	movs r1, #0x80
	movs r2, #0x48
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #2
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #1
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #3
	movs r1, #0x86
	movs r2, #0x3c
	movs r3, #1
	bl EndingBslCrashingSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08095168 @ =sCutsceneTextNone
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809516C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08095170 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _08095174 @ =EndingBslCrashingVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080950DC: .4byte 0x04000208
_080950E0: .4byte 0x04000004
_080950E4: .4byte 0x0000FFEF
_080950E8: .4byte 0x04000200
_080950EC: .4byte 0x0000FFFD
_080950F0: .4byte unk_99940
_080950F4: .4byte 0x040000D4
_080950F8: .4byte gNonGameplayRam
_080950FC: .4byte 0x85000150
_08095100: .4byte sSr388CollisionUnk_6238f4
_08095104: .4byte 0x06010000
_08095108: .4byte sSr388CollisionUnk_636c38
_0809510C: .4byte 0x05000200
_08095110: .4byte 0x84000080
_08095114: .4byte sSr388CollisionUnk_62b5f4
_08095118: .4byte sSr388CollisionUnk_638c14
_0809511C: .4byte 0x0600F000
_08095120: .4byte sSr388CollisionUnk_639bc4
_08095124: .4byte 0x0600F800
_08095128: .4byte sSr388CollisionUnk_637038
_0809512C: .4byte gBg1XPosition
_08095130: .4byte gBg1YPosition
_08095134: .4byte 0x0300122C
_08095138: .4byte 0x0300122E
_0809513C: .4byte 0x03001230
_08095140: .4byte 0x03001232
_08095144: .4byte 0x04000010
_08095148: .4byte 0x04000008
_0809514C: .4byte 0x00001C08
_08095150: .4byte 0x00001E01
_08095154: .4byte 0x00001F03
_08095158: .4byte gWrittenToBldy
_0809515C: .4byte 0x04000054
_08095160: .4byte gWrittenToBldalpha_Eva
_08095164: .4byte gWrittenToBldalpha_Evb
_08095168: .4byte sCutsceneTextNone
_0809516C: .4byte 0x0600D000
_08095170: .4byte 0x85000400
_08095174: .4byte EndingBslCrashingVblank

	thumb_func_start EndingShipFrontViewInit
EndingShipFrontViewInit: @ 0x08095178
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, _080952D4 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080952D8 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080952DC @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080952E0 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080952E4 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080952E8 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080952EC @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r6, _080952F0 @ =0x030016A0
	str r6, [r4, #4]
	ldr r0, _080952F4 @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r1, sp, #4
	strh r5, [r1]
	str r1, [r4]
	ldr r2, _080952F8 @ =0xFFFFFDF8
	adds r0, r6, r2
	str r0, [r4, #4]
	ldr r2, _080952FC @ =0x8100007E
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r1]
	str r1, [r4]
	ldr r1, _08095300 @ =0xFFFFFEF4
	adds r0, r6, r1
	str r0, [r4, #4]
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095304 @ =sEndingUnk_626738
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08095308 @ =sEndingUnk_63929c
	ldr r1, _0809530C @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08095310 @ =sEndingUnk_6395b8
	ldr r1, _08095314 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095318 @ =sEndingUnk_636e38
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _0809531C @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095320 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _08095324 @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _08095328 @ =0x0300122C
	strh r5, [r0]
	ldr r3, _0809532C @ =0x0300122E
	ldr r2, _08095330 @ =0x0000FFE2
	adds r0, r2, #0
	strh r0, [r3]
	ldr r0, _08095334 @ =0x03001230
	strh r5, [r0]
	ldr r0, _08095338 @ =0x03001232
	strh r5, [r0]
	ldr r0, _0809533C @ =0x04000010
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
	strh r5, [r0]
	ldr r1, _08095340 @ =0x04000008
	ldr r2, _08095344 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08095348 @ =0x00001E02
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0809534C @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xbf
	strh r0, [r1]
	ldr r0, _08095350 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08095354 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08095358 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809535C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08095360 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	ldrsh r2, [r3, r0]
	movs r0, #0xc
	movs r1, #0
	movs r3, #0
	bl EndingBslCrashingSetupOam
	movs r0, #0xa
	movs r1, #0x78
	movs r2, #0x6a
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #0xb
	movs r1, #0x78
	movs r2, #0x40
	movs r3, #0
	bl EndingBslCrashingSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08095364 @ =0xFFFFFDE4
	adds r6, r6, r1
	ldr r0, _08095368 @ =sCutsceneTextNone
	str r0, [r6]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809536C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08095370 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08095374 @ =EndingShipFrontViewVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080952D4: .4byte 0x04000208
_080952D8: .4byte 0x04000004
_080952DC: .4byte 0x0000FFEF
_080952E0: .4byte 0x04000200
_080952E4: .4byte 0x0000FFFD
_080952E8: .4byte unk_99940
_080952EC: .4byte 0x040000D4
_080952F0: .4byte 0x030016A0
_080952F4: .4byte 0x850000B4
_080952F8: .4byte 0xFFFFFDF8
_080952FC: .4byte 0x8100007E
_08095300: .4byte 0xFFFFFEF4
_08095304: .4byte sEndingUnk_626738
_08095308: .4byte sEndingUnk_63929c
_0809530C: .4byte 0x0600F000
_08095310: .4byte sEndingUnk_6395b8
_08095314: .4byte 0x0600F800
_08095318: .4byte sEndingUnk_636e38
_0809531C: .4byte 0x84000080
_08095320: .4byte gBg1XPosition
_08095324: .4byte gBg1YPosition
_08095328: .4byte 0x0300122C
_0809532C: .4byte 0x0300122E
_08095330: .4byte 0x0000FFE2
_08095334: .4byte 0x03001230
_08095338: .4byte 0x03001232
_0809533C: .4byte 0x04000010
_08095340: .4byte 0x04000008
_08095344: .4byte 0x00001C08
_08095348: .4byte 0x00001E02
_0809534C: .4byte 0x00001F03
_08095350: .4byte gWrittenToBldy
_08095354: .4byte 0x04000054
_08095358: .4byte gWrittenToBldalpha_Eva
_0809535C: .4byte gWrittenToBldalpha_Evb
_08095360: .4byte 0x04000052
_08095364: .4byte 0xFFFFFDE4
_08095368: .4byte sCutsceneTextNone
_0809536C: .4byte 0x0600D000
_08095370: .4byte 0x85000400
_08095374: .4byte EndingShipFrontViewVblank

	thumb_func_start EndingBslCrashingProcess
EndingBslCrashingProcess: @ 0x08095378
	push {r4, r5, r6, lr}
	movs r5, #0
	ldr r2, _080953A4 @ =gNonGameplayRam
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
	cmp r0, #9
	bls _0809539A
	b _08095634
_0809539A:
	lsls r0, r0, #2
	ldr r1, _080953A8 @ =_080953AC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080953A4: .4byte gNonGameplayRam
_080953A8: .4byte _080953AC
_080953AC: @ jump table
	.4byte _080953D4 @ case 0
	.4byte _08095418 @ case 1
	.4byte _08095424 @ case 2
	.4byte _0809548C @ case 3
	.4byte _080954E4 @ case 4
	.4byte _08095534 @ case 5
	.4byte _08095556 @ case 6
	.4byte _08095578 @ case 7
	.4byte _0809559C @ case 8
	.4byte _080955EC @ case 9
_080953D4:
	ldr r4, _080953F0 @ =gWrittenToBldy
	ldrh r2, [r4]
	cmp r2, #0
	beq _080953F8
	cmp r2, #0x10
	bne _080953E6
	ldr r0, _080953F4 @ =0x0000024B
	bl SoundPlay_3b1c
_080953E6:
	ldrh r0, [r4]
	subs r0, #1
	strh r0, [r4]
	b _080955DC
	.align 2, 0
_080953F0: .4byte gWrittenToBldy
_080953F4: .4byte 0x0000024B
_080953F8:
	ldr r1, _08095414 @ =0x04000050
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
	b _080955DA
	.align 2, 0
_08095414: .4byte 0x04000050
_08095418:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	b _080955DC
_08095424:
	movs r6, #0x84
	lsls r6, r6, #2
	adds r4, r3, r6
	ldrh r2, [r4]
	cmp r2, #1
	bne _08095458
	ldr r0, _0809544C @ =gWrittenToBldalpha_Eva
	movs r1, #0xa
	strh r1, [r0]
	ldr r0, _08095450 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x88
	lsls r1, r1, #1
	adds r0, r3, r1
	movs r1, #0
	strb r2, [r0]
	ldr r2, _08095454 @ =0x00000111
	adds r0, r3, r2
	strb r1, [r0]
	b _080955DC
	.align 2, 0
_0809544C: .4byte gWrittenToBldalpha_Eva
_08095450: .4byte gWrittenToBldalpha_Evb
_08095454: .4byte 0x00000111
_08095458:
	cmp r2, #2
	beq _0809545E
	b _080955DC
_0809545E:
	ldr r1, _08095484 @ =0x04000050
	ldr r6, _08095488 @ =0x00000842
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
	b _080955DA
	.align 2, 0
_08095484: .4byte 0x04000050
_08095488: .4byte 0x00000842
_0809548C:
	ldr r1, _080954B8 @ =0x00000111
	adds r4, r3, r1
	ldrb r2, [r4]
	cmp r2, #0xe
	bhi _080954BC
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #4
	beq _080954A4
	b _080955DC
_080954A4:
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r3, r0
	movs r0, #1
	strb r0, [r1]
	adds r0, r2, #1
	strb r0, [r4]
	b _080955DC
	.align 2, 0
_080954B8: .4byte 0x00000111
_080954BC:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	ldrh r0, [r1]
	cmp r0, #0x14
	beq _080954CA
	b _080955DC
_080954CA:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080954E0 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #4
	b _080955DA
	.align 2, 0
_080954E0: .4byte gWrittenToBldy
_080954E4:
	ldr r4, _0809550C @ =gWrittenToBldalpha_Eva
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08095514
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #6
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	adds r0, r2, #1
	strh r0, [r4]
	ldr r1, _08095510 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	b _080955DC
	.align 2, 0
_0809550C: .4byte gWrittenToBldalpha_Eva
_08095510: .4byte gWrittenToBldalpha_Evb
_08095514:
	ldr r1, _08095530 @ =0x04000050
	movs r0, #0xbf
	strh r0, [r1]
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #0
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #5
	b _080955DA
	.align 2, 0
_08095530: .4byte 0x04000050
_08095534:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	ldrh r0, [r1]
	cmp r0, #0xa
	beq _08095542
	b _08095634
_08095542:
	movs r0, #0
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #6
	strb r0, [r1]
	bl EndingShipFrontViewInit
	b _08095634
_08095556:
	ldr r1, _08095574 @ =0x04000050
	movs r2, #0xc4
	lsls r2, r2, #4
	adds r0, r2, #0
	strh r0, [r1]
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #7
	b _080955DA
	.align 2, 0
_08095574: .4byte 0x04000050
_08095578:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #0xa8
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08095598 @ =gWrittenToBldy
	movs r0, #2
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #8
	b _080955DA
	.align 2, 0
_08095598: .4byte gWrittenToBldy
_0809559C:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	ldrh r0, [r1]
	cmp r0, #1
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080955C8 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	cmp r0, #0
	beq _080955CC
	subs r0, #1
	strh r0, [r1]
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080955DC
	movs r0, #0xa
	bl SpecialCutsceneDestroyOamOfType
	b _080955DC
	.align 2, 0
_080955C8: .4byte gWrittenToBldalpha_Eva
_080955CC:
	ldr r1, _080955E8 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #9
_080955DA:
	strb r0, [r1]
_080955DC:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08095634
	.align 2, 0
_080955E8: .4byte 0x04000050
_080955EC:
	ldr r4, _0809560C @ =gWrittenToBldy
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08095610
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #4
	bne _0809562C
	adds r0, r2, #1
	strh r0, [r4]
	movs r0, #0
	strh r0, [r1]
	b _0809562C
	.align 2, 0
_0809560C: .4byte gWrittenToBldy
_08095610:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r2, r3, r1
	ldrh r0, [r2]
	cmp r0, #0x5a
	bne _0809562C
	movs r0, #0
	movs r1, #0
	strh r1, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	strb r0, [r1]
	movs r5, #1
_0809562C:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08095634:
	adds r0, r5, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1

	thumb_func_start EndingBslCrashing
EndingBslCrashing: @ 0x0809563C
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08095654 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _08095668
	cmp r0, #1
	bgt _08095658
	cmp r0, #0
	beq _08095662
	b _080956BC
	.align 2, 0
_08095654: .4byte gNonGameplayRam
_08095658:
	cmp r0, #2
	beq _08095680
	cmp r0, #3
	beq _0809569C
	b _080956BC
_08095662:
	bl EndingBslCrashingInit
	b _08095674
_08095668:
	bl SpecialCutsceneFadeIn
	ldr r0, _0809567C @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080956BC
_08095674:
	movs r0, #2
	strh r0, [r4, #8]
	b _080956BC
	.align 2, 0
_0809567C: .4byte gWrittenToBldy
_08095680:
	bl EndingBslCrashingProcess
	cmp r0, #0
	beq _080956BC
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080956BC
_0809569C:
	ldr r1, _080956AC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080956B0
	adds r0, #1
	strh r0, [r1]
	b _080956B4
	.align 2, 0
_080956AC: .4byte gWrittenToBldy
_080956B0:
	strh r5, [r4, #8]
	movs r5, #1
_080956B4:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080956BC:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingProcessFallingBsl
EndingProcessFallingBsl: @ 0x080956C4
	push {r4, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #0xa]
	adds r0, #1
	movs r2, #0
	strh r0, [r4, #0xa]
	ldrb r1, [r4, #0x14]
	cmp r1, #0
	bne _080956E6
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strh r1, [r4, #0xa]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08095796
_080956E6:
	cmp r1, #1
	bne _08095744
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08095702
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08095702
	strb r2, [r4, #0x12]
_08095702:
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
	ble _0809572E
	movs r0, #0
	strh r0, [r4, #0xa]
	movs r0, #2
	strb r0, [r4, #0x14]
_0809572E:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0809573C
	ldrh r0, [r4, #6]
	subs r0, #1
	strh r0, [r4, #6]
	b _08095796
_0809573C:
	ldrh r0, [r4, #6]
	subs r0, #2
	strh r0, [r4, #6]
	b _08095796
_08095744:
	cmp r1, #2
	bne _08095770
	movs r0, #3
	strb r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0809578A
	ldr r0, _08095768 @ =sSr388CollisionUnk_6362b8
	str r0, [r4, #0x1c]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _0809576C @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	strb r1, [r0]
	b _08095796
	.align 2, 0
_08095768: .4byte sSr388CollisionUnk_6362b8
_0809576C: .4byte gNonGameplayRam
_08095770:
	cmp r1, #3
	bne _08095796
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08095796
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08095796
_0809578A:
	strb r2, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_08095796:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_9579c
unk_9579c: @ 0x0809579C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080957C8
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _080957C8
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080957C8
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x18]
_080957C8:
	pop {r0}
	bx r0

	thumb_func_start EndingProcessLeavingSmallShip
EndingProcessLeavingSmallShip: @ 0x080957CC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrh r0, [r5, #0xa]
	adds r2, r0, #1
	strh r2, [r5, #0xa]
	ldrb r1, [r5, #0x14]
	cmp r1, #0
	bne _080957FC
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x96
	bne _0809582A
	strh r1, [r5, #0xa]
	ldrb r0, [r5, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0x18]
	movs r0, #1
	strb r0, [r5, #0x14]
	b _0809582A
_080957FC:
	cmp r1, #1
	bne _0809582A
	lsls r0, r2, #2
	ldrh r4, [r5]
	subs r4, r4, r0
	strh r4, [r5, #0xc]
	ldrh r0, [r5, #0xa]
	movs r1, #3
	bl __udivsi3
	ldrh r1, [r5, #2]
	adds r1, r1, r0
	strh r1, [r5, #0xe]
	lsls r4, r4, #0x10
	cmp r4, #0
	bge _0809582A
	movs r0, #0
	strb r0, [r5, #0x10]
	ldrb r1, [r5, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
_0809582A:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessLeavingBigShip
EndingProcessLeavingBigShip: @ 0x08095830
	push {lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r2, r0, #1
	strh r2, [r3, #0xa]
	ldrb r1, [r3, #0x14]
	cmp r1, #0
	bne _08095860
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf0
	bne _08095890
	strh r1, [r3, #0xa]
	ldrb r0, [r3, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r3, #0x18]
	movs r0, #1
	strb r0, [r3, #0x14]
	b _08095890
_08095860:
	cmp r1, #1
	bne _08095890
	lsls r2, r2, #2
	ldrh r0, [r3]
	adds r2, r2, r0
	strh r2, [r3, #0xc]
	ldrh r0, [r3, #0xa]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldrh r0, [r3, #2]
	subs r0, r0, r1
	strh r0, [r3, #0xe]
	lsls r2, r2, #0x10
	movs r0, #0x8c
	lsls r0, r0, #0x11
	cmp r2, r0
	ble _08095890
	movs r0, #0
	strb r0, [r3, #0x10]
	ldrb r1, [r3, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3, #0x18]
_08095890:
	pop {r0}
	bx r0

	thumb_func_start EndingProcessFrontFacingShipThrusters
EndingProcessFrontFacingShipThrusters: @ 0x08095894
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r0, [r5, #0x14]
	cmp r0, #0
	bne _080958A8
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	movs r0, #1
	strb r0, [r5, #0x14]
_080958A8:
	mov r4, sp
	adds r4, #2
	movs r0, #0xc
	mov r1, sp
	adds r2, r4, #0
	bl EndingGetPositionAndSlotOfOamByType
	ldrh r0, [r5, #2]
	ldrh r1, [r4]
	subs r0, r0, r1
	strh r0, [r5, #0xe]
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EndingProcessFrontFacingShip
EndingProcessFrontFacingShip: @ 0x080958C8
	push {r4, lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r0, #1
	movs r4, #0
	strh r0, [r3, #0xa]
	ldrb r1, [r3, #0x14]
	cmp r1, #0
	bne _080958EA
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	strh r4, [r3, #0xa]
	movs r0, #4
	strb r0, [r3, #0x13]
	movs r0, #1
	strb r0, [r3, #0x14]
	b _08095944
_080958EA:
	cmp r1, #1
	bne _0809591C
	ldrb r1, [r3, #0x13]
	adds r1, #1
	strb r1, [r3, #0x13]
	ldr r2, _08095918 @ =sSineTable
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x13
	ldrh r2, [r3, #2]
	adds r0, r0, r2
	strh r0, [r3, #0xe]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	cmp r1, #0x40
	bne _08095944
	movs r0, #2
	strb r0, [r3, #0x14]
	strh r4, [r3, #0xa]
	b _08095944
	.align 2, 0
_08095918: .4byte sSineTable
_0809591C:
	cmp r1, #2
	bne _08095944
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _08095930
	strh r4, [r3, #0xa]
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
_08095930:
	ldr r1, _08095950 @ =sSineTable
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x13
	ldrh r1, [r3, #2]
	adds r0, r0, r1
	strh r0, [r3, #0xe]
_08095944:
	ldr r1, _08095954 @ =0x0300122E
	ldrh r0, [r3, #0xe]
	strh r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08095950: .4byte sSineTable
_08095954: .4byte 0x0300122E

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
