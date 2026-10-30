@ Voicegroups: arrays of 12 byte voices (type, key, length, pan/sweep, then a sample,
@ wave or sub-voicegroup pointer, or a CGB setting, then attack, decay, sustain, release,
@ or for a keysplit voice a keysplit table pointer). The bytes come from
@ data/voicegroups/<offset>.bin; the pointers are written as symbols so that they
@ follow the data they point to.

    .include "asm/voicegroup.inc"

    .section .rodata

    .align 2
    .type sVoicegroup_a5710, object
    .global sVoicegroup_a5710
sVoicegroup_a5710:
    voice_ptr "data/voicegroups/a5710.bin", 0, DirectSoundData_080AA488
    voice_ptr "data/voicegroups/a5710.bin", 1, DirectSoundData_080AA84C
    voice_ptr "data/voicegroups/a5710.bin", 2, DirectSoundData_080AA9B0
    voice "data/voicegroups/a5710.bin", 3
    voice_ptr "data/voicegroups/a5710.bin", 4, DirectSoundData_080AB22C
    voice_ptr "data/voicegroups/a5710.bin", 5, DirectSoundData_080ABA4C
    voice_ptr "data/voicegroups/a5710.bin", 6, DirectSoundData_080AC340
    voice_ptr "data/voicegroups/a5710.bin", 7, DirectSoundData_080ABA4C
    voice "data/voicegroups/a5710.bin", 8
    voice_ptr "data/voicegroups/a5710.bin", 9, DirectSoundData_080ABA4C
    voice_ptr "data/voicegroups/a5710.bin", 10, DirectSoundData_080ACA18
    voice_ptr "data/voicegroups/a5710.bin", 11, DirectSoundData_080ABA4C
    voice_ptr "data/voicegroups/a5710.bin", 12, DirectSoundData_080ABA4C
    voice_ptr "data/voicegroups/a5710.bin", 13, DirectSoundData_080AD784
    voice "data/voicegroups/a5710.bin", 14
    voice "data/voicegroups/a5710.bin", 15
    voice "data/voicegroups/a5710.bin", 16
    voice "data/voicegroups/a5710.bin", 17
    voice_ptr "data/voicegroups/a5710.bin", 18, DirectSoundData_080AE354
    voice "data/voicegroups/a5710.bin", 19
    voice "data/voicegroups/a5710.bin", 20
    voice_ptr "data/voicegroups/a5710.bin", 21, DirectSoundData_080AD784
    voice "data/voicegroups/a5710.bin", 22
    voice "data/voicegroups/a5710.bin", 23
    voice "data/voicegroups/a5710.bin", 24
    voice "data/voicegroups/a5710.bin", 25
    voice "data/voicegroups/a5710.bin", 26
    voice "data/voicegroups/a5710.bin", 27
    voice "data/voicegroups/a5710.bin", 28
    voice "data/voicegroups/a5710.bin", 29
    voice "data/voicegroups/a5710.bin", 30
    voice "data/voicegroups/a5710.bin", 31
    voice "data/voicegroups/a5710.bin", 32
    voice_ptr "data/voicegroups/a5710.bin", 33, DirectSoundData_080AD784
    voice "data/voicegroups/a5710.bin", 34
    voice "data/voicegroups/a5710.bin", 35
    voice "data/voicegroups/a5710.bin", 36
    voice "data/voicegroups/a5710.bin", 37
    voice "data/voicegroups/a5710.bin", 38
    voice_ptr "data/voicegroups/a5710.bin", 39, DirectSoundData_080AEBD0
    voice "data/voicegroups/a5710.bin", 40
    voice "data/voicegroups/a5710.bin", 41
    voice "data/voicegroups/a5710.bin", 42
    voice "data/voicegroups/a5710.bin", 43
    voice "data/voicegroups/a5710.bin", 44
    voice "data/voicegroups/a5710.bin", 45
    voice "data/voicegroups/a5710.bin", 46
    voice "data/voicegroups/a5710.bin", 47
    voice "data/voicegroups/a5710.bin", 48
    voice "data/voicegroups/a5710.bin", 49
    voice "data/voicegroups/a5710.bin", 50
    voice "data/voicegroups/a5710.bin", 51
    voice_ptr "data/voicegroups/a5710.bin", 52, DirectSoundData_080ACA18
    voice "data/voicegroups/a5710.bin", 53
    voice_ptr "data/voicegroups/a5710.bin", 54, DirectSoundData_080AC340
    voice "data/voicegroups/a5710.bin", 55
    voice "data/voicegroups/a5710.bin", 56
    voice "data/voicegroups/a5710.bin", 57
    voice_ptr "data/voicegroups/a5710.bin", 58, DirectSoundData_080AEE10
    voice_ptr "data/voicegroups/a5710.bin", 59, DirectSoundData_080AF6B8
    .size sVoicegroup_a5710, . - sVoicegroup_a5710

    .align 2
    .type sVoicegroup_a59e0, object
    .global sVoicegroup_a59e0
sVoicegroup_a59e0:
    voice_ptr "data/voicegroups/a59e0.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice_ptr "data/voicegroups/a59e0.bin", 1, DirectSoundData_080AFED0
    voice_ptr "data/voicegroups/a59e0.bin", 2, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a59e0.bin", 3, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a59e0.bin", 4, DirectSoundData_080B3148
    voice "data/voicegroups/a59e0.bin", 5
    voice "data/voicegroups/a59e0.bin", 6
    voice "data/voicegroups/a59e0.bin", 7
    voice "data/voicegroups/a59e0.bin", 8
    voice "data/voicegroups/a59e0.bin", 9
    voice_ptr "data/voicegroups/a59e0.bin", 10, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a59e0.bin", 11, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a59e0.bin", 12, DirectSoundData_080B4520
    voice "data/voicegroups/a59e0.bin", 13
    voice_ptr "data/voicegroups/a59e0.bin", 14, DirectSoundData_080B51D0
    voice_ptr "data/voicegroups/a59e0.bin", 15, DirectSoundData_080B5750
    voice "data/voicegroups/a59e0.bin", 16
    voice "data/voicegroups/a59e0.bin", 17
    voice "data/voicegroups/a59e0.bin", 18
    voice "data/voicegroups/a59e0.bin", 19
    voice "data/voicegroups/a59e0.bin", 20
    voice_ptr "data/voicegroups/a59e0.bin", 21, DirectSoundData_080B5BC8
    voice "data/voicegroups/a59e0.bin", 22
    voice "data/voicegroups/a59e0.bin", 23
    voice_ptr "data/voicegroups/a59e0.bin", 24, DirectSoundData_080B60A4
    voice "data/voicegroups/a59e0.bin", 25
    voice "data/voicegroups/a59e0.bin", 26
    voice "data/voicegroups/a59e0.bin", 27
    voice_ptr "data/voicegroups/a59e0.bin", 28, DirectSoundData_080B6A84
    .size sVoicegroup_a59e0, . - sVoicegroup_a59e0

    .align 2
    .type sVoicegroup_a5b3c, object
    .global sVoicegroup_a5b3c
sVoicegroup_a5b3c:
    voice_ptr "data/voicegroups/a5b3c.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5b3c.bin", 1
    voice_ptr "data/voicegroups/a5b3c.bin", 2, DirectSoundData_080B7054
    voice "data/voicegroups/a5b3c.bin", 3
    voice_ptr "data/voicegroups/a5b3c.bin", 4, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5b3c.bin", 5, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a5b3c.bin", 6, DirectSoundData_080B75BC
    voice_ptr "data/voicegroups/a5b3c.bin", 7, sVoicegroup_a5710 + 14 * 12
    voice_ptr "data/voicegroups/a5b3c.bin", 8, DirectSoundData_080B7A14
    voice "data/voicegroups/a5b3c.bin", 9
    voice_ptr "data/voicegroups/a5b3c.bin", 10, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5b3c.bin", 11, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5b3c.bin", 12, DirectSoundData_080B0310
    .size sVoicegroup_a5b3c, . - sVoicegroup_a5b3c

    .align 2
    .type sVoicegroup_a5bd8, object
    .global sVoicegroup_a5bd8
sVoicegroup_a5bd8:
    voice_ptr "data/voicegroups/a5bd8.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5bd8.bin", 1
    voice_ptr "data/voicegroups/a5bd8.bin", 2, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5bd8.bin", 3, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5bd8.bin", 4, DirectSoundData_080B3910
    voice "data/voicegroups/a5bd8.bin", 5
    voice_ptr "data/voicegroups/a5bd8.bin", 6, DirectSoundData_080B83C0
    voice_ptr "data/voicegroups/a5bd8.bin", 7, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a5bd8.bin", 8, DirectSoundData_080BD1B0
    voice_ptr "data/voicegroups/a5bd8.bin", 9, DirectSoundData_080BA2C0
    voice_ptr "data/voicegroups/a5bd8.bin", 10, DirectSoundData_080BA964
    voice_ptr "data/voicegroups/a5bd8.bin", 11, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5bd8.bin", 12, DirectSoundData_080B0E50
    voice "data/voicegroups/a5bd8.bin", 13
    voice_ptr "data/voicegroups/a5bd8.bin", 14, DirectSoundData_080BBB78
    voice_ptr "data/voicegroups/a5bd8.bin", 15, DirectSoundData_080BD1B0
    voice_ptr "data/voicegroups/a5bd8.bin", 16, DirectSoundData_080BDB48
    .size sVoicegroup_a5bd8, . - sVoicegroup_a5bd8

    .align 2
    .type sVoicegroup_a5ca4, object
    .global sVoicegroup_a5ca4
sVoicegroup_a5ca4:
    voice_ptr "data/voicegroups/a5ca4.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5ca4.bin", 1
    voice_ptr "data/voicegroups/a5ca4.bin", 2, DirectSoundData_080BE5B8
    voice_ptr "data/voicegroups/a5ca4.bin", 3, DirectSoundData_080BF78C
    voice_ptr "data/voicegroups/a5ca4.bin", 4, DirectSoundData_080C857C
    voice_ptr "data/voicegroups/a5ca4.bin", 5, DirectSoundData_080B75BC
    voice_ptr "data/voicegroups/a5ca4.bin", 6, DirectSoundData_080C9288
    .size sVoicegroup_a5ca4, . - sVoicegroup_a5ca4

    .align 2
    .type sVoicegroup_a5cf8, object
    .global sVoicegroup_a5cf8
sVoicegroup_a5cf8:
    voice_ptr "data/voicegroups/a5cf8.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5cf8.bin", 1
    voice_ptr "data/voicegroups/a5cf8.bin", 2, DirectSoundData_080C9BE4
    voice_ptr "data/voicegroups/a5cf8.bin", 3, DirectSoundData_080CA0BC
    voice_ptr "data/voicegroups/a5cf8.bin", 4, DirectSoundData_080B83C0
    voice_keysplit "data/voicegroups/a5cf8.bin", 5, sVoicegroup_a5cf8, sKeysplitTable_a8c44 - 36
    voice_ptr "data/voicegroups/a5cf8.bin", 6, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5cf8.bin", 7, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a5cf8.bin", 8, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5cf8.bin", 9, DirectSoundData_080CACAC
    voice_ptr "data/voicegroups/a5cf8.bin", 10, DirectSoundData_080CACAC
    voice "data/voicegroups/a5cf8.bin", 11
    voice "data/voicegroups/a5cf8.bin", 12
    .size sVoicegroup_a5cf8, . - sVoicegroup_a5cf8

    .align 2
    .type sVoicegroup_a5d94, object
    .global sVoicegroup_a5d94
