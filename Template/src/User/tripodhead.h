#ifndef _TRIPODHEAD_H_
#define _TRIPODHEAD_H_

#define TRIHEAD_DATA_PROCESS_EN 1
#define TRIHEAD_CTRL_STRATEGY_EN 1

typedef struct
{
  steer_ctrl_t *SteerH;
  steer_ctrl_t *SteerV;
#if TRIHEAD_CTRL_STRATEGY_EN
  short (*CtrlStrategy)(short*,short*);
#endif
  
#if TRIHEAD_DATA_PROCESS_EN  
  short (*DataProcess)(short*,short*);
#endif
  
  bool Is_Run;
  
}tripodhead_t;

extern tripodhead_t TripodHead;

void TriHeadController(tripodhead_t *TripodHead,short AngleH,short AngleV);
void TriHeadInit(tripodhead_t *TripodHead,steer_ctrl_t *SteerH,steer_ctrl_t *SteerV);
void SetTriHeadAngle(tripodhead_t *TripodHead,short AngleH,short AngleV);

void TriHeadTest();
#endif
