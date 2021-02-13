/*
  @attention： 
  本文件用于编写结Steer.c中
  steer_ctrl_t 结构体中定义的函数
  包括舵机的控制函数、数据处理函数、获取角度函数、以及各个回调函数
*/
#include "include.h"
#include "steer_ctrl.h"



short Steer1Ctrl(steer_handle_t* handle,short data)
{
   return  -data+handle->PwmCentValue;
}

short Steer1DataProcess(steer_handle_t *handle,short value)
{
   return value;
}
    
short Steer2Ctrl(steer_handle_t* handle,short data)
{
   return  -data+handle->PwmCentValue;
}

short Steer2DataProcess(steer_handle_t *handle,short value)
{
   return value;
}
    
short Steer0Ctrl(steer_handle_t* handle,short data)
{
   return  -data+handle->PwmCentValue;
}

short Steer0DataProcess(steer_handle_t *handle,short value)
{
   return value;
}