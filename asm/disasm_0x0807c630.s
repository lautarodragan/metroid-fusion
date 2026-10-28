    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start unk_7c630
unk_7c630: @ 0x0807C630
	push {r4, lr}
	sub sp, #4
	ldr r1, _0807C650 @ =gNonGameplayRam
	ldr r2, _0807C654 @ =0x00000265
	adds r0, r1, r2
	ldrb r0, [r0]
	adds r4, r1, #0
	cmp r0, #0x25
	bls _0807C646
	bl _0807CE56
_0807C646:
	lsls r0, r0, #2
	ldr r1, _0807C658 @ =_0807C65C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807C650: .4byte gNonGameplayRam
_0807C654: .4byte 0x00000265
_0807C658: .4byte _0807C65C
_0807C65C: @ jump table
	.4byte _0807C6F4 @ case 0
	.4byte _0807C770 @ case 1
	.4byte _0807C79C @ case 2
	.4byte _0807C7B8 @ case 3
	.4byte _0807C7E4 @ case 4
	.4byte _0807C810 @ case 5
	.4byte _0807C82C @ case 6
	.4byte _0807C858 @ case 7
	.4byte _0807C884 @ case 8
	.4byte _0807C8A0 @ case 9
	.4byte _0807C8CC @ case 10
	.4byte _0807C924 @ case 11
	.4byte _0807C940 @ case 12
	.4byte _0807C970 @ case 13
	.4byte _0807C99C @ case 14
	.4byte _0807C9C8 @ case 15
	.4byte _0807C9F0 @ case 16
	.4byte _0807CA10 @ case 17
	.4byte _0807CA50 @ case 18
	.4byte _0807CA90 @ case 19
	.4byte _0807CAD0 @ case 20
	.4byte _0807CAFC @ case 21
	.4byte _0807CB20 @ case 22
	.4byte _0807CB58 @ case 23
	.4byte _0807CBB0 @ case 24
	.4byte _0807CBE0 @ case 25
	.4byte _0807CC18 @ case 26
	.4byte _0807CC4C @ case 27
	.4byte _0807CC70 @ case 28
	.4byte _0807CC9C @ case 29
	.4byte _0807CCC8 @ case 30
	.4byte _0807CCE4 @ case 31
	.4byte _0807CD30 @ case 32
	.4byte _0807CD5C @ case 33
	.4byte _0807CD78 @ case 34
	.4byte _0807CDA4 @ case 35
	.4byte _0807CDD0 @ case 36
	.4byte _0807CE10 @ case 37
