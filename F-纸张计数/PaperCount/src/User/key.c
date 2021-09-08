#include "include.h"

uint8_t Page=0;
uint8_t Selection=0;
uint8_t StartCar_flag=0;

bool StartCount = false;


void KEY_Init(void)
{
   GPIO_PinInit(PTE24, GPI_UP, 1);
   GPIO_PinInit(PTE25, GPI_UP, 1);
   GPIO_PinInit(PTE26, GPI_UP, 1);
   GPIO_PinInit(PTE27, GPI_UP, 1);
   GPIO_PinInit(PTE28, GPI_UP, 1);
}

uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
      key_up=1;      //֧������
    }
    if(key_up && (GPIO_PinRead(PTE24)==0 || GPIO_PinRead(PTE25)==0 || GPIO_PinRead(PTE26)==0 || GPIO_PinRead(PTE27)==0 || GPIO_PinRead(PTE28)==0))
    {
      delayms(50);   //����
      key_up=0;
      /*Page=0,��ʾAD����ֵ��Page=1����ʾ��ѡ��ɵ��ڲ�����Page=3,���ڲ���*/
      if(GPIO_PinRead(PTE28)==0)      //ȷ��
      {
        return 1;
      }
      
      if(GPIO_PinRead(PTE25)==0) //����
      {
        return 2;    
      }
      /*ѡ������ѡ�����ƣ���������С*/
      if(GPIO_PinRead(PTE27)==0) //����
      {
        return 3;    
      }
      if(GPIO_PinRead(PTE26)==0) //����
      {
        return 4;    
      }
      if(GPIO_PinRead(PTE24)==0) //����
      {
        return 5;    
      }
    }
    if(GPIO_PinRead(PTE24)==1 && GPIO_PinRead(PTE25)==1 && GPIO_PinRead(PTE26)==1 && GPIO_PinRead(PTE27)==1 && GPIO_PinRead(PTE28)==1) 
    {
     key_up=1;   
    }
    return 0;   //�ް�������
     
}

void Key_Effect(void)
{ 
    uint8_t key = KEY_Read(0);
    static int times = 0;
    switch(key)
    {
        case 5:
          StartCount = true;
          break;
        case 1:
          times++;
          if (times == 1)
          {
              for(int i = 0 ; i<10 ;i++)
                C += FDC_SlidingMedianFilter(0);
              
              C /= 10;
              
              PaperIndex[1] = C;
          }
          else if(times == 2)
          {
              C = 0;;
              for(int i = 0 ; i<10 ;i++)
                C += FDC_SlidingMedianFilter(0);
              
              C /= 10;
              PaperIndex[5*(times-1)] = C;
              
              
              float k = (PaperIndex[5*(times-1)] - PaperIndex[5*(times-2)+1])*1.0/(5.0-1.0);
              
              for(int i = 0 ; i<3 ;i++)
              {
                  PaperIndex[5*(times-2)+i+2] =(uint32_t)(PaperIndex[5*(times-2)+1] + k * (i+1));
              }   
          }
          else if(times <= 9)
          {
              C = 0;;
              for(int i = 0 ; i<10 ;i++)
                C += FDC_SlidingMedianFilter(0);
              
              C /= 10;
              PaperIndex[5*(times-1)] = C;
              
              
              float k = (PaperIndex[5*(times-1)] - PaperIndex[5*(times-2)+1])*1.0/(5.0-1.0);
              
              for(int i = 0 ; i<=4 ;i++)
              {
                  PaperIndex[5*(times-2)+i+1] =(uint32_t)(PaperIndex[5*(times-2)] + k * (i+1));
              }
              
          }
          else if (times <= 12)
          {
              C = 0;;
              for(int i = 0 ; i<10 ;i++)
                C += FDC_SlidingMedianFilter(0);
              
              C /= 10;
              PaperIndex[10*(times-9) + 40] = C;
              
              float k = (PaperIndex[10*(times-9) + 40] - PaperIndex[10*(times-10) + 40 + 1])*1.0/(10.0-1.0);
              
              for(int i = 0 ; i<=9 ;i++)
              {
                  PaperIndex[10*(times-9) + 40+i+1] =(uint32_t)(PaperIndex[10*(times-9) + 40] + k * (i+1));
              }
          }
          else
          {
              times = 0;
          }
          
          
          
          
        break;
    }
    
}
        