sVoicegroup_a5d94:
    voice_ptr "data/voicegroups/a5d94.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5d94.bin", 1
    voice_ptr "data/voicegroups/a5d94.bin", 2, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5d94.bin", 3, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5d94.bin", 4, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5d94.bin", 5, DirectSoundData_080B8B88
    voice "data/voicegroups/a5d94.bin", 6
    voice "data/voicegroups/a5d94.bin", 7
    voice_ptr "data/voicegroups/a5d94.bin", 8, DirectSoundData_080ABA4C
    voice "data/voicegroups/a5d94.bin", 9
    voice "data/voicegroups/a5d94.bin", 10
    voice_ptr "data/voicegroups/a5d94.bin", 11, DirectSoundData_080B6A84
    voice_ptr "data/voicegroups/a5d94.bin", 12, DirectSoundData_080AA84C
    voice_ptr "data/voicegroups/a5d94.bin", 13, DirectSoundData_080AE354
    .size sVoicegroup_a5d94, . - sVoicegroup_a5d94

    .align 2
    .type sVoicegroup_a5e3c, object
    .global sVoicegroup_a5e3c
sVoicegroup_a5e3c:
    voice_ptr "data/voicegroups/a5e3c.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice_ptr "data/voicegroups/a5e3c.bin", 1, sVoicegroup_a5bd8 + 11 * 12
    voice "data/voicegroups/a5e3c.bin", 2
    voice "data/voicegroups/a5e3c.bin", 3
    voice_ptr "data/voicegroups/a5e3c.bin", 4, DirectSoundData_080CCD9C
    voice_ptr "data/voicegroups/a5e3c.bin", 5, DirectSoundData_080CEE3C
    voice_ptr "data/voicegroups/a5e3c.bin", 6, DirectSoundData_080CEE3C
    voice "data/voicegroups/a5e3c.bin", 7
    voice "data/voicegroups/a5e3c.bin", 8
    voice "data/voicegroups/a5e3c.bin", 9
    voice_ptr "data/voicegroups/a5e3c.bin", 10, DirectSoundData_080CF140
    voice_ptr "data/voicegroups/a5e3c.bin", 11, DirectSoundData_080BBB78
    voice_ptr "data/voicegroups/a5e3c.bin", 12, DirectSoundData_080CF140
    voice "data/voicegroups/a5e3c.bin", 13
    voice "data/voicegroups/a5e3c.bin", 14
    voice_ptr "data/voicegroups/a5e3c.bin", 15, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5e3c.bin", 16, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a5e3c.bin", 17, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5e3c.bin", 18, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a5e3c.bin", 19, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a5e3c.bin", 20, DirectSoundData_080D05B8
    voice_ptr "data/voicegroups/a5e3c.bin", 21, DirectSoundData_080D0BF4
    voice "data/voicegroups/a5e3c.bin", 22
    voice_ptr "data/voicegroups/a5e3c.bin", 23, DirectSoundData_080D1414
    voice_ptr "data/voicegroups/a5e3c.bin", 24, DirectSoundData_080D1CB4
    .size sVoicegroup_a5e3c, . - sVoicegroup_a5e3c

    .align 2
    .type sVoicegroup_a5f68, object
    .global sVoicegroup_a5f68
sVoicegroup_a5f68:
    voice_ptr "data/voicegroups/a5f68.bin", 0, DirectSoundData_080D1F1C
    voice "data/voicegroups/a5f68.bin", 1
    voice_ptr "data/voicegroups/a5f68.bin", 2, DirectSoundData_080D2924
    voice_ptr "data/voicegroups/a5f68.bin", 3, DirectSoundData_080D3598
    voice_ptr "data/voicegroups/a5f68.bin", 4, DirectSoundData_080D3598
    voice "data/voicegroups/a5f68.bin", 5
    voice "data/voicegroups/a5f68.bin", 6
    .size sVoicegroup_a5f68, . - sVoicegroup_a5f68

    .align 2
    .type sVoicegroup_a5fbc, object
    .global sVoicegroup_a5fbc
sVoicegroup_a5fbc:
    voice_ptr "data/voicegroups/a5fbc.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a5fbc.bin", 1
    voice_ptr "data/voicegroups/a5fbc.bin", 2, DirectSoundData_080D3694
    voice_ptr "data/voicegroups/a5fbc.bin", 3, DirectSoundData_080D4204
    voice_ptr "data/voicegroups/a5fbc.bin", 4, DirectSoundData_080D3694
    voice_ptr "data/voicegroups/a5fbc.bin", 5, sVoicegroup_a5e3c + 10 * 12
    voice_ptr "data/voicegroups/a5fbc.bin", 6, DirectSoundData_080D468C
    voice "data/voicegroups/a5fbc.bin", 7
    voice "data/voicegroups/a5fbc.bin", 8
    voice_ptr "data/voicegroups/a5fbc.bin", 9, DirectSoundData_080D4CB4
    voice "data/voicegroups/a5fbc.bin", 10
    voice "data/voicegroups/a5fbc.bin", 11
    voice "data/voicegroups/a5fbc.bin", 12
    voice_ptr "data/voicegroups/a5fbc.bin", 13, DirectSoundData_080D5304
    voice_ptr "data/voicegroups/a5fbc.bin", 14, DirectSoundData_080D55D0
    voice "data/voicegroups/a5fbc.bin", 15
    voice_ptr "data/voicegroups/a5fbc.bin", 16, DirectSoundData_080D5A40
    voice_ptr "data/voicegroups/a5fbc.bin", 17, DirectSoundData_080D5BB8
    .size sVoicegroup_a5fbc, . - sVoicegroup_a5fbc

    .align 2
    .type sVoicegroup_a6094, object
    .global sVoicegroup_a6094
sVoicegroup_a6094:
    voice "data/voicegroups/a6094.bin", 0
    voice "data/voicegroups/a6094.bin", 1
    voice "data/voicegroups/a6094.bin", 2
    voice "data/voicegroups/a6094.bin", 3
    voice "data/voicegroups/a6094.bin", 4
    voice_ptr "data/voicegroups/a6094.bin", 5, DirectSoundData_080D4204
    voice "data/voicegroups/a6094.bin", 6
    voice "data/voicegroups/a6094.bin", 7
    voice_ptr "data/voicegroups/a6094.bin", 8, DirectSoundData_080D767C
    voice_ptr "data/voicegroups/a6094.bin", 9, DirectSoundData_080D8528
    voice_ptr "data/voicegroups/a6094.bin", 10, DirectSoundData_080DABEC
    voice "data/voicegroups/a6094.bin", 11
    voice "data/voicegroups/a6094.bin", 12
    voice "data/voicegroups/a6094.bin", 13
    voice_ptr "data/voicegroups/a6094.bin", 14, DirectSoundData_080D5E5C
    voice "data/voicegroups/a6094.bin", 15
    voice "data/voicegroups/a6094.bin", 16
    voice "data/voicegroups/a6094.bin", 17
    voice "data/voicegroups/a6094.bin", 18
    voice "data/voicegroups/a6094.bin", 19
    voice "data/voicegroups/a6094.bin", 20
    voice_ptr "data/voicegroups/a6094.bin", 21, DirectSoundData_080D5ECC
    voice_ptr "data/voicegroups/a6094.bin", 22, DirectSoundData_080D73C8
    voice "data/voicegroups/a6094.bin", 23
    voice "data/voicegroups/a6094.bin", 24
    voice "data/voicegroups/a6094.bin", 25
    voice_ptr "data/voicegroups/a6094.bin", 26, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a6094.bin", 27, DirectSoundData_080DCB7C
    voice_ptr "data/voicegroups/a6094.bin", 28, DirectSoundData_080E1DAC
    voice_ptr "data/voicegroups/a6094.bin", 29, DirectSoundData_080E45AC
    .size sVoicegroup_a6094, . - sVoicegroup_a6094

    .align 2
    .type sVoicegroup_a61fc, object
    .global sVoicegroup_a61fc
sVoicegroup_a61fc:
    voice_ptr "data/voicegroups/a61fc.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a61fc.bin", 1
    voice_ptr "data/voicegroups/a61fc.bin", 2, DirectSoundData_080E6FBC
    voice_ptr "data/voicegroups/a61fc.bin", 3, DirectSoundData_080E7880
    voice_ptr "data/voicegroups/a61fc.bin", 4, DirectSoundData_080EBEFC
    voice_ptr "data/voicegroups/a61fc.bin", 5, DirectSoundData_080E84E8
    voice_ptr "data/voicegroups/a61fc.bin", 6, DirectSoundData_080E84E8
    voice_ptr "data/voicegroups/a61fc.bin", 7, sVoicegroup_a5e3c + 17 * 12
    voice "data/voicegroups/a61fc.bin", 8
    voice_ptr "data/voicegroups/a61fc.bin", 9, DirectSoundData_080EA434
    voice "data/voicegroups/a61fc.bin", 10
    voice_ptr "data/voicegroups/a61fc.bin", 11, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a61fc.bin", 12, DirectSoundData_080ED67C
    voice "data/voicegroups/a61fc.bin", 13
    voice "data/voicegroups/a61fc.bin", 14
    voice "data/voicegroups/a61fc.bin", 15
    voice_ptr "data/voicegroups/a61fc.bin", 16, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a61fc.bin", 17, DirectSoundData_080EA74C
    voice_ptr "data/voicegroups/a61fc.bin", 18, DirectSoundData_080EADF4
    voice_ptr "data/voicegroups/a61fc.bin", 19, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a61fc.bin", 20, DirectSoundData_080BDB48
    .size sVoicegroup_a61fc, . - sVoicegroup_a61fc

    .align 2
    .type sVoicegroup_a62f8, object
    .global sVoicegroup_a62f8
sVoicegroup_a62f8:
    voice_ptr "data/voicegroups/a62f8.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a62f8.bin", 1
    voice "data/voicegroups/a62f8.bin", 2
    voice "data/voicegroups/a62f8.bin", 3
    voice_ptr "data/voicegroups/a62f8.bin", 4, DirectSoundData_080EDB54
    voice_ptr "data/voicegroups/a62f8.bin", 5, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a62f8.bin", 6, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a62f8.bin", 7, DirectSoundData_080EE514
    voice_ptr "data/voicegroups/a62f8.bin", 8, DirectSoundData_080EF02C
    voice "data/voicegroups/a62f8.bin", 9
    voice_ptr "data/voicegroups/a62f8.bin", 10, DirectSoundData_080EF660
    voice_ptr "data/voicegroups/a62f8.bin", 11, sWaveData_a8cac
    voice_ptr "data/voicegroups/a62f8.bin", 12, DirectSoundData_080F0CB0
    voice_ptr "data/voicegroups/a62f8.bin", 13, DirectSoundData_080EDB54
    voice_ptr "data/voicegroups/a62f8.bin", 14, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a62f8.bin", 15, DirectSoundData_080BA964
    voice_ptr "data/voicegroups/a62f8.bin", 16, DirectSoundData_080EA434
    voice "data/voicegroups/a62f8.bin", 17
    voice "data/voicegroups/a62f8.bin", 18
    voice_ptr "data/voicegroups/a62f8.bin", 19, DirectSoundData_080BA964
    voice_ptr "data/voicegroups/a62f8.bin", 20, DirectSoundData_080B8B88
    voice "data/voicegroups/a62f8.bin", 21
    voice_ptr "data/voicegroups/a62f8.bin", 22, DirectSoundData_080F32C8
    voice_ptr "data/voicegroups/a62f8.bin", 23, DirectSoundData_080F3AFC
    voice "data/voicegroups/a62f8.bin", 24
    voice "data/voicegroups/a62f8.bin", 25
    voice_ptr "data/voicegroups/a62f8.bin", 26, DirectSoundData_080BA2C0
    voice_ptr "data/voicegroups/a62f8.bin", 27, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a62f8.bin", 28, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a62f8.bin", 29, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a62f8.bin", 30, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a62f8.bin", 31, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a62f8.bin", 32, DirectSoundData_080B8B88
    voice "data/voicegroups/a62f8.bin", 33
    voice_ptr "data/voicegroups/a62f8.bin", 34, DirectSoundData_080C9BE4
    voice_ptr "data/voicegroups/a62f8.bin", 35, DirectSoundData_080CA0BC
    voice_ptr "data/voicegroups/a62f8.bin", 36, DirectSoundData_080B83C0
    voice_ptr "data/voicegroups/a62f8.bin", 37, DirectSoundData_080B0E50
    .size sVoicegroup_a62f8, . - sVoicegroup_a62f8

    .align 2
    .type sVoicegroup_a64c0, object
    .global sVoicegroup_a64c0
