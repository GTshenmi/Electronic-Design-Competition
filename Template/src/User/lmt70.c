#include "include.h"
#include "lmt70.h"

#define USING_FITTING_FUNCTION 1

void LMT70DefaultInit()
{
    adc_handle_t handle;
    
    
    ADC_CreateDefaultHandle(&handle);
    handle.UsingDefaultConfig = false;
    handle.UsingFilter = true;
    handle.Bit = ADC_16bit;
    handle.ValueLimit.Max = 65535;
    handle.ValueLimit.Min = 0;

    
    
    ADCx_Init(LMT70.ADC,&handle);
}

uint32_t LMT70GetADCValue()
{       
    return (ADC_GetProcessedValue(LMT70.ADC));
}


float LMT70BinarySearch(float *Array,unsigned int len,float value)
{
     unsigned int low = 0;
     unsigned int high = len;
     unsigned int mid = len/2;
                                   /*      low               mid                  high
                                      index 0        1        2           3        4
                                      Array 5        4        3           2        1   */
     for(int i = 0;i <= len-1;i++)  
     {
        if(value >= Array[mid])
        {
            high = mid;
        }
        else if(value < Array[mid+1])
        {
            low = mid;
        }
        else
        {
            break;
        }
        
        mid = (low+high)/2;
        
        
        if(low == mid && low == high)
        {
            break;
        }
     }
     
     if(!(value >= Array[mid] && mid == 0))
       mid += 1; 
       
     return (-55.0 + 0.1*(mid));
}

float LMT70GetTemperature()
{
    float Value = LMT70GetADCValue() * 3.3*1000/65536.0;
    float temp = 0.0;
    temp = -51;
    
    if(Value > LUTThreshold01C[0])
      temp = -55;
    else if(Value < LUTThreshold01C[2051]) 
      temp = 150;
    else
    {
        uint16_t SampleValue = LMT70GetADCValue();
        
        float Value = (SampleValue * 3.3 *1000.0)/65536.0;
        
#if USING_FITTING_FUNCTION    
        

        double a= -1.064200E-09;
        double b= -5.759725E-06;
        double c= -1.789883E-01;
        double d=  2.048570E+02;

        //uint32_t time = systime.get_time_us();
        temp=a*(Value)*(Value)*(Value)+b*(Value)*(Value)+c*(Value)+d;
        //time = systime.get_time_us() - time;
        //LCD.Write.XLine(3,"Time:%d",time);
//        float stemp = LMT70BinarySearch(LUTThreshold01C,2052,Value);
//        
//        temp = stemp - temp;
        
#else
        temp = LMT70BinarySearch(LUTThreshold01C,2052,Value);
        
#endif
    }
    
    if(temp > LMT70.TempLimit.Max)
      temp = LMT70.TempLimit.Max;
    else if(temp < LMT70.TempLimit.Min)
      temp = LMT70.TempLimit.Min;
    
    return temp;
    
}

int SearchTest()
{
    uint32_t now_time;
    uint32_t now_time_us;
    int error_times = 0;
    float result = 0.0;
    uint32_t max_time = 0;
    uint32_t max_time_us = 0;
    
    for(int i = 0;i<2052;i++)
    {
        now_time_us =systime.get_time_us();
        now_time = systime.get_time_ms();
        result = LMT70BinarySearch(LUTThreshold01C,2052,LUTThreshold01C[i]);
        now_time = systime.get_time_ms() - now_time;
        now_time_us = systime.get_time_us();
        if(now_time >= max_time)
          max_time = now_time;
        
        if(now_time_us >= max_time_us)
          max_time_us = now_time_us;
          
        LCD.Write.XLine(0,"STemp:%.3f",result);
        LCD.Write.XLine(1,"RTemp:%.3f",(-55.0+(i)*0.1));
        
        if(fabs(result -(-55.0+(i)*0.1)) >= 1e-2)
        {
            error_times++;
        }
        
        LCD.Write.XLine(2,"error_time:%d",error_times);
    }
    
    if(max_time)
      LCD.Write.XLine(3,"max time:%d ms",max_time);
    else
      LCD.Write.XLine(3,"max time:%d us",max_time_us);
    
    return error_times;
  
}
void LMT70Test()
{
    LMT70DefaultInit();
    float Value = LMT70GetADCValue() * 3.3*1000/65536.0;
    //Value = 900.0;
    uint32_t ms[2] = {0,0};
    uint32_t us[2] = {0,0};
    uint32_t time = 0;
    float temp = 0.0;
    while(1)
    {
      
      if(systime.get_time_ms() - time >= 200)
      {
        time = systime.get_time_ms();
                LCD.Debug.Clear(WHITE);
      Value = LMT70GetADCValue() * 3.3*1000/65536.0;
      temp = -51;
      if(Value > LUTThreshold01C[0])
        temp= -55;
      else if(Value < LUTThreshold01C[2051]) 
        temp = 150;
      else
      {
          uint16_t SampleValue = LMT70GetADCValue();
          
          float Value = (SampleValue * 3.3 *1000.0)/65536.0;
          
          ms[1] = systime.get_time_ms();
          us[1] = systime.get_time_us();

         // LCD.Write.XLine(2,"Error Times:%d",SearchTest());
          
          //systime.delay_ms(1000);
          
          temp = LMT70BinarySearch(LUTThreshold01C,2052,Value);    
          
          ms[1] = systime.get_time_ms() - ms[1];
          us[1] = systime.get_time_us() - us[1];
          
          if(ms[1])
          {
            LCD.Write.XLine(5,"BSearch Time:%lu ms",ms[1]);
            
          }
          else
          {
            LCD.Write.XLine(5,"BSearch Time:%lu us",us[1]);
          }
      }
      if(temp != -51)
         LCD.Write.XLine(4,"Temp:%.3f C",temp);
      else
         LCD.Write.XLine(4,"Get Temp Failed.");
      
      }
    }
}
lmt70_t LMT70 = 
{
   .ADC = &AD[0], 
   .TempLimit.Max = 150,
   .TempLimit.Min = -55,
   .GetADCValue = LMT70GetADCValue,
   .BinarySearch = LMT70BinarySearch,
   .SearchTest = SearchTest,
};