#include "include.h"
#include "gyro_filter.h"

#define  ACC_X_Offset 0								//���ٶȼ�X������ƫ�ƣ��ɱ궨
#define  ACC_Y_Offset 0								//���ٶȼ�Y������ƫ�ƣ��ɱ궨
#define  ACC_Z_Offset	0							//���ٶȼ�Z������ƫ��

#define  GRY_X_Offset	0							//�����ǵ����Ư��
#define  GRY_Y_Offset	0							//�����ǵ����Ư��
#define  GRY_Z_Offset	0							//�����ǵ����Ư��

#define INV_WXYZ_QUAT       (0x100)
#define q30  1073741824.0f



float q0=1.0,q1=0.0,q2=0.0,q3=0.0;  /*��ʼ��̬��Ԫ��*/

float exInt=0.0,eyInt=0.0,ezInt=0.0; /*��ǰ�ӼƲ�õ��������ٶ��������ϵķ���*/

float ex=0.0, ey=0.0, ez=0.0;       /*���õ�ǰ��̬��������������������ϵķ��������Ļ��� ?*/

float vx, vy, vz;                     /*��ǰ��̬��������������������ϵķ���*/

#define G_Kp 2.0       /*���ڵ������ٶȼ����������ǵ��ٶ�*/
#define G_Ki 0.0001   


#define halfT (float)(1.0/2000.0)    /*�������ڵ�һ��(��λ:s)�����������Ԫ��΢�ַ���ʱ���������*/

/*
    Raw:  ax,ay,az,gx,gy,gz    -> MPU_Get_Raw_data();
    Q[4]: q0,q1,q2,q3          ->��Ԫ�� 
    E:    exInt,eyInt,ezInt    ->��ǰ���ٶȼƲ�õ��������ٶ��������ϵķ���
    G:    ex, ey ,ez           ->��ǰ�ӼƲ�õ��������ٶ��������ϵķ���
                                 ���õ�ǰ��̬��������������������ϵķ��������
          HalfT                ->T�������� ->HalfT = T/2
    V:    vx, vy, vz           ->��ǰ��̬��������������������ϵķ���
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
       
    /*��������ת��Ϊ��λ����*/
    norm = sqrt(ax*ax + ay*ay + az*az);      
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
    
    /*�����������������*/
    vx = 2*(q1*q3 - q0*q2);
    vy = 2*(q0*q1 + q2*q3);
    vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
    
    /*���������������ƫ*/
    ex = (ay*vz - az*vy) ;                                                                  
    ey = (az*vx - ax*vz) ;
    ez = (ax*vy - ay*vx) ;
    exInt = exInt + ex*G_Ki;
    eyInt = eyInt + ey*G_Ki;
    ezInt = ezInt + ez*G_Ki;

    gx = gx + G_Kp*ex + exInt;
    gy = gy + G_Kp*ey + eyInt;
    gz = gz + G_Kp*ez + ezInt;
  
    /*������Ԫ������һ��*/
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;
    
    /*��Ԫ��ת����ŷ����*/
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
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//�����м���
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//�����м���
         GYRO.Roll = -GYRO.Roll;
    }
    
    if (GYRO.Raw_Ax>0)
    {
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//�����м���
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//�����м���
         GYRO.Roll = -GYRO.Roll;
    }
    
    if (GYRO.Raw_Az>0)
    {
        GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265);		   			//�����м���
      
      
    }
    else
    {
         GYRO.Roll = atan2((float)GYRO.Acc_Y,(float)GYRO.Acc_Z)*(180/3.14159265) - 90;		   			//�����м���
         GYRO.Roll = -GYRO.Roll;
    }
  
}


//s16  temp_acc_y=0,temp_acc_z=0,temp_Gry_x=0,temp_Gry_z=0;				   	         //��������м����������������Ϊ���ε�
//float  Acc_angle=0,Gry_vivi=0,Gyro_z;;												//���ٶȵ���Ǽ���ó��Ľ��Ϊ�������ͣ�
//float  anglexxx,gyy,angyy;
//
////*****һ���˲�************
//float angle_m;
//float gyro_m;
//float dt;
//float K1=0.05;
//float angle6; 
//
///*****kalmanfilter********/
//float angle,Gyro_x,angle_dot;         //С���˲�����б�Ƕ�/���ٶ�	
//float gyx;
//float anglex;
////******����������************
//		
//float  Q_angle=0.001;  
//float  Q_gyro=0.003;
//float  R_angle=0.5;
//float  dt=0.005;	                  //dtΪkalman�˲�������ʱ��;
//char   C_0 = 1;
//float  Q_bias, Angle_err;
//float  PCt_0=0, PCt_1=0, E=0;
//float  K_0=0, K_1=0, t_0=0, t_1=0;
//float  Pdot[4] ={0,0,0,0};
//float  PP[2][2] = { { 1, 0 },{ 0, 1 } };
//int x,y1,z1,y2,z2,flagbt;
//
////���Ư���벹��//
//#define  ACC_Y_offset 0															//���ٶȼ�Y������ƫ�ƣ��ɱ궨
//#define  ACC_Z_offset	0														   //���ٶȼ�Z������ƫ��
//#define  GRY_X_offset	0														//�����ǵ����Ư��
//		
//
//
//void Balance_filter()
//{
//   temp_Gry_x = GYRO.Ax+ GRY_X_offset;									//��ȡ������X�����ݼĴ������õ����������ݣ�16λ�Ķ����Ʋ��룩��
//   Gry_vivi =((float)temp_Gry_x)*(0.0304878);  
//  
//   count_Acc_angle();	//������ٶȼƵ����ֵ																					 //��ȡ�����ǵ�ֵ
////	 anglestop();
//   kalmanfilter(Gry_vivi,Acc_angle);														 //�������˲�
//} 
////�����м������ֵ
//void count_Acc_angle()																									//�������
//{
////        GYRO.Acc_X = GYRO.Ax+ACC_X_offset;
//        temp_acc_y = GYRO.Ay+ACC_Y_offset;
//        temp_acc_z = GYRO.Az+ACC_Z_offset;
//        
//        
//        if(temp_acc_y>0)
//	{
//		Acc_angle = atan2((float)temp_acc_y,(float)temp_acc_z)*(180/3.14159265);		   			//�����м���
//
//	}
//		else
//	{
//                Acc_angle = atan2((float)temp_acc_z,(float)temp_acc_y)*(180/3.14159265)-90;				//�����м���
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
//	angle+=(Gyro - Q_bias) * dt; //�������
//	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��
//
//	Pdot[1]=-PP[1][1];
//	Pdot[2]=-PP[1][1];
//	Pdot[3]=Q_gyro;
//	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
//	PP[0][1] += Pdot[1] * dt;   // =����������Э����
//	PP[1][0] += Pdot[2] * dt;
//	PP[1][1] += Pdot[3] * dt;
//		
//	Angle_err = Accel - angle;	//zk-�������
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
//	PP[0][0] -= K_0 * t_0;		 //����������Э����
//	PP[0][1] -= K_0 * t_1;
//	PP[1][0] -= K_1 * t_0;
//	PP[1][1] -= K_1 * t_1;
//		
//	angle	+= K_0 * Angle_err;	 //�������
//	Q_bias	+= K_1 * Angle_err;	 //�������
//	angle_dot   = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
//        GYRO.Angle_X = (short)angle_dot;
// }


