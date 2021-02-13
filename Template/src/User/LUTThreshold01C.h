#ifndef __LUTTHRESHOLD01C_H__
#define __LUTTHRESHOLD01C_H__

//LUTThreshold[0]为-55对应的传感器电压值，
//LUTThreshold[1]~LUTThreshold[2050]为-55~150度的
//0.1精度中两邻两度中间阈值
//LUTThreshold[0为-55度对应的传感器电压值，
//LUTThreshold[2051]为150度对应的传感器电压值，
extern float LUTThreshold01C[2052];
extern float LUT1C[206];

#endif