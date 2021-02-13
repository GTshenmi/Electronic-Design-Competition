#ifndef _STEER_H_
#define _STEER_H_

#define STEER0_FTM FTM3
#define STEER1_FTM FTM3//FTM3
#define STEER2_FTM FTM3//FTM3
#define STEER3_FTM FTM3

#define STEER0_FTM_CH FTM_CH0
#define STEER1_FTM_CH FTM_CH1//FTM_CH0
#define STEER2_FTM_CH FTM_CH2//FTM_CH1
#define STEER3_FTM_CH FTM_CH3

#define Steer0 Steer[0]
#define Steer1 Steer[1]
#define Steer2 Steer[2]
#define Steer3 Steer[3]

#define PSteer0 &Steer[0]
#define PSteer1 &Steer[1]
#define PSteer2 &Steer[2]
#define PSteer3 &Steer[3]

#define STEER_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C

//#define STEER0_MAX_PWM_DUTY_L   820 //l
//#define STEER0_PWM_CENT_VALUE   740 //338R->350L->344R->347R->350C
//#define STEER0_MIN_PWM_DUTY_R   665//r

#define STEER0_MAX_PWM_DUTY_L   1285 //l
#define STEER0_PWM_CENT_VALUE   750 //338R->350L->344R->347R->350C
#define STEER0_MIN_PWM_DUTY_R   200//r

#define STEER1_MAX_PWM_DUTY_L   1285//1050 //l 
#define STEER1_PWM_CENT_VALUE   750 //338R->350L->344R->347R->350C 5 7.5 10.5 V
#define STEER1_MIN_PWM_DUTY_R   200//500//r

#define STEER2_MAX_PWM_DUTY_L   1215 //l
#define STEER2_PWM_CENT_VALUE   750 //338R->350L->344R->347R->350C 5 7.5 10.5 H
#define STEER2_MIN_PWM_DUTY_R   225//r

#define STEER3_MAX_PWM_DUTY_L   1215 //l
#define STEER3_PWM_CENT_VALUE   750 //338R->350L->344R->347R->350C
#define STEER3_MIN_PWM_DUTY_R   225//r

#define STEER_CTRL_FIN_CALLBACK_EN 0
#define STEER_DATAPROCESS_FIN_CALLBACK_EN 0
#define STEER_CTRLSTRATEGY_EN 1
#define STEER_DATAPROCESS_EN 1

#define steer_limit_t int16_limit_t
#define PwmToAngle(CentValue,PwmValue) (-(PwmValue)+(CentValue))

typedef struct
{
      FTM_Type *PwmFTM;     /*Model to gengerate PWM*/
      FTM_CHn_e PwmChannel; /*PWM Channel*/
      
      steer_limit_t AngleLimit;   /*Max and Min angle*/
      steer_limit_t PwmLimit;     /*Max and Min PWM duty*/
      
      short PwmFreq;        /*PWM Frequency*/
      short PwmCentValue;   /*Steer center PWM duty*/
      short PwmValue;			 /*舵机PWM值*/
      bool  UsingDefaultConfig;
       
}steer_handle_t;

typedef struct
{     
      steer_handle_t Handle;            /*Config of Steer and PWM generator*/
      
#if STEER_CTRLSTRATEGY_EN
      short (*CtrlStrategy)(steer_handle_t*,short);     /*Steer Control Function: Angle Cycle*/
#endif
      
#if STEER_DATAPROCESS_EN
      short (*DataProcess)(steer_handle_t*,short);        /*process input data*/
#endif
      
#if STEER_CTRL_FIN_CALLBACK_EN
      void (*CtrlFinishCallBack)(steer_handle_t*); /*Finish control callback function*/
#endif

#if STEER_DATAPROCESS_FIN_CALLBACK_EN
      void (*DataProcessFinishCallBack)(steer_handle_t*); /*finish data process callback function*/
#endif

      short (*GetActualAngle)(steer_handle_t*);         /*获取角度值*/
      short TargetAngle;		 /*目标角度*/
      short TargetAngle_Inc;
      
      short CurrentAngle;	         /*当前角度*/
                
      bool Is_Run;                       /*舵机运行标志位*/
                
}steer_ctrl_t;

extern steer_ctrl_t Steer[4];

void SteerInit(steer_ctrl_t *Steer,steer_handle_t *handle);
void SteerCreateDefaultHandle(steer_handle_t *handle);
void SteerCreateHandle(steer_ctrl_t *Steer,steer_handle_t *handle);

void SetSteerAngle(steer_ctrl_t *Steer,short angle);
void SetSteerPwmDuty(steer_ctrl_t *Steer,short duty);

short Steer_DefaultCtrl(steer_handle_t* handle,short data);
short Steer_DefaultDataProcess(steer_handle_t *handle,short value);
void Steer_DefaultDataProcessFinishCallBack(steer_handle_t *handle);
void Steer_DefaultCtrlFinishCallBack(steer_handle_t* handle);
short Steer_DefaultGetActualAngle(steer_handle_t* handle);

#endif
