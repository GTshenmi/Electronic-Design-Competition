//#include "motor_speed_ctrl.h"
//#include "include.h"
//void MotorDemo()
//{
//    float speed = 0.0;
//    
//    /*��ȡ�ٶ�*/
//    speed = LeftMotor.SpeedCtrl.GetProcessedSpeed();
//    
//    /*�����ٶȷ���һ*/ 
//    LeftMotor.SpeedCtrl.SetSpeed((uint16_t)speed);
//    /*ע:�����÷���ֻ��Чһ��ʱ�䣬���´ζ�ʱ���жϵ������ٶȻᱻ����*/
//    
//    /*�����ٶȷ�����*/
//    LeftMotor.SpeedCtrl.TargetSpeed = 5000;
//    LeftMotor.SpeedCtrl.TargetSpeed_Inc = 0;
//    
//}
///**
//  * @brief  �����ٶȻ����Ʋ��Ժ���
//  * @param  Ŀ���ٶ�
//  * @retval ռ�ձ�	
//  * @attention �ɱ༭�����ɵ���
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
//  * @brief  �ҵ���ٶȻ����Ʋ��Ժ���
//  * @param  Ŀ���ٶ�
//  * @retval ռ�ձ�		
//  * @attention �ɱ༭�����ɵ���
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
//  * @brief  �����ٶȻ����ݴ�����
//  * @param  ����������
//  * @retval ����������	
//  * @attention �ɱ༭���ɵ���
//  */
//int16_t LeftMotorSpeedCtrlDataProcessing(int16_t speed)
//{
//    
//    return speed;
//}
//
///**
//  * @brief  �����ٶȻ����ݴ�����
//  * @param  ����������
//  * @retval ����������	
//  * @attention �ɱ༭���ɵ���
//  */
//int16_t RightMotorSpeedCtrlDataProcessing(int16_t speed)
//{
//    
//    return speed;
//}
