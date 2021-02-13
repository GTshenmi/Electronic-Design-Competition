#ifndef _TASK_H_
#define _TASK_H_

#include "include.h"

typedef struct
{
   bool DoPaperCount;
   void (*KeyScan)();
   void (*IOScan)();
   void (*LEDScan)();
   void (*BeepScan)();
}_task_t_;


extern _task_t_ Task;

#endif