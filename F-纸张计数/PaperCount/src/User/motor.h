#ifndef _MOTOR_H_
#define _MOTOR_H_

#define PWML1   FTM3
#define PWML2   FTM3

#define PWMR1   FTM3
#define PWMR2   FTM3


#define PWML1_CH   FTM_CH3     
#define PWML2_CH   FTM_CH2

//#define PWML1_CH   FTM_CH0     
//#define PWML2_CH   FTM_CH1

#define PWMR1_CH   FTM_CH1
#define PWMR2_CH   FTM_CH0   

#define ENCL    FTM1
#define ENCR    FTM2  

#define MOTOR_PWM_FREQ 10000
#define MOTOR_PWM_INIT_DUTY 0
#define LIMIT_SPEED 8000
#define LIMIT_PWM 10000

/*���Ե��:1*/
#define TEST_CAR_MOTOR 0

#define dt ((float)(MotorInterruptInterval/1000.0))

#define pulse_per_cycle ((float)(512*68/30))

#define dw 0.064      
#define pi 3.1415926

#define Px ((float)(pi*dw/pulse_per_cycle)) /*ϵ��*/

#define intergal_error 0.1667841432

#define track_length 45.3265491901

#define intergal_error_rate ((float)((intergal_error)/(track_length)))  //0.0036796126


typedef struct
{
		short MaxSpeed;			/*����ٶ�*/
		short MinSpeed;			/*��С�ٶ�*/	
                
                void (*SetSpeed)(short speed);    /*�����ٶ�*/
		void (*SetPwm)(short duty);	/*�趨ռ�ձ�*/
		float (*GetActualSpeed)(void);	/*��ȡʵ���ٶ�*/

/*		PID ������			*/	
		float	Kp;							
		float   Ki;
		float	Kd;
	
                float PID_ErrorGateValue;
		float PID_Error;		 /*��ǰ���*/
		float PID_PreError;	         /*��һ�����*/
		float PID_LastError;	         /*���ϴ����*/
		float PID_Inc;	                 /*��������*/

/*			ʵ��ֵ				*/	
                short RawSpeed;                  /*ԭʼ�ٶ�(δ��һ��)*/
		float CurrentSpeed;	         /*��ǰ�ٶ�*/	
		float LastSpeed;		 /*��һ�ε��ٶ�*/
	
/*			�趨ֵ				*/
                short Speed;                     /*Ҫ���õ��ٶȣ�����UART/���������������ٶ�)*/
                short Speed_Inc;                 /*Ҫ���õ��ٶ�����������UART/���������е����ٶ�)*/
                short User_Inc;
                short Max_Speed_Inc;
//                short BoundProtect_Inc;          /*�߽籣�������Ĳ�������*/
//                short Dynamic_Inc;              /*��̬�ٶ�*/
		float TargetSpeed;		 /*Ŀ���ٶ�*/

		short PwmValue;			 /*�趨PWM*/
                
                bool PID_Lock;                  /*PID���Ʊ�־λ*/
                bool Is_Run;                    /*������б�־λ*/
                
                float Dynamic_Basic_Speed;
                float Speed_J;
                float _Speed[10];               /*��̬�ٶ�*/
                
                
                float dx;
                
                double x;    
                
                int xi;
                
                float dv;
                  
                float v;
                
                uint32_t n;
                
}motor_ctrl_t;

typedef struct
{
    bool Dynamic_Speed_Is_Run;
    bool DSpeed_Is_Run;
    bool Boundarty_Protect_Is_Run;
    bool Is_Run;
  
}_speed_ctrl_t;

typedef enum
{
                BoundProtect_state_1,          //����Ѱ��״̬
                BoundProtect_state_2          //ǰհ�����������������ѣ��������������С�������֣���
                                               //��ʱͨ��������������������������ɺ󷵻�״̬1.          
}boundarty_protect_t;

extern _speed_ctrl_t SpeedCtrl;
extern motor_ctrl_t LeftMotor;
extern motor_ctrl_t RightMotor;

extern bool using_outwayprotect;

void Dynamic_Speed();
void DSpeedCtrl();
void BoundaryProtect();

void MotorInit();
void MotorDriverInit();


void SetLeftMotorSpeed(short speed);
void SetRightMotorSpeed(short speed);

void EmergencyBrake();
void WayOutProtection();

float GetLeftMotorSpeed(void);
float GetRightMotorSpeed(void);

void LeftMotorCtrl(short duty);
void RightMotorCtrl(short duty);

extern boundarty_protect_t BoundaryProtect_State;
//extern float  Basic_Speed;
//extern float Speed_J;
//extern float _Speed[10];

#endif