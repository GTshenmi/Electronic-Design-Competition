/*
  @attention�� 
  ���ļ����ڱ�д��Steer.c��
  steer_ctrl_t �ṹ���ж���ĺ���
  ��������Ŀ��ƺ��������ݴ���������ȡ�ǶȺ������Լ������ص�����
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