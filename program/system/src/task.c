#include "task.h"

extern UART_DATA uart_Data;

void BELL_task(void * p)
{
  BELL_Init();
  while(1)
  {
    delay_ms(500);
  }
}

void LCD_task(void * p)
{
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  delay_ms(100);
  LCD_EN = 1;
  LCD_SetBrightness(100);
  PageMain_Init();
  while(1)
  {
    lv_task_handler();
    delay_ms(10);
  }
}