_0807C6F4:
	movs r0, #0x80
	lsls r0, r0, #0x13
	ldrh r1, [r0]
	ldr r3, _0807C74C @ =0x0000026A
	adds r0, r4, r3
	movs r2, #0
	strh r1, [r0]
	ldr r0, _0807C750 @ =0x0400000E
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C754 @ =0x0400000C
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C758 @ =0x04000050
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C75C @ =0x04000052
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	movs r1, #0x9a
	lsls r1, r1, #2
	adds r0, r4, r1
	strh r2, [r0]
	ldr r1, _0807C760 @ =0x040000D4
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1]
	ldr r0, _0807C764 @ =0x02035000
	str r0, [r1, #4]
	ldr r0, _0807C768 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _0807C76C @ =0x00000265
	adds r1, r4, r2
	b _0807CDEE
	.align 2, 0
_0807C74C: .4byte 0x0000026A
_0807C750: .4byte 0x0400000E
_0807C754: .4byte 0x0400000C
_0807C758: .4byte 0x04000050
_0807C75C: .4byte 0x04000052
_0807C760: .4byte 0x040000D4
_0807C764: .4byte 0x02035000
_0807C768: .4byte 0x80000100
_0807C76C: .4byte 0x00000265
_0807C770:
	ldr r1, _0807C78C @ =0x06004000
	ldr r2, _0807C790 @ =0x02008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C794 @ =gNonGameplayRam
	ldr r3, _0807C798 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C78C: .4byte 0x06004000
_0807C790: .4byte 0x02008000
_0807C794: .4byte gNonGameplayRam
_0807C798: .4byte 0x00000265
_0807C79C:
	ldr r1, _0807C7B0 @ =0x06005000
	ldr r2, _0807C7B4 @ =0x02009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C7B0: .4byte 0x06005000
_0807C7B4: .4byte 0x02009000
_0807C7B8:
	ldr r1, _0807C7D4 @ =0x06006000
	ldr r2, _0807C7D8 @ =0x0200A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C7DC @ =gNonGameplayRam
	ldr r2, _0807C7E0 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C7D4: .4byte 0x06006000
_0807C7D8: .4byte 0x0200A000
_0807C7DC: .4byte gNonGameplayRam
_0807C7E0: .4byte 0x00000265
_0807C7E4:
	ldr r1, _0807C800 @ =0x06007000
	ldr r2, _0807C804 @ =0x0200B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C808 @ =gNonGameplayRam
	ldr r3, _0807C80C @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C800: .4byte 0x06007000
_0807C804: .4byte 0x0200B000
_0807C808: .4byte gNonGameplayRam
_0807C80C: .4byte 0x00000265
_0807C810:
	movs r1, #0x80
	lsls r1, r1, #0x12
	ldr r2, _0807C828 @ =0x06004000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C828: .4byte 0x06004000
_0807C82C:
	ldr r1, _0807C848 @ =0x02001000
	ldr r2, _0807C84C @ =0x06005000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C850 @ =gNonGameplayRam
	ldr r2, _0807C854 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C848: .4byte 0x02001000
_0807C84C: .4byte 0x06005000
_0807C850: .4byte gNonGameplayRam
_0807C854: .4byte 0x00000265
_0807C858:
	ldr r1, _0807C874 @ =0x02002000
	ldr r2, _0807C878 @ =0x06006000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C87C @ =gNonGameplayRam
	ldr r3, _0807C880 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C874: .4byte 0x02002000
_0807C878: .4byte 0x06006000
_0807C87C: .4byte gNonGameplayRam
_0807C880: .4byte 0x00000265
_0807C884:
	ldr r1, _0807C898 @ =0x02003000
	ldr r2, _0807C89C @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C898: .4byte 0x02003000
_0807C89C: .4byte 0x06007000
_0807C8A0:
	ldr r1, _0807C8BC @ =0x02004000
	ldr r2, _0807C8C0 @ =0x06008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C8C4 @ =gNonGameplayRam
	ldr r2, _0807C8C8 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C8BC: .4byte 0x02004000
_0807C8C0: .4byte 0x06008000
_0807C8C4: .4byte gNonGameplayRam
_0807C8C8: .4byte 0x00000265
_0807C8CC:
	ldr r1, _0807C8F8 @ =0x02005000
	ldr r2, _0807C8FC @ =0x06009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r2, _0807C900 @ =gNonGameplayRam
	movs r3, #0x88
	lsls r3, r3, #2
	adds r0, r2, r3
	ldrb r0, [r0]
	cmp r0, #0x35
	bne _0807C908
	ldr r0, _0807C904 @ =0x00000265
	adds r1, r2, r0
	movs r0, #0xd
	strb r0, [r1]
	b _0807CE56
	.align 2, 0
_0807C8F8: .4byte 0x02005000
_0807C8FC: .4byte 0x06009000
_0807C900: .4byte gNonGameplayRam
_0807C904: .4byte 0x00000265
_0807C908:
	ldr r1, _0807C918 @ =gWrittenToBldalpha_Evb
	movs r0, #0
	strh r0, [r1]
	ldr r0, _0807C91C @ =gWrittenToBldalpha_Eva
	strh r4, [r0]
	ldr r3, _0807C920 @ =0x00000265
	adds r1, r2, r3
	b _0807CDEE
	.align 2, 0
_0807C918: .4byte gWrittenToBldalpha_Evb
_0807C91C: .4byte gWrittenToBldalpha_Eva
_0807C920: .4byte 0x00000265
_0807C924:
	ldr r1, _0807C938 @ =0x02006000
	ldr r2, _0807C93C @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C938: .4byte 0x02006000
_0807C93C: .4byte 0x0600A000
_0807C940:
	ldr r1, _0807C960 @ =0x02007000
	ldr r2, _0807C964 @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r0, _0807C968 @ =gNonGameplayRam
	ldr r1, _0807C96C @ =0x00000265
	adds r0, r0, r1
	movs r1, #0x15
	strb r1, [r0]
	b _0807CE56
	.align 2, 0
_0807C960: .4byte 0x02007000
_0807C964: .4byte 0x0600B000
_0807C968: .4byte gNonGameplayRam
_0807C96C: .4byte 0x00000265
_0807C970:
	ldr r1, _0807C98C @ =0x02006000
	ldr r2, _0807C990 @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C994 @ =gNonGameplayRam
	ldr r2, _0807C998 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C98C: .4byte 0x02006000
_0807C990: .4byte 0x0600A000
_0807C994: .4byte gNonGameplayRam
_0807C998: .4byte 0x00000265
_0807C99C:
	ldr r1, _0807C9B8 @ =0x02007000
	ldr r2, _0807C9BC @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C9C0 @ =gNonGameplayRam
	ldr r3, _0807C9C4 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C9B8: .4byte 0x02007000
_0807C9BC: .4byte 0x0600B000
_0807C9C0: .4byte gNonGameplayRam
_0807C9C4: .4byte 0x00000265
_0807C9C8:
	ldr r1, _0807C9E0 @ =0x040000D4
	ldr r0, _0807C9E4 @ =sUnk_57bec4
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807C9E8 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807C9EC @ =PauseScreenVBlank_Unused
	b _0807CDE4
	.align 2, 0
_0807C9E0: .4byte 0x040000D4
_0807C9E4: .4byte sUnk_57bec4
_0807C9E8: .4byte 0x80000100
_0807C9EC: .4byte PauseScreenVBlank_Unused
_0807C9F0:
	ldr r1, _0807CA08 @ =0x0300000A
	ldr r2, _0807CA0C @ =0x00001407
	adds r0, r2, #0
	strh r0, [r1]
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r4, r3
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #4
	b _0807CB7C
	.align 2, 0
_0807CA08: .4byte 0x0300000A
_0807CA0C: .4byte 0x00001407
_0807CA10:
	ldr r3, _0807CA3C @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CA40 @ =sUnk_79c17c
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	bhi _0807CA28
	b _0807CE56
_0807CA28:
	ldr r1, _0807CA44 @ =0x0300000A
	ldr r3, _0807CA48 @ =0x00001507
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CA4C @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CA3C: .4byte 0x00000266
_0807CA40: .4byte sUnk_79c17c
_0807CA44: .4byte 0x0300000A
_0807CA48: .4byte 0x00001507
_0807CA4C: .4byte 0x00000265
_0807CA50:
	ldr r1, _0807CA7C @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CA80 @ =sUnk_79c17c
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #1]
	cmp r0, r1
	bhi _0807CA68
	b _0807CE56
_0807CA68:
	ldr r1, _0807CA84 @ =0x0300000A
	ldr r3, _0807CA88 @ =0x00001607
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CA8C @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CA7C: .4byte 0x00000266
_0807CA80: .4byte sUnk_79c17c
_0807CA84: .4byte 0x0300000A
_0807CA88: .4byte 0x00001607
_0807CA8C: .4byte 0x00000265
_0807CA90:
	ldr r1, _0807CABC @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CAC0 @ =sUnk_79c17c
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #2]
	cmp r0, r1
	bhi _0807CAA8
	b _0807CE56
_0807CAA8:
	ldr r1, _0807CAC4 @ =0x0300000A
	ldr r3, _0807CAC8 @ =0x00001707
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CACC @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CABC: .4byte 0x00000266
_0807CAC0: .4byte sUnk_79c17c
_0807CAC4: .4byte 0x0300000A
_0807CAC8: .4byte 0x00001707
_0807CACC: .4byte 0x00000265
_0807CAD0:
	ldr r1, _0807CAF0 @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CAF4 @ =sUnk_79c17c
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #3]
	cmp r0, r1
	bhi _0807CAE8
	b _0807CE56
_0807CAE8:
	ldr r3, _0807CAF8 @ =0x00000265
	adds r0, r4, r3
	b _0807CC34
	.align 2, 0
_0807CAF0: .4byte 0x00000266
_0807CAF4: .4byte sUnk_79c17c
_0807CAF8: .4byte 0x00000265
_0807CAFC:
	ldr r0, _0807CB10 @ =sSaXCloseUpTileTable1
	ldr r1, _0807CB14 @ =0x06007800
	bl LZ77UncompVram
	ldr r0, _0807CB18 @ =sSaXCloseUpTileTable2
	ldr r1, _0807CB1C @ =0x0600B800
	bl LZ77UncompVram
	b _0807CDE8
	.align 2, 0
_0807CB10: .4byte sSaXCloseUpTileTable1
_0807CB14: .4byte 0x06007800
_0807CB18: .4byte sSaXCloseUpTileTable2
_0807CB1C: .4byte 0x0600B800
_0807CB20:
	ldr r1, _0807CB40 @ =0x040000D4
	ldr r0, _0807CB44 @ =sSaXCloseUpPalGrayscale
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807CB48 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807CB4C @ =PauseScreenVBlank_Unused
	bl CallbackSetVBlank
	ldr r1, _0807CB50 @ =gNonGameplayRam
	ldr r2, _0807CB54 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CB40: .4byte 0x040000D4
_0807CB44: .4byte sSaXCloseUpPalGrayscale
_0807CB48: .4byte 0x80000100
_0807CB4C: .4byte PauseScreenVBlank_Unused
_0807CB50: .4byte gNonGameplayRam
_0807CB54: .4byte 0x00000265
_0807CB58:
	ldr r1, _0807CB98 @ =0x0400000C
	ldr r3, _0807CB9C @ =0x00000F06
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0807CBA0 @ =0x00001707
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	ldr r3, _0807CBA4 @ =0x00000844
	adds r0, r3, #0
	strh r0, [r1]
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrh r1, [r2]
	movs r3, #0xc0
	lsls r3, r3, #4
_0807CB7C:
	adds r0, r3, #0
	movs r3, #0
	orrs r0, r1
	strh r0, [r2]
	ldr r0, _0807CBA8 @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807CBAC @ =0x00000266
	adds r0, r4, r1
	strb r3, [r0]
	b _0807CE56
	.align 2, 0
_0807CB98: .4byte 0x0400000C
_0807CB9C: .4byte 0x00000F06
_0807CBA0: .4byte 0x00001707
_0807CBA4: .4byte 0x00000844
_0807CBA8: .4byte 0x00000265
_0807CBAC: .4byte 0x00000266
_0807CBB0:
	ldr r3, _0807CBD4 @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CBD8 @ =sSaXCloseUpDurations
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	bhi _0807CBC8
	b _0807CE56
_0807CBC8:
	ldr r1, _0807CBDC @ =0x00000265
	adds r0, r4, r1
	ldrb r1, [r0]
	adds r1, #1
	b _0807CC36
	.align 2, 0
_0807CBD4: .4byte 0x00000266
_0807CBD8: .4byte sSaXCloseUpDurations
_0807CBDC: .4byte 0x00000265
_0807CBE0:
	ldr r1, _0807CBF8 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	adds r2, r0, #0
	cmp r2, #0
	bne _0807CC04
	ldr r3, _0807CBFC @ =0x00000265
	adds r0, r4, r3
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldr r1, _0807CC00 @ =0x00000266
	b _0807CE52
	.align 2, 0
_0807CBF8: .4byte gWrittenToBldalpha_Eva
_0807CBFC: .4byte 0x00000265
_0807CC00: .4byte 0x00000266
_0807CC04:
	subs r0, #1
	strh r0, [r1]
	ldr r2, _0807CC14 @ =gWrittenToBldalpha_Evb
	movs r1, #0x10
	subs r1, r1, r0
	strh r1, [r2]
	b _0807CE56
	.align 2, 0
_0807CC14: .4byte gWrittenToBldalpha_Evb
_0807CC18:
	ldr r3, _0807CC40 @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CC44 @ =sSaXCloseUpDurations
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #1]
	cmp r0, r1
	bhi _0807CC30
	b _0807CE56
_0807CC30:
	ldr r1, _0807CC48 @ =0x00000265
	adds r0, r4, r1
_0807CC34:
	movs r1, #0x1b
_0807CC36:
	strb r1, [r0]
_0807CC38:
	movs r0, #0
	strb r0, [r2]
	b _0807CE56
	.align 2, 0
_0807CC40: .4byte 0x00000266
_0807CC44: .4byte sSaXCloseUpDurations
_0807CC48: .4byte 0x00000265
_0807CC4C:
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r2, #0
	movs r0, #0
	strh r0, [r1]
	ldr r3, _0807CC68 @ =0x00000265
	adds r1, r4, r3
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807CC6C @ =0x00000266
	b _0807CE52
	.align 2, 0
_0807CC68: .4byte 0x00000265
_0807CC6C: .4byte 0x00000266
_0807CC70:
	ldr r1, _0807CC8C @ =sMinimapTilesGfx
	ldr r2, _0807CC90 @ =0x06008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CC94 @ =gNonGameplayRam
	ldr r2, _0807CC98 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CC8C: .4byte sMinimapTilesGfx
_0807CC90: .4byte 0x06008000
_0807CC94: .4byte gNonGameplayRam
_0807CC98: .4byte 0x00000265
_0807CC9C:
	ldr r1, _0807CCB8 @ =sMinimapTilesGfx+0x1000
	ldr r2, _0807CCBC @ =0x06009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CCC0 @ =gNonGameplayRam
	ldr r3, _0807CCC4 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CCB8: .4byte sMinimapTilesGfx+0x1000
_0807CCBC: .4byte 0x06009000
_0807CCC0: .4byte gNonGameplayRam
_0807CCC4: .4byte 0x00000265
_0807CCC8:
	ldr r1, _0807CCDC @ =sMinimapTilesGfx+0x2000
	ldr r2, _0807CCE0 @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807CCDC: .4byte sMinimapTilesGfx+0x2000
_0807CCE0: .4byte 0x0600A000
_0807CCE4:
	ldr r1, _0807CD10 @ =sMinimapTilesGfx+0x3000
	ldr r2, _0807CD14 @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #4
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD18 @ =0x040000D4
	ldr r0, _0807CD1C @ =0x06009800
	str r0, [r1]
	ldr r0, _0807CD20 @ =0x06009400
	str r0, [r1, #4]
	ldr r0, _0807CD24 @ =0x80000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r1, _0807CD28 @ =gNonGameplayRam
	ldr r2, _0807CD2C @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CD10: .4byte sMinimapTilesGfx+0x3000
_0807CD14: .4byte 0x0600B000
_0807CD18: .4byte 0x040000D4
_0807CD1C: .4byte 0x06009800
_0807CD20: .4byte 0x06009400
_0807CD24: .4byte 0x80000200
_0807CD28: .4byte gNonGameplayRam
_0807CD2C: .4byte 0x00000265
_0807CD30:
	ldr r1, _0807CD4C @ =0x02008000
	ldr r2, _0807CD50 @ =0x06004000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD54 @ =gNonGameplayRam
	ldr r3, _0807CD58 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CD4C: .4byte 0x02008000
_0807CD50: .4byte 0x06004000
_0807CD54: .4byte gNonGameplayRam
_0807CD58: .4byte 0x00000265
_0807CD5C:
	ldr r1, _0807CD70 @ =0x02009000
	ldr r2, _0807CD74 @ =0x06005000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807CD70: .4byte 0x02009000
_0807CD74: .4byte 0x06005000
_0807CD78:
	ldr r1, _0807CD94 @ =0x0200A000
	ldr r2, _0807CD98 @ =0x06006000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD9C @ =gNonGameplayRam
	ldr r2, _0807CDA0 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CD94: .4byte 0x0200A000
_0807CD98: .4byte 0x06006000
_0807CD9C: .4byte gNonGameplayRam
_0807CDA0: .4byte 0x00000265
_0807CDA4:
	ldr r1, _0807CDC0 @ =0x0200B000
	ldr r2, _0807CDC4 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CDC8 @ =gNonGameplayRam
	ldr r3, _0807CDCC @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CDC0: .4byte 0x0200B000
_0807CDC4: .4byte 0x06007000
_0807CDC8: .4byte gNonGameplayRam
_0807CDCC: .4byte 0x00000265
_0807CDD0:
	ldr r1, _0807CDF8 @ =0x040000D4
	ldr r0, _0807CDFC @ =0x02035000
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807CE00 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807CE04 @ =PauseScreenVBlank
_0807CDE4:
	bl CallbackSetVBlank
_0807CDE8:
	ldr r1, _0807CE08 @ =gNonGameplayRam
	ldr r0, _0807CE0C @ =0x00000265
	adds r1, r1, r0
_0807CDEE:
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CE56
	.align 2, 0
_0807CDF8: .4byte 0x040000D4
_0807CDFC: .4byte 0x02035000
_0807CE00: .4byte 0x80000100
_0807CE04: .4byte PauseScreenVBlank
_0807CE08: .4byte gNonGameplayRam
_0807CE0C: .4byte 0x00000265
_0807CE10:
	ldr r1, _0807CE60 @ =0x0400000E
	movs r2, #0x9b
	lsls r2, r2, #2
	adds r0, r4, r2
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #2
	ldr r3, _0807CE64 @ =0x0000026E
	adds r0, r4, r3
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #0x44
	adds r2, #4
	adds r0, r4, r2
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	adds r3, #4
	adds r0, r4, r3
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807CE68 @ =0x0000026A
	adds r0, r4, r1
	ldrh r1, [r0]
	subs r2, #8
	adds r0, r4, r2
	movs r2, #0
	strh r1, [r0]
	subs r3, #0xd
	adds r0, r4, r3
	strb r2, [r0]
	movs r1, #0x99
	lsls r1, r1, #2
_0807CE52:
	adds r0, r4, r1
	strb r2, [r0]
_0807CE56:
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807CE60: .4byte 0x0400000E
_0807CE64: .4byte 0x0000026E
_0807CE68: .4byte 0x0000026A