sVoicegroup_a64c0:
    voice_ptr "data/voicegroups/a64c0.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a64c0.bin", 1
    voice_ptr "data/voicegroups/a64c0.bin", 2, DirectSoundData_080D468C
    voice_ptr "data/voicegroups/a64c0.bin", 3, DirectSoundData_080B8B88
    voice "data/voicegroups/a64c0.bin", 4
    voice_ptr "data/voicegroups/a64c0.bin", 5, DirectSoundData_080BA964
    voice_ptr "data/voicegroups/a64c0.bin", 6, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a64c0.bin", 7, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a64c0.bin", 8, DirectSoundData_080D3598
    voice_ptr "data/voicegroups/a64c0.bin", 9, DirectSoundData_080F4548
    voice_ptr "data/voicegroups/a64c0.bin", 10, DirectSoundData_080BDB48
    .size sVoicegroup_a64c0, . - sVoicegroup_a64c0

    .align 2
    .type sVoicegroup_a6544, object
    .global sVoicegroup_a6544
sVoicegroup_a6544:
    voice_ptr "data/voicegroups/a6544.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a6544.bin", 1
    voice "data/voicegroups/a6544.bin", 2
    voice_ptr "data/voicegroups/a6544.bin", 3, DirectSoundData_080ACA18
    voice "data/voicegroups/a6544.bin", 4
    voice "data/voicegroups/a6544.bin", 5
    voice_ptr "data/voicegroups/a6544.bin", 6, DirectSoundData_080F5F80
    voice "data/voicegroups/a6544.bin", 7
    voice "data/voicegroups/a6544.bin", 8
    voice_ptr "data/voicegroups/a6544.bin", 9, DirectSoundData_080F6FF0
    voice_ptr "data/voicegroups/a6544.bin", 10, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a6544.bin", 11, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a6544.bin", 12, DirectSoundData_080B8B88
    voice "data/voicegroups/a6544.bin", 13
    voice "data/voicegroups/a6544.bin", 14
    voice "data/voicegroups/a6544.bin", 15
    voice "data/voicegroups/a6544.bin", 16
    voice_ptr "data/voicegroups/a6544.bin", 17, DirectSoundData_080DABEC
    voice_ptr "data/voicegroups/a6544.bin", 18, DirectSoundData_080D8528
    .size sVoicegroup_a6544, . - sVoicegroup_a6544

    .align 2
    .type sVoicegroup_a6628, object
    .global sVoicegroup_a6628
sVoicegroup_a6628:
    voice "data/voicegroups/a6628.bin", 0
    voice "data/voicegroups/a6628.bin", 1
    voice_ptr "data/voicegroups/a6628.bin", 2, DirectSoundData_080B83C0
    voice_ptr "data/voicegroups/a6628.bin", 3, DirectSoundData_080F79E0
    voice_ptr "data/voicegroups/a6628.bin", 4, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a6628.bin", 5, DirectSoundData_080CACAC
    voice_ptr "data/voicegroups/a6628.bin", 6, DirectSoundData_080D5ECC
    voice "data/voicegroups/a6628.bin", 7
    voice_ptr "data/voicegroups/a6628.bin", 8, DirectSoundData_080F79E0
    voice "data/voicegroups/a6628.bin", 9
    voice "data/voicegroups/a6628.bin", 10
    voice "data/voicegroups/a6628.bin", 11
    voice "data/voicegroups/a6628.bin", 12
    voice "data/voicegroups/a6628.bin", 13
    voice "data/voicegroups/a6628.bin", 14
    voice "data/voicegroups/a6628.bin", 15
    voice "data/voicegroups/a6628.bin", 16
    voice_ptr "data/voicegroups/a6628.bin", 17, DirectSoundData_080B8B88
    voice "data/voicegroups/a6628.bin", 18
    voice_ptr "data/voicegroups/a6628.bin", 19, DirectSoundData_080B0E50
    .size sVoicegroup_a6628, . - sVoicegroup_a6628

    .align 2
    .type sVoicegroup_a6718, object
    .global sVoicegroup_a6718
sVoicegroup_a6718:
    voice_ptr "data/voicegroups/a6718.bin", 0, sVoicegroup_a5710 - 36 * 12
    voice "data/voicegroups/a6718.bin", 1
    voice_ptr "data/voicegroups/a6718.bin", 2, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a6718.bin", 3, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a6718.bin", 4, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a6718.bin", 5, DirectSoundData_080BA2C0
    voice_ptr "data/voicegroups/a6718.bin", 6, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a6718.bin", 7, DirectSoundData_080B3910
    voice_ptr "data/voicegroups/a6718.bin", 8, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a6718.bin", 9, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a6718.bin", 10, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a6718.bin", 11, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a6718.bin", 12, DirectSoundData_080B8B88
    voice_ptr "data/voicegroups/a6718.bin", 13, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a6718.bin", 14, DirectSoundData_080D2924
    voice_ptr "data/voicegroups/a6718.bin", 15, DirectSoundData_080D3598
    voice_ptr "data/voicegroups/a6718.bin", 16, DirectSoundData_080CACAC
    voice_ptr "data/voicegroups/a6718.bin", 17, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a6718.bin", 18, DirectSoundData_080F4548
    voice_ptr "data/voicegroups/a6718.bin", 19, DirectSoundData_080BA964
    voice_ptr "data/voicegroups/a6718.bin", 20, DirectSoundData_080B8B88
    voice "data/voicegroups/a6718.bin", 21
    voice_ptr "data/voicegroups/a6718.bin", 22, DirectSoundData_080F9A28
    .size sVoicegroup_a6718, . - sVoicegroup_a6718

    .align 2
    .type sVoicegroup_a682c, object
    .global sVoicegroup_a682c
sVoicegroup_a682c:
    voice_ptr "data/voicegroups/a682c.bin", 0, DirectSoundData_08119D40
    voice_ptr "data/voicegroups/a682c.bin", 1, DirectSoundData_0811A384
    voice_ptr "data/voicegroups/a682c.bin", 2, DirectSoundData_0811A4B4
    voice_ptr "data/voicegroups/a682c.bin", 3, DirectSoundData_0811A6B8
    voice_ptr "data/voicegroups/a682c.bin", 4, DirectSoundData_0811AB98
    voice_ptr "data/voicegroups/a682c.bin", 5, DirectSoundData_0811ACB0
    voice_ptr "data/voicegroups/a682c.bin", 6, DirectSoundData_0811ACB0
    voice_ptr "data/voicegroups/a682c.bin", 7, DirectSoundData_0811AE5C
    voice_ptr "data/voicegroups/a682c.bin", 8, DirectSoundData_0811B124
    voice_ptr "data/voicegroups/a682c.bin", 9, DirectSoundData_0811A384
    voice "data/voicegroups/a682c.bin", 10
    voice_ptr "data/voicegroups/a682c.bin", 11, DirectSoundData_0811AB98
    voice_ptr "data/voicegroups/a682c.bin", 12, DirectSoundData_0811B3A4
    voice_ptr "data/voicegroups/a682c.bin", 13, DirectSoundData_0811B760
    voice_ptr "data/voicegroups/a682c.bin", 14, DirectSoundData_0811B8B0
    voice_ptr "data/voicegroups/a682c.bin", 15, DirectSoundData_0811BB74
    voice_ptr "data/voicegroups/a682c.bin", 16, DirectSoundData_0811BF4C
    voice_ptr "data/voicegroups/a682c.bin", 17, DirectSoundData_0811C188
    voice_ptr "data/voicegroups/a682c.bin", 18, DirectSoundData_0811C3E0
    voice_ptr "data/voicegroups/a682c.bin", 19, sWaveData_a8cbc
    voice "data/voicegroups/a682c.bin", 20
    voice_ptr "data/voicegroups/a682c.bin", 21, DirectSoundData_0811C930
    voice_ptr "data/voicegroups/a682c.bin", 22, DirectSoundData_0811C930
    voice_ptr "data/voicegroups/a682c.bin", 23, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a682c.bin", 24, DirectSoundData_0811D098
    voice_ptr "data/voicegroups/a682c.bin", 25, DirectSoundData_0811D098
    voice_ptr "data/voicegroups/a682c.bin", 26, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a682c.bin", 27, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a682c.bin", 28, DirectSoundData_0811EA04
    voice_ptr "data/voicegroups/a682c.bin", 29, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a682c.bin", 30, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a682c.bin", 31, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a682c.bin", 32, DirectSoundData_0811F868
    voice_ptr "data/voicegroups/a682c.bin", 33, DirectSoundData_0811FA88
    voice_ptr "data/voicegroups/a682c.bin", 34, DirectSoundData_0811FE08
    voice_ptr "data/voicegroups/a682c.bin", 35, DirectSoundData_08120188
    voice_ptr "data/voicegroups/a682c.bin", 36, DirectSoundData_08120508
    voice_ptr "data/voicegroups/a682c.bin", 37, DirectSoundData_08120888
    voice_ptr "data/voicegroups/a682c.bin", 38, DirectSoundData_08120C08
    voice_ptr "data/voicegroups/a682c.bin", 39, DirectSoundData_08120F88
    voice_ptr "data/voicegroups/a682c.bin", 40, DirectSoundData_081220C8
    voice_ptr "data/voicegroups/a682c.bin", 41, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a682c.bin", 42, DirectSoundData_08123394
    voice_ptr "data/voicegroups/a682c.bin", 43, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a682c.bin", 44, DirectSoundData_08123CA0
    voice_ptr "data/voicegroups/a682c.bin", 45, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a682c.bin", 46, DirectSoundData_08124188
    voice_ptr "data/voicegroups/a682c.bin", 47, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a682c.bin", 48, DirectSoundData_0812466C
    voice_ptr "data/voicegroups/a682c.bin", 49, DirectSoundData_08124BFC
    voice_ptr "data/voicegroups/a682c.bin", 50, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a682c.bin", 51, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a682c.bin", 52, DirectSoundData_08125B24
    voice_ptr "data/voicegroups/a682c.bin", 53, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a682c.bin", 54, DirectSoundData_08126E38
    voice_ptr "data/voicegroups/a682c.bin", 55, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a682c.bin", 56, DirectSoundData_08127B24
    voice_ptr "data/voicegroups/a682c.bin", 57, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a682c.bin", 58, DirectSoundData_08128C80
    .size sVoicegroup_a682c, . - sVoicegroup_a682c

    .align 2
    .type sVoicegroup_a6af0, object
    .global sVoicegroup_a6af0
