#ifndef _STEER_H_
#define _STEER_H_

#define NotSetLimit (short)32767

#define STEER_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C

#define STEER0_MAX_PWM_DUTY_L   700 //l
#define STEER0_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C
#define STEER0_MIN_PWM_DUTY_R   560//r

#define STEER1_MAX_PWM_DUTY_L   700 //l
#define STEER1_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C
#define STEER1_MIN_PWM_DUTY_R   560//r

#define STEER2_MAX_PWM_DUTY_L   700 //l
#define STEER2_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C
#define STEER2_MIN_PWM_DUTY_R   560//r

#define STEER3_MAX_PWM_DUTY_L   700 //l
#define STEER3_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C
#define STEER3_MIN_PWM_DUTY_R   560//r

#define STEER_CTRL_FIN_CALLBACK_EN 1
#define STEER_DATAPROCESS_FIN_CALLBACK_EN 0
#define STEER_CTRLSTRATEGY_EN 1
#define STEER_DATAPROCESS_EN 1

typedef struct
{
      FTM_Type *PwmFTM;     /*Model to gengerate PWM*/
      FTM_CHn_e PwmChannel; /*PWM Channel*/
      
      short PwmFreq;        /*PWM Frequency*/
      short PwmCentValue;   /*Steer center PWM duty*/
      
      limit_t AngleLimit;   /*Max and Min angle*/
      limit_t PwmLimit;     /*Max and Min PWM duty*/
       
}steer_handle_t;

typedef struct
{     
      steer_handle_t Handle;            /*Config of Steer and PWM generator*/
      
#if STEER_CTRLSTRATEGY_EN
      short (*CtrlStrategy)(short);     /*Steer Control Function: Angle Cycle*/
#endif

#if STEER_CTRL_FIN_CALLBACK_EN
      void (*CtrlFinishCallBack)(void); /*Finish control callback function*/
#endif

#if STEER_DATAPROCESS_EN
      short (*DataProcess)(short);        /*process input data*/
#endif

#if STEER_DATAPROCESS_FIN_CALLBACK_EN
      void (*DataProcessFinishCallBack)(void); /*finish data process callback function*/
#endif

      short TargetAngle;		 /*目标角度*/
      short TargetAngle_Inc;
      
      short CurrentAngle;	         /*当前角度*/
      short (*GetActualAngle)();         /*获取角度值*/
    
      short PwmValue;			 /*舵机PWM值*/
                
      bool Is_Run;                       /*舵机运行标志位*/
                
}steer_ctrl_t;

extern steer_ctrl_t Steer[4];

void SteerController(steer_ctrl_t *Steer,short angle);

void SteerInit(steer_ctrl_t *Steer);
void SetSteerAngle(steer_ctrl_t *Steer,short angle);
void SetSteerPwmDuty(steer_ctrl_t *Steer,short duty);
void SteerCreateHandle(steer_ctrl_t *Steer,steer_handle_t *handle);


#endif
