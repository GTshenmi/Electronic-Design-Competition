//#include "motor_speed_ctrl.h"
//#include "include.h"
//void MotorDemo()
//{
//    float speed = 0.0;
//    
//    /*获取速度*/
//    speed = LeftMotor.SpeedCtrl.GetProcessedSpeed();
//    
//    /*设置速度方法一*/ 
//    LeftMotor.SpeedCtrl.SetSpeed((uint16_t)speed);
//    /*注:该设置方法只生效一段时间，在下次定时器中断到来后速度会被重置*/
//    
//    /*设置速度方法二*/
//    LeftMotor.SpeedCtrl.TargetSpeed = 5000;
//    LeftMotor.SpeedCtrl.TargetSpeed_Inc = 0;
//    
//}
///**
//  * @brief  左电机速度环控制策略函数
//  * @param  目标速度
//  * @retval 占空比	
//  * @attention 可编辑，不可调用
//  */
//int16_t LeftMotorSpeedCtrlStrategy(int16_t TargetValue)
//{
//    float PwmValue = TargetValue*1.0;
//    
//    
//    
//    return (int16_t)PwmValue ;
//}
///**
//  * @brief  右电机速度环控制策略函数
//  * @param  目标速度
//  * @retval 占空比		
//  * @attention 可编辑，不可调用
//  */
//int16_t RightMotorSpeedCtrlStrategy(int16_t TargetValue)
//{
//    float PwmValue = TargetValue*1.0;
//    
//    
//    return (int16_t)PwmValue ;
//}
//
///**
//  * @brief  左电机速度环数据处理函数
//  * @param  待处理数据
//  * @retval 处理后的数据	
//  * @attention 可编辑，可调用
//  */
//int16_t LeftMotorSpeedCtrlDataProcessing(int16_t speed)
//{
//    
//    return speed;
//}
//
///**
//  * @brief  左电机速度环数据处理函数
//  * @param  待处理数据
//  * @retval 处理后的数据	
//  * @attention 可编辑，可调用
//  */
//int16_t RightMotorSpeedCtrlDataProcessing(int16_t speed)
//{
//    
//    return speed;
//}
