#ifndef _ELEMENT_H_
#define _ELEMENT_H_

typedef enum
{
    Straight,       /*直道*/ 
    
    SmallSCurveIN,    /*小S弯道*/
    SmallSCurveOUT,   
    
    BigSCurveIN,      /*大S弯道*/ 
    BigSCurveOUT, 
    
    CurveIN,          /*普通弯道*/ 
    CurveOUT,          
    
    RoundaboutIN,     /*环岛*/ 
    RoundaboutOUT,    
    
    CrossIN,          /*十字*/
    CrossOUT,         
    
    Garage,           /*车库*/
    GarageIn,
    GarageOut,
    
    Lose,             /*无法判断*/ 
}_element_t;

typedef enum
{
  Out_State_1,//空闲
  Out_State_2,//竖直电感感值持续增加
  Out_State_3,//到达阀值后强制性打角
}_outpark_t;

typedef enum
{
    Circle_State_1,//空闲
    Circle_State_2,//感值升高
    Circle_State_3,//到达阀值
    Circle_State_4,//低于阀值
    Circle_State_5 //该状态不在入环
}_circle_t;

typedef enum
{
   Ramp_state_1,             //上坡
   Ramp_state_2,             //下坡
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
    RunBack,//正跑
    Running,//反跑
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