sVoicegroup_a6af0:
    voice_ptr "data/voicegroups/a6af0.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a6af0.bin", 1, DirectSoundData_0812A328
    voice_ptr "data/voicegroups/a6af0.bin", 2, DirectSoundData_0812B1C0
    voice_ptr "data/voicegroups/a6af0.bin", 3, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a6af0.bin", 4, DirectSoundData_0811BB74
    voice_ptr "data/voicegroups/a6af0.bin", 5, DirectSoundData_0812B614
    voice_ptr "data/voicegroups/a6af0.bin", 6, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a6af0.bin", 7, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a6af0.bin", 8, DirectSoundData_0812C4F8
    voice_ptr "data/voicegroups/a6af0.bin", 9, DirectSoundData_0812BF0C
    voice "data/voicegroups/a6af0.bin", 10
    voice "data/voicegroups/a6af0.bin", 11
    voice "data/voicegroups/a6af0.bin", 12
    voice_ptr "data/voicegroups/a6af0.bin", 13, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a6af0.bin", 14, DirectSoundData_0812C6D4
    voice_ptr "data/voicegroups/a6af0.bin", 15, DirectSoundData_0812CCA8
    voice_ptr "data/voicegroups/a6af0.bin", 16, DirectSoundData_0812CE14
    voice_ptr "data/voicegroups/a6af0.bin", 17, DirectSoundData_0812D244
    voice_ptr "data/voicegroups/a6af0.bin", 18, DirectSoundData_0812D674
    voice_ptr "data/voicegroups/a6af0.bin", 19, DirectSoundData_0812DAA4
    voice_ptr "data/voicegroups/a6af0.bin", 20, DirectSoundData_0812DE34
    voice_ptr "data/voicegroups/a6af0.bin", 21, DirectSoundData_0812E540
    voice_ptr "data/voicegroups/a6af0.bin", 22, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a6af0.bin", 23, DirectSoundData_0812F11C
    voice "data/voicegroups/a6af0.bin", 24
    voice_ptr "data/voicegroups/a6af0.bin", 25, DirectSoundData_0812F8C4
    voice_ptr "data/voicegroups/a6af0.bin", 26, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a6af0.bin", 27, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a6af0.bin", 28, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a6af0.bin", 29, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a6af0.bin", 30, DirectSoundData_08130750
    voice_ptr "data/voicegroups/a6af0.bin", 31, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a6af0.bin", 32, DirectSoundData_0812E540
    voice_ptr "data/voicegroups/a6af0.bin", 33, DirectSoundData_0812E540
    voice_ptr "data/voicegroups/a6af0.bin", 34, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a6af0.bin", 35, DirectSoundData_0812F11C
    voice_ptr "data/voicegroups/a6af0.bin", 36, DirectSoundData_0812DAA4
    voice_ptr "data/voicegroups/a6af0.bin", 37, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a6af0.bin", 38, DirectSoundData_0812DE34
    voice_ptr "data/voicegroups/a6af0.bin", 39, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a6af0.bin", 40, DirectSoundData_0812E540
    voice_ptr "data/voicegroups/a6af0.bin", 41, DirectSoundData_08131124
    voice_ptr "data/voicegroups/a6af0.bin", 42, DirectSoundData_081314F8
    voice_ptr "data/voicegroups/a6af0.bin", 43, DirectSoundData_081319E8
    voice_ptr "data/voicegroups/a6af0.bin", 44, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a6af0.bin", 45, DirectSoundData_081324F8
    voice_ptr "data/voicegroups/a6af0.bin", 46, DirectSoundData_081346B8
    voice_ptr "data/voicegroups/a6af0.bin", 47, DirectSoundData_08137008
    voice_ptr "data/voicegroups/a6af0.bin", 48, DirectSoundData_08139068
    voice_ptr "data/voicegroups/a6af0.bin", 49, DirectSoundData_0813B7A8
    voice_ptr "data/voicegroups/a6af0.bin", 50, DirectSoundData_0813D1D8
    .size sVoicegroup_a6af0, . - sVoicegroup_a6af0

    .align 2
    .type sVoicegroup_a6d54, object
    .global sVoicegroup_a6d54
sVoicegroup_a6d54:
    voice_ptr "data/voicegroups/a6d54.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a6d54.bin", 1, DirectSoundData_0811F868
    voice_ptr "data/voicegroups/a6d54.bin", 2, DirectSoundData_0811FA88
    voice_ptr "data/voicegroups/a6d54.bin", 3, DirectSoundData_0811FE08
    voice_ptr "data/voicegroups/a6d54.bin", 4, DirectSoundData_08120188
    voice_ptr "data/voicegroups/a6d54.bin", 5, DirectSoundData_08120508
    voice_ptr "data/voicegroups/a6d54.bin", 6, DirectSoundData_0813F868
    voice_ptr "data/voicegroups/a6d54.bin", 7, DirectSoundData_0813FA88
    voice_ptr "data/voicegroups/a6d54.bin", 8, DirectSoundData_0813FE08
    voice_ptr "data/voicegroups/a6d54.bin", 9, DirectSoundData_08120888
    voice_ptr "data/voicegroups/a6d54.bin", 10, DirectSoundData_08120C08
    voice_ptr "data/voicegroups/a6d54.bin", 11, DirectSoundData_0811F868
    voice_ptr "data/voicegroups/a6d54.bin", 12, DirectSoundData_0811FA88
    voice_ptr "data/voicegroups/a6d54.bin", 13, DirectSoundData_0811FE08
    voice_ptr "data/voicegroups/a6d54.bin", 14, DirectSoundData_08120188
    voice_ptr "data/voicegroups/a6d54.bin", 15, DirectSoundData_08120508
    voice_ptr "data/voicegroups/a6d54.bin", 16, DirectSoundData_08120888
    voice_ptr "data/voicegroups/a6d54.bin", 17, DirectSoundData_08120C08
    voice_ptr "data/voicegroups/a6d54.bin", 18, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a6d54.bin", 19, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a6d54.bin", 20, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a6d54.bin", 21, DirectSoundData_081409F8
    voice "data/voicegroups/a6d54.bin", 22
    voice_ptr "data/voicegroups/a6d54.bin", 23, DirectSoundData_08140CC8
    voice "data/voicegroups/a6d54.bin", 24
    voice "data/voicegroups/a6d54.bin", 25
    voice "data/voicegroups/a6d54.bin", 26
    voice "data/voicegroups/a6d54.bin", 27
    voice "data/voicegroups/a6d54.bin", 28
    voice "data/voicegroups/a6d54.bin", 29
    voice "data/voicegroups/a6d54.bin", 30
    voice_ptr "data/voicegroups/a6d54.bin", 31, DirectSoundData_08141238
    voice "data/voicegroups/a6d54.bin", 32
    voice "data/voicegroups/a6d54.bin", 33
    voice_ptr "data/voicegroups/a6d54.bin", 34, DirectSoundData_081415B8
    voice_ptr "data/voicegroups/a6d54.bin", 35, DirectSoundData_08141A98
    voice_ptr "data/voicegroups/a6d54.bin", 36, DirectSoundData_08142A78
    voice_ptr "data/voicegroups/a6d54.bin", 37, DirectSoundData_08142DF8
    voice_ptr "data/voicegroups/a6d54.bin", 38, DirectSoundData_08143C28
    voice "data/voicegroups/a6d54.bin", 39
    voice_ptr "data/voicegroups/a6d54.bin", 40, DirectSoundData_08143FCC
    voice_ptr "data/voicegroups/a6d54.bin", 41, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a6d54.bin", 42, DirectSoundData_0811C3E0
    voice_ptr "data/voicegroups/a6d54.bin", 43, DirectSoundData_0812B614
    voice_ptr "data/voicegroups/a6d54.bin", 44, DirectSoundData_08141238
    voice_ptr "data/voicegroups/a6d54.bin", 45, DirectSoundData_0811A6B8
    voice "data/voicegroups/a6d54.bin", 46
    voice_ptr "data/voicegroups/a6d54.bin", 47, DirectSoundData_0812F8C4
    voice_ptr "data/voicegroups/a6d54.bin", 48, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a6d54.bin", 49, DirectSoundData_081441EC
    voice_ptr "data/voicegroups/a6d54.bin", 50, DirectSoundData_0811AB98
    voice_ptr "data/voicegroups/a6d54.bin", 51, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a6d54.bin", 52, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a6d54.bin", 53, DirectSoundData_0814439C
    voice "data/voicegroups/a6d54.bin", 54
    voice_ptr "data/voicegroups/a6d54.bin", 55, DirectSoundData_081448B0
    voice_ptr "data/voicegroups/a6d54.bin", 56, DirectSoundData_0811F868
    voice_ptr "data/voicegroups/a6d54.bin", 57, DirectSoundData_0811FA88
    voice_ptr "data/voicegroups/a6d54.bin", 58, DirectSoundData_0811FE08
    voice_ptr "data/voicegroups/a6d54.bin", 59, DirectSoundData_08120188
    voice_ptr "data/voicegroups/a6d54.bin", 60, DirectSoundData_08120508
    voice_ptr "data/voicegroups/a6d54.bin", 61, DirectSoundData_081220C8
    voice_ptr "data/voicegroups/a6d54.bin", 62, DirectSoundData_08145230
    voice_ptr "data/voicegroups/a6d54.bin", 63, DirectSoundData_081455D4
    voice_ptr "data/voicegroups/a6d54.bin", 64, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a6d54.bin", 65, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a6d54.bin", 66, DirectSoundData_08130750
    voice "data/voicegroups/a6d54.bin", 67
    voice_ptr "data/voicegroups/a6d54.bin", 68, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a6d54.bin", 69, DirectSoundData_0814439C
    voice_ptr "data/voicegroups/a6d54.bin", 70, DirectSoundData_08123CA0
    voice_ptr "data/voicegroups/a6d54.bin", 71, DirectSoundData_0814439C
    voice_ptr "data/voicegroups/a6d54.bin", 72, DirectSoundData_0812E970
    voice "data/voicegroups/a6d54.bin", 73
    voice_ptr "data/voicegroups/a6d54.bin", 74, DirectSoundData_081459B0
    voice_ptr "data/voicegroups/a6d54.bin", 75, DirectSoundData_0811BB74
    voice_ptr "data/voicegroups/a6d54.bin", 76, DirectSoundData_08145DF0
    voice_ptr "data/voicegroups/a6d54.bin", 77, DirectSoundData_08145F50
    voice_ptr "data/voicegroups/a6d54.bin", 78, DirectSoundData_08130750
    voice_ptr "data/voicegroups/a6d54.bin", 79, DirectSoundData_08146D20
    voice_ptr "data/voicegroups/a6d54.bin", 80, DirectSoundData_08140188
    voice "data/voicegroups/a6d54.bin", 81
    voice_ptr "data/voicegroups/a6d54.bin", 82, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a6d54.bin", 83, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a6d54.bin", 84, DirectSoundData_081409F8
    voice "data/voicegroups/a6d54.bin", 85
    voice_ptr "data/voicegroups/a6d54.bin", 86, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a6d54.bin", 87, DirectSoundData_08147DB0
    voice_ptr "data/voicegroups/a6d54.bin", 88, DirectSoundData_081220C8
    voice_ptr "data/voicegroups/a6d54.bin", 89, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a6d54.bin", 90, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a6d54.bin", 91, DirectSoundData_08148B4C
    voice_ptr "data/voicegroups/a6d54.bin", 92, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a6d54.bin", 93, DirectSoundData_0814A838
    voice_ptr "data/voicegroups/a6d54.bin", 94, DirectSoundData_0814A838
    voice_ptr "data/voicegroups/a6d54.bin", 95, DirectSoundData_0814B818
    voice_ptr "data/voicegroups/a6d54.bin", 96, DirectSoundData_0814C7F8
    voice_ptr "data/voicegroups/a6d54.bin", 97, DirectSoundData_081250B0
    .size sVoicegroup_a6d54, . - sVoicegroup_a6d54

    .align 2
    .type sVoicegroup_a71ec, object
    .global sVoicegroup_a71ec
