    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start StatusScreenDrawMissileOrBomb
StatusScreenDrawMissileOrBomb: @ 0x0807E97C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x18
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	movs r0, #1
	rsbs r0, r0, #0
	str r0, [sp, #4]
	movs r2, #0
	ldr r0, _0807EA30 @ =sStatusScreenSectionSizes
	adds r1, r7, r0
	ldrb r1, [r1]
	cmp r2, r1
	bge _0807EA5C
	ldr r1, _0807EA34 @ =sStatusScreenUnk_58217c
	lsls r3, r7, #2
	mov sl, r3
	adds r5, r3, r7
	ldr r0, _0807EA38 @ =sStatusScreenUnk_5821b3
	adds r0, #2
	adds r0, r5, r0
	ldrb r0, [r0]
	str r0, [sp, #8]
	adds r0, r1, #3
	adds r0, r5, r0
	str r0, [sp, #0x14]
	adds r0, r5, r1
	ldrb r0, [r0]
	adds r1, #2
	adds r1, r5, r1
	ldrb r6, [r1]
	mov sb, r6
	str r5, [sp, #0xc]
	str r1, [sp, #0x10]
	lsls r0, r0, #5
	mov ip, r0
_0807E9D0:
	mov r0, ip
	add r0, sb
	mov r8, r0
	ldr r1, _0807EA38 @ =sStatusScreenUnk_5821b3
	adds r0, r5, r1
	ldrb r0, [r0]
	adds r0, r0, r2
	lsls r0, r0, #5
	ldr r3, [sp, #8]
	adds r6, r0, r3
	ldr r0, _0807EA3C @ =sPauseDebugItemFlagsPointers
	add r0, sl
	ldr r0, [r0]
	adds r0, r0, r2
	ldrb r0, [r0]
	ldr r1, [sp]
	ands r0, r1
	cmp r0, #0
	beq _0807EA48
	str r2, [sp, #4]
	ldr r3, [sp, #0x14]
	ldrb r0, [r3]
	mov r1, sb
	subs r0, r0, r1
	cmp r0, #0
	blt _0807EA4C
	ldr r0, _0807EA40 @ =sStatusScreenUnk_58217c+3
	ldr r3, [sp, #0xc]
	adds r0, r3, r0
	ldrb r1, [r0]
	ldr r3, [sp, #0x10]
	ldrb r0, [r3]
	subs r1, r1, r0
	lsls r0, r6, #1
	ldr r6, _0807EA44 @ =0x0600C800
	adds r4, r0, r6
	mov r3, r8
	lsls r0, r3, #1
	adds r3, r0, r6
	adds r1, #1
_0807EA20:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EA20
	b _0807EA4C
	.align 2, 0
_0807EA30: .4byte sStatusScreenSectionSizes
_0807EA34: .4byte sStatusScreenUnk_58217c
_0807EA38: .4byte sStatusScreenUnk_5821b3
_0807EA3C: .4byte sPauseDebugItemFlagsPointers
_0807EA40: .4byte sStatusScreenUnk_58217c+3
_0807EA44: .4byte 0x0600C800
_0807EA48:
	cmp r2, #0
	beq _0807EAB8
_0807EA4C:
	movs r6, #0x20
	add ip, r6
	adds r2, #1
	ldr r1, _0807EAC8 @ =sStatusScreenSectionSizes
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r2, r0
	blt _0807E9D0
_0807EA5C:
	ldr r2, [sp, #4]
	cmp r2, #0
	blt _0807EAB8
	ldr r3, _0807EACC @ =sStatusScreenUnk_58217c
	lsls r2, r7, #2
	adds r2, r2, r7
	adds r0, r2, r3
	ldr r1, [sp, #4]
	adds r1, #1
	ldrb r0, [r0]
	adds r1, r1, r0
	lsls r1, r1, #5
	adds r0, r3, #2
	adds r0, r2, r0
	ldrb r4, [r0]
	adds r1, r1, r4
	mov r8, r1
	ldr r1, _0807EAD0 @ =sStatusScreenUnk_5821b3
	adds r0, r1, #1
	adds r0, r2, r0
	ldrb r0, [r0]
	adds r1, #2
	adds r1, r2, r1
	lsls r0, r0, #5
	ldrb r1, [r1]
	adds r6, r0, r1
	adds r3, #3
	adds r2, r2, r3
	ldrb r0, [r2]
	subs r1, r0, r4
	cmp r1, #0
	blt _0807EAB8
	lsls r0, r6, #1
	ldr r3, _0807EAD4 @ =0x0600C800
	adds r4, r0, r3
	mov r6, r8
	lsls r0, r6, #1
	adds r3, r0, r3
	adds r1, #1
_0807EAAA:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EAAA
_0807EAB8:
	add sp, #0x18
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807EAC8: .4byte sStatusScreenSectionSizes
_0807EACC: .4byte sStatusScreenUnk_58217c
_0807EAD0: .4byte sStatusScreenUnk_5821b3
_0807EAD4: .4byte 0x0600C800

	thumb_func_start StatusScreenDrawMisc
StatusScreenDrawMisc: @ 0x0807EAD8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x24
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov r8, r0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	movs r0, #0
	str r0, [sp, #4]
	movs r4, #0
	ldr r0, _0807EBF8 @ =sStatusScreenSectionSizes
	mov r2, r8
	adds r1, r2, r0
	ldrb r1, [r1]
	cmp r4, r1
	bge _0807EB9C
	ldr r1, _0807EBFC @ =sStatusScreenUnk_58217c
	lsls r2, r2, #2
	mov sb, r2
	add r2, r8
	ldr r3, _0807EC00 @ =sStatusScreenUnk_5821b3
	mov sl, r3
	mov r0, sl
	adds r0, #2
	adds r0, r2, r0
	ldrb r0, [r0]
	str r0, [sp, #0xc]
	adds r0, r1, #3
	adds r6, r2, r0
	str r6, [sp, #0x1c]
	adds r0, r2, r1
	ldrb r0, [r0]
	adds r0, #1
	str r0, [sp, #8]
	adds r1, #2
	adds r1, r2, r1
	ldrb r7, [r1]
	str r2, [sp, #0x10]
	mov ip, r1
_0807EB30:
	ldr r1, [sp, #8]
	adds r0, r1, r4
	lsls r0, r0, #5
	adds r6, r0, r7
	mov r3, sl
	adds r0, r2, r3
	ldrb r0, [r0]
	adds r0, #1
	adds r0, r0, r4
	lsls r0, r0, #5
	ldr r1, [sp, #0xc]
	adds r3, r0, r1
	ldr r0, _0807EC04 @ =sPauseDebugItemFlagsPointers
	add r0, sb
	ldr r0, [r0]
	adds r0, r0, r4
	ldrb r0, [r0]
	ldr r1, [sp]
	ands r0, r1
	adds r5, r4, #1
	cmp r0, #0
	beq _0807EB90
	str r5, [sp, #4]
	ldr r4, [sp, #0x1c]
	ldrb r0, [r4]
	subs r0, r0, r7
	cmp r0, #0
	blt _0807EB90
	ldr r1, [sp, #0x10]
	ldr r4, _0807EC08 @ =sStatusScreenUnk_58217c+3
	adds r0, r1, r4
	ldrb r1, [r0]
	mov r4, ip
	ldrb r0, [r4]
	subs r1, r1, r0
	lsls r0, r3, #1
	ldr r3, _0807EC0C @ =0x0600C800
	adds r4, r0, r3
	lsls r0, r6, #1
	adds r3, r0, r3
	adds r1, #1
_0807EB82:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EB82
_0807EB90:
	adds r4, r5, #0
	ldr r0, _0807EBF8 @ =sStatusScreenSectionSizes
	add r0, r8
	ldrb r0, [r0]
	cmp r4, r0
	blt _0807EB30
_0807EB9C:
	ldr r4, [sp, #4]
	cmp r4, #0
	beq _0807EC6C
	movs r4, #0
	ldr r1, _0807EBFC @ =sStatusScreenUnk_58217c
	mov r6, r8
	lsls r6, r6, #2
	str r6, [sp, #0x14]
	adds r7, r6, #0
	add r7, r8
	adds r2, r1, #2
	adds r0, r7, r2
	mov ip, r0
	ldr r0, _0807EC00 @ =sStatusScreenUnk_5821b3
	adds r0, #2
	adds r0, r0, r7
	mov sl, r0
	adds r2, r7, r1
	mov sb, r2
	ldr r0, _0807EC00 @ =sStatusScreenUnk_5821b3
	adds r0, #1
	adds r0, r7, r0
	str r0, [sp, #0x18]
	ldr r3, _0807EC08 @ =sStatusScreenUnk_58217c+3
	adds r3, r7, r3
	str r3, [sp, #0x20]
_0807EBD0:
	cmp r4, #0
	bne _0807EC10
	ldr r6, [sp, #4]
	adds r6, #1
	str r6, [sp, #4]
	mov r1, sb
	ldrb r0, [r1]
	adds r0, r0, r6
	lsls r0, r0, #5
	mov r2, ip
	ldrb r2, [r2]
	adds r6, r0, r2
	ldr r3, [sp, #0x18]
	ldrb r0, [r3]
	lsls r0, r0, #5
	mov r1, sl
	ldrb r1, [r1]
	adds r3, r0, r1
	b _0807EC2A
	.align 2, 0
_0807EBF8: .4byte sStatusScreenSectionSizes
_0807EBFC: .4byte sStatusScreenUnk_58217c
_0807EC00: .4byte sStatusScreenUnk_5821b3
_0807EC04: .4byte sPauseDebugItemFlagsPointers
_0807EC08: .4byte sStatusScreenUnk_58217c+3
_0807EC0C: .4byte 0x0600C800
_0807EC10:
	mov r2, sb
	ldrb r0, [r2]
	lsls r0, r0, #5
	mov r3, ip
	ldrb r3, [r3]
	adds r6, r0, r3
	ldr r1, _0807EC7C @ =sStatusScreenUnk_5821b3
	adds r0, r7, r1
	ldrb r0, [r0]
	lsls r0, r0, #5
	mov r2, sl
	ldrb r2, [r2]
	adds r3, r0, r2
_0807EC2A:
	ldr r0, [sp, #0x20]
	ldrb r1, [r0]
	mov r2, ip
	ldrb r0, [r2]
	subs r1, r1, r0
	adds r5, r4, #1
	cmp r1, #0
	blt _0807EC66
	ldr r1, [sp, #0x14]
	add r1, r8
	ldr r4, _0807EC80 @ =sStatusScreenUnk_58217c+3
	adds r0, r1, r4
	ldrb r2, [r0]
	ldr r0, _0807EC84 @ =sStatusScreenUnk_58217c+2
	adds r1, r1, r0
	ldrb r0, [r1]
	subs r2, r2, r0
	lsls r0, r3, #1
	ldr r1, _0807EC88 @ =0x0600C800
	adds r4, r0, r1
	lsls r0, r6, #1
	adds r3, r0, r1
	adds r1, r2, #1
_0807EC58:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EC58
_0807EC66:
	adds r4, r5, #0
	cmp r4, #1
	ble _0807EBD0
_0807EC6C:
	add sp, #0x24
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807EC7C: .4byte sStatusScreenUnk_5821b3
_0807EC80: .4byte sStatusScreenUnk_58217c+3
_0807EC84: .4byte sStatusScreenUnk_58217c+2
_0807EC88: .4byte 0x0600C800
