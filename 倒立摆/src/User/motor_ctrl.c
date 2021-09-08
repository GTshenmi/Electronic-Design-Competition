#include "include.h"
#include "motor_ctrl.h"

short GetMotorParameter(motor_ctrl_t *Motor)
{
   return Motor->DataProcess(FTM_ABGet(Motor->Handle.ENCFTM)); 
}