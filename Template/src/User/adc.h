#ifndef _ADC_H_
#define _ADC_H_

#define ADC_0 ADC0
#define ADC_1 ADC0
#define ADC_2 ADC0
#define ADC_3 ADC0
#define ADC_4 ADC1
#define ADC_5 ADC1
#define ADC_6 ADC1
#define ADC_7 ADC1

#define AD0_CHANNEL ADC0_SE12
#define AD1_CHANNEL ADC0_SE13
#define AD2_CHANNEL ADC0_SE8
#define AD3_CHANNEL ADC0_SE9
#define AD4_CHANNEL ADC1_SE12
#define AD5_CHANNEL ADC1_SE13
#define AD6_CHANNEL ADC1_SE10
#define AD7_CHANNEL ADC1_SE11

#define AD0 AD[0]
#define AD1 AD[1]
#define AD2 AD[2]
#define AD3 AD[3]
#define AD4 AD[4]
#define AD5 AD[5]
#define AD6 AD[6]
#define AD7 AD[7]

#define PAD0 &AD[0]
#define PAD1 &AD[1]
#define PAD2 &AD[2]
#define PAD3 &AD[3]
#define PAD4 &AD[4]
#define PAD5 &AD[5]
#define PAD6 &AD[6]
#define PAD7 &AD[7]

typedef struct 
{
   uint32_t Max;
   uint32_t Min;
}adc_limit_t;

typedef struct
{
   ADC_Type   *ADC_n;
   ADCn_Ch_e   ADC_CH;
   ADC_nbit    Bit;
   adc_limit_t ValueLimit;
   
   bool UsingDefaultConfig;
   bool UsingFilter;
   
}adc_handle_t;

typedef struct 
{ 
     adc_handle_t Handle;
     
     uint32_t (*DataProcess)(adc_handle_t* ,uint32_t);
     
     uint32_t FilterArray[10];
     
     uint32_t ProcessedValue;/*处理后的值*/
     
     uint32_t SamplingValue;  /*采样值*/	
    
}adc_t;

extern adc_t AD[8];
extern KFP ADC_KFP;

void ADCx_Init(adc_t *ADC,adc_handle_t *handle);
void ADC_FilterInit();
void ADC_CreateDefaultHandle(adc_handle_t *handle);
void ADCCreateHandle(adc_t *ADC,adc_handle_t *handle);

uint32_t ADC_GetSampleValue(adc_t *ADC);
short ADC_GetProcessedValue(adc_t *ADC);

uint32_t ADCx_Filter(uint32_t *SampleValueArray,uint16_t len,uint32_t SampleValue);
uint32_t ADCMovingAverageFilter(uint32_t *data,unsigned short len,uint32_t newdata);

uint32_t ADC_DefaultDataProcess(adc_handle_t *handle,uint32_t data);

void ADC_Test();

#endif