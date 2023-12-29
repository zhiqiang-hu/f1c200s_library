// UTF-8
#include "myresource.h"

Pagesdiotest pagesdiotest;
extern DATA mydata;
extern rt_sem_t sdio_test_sem;

static void Back_Button_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    lv_timer_del(pagesdiotest.timer);
    lv_obj_del(pagesdiotest.view);
    lv_obj_clear_flag(pageDemoSelect.view, LV_OBJ_FLAG_HIDDEN);
  }
}

static void Test_Event(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED)
  {
    mydata.sd_write_ok_flag = 0;
    rt_sem_release(sdio_test_sem);
  }
}

static void my_timer(lv_timer_t * timer)
{
  if(mydata.sd_write_ok_flag == 1)
  {
    lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:file write sucess");
    lv_obj_align_to(pagesdiotest.sdio_write_file_tips,
                    pagesdiotest.sdio_write_file_btn,
                    LV_ALIGN_OUT_BOTTOM_MID,
                    0,
                    0);
  }
  else
  {
    if(mydata.sd_res == FR_OK)
    {
      lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:%d", mydata.sd_res);
      lv_obj_align_to(pagesdiotest.sdio_write_file_tips,
                      pagesdiotest.sdio_write_file_btn,
                      LV_ALIGN_OUT_BOTTOM_MID,
                      0,
                      0);
    }
    else
    {
      lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips_error:%d", mydata.sd_res);
      lv_obj_align_to(pagesdiotest.sdio_write_file_tips,
                      pagesdiotest.sdio_write_file_btn,
                      LV_ALIGN_OUT_BOTTOM_MID,
                      0,
                      0);
    }
  }
}

void Pagesdiotest_Init(void)
{
  mydata.sd_res = FR_OK;
  mydata.sd_write_ok_flag = 0;

  pagesdiotest.view = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(pagesdiotest.view);
  lv_obj_set_size(pagesdiotest.view, LV_PCT(100), LV_PCT(100));

  pagesdiotest.back_btn = lv_btn_create(pagesdiotest.view);
  lv_obj_set_size(pagesdiotest.back_btn, 120, 50);
  lv_obj_align(pagesdiotest.back_btn, LV_ALIGN_TOP_LEFT, LV_PCT(2), LV_PCT(2));
  lv_obj_add_event_cb(pagesdiotest.back_btn, Back_Button_Event, LV_EVENT_CLICKED, NULL);

  pagesdiotest.back_btn_label = lv_label_create(pagesdiotest.back_btn);
  lv_obj_center(pagesdiotest.back_btn_label);
  lv_label_set_text(pagesdiotest.back_btn_label, "back");

  pagesdiotest.sdio_write_file_btn = lv_btn_create(pagesdiotest.view);
  lv_obj_set_width(pagesdiotest.sdio_write_file_btn, 150);
  lv_obj_center(pagesdiotest.sdio_write_file_btn);
  lv_obj_add_event_cb(pagesdiotest.sdio_write_file_btn, Test_Event, LV_EVENT_CLICKED, NULL);

  pagesdiotest.sdio_write_file_btn_label = lv_label_create(pagesdiotest.sdio_write_file_btn);
  lv_obj_center(pagesdiotest.sdio_write_file_btn_label);
  lv_label_set_text(pagesdiotest.sdio_write_file_btn_label, "sdio write file");

  pagesdiotest.sdio_write_file_tips = lv_label_create(pagesdiotest.view);
  lv_label_set_text_fmt(pagesdiotest.sdio_write_file_tips, "tips:%d", mydata.sd_res);
  lv_obj_align_to(pagesdiotest.sdio_write_file_tips,
                  pagesdiotest.sdio_write_file_btn,
                  LV_ALIGN_OUT_BOTTOM_MID,
                  0,
                  0);

  pagesdiotest.timer = lv_timer_create(my_timer, 100, NULL);
}
