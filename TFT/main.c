#include <stm32f10x.h>
#include "GUI.h"
#include "pic.h"

int main()
{
  TFT_Init();
  TFT_Clear(0x0);
  showimage(0,0,128,71,gImage_pic);
  while(1)
  {
  }
}
