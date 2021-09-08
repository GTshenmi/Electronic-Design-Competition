#ifndef _PID_CTRL_H_
#define _PID_CTRL_H_

typedef enum
{
	PositionalPID,IncrementalPID,
}pid_type_t;

typedef struct 
{
	 float Input;
	 float Output;
}pid_gain_t;

typedef struct
{
	 float Kp;
	 float Ki;
	 float Kd;
}pid_ctrl_t;

typedef struct
{
	
	 float Kp;
	 float Ki;
	 float Kd;
	
	 float PID_Error[3];
	 float IntegralValue;
	
	 float Result;
	
	 pid_gain_t Gain;
	
	 pid_type_t PID_Type;
	 
}PID_TypeDef;


PID_TypeDef PID_Init(pid_type_t PID_Type);

PID_TypeDef PID_SetValue(pid_ctrl_t PIDValue,PID_TypeDef *PID_CtrlStr);

PID_TypeDef PID_SetGain(pid_gain_t GainValue,PID_TypeDef *PID_CtrlStr);

PID_TypeDef PID_Ctrl(float TargetValue,float ActualValue,PID_TypeDef *PID_CtrlStr);

pid_ctrl_t PIDValue(float Kp,float Ki,float Kd);

pid_gain_t PIDGainValue(float inputgain,float outputgain);

#endif