//void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)//g�������ǣ�a��Ӽ�
//{
//
//  float q0temp,q1temp,q2temp,q3temp;//��Ԫ���ݴ���������΢�ַ���ʱҪ��
//  float norm; //ʸ����ģ����Ԫ���ķ���
//  float vx, vy, vz;//��ǰ��̬��������������������ϵķ���
//  float ex, ey, ez;//��ǰ�ӼƲ�õ��������ٶ��������ϵķ���
//              //���õ�ǰ��̬��������������������ϵķ��������
//
//  // �Ȱ���Щ�õõ���ֵ���
//  float q0q0 = q0*q0;
//  float q0q1 = q0*q1;
//  float q0q2 = q0*q2;
//  float q1q1 = q1*q1;
//  float q1q3 = q1*q3;
//  float q2q2 = q2*q2;
//  float q2q3 = q2*q3;
//  float q3q3 = q3*q3;      
//  if(ax*ay*az==0)//�Ӽƴ�����������״̬ʱ��������̬���㣬��Ϊ�������ĸ���������
//        return;
//  norm = sqrt(ax*ax + ay*ay + az*az);//��λ�����ٶȼƣ�
//  ax = ax /norm;// �������������Ҳ����Ҫ�޸�KP��������Ϊ�����һ����
//  ay = ay / norm;
//  az = az / norm;
//  //�õ�ǰ��̬������������������ϵķ�����
//  //�ο�����nϵת������������bϵ������Ԫ����ʾ�ķ������Ҿ�������м��ǣ�����һ�����ᵽ��
//  vx = 2*(q1q3 - q0q2);        
//  vy = 2*(q0q1 + q2q3);
//  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
//  //�����õ������������������������������Ա�ʾ��һ���
//  //ԭ�����������Ϊ���������ǵ�λ������sin0����0
//  //����Ҫ�Ǽн���180����~�����û���
//  ex = (ay*vz - az*vy) ;                                                                  
//  ey = (az*vx - ax*vz) ;
//  ez = (ax*vy - ay*vx) ;
//
//  exInt = exInt + ex * G_Ki;                                           //�������л���
//  eyInt = eyInt + ey * G_Ki;
//  ezInt = ezInt + ez * G_Ki;
//  // adjusted gyroscope measurements
//  gx = gx + G_Kp*ex + exInt;  //�����PI�󲹳��������ǣ����������Ư��
//  gy = gy + G_Kp*ey + eyInt;
//  gz = gz + G_Kp*ez + ezInt;    //�����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�
//  //���������̬�ĸ��£�Ҳ������Ԫ��΢�ַ��̵����
//  q0temp=q0;//�ݴ浱ǰֵ���ڼ���
//  q1temp=q1;//���ϴ�������㷨���û��ע��������⣬�ڴ˸���
//  q2temp=q2;
//  q3temp=q3;
//  //����һ�ױϿ��ⷨ�����֪ʶ�ɲμ���������������Ե���ϵͳ��P212
//  q0 = q0temp + (-q1temp*gx - q2temp*gy -q3temp*gz)*halfT;
//  q1 = q1temp + (q0temp*gx + q2temp*gz -q3temp*gy)*halfT;
//  q2 = q2temp + (q0temp*gy - q1temp*gz +q3temp*gx)*halfT;
//  q3 = q3temp + (q0temp*gz + q1temp*gy -q2temp*gx)*halfT;
//  //��λ����Ԫ���ڿռ���תʱ�������죬������ת�Ƕȣ����������Դ�����������任
//  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
//  q0 = q0 / norm;
//  q1 = q1 / norm;
//  q2 = q2 / norm;
//  q3 = q3 / norm;
//  //��Ԫ����ŷ���ǵ�ת������ʽ�Ƶ�������һ
//  //����YAW��������ڼ��ٶȼƶ���û���������ã���˴˴�ֱ���������ǻ��ִ���
//  GYRO.Yaw = GYRO.Angle_Z; // yaw
//  GYRO.Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)*57.3; // pitch
//  GYRO.Roll = atan2(2 * q2 * q3 + 2 * q0 * q1,-2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
//}

