#include "include.h"
#include "gyro_filter.h"

#define  ACC_X_Offset 0								//加速度计X轴的零点偏移，可标定
#define  ACC_Y_Offset 0								//加速度计Y轴的零点偏移，可标定
#define  ACC_Z_Offset	0							//加速度计Z轴的零点偏移

#define  GRY_X_Offset	0							//陀螺仪的零点漂移
#define  GRY_Y_Offset	0							//陀螺仪的零点漂移
#define  GRY_Z_Offset	0							//陀螺仪的零点漂移

#define INV_WXYZ_QUAT       (0x100)
#define q30  1073741824.0f



float q0=1.0,q1=0.0,q2=0.0,q3=0.0;  /*初始姿态四元数*/

float exInt=0.0,eyInt=0.0,ezInt=0.0; /*当前加计测得的重力加速度在三轴上的分量*/

float ex=0.0, ey=0.0, ez=0.0;       /*与用当前姿态计算得来的重力在三轴上的分量的误差的积分 ?*/

float vx, vy, vz;                     /*当前姿态计算得来的重力在三轴上的分量*/

#define G_Kp 2.0       /*用于调整加速度计修正陀螺仪的速度*/
#define G_Ki 0.0001   


#define halfT (float)(1.0/2000.0)    /*采样周期的一半(单位:s)，用于求解四元数微分方程时计算角增量*/

/*
    Raw:  ax,ay,az,gx,gy,gz    -> MPU_Get_Raw_data();
    Q[4]: q0,q1,q2,q3          ->四元数 
    E:    exInt,eyInt,ezInt    ->当前加速度计测得的重力加速度在三轴上的分量
    G:    ex, ey ,ez           ->当前加计测得的重力加速度在三轴上的分量
                                 与用当前姿态计算得来的重力在三轴上的分量的误差
          HalfT                ->T采样周期 ->HalfT = T/2
    V:    vx, vy, vz           ->当前姿态计算得来的重力在三轴上的分量
*/

void IMUupdate(float *gxi, float *gyi, float *gzi, float *axi, float *ayi, float *azi) 
{
    float ax = *axi;
    float ay = *ayi;
    float az = *azi;
    float gx = *gxi;
    float gy = *gyi;
    float gz = *gzi;
    
    
    float norm;
       
    /*传入数据转化为单位向量*/
    norm = sqrt(ax*ax + ay*ay + az*az);      
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
    
    /*计算重力的三轴分量*/
    vx = 2*(q1*q3 - q0*q2);
    vy = 2*(q0*q1 + q2*q3);
    vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
    
    /*叉积法修正陀螺零偏*/
    ex = (ay*vz - az*vy) ;                                                                  
    ey = (az*vx - ax*vz) ;
    ez = (ax*vy - ay*vx) ;
    exInt = exInt + ex*G_Ki;
    eyInt = eyInt + ey*G_Ki;
    ezInt = ezInt + ez*G_Ki;

    gx = gx + G_Kp*ex + exInt;
    gy = gy + G_Kp*ey + eyInt;
    gz = gz + G_Kp*ez + ezInt;
  
    /*整合四元数并归一化*/
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;
    
    /*四元数转换成欧拉角*/
    GYRO.Yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.3;    // yaw
    GYRO.Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;                               // pitch
    GYRO.Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
    
}
void AttitudeCalculation()
{
    Read_Acc();
    Read_Gyro();
    IMUupdate(&GYRO.Angle_X,&GYRO.Angle_Y,&GYRO.Angle_Z,&GYRO.Acc_X,&GYRO.Acc_Y,&GYRO.Acc_Z);
    //IMUupdate(GYRO.Angle_X,GYRO.Angle_Y,GYRO.Angle_Z,GYRO.Acc_X,GYRO.Acc_Y,GYRO.Acc_Z);
}
void Read_Acc()
{
    MPU_Get_Accelerometer(&GYRO.Raw_Ax,&GYRO.Raw_Ay,&GYRO.Raw_Az);
    GYRO.Acc_X = GYRO.Raw_Ax;
    GYRO.Acc_Y = GYRO.Raw_Ay;
    GYRO.Acc_Z = GYRO.Raw_Az; 
}
void Read_Gyro()
{
    MPU_Get_Gyroscope(&GYRO.Raw_Gx,&GYRO.Raw_Gy,&GYRO.Raw_Gz);
    GYRO.Angle_X = GYRO.Raw_Gx*0.001064;
    GYRO.Angle_Y = GYRO.Raw_Gy*0.001064;
    GYRO.Angle_Z = GYRO.Raw_Gz*0.001064; 
}

