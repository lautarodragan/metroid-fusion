    .include "asm/macros.inc"

    .syntax unified

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
