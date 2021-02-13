#include "include.h"
#include "init.h"

void UARTxInit()
{
      uart_handle_t handle;
      
      UARTxCreateDefaultHandle(&handle);
      UARTx_Init(&uart[1],&handle);

      uart[1].ReceiveLen = 12;
      NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
      NVIC_EnableIRQ(UART4_RX_TX_IRQn);
}
void ADCxInit()
{
    adc_handle_t handle;
    
    handle.UsingDefaultConfig = true;
    
    for(int i = 0;i<8;i++)
      ADCx_Init(&AD[i],&handle);

}
void TempSensorInit()
{
    adc_handle_t handle;
    
    
    ADC_CreateDefaultHandle(&handle);
//    handle.UsingDefaultConfig = false;
//    handle.UsingFilter = true;
    //handle.Bit = ADC_16bit;

    
    
    //ADCx_Init(LMT70.ADC,&handle);
}
void SteerxInit()
{
    steer_handle_t handle;
    
    handle.UsingDefaultConfig = true;

    SteerInit(&Steer[0],&handle);
    SteerInit(&Steer[1],&handle);
    SteerInit(&Steer[2],&handle);
    SteerInit(&Steer[3],&handle);
 
}

void MotorxInit()
{
    motor_handle_t handle;
 
    MotorCreateDefaultHandle(&handle);
    
    handle.UsingDefaultConfig = false;
    handle.UsingFeedBack = true;
    handle.ParameterLimit.Max = 100;
    handle.ParameterLimit.Min = -100;
    //handle.UsingFeedBack = true;
    
    MotorInit(&Motor[0],&handle);
    
//    PID_CtrlStr = PID_Init(IncrementalPID); /*创建PID控制结构体*/
//    
//    PID_SetValue(&PID_CtrlStr,PIDValue(10.0,0.0,1.0));  /*设置PID系数*/
//	
//    PID_SetGain(&PID_CtrlStr,PIDGainValue(1.0,25.0)); /*设置输入输出增益*/
//    
//    Motor[0].CtrlStrategy = Motor0CtrlStrategy;
//    for(int i = 0;i<4;i++)
//    {
//        MotorInit(&Motor[i],&handle);
//        //SetMotorPwmDuty(&Motor[i],i*1000);
//    }
    
}
void TriHeadxInit()
{
    TriHeadInit(&TripodHead,&Steer[0],&Steer[3]);
    
    TripodHead.CtrlStrategy = TriHeadx_Ctrl;
    TripodHead.DataProcess = TriHeadx_DataProcess;
}