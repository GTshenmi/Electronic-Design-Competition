#ifndef _TRIPODHEAD_H_
#define _TRIPODHEAD_H_

#include "include.h"

typedef struct
{
  steer_ctrl_t *SteerH;
  steer_ctrl_t *SteerV;
  short (*CtrlStrategy)(short*,short*);
  bool Is_Run;
  
}tripodhead_t;
void TriHeadController(tripodhead_t *TripodHead);
void TriHeadInit(tripodhead_t *TripodHead);
void SetTriHeadAngle(tripodhead_t *TripodHead,short AngleH,short AngleV);

#endif
