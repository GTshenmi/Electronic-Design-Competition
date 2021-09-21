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

/*测试电机:1*/
#define TEST_CAR_MOTOR 0

#define dt ((float)(MotorInterruptInterval/1000.0))

#define pulse_per_cycle ((float)(512*68/30))

#define dw 0.064      
#define pi 3.1415926

#define Px ((float)(pi*dw/pulse_per_cycle)) /*系数*/

#define intergal_error 0.1667841432

#define track_length 45.3265491901

#define intergal_error_rate ((float)((intergal_error)/(track_length)))  //0.0036796126


typedef struct
{
		short MaxSpeed;			/*最大速度*/
		short MinSpeed;			/*最小速度*/	
                
                void (*SetSpeed)(short speed);    /*设置速度*/
		void (*SetPwm)(short duty);	/*设定占空比*/
		float (*GetActualSpeed)(void);	/*获取实际速度*/

/*		PID 控制器			*/	
		float	Kp;							
		float   Ki;
		float	Kd;
	
                float PID_ErrorGateValue;
		float PID_Error;		 /*当前误差*/
		float PID_PreError;	         /*上一次误差*/
		float PID_LastError;	         /*上上次误差*/
		float PID_Inc;	                 /*调整增量*/

/*			实际值				*/	
                short RawSpeed;                  /*原始速度(未归一化)*/
		float CurrentSpeed;	         /*当前速度*/	
		float LastSpeed;		 /*上一次的速度*/
	
/*			设定值				*/
                short Speed;                     /*要设置的速度（用于UART/其他函数中设置速度)*/
                short Speed_Inc;                 /*要设置的速度增量（用于UART/其他函数中调整速度)*/
                short User_Inc;
                short Max_Speed_Inc;
//                short BoundProtect_Inc;          /*边界保护产生的差速增量*/
//                short Dynamic_Inc;              /*动态速度*/
		float TargetSpeed;		 /*目标速度*/

		short PwmValue;			 /*设定PWM*/
                
                bool PID_Lock;                  /*PID控制标志位*/
                bool Is_Run;                    /*电机运行标志位*/
                
                float Dynamic_Basic_Speed;
                float Speed_J;
                float _Speed[10];               /*动态速度*/
                
                
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
                BoundProtect_state_1,          //正常寻迹状态
                BoundProtect_state_2          //前瞻超出赛道，过弯困难（常在连续急弯和小环岛出现），
                                               //此时通过增大电机差速来调整。调整完成后返回状态1.          
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