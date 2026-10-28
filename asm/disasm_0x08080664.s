    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start Sram_CheckLoadSaveFile
Sram_CheckLoadSaveFile: @ 0x08080664
	push {r4, r5, r6, lr}
	ldr r2, _080806BC @ =gButtonAssignments
	ldr r0, _080806C0 @ =sSramUnk_5822c8
	ldr r1, [r0, #4]
	ldr r0, [r0]
	str r0, [r2]
	str r1, [r2, #4]
	ldr r1, _080806C4 @ =gBootDebugOptions
	ldr r0, _080806C8 @ =sSramUnk_5822e4
	ldm r0!, {r2, r3, r4}
	stm r1!, {r2, r3, r4}
	ldr r2, _080806CC @ =gIsLoadingFile
	ldr r6, _080806D0 @ =0x03000B94
	ldr r4, _080806D4 @ =0x03000B8D
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r0, [r0]
	strb r0, [r2]
	lsls r0, r0, #0x18
	asrs r5, r0, #0x18
	cmp r5, #0
	bne _080806DC
	bl Sram_InitSaveFile
	ldr r2, _080806D8 @ =0x03000014
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r0, [r0, #0x10]
	strb r0, [r2]
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r0, [r0, #0x11]
	strb r0, [r2, #1]
	strb r5, [r2, #2]
	b _080806E0
	.align 2, 0
_080806BC: .4byte gButtonAssignments
_080806C0: .4byte sSramUnk_5822c8
_080806C4: .4byte gBootDebugOptions
_080806C8: .4byte sSramUnk_5822e4
_080806CC: .4byte gIsLoadingFile
_080806D0: .4byte 0x03000B94
_080806D4: .4byte 0x03000B8D
_080806D8: .4byte 0x03000014
_080806DC:
	bl SramLoad_CurrentSave
_080806E0:
	ldr r0, _08080718 @ =gUnk_3000be3
	movs r1, #0
	strb r1, [r0]
	ldr r0, _0808071C @ =0x03000018
	strb r1, [r0]
	ldr r0, _08080720 @ =gDisableSoftReset
	strb r1, [r0]
	ldr r0, _08080724 @ =gMaxInGameTimeFlag
	strb r1, [r0]
	ldr r0, _08080728 @ =0x03000022
	strb r1, [r0]
	ldr r0, _0808072C @ =gSkipDoorTransition
	strb r1, [r0]
	ldr r0, _08080730 @ =gPauseScreenFlag
	strb r1, [r0]
	ldr r0, _08080734 @ =0x03000B85
	strb r1, [r0]
	ldr r0, _08080738 @ =0x0300002B
	strb r1, [r0]
	ldr r0, _0808073C @ =gSamusDoorPositionOffset
	movs r1, #0
	strh r1, [r0]
	ldr r0, _08080740 @ =gDebugFlag
	strb r1, [r0]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08080718: .4byte gUnk_3000be3
_0808071C: .4byte 0x03000018
_08080720: .4byte gDisableSoftReset
_08080724: .4byte gMaxInGameTimeFlag
_08080728: .4byte 0x03000022
_0808072C: .4byte gSkipDoorTransition
_08080730: .4byte gPauseScreenFlag
_08080734: .4byte 0x03000B85
_08080738: .4byte 0x0300002B
_0808073C: .4byte gSamusDoorPositionOffset
_08080740: .4byte gDebugFlag

	thumb_func_start Sram_EraseFile
Sram_EraseFile: @ 0x08080744
	push {r4, r5, lr}
	sub sp, #0x18
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	adds r5, r4, #0
	add r0, sp, #4
	movs r1, #0
	movs r2, #0x14
	bl memset
	cmp r4, #0
	bne _08080798
	ldr r1, _08080784 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r2, _08080788 @ =0x03000B94
	ldr r3, _0808078C @ =0x03000B8D
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	add r0, sp, #4
	ldm r0!, {r2, r4, r5}
	stm r1!, {r2, r4, r5}
	ldm r0!, {r2, r4}
	stm r1!, {r2, r4}
	ldr r1, _08080790 @ =0x0000FFFF
	ldr r2, _08080794 @ =sSaveDataEwramPointers
	ldrb r0, [r3]
	b _080807AE
	.align 2, 0
_08080784: .4byte gDisableSoftReset
_08080788: .4byte 0x03000B94
_0808078C: .4byte 0x03000B8D
_08080790: .4byte 0x0000FFFF
_08080794: .4byte sSaveDataEwramPointers
_08080798:
	cmp r4, #1
	bne _080807A2
	bl WriteMostRecentFileToSram
	b _080807DE
_080807A2:
	cmp r4, #2
	bne _080807D0
	ldr r1, _080807C4 @ =0x0000FFFF
	ldr r2, _080807C8 @ =sSaveDataEwramBackupPointers
	ldr r0, _080807CC @ =0x03000B8D
	ldrb r0, [r0]
_080807AE:
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl BitFill
	b _080807DE
	.align 2, 0
_080807C4: .4byte 0x0000FFFF
_080807C8: .4byte sSaveDataEwramBackupPointers
_080807CC: .4byte 0x03000B8D
_080807D0:
	cmp r5, #3
	bne _080807D8
	bl WriteMostRecentFileBackupToSram
_080807D8:
	ldr r1, _080807E8 @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_080807DE:
	add sp, #0x18
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080807E8: .4byte gDisableSoftReset

	thumb_func_start Sram_CopyFile
Sram_CopyFile: @ 0x080807EC
	push {r4, r5, r6, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	adds r2, r6, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r1, #0
	cmp r1, #0
	bne _08080844
	ldr r1, _08080834 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r4, _08080838 @ =0x03000B94
	lsls r3, r6, #2
	adds r1, r3, r6
	lsls r1, r1, #2
	ldr r5, _0808083C @ =0x03000B8D
	ldrb r2, [r5]
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r1, r1, r4
	adds r0, r0, r4
	ldm r0!, {r2, r4, r6}
	stm r1!, {r2, r4, r6}
	ldm r0!, {r2, r4}
	stm r1!, {r2, r4}
	ldr r2, _08080840 @ =sSaveDataEwramPointers
	ldrb r0, [r5]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r0]
	adds r3, r3, r2
	ldr r2, [r3]
	b _08080872
	.align 2, 0
_08080834: .4byte gDisableSoftReset
_08080838: .4byte 0x03000B94
_0808083C: .4byte 0x03000B8D
_08080840: .4byte sSaveDataEwramPointers
_08080844:
	cmp r1, #1
	bne _0808085C
	ldr r4, _08080858 @ =0x03000B8D
	ldrb r5, [r4]
	strb r6, [r4]
	bl WriteMostRecentFileToSram
	strb r5, [r4]
	b _080808A2
	.align 2, 0
_08080858: .4byte 0x03000B8D
_0808085C:
	cmp r1, #2
	bne _0808088C
	ldr r2, _08080884 @ =sSaveDataEwramBackupPointers
	ldr r0, _08080888 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r0]
	lsls r0, r6, #2
	adds r0, r0, r2
	ldr r2, [r0]
_08080872:
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _080808A2
	.align 2, 0
_08080884: .4byte sSaveDataEwramBackupPointers
_08080888: .4byte 0x03000B8D
_0808088C:
	cmp r0, #3
	bne _0808089C
	ldr r4, _080808AC @ =0x03000B8D
	ldrb r5, [r4]
	strb r2, [r4]
	bl WriteMostRecentFileBackupToSram
	strb r5, [r4]
_0808089C:
	ldr r1, _080808B0 @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_080808A2:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080808AC: .4byte 0x03000B8D
_080808B0: .4byte gDisableSoftReset

	thumb_func_start Sram_WriteFileInfo
Sram_WriteFileInfo: @ 0x080808B4
	push {r4, lr}
	movs r4, #0
	movs r3, #0
	ldr r2, _08080948 @ =0x03000B94
_080808BC:
	lsls r1, r4, #2
	ldrb r0, [r2]
	cmp r0, #1
	bne _0808091A
	ldr r0, _0808094C @ =sSaveDataEwramPointers
	adds r0, r1, r0
	ldr r1, [r0]
	ldrb r0, [r1, #0x1d]
	strb r0, [r2, #2]
	adds r0, r1, #0
	adds r0, #0x21
	ldrb r0, [r0]
	strb r0, [r2, #3]
	adds r0, r1, #0
	adds r0, #0xc4
	ldrh r0, [r0]
	strh r0, [r2, #4]
	adds r0, r1, #0
	adds r0, #0xc6
	ldrh r0, [r0]
	strh r0, [r2, #6]
	adds r0, r1, #0
	adds r0, #0xc8
	ldrh r0, [r0]
	strh r0, [r2, #8]
	adds r0, r1, #0
	adds r0, #0xca
	ldrh r0, [r0]
	strh r0, [r2, #0xa]
	adds r0, r1, #0
	adds r0, #0xcf
	ldrb r0, [r0]
	strb r0, [r2, #0xc]
	adds r0, r1, #0
	adds r0, #0xe4
	ldrb r0, [r0]
	strb r0, [r2, #0xd]
	adds r0, r1, #0
	adds r0, #0xe5
	ldrb r0, [r0]
	strb r0, [r2, #0xe]
	ldrb r0, [r1, #0x1c]
	strb r0, [r2, #0xf]
	ldrb r0, [r1, #0x18]
	strb r0, [r2, #0x10]
	ldrb r0, [r1, #0x19]
	strb r0, [r2, #0x11]
_0808091A:
	ldrb r0, [r2]
	cmp r0, #0
	beq _08080926
	ldrb r0, [r2, #0xf]
	cmp r0, #0
	bne _0808093A
_08080926:
	strb r3, [r2]
	strb r3, [r2, #2]
	strb r3, [r2, #3]
	strh r3, [r2, #4]
	strh r3, [r2, #6]
	strh r3, [r2, #8]
	strh r3, [r2, #0xa]
	strb r3, [r2, #0xc]
	strb r3, [r2, #0xd]
	strb r3, [r2, #0xe]
_0808093A:
	adds r2, #0x14
	adds r4, #1
	cmp r4, #2
	ble _080808BC
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080948: .4byte 0x03000B94
_0808094C: .4byte sSaveDataEwramPointers

	thumb_func_start Sram_LoadingfileVblank
Sram_LoadingfileVblank: @ 0x08080950
	sub sp, #4
	mov r1, sp
	movs r0, #0
	strb r0, [r1]
	add sp, #4
	bx lr

	thumb_func_start Sram_AfterLoadingFileVblank
Sram_AfterLoadingFileVblank: @ 0x0808095C
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start Sram_ChecLoadSaveFileWithBlank
Sram_ChecLoadSaveFileWithBlank: @ 0x08080968
	push {lr}
	ldr r0, _08080988 @ =Sram_AfterLoadingFileVblank
	bl CallbackSetVBlank
	bl Sram_CheckLoadSaveFile
	ldr r0, _0808098C @ =Sram_LoadingfileVblank
	bl CallbackSetVBlank
	ldr r0, _08080990 @ =gIsLoadingFile
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	pop {r1}
	bx r1
	.align 2, 0
_08080988: .4byte Sram_AfterLoadingFileVblank
_0808098C: .4byte Sram_LoadingfileVblank
_08080990: .4byte gIsLoadingFile

	thumb_func_start Sram_SetCurrentFile
Sram_SetCurrentFile: @ 0x08080994
	push {r4, lr}
	ldr r1, _080809B8 @ =0x03000B8D
	ldrb r4, [r1]
	strb r0, [r1]
	ldr r2, _080809BC @ =0x03000B94
	ldrb r1, [r1]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldrb r0, [r0, #1]
	cmp r0, #1
	beq _080809C0
	cmp r0, #1
	ble _080809CE
	cmp r0, #2
	beq _080809C6
	b _080809CE
	.align 2, 0
_080809B8: .4byte 0x03000B8D
_080809BC: .4byte 0x03000B94
_080809C0:
	bl WriteMostRecentFileToSram
	b _080809CE
_080809C6:
	bl WriteMostRecentFileToSram
	bl WriteMostRecentFileBackupToSram
_080809CE:
	ldr r3, _080809E8 @ =0x03000B94
	ldr r2, _080809EC @ =0x03000B8D
	ldrb r1, [r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	movs r1, #0
	strb r1, [r0, #1]
	strb r4, [r2]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080809E8: .4byte 0x03000B94
_080809EC: .4byte 0x03000B8D

	thumb_func_start EraseSramMenuHandler
EraseSramMenuHandler: @ 0x080809F0
	push {r4, r5, r6, lr}
	movs r6, #0
	ldr r0, _08080A18 @ =gNonGameplayRam
	ldrh r1, [r0, #4]
	adds r1, #1
	strh r1, [r0, #4]
	ldr r1, _08080A1C @ =gSubGameMode1
	movs r3, #0
	ldrsh r2, [r1, r3]
	adds r3, r0, #0
	adds r5, r1, #0
	cmp r2, #6
	bls _08080A0C
	b _08080AFA
_08080A0C:
	lsls r0, r2, #2
	ldr r1, _08080A20 @ =_08080A24
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08080A18: .4byte gNonGameplayRam
_08080A1C: .4byte gSubGameMode1
_08080A20: .4byte _08080A24
_08080A24: @ jump table
	.4byte _08080A40 @ case 0
	.4byte _08080A50 @ case 1
	.4byte _08080A74 @ case 2
	.4byte _08080AB0 @ case 3
	.4byte _08080ABC @ case 4
	.4byte _08080ACC @ case 5
	.4byte _08080AE2 @ case 6
_08080A40:
	bl EraseSramMenuInit
	ldr r1, _08080A4C @ =gSubGameMode1
	ldrh r0, [r1]
	b _08080AEA
	.align 2, 0
_08080A4C: .4byte gSubGameMode1
_08080A50:
	ldr r4, _08080A60 @ =gWrittenToBldy
	ldrh r1, [r4]
	adds r2, r1, #0
	cmp r2, #0
	beq _08080A64
	subs r0, r1, #1
	strh r0, [r4]
	b _08080AFA
	.align 2, 0
_08080A60: .4byte gWrittenToBldy
_08080A64:
	movs r0, #0xef
	strh r0, [r3, #6]
	strb r1, [r3, #8]
	ldrh r0, [r5]
	adds r0, #1
	strh r0, [r5]
	strh r2, [r3, #4]
	b _08080AFA
_08080A74:
	ldr r4, _08080A98 @ =gSubGameMode2
	bl EraseSramProcessInput
	strb r0, [r4]
	lsls r0, r0, #0x18
	asrs r2, r0, #0x18
	cmp r2, #0
	beq _08080AFA
	ldr r1, _08080A9C @ =gNonGameplayRam
	movs r0, #0
	strh r0, [r1, #4]
	cmp r2, #1
	bne _08080AA4
	ldr r1, _08080AA0 @ =gSubGameMode1
	movs r0, #5
	strh r0, [r1]
	b _08080AFA
	.align 2, 0
_08080A98: .4byte gSubGameMode2
_08080A9C: .4byte gNonGameplayRam
_08080AA0: .4byte gSubGameMode1
_08080AA4:
	ldr r1, _08080AAC @ =gSubGameMode1
	movs r0, #3
	strh r0, [r1]
	b _08080AFA
	.align 2, 0
_08080AAC: .4byte gSubGameMode1
_08080AB0:
	ldrh r0, [r3, #4]
	cmp r0, #0x28
	bls _08080AFA
	movs r1, #0
	movs r0, #0xff
	b _08080AD6
_08080ABC:
	ldr r1, _08080AC8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bls _08080AEA
	b _08080AF8
	.align 2, 0
_08080AC8: .4byte gWrittenToBldy
_08080ACC:
	ldrh r0, [r3, #4]
	cmp r0, #0x28
	bls _08080AFA
	movs r1, #0
	movs r0, #0xbf
_08080AD6:
	strh r0, [r3, #6]
	strh r1, [r3, #4]
	ldrh r0, [r5]
	adds r0, #1
	strh r0, [r5]
	b _08080AFA
_08080AE2:
	ldr r1, _08080AF0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08080AF4
_08080AEA:
	adds r0, #1
	strh r0, [r1]
	b _08080AFA
	.align 2, 0
_08080AF0: .4byte gWrittenToBldy
_08080AF4:
	bl EraseSram
_08080AF8:
	movs r6, #1
_08080AFA:
	bl EraseSramProcessOam
	bl ResetFreeOam
	adds r0, r6, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start EraseSramProcessInput
EraseSramProcessInput: @ 0x08080B0C
	push {r4, lr}
	movs r4, #0
	ldr r0, _08080B24 @ =gNonGameplayRam
	ldrb r1, [r0, #1]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _08080B28
	bl EraseSramApplyInput
	b _08080B2E
	.align 2, 0
_08080B24: .4byte gNonGameplayRam
_08080B28:
	bl EraseSramCheckForInput
	adds r4, r0, #0
_08080B2E:
	ldr r0, _08080B44 @ =gNonGameplayRam
	ldr r3, _08080B48 @ =gWrittenToBldy
	ldrh r1, [r3]
	ldrb r2, [r0, #8]
	adds r0, r1, #0
	cmp r2, r0
	beq _08080B50
	cmp r2, r0
	bls _08080B4C
	adds r0, r1, #1
	b _08080B4E
	.align 2, 0
_08080B44: .4byte gNonGameplayRam
_08080B48: .4byte gWrittenToBldy
_08080B4C:
	subs r0, r1, #1
_08080B4E:
	strh r0, [r3]
_08080B50:
	bl EraseSramUpdateCursorPosition
	adds r0, r4, #0
	pop {r4}
	pop {r1}
	bx r1

	thumb_func_start EraseSramApplyInput
EraseSramApplyInput: @ 0x08080B5C
	push {lr}
	ldr r1, _08080B84 @ =gNonGameplayRam
	ldrb r0, [r1, #0x16]
	adds r2, r1, #0
	cmp r0, #2
	beq _08080BE2
	ldrb r1, [r2, #1]
	movs r0, #0x7f
	ands r0, r1
	movs r3, #0
	strb r0, [r2, #1]
	strb r0, [r2]
	ldrb r0, [r2, #1]
	cmp r0, #1
	beq _08080B9C
	cmp r0, #1
	bgt _08080B88
	cmp r0, #0
	beq _08080B92
	b _08080BC6
	.align 2, 0
_08080B84: .4byte gNonGameplayRam
_08080B88:
	cmp r0, #2
	beq _08080BB4
	cmp r0, #3
	beq _08080BBC
	b _08080BC6
_08080B92:
	ldr r0, _08080B98 @ =sEraseSramUnk_58b3b0
	b _08080B9E
	.align 2, 0
_08080B98: .4byte sEraseSramUnk_58b3b0
_08080B9C:
	ldr r0, _08080BB0 @ =sEraseSramUnk_58b3b0+1
_08080B9E:
	ldrb r0, [r0]
	adds r1, r2, #0
	adds r1, #0x2e
	strb r0, [r1]
	adds r0, r2, #0
	adds r0, #0x22
	strb r3, [r0]
	b _08080BC6
	.align 2, 0
_08080BB0: .4byte sEraseSramUnk_58b3b0+1
_08080BB4:
	ldr r0, _08080BB8 @ =sEraseSramUnk_58b3b0+2
	b _08080BBE
	.align 2, 0
_08080BB8: .4byte sEraseSramUnk_58b3b0+2
_08080BBC:
	ldr r0, _08080BE8 @ =sEraseSramUnk_58b3b0+3
_08080BBE:
	ldrb r0, [r0]
	adds r1, r2, #0
	adds r1, #0x22
	strb r0, [r1]
_08080BC6:
	adds r0, r2, #0
	adds r0, #0x20
	movs r1, #0
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	adds r0, #0xb
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	movs r0, #1
	strb r0, [r2, #0x16]
	strb r1, [r2, #0x14]
	strb r1, [r2, #0x15]
_08080BE2:
	pop {r0}
	bx r0
	.align 2, 0
_08080BE8: .4byte sEraseSramUnk_58b3b0+3

	thumb_func_start EraseSramCheckForInput
EraseSramCheckForInput: @ 0x08080BEC
	push {r4, r5, lr}
	movs r5, #0
	movs r4, #0
	ldr r0, _08080C08 @ =gNonGameplayRam
	ldrb r1, [r0]
	adds r3, r0, #0
	cmp r1, #1
	beq _08080C3A
	cmp r1, #1
	bgt _08080C0C
	cmp r1, #0
	beq _08080C16
	b _08080CCA
	.align 2, 0
_08080C08: .4byte gNonGameplayRam
_08080C0C:
	cmp r1, #2
	beq _08080C62
	cmp r1, #3
	beq _08080C94
	b _08080CCA
_08080C16:
	ldr r0, _08080C28 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08080C2C
	movs r0, #0x81
	b _08080CA2
	.align 2, 0
_08080C28: .4byte gChangedInput
_08080C2C:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08080CCA
	movs r5, #2
	movs r4, #1
	b _08080CD0
_08080C3A:
	ldr r0, _08080C4C @ =gChangedInput
	ldrh r2, [r0]
	movs r0, #0x20
	ands r0, r2
	cmp r0, #0
	beq _08080C50
	movs r0, #0x80
	b _08080CA2
	.align 2, 0
_08080C4C: .4byte gChangedInput
_08080C50:
	ands r1, r2
	cmp r1, #0
	beq _08080CCA
	movs r0, #0x82
	strb r0, [r3, #1]
	movs r4, #1
	movs r0, #4
	strb r0, [r3, #8]
	b _08080CCA
_08080C62:
	ldr r0, _08080C74 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08080C78
	movs r0, #0x83
	b _08080CA2
	.align 2, 0
_08080C74: .4byte gChangedInput
_08080C78:
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	beq _08080CCA
	movs r0, #0x80
	strb r0, [r3, #1]
	strb r5, [r3, #8]
	movs r0, #1
	ands r0, r1
	movs r4, #3
	cmp r0, #0
	beq _08080CCA
	movs r4, #1
	b _08080CCA
_08080C94:
	ldr r0, _08080CA8 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08080CAC
	movs r0, #0x82
_08080CA2:
	strb r0, [r3, #1]
	movs r4, #4
	b _08080CCA
	.align 2, 0
_08080CA8: .4byte gChangedInput
_08080CAC:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08080CBA
	movs r5, #1
	movs r4, #2
	b _08080CD0
_08080CBA:
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08080CCA
	movs r0, #0x80
	strb r0, [r3, #1]
	movs r4, #3
	strb r5, [r3, #8]
_08080CCA:
	movs r0, #0
	cmp r0, #0
	beq _08080CDA
_08080CD0:
	movs r1, #0
	movs r0, #2
	strb r0, [r3, #0x16]
	strb r1, [r3, #0x14]
	strb r1, [r3, #0x15]
_08080CDA:
	ldr r0, _08080CF4 @ =sEraseSramUnk_58b3b4
	lsls r1, r4, #1
	adds r1, r1, r0
	ldrh r0, [r1]
	cmp r0, #0
	beq _08080CEA
	bl SoundPlay
_08080CEA:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08080CF4: .4byte sEraseSramUnk_58b3b4

	thumb_func_start EraseSramMenuInit
EraseSramMenuInit: @ 0x08080CF8
	push {r4, r5, lr}
	sub sp, #4
	ldr r3, _08080E4C @ =0x04000208
	movs r5, #0
	strh r5, [r3]
	ldr r2, _08080E50 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08080E54 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08080E58 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08080E5C @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08080E60 @ =EraseSramLoadingVBlank
	bl CallbackSetVBlank
	ldr r1, _08080E64 @ =0x04000050
	movs r0, #0xbf
	strh r0, [r1]
	ldr r0, _08080E68 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08080E6C @ =0x04000054
	strh r1, [r0]
	movs r0, #0
	str r0, [sp]
	ldr r1, _08080E70 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r4, _08080E74 @ =gNonGameplayRam
	str r4, [r1, #4]
	ldr r0, _08080E78 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	bl ClearGfxRam
	ldr r0, _08080E7C @ =gNextOamSlot
	strb r5, [r0]
	bl ResetFreeOam
	ldr r1, _08080E80 @ =0x03000011
	ldrb r0, [r1]
	strb r0, [r4, #2]
	subs r0, #2
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #4
	bls _08080D66
	movs r0, #2
	strb r0, [r4, #2]
	strb r5, [r1]
_08080D66:
	ldr r1, _08080E84 @ =0x04000006
	ldrh r0, [r1]
	subs r0, #0x15
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	ldr r2, _08080E88 @ =sEraseSramUnk_5823d0
	ldr r3, _08080E8C @ =sEraseSramUnk_5822f0
	ldr r4, _08080E90 @ =sEraseSramUnk_58340c
	cmp r0, #0x8b
	bhi _08080D86
_08080D7A:
	ldrh r0, [r1]
	subs r0, #0x15
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x8b
	bls _08080D7A
_08080D86:
	ldr r0, _08080E70 @ =0x040000D4
	str r2, [r0]
	movs r1, #0xa0
	lsls r1, r1, #0x13
	str r1, [r0, #4]
	ldr r1, _08080E94 @ =0x80000100
	str r1, [r0, #8]
	ldr r1, [r0, #8]
	str r3, [r0]
	ldr r1, _08080E98 @ =0x05000200
	str r1, [r0, #4]
	ldr r1, _08080E9C @ =0x80000070
	str r1, [r0, #8]
	ldr r0, [r0, #8]
	ldr r1, _08080EA0 @ =0x06001000
	adds r0, r4, #0
	bl LZ77UncompVram
	ldr r0, _08080EA4 @ =sEraseSramUnk_582bbc
	ldr r1, _08080EA8 @ =0x06012000
	bl LZ77UncompVram
	ldr r5, _08080EAC @ =sEraseSramUnk_79c228
	ldr r4, _08080E74 @ =gNonGameplayRam
	ldrb r0, [r4, #2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldrb r0, [r4, #2]
	lsls r0, r0, #3
	adds r1, r5, #4
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r1, _08080EB0 @ =0x06011000
	bl LZ77UncompVram
	ldrb r0, [r4, #2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldr r0, [r0]
	ldr r1, _08080EB4 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08080EB8 @ =sEraseSramUnk_58abe4
	ldr r1, _08080EBC @ =0x0600D000
	bl LZ77UncompVram
	ldr r0, _08080EC0 @ =sEraseSramUnk_58adf0
	ldr r1, _08080EC4 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08080EC8 @ =0x04000008
	movs r1, #0
	strh r1, [r0]
	adds r0, #4
	strh r1, [r0]
	ldr r2, _08080ECC @ =0x0400000A
	ldr r3, _08080ED0 @ =0x00001A01
	adds r0, r3, #0
	strh r0, [r2]
	adds r2, #4
	ldr r3, _08080ED4 @ =0x00001E03
	adds r0, r3, #0
	strh r0, [r2]
	ldr r0, _08080ED8 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r0, _08080EDC @ =0x04000052
	strh r1, [r0]
	ldr r0, _08080EE0 @ =gUnk_3000be3
	strb r1, [r0]
	ldr r0, _08080EE4 @ =gBg1XPosition
	strh r1, [r0]
	ldr r0, _08080EE8 @ =gBg1YPosition
	strh r1, [r0]
	ldr r0, _08080EEC @ =0x03001230
	strh r1, [r0]
	ldr r0, _08080EF0 @ =0x03001232
	strh r1, [r0]
	bl EraseSramResetOam
	bl EraseSramProcessOam
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xd0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08080EF4 @ =EraseSramVBlank
	bl CallbackSetVBlank
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08080E4C: .4byte 0x04000208
_08080E50: .4byte 0x04000004
_08080E54: .4byte 0x0000FFEF
_08080E58: .4byte 0x04000200
_08080E5C: .4byte 0x0000FFFD
_08080E60: .4byte EraseSramLoadingVBlank
_08080E64: .4byte 0x04000050
_08080E68: .4byte gWrittenToBldy
_08080E6C: .4byte 0x04000054
_08080E70: .4byte 0x040000D4
_08080E74: .4byte gNonGameplayRam
_08080E78: .4byte 0x85000150
_08080E7C: .4byte gNextOamSlot
_08080E80: .4byte 0x03000011
_08080E84: .4byte 0x04000006
_08080E88: .4byte sEraseSramUnk_5823d0
_08080E8C: .4byte sEraseSramUnk_5822f0
_08080E90: .4byte sEraseSramUnk_58340c
_08080E94: .4byte 0x80000100
_08080E98: .4byte 0x05000200
_08080E9C: .4byte 0x80000070
_08080EA0: .4byte 0x06001000
_08080EA4: .4byte sEraseSramUnk_582bbc
_08080EA8: .4byte 0x06012000
_08080EAC: .4byte sEraseSramUnk_79c228
_08080EB0: .4byte 0x06011000
_08080EB4: .4byte 0x06010000
_08080EB8: .4byte sEraseSramUnk_58abe4
_08080EBC: .4byte 0x0600D000
_08080EC0: .4byte sEraseSramUnk_58adf0
_08080EC4: .4byte 0x0600F000
_08080EC8: .4byte 0x04000008
_08080ECC: .4byte 0x0400000A
_08080ED0: .4byte 0x00001A01
_08080ED4: .4byte 0x00001E03
_08080ED8: .4byte gWrittenToBldalpha_Evb
_08080EDC: .4byte 0x04000052
_08080EE0: .4byte gUnk_3000be3
_08080EE4: .4byte gBg1XPosition
_08080EE8: .4byte gBg1YPosition
_08080EEC: .4byte 0x03001230
_08080EF0: .4byte 0x03001232
_08080EF4: .4byte EraseSramVBlank

	thumb_func_start EraseSramResetOam
EraseSramResetOam: @ 0x08080EF8
	push {lr}
	ldr r3, _08080F48 @ =gNonGameplayRam
	movs r1, #0
	strb r1, [r3]
	movs r0, #0x80
	strb r0, [r3, #1]
	ldr r0, _08080F4C @ =sEraseSramUnk_58b3b0
	ldrb r0, [r0]
	adds r2, r3, #0
	adds r2, #0x2e
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x2c
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	ldr r2, _08080F50 @ =sEraseSramUnk_58b3be
	ldrb r0, [r2, #1]
	strh r0, [r3, #0x24]
	ldrb r0, [r2]
	strh r0, [r3, #0x26]
	movs r0, #1
	strb r0, [r3, #0x16]
	strb r1, [r3, #0x14]
	strb r1, [r3, #0x15]
	adds r0, r3, #0
	adds r0, #0x22
	strb r1, [r0]
	subs r0, #2
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	ldrb r0, [r2, #3]
	strh r0, [r3, #0x18]
	ldrb r0, [r2, #2]
	strh r0, [r3, #0x1a]
	bl EraseSramUpdateCursorPosition
	pop {r0}
	bx r0
	.align 2, 0
_08080F48: .4byte gNonGameplayRam
_08080F4C: .4byte sEraseSramUnk_58b3b0
_08080F50: .4byte sEraseSramUnk_58b3be

	thumb_func_start EraseSramUpdateCursorPosition
EraseSramUpdateCursorPosition: @ 0x08080F54
	push {r4, r5, r6, lr}
	ldr r4, _08080F94 @ =gNonGameplayRam
	ldr r6, _08080F98 @ =sEraseSramUnk_58b3be
	ldrb r2, [r4]
	lsrs r2, r2, #1
	lsls r2, r2, #1
	adds r3, r6, #1
	adds r3, r2, r3
	ldr r5, _08080F9C @ =sEraseSramUnk_58b3c2
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r1, r5, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrb r3, [r3]
	adds r0, r0, r3
	strh r0, [r4, #0xc]
	adds r2, r2, r6
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrb r2, [r2]
	adds r0, r0, r2
	strh r0, [r4, #0xe]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08080F94: .4byte gNonGameplayRam
_08080F98: .4byte sEraseSramUnk_58b3be
_08080F9C: .4byte sEraseSramUnk_58b3c2

	thumb_func_start EraseSramVBlank
EraseSramVBlank: @ 0x08080FA0
	push {lr}
	ldr r1, _08080FF0 @ =0x040000D4
	ldr r0, _08080FF4 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08080FF8 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	subs r1, #0x80
	ldr r0, _08080FFC @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08081000 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08081004 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #6
	ldr r0, _08081008 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _0808100C @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r2, _08081010 @ =gNonGameplayRam
	ldrh r1, [r2, #6]
	cmp r1, #0
	beq _08080FEC
	ldr r0, _08081014 @ =0x04000050
	strh r1, [r0]
	movs r0, #0
	strh r0, [r2, #6]
_08080FEC:
	pop {r0}
	bx r0
	.align 2, 0
_08080FF0: .4byte 0x040000D4
_08080FF4: .4byte gOamData
_08080FF8: .4byte 0x84000100
_08080FFC: .4byte gWrittenToBldy
_08081000: .4byte gBg1XPosition
_08081004: .4byte gBg1YPosition
_08081008: .4byte 0x03001230
_0808100C: .4byte 0x03001232
_08081010: .4byte gNonGameplayRam
_08081014: .4byte 0x04000050

	thumb_func_start EraseSramLoadingVBlank
EraseSramLoadingVBlank: @ 0x08081018
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EraseSramProcessOam
EraseSramProcessOam: @ 0x08081024
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	ldr r1, _0808114C @ =gNextOamSlot
	movs r0, #0
	strb r0, [r1]
	ldr r5, _08081150 @ =gOamData
	movs r0, #0
	str r0, [sp]
	movs r6, #0
	movs r4, #0
_08081040:
	lsls r0, r4, #1
	adds r1, r0, r4
	lsls r1, r1, #2
	ldr r2, _08081154 @ =gNonGameplayRam
	adds r3, r1, r2
	ldrb r1, [r3, #0x16]
	adds r2, r0, #0
	adds r0, r4, #1
	mov r8, r0
	cmp r1, #0
	beq _0808112C
	adds r0, r1, #0
	cmp r0, #0
	beq _08081092
	cmp r0, #0
	blt _08081092
	cmp r0, #6
	bgt _08081092
	ldr r1, _08081158 @ =sEraseSramUnk_79c260
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r7, [r0]
	ldrb r0, [r3, #0x15]
	lsls r0, r0, #3
	adds r0, r0, r7
	ldrb r1, [r3, #0x14]
	ldrb r0, [r0, #4]
	cmp r1, r0
	blo _08081092
	movs r0, #0
	strb r0, [r3, #0x14]
	ldrb r0, [r3, #0x15]
	adds r0, #1
	strb r0, [r3, #0x15]
	ldrb r0, [r3, #0x15]
	lsls r0, r0, #3
	adds r0, r0, r7
	ldrb r0, [r0, #4]
	cmp r0, #0
	bne _08081092
	strb r0, [r3, #0x15]
_08081092:
	adds r2, r2, r4
	lsls r2, r2, #2
	ldr r1, _08081154 @ =gNonGameplayRam
	adds r2, r2, r1
	ldrb r0, [r2, #0x14]
	adds r0, #1
	strb r0, [r2, #0x14]
	ldr r1, _0808115C @ =gBg1YPosition
	ldrh r0, [r2, #0xc]
	ldrh r1, [r1]
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov sb, r0
	ldr r1, _08081160 @ =gBg1XPosition
	ldrh r0, [r2, #0xe]
	ldrh r1, [r1]
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldrb r0, [r2, #0x15]
	lsls r0, r0, #3
	adds r7, r7, r0
	ldr r3, [r7]
	ldrh r0, [r3]
	ldr r2, [sp]
	adds r2, r2, r0
	str r2, [sp]
	adds r3, #2
	adds r4, #1
	mov r8, r4
	cmp r6, r2
	bge _0808112C
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	mov ip, r0
	lsls r0, r6, #3
	ldr r1, _08081150 @ =gOamData
	adds r4, r0, r1
	ldr r2, _08081164 @ =0x000001FF
	mov sl, r2
	ldr r0, [sp]
	subs r6, r0, r6
_080810E8:
	ldrh r0, [r3]
	adds r3, #2
	strh r0, [r5]
	adds r5, #2
	add r0, sb
	strb r0, [r4]
	ldrh r1, [r3]
	adds r3, #2
	strh r1, [r5]
	adds r5, #2
	add r1, ip
	mov r2, sl
	ands r1, r2
	ldrh r2, [r4, #2]
	ldr r0, _08081168 @ =0xFFFFFE00
	ands r0, r2
	orrs r0, r1
	strh r0, [r4, #2]
	ldrh r0, [r3]
	strh r0, [r5]
	adds r3, #2
	ldrb r1, [r4, #5]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r4, #5]
	adds r5, #4
	adds r4, #8
	subs r6, #1
	cmp r6, #0
	bne _080810E8
	ldr r6, [sp]
_0808112C:
	mov r4, r8
	cmp r4, #2
	ble _08081040
	mov r0, sp
	ldrb r1, [r0]
	ldr r0, _0808114C @ =gNextOamSlot
	strb r1, [r0]
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808114C: .4byte gNextOamSlot
_08081150: .4byte gOamData
_08081154: .4byte gNonGameplayRam
_08081158: .4byte sEraseSramUnk_79c260
_0808115C: .4byte gBg1YPosition
_08081160: .4byte gBg1XPosition
_08081164: .4byte 0x000001FF
_08081168: .4byte 0xFFFFFE00
