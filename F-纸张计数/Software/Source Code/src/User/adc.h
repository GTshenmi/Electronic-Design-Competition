#ifndef _ADC_H_
#define _ADC_H_

#define ADCx ADC1

#define AD1_CHANNEL ADC1_SE11
#define AD2_CHANNEL ADC1_SE10
#define AD3_CHANNEL ADC1_SE13
#define AD4_CHANNEL ADC1_SE12
#define AD5_CHANNEL ADC1_SE15

/*����ADC:1*/
#define TEST_CAR_ADC 0 
/*��һ��:1 ��Ⱥ�:0*/
#define Normalized 0
/*ʹ���˲���*/
#define USING_FILTER 1

#define ADC_ErrorBuf_Len 10

typedef struct
{
	 uint32_t MaxValue;       /*���ֵ*/
	 uint32_t MinValue;       /*��Сֵ*/
	 uint32_t ProcessedValue;/*������ֵ*/
	 uint32_t SamplingValue;  /*����ֵ*/	
         uint32_t LastProcessedValue;
         uint32_t Error[ADC_ErrorBuf_Len];
}adc_t;

extern adc_t AD[5];

uint32_t SlidingMedianFilter(ADC_Type * adc_n,ADCn_Ch_e adc_ch,ADC_nbit bit);
void ADCx_Filter();
void ESensorInit();
void ADCx_GetProcessedValue();
void ADC_GetSampleValue();

#endif