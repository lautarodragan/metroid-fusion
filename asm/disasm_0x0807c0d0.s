    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NavigationConversationUpdateXParasitePopUp
NavigationConversationUpdateXParasitePopUp: @ 0x0807C0D0
	push {r4, r5, r6, r7, lr}
	bl unk_7c3b4
	ldr r0, _0807C148 @ =sNavConversationUnk_57bc50
	mov ip, r0
	ldr r3, _0807C14C @ =gNonGameplayRam
	ldr r1, _0807C150 @ =0x0000021A
	adds r6, r3, r1
	ldrb r1, [r6]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	mov r2, ip
	adds r1, r0, r2
	ldrb r0, [r1, #0x12]
	lsls r2, r0, #0x1c
	lsrs r0, r2, #0x1c
	cmp r0, #8
	beq _0807C0F8
	b _0807C20C
_0807C0F8:
	ldr r7, [r1]
	ldr r0, _0807C154 @ =0x0000021B
	adds r2, r3, r0
	movs r1, #0x87
	lsls r1, r1, #2
	adds r4, r3, r1
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r2]
	ldrb r0, [r0, #1]
	cmp r1, r0
	bhs _0807C114
	b _0807C2F4
_0807C114:
	movs r5, #0
	strb r5, [r2]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	ldrb r2, [r6]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	add r1, ip
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #4]
	cmp r0, r1
	blo _0807C134
	strb r5, [r4]
_0807C134:
	ldr r2, _0807C158 @ =0x00000219
	adds r0, r3, r2
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807C160
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	ldr r0, _0807C15C @ =0x02004000
	b _0807C17E
	.align 2, 0
_0807C148: .4byte sNavConversationUnk_57bc50
_0807C14C: .4byte gNonGameplayRam
_0807C150: .4byte 0x0000021A
_0807C154: .4byte 0x0000021B
_0807C158: .4byte 0x00000219
_0807C15C: .4byte 0x02004000
_0807C160:
	cmp r0, #2
	bne _0807C174
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	ldr r0, _0807C170 @ =0x02008000
	b _0807C17E
	.align 2, 0
_0807C170: .4byte 0x02008000
_0807C174:
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #0x80
	lsls r0, r0, #0x12
_0807C17E:
	str r0, [r1]
	ldr r3, _0807C1F0 @ =sNavConversationUnk_57bc50
	ldr r2, _0807C1F4 @ =gNonGameplayRam
	ldr r1, _0807C1F8 @ =0x0000021A
	adds r0, r2, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r0, r0, r3
	ldrb r0, [r0, #0x11]
	lsls r3, r0, #0x1c
	lsrs r6, r0, #4
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r0]
	movs r0, #3
	ands r0, r1
	lsls r4, r0, #8
	lsrs r1, r1, #2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xb
	adds r4, r4, r0
	movs r0, #0x85
	lsls r0, r0, #2
	adds r2, r2, r0
	ldr r0, [r2]
	adds r5, r0, r4
	str r5, [r2]
	lsrs r4, r3, #0x1c
	cmp r4, #0
	bgt _0807C1CA
	b _0807C2F4
_0807C1CA:
	ldr r3, _0807C1FC @ =0x040000D4
	lsls r2, r4, #0xa
	ldr r0, _0807C200 @ =0x06014300
	adds r1, r2, r0
	lsls r0, r6, #0xa
	adds r1, r1, r0
	adds r2, r2, r5
	ldr r5, _0807C204 @ =0xFFFFFC00
	ldr r6, _0807C208 @ =0x80000080
_0807C1DC:
	adds r1, r1, r5
	adds r2, r2, r5
	subs r4, #1
	str r2, [r3]
	str r1, [r3, #4]
	str r6, [r3, #8]
	ldr r0, [r3, #8]
	cmp r4, #0
	bgt _0807C1DC
	b _0807C2F4
	.align 2, 0
_0807C1F0: .4byte sNavConversationUnk_57bc50
_0807C1F4: .4byte gNonGameplayRam
_0807C1F8: .4byte 0x0000021A
_0807C1FC: .4byte 0x040000D4
_0807C200: .4byte 0x06014300
_0807C204: .4byte 0xFFFFFC00
_0807C208: .4byte 0x80000080
_0807C20C:
	lsrs r0, r2, #0x1c
	cmp r0, #4
	bne _0807C2F4
	ldr r7, [r1]
	ldr r1, _0807C260 @ =0x0000021B
	adds r2, r3, r1
	movs r0, #0x87
	lsls r0, r0, #2
	adds r4, r3, r0
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r2]
	ldrb r0, [r0, #1]
	cmp r1, r0
	blo _0807C2F4
	movs r5, #0
	strb r5, [r2]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	ldrb r2, [r6]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	add r1, ip
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #4]
	cmp r0, r1
	blo _0807C24C
	strb r5, [r4]
_0807C24C:
	ldr r1, _0807C264 @ =0x00000219
	adds r0, r3, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807C26C
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	ldr r0, _0807C268 @ =0x02004000
	b _0807C28A
	.align 2, 0
_0807C260: .4byte 0x0000021B
_0807C264: .4byte 0x00000219
_0807C268: .4byte 0x02004000
_0807C26C:
	cmp r0, #2
	bne _0807C280
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	ldr r0, _0807C27C @ =0x02008000
	b _0807C28A
	.align 2, 0
_0807C27C: .4byte 0x02008000
_0807C280:
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #0x80
	lsls r0, r0, #0x12
_0807C28A:
	str r0, [r1]
	ldr r3, _0807C2FC @ =sNavConversationUnk_57bc50
	ldr r2, _0807C300 @ =gNonGameplayRam
	ldr r1, _0807C304 @ =0x0000021A
	adds r0, r2, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r0, r0, r3
	ldrb r0, [r0, #0x11]
	lsls r3, r0, #0x1c
	lsrs r6, r0, #4
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r0]
	movs r0, #7
	ands r0, r1
	lsls r4, r0, #7
	lsrs r1, r1, #3
	lsls r1, r1, #0xc
	adds r4, r4, r1
	movs r0, #0x85
	lsls r0, r0, #2
	adds r2, r2, r0
	ldr r0, [r2]
	adds r5, r0, r4
	str r5, [r2]
	lsrs r4, r3, #0x1c
	cmp r4, #0
	ble _0807C2F4
	ldr r3, _0807C308 @ =0x040000D4
	lsls r2, r4, #0xa
	ldr r0, _0807C30C @ =0x06014340
	adds r1, r2, r0
	lsls r0, r6, #0xa
	adds r1, r1, r0
	adds r2, r2, r5
	ldr r5, _0807C310 @ =0xFFFFFC00
	ldr r6, _0807C314 @ =0x80000040
_0807C2E2:
	adds r1, r1, r5
	adds r2, r2, r5
	subs r4, #1
	str r2, [r3]
	str r1, [r3, #4]
	str r6, [r3, #8]
	ldr r0, [r3, #8]
	cmp r4, #0
	bgt _0807C2E2
_0807C2F4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807C2FC: .4byte sNavConversationUnk_57bc50
_0807C300: .4byte gNonGameplayRam
_0807C304: .4byte 0x0000021A
_0807C308: .4byte 0x040000D4
_0807C30C: .4byte 0x06014340
_0807C310: .4byte 0xFFFFFC00
_0807C314: .4byte 0x80000040
