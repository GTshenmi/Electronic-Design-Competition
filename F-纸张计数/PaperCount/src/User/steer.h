#ifndef _STEER_H_
#define _STEER_H_

#include "element.h"

#define STEER_PWM            FTM0
#define STEER_PWM_CHANNEL    FTM_CH5
#define STEER_PWM_FREQ       50

/*测试舵机:1*/
#define TEST_CAR_STEER 0
/*使用增量式PID:1*/
#define USING_INC 0
/*使用动态PID:1*/
#define USING_DYNAMIC_PID 1

#define Using_Dynamic_PID_1 1

#define UsingDynamicKbCtrl 0
///*使用差速:1*/
//#define USING_DSPEED 1

#if TEST_CAR_STEER

#define STEER_MAX_PWM_DUTY_L   700 //l
#define STEER_PWM_CENT_VALUE   630 //338R->350L->344R->347R->350C
#define STEER_MIN_PWM_DUTY_R   560//r

#else       

#define STEER_MAX_PWM_DUTY_L   (short)700 
#define STEER_PWM_CENT_VALUE   (short)630  
#define STEER_MIN_PWM_DUTY_R   (short)560

#endif


#define ADLS    AD[0]
#define ADRS    AD[4]
#define ADLC    AD[1]
#define ADRC    AD[3]
#define ADM     AD[2]

typedef enum
{
   ADS,ADC, 
}_L_t_;


typedef enum
{
    TurnLeft,TurnRight
}_dir_t_;

typedef struct
{
		short MaxAngle;			/*最大角度*/
		short MinAngle;			/*最小角度*/	
                
                float Jp;                        /*动态PID 系数*/
                float Kp_MaxValue;               /*动态PID 限幅*/
                float Jd;
                float Kd_MaxValue;  
                float Differnce_P;              /*差速系数*/
                float Boundprotect_P;           /*边界保护差速P*/
                
                void (*SetAngle)(short angle);    /*设置角度*/
		void (*SetPwm)(short duty);	/*设定占空比*/
		short (*GetActualPosition)();	/*获取实际中线偏差*/
                void (*Protect)(void);          /*舵机保护程序*/
                void (*ForceTurnLeft)();        /*舵机强制左转*/
                void (*ForceTurnRight)();       /*舵机强制右转*/

/*		PID 控制器			*/	
		float Kp;	
                float Kp_Inc;
		float Ki;
		float Kd;
                float Kd_Inc;
          
                short dA;
                long A;
                long MaxA;
                long MinA;
	
		float PID_Error;		 /*当前误差*/
		float PID_PreError;	         /*上一次误差*/
		float PID_LastError;	         /*上上次误差*/
		float PID_Inc;	                 /*调整增量*/

/*			实际值				*/		
	
                short CurrentPosition;          /*当前中线偏差*/
                short LastPosition;             /*上次中线偏差*/
                short _Bias[10];
                short Bias;
                short LastBias;
                float Kb[10];
                float Kb_Inc[10];
                short Position;                 /*要设置的中线偏差（用于其他函数中设置中线偏差)*/
                short Position_Inc;             /*要设置的中线偏差增量（用于其他函数中调整中线偏差)*/
                short TargetPosition;
/*			设定值				*/
                short _Angle[10];
                short Angle;                     /*要设置的角度（用于其他函数中设置角度)*/
                short Angle_Inc;                 /*角度增量（用于其他函数中调整角度)*/
		short TargetAngle;		 /*目标角度*/
		short CurrentAngle;	         /*当前角度*/	
		short LastAngle;		/*上一次的角度*/
    
		short PwmValue;			 /*舵机PWM值*/
                
                bool PID_Lock;                   /*PID控制标志位*/
                bool using_steerprotect;         /*舵机保护标志位*/
                bool Is_Run;                     /*舵机运行标志位*/
                
}steer_ctrl_t;


extern steer_ctrl_t Steer;

void SteerInit();
void SteerPIDValueInit();
short GetInductanceDifference();

void SetSteerDynamicPID();
void SetMidlineDeviation(int dx);
void SetSteerAngle(short angle);
void SteerForceTurnLeft();
void SteerForceTurnRight();
void SteerCtrl(short duty);


#endif
