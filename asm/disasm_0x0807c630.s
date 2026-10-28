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

	thumb_func_start unk_7ce6c
unk_7ce6c: @ 0x0807CE6C
	push {r4, r5, r6, lr}
	sub sp, #4
	ldr r3, _0807CEBC @ =gCurrentArea
	ldrb r0, [r3]
	cmp r0, #6
	bls _0807CE7A
	b _0807CF8A
_0807CE7A:
	ldr r2, _0807CEC0 @ =gNonGameplayRam
	movs r0, #0x90
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _0807CEC4 @ =sUnk_581500
	ldm r0!, {r4, r5, r6}
	stm r1!, {r4, r5, r6}
	ldr r0, [r0]
	str r0, [r1]
	ldrb r0, [r2]
	adds r6, r2, #0
	cmp r0, #0
	beq _0807CF8A
	ldr r0, _0807CEC8 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _0807CF8A
	ldrb r0, [r3]
	cmp r0, #0
	beq _0807CED4
	ldr r2, _0807CECC @ =sEvent_57607D
	ldr r1, _0807CED0 @ =sEvent_576073
	adds r0, r0, r1
	ldrb r0, [r0]
	adds r0, r0, r2
	ldrb r1, [r0]
	movs r2, #0x91
	lsls r2, r2, #2
	adds r0, r6, r2
	b _0807CEDE
	.align 2, 0
