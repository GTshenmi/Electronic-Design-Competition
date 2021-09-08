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

#define AD0_CHANNEL ADC1_SE9
#define AD1_CHANNEL ADC1_SE8
#define AD2_CHANNEL ADC1_SE13
#define AD3_CHANNEL ADC1_SE12
#define AD4_CHANNEL ADC1_SE11
#define AD5_CHANNEL ADC1_SE10
#define AD6_CHANNEL ADC1_SE13
#define AD7_CHANNEL ADC1_SE12

/*测试ADC:1*/
#define TEST_ADC 0 

#define Normalized 1
/*使用滤波器*/
#define USING_FILTER 1
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
   
}adc_handle_t;

typedef struct
{ 
     adc_handle_t Handle;
     
     uint32_t ProcessedValue;/*处理后的值*/
     
     uint32_t SamplingValue;  /*采样值*/	
}adc_t;

extern adc_t AD[8];

void ADCx_Init(adc_t *ADC);
void ADCCreateHandle(adc_t *ADC,adc_handle_t *handle);
uint32_t ADC_GetSampleValue(adc_t *ADC);
short ADC_GetProcessedValue(adc_t *ADC);
uint32_t ADCSlidingMedianFilter(uint32_t SampleValue[][3]);

//uint32_t ADCSlidingMedianFilter(ADC_Type * adc_n,ADCn_Ch_e adc_ch,ADC_nbit bit);
//void ADCx_Filter();
//void ADCx_Init();
//void ADCx_GetProcessedValue();
//void ADC_GetSampleValue();

#endif