#ifndef _ELEMENT_H_
#define _ELEMENT_H_

typedef enum
{
    Straight,       /*ֱ��*/ 
    
    SmallSCurveIN,    /*СS���*/
    SmallSCurveOUT,   
    
    BigSCurveIN,      /*��S���*/ 
    BigSCurveOUT, 
    
    CurveIN,          /*��ͨ���*/ 
    CurveOUT,          
    
    RoundaboutIN,     /*����*/ 
    RoundaboutOUT,    
    
    CrossIN,          /*ʮ��*/
    CrossOUT,         
    
    Garage,           /*����*/
    GarageIn,
    GarageOut,
    
    Lose,             /*�޷��ж�*/ 
}_element_t;

typedef enum
{
  Out_State_1,//����
  Out_State_2,//��ֱ��и�ֵ��������
  Out_State_3,//���﷧ֵ��ǿ���Դ��
}_outpark_t;

typedef enum
{
    Circle_State_1,//����
    Circle_State_2,//��ֵ����
    Circle_State_3,//���﷧ֵ
    Circle_State_4,//���ڷ�ֵ
    Circle_State_5 //��״̬�����뻷
}_circle_t;

typedef enum
{
   Ramp_state_1,             //����
   Ramp_state_2,             //����
   Ramp_state_3
}_ramp_t;

typedef enum
{
   WaitingForOutGarage,
   GoStraight_Out,
   ArriveDesignatedLocation_Out,
   Turn90Degrees_Out,
   ArriveDesignatedAngle_Out,
   OutGarage_Success,
}_outgarage_t_;

typedef enum
{
   WaitingForInGarage,
   SlowDown,
   StartDetectGarage,
   IsGarage,
   GoStraight_In,   
   ArriveDesignatedLocation_In,
   Turn90Degrees_In,
   ArriveDesignatedAngle_In,
   InGarage_Success,
}_ingarage_t_;

typedef enum
{
   RisingEdge,
   FallingEdge,
   LowLevel,
   HighLevel,
   NoEdge,
   Is_Edge,
}_edge_t_;

typedef enum
{
    RunBack,//����
    Running,//����
}_run_state_t;

extern _run_state_t run_state;

#define white true
#define black false


extern _element_t Element;
extern _outgarage_t_ OutGarageState;
extern _ingarage_t_ InGarageState;

extern _circle_t Circle_State;
extern _ramp_t Ramp_State;
extern _outpark_t Out_State;
extern uint32_t Car_Run_count;


_element_t ElementDetermine(void);

bool DetectGarage();
void OutGarage();
void InGarage();

void Car_Run_Time(void);
void CircleGet(void);
void OutPark(void);

#endif
