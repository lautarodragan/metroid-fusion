#ifndef SA_X_CLOSE_UP_STRUCTS_H
#define SA_X_CLOSE_UP_STRUCTS_H

#include "types.h"

struct SaXCloseUpData {
    u8 skipProcess; // The close-up only plays while clear, never set in the final game
    u8 stage;
    u8 timer;
};

#endif /* SA_X_CLOSE_UP_STRUCTS_H */
