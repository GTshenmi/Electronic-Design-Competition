#ifndef _MOTOR_H_
#define _MOTOR_H_

#define MOTOR_CTRL_FIN_CALLBACK_EN 0
#define MOTOR_DATAPROCESS_FIN_CALLBACK_EN 0
#define MOTOR_CTRLSTRATEGY_EN 1
#define MOTOR_DATAPROCESS_EN 1

#define MOTOR0_PWMFTM {FTM0,FTM0}
#define MOTOR1_PWMFTM {FTM0,FTM0}
#define MOTOR2_PWMFTM {FTM0,FTM0}
#define MOTOR3_PWMFTM {FTM0,FTM0}

#define MOTOR0_PWMFTM_CH {FTM_CH0,FTM_CH1}
#define MOTOR1_PWMFTM_CH {FTM_CH2,FTM_CH3}
#define MOTOR2_PWMFTM_CH {FTM_CH7,FTM_CH5}
#define MOTOR3_PWMFTM_CH {FTM_CH4,FTM_CH6}

#define MOTOR0_PWMFTM_FREQ 10000
#define MOTOR1_PWMFTM_FREQ 10000
#define MOTOR2_PWMFTM_FREQ 10000
#define MOTOR3_PWMFTM_FREQ 10000

#define MOTOR0_ENCFTM FTM2
#define MOTOR1_ENCFTM FTM1
#define MOTOR2_ENCFTM FTM2
#define MOTOR3_ENCFTM FTM2


#define LeftMotor Motor[0]
#define RightMotor Motor[1]

#define motor_limit_t int16_limit_t

#define Motor0 Motor[0]
#define Motor1 Motor[1]
#define Motor2 Motor[2]
#define Motor3 Motor[3]

#define PMotor0 &Motor[0]
#define PMotor1 &Motor[1]
#define PMotor2 &Motor[2]
#define PMotor3 &Motor[3]

typedef enum
{
   SpeedCtrl,PositionCtrl,
}motor_ctrltype_t;

typedef struct
{    
    FTM_Type *PwmFTM[2];
    FTM_Type *ENCFTM; 
    
    FTM_CHn_e PwmChannel[2]; 
    FTM_CHn_e ENCFTMChannel;    
      
    motor_limit_t ParameterLimit;           
    
    motor_limit_t PwmLimit;   
    
    short PwmValue;
    short PwmFreq;      
    
    motor_ctrltype_t CtrlType;
    
    bool UsingFeedBack;
    
    bool UsingDefaultConfig;
    
}motor_handle_t;



typedef struct
{
     
     motor_handle_t Handle;   
     
#if MOTOR_CTRLSTRATEGY_EN
     short (*CtrlStrategy)(motor_handle_t*,short);     
#endif
#if MOTOR_DATAPROCESS_EN
     short (*DataProcess)(motor_handle_t*,short);     
#endif
      
#if MOTOR_CTRL_FIN_CALLBACK_EN
     void (*CtrlFinishCallBack)(motor_handle_t*); 
#endif

#if MOTOR_DATAPROCESS_FIN_CALLBACK_EN
     void (*DataProcessFinishCallBack)(motor_handle_t*); 
#endif

     short (*GetActualValue)(motor_handle_t* handle); 
     
     short TargetValue;		       
     short TargetValue_Inc;
      
     short CurrentValue;	               		
                
     bool Is_Run;                     
     
}motor_ctrl_t;

extern motor_ctrl_t Motor[4];

void MotorInit(motor_ctrl_t *Motor,motor_handle_t *handle);
void MotorCreateDefaultHandle(motor_handle_t *handle);
void MotorCreateHandle(motor_ctrl_t *Motor,motor_handle_t *handle);

void SetMotorParameter(motor_ctrl_t *Motor,short value);
short GetMotorParameter(motor_ctrl_t *Motor);

void SetMotorPwmDuty(motor_ctrl_t *Motor,short duty);

short Motor_DefaultCtrl(motor_handle_t* handle,short value);
short Motor_DefaultDataProcess(motor_handle_t *handle,short value);

#if MOTOR_CTRL_FIN_CALLBACK_EN
void Motor_DefaultCtrlFinishCallBack();
#endif
#if MOTOR_DATAPROCESS_FIN_CALLBACK_EN
void Motor_DefaultDataProcessFinishCallBack();
#endif

short Motor_DefaultGetValue();

void MotorTest();
    
#endif