void CalculateAccAngle()
{
    Read_Acc();
    if (GYRO.Raw_Ay>0)
    {
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//反正切计算
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//反正切计算
         GYRO.Roll = -GYRO.Roll;
    }
    
    if (GYRO.Raw_Ax>0)
    {
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//反正切计算
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//反正切计算
         GYRO.Roll = -GYRO.Roll;
    }
    
    if (GYRO.Raw_Az>0)
    {
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//反正切计算
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//反正切计算
         GYRO.Roll = -GYRO.Roll;
    }
  
}


//s16  temp_acc_y=0,temp_acc_z=0,temp_Gry_x=0,temp_Gry_z=0;				   	         //计算倾角中间变量，读出的数据为整形的
//float  Acc_angle=0,Gry_vivi=0,Gyro_z;;												//加速度的倾角计算得出的结果为浮点类型；
//float  anglexxx,gyy,angyy;
//
////*****一阶滤波************
//float angle_m;
//float gyro_m;
//float dt;
//float K1=0.05;
//float angle6; 
//
///*****kalmanfilter********/
//float angle,Gyro_x,angle_dot;         //小车滤波后倾斜角度/角速度	
//float gyx;
//float anglex;
////******卡尔曼参数************
//		
//float  Q_angle=0.001;  
//float  Q_gyro=0.003;
//float  R_angle=0.5;
//float  dt=0.005;	                  //dt为kalman滤波器采样时间;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0=0, PCt_1=0, E=0;
//float  K_0=0, K_1=0, t_0=0, t_1=0;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//int x,y1,z1,y2,z2,flagbt;
//
////零点漂移与补偿//
//#define  ACC_Y_offset 0															//加速度计Y轴的零点偏移，可标定
//#define  ACC_Z_offset	0														   //加速度计Z轴的零点偏移
//#define  GRY_X_offset	0														//陀螺仪的零点漂移
//		
//
//
//void Balance_filter()
//{
//   temp_Gry_x = GYRO.Ax+ GRY_X_offset;									//读取陀螺仪X轴数据寄存器，得到陀螺仪数据（16位的二进制补码）；
//   Gry_vivi =((float)temp_Gry_x)*(0.0304878);  
//  
//   count_Acc_angle();	//计算加速度计的倾角值																					 //读取陀螺仪的值
////	 anglestop();
//   kalmanfilter(Gry_vivi,Acc_angle);														 //卡尔曼滤波
//} 
////反正切计算倾角值
//void count_Acc_angle()																									//计算倾角
//{
////        GYRO.Acc_X = GYRO.Ax+ACC_X_offset;
//        temp_acc_y = GYRO.Ay+ACC_Y_offset;
//        temp_acc_z = GYRO.Az+ACC_Z_offset;
//        
//        
//        if(temp_acc_y>0)
//	{
//		Acc_angle = atan2((float)temp_acc_y,(float)temp_acc_z)*(180/3.14159265);		   			//反正切计算
//
//	}
//		else
//	{
//                Acc_angle = atan2((float)temp_acc_z,(float)temp_acc_y)*(180/3.14159265)-90;				//反正切计算
//		Acc_angle = -Acc_angle;
//	}
//	
//
//}
//
//void Yiorderfilter()
//{
//  angle6 = K1 * angle_m + (1 - K1) * (angle6 + gyro_m * dt);
//}
//
//void kalmanfilter(float Gyro,float Accel)
// {
//	 
//	angle+=(Gyro - Q_bias) * dt; //先验估计
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//	Pdot[1]=-PP[1][1];
//	Pdot[2]=-PP[1][1];
//	Pdot[3]=Q_gyro;
//	PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//	PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - angle;	//zk-先验估计
//	
//	PCt_0 = C_0 * PP[0][0];
//	PCt_1 = C_0 * PP[1][0];
//	
//	E = R_angle + C_0 * PCt_0;
//	
//	K_0 = PCt_0 / E;
//	K_1 = PCt_1 / E;
//	
//	t_0 = PCt_0;
//	t_1 = C_0 * PP[0][1];
//
//	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	angle	+= K_0 * Angle_err;	 //后验估计
//	Q_bias	+= K_1 * Angle_err;	 //后验估计
//	angle_dot   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
//        GYRO.Angle_X = (short)angle_dot;
// }


