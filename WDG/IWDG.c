#include "IWDG.h"

 void WDG_Init(u16 pre,u8 rlr)
 {
   IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
   IWDG_SetPrescaler(pre);
   IWDG_SetPrescaler(rlr);
   IWDG_ReloadCounter();
   IWDG_Enable();
 }