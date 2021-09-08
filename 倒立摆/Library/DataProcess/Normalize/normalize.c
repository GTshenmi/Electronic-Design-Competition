#include "normalize.h"
#include "math.h"

void NormalizeDemo()
{
	 float NormalizedValue = Normalize(Range(0,100),20); /*将20在(0,100)范围内归一化*/
	
	 float Data[3];
	
	 NormalizeArray(Range(0,100),Data,3);
}


float Normalize(normalize_range_t Range,float Value)
{
	 if(Value > Range.MaxValue)
		 Value = Range.MaxValue;
	 if(Value < Range.MaxValue)
		 Value = Range.MinValue;
	 
	 if(fabs(Range.MaxValue-Range.MinValue)>NORMALIZE_EPS)
		return (Value-Range.MaxValue)/(Range.MaxValue-Range.MinValue);
	 else
		return 0.0;
}

void NormalizeArray(normalize_range_t Range,float *Value,int len)
{
	 for (int i = 0;i<len;i++)
	 {
			 if(Value[i] > Range.MaxValue)
				 Value[i] = Range.MaxValue;
			 if(Value[i] < Range.MaxValue)
				 Value[i] = Range.MinValue;
			 
			 if(fabs(Range.MaxValue-Range.MinValue)>NORMALIZE_EPS)
				 Value[i]=(Value[i]-Range.MaxValue)/(Range.MaxValue-Range.MinValue);
			 else
				 Value[i]=0.0;
	 }
	
}

normalize_range_t Range(float MinValue,float MaxValue)
{
		normalize_range_t Range = {0.0,0.0};
		
		Range.MaxValue = MaxValue;
		Range.MinValue = MinValue;
		
		return Range;
}