//void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)//g表陀螺仪，a表加计
//{
//
//  float q0temp,q1temp,q2temp,q3temp;//四元数暂存变量，求解微分方程时要用
//  float norm; //矢量的模或四元数的范数
//  float vx, vy, vz;//当前姿态计算得来的重力在三轴上的分量
//  float ex, ey, ez;//当前加计测得的重力加速度在三轴上的分量
//              //与用当前姿态计算得来的重力在三轴上的分量的误差
//
//  // 先把这些用得到的值算好
//  float q0q0 = q0*q0;
//  float q0q1 = q0*q1;
//  float q0q2 = q0*q2;
//  float q1q1 = q1*q1;
//  float q1q3 = q1*q3;
//  float q2q2 = q2*q2;
//  float q2q3 = q2*q3;
//  float q3q3 = q3*q3;      
//  if(ax*ay*az==0)//加计处于自由落体状态时不进行姿态解算，因为会产生分母无穷大的情况
//        return;
//  norm = sqrt(ax*ax + ay*ay + az*az);//单位化加速度计，
//  ax = ax /norm;// 这样变更了量程也不需要修改KP参数，因为这里归一化了
//  ay = ay / norm;
//  az = az / norm;
//  //用当前姿态计算出重力在三个轴上的分量，
//  //参考坐标n系转化到载体坐标b系的用四元数表示的方向余弦矩阵第三列即是（博文一中有提到）
//  vx = 2*(q1q3 - q0q2);        
//  vy = 2*(q0q1 + q2q3);
//  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
//  //计算测得的重力与计算得重力间的误差，向量外积可以表示这一误差
//  //原因我理解是因为两个向量是单位向量且sin0等于0
//  //不过要是夹角是180度呢~这个还没理解
//  ex = (ay*vz - az*vy) ;                                                                  
//  ey = (az*vx - ax*vz) ;
//  ez = (ax*vy - ay*vx) ;
//
//  exInt = exInt + ex * G_Ki;                                           //对误差进行积分
//  eyInt = eyInt + ey * G_Ki;
//  ezInt = ezInt + ez * G_Ki;
//  // adjusted gyroscope measurements
//  gx = gx + G_Kp*ex + exInt;  //将误差PI后补偿到陀螺仪，即补偿零点漂移
//  gy = gy + G_Kp*ey + eyInt;
//  gz = gz + G_Kp*ez + ezInt;    //这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减
//  //下面进行姿态的更新，也就是四元数微分方程的求解
//  q0temp=q0;//暂存当前值用于计算
//  q1temp=q1;//网上传的这份算法大多没有注意这个问题，在此更正
//  q2temp=q2;
//  q3temp=q3;
//  //采用一阶毕卡解法，相关知识可参见《惯性器件与惯性导航系统》P212
//  q0 = q0temp + (-q1temp*gx - q2temp*gy -q3temp*gz)*halfT;
//  q1 = q1temp + (q0temp*gx + q2temp*gz -q3temp*gy)*halfT;
//  q2 = q2temp + (q0temp*gy - q1temp*gz +q3temp*gx)*halfT;
//  q3 = q3temp + (q0temp*gz + q1temp*gy -q2temp*gx)*halfT;
//  //单位化四元数在空间旋转时不会拉伸，仅有旋转角度，这类似线性代数里的正交变换
//  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
//  q0 = q0 / norm;
//  q1 = q1 / norm;
//  q2 = q2 / norm;
//  q3 = q3 / norm;
//  //四元数到欧拉角的转换，公式推导见博文一
//  //其中YAW航向角由于加速度计对其没有修正作用，因此此处直接用陀螺仪积分代替
//  GYRO.Yaw = GYRO.Angle_Z; // yaw
//  GYRO.Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)*57.3; // pitch
//  GYRO.Roll = atan2(2 * q2 * q3 + 2 * q0 * q1,-2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
//}