_0807CEBC: .4byte gCurrentArea
_0807CEC0: .4byte gNonGameplayRam
_0807CEC4: .4byte sUnk_581500
_0807CEC8: .4byte gPauseScreenFlag
_0807CECC: .4byte sEvent_57607D
_0807CED0: .4byte sEvent_576073
_0807CED4:
	ldr r0, _0807CF48 @ =sEvent_57607D
	ldrb r1, [r0, #7]
	movs r4, #0x91
	lsls r4, r4, #2
	adds r0, r6, r4
_0807CEDE:
	strb r1, [r0]
	ldr r1, _0807CF4C @ =sUnk_79c180
	movs r5, #0x91
	lsls r5, r5, #2
	adds r0, r6, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r0, r0, r1
	ldrb r0, [r0]
	adds r1, r6, #0
	adds r1, #0xc6
	strb r0, [r1]
	subs r1, #8
	movs r0, #0x1c
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x32
	strh r0, [r1]
	adds r2, r6, #0
	adds r2, #0xc7
	ldrb r1, [r2]
	movs r4, #4
	rsbs r4, r4, #0
	adds r0, r4, #0
	ands r0, r1
	movs r5, #1
	orrs r0, r5
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0xa
	movs r1, #0
	bl UpdateMenuOamDataId
	adds r1, r6, #0
	adds r1, #0xaf
	ldrb r0, [r1]
	ands r4, r0
	orrs r4, r5
	strb r4, [r1]
	ldr r2, _0807CF50 @ =gCurrentArea
	ldrb r0, [r2]
	cmp r0, #0
	beq _0807CF5C
	ldr r1, _0807CF54 @ =sEvent_576073
	adds r0, r0, r1
	ldrb r1, [r0]
	ldr r2, _0807CF58 @ =0x00000249
	adds r0, r6, r2
	b _0807CF6C
	.align 2, 0
_0807CF48: .4byte sEvent_57607D
_0807CF4C: .4byte sUnk_79c180
_0807CF50: .4byte gCurrentArea
_0807CF54: .4byte sEvent_576073
_0807CF58: .4byte 0x00000249
_0807CF5C:
	ldr r1, _0807CF94 @ =sUnk_5760e8
	ldr r0, _0807CF98 @ =gCurrentRoom
	ldrb r0, [r0]
	adds r0, #1
	adds r0, r0, r1
	ldrb r1, [r0]
	ldr r4, _0807CF9C @ =0x00000249
	adds r0, r6, r4
_0807CF6C:
	strb r1, [r0]
	bl unk_7d27c
	mov r1, sp
	ldr r5, _0807CFA0 @ =0x00007A73
	adds r0, r5, #0
	strh r0, [r1]
	ldr r1, _0807CFA4 @ =0x040000D4
	mov r6, sp
	str r6, [r1]
	ldr r0, _0807CFA8 @ =0x05000342
	str r0, [r1, #4]
	ldr r0, _0807CFAC @ =0x8100000C
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_0807CF8A:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807CF94: .4byte sUnk_5760e8
_0807CF98: .4byte gCurrentRoom
_0807CF9C: .4byte 0x00000249
_0807CFA0: .4byte 0x00007A73
_0807CFA4: .4byte 0x040000D4
_0807CFA8: .4byte 0x05000342
_0807CFAC: .4byte 0x8100000C

	thumb_func_start unk_7cfb0
unk_7cfb0: @ 0x0807CFB0
	push {r4, lr}
	ldr r1, _0807D034 @ =gNonGameplayRam
	ldrb r0, [r1]
	mov ip, r1
	cmp r0, #0
	bne _0807CFBE
	b _0807D270
_0807CFBE:
	ldr r0, _0807D038 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _0807CFCC
	b _0807D270
_0807CFCC:
	movs r1, #0x92
	lsls r1, r1, #2
	add r1, ip
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0807D014
	strb r2, [r1]
	ldr r3, _0807D03C @ =0x00000247
	add r3, ip
	ldrb r0, [r3]
	adds r0, #1
	strb r0, [r3]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #5
	bls _0807CFF8
	strb r2, [r3]
_0807CFF8:
	ldr r0, _0807D040 @ =0x00000249
	add r0, ip
	ldrb r4, [r0]
	lsls r1, r4, #1
	ldr r0, _0807D044 @ =0x05000340
	adds r1, r1, r0
	ldr r2, _0807D048 @ =sUnk_581300
	ldrb r0, [r3]
	lsls r0, r0, #4
	adds r0, r0, r4
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
_0807D014:
	ldr r1, _0807D04C @ =0x0000024A
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #2
	bne _0807D050
	movs r0, #3
	strb r0, [r1]
	mov r1, ip
	adds r1, #0xa6
	movs r0, #0x1c
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x32
	strh r0, [r1]
	b _0807D0DA
	.align 2, 0
_0807D034: .4byte gNonGameplayRam
_0807D038: .4byte gPauseScreenFlag
_0807D03C: .4byte 0x00000247
_0807D040: .4byte 0x00000249
_0807D044: .4byte 0x05000340
_0807D048: .4byte sUnk_581300
_0807D04C: .4byte 0x0000024A
_0807D050:
	cmp r0, #3
	bne _0807D0DA
	ldr r0, _0807D090 @ =sEvent_57608A
	ldr r1, _0807D094 @ =0x0300004C
	ldrb r1, [r1]
	adds r0, r1, r0
	movs r4, #0
	ldrsb r4, [r0, r4]
	cmp r4, #0
	blt _0807D09C
	movs r0, #0x91
	lsls r0, r0, #2
	add r0, ip
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r4, r4, r0
	cmp r4, #0x23
	ble _0807D078
	subs r4, #0x24
_0807D078:
	mov r1, ip
	adds r1, #0xbe
	ldr r3, _0807D098 @ =sUnk_79c1a4
	lsls r2, r4, #1
	adds r2, r2, r4
	adds r0, r2, r3
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r1, [r1]
	adds r0, r0, r1
	b _0807D0B2
	.align 2, 0
_0807D090: .4byte sEvent_57608A
_0807D094: .4byte 0x0300004C
_0807D098: .4byte sUnk_79c1a4
_0807D09C:
	mov r4, ip
	adds r4, #0xbe
	ldr r3, _0807D108 @ =sUnk_79c210
	lsls r2, r1, #1
	adds r2, r2, r1
	adds r0, r2, r3
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r4, [r4]
	adds r0, r0, r4
_0807D0B2:
	mov r1, ip
	adds r1, #0xa6
	strh r0, [r1]
	adds r1, #0x16
	adds r0, r3, #1
	adds r0, r2, r0
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r1, [r1]
	adds r0, r0, r1
	mov r1, ip
	adds r1, #0xa4
	strh r0, [r1]
	adds r3, #2
	adds r2, r2, r3
	ldrb r0, [r2]
	adds r0, #0x16
	adds r1, #0xa
	strb r0, [r1]
_0807D0DA:
	movs r2, #0x90
	lsls r2, r2, #2
	add r2, ip
	ldrb r0, [r2]
	cmp r0, #0
	bne _0807D0E8
	b _0807D270
_0807D0E8:
	ldr r0, _0807D10C @ =0x00000242
	add r0, ip
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldrb r0, [r2]
	subs r0, #1
	cmp r0, #5
	bls _0807D0FC
	b _0807D270
_0807D0FC:
	lsls r0, r0, #2
	ldr r1, _0807D110 @ =_0807D114
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807D108: .4byte sUnk_79c210
_0807D10C: .4byte 0x00000242
_0807D110: .4byte _0807D114
_0807D114: @ jump table
	.4byte _0807D12C @ case 0
	.4byte _0807D142 @ case 1
	.4byte _0807D164 @ case 2
	.4byte _0807D19C @ case 3
	.4byte _0807D1C4 @ case 4
	.4byte _0807D1EC @ case 5
_0807D12C:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	bne _0807D13C
	b _0807D270
_0807D13C:
	movs r1, #0x90
	lsls r1, r1, #2
	b _0807D1DE
_0807D142:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	beq _0807D152
	b _0807D270
_0807D152:
	ldr r1, _0807D160 @ =0x0000024A
	add r1, ip
	movs r0, #2
	strb r0, [r1]
	movs r1, #0x90
	lsls r1, r1, #2
	b _0807D1B6
	.align 2, 0
_0807D160: .4byte 0x0000024A
_0807D164:
	ldr r1, _0807D194 @ =0x00000242
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #8
	bhi _0807D170
	b _0807D270
_0807D170:
	movs r3, #0
	strb r3, [r1]
	movs r2, #0x91
	lsls r2, r2, #2
	add r2, ip
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0x23
	ble _0807D18A
	strb r3, [r2]
_0807D18A:
	ldr r1, _0807D198 @ =sUnk_79c180
	movs r0, #0
	ldrsb r0, [r2, r0]
	b _0807D266
	.align 2, 0
_0807D194: .4byte 0x00000242
_0807D198: .4byte sUnk_79c180
_0807D19C:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	beq _0807D270
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r0, #5
	strb r0, [r1]
	ldr r1, _0807D1C0 @ =0x00000241
_0807D1B6:
	add r1, ip
	movs r0, #1
	strb r0, [r1]
	b _0807D270
	.align 2, 0
_0807D1C0: .4byte 0x00000241
_0807D1C4:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	bne _0807D270
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r0, #6
	strb r0, [r1]
	ldr r1, _0807D1E8 @ =0x0000024A
_0807D1DE:
	add r1, ip
	movs r0, #2
	strb r0, [r1]
	b _0807D270
	.align 2, 0
_0807D1E8: .4byte 0x0000024A
_0807D1EC:
	movs r2, #0x91
	lsls r2, r2, #2
	add r2, ip
	ldr r0, _0807D21C @ =0x00000245
	add r0, ip
	ldrb r4, [r2]
	movs r1, #0
	ldrsb r1, [r2, r1]
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r1, r0
	bne _0807D224
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r2, #0
	movs r0, #4
	strb r0, [r1]
	ldr r0, _0807D220 @ =0x00000241
	add r0, ip
	strb r2, [r0]
	b _0807D270
	.align 2, 0
_0807D21C: .4byte 0x00000245
_0807D220: .4byte 0x00000241
_0807D224:
	ldr r1, _0807D248 @ =0x00000242
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #8
	bls _0807D270
	movs r3, #0
	strb r3, [r1]
	ldr r0, _0807D24C @ =0x00000246
	add r0, ip
	ldrb r0, [r0]
	adds r0, r4, r0
	strb r0, [r2]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0x23
	ble _0807D250
	strb r3, [r2]
	b _0807D258
	.align 2, 0
_0807D248: .4byte 0x00000242
_0807D24C: .4byte 0x00000246
_0807D250:
	cmp r0, #0
	bge _0807D258
	movs r0, #0x23
	strb r0, [r2]
_0807D258:
	ldr r1, _0807D278 @ =sUnk_79c180
	movs r0, #0x91
	lsls r0, r0, #2
	add r0, ip
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
_0807D266:
	adds r0, r0, r1
	ldrb r1, [r0]
	mov r0, ip
	adds r0, #0xc6
	strb r1, [r0]
_0807D270:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807D278: .4byte sUnk_79c180

	thumb_func_start unk_7d27c
unk_7d27c: @ 0x0807D27C
	push {r4, r5, lr}
	ldr r0, _0807D294 @ =0x0300004C
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	bne _0807D29C
	ldr r0, _0807D298 @ =gNonGameplayRam
	movs r2, #0x90
	lsls r2, r2, #2
	adds r0, r0, r2
	b _0807D33E
	.align 2, 0
_0807D294: .4byte 0x0300004C
_0807D298: .4byte gNonGameplayRam
_0807D29C:
	ldr r0, _0807D2C4 @ =gNonGameplayRam
	movs r2, #0x90
	lsls r2, r2, #2
	adds r1, r0, r2
	movs r4, #1
	strb r4, [r1]
	subs r2, #0x20
	adds r1, r0, r2
	ldr r2, _0807D2C8 @ =gPreviousNavigationConversation
	ldrb r1, [r1]
	adds r3, r0, #0
	ldrb r2, [r2]
	cmp r1, r2
	bne _0807D2D0
	ldr r0, _0807D2CC @ =0x0000024A
	adds r1, r3, r0
	movs r0, #2
	strb r0, [r1]
	b _0807D2D6
	.align 2, 0
_0807D2C4: .4byte gNonGameplayRam
_0807D2C8: .4byte gPreviousNavigationConversation
_0807D2CC: .4byte 0x0000024A
_0807D2D0:
	ldr r1, _0807D324 @ =0x0000024A
	adds r0, r3, r1
	strb r4, [r0]
_0807D2D6:
	ldr r1, _0807D328 @ =sEvent_57607D
	ldrb r0, [r5]
	adds r0, r0, r1
	ldrb r1, [r0]
	movs r2, #0
	ldrsb r2, [r0, r2]
	cmp r2, #0
	blt _0807D340
	ldr r0, _0807D32C @ =0x00000245
	adds r5, r3, r0
	strb r1, [r5]
	movs r1, #0x91
	lsls r1, r1, #2
	adds r4, r3, r1
	movs r0, #0
	ldrsb r0, [r4, r0]
	cmp r2, r0
	beq _0807D340
	movs r2, #0x90
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #4
	strb r0, [r1]
	movs r1, #0
	ldrsb r1, [r5, r1]
	movs r0, #0
	ldrsb r0, [r4, r0]
	subs r1, r1, r0
	movs r0, #1
	cmp r1, #0
	bge _0807D316
	subs r0, #2
_0807D316:
	muls r1, r0, r1
	cmp r1, #0x12
	ble _0807D330
	movs r1, #1
	rsbs r1, r1, #0
	b _0807D338
	.align 2, 0
_0807D324: .4byte 0x0000024A
_0807D328: .4byte sEvent_57607D
_0807D32C: .4byte 0x00000245
_0807D330:
	cmp r1, #0x12
	bne _0807D336
	movs r0, #1
_0807D336:
	movs r1, #1
_0807D338:
	muls r1, r0, r1
	ldr r2, _0807D348 @ =0x00000246
	adds r0, r3, r2
_0807D33E:
	strb r1, [r0]
_0807D340:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807D348: .4byte 0x00000246
