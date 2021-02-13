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

PID_TypeDef PID_SetValue(PID_TypeDef *PID_CtrlStr,pid_ctrl_t PIDValue);

PID_TypeDef PID_SetGain(PID_TypeDef *PID_CtrlStr,pid_gain_t GainValue);

PID_TypeDef PID_Ctrl(PID_TypeDef *PID_CtrlStr,float TargetValue,float ActualValue);

pid_ctrl_t PIDValue(float Kp,float Ki,float Kd);

pid_gain_t PIDGainValue(float inputgain,float outputgain);

typedef struct
{

  float setpoint;      //设定值

  float proportiongain;     //比例系数

  float integralgain;     //积分系数

  float derivativegain;   //微分系数

  float lasterror;    //前一拍偏差

  float result;//输出值

  float integral;//积分值

  float epsilon; //偏差检测阈值

}ipid_t;

void PIDRegulation(ipid_t *vPID, float processValue);

#endif

