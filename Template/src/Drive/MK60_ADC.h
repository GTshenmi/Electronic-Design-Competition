/******************** LQ_K60_������ v1.0 ********************
 * �ļ���           ��ADC.H
 * ����             ������ADC����ģʽ
 * ��ע             ���ٷ��������޸�
 * ����             ��2015-10-16
 * ʵ��ƽ̨         ������ k60DN512Z���İ� 
 * ����             �������� 006
 * �Ա���           ��https://longqiu.taobao.com
 * �������ܳ�����Ⱥ ��202949437
*************************************************************/
#ifndef __ADC_H__
#define __ADC_H__ 
/*
                        ADC��Ӧ����
----------------ADC0--------------------ADC1---------------

      ADC0_SE8-----PTB0         ADC1_SE4a-----PTE0 
      ADC0_SE9-----PTB1         ADC1_SE5a-----PTE1 
      ADC0_SE10----PTA7         ADC1_SE6a-----PTE2 
      ADC0_SE11----PTA8         ADC1_SE7a-----PTE3 
      ADC0_SE12----PTB2         ADC1_SE8------PTB0
      ADC0_SE13----PTB3         ADC1_SE9------PTB1
      ADC0_SE14----PTC0         ADC1_SE10-----PTB4
      ADC0_SE15----PTC1         ADC1_SE11-----PTB5
                                ADC1_SE12-----PTB6
      ADC0_SE16----ADC0_SE16    ADC1_SE13-----PTB7
                                ADC1_SE14-----PTB10
      ADC0_SE17----PTE24        ADC1_SE15-----PTB11
      ADC0_SE18----PTBE25       ADC1_SE16-----ADC1_SE16
                                ADC1_SE17-----PTA17

      ADC0_DM0-----ADC0_DM0     ADC1_DM0------ADC1_DM0
      ADC0_DM1-----ADC0_DM1     ADC1_DM1------ADC1_DM1

*/

typedef enum
{
    // ---------------------------------ADC0-------------------------
    ADC0_DP0  =0,
    ADC0_DP1  =1,
    PGA0_DP   =2,        //��֧��ADC����Ҫ���� ADC PGA register ���÷Ŵ�����
    ADC0_DP3  =3,
    //����������֧��Bͨ��
    ADC0_SE4b =4,      // PTC2     ��֧������ADC
    ADC0_SE5b =5,      // PTD1     ��֧������ADC
    ADC0_SE6b =6,      // PTD5     ��֧������ADC
    ADC0_SE7b =7,      // PTD6     ��֧������ADC

    ADC0_SE8  =8,       // PTB0
    ADC0_SE9  =9,       // PTB1
    ADC0_SE10 =10,      // PTA7
    ADC0_SE11 =11,      // PTA8
    ADC0_SE12 =12,      // PTB2
    ADC0_SE13 =13,      // PTB3
    ADC0_SE14 =14,      // PTC0
    ADC0_SE15 =15,      // PTC1
    ADC0_SE16 =16,      // ADC0_SE16
    ADC0_SE17 =17,      // PTE24
    ADC0_SE18 =18,      // PTE25
    ADC0_DM0  =19,      // ADC0_DM0
    ADC0_DM1  =20,      // ADC0_DM1
    ADC0_SE21 =21,      // ����
    ADC0_SE22 =22,      // ����
    DAC0_OUT,       // DAC0��� ��֧��ADC
    RES2,           // ����
    RES3,           // ����
    Temp0_Sensor,   // Temperature Sensor,�ڲ��¶Ȳ���������ADC����
    Bandgap0,       // �¶Ȳ����ṹ��϶��׼Դ   ��֧��ADC
    RES4,           // ����
    VREFH0,         // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
    VREFL0,         // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
    Module0_Dis,    // ��֧�� ADC

    // ---------------------------------ADC1-------------------------
    ADC1_DP0  =0,
    ADC1_DP1  =1,
    PGA1_DP   =2,        // ��֧�� ADC
    ADC1_DP3  =3,
    ADC1_SE4a =4,      // PTE0
    ADC1_SE5a =5,      // PTE1
    ADC1_SE6a =6,      // PTE2
    ADC1_SE7a =7,      // PTE3

    ADC1_SE4b = ADC1_SE4a,  // PTC8    Bͨ�� ��֧������ADC ,���� ADC1_SE4b ������ADC������ᵱ�� ADC1_SE4a ������
    ADC1_SE5b = ADC1_SE5a,  // PTC9    Bͨ�� ��֧������ADC
    ADC1_SE6b = ADC1_SE6a,  // PTC10   Bͨ�� ��֧������ADC
    ADC1_SE7b = ADC1_SE7a,  // PTC11   Bͨ�� ��֧������ADC

    ADC1_SE8  =8,       // PTB0
    ADC1_SE9  =9,       // PTB1
    ADC1_SE10 =10,      // PTB4
    ADC1_SE11 =11,      // PTB5
    ADC1_SE12 =12,      // PTB6
    ADC1_SE13 =13,      // PTB7
    ADC1_SE14 =14,      // PTB10
    ADC1_SE15 =15,      // PTB11
    ADC1_SE16 =16,      // ADC1_SE16
    ADC1_SE17 =17,      // PTA17
    VREF_OUTPUT,    // VREF Output
    ADC1_DM0  =19,       // ADC1_DM0
    ADC1_DM1  =20,       // ADC1_DM1
    RES5,           //����
    RES6,
    DAC1_OUT,
    RES7,           //����
    RES8,
    Temp1_Sensor,
    Bandgap1,       // �¶Ȳ����ṹ��϶��׼Դ   ��֧��ADC
    RES9,
    VREFH1,         // �ο��ߵ�ѹ,����ADC���� ,�����Ϊ 2^n-1
    VREFL1,         // �ο��͵�ѹ,����ADC���� ,�����Ϊ 0
    Module1_Dis,    // ��֧�� ADC

} ADCn_Ch_e;



