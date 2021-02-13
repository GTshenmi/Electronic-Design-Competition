#ifndef _STEER_CTRL_H_
#define _STEER_CTRL_H_

short Steer0Ctrl(steer_handle_t* handle,short data);
short Steer0DataProcess(steer_handle_t *handle,short value);
short Steer1Ctrl(steer_handle_t* handle,short data);
short Steer1DataProcess(steer_handle_t *handle,short value);
short Steer2Ctrl(steer_handle_t* handle,short data);
short Steer2DataProcess(steer_handle_t *handle,short value);

#endif