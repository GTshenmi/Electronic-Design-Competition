#ifndef _MOTOR_CTRL_H_
#define _MOTOR_CTRL_H_

short Motor0CtrlStrategy(motor_handle_t *handle,short value);

extern PID_TypeDef PID_CtrlStr; 

#endif