//����λ��
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************************************
                                                    ADCģ�麯��
**************************************************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------------------------------------------
����    ����ADC_Init
����    �ܡ���ʼ��ADCģʽ
����    ����ADCn_e�� Ҫ��ʼ����ADCģ�飬 ADC0  ADC1
���� �� ֵ����
��ʵ    ����ADC_Init(ADC0); //��ʼ��ADC0ģ��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void ADC_Init(ADC_Type * adc_n);



/*------------------------------------------------------------------------------------------------------
����    ����ADC_Start
����    �ܡ�����ADCת��
����    ����adc_n ��  ģ����ADC0��ADC1 
����    ����adc_ch��  ADCͨ����� 
����    ����bit   ��  ����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit
���� �� ֵ����
��ʵ    ����ADC_Init(ADC0,ADC1_SE8,ADC_12bit); //ͨ�����Ϊ ADC1_SE8������
��ע�����ʹ��ǰӦ��ʼ����ӦADCģ��
--------------------------------------------------------------------------------------------------------*/
void ADC_Start(ADC_Type * adc_n, ADCn_Ch_e adc_ch, ADC_nbit bit);



/*------------------------------------------------------------------------------------------------------
����    ����ADC_Once
����    �ܡ�����ADCת�� ��ȡһ��ADCת��ֵ
����    ����adc_n ��  ģ����ADC0��ADC1 
����    ����adc_ch��  ADCͨ����� 
����    ����bit   ��  ����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit
���� �� ֵ����
��ʵ    ����ADC_Once(ADC0,ADC1_SE8,ADC_12bit) ͨ�����Ϊ ADC1_SE8�����ţ�����һ��ADCת����
��ע�����
--------------------------------------------------------------------------------------------------------*/
uint16_t ADC_Once(ADC_Type * adc_n, ADCn_Ch_e adc_ch, ADC_nbit bit);



/*------------------------------------------------------------------------------------------------------
����    ����ADC_Mid
����    �ܡ�����ADC3��ת��ȡ�м�ֵ
����    ����adc_n ��  ģ����ADC0��ADC1 
����    ����adc_ch��  ADCͨ����� 
����    ����bit   ��  ����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit
���� �� ֵ����ֵ
��ʵ    ����ADC_Mid(ADC0,ADC1_SE8,ADC_12bit) ͨ�����Ϊ ADC1_SE8�����ţ�����3��ADCת����ѡȡ�м�ֵ���ء�
��ע�����
--------------------------------------------------------------------------------------------------------*/
uint16_t ADC_Mid(ADC_Type * adc_n,  ADCn_Ch_e adc_ch, ADC_nbit bit);



/*------------------------------------------------------------------------------------------------------
����    ����ADC_Ave
����    �ܡ�����ADC3��ת��ȡ�м�ֵ
����    ����adc_n ��  ģ����ADC0��ADC1 
����    ����adc_ch��  ADCͨ����� 
����    ����bit   ��  ����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit
����    ����N     :   ��ֵ�˲�������1~65535��
���� �� ֵ��ƽ��ֵ
��ʵ    ����ADC_Ave(ADC0,ADC1_SE8,ADC_12bit,100) ͨ�����Ϊ ADC1_SE8�����ţ�����100��ADCת���������ƽ��ֵ���ء�   
��ע�����
--------------------------------------------------------------------------------------------------------*/
uint16_t ADC_Ave(ADC_Type * adc_n,  ADCn_Ch_e adc_ch, ADC_nbit bit, uint16_t N);




#endif /* __MK60_ADC16_H__ */