sVoicegroup_a71ec:
    voice_ptr "data/voicegroups/a71ec.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a71ec.bin", 1, DirectSoundData_0814D468
    voice_ptr "data/voicegroups/a71ec.bin", 2, DirectSoundData_0814D868
    voice_ptr "data/voicegroups/a71ec.bin", 3, DirectSoundData_0814D868
    voice_ptr "data/voicegroups/a71ec.bin", 4, DirectSoundData_0814DEA8
    voice_ptr "data/voicegroups/a71ec.bin", 5, DirectSoundData_0814E270
    voice_ptr "data/voicegroups/a71ec.bin", 6, DirectSoundData_0814DEA8
    voice_ptr "data/voicegroups/a71ec.bin", 7, DirectSoundData_0814E890
    voice_ptr "data/voicegroups/a71ec.bin", 8, DirectSoundData_0811BB74
    voice_ptr "data/voicegroups/a71ec.bin", 9, DirectSoundData_0814EF74
    voice_ptr "data/voicegroups/a71ec.bin", 10, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a71ec.bin", 11, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a71ec.bin", 12, DirectSoundData_081441EC
    voice_ptr "data/voicegroups/a71ec.bin", 13, DirectSoundData_0814F4D4
    voice_ptr "data/voicegroups/a71ec.bin", 14, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a71ec.bin", 15, DirectSoundData_0812B614
    voice_ptr "data/voicegroups/a71ec.bin", 16, DirectSoundData_0812F8C4
    voice_ptr "data/voicegroups/a71ec.bin", 17, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a71ec.bin", 18, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a71ec.bin", 19, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a71ec.bin", 20, DirectSoundData_0814F72C
    voice_ptr "data/voicegroups/a71ec.bin", 21, DirectSoundData_0811AB98
    voice_ptr "data/voicegroups/a71ec.bin", 22, DirectSoundData_0814F958
    voice_ptr "data/voicegroups/a71ec.bin", 23, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a71ec.bin", 24, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a71ec.bin", 25, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a71ec.bin", 26, sWaveData_a8cbc
    voice_ptr "data/voicegroups/a71ec.bin", 27, DirectSoundData_0814F958
    voice_ptr "data/voicegroups/a71ec.bin", 28, DirectSoundData_0812F8C4
    voice_ptr "data/voicegroups/a71ec.bin", 29, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a71ec.bin", 30, DirectSoundData_0814FD38
    voice_ptr "data/voicegroups/a71ec.bin", 31, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a71ec.bin", 32, DirectSoundData_081502D4
    voice_ptr "data/voicegroups/a71ec.bin", 33, DirectSoundData_081506AC
    voice_ptr "data/voicegroups/a71ec.bin", 34, DirectSoundData_081459B0
    voice_ptr "data/voicegroups/a71ec.bin", 35, DirectSoundData_08150A2C
    voice_ptr "data/voicegroups/a71ec.bin", 36, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a71ec.bin", 37, DirectSoundData_081455D4
    voice_ptr "data/voicegroups/a71ec.bin", 38, DirectSoundData_08150CFC
    voice_ptr "data/voicegroups/a71ec.bin", 39, DirectSoundData_0812B1C0
    voice_ptr "data/voicegroups/a71ec.bin", 40, DirectSoundData_081510BC
    voice_ptr "data/voicegroups/a71ec.bin", 41, DirectSoundData_0815129C
    voice "data/voicegroups/a71ec.bin", 42
    voice_ptr "data/voicegroups/a71ec.bin", 43, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a71ec.bin", 44, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a71ec.bin", 45, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a71ec.bin", 46, DirectSoundData_081409F8
    voice "data/voicegroups/a71ec.bin", 47
    voice_ptr "data/voicegroups/a71ec.bin", 48, DirectSoundData_081516CC
    voice_ptr "data/voicegroups/a71ec.bin", 49, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a71ec.bin", 50, DirectSoundData_081520D4
    voice_ptr "data/voicegroups/a71ec.bin", 51, DirectSoundData_081523A4
    voice_ptr "data/voicegroups/a71ec.bin", 52, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a71ec.bin", 53, DirectSoundData_08128C80
    voice_ptr "data/voicegroups/a71ec.bin", 54, DirectSoundData_08152FB0
    voice_ptr "data/voicegroups/a71ec.bin", 55, DirectSoundData_0814439C
    voice_ptr "data/voicegroups/a71ec.bin", 56, DirectSoundData_08153B50
    voice_ptr "data/voicegroups/a71ec.bin", 57, DirectSoundData_08153CC0
    voice_ptr "data/voicegroups/a71ec.bin", 58, DirectSoundData_08154528
    voice_ptr "data/voicegroups/a71ec.bin", 59, DirectSoundData_08155038
    voice_ptr "data/voicegroups/a71ec.bin", 60, DirectSoundData_08120F88
    .size sVoicegroup_a71ec, . - sVoicegroup_a71ec

    .align 2
    .type sVoicegroup_a74c8, object
    .global sVoicegroup_a74c8
sVoicegroup_a74c8:
    voice_ptr "data/voicegroups/a74c8.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a74c8.bin", 1, DirectSoundData_08155B48
    voice_ptr "data/voicegroups/a74c8.bin", 2, DirectSoundData_08155E18
    voice_ptr "data/voicegroups/a74c8.bin", 3, DirectSoundData_081560E8
    voice_ptr "data/voicegroups/a74c8.bin", 4, DirectSoundData_081563B8
    voice_ptr "data/voicegroups/a74c8.bin", 5, DirectSoundData_08155B48
    voice_ptr "data/voicegroups/a74c8.bin", 6, DirectSoundData_08155E18
    voice_ptr "data/voicegroups/a74c8.bin", 7, DirectSoundData_081563B8
    voice_ptr "data/voicegroups/a74c8.bin", 8, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a74c8.bin", 9, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a74c8.bin", 10, DirectSoundData_08156688
    voice_ptr "data/voicegroups/a74c8.bin", 11, DirectSoundData_08157928
    voice_ptr "data/voicegroups/a74c8.bin", 12, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a74c8.bin", 13, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a74c8.bin", 14, DirectSoundData_0812E540
    voice_ptr "data/voicegroups/a74c8.bin", 15, DirectSoundData_0812D244
    voice_ptr "data/voicegroups/a74c8.bin", 16, DirectSoundData_0812D674
    voice_ptr "data/voicegroups/a74c8.bin", 17, DirectSoundData_0812D674
    voice_ptr "data/voicegroups/a74c8.bin", 18, DirectSoundData_08157BF8
    voice "data/voicegroups/a74c8.bin", 19
    voice_ptr "data/voicegroups/a74c8.bin", 20, DirectSoundData_08158790
    voice "data/voicegroups/a74c8.bin", 21
    voice_ptr "data/voicegroups/a74c8.bin", 22, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a74c8.bin", 23, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a74c8.bin", 24, DirectSoundData_08142DF8
    voice "data/voicegroups/a74c8.bin", 25
    voice_ptr "data/voicegroups/a74c8.bin", 26, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a74c8.bin", 27, DirectSoundData_0811BB74
    voice_ptr "data/voicegroups/a74c8.bin", 28, DirectSoundData_0814439C
    voice_ptr "data/voicegroups/a74c8.bin", 29, DirectSoundData_0812CCA8
    voice_ptr "data/voicegroups/a74c8.bin", 30, DirectSoundData_0812C6D4
    voice_ptr "data/voicegroups/a74c8.bin", 31, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a74c8.bin", 32, DirectSoundData_081590A4
    .size sVoicegroup_a74c8, . - sVoicegroup_a74c8

    .align 2
    .type sVoicegroup_a7654, object
    .global sVoicegroup_a7654
sVoicegroup_a7654:
    voice_ptr "data/voicegroups/a7654.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7654.bin", 1, DirectSoundData_0815A974
    voice_ptr "data/voicegroups/a7654.bin", 2, DirectSoundData_0815A974
    voice_ptr "data/voicegroups/a7654.bin", 3, DirectSoundData_0812A328
    voice_ptr "data/voicegroups/a7654.bin", 4, DirectSoundData_0812B1C0
    voice_ptr "data/voicegroups/a7654.bin", 5, DirectSoundData_0811AE5C
    voice_ptr "data/voicegroups/a7654.bin", 6, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7654.bin", 7, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a7654.bin", 8, DirectSoundData_0812BF0C
    voice "data/voicegroups/a7654.bin", 9
    voice_ptr "data/voicegroups/a7654.bin", 10, DirectSoundData_0812B614
    voice_ptr "data/voicegroups/a7654.bin", 11, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7654.bin", 12, DirectSoundData_0812FDDC
    voice_ptr "data/voicegroups/a7654.bin", 13, DirectSoundData_0815B2B4
    voice_ptr "data/voicegroups/a7654.bin", 14, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a7654.bin", 15, sWaveData_a8cbc
    voice_ptr "data/voicegroups/a7654.bin", 16, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7654.bin", 17, DirectSoundData_0812C4F8
    voice_ptr "data/voicegroups/a7654.bin", 18, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7654.bin", 19, DirectSoundData_0815B844
    voice_ptr "data/voicegroups/a7654.bin", 20, DirectSoundData_0815D064
    .size sVoicegroup_a7654, . - sVoicegroup_a7654

    .align 2
    .type sVoicegroup_a7750, object
    .global sVoicegroup_a7750
sVoicegroup_a7750:
    voice_ptr "data/voicegroups/a7750.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7750.bin", 1, DirectSoundData_080D5E5C
    voice_ptr "data/voicegroups/a7750.bin", 2, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7750.bin", 3, DirectSoundData_080D5E5C
    voice_ptr "data/voicegroups/a7750.bin", 4, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7750.bin", 5, DirectSoundData_08128C80
    .size sVoicegroup_a7750, . - sVoicegroup_a7750

    .align 2
    .type sVoicegroup_a7798, object
    .global sVoicegroup_a7798
sVoicegroup_a7798:
    voice_ptr "data/voicegroups/a7798.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7798.bin", 1, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7798.bin", 2, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a7798.bin", 3, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a7798.bin", 4, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a7798.bin", 5, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7798.bin", 6, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7798.bin", 7, DirectSoundData_081409F8
    voice "data/voicegroups/a7798.bin", 8
    voice "data/voicegroups/a7798.bin", 9
    voice_ptr "data/voicegroups/a7798.bin", 10, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7798.bin", 11, DirectSoundData_08130750
    voice_ptr "data/voicegroups/a7798.bin", 12, DirectSoundData_0815E514
    voice_ptr "data/voicegroups/a7798.bin", 13, DirectSoundData_0815F5A4
    voice_ptr "data/voicegroups/a7798.bin", 14, DirectSoundData_0815A974
    voice_ptr "data/voicegroups/a7798.bin", 15, DirectSoundData_081441EC
    voice_ptr "data/voicegroups/a7798.bin", 16, DirectSoundData_0814F4D4
    voice_ptr "data/voicegroups/a7798.bin", 17, DirectSoundData_08128C80
    voice_ptr "data/voicegroups/a7798.bin", 18, DirectSoundData_0815FD84
    voice_ptr "data/voicegroups/a7798.bin", 19, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7798.bin", 20, DirectSoundData_081459B0
    voice_ptr "data/voicegroups/a7798.bin", 21, DirectSoundData_08150A2C
    voice_ptr "data/voicegroups/a7798.bin", 22, DirectSoundData_0814E890
    voice_ptr "data/voicegroups/a7798.bin", 23, DirectSoundData_08142DF8
    voice_ptr "data/voicegroups/a7798.bin", 24, DirectSoundData_0814D468
    voice_ptr "data/voicegroups/a7798.bin", 25, DirectSoundData_0815FFA4
    voice_ptr "data/voicegroups/a7798.bin", 26, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a7798.bin", 27, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a7798.bin", 28, DirectSoundData_08145F50
    voice_ptr "data/voicegroups/a7798.bin", 29, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a7798.bin", 30, DirectSoundData_0811F868
    voice_ptr "data/voicegroups/a7798.bin", 31, DirectSoundData_0811FA88
    voice_ptr "data/voicegroups/a7798.bin", 32, DirectSoundData_0811FE08
    voice_ptr "data/voicegroups/a7798.bin", 33, DirectSoundData_08120188
    voice_ptr "data/voicegroups/a7798.bin", 34, DirectSoundData_08120508
    voice_ptr "data/voicegroups/a7798.bin", 35, DirectSoundData_0813F868
    voice_ptr "data/voicegroups/a7798.bin", 36, DirectSoundData_0813FA88
    voice_ptr "data/voicegroups/a7798.bin", 37, DirectSoundData_0813FE08
    voice_ptr "data/voicegroups/a7798.bin", 38, DirectSoundData_08120888
    voice_ptr "data/voicegroups/a7798.bin", 39, DirectSoundData_08120C08
    voice_ptr "data/voicegroups/a7798.bin", 40, DirectSoundData_0815E514
    voice "data/voicegroups/a7798.bin", 41
    voice_ptr "data/voicegroups/a7798.bin", 42, DirectSoundData_08160730
    voice "data/voicegroups/a7798.bin", 43
    voice "data/voicegroups/a7798.bin", 44
    voice_ptr "data/voicegroups/a7798.bin", 45, DirectSoundData_08161A48
    voice_ptr "data/voicegroups/a7798.bin", 46, DirectSoundData_08120F88
    voice_ptr "data/voicegroups/a7798.bin", 47, DirectSoundData_0811C3E0
    voice_ptr "data/voicegroups/a7798.bin", 48, DirectSoundData_08162228
    voice_ptr "data/voicegroups/a7798.bin", 49, DirectSoundData_08130750
    voice_ptr "data/voicegroups/a7798.bin", 50, DirectSoundData_081644C8
    voice_ptr "data/voicegroups/a7798.bin", 51, DirectSoundData_08150CFC
    voice_ptr "data/voicegroups/a7798.bin", 52, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7798.bin", 53, DirectSoundData_0811EE04
    voice_ptr "data/voicegroups/a7798.bin", 54, DirectSoundData_0811D960
    voice_ptr "data/voicegroups/a7798.bin", 55, DirectSoundData_081502D4
    voice_ptr "data/voicegroups/a7798.bin", 56, DirectSoundData_0816602C
    voice_ptr "data/voicegroups/a7798.bin", 57, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a7798.bin", 58, DirectSoundData_08167BBC
    voice_ptr "data/voicegroups/a7798.bin", 59, DirectSoundData_0815F5A4
    voice_ptr "data/voicegroups/a7798.bin", 60, DirectSoundData_0815D064
    voice_ptr "data/voicegroups/a7798.bin", 61, DirectSoundData_08168D90
    voice_ptr "data/voicegroups/a7798.bin", 62, DirectSoundData_0816ABE0
    voice_ptr "data/voicegroups/a7798.bin", 63, DirectSoundData_0816C350
    voice_ptr "data/voicegroups/a7798.bin", 64, DirectSoundData_0816E250
    .size sVoicegroup_a7798, . - sVoicegroup_a7798

    .align 2
    .type sVoicegroup_a7aa4, object
    .global sVoicegroup_a7aa4
