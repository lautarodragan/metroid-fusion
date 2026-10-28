    .include "asm/macros.inc"

    .syntax unified

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
