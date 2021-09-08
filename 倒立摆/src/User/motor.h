#ifndef _MOTOR_H_
#define _MOTOR_H_

#define MOTOR_CTRL_FIN_CALLBACK_EN 1
#define MOTOR_DATAPROCESS_FIN_CALLBACK_EN 0
#define MOTOR_CTRLSTRATEGY_EN 1
#define MOTOR_DATAPROCESS_EN 1

#define MOTOR0_PWMFTM FTM0
#define MOTOR1_PWMFTM FTM0
#define MOTOR2_PWMFTM FTM0
#define MOTOR3_PWMFTM FTM0

#define MOTOR0_PWMFTM_CH {FTM_CH0,FTM_CH1}
#define MOTOR1_PWMFTM_CH {FTM_CH2,FTM_CH3}
#define MOTOR2_PWMFTM_CH {FTM_CH0,FTM_CH1}
#define MOTOR3_PWMFTM_CH {FTM_CH2,FTM_CH3}

#define MOTOR0_PWMFTM_FREQ 300
#define MOTOR1_PWMFTM_FREQ 300
#define MOTOR2_PWMFTM_FREQ 300
#define MOTOR3_PWMFTM_FREQ 300

#define MOTOR0_ENCFTM FTM2
#define MOTOR1_ENCFTM FTM2
#define MOTOR2_ENCFTM FTM2
#define MOTOR3_ENCFTM FTM2


#define LeftMotor Motor[0]
#define RightMotor Motor[1]

typedef struct
{
    int16_t Max;
    int16_t Min;
    
}limit_t;

typedef enum
{
   SpeedCtrl,PositionCtrl,
}motor_ctrltype_t;

typedef struct
{    
    FTM_Type *PwmFTM[2]; 
    FTM_CHn_e PwmChannel[2]; 
    
    FTM_Type *ENCFTM; 
    FTM_CHn_e ENCFTMChannel;    
    
    short PwmFreq;      
    
    motor_ctrltype_t CtrlType;
      
    limit_t ParameterLimit;           
    
    limit_t PwmLimit;              /*
                                     * Pwm极限值：
                                     * 赋值：√
                                     * 使用：√
                                     *                  */   
    
}motor_handle_t;



typedef struct
{
     
     motor_handle_t Handle;   
     
#if MOTOR_CTRLSTRATEGY_EN
      short (*CtrlStrategy)(short);     
#endif

#if MOTOR_CTRL_FIN_CALLBACK_EN
      void (*CtrlFinishCallBack)(void); 
#endif

#if MOTOR_DATAPROCESS_EN
      short (*DataProcess)(short);     
#endif

#if MOTOR_DATAPROCESS_FIN_CALLBACK_EN
      void (*DataProcessFinishCallBack)(void); 
#endif

     short TargetValue;		       
     short TargetValue_Inc;
      
     short CurrentValue;	       
     short (*GetActualValue)();         
    
     short PwmValue;			
                
     bool Is_Run;                     
     
}motor_ctrl_t;

extern motor_ctrl_t Motor[4];

void MotorInit(motor_ctrl_t *Motor);
void MotorCreateHandle(motor_ctrl_t *Motor,motor_handle_t *handle);

void SetMotorParameter(motor_ctrl_t *Motor,short value);
short GetMotorParameter(motor_ctrl_t *Motor);

void SetMotorPwmDuty(motor_ctrl_t *Motor,short duty);

#endif