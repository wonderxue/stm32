#ifndef __WWDG_H__
#define __WWDG_H__

#include "stm32f10x.h"

#define  WWDG_IT   1

void WWDG_Init(u8 cr,u16 pre,u8 wr);
void WWDG_ReloadCounter();

#endif  //__WWDG_H__ 