sVoicegroup_a7aa4:
    voice_ptr "data/voicegroups/a7aa4.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7aa4.bin", 1, DirectSoundData_0815E514
    voice_ptr "data/voicegroups/a7aa4.bin", 2, DirectSoundData_08161A48
    voice_ptr "data/voicegroups/a7aa4.bin", 3, DirectSoundData_0815FFA4
    voice_ptr "data/voicegroups/a7aa4.bin", 4, DirectSoundData_0814EF74
    voice_ptr "data/voicegroups/a7aa4.bin", 5, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7aa4.bin", 6, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a7aa4.bin", 7, DirectSoundData_0811AE5C
    voice_ptr "data/voicegroups/a7aa4.bin", 8, DirectSoundData_0812B1C0
    voice_ptr "data/voicegroups/a7aa4.bin", 9, DirectSoundData_0812A328
    voice "data/voicegroups/a7aa4.bin", 10
    voice_ptr "data/voicegroups/a7aa4.bin", 11, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7aa4.bin", 12, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a7aa4.bin", 13, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7aa4.bin", 14, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7aa4.bin", 15, DirectSoundData_081409F8
    voice "data/voicegroups/a7aa4.bin", 16
    voice_ptr "data/voicegroups/a7aa4.bin", 17, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7aa4.bin", 18, DirectSoundData_0812BF0C
    voice "data/voicegroups/a7aa4.bin", 19
    voice_ptr "data/voicegroups/a7aa4.bin", 20, DirectSoundData_08130750
    voice "data/voicegroups/a7aa4.bin", 21
    voice_ptr "data/voicegroups/a7aa4.bin", 22, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7aa4.bin", 23, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7aa4.bin", 24, DirectSoundData_081409F8
    voice "data/voicegroups/a7aa4.bin", 25
    voice "data/voicegroups/a7aa4.bin", 26
    voice "data/voicegroups/a7aa4.bin", 27
    voice_ptr "data/voicegroups/a7aa4.bin", 28, DirectSoundData_0816F428
    voice_ptr "data/voicegroups/a7aa4.bin", 29, DirectSoundData_081706C8
    voice "data/voicegroups/a7aa4.bin", 30
    voice "data/voicegroups/a7aa4.bin", 31
    voice "data/voicegroups/a7aa4.bin", 32
    voice "data/voicegroups/a7aa4.bin", 33
    voice "data/voicegroups/a7aa4.bin", 34
    voice "data/voicegroups/a7aa4.bin", 35
    voice "data/voicegroups/a7aa4.bin", 36
    voice "data/voicegroups/a7aa4.bin", 37
    voice "data/voicegroups/a7aa4.bin", 38
    voice "data/voicegroups/a7aa4.bin", 39
    voice "data/voicegroups/a7aa4.bin", 40
    voice "data/voicegroups/a7aa4.bin", 41
    voice "data/voicegroups/a7aa4.bin", 42
    voice "data/voicegroups/a7aa4.bin", 43
    voice "data/voicegroups/a7aa4.bin", 44
    voice "data/voicegroups/a7aa4.bin", 45
    voice "data/voicegroups/a7aa4.bin", 46
    voice "data/voicegroups/a7aa4.bin", 47
    voice "data/voicegroups/a7aa4.bin", 48
    voice "data/voicegroups/a7aa4.bin", 49
    voice_ptr "data/voicegroups/a7aa4.bin", 50, DirectSoundData_081721A8
    voice_ptr "data/voicegroups/a7aa4.bin", 51, DirectSoundData_081225A8
    .size sVoicegroup_a7aa4, . - sVoicegroup_a7aa4

    .align 2
    .type sVoicegroup_a7d14, object
    .global sVoicegroup_a7d14
sVoicegroup_a7d14:
    voice_ptr "data/voicegroups/a7d14.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7d14.bin", 1, DirectSoundData_08147DB0
    voice_ptr "data/voicegroups/a7d14.bin", 2, DirectSoundData_08175F98
    voice_ptr "data/voicegroups/a7d14.bin", 3, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a7d14.bin", 4, DirectSoundData_08176DB8
    voice_ptr "data/voicegroups/a7d14.bin", 5, DirectSoundData_08177558
    voice_ptr "data/voicegroups/a7d14.bin", 6, DirectSoundData_08145230
    voice_ptr "data/voicegroups/a7d14.bin", 7, DirectSoundData_08177A38
    voice_ptr "data/voicegroups/a7d14.bin", 8, DirectSoundData_08145230
    voice_ptr "data/voicegroups/a7d14.bin", 9, DirectSoundData_08145DF0
    voice_ptr "data/voicegroups/a7d14.bin", 10, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a7d14.bin", 11, DirectSoundData_081783A8
    voice_ptr "data/voicegroups/a7d14.bin", 12, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7d14.bin", 13, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a7d14.bin", 14, DirectSoundData_0812BF0C
    voice "data/voicegroups/a7d14.bin", 15
    voice "data/voicegroups/a7d14.bin", 16
    voice_ptr "data/voicegroups/a7d14.bin", 17, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7d14.bin", 18, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7d14.bin", 19, DirectSoundData_081409F8
    voice_ptr "data/voicegroups/a7d14.bin", 20, DirectSoundData_081220C8
    .size sVoicegroup_a7d14, . - sVoicegroup_a7d14

    .align 2
    .type sVoicegroup_a7e10, object
    .global sVoicegroup_a7e10
sVoicegroup_a7e10:
    voice_ptr "data/voicegroups/a7e10.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7e10.bin", 1, DirectSoundData_081721A8
    voice_ptr "data/voicegroups/a7e10.bin", 2, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a7e10.bin", 3, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a7e10.bin", 4, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a7e10.bin", 5, DirectSoundData_0811D098
    voice_ptr "data/voicegroups/a7e10.bin", 6, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7e10.bin", 7, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a7e10.bin", 8, DirectSoundData_0811D098
    voice_ptr "data/voicegroups/a7e10.bin", 9, DirectSoundData_08178D10
    voice_ptr "data/voicegroups/a7e10.bin", 10, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7e10.bin", 11, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7e10.bin", 12, DirectSoundData_0812BF0C
    voice "data/voicegroups/a7e10.bin", 13
    voice "data/voicegroups/a7e10.bin", 14
    voice_ptr "data/voicegroups/a7e10.bin", 15, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7e10.bin", 16, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7e10.bin", 17, DirectSoundData_081409F8
    voice "data/voicegroups/a7e10.bin", 18
    voice_ptr "data/voicegroups/a7e10.bin", 19, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7e10.bin", 20, DirectSoundData_0815F5A4
    voice_ptr "data/voicegroups/a7e10.bin", 21, DirectSoundData_08153CC0
    voice_ptr "data/voicegroups/a7e10.bin", 22, DirectSoundData_081225A8
    .size sVoicegroup_a7e10, . - sVoicegroup_a7e10

    .align 2
    .type sVoicegroup_a7f24, object
    .global sVoicegroup_a7f24
sVoicegroup_a7f24:
    voice_ptr "data/voicegroups/a7f24.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a7f24.bin", 1, DirectSoundData_08145230
    voice "data/voicegroups/a7f24.bin", 2
    voice_ptr "data/voicegroups/a7f24.bin", 3, DirectSoundData_08179738
    voice_ptr "data/voicegroups/a7f24.bin", 4, DirectSoundData_08176DB8
    voice_ptr "data/voicegroups/a7f24.bin", 5, DirectSoundData_08177558
    voice_ptr "data/voicegroups/a7f24.bin", 6, DirectSoundData_0812DAA4
    voice_ptr "data/voicegroups/a7f24.bin", 7, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7f24.bin", 8, DirectSoundData_0812C6D4
    voice_ptr "data/voicegroups/a7f24.bin", 9, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a7f24.bin", 10, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a7f24.bin", 11, DirectSoundData_081409F8
    voice "data/voicegroups/a7f24.bin", 12
    voice_ptr "data/voicegroups/a7f24.bin", 13, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a7f24.bin", 14, DirectSoundData_081225A8
    voice_ptr "data/voicegroups/a7f24.bin", 15, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a7f24.bin", 16, DirectSoundData_08146D20
    voice_ptr "data/voicegroups/a7f24.bin", 17, DirectSoundData_08140188
    voice "data/voicegroups/a7f24.bin", 18
    .size sVoicegroup_a7f24, . - sVoicegroup_a7f24

    .align 2
    .type sVoicegroup_a8008, object
    .global sVoicegroup_a8008
sVoicegroup_a8008:
    voice_ptr "data/voicegroups/a8008.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a8008.bin", 1, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a8008.bin", 2, DirectSoundData_0817A198
    voice_ptr "data/voicegroups/a8008.bin", 3, DirectSoundData_0817B310
    voice_ptr "data/voicegroups/a8008.bin", 4, DirectSoundData_0817B310
    voice_ptr "data/voicegroups/a8008.bin", 5, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a8008.bin", 6, DirectSoundData_0817DE70
    voice_ptr "data/voicegroups/a8008.bin", 7, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a8008.bin", 8, DirectSoundData_081448B0
    voice_ptr "data/voicegroups/a8008.bin", 9, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a8008.bin", 10, DirectSoundData_0817EFB0
    .size sVoicegroup_a8008, . - sVoicegroup_a8008

    .align 2
    .type sVoicegroup_a808c, object
    .global sVoicegroup_a808c
