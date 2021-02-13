#include "task.h"


void Task_KEY_Scan()
{
  
}
_task_t_ Task = 
{
    .DoPaperCount = true,
    .KeyScan = Task_KEY_Scan,
    .IOScan = Task_IOScan,
    .LEDScan = Task_LEDScan,
    .BeepScan = Task_BeepScan,
};