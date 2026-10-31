#ifndef SECRET_CONVERSATION_H
#define SECRET_CONVERSATION_H

#include "types.h"

#include "structs/cutscene_data.h"

boolu32 CutsceneFederationMonologueProcess(void);
u8 CutsceneFederationMonologueSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneFederationMonologueVblank(void);
void CutsceneFederationMonologueLoadingVblank(void);

boolu32 CutsceneSecretConversation(void);
void CutsceneSecretConversationInit(void);
boolu32 CutsceneSecretConversationProcess(void);
u8 CutsceneSecretConversationSetupOam(u8 type, u16 xPosition, u16 yPosition);
void CutsceneSecretConversationProcessNavigationPanel(struct CutsceneOam* pOam);
void CutsceneSecretConversationProcessIncomingDispatch(struct CutsceneOam* pOam);
void CutsceneSecretConversationVblank(void);
void CutsceneSecretConversationLoadingVblank(void);

#endif /* SECRET_CONVERSATION_H */