sVoicegroup_a808c:
    voice_ptr "data/voicegroups/a808c.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a808c.bin", 1, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a808c.bin", 2, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a808c.bin", 3, DirectSoundData_0812BF0C
    voice_ptr "data/voicegroups/a808c.bin", 4, DirectSoundData_08140188
    voice_ptr "data/voicegroups/a808c.bin", 5, DirectSoundData_08140458
    voice_ptr "data/voicegroups/a808c.bin", 6, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a808c.bin", 7, DirectSoundData_081409F8
    voice "data/voicegroups/a808c.bin", 8
    voice "data/voicegroups/a808c.bin", 9
    voice "data/voicegroups/a808c.bin", 10
    voice "data/voicegroups/a808c.bin", 11
    voice "data/voicegroups/a808c.bin", 12
    voice "data/voicegroups/a808c.bin", 13
    voice "data/voicegroups/a808c.bin", 14
    voice_ptr "data/voicegroups/a808c.bin", 15, DirectSoundData_0814439C
    voice_ptr "data/voicegroups/a808c.bin", 16, DirectSoundData_08180460
    voice_ptr "data/voicegroups/a808c.bin", 17, DirectSoundData_08180460
    voice_ptr "data/voicegroups/a808c.bin", 18, DirectSoundData_081830F8
    voice_ptr "data/voicegroups/a808c.bin", 19, DirectSoundData_08186F98
    voice_ptr "data/voicegroups/a808c.bin", 20, DirectSoundData_081220C8
    voice_ptr "data/voicegroups/a808c.bin", 21, DirectSoundData_0815F5A4
    voice_ptr "data/voicegroups/a808c.bin", 22, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a808c.bin", 23, DirectSoundData_08126E38
    voice_ptr "data/voicegroups/a808c.bin", 24, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a808c.bin", 25, DirectSoundData_08187B14
    voice_ptr "data/voicegroups/a808c.bin", 26, DirectSoundData_0816602C
    voice_ptr "data/voicegroups/a808c.bin", 27, DirectSoundData_0814A838
    voice_ptr "data/voicegroups/a808c.bin", 28, DirectSoundData_0814A838
    .size sVoicegroup_a808c, . - sVoicegroup_a808c

    .align 2
    .type sVoicegroup_a81e8, object
    .global sVoicegroup_a81e8
sVoicegroup_a81e8:
    voice_ptr "data/voicegroups/a81e8.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a81e8.bin", 1, DirectSoundData_08140CC8
    voice_ptr "data/voicegroups/a81e8.bin", 2, DirectSoundData_08180460
    voice_ptr "data/voicegroups/a81e8.bin", 3, DirectSoundData_08180460
    voice_ptr "data/voicegroups/a81e8.bin", 4, DirectSoundData_08188BD0
    voice_ptr "data/voicegroups/a81e8.bin", 5, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a81e8.bin", 6, DirectSoundData_0812E970
    voice_ptr "data/voicegroups/a81e8.bin", 7, DirectSoundData_08125B24
    voice_ptr "data/voicegroups/a81e8.bin", 8, DirectSoundData_08157BF8
    voice_ptr "data/voicegroups/a81e8.bin", 9, DirectSoundData_08130750
    voice "data/voicegroups/a81e8.bin", 10
    .size sVoicegroup_a81e8, . - sVoicegroup_a81e8

    .align 2
    .type sVoicegroup_a826c, object
    .global sVoicegroup_a826c
sVoicegroup_a826c:
    voice_ptr "data/voicegroups/a826c.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a826c.bin", 1, DirectSoundData_0811F228
    voice_ptr "data/voicegroups/a826c.bin", 2, DirectSoundData_08125B24
    voice_ptr "data/voicegroups/a826c.bin", 3, DirectSoundData_081830F8
    voice_ptr "data/voicegroups/a826c.bin", 4, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a826c.bin", 5, DirectSoundData_08128634
    voice_ptr "data/voicegroups/a826c.bin", 6, DirectSoundData_0811E1BC
    voice_ptr "data/voicegroups/a826c.bin", 7, DirectSoundData_081899A0
    voice_ptr "data/voicegroups/a826c.bin", 8, DirectSoundData_0817EFB0
    voice_ptr "data/voicegroups/a826c.bin", 9, DirectSoundData_0818B530
    voice_ptr "data/voicegroups/a826c.bin", 10, DirectSoundData_08145F50
    .size sVoicegroup_a826c, . - sVoicegroup_a826c

    .align 2
    .type sVoicegroup_a82f0, object
    .global sVoicegroup_a82f0
sVoicegroup_a82f0:
    voice_ptr "data/voicegroups/a82f0.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a82f0.bin", 1, DirectSoundData_08157BF8
    voice_ptr "data/voicegroups/a82f0.bin", 2, DirectSoundData_08130750
    voice "data/voicegroups/a82f0.bin", 3
    voice "data/voicegroups/a82f0.bin", 4
    voice_ptr "data/voicegroups/a82f0.bin", 5, DirectSoundData_08140728
    voice_ptr "data/voicegroups/a82f0.bin", 6, DirectSoundData_0811CBA8
    voice_ptr "data/voicegroups/a82f0.bin", 7, DirectSoundData_08130750
    voice_ptr "data/voicegroups/a82f0.bin", 8, DirectSoundData_0811A6B8
    voice "data/voicegroups/a82f0.bin", 9
    voice_ptr "data/voicegroups/a82f0.bin", 10, DirectSoundData_0818C930
    voice_ptr "data/voicegroups/a82f0.bin", 11, DirectSoundData_08186F98
    voice_ptr "data/voicegroups/a82f0.bin", 12, DirectSoundData_08145230
    .size sVoicegroup_a82f0, . - sVoicegroup_a82f0

    .align 2
    .type sVoicegroup_a838c, object
    .global sVoicegroup_a838c
sVoicegroup_a838c:
    voice_ptr "data/voicegroups/a838c.bin", 0, DirectSoundData_08128D40
    voice_ptr "data/voicegroups/a838c.bin", 1, DirectSoundData_0814C7F8
    voice_ptr "data/voicegroups/a838c.bin", 2, DirectSoundData_0818D9C0
    voice "data/voicegroups/a838c.bin", 3
    voice_ptr "data/voicegroups/a838c.bin", 4, DirectSoundData_08167BBC
    voice_ptr "data/voicegroups/a838c.bin", 5, DirectSoundData_08126574
    voice_ptr "data/voicegroups/a838c.bin", 6, DirectSoundData_08126E38
    voice_ptr "data/voicegroups/a838c.bin", 7, DirectSoundData_08187B14
    voice_ptr "data/voicegroups/a838c.bin", 8, DirectSoundData_081250B0
    voice_ptr "data/voicegroups/a838c.bin", 9, DirectSoundData_0818E8F0
    voice_ptr "data/voicegroups/a838c.bin", 10, DirectSoundData_0818F980
    voice_ptr "data/voicegroups/a838c.bin", 11, DirectSoundData_0818FCEC
    voice_ptr "data/voicegroups/a838c.bin", 12, DirectSoundData_0819029C
    voice_ptr "data/voicegroups/a838c.bin", 13, DirectSoundData_08190488
    voice_ptr "data/voicegroups/a838c.bin", 14, DirectSoundData_08190AB4
    voice_ptr "data/voicegroups/a838c.bin", 15, DirectSoundData_08190D18
    voice_ptr "data/voicegroups/a838c.bin", 16, DirectSoundData_081913E0
    voice_ptr "data/voicegroups/a838c.bin", 17, DirectSoundData_081919E0
    voice_ptr "data/voicegroups/a838c.bin", 18, DirectSoundData_08192424
    voice "data/voicegroups/a838c.bin", 19
    voice "data/voicegroups/a838c.bin", 20
    voice "data/voicegroups/a838c.bin", 21
    voice_ptr "data/voicegroups/a838c.bin", 22, DirectSoundData_080AA488
    voice_ptr "data/voicegroups/a838c.bin", 23, DirectSoundData_080AA84C
    voice_ptr "data/voicegroups/a838c.bin", 24, DirectSoundData_080AEBD0
    voice_ptr "data/voicegroups/a838c.bin", 25, DirectSoundData_080AA9B0
    voice_ptr "data/voicegroups/a838c.bin", 26, DirectSoundData_080AB22C
    voice_ptr "data/voicegroups/a838c.bin", 27, DirectSoundData_080ABA4C
    voice_ptr "data/voicegroups/a838c.bin", 28, DirectSoundData_080AC340
    voice_ptr "data/voicegroups/a838c.bin", 29, DirectSoundData_080AD784
    voice_ptr "data/voicegroups/a838c.bin", 30, DirectSoundData_080AE354
    voice_ptr "data/voicegroups/a838c.bin", 31, DirectSoundData_080ACA18
    voice_ptr "data/voicegroups/a838c.bin", 32, DirectSoundData_080AEE10
    voice "data/voicegroups/a838c.bin", 33
    voice_ptr "data/voicegroups/a838c.bin", 34, DirectSoundData_081937EC
    voice_ptr "data/voicegroups/a838c.bin", 35, DirectSoundData_08193EC4
    voice_ptr "data/voicegroups/a838c.bin", 36, DirectSoundData_0819496C
    voice_ptr "data/voicegroups/a838c.bin", 37, DirectSoundData_08194FD8
    .size sVoicegroup_a838c, . - sVoicegroup_a838c

    .align 2
    .type sVoicegroup_a8554, object
    .global sVoicegroup_a8554
