@ Voices of a voicegroup (12 bytes each), taken from \file (data/voicegroups/<offset>.bin).
@ Only the pointers are written in the source, as symbols, so that they follow what they
@ point to.

@ A voice without a pointer (CGB square/noise voices, unused voices)
    .macro voice file, index
    .incbin "\file", (\index) * 12, 12
    .endm

@ A voice whose second word points to a direct sound sample, CGB wave data or a drum kit
    .macro voice_ptr file, index, ptr
    .incbin "\file", (\index) * 12, 4
    .4byte \ptr
    .incbin "\file", (\index) * 12 + 8, 4
    .endm

@ A keysplit voice: the voicegroup to use and the table giving the voice of each key
    .macro voice_keysplit file, index, voicegroup, table
    .incbin "\file", (\index) * 12, 4
    .4byte \voicegroup
    .4byte \table
    .endm
