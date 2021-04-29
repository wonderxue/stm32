#ifndef __IWDG_H__
#define __IWDG_H__

#include "stm32f10x.h"

void IWDG_Init(u16 pre,u8 rlr);
void IWDG_ReloadCounter();

#endif  //__IWDG_H__ 