sVoicegroup_a8554:
    voice_ptr "data/voicegroups/a8554.bin", 0, sVoicegroup_a808c + 26 * 12
    voice_ptr "data/voicegroups/a8554.bin", 1, DirectSoundData_08195670
    voice "data/voicegroups/a8554.bin", 2
    voice_ptr "data/voicegroups/a8554.bin", 3, DirectSoundData_08195EBC
    voice_ptr "data/voicegroups/a8554.bin", 4, DirectSoundData_08196984
    voice_ptr "data/voicegroups/a8554.bin", 5, DirectSoundData_08197268
    voice_ptr "data/voicegroups/a8554.bin", 6, DirectSoundData_08197CC0
    voice "data/voicegroups/a8554.bin", 7
    voice "data/voicegroups/a8554.bin", 8
    voice_ptr "data/voicegroups/a8554.bin", 9, DirectSoundData_08197E88
    voice_ptr "data/voicegroups/a8554.bin", 10, DirectSoundData_08198684
    voice_ptr "data/voicegroups/a8554.bin", 11, DirectSoundData_08199414
    voice_ptr "data/voicegroups/a8554.bin", 12, DirectSoundData_0819A0B0
    voice_ptr "data/voicegroups/a8554.bin", 13, DirectSoundData_0819C754
    voice "data/voicegroups/a8554.bin", 14
    voice "data/voicegroups/a8554.bin", 15
    voice_ptr "data/voicegroups/a8554.bin", 16, DirectSoundData_0819CAF0
    voice "data/voicegroups/a8554.bin", 17
    voice_ptr "data/voicegroups/a8554.bin", 18, DirectSoundData_0819D3C8
    voice_ptr "data/voicegroups/a8554.bin", 19, DirectSoundData_0819DAC0
    voice_ptr "data/voicegroups/a8554.bin", 20, DirectSoundData_0819E524
    voice_ptr "data/voicegroups/a8554.bin", 21, DirectSoundData_0819C754
    voice_ptr "data/voicegroups/a8554.bin", 22, DirectSoundData_0819A0B0
    voice_ptr "data/voicegroups/a8554.bin", 23, DirectSoundData_0819E958
    voice_ptr "data/voicegroups/a8554.bin", 24, DirectSoundData_0819EE6C
    voice_ptr "data/voicegroups/a8554.bin", 25, DirectSoundData_0819FEBC
    voice_ptr "data/voicegroups/a8554.bin", 26, DirectSoundData_080B0E50
    voice_ptr "data/voicegroups/a8554.bin", 27, DirectSoundData_081A064C
    voice_ptr "data/voicegroups/a8554.bin", 28, DirectSoundData_081A23FC
    voice_ptr "data/voicegroups/a8554.bin", 29, DirectSoundData_081A28F8
    voice_ptr "data/voicegroups/a8554.bin", 30, DirectSoundData_081A2DF4
    voice_ptr "data/voicegroups/a8554.bin", 31, DirectSoundData_081A32F0
    voice_ptr "data/voicegroups/a8554.bin", 32, DirectSoundData_081A37EC
    voice_ptr "data/voicegroups/a8554.bin", 33, DirectSoundData_081A43D0
    voice_ptr "data/voicegroups/a8554.bin", 34, DirectSoundData_081A4AC0
    voice_ptr "data/voicegroups/a8554.bin", 35, DirectSoundData_081A5090
    voice_ptr "data/voicegroups/a8554.bin", 36, DirectSoundData_081A5434
    voice_ptr "data/voicegroups/a8554.bin", 37, DirectSoundData_081A5E40
    voice "data/voicegroups/a8554.bin", 38
    voice "data/voicegroups/a8554.bin", 39
    voice_ptr "data/voicegroups/a8554.bin", 40, DirectSoundData_0819CAF0
    voice_ptr "data/voicegroups/a8554.bin", 41, DirectSoundData_081A37EC
    voice_ptr "data/voicegroups/a8554.bin", 42, DirectSoundData_081A6AFC
    voice_ptr "data/voicegroups/a8554.bin", 43, DirectSoundData_0819DAC0
    voice_ptr "data/voicegroups/a8554.bin", 44, DirectSoundData_081AB0B0
    voice_ptr "data/voicegroups/a8554.bin", 45, DirectSoundData_081AB320
    voice_ptr "data/voicegroups/a8554.bin", 46, DirectSoundData_081ABA98
    voice_ptr "data/voicegroups/a8554.bin", 47, DirectSoundData_081AD364
    voice_ptr "data/voicegroups/a8554.bin", 48, DirectSoundData_081AEF28
    voice "data/voicegroups/a8554.bin", 49
    voice "data/voicegroups/a8554.bin", 50
    voice_ptr "data/voicegroups/a8554.bin", 51, DirectSoundData_081B0958
    voice_ptr "data/voicegroups/a8554.bin", 52, DirectSoundData_081B0FCC
    voice_ptr "data/voicegroups/a8554.bin", 53, DirectSoundData_0819FEBC
    voice_ptr "data/voicegroups/a8554.bin", 54, DirectSoundData_081B17A0
    voice "data/voicegroups/a8554.bin", 55
    voice "data/voicegroups/a8554.bin", 56
    voice "data/voicegroups/a8554.bin", 57
    voice_ptr "data/voicegroups/a8554.bin", 58, DirectSoundData_08195670
    voice_ptr "data/voicegroups/a8554.bin", 59, DirectSoundData_080D3598
    voice_ptr "data/voicegroups/a8554.bin", 60, DirectSoundData_080D5E5C
    voice_ptr "data/voicegroups/a8554.bin", 61, DirectSoundData_080D3694
    voice_ptr "data/voicegroups/a8554.bin", 62, DirectSoundData_080C9BE4
    voice_ptr "data/voicegroups/a8554.bin", 63, DirectSoundData_080B0310
    voice_ptr "data/voicegroups/a8554.bin", 64, DirectSoundData_080B8B88
    voice "data/voicegroups/a8554.bin", 65
    voice "data/voicegroups/a8554.bin", 66
    voice_ptr "data/voicegroups/a8554.bin", 67, DirectSoundData_08195670
    voice_ptr "data/voicegroups/a8554.bin", 68, DirectSoundData_081B1DA4
    voice_ptr "data/voicegroups/a8554.bin", 69, DirectSoundData_081B28E0
    voice_ptr "data/voicegroups/a8554.bin", 70, DirectSoundData_081B5230
    voice "data/voicegroups/a8554.bin", 71
    voice "data/voicegroups/a8554.bin", 72
    voice_ptr "data/voicegroups/a8554.bin", 73, sWaveData_a8ccc
    voice_ptr "data/voicegroups/a8554.bin", 74, DirectSoundData_081B7E84
    voice_ptr "data/voicegroups/a8554.bin", 75, DirectSoundData_081B808C
    voice_ptr "data/voicegroups/a8554.bin", 76, DirectSoundData_081B8548
    voice "data/voicegroups/a8554.bin", 77
    voice_ptr "data/voicegroups/a8554.bin", 78, DirectSoundData_081B87F4
    voice_ptr "data/voicegroups/a8554.bin", 79, DirectSoundData_081B8FDC
    voice_ptr "data/voicegroups/a8554.bin", 80, DirectSoundData_081BB0CC
    voice_ptr "data/voicegroups/a8554.bin", 81, DirectSoundData_081BB470
    voice_ptr "data/voicegroups/a8554.bin", 82, DirectSoundData_081BE070
    voice_ptr "data/voicegroups/a8554.bin", 83, DirectSoundData_081BE190
    voice_ptr "data/voicegroups/a8554.bin", 84, DirectSoundData_081BEB4C
    voice_ptr "data/voicegroups/a8554.bin", 85, DirectSoundData_081BF2E8
    voice_ptr "data/voicegroups/a8554.bin", 86, DirectSoundData_081BF9A8
    voice_ptr "data/voicegroups/a8554.bin", 87, DirectSoundData_081BFC48
    voice "data/voicegroups/a8554.bin", 88
    voice_ptr "data/voicegroups/a8554.bin", 89, DirectSoundData_081BB470
    voice_ptr "data/voicegroups/a8554.bin", 90, DirectSoundData_081BFFB8
    voice_ptr "data/voicegroups/a8554.bin", 91, DirectSoundData_081C07F8
    voice_ptr "data/voicegroups/a8554.bin", 92, DirectSoundData_081C1120
    voice_ptr "data/voicegroups/a8554.bin", 93, DirectSoundData_081C12E8
    voice_ptr "data/voicegroups/a8554.bin", 94, DirectSoundData_081C166C
    voice_ptr "data/voicegroups/a8554.bin", 95, DirectSoundData_081C1B40
    voice_ptr "data/voicegroups/a8554.bin", 96, DirectSoundData_081C258C
    voice_ptr "data/voicegroups/a8554.bin", 97, DirectSoundData_081C3004
    voice_ptr "data/voicegroups/a8554.bin", 98, DirectSoundData_081C3704
    voice_ptr "data/voicegroups/a8554.bin", 99, DirectSoundData_081C3E08
    voice_ptr "data/voicegroups/a8554.bin", 100, DirectSoundData_081C4714
    voice_ptr "data/voicegroups/a8554.bin", 101, DirectSoundData_081C490C
    voice_ptr "data/voicegroups/a8554.bin", 102, DirectSoundData_081C4E74
    voice_ptr "data/voicegroups/a8554.bin", 103, DirectSoundData_081C6480
    voice_ptr "data/voicegroups/a8554.bin", 104, DirectSoundData_081C781C
    voice "data/voicegroups/a8554.bin", 105
    voice_ptr "data/voicegroups/a8554.bin", 106, DirectSoundData_081CDC5C
    voice_ptr "data/voicegroups/a8554.bin", 107, DirectSoundData_081D2ECC
    voice_ptr "data/voicegroups/a8554.bin", 108, DirectSoundData_081D387C
    voice_ptr "data/voicegroups/a8554.bin", 109, DirectSoundData_081D43A0
    voice_ptr "data/voicegroups/a8554.bin", 110, DirectSoundData_081D5D58
    voice_ptr "data/voicegroups/a8554.bin", 111, DirectSoundData_0819CAF0
    voice_ptr "data/voicegroups/a8554.bin", 112, DirectSoundData_081D7994
    voice_ptr "data/voicegroups/a8554.bin", 113, DirectSoundData_08197CC0
    voice_ptr "data/voicegroups/a8554.bin", 114, DirectSoundData_081E06F4
    voice_ptr "data/voicegroups/a8554.bin", 115, DirectSoundData_081E17E4
    voice_ptr "data/voicegroups/a8554.bin", 116, DirectSoundData_081E3114
    voice_ptr "data/voicegroups/a8554.bin", 117, DirectSoundData_081E37C8
    voice_ptr "data/voicegroups/a8554.bin", 118, DirectSoundData_081E4238
    voice_ptr "data/voicegroups/a8554.bin", 119, DirectSoundData_081E6620
    .size sVoicegroup_a8554, . - sVoicegroup_a8554

    .align 2
    .type sVoicegroup_a8af4, object
    .global sVoicegroup_a8af4
sVoicegroup_a8af4:
    voice_ptr "data/voicegroups/a8af4.bin", 0, DirectSoundData_081E70F8
    voice_ptr "data/voicegroups/a8af4.bin", 1, DirectSoundData_081ECDBC
    voice_ptr "data/voicegroups/a8af4.bin", 2, DirectSoundData_081EF770
    voice_ptr "data/voicegroups/a8af4.bin", 3, DirectSoundData_081F1F3C
    voice_ptr "data/voicegroups/a8af4.bin", 4, DirectSoundData_081F43A0
    voice_ptr "data/voicegroups/a8af4.bin", 5, DirectSoundData_081F6830
    voice_ptr "data/voicegroups/a8af4.bin", 6, DirectSoundData_081F8B80
    voice_ptr "data/voicegroups/a8af4.bin", 7, DirectSoundData_081FB34C
    voice_ptr "data/voicegroups/a8af4.bin", 8, DirectSoundData_081FDB98
    voice_ptr "data/voicegroups/a8af4.bin", 9, DirectSoundData_0820037C
    voice_ptr "data/voicegroups/a8af4.bin", 10, DirectSoundData_082027B8
    voice_ptr "data/voicegroups/a8af4.bin", 11, DirectSoundData_08204F48
    voice_ptr "data/voicegroups/a8af4.bin", 12, DirectSoundData_08207CD8
    voice_ptr "data/voicegroups/a8af4.bin", 13, DirectSoundData_0820A158
    voice_ptr "data/voicegroups/a8af4.bin", 14, DirectSoundData_0820C53C
    voice_ptr "data/voicegroups/a8af4.bin", 15, DirectSoundData_0820E5D8
    voice_ptr "data/voicegroups/a8af4.bin", 16, DirectSoundData_0821073C
    voice_ptr "data/voicegroups/a8af4.bin", 17, DirectSoundData_08212B70
    voice_ptr "data/voicegroups/a8af4.bin", 18, DirectSoundData_08215298
    voice_ptr "data/voicegroups/a8af4.bin", 19, DirectSoundData_0821E0EC
    voice_ptr "data/voicegroups/a8af4.bin", 20, DirectSoundData_08228B64
    voice_ptr "data/voicegroups/a8af4.bin", 21, DirectSoundData_0822DF60
    voice_ptr "data/voicegroups/a8af4.bin", 22, DirectSoundData_08234300
    voice_ptr "data/voicegroups/a8af4.bin", 23, DirectSoundData_08236BE0
    voice_ptr "data/voicegroups/a8af4.bin", 24, DirectSoundData_0823C1F8
    voice_ptr "data/voicegroups/a8af4.bin", 25, DirectSoundData_0823FACC
    voice_ptr "data/voicegroups/a8af4.bin", 26, DirectSoundData_082438E4
    voice_ptr "data/voicegroups/a8af4.bin", 27, DirectSoundData_082466E0
    .size sVoicegroup_a8af4, . - sVoicegroup_a8af4

@ Data after the voices: the keysplit table of sVoicegroup_a5cf8's keysplit voice (voice
@ indexes for keys 36 to 107; the voice points 36 bytes before it), CGB wave data
    .type sKeysplitTable_a8c44, object
    .global sKeysplitTable_a8c44
sKeysplitTable_a8c44:
    .incbin "data/voicegroups/a8af4.bin", 0x150, 0x48
    .size sKeysplitTable_a8c44, . - sKeysplitTable_a8c44
    .type sWaveData_a8c8c, object
    .global sWaveData_a8c8c
sWaveData_a8c8c:
    .incbin "data/voicegroups/a8af4.bin", 0x198, 0x10
    .size sWaveData_a8c8c, . - sWaveData_a8c8c
    .type sWaveData_a8c9c, object
    .global sWaveData_a8c9c
sWaveData_a8c9c:
    .incbin "data/voicegroups/a8af4.bin", 0x1a8, 0x10
    .size sWaveData_a8c9c, . - sWaveData_a8c9c
    .type sWaveData_a8cac, object
    .global sWaveData_a8cac
sWaveData_a8cac:
    .incbin "data/voicegroups/a8af4.bin", 0x1b8, 0x10
    .size sWaveData_a8cac, . - sWaveData_a8cac
    .type sWaveData_a8cbc, object
    .global sWaveData_a8cbc
sWaveData_a8cbc:
    .incbin "data/voicegroups/a8af4.bin", 0x1c8, 0x10
    .size sWaveData_a8cbc, . - sWaveData_a8cbc
    .type sWaveData_a8ccc, object
    .global sWaveData_a8ccc
sWaveData_a8ccc:
    .incbin "data/voicegroups/a8af4.bin", 0x1d8, 0x10
    .size sWaveData_a8ccc, . - sWaveData_a8ccc
