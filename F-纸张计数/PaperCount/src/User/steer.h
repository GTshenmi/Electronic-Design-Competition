#ifndef _STEER_H_
#define _STEER_H_

#include "element.h"

#define STEER_PWM            FTM0
#define STEER_PWM_CHANNEL    FTM_CH5
#define STEER_PWM_FREQ       50

/*���Զ��:1*/
#define TEST_CAR_STEER 0
/*ʹ������ʽPID:1*/
#define USING_INC 0
/*ʹ�ö�̬PID:1*/
#define USING_DYNAMIC_PID 1

#define Using_Dynamic_PID_1 1

#define UsingDynamicKbCtrl 0
///*ʹ�ò���:1*/
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
		short MaxAngle;			/*���Ƕ�*/
		short MinAngle;			/*��С�Ƕ�*/	
                
                float Jp;                        /*��̬PID ϵ��*/
                float Kp_MaxValue;               /*��̬PID �޷�*/
                float Jd;
                float Kd_MaxValue;  
                float Differnce_P;              /*����ϵ��*/
                float Boundprotect_P;           /*�߽籣������P*/
                
                void (*SetAngle)(short angle);    /*���ýǶ�*/
		void (*SetPwm)(short duty);	/*�趨ռ�ձ�*/
		short (*GetActualPosition)();	/*��ȡʵ������ƫ��*/
                void (*Protect)(void);          /*�����������*/
                void (*ForceTurnLeft)();        /*���ǿ����ת*/
                void (*ForceTurnRight)();       /*���ǿ����ת*/

/*		PID ������			*/	
		float Kp;	
                float Kp_Inc;
		float Ki;
		float Kd;
                float Kd_Inc;
          
                short dA;
                long A;
                long MaxA;
                long MinA;
	
		float PID_Error;		 /*��ǰ���*/
		float PID_PreError;	         /*��һ�����*/
		float PID_LastError;	         /*���ϴ����*/
		float PID_Inc;	                 /*��������*/

/*			ʵ��ֵ				*/		
	
                short CurrentPosition;          /*��ǰ����ƫ��*/
                short LastPosition;             /*�ϴ�����ƫ��*/
                short _Bias[10];
                short Bias;
                short LastBias;
                float Kb[10];
                float Kb_Inc[10];
                short Position;                 /*Ҫ���õ�����ƫ�����������������������ƫ��)*/
                short Position_Inc;             /*Ҫ���õ�����ƫ���������������������е�������ƫ��)*/
                short TargetPosition;
/*			�趨ֵ				*/
                short _Angle[10];
                short Angle;                     /*Ҫ���õĽǶȣ������������������ýǶ�)*/
                short Angle_Inc;                 /*�Ƕ��������������������е����Ƕ�)*/
		short TargetAngle;		 /*Ŀ��Ƕ�*/
		short CurrentAngle;	         /*��ǰ�Ƕ�*/	
		short LastAngle;		/*��һ�εĽǶ�*/
    
		short PwmValue;			 /*���PWMֵ*/
                
                bool PID_Lock;                   /*PID���Ʊ�־λ*/
                bool using_steerprotect;         /*���������־λ*/
                bool Is_Run;                     /*������б�־λ*/
                
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
