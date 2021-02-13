#include "include.h"
#include "papercount.h"

#define MaxNum 100
#define CountTimes 5


uint32_t num = 0;
uint32_t totaltime = 0;
bool StartCount = false;

uint32_t PaperIndex[] = 
{
 122347,13995,16200,17826,18770
 ,19823,20780,21280,21755,22195
 ,22924,23150,23458,23766,24110
 ,24425,24505,24800,24908,25103
 ,25255,25395,25530,25652,25792
 ,25907,25997,26102,26214,26299
 ,26375,26470,26526,26608,26678
 ,26740,26826,26866,26918,26972
 ,27018,27068,27124,27172,27204
 ,27250,27278,27325,27365,27400
 ,27438,27450,27480,27502,27530
 ,27572,27594,27630,27668,27685
 ,27705,27729,27753,27778,27793
 ,27818,27842,27858,27888,27905
 ,27932,27960,27982,27997,28009
 ,28025,28046,28058,28079,28096
 ,28114,28126,28148,28160,28173
 ,28187,28196,28202,28210,28233
 ,28242,28252,28267,28273,28293
 ,28306,28312,28324,28339,28351
 ,28358};


void _PaperCountSystemInit_()/*?*/
{
	PLL_Init(PLL180);                       //初始化PLL为180M  

        NVIC_SetPriorityGrouping(0x07 - 2);      
        systime.init();                         

        LED_Init();   
        BEEP_Init();                            
        
        PaperCount_KEY_Init();                             

        OLED_Init();                            
        
        WLUART_Init();    
        
        FDC_Init();
}                       

void PaperCount_OLED_Display(void)
{
    OLED_CLS();

    OLED_WriteXLine(0,"RawC:%lu",RawC);
    OLED_WriteXLine(2,"C:%lu",C); 
      
    OLED_WriteXLine(4,"Num:%u",num);
    OLED_WriteXLine(6,"Time:%lums",totaltime);
   
}

void PaperCount()
{
    _PaperCountSystemInit_();
    
    OLED_ShowInitUI();
   
    uint32_t now_time = systime.get_time_ms();
    uint32_t starttime = 0;
    uint32_t N[5] = {0,0,0,0,0};
    
    //Task.DoPaperCount = true;
    
    while(Task.DoPaperCount)
    {
          //Task.DoPaperCount = true;
          PaperCount_Key_Effect();
          //StartCount = true;
          if(systime.get_time_ms() - now_time >= 50)
          {
              now_time = systime.get_time_ms();
              if (StartCount)
              {
                  starttime = systime.get_time_ms();
                  
                  for(int i = 0 ;i< CountTimes ;i++)
                  {
                      C = FDC_SlidingMedianFilter(0);
                      N[i] = CountPaperNum(C);
                  }
                    
                  num = ResultFilter(N,CountTimes);
                  
                  totaltime = systime.get_time_ms() - starttime;     
                  
                  BEEP_ON;
                  systime.delay_ms(500);
                  BEEP_OFF;
                  
                  StartCount = false;
              }
              PaperCount_OLED_Display();
              
          }
    }
}

uint16_t C100_Func(uint16_t C)
{
    float res = (0.0738*C - 2000.95955);
    
    return (uint16_t)res;
}

uint16_t C70_Func(uint16_t i)
{
    float res = (13.548*i + 27019);
    
    return (uint16_t)res;
}

uint16_t CountPaperNum(uint32_t C)
{
    uint16_t num = 0;
    uint32_t error[2];
    
    if (C < (PaperIndex[1]+(PaperIndex[2]-PaperIndex[1])/2))
      num = 1;
    else if (C >= PaperIndex[MaxNum] && C <= (PaperIndex[0] - (PaperIndex[0] - PaperIndex[MaxNum])/2))
    {
        num = C100_Func(C);
    }
    else if (C <= PaperIndex[MaxNum] && (C>= (PaperIndex[MaxNum-1]+(PaperIndex[MaxNum]-PaperIndex[MaxNum-1])/2)))
    {
        num = MaxNum;
    }
    else if (C >= (PaperIndex[0] - (PaperIndex[0] - PaperIndex[MaxNum])/2))
    {
        num = 0;
    }
    else
    {
      for (int i = 1;i<MaxNum -1;i++)
      {
         error[0] = (PaperIndex[i+1] - PaperIndex[i])/2;
         error[1] = (PaperIndex[i+2] - PaperIndex[i+1])/2;
         if(i<=50)
         {
           if ((C >= (PaperIndex[i] + error[0])) && (C<= (PaperIndex[i+1] + error[1])))
           {
              num = i+1;
              break;
           }
         }
         else if(i<=70)
         {
            if(C >= PaperIndex[i] && C <= PaperIndex[i+1])
            {
                num = i;
            }
         }
         else
         {
           if ((C >= (PaperIndex[i] + error[0])) && (C<= (PaperIndex[i+1] + error[1])))
           {
              num = i+1;
           }
//             if(C > C70_Func(i) && C < C70_Func(i+1))
//             {
//                num = i;
//             }
         }
      }
    }
    
    if (num == 0)
    {
        BEEP_ON;
    }
    else
    {
        BEEP_OFF;
    }
    
    return num;
  
}

void PaperCount_KEY_Init(void)
{
   GPIO_PinInit(PTE24, GPI_UP, 1);
   GPIO_PinInit(PTE25, GPI_UP, 1);
   GPIO_PinInit(PTE26, GPI_UP, 1);
   GPIO_PinInit(PTE27, GPI_UP, 1);
   GPIO_PinInit(PTE28, GPI_UP, 1);
}

uint8_t PaperCount_KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
      key_up=1;      //支持连按
    }
    if(key_up && (GPIO_PinRead(PTE24)==0 || GPIO_PinRead(PTE25)==0 || GPIO_PinRead(PTE26)==0 || GPIO_PinRead(PTE27)==0 || GPIO_PinRead(PTE28)==0))
    {
      delayms(50);   //消抖
      key_up=0;
      /*Page=0,显示AD采样值；Page=1，显示并选择可调节参数；Page=3,调节参数*/
      if(GPIO_PinRead(PTE28)==0)      //确定
      {
        return 1;
      }
      
      if(GPIO_PinRead(PTE25)==0) //返回
      {
        return 2;    
      }
      /*选项下移选项上移；参数调大小*/
      if(GPIO_PinRead(PTE27)==0) //下移
      {
        return 3;    
      }
      if(GPIO_PinRead(PTE26)==0) //上移
      {
        return 4;    
      }
      if(GPIO_PinRead(PTE24)==0) //开车
      {
        return 5;    
      }
    }
    if(GPIO_PinRead(PTE24)==1 && GPIO_PinRead(PTE25)==1 && GPIO_PinRead(PTE26)==1 && GPIO_PinRead(PTE27)==1 && GPIO_PinRead(PTE28)==1) 
    {
     key_up=1;   
    }
    return 0;   //无按键按下
     
}

void PaperCount_Key_Effect(void)
{ 
    uint8_t key = PaperCount_KEY_Read(0);
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

uint32_t ResultFilter(uint32_t *Result,uint16_t len)
{
    uint32_t SameNum[5] = {0,0,0,0,0};
                  
    for(int i = 0 ; i < len ; i++)
    {
      for(int j = 0; j<len ;j++)
      {
           if(j!=i)
           {
               if(Result[j] == Result[i])
                   SameNum[i]++;
           }
                          
      }
    }
    
    uint32_t _MaxNum = 0;
  
    uint32_t MaxIndex = 0;
   
    _MaxNum = SameNum[0];
    
    for(int i = 0 ; i < len ; i++)
    {
         if(SameNum[i] >= _MaxNum)
         {
            _MaxNum = SameNum[i];
            MaxIndex = i;  
         }
    } 
    
    return Result[MaxIndex];
}

void FDC_MedianFilterDelay(int delay_time)
{
    systime.delay_ms(delay_time);
}

uint32_t FDC_MedianFilter(unsigned int delay_time)
{
	 uint32_t i = 0;
	 uint32_t j = 0;
	 uint32_t k = 0;
	 uint32_t temp = 0;

	i = FDC_read_CHx(3);
	FDC_MedianFilterDelay(delay_time);
	j = FDC_read_CHx(3);
	FDC_MedianFilterDelay(delay_time);
	k = FDC_read_CHx(3);

        if (i > j)
        {
            temp = i; i = j; j = temp;
        }
        if (k > j) 
            temp = j;
        else if(k > i) 
            temp = k; 
        else 
            temp = i;
        
        return temp; 
}
uint32_t FDC_SlidingMedianFilter(unsigned int delay_time)
{
    uint32_t Value0[4]={0,0,0,0};
    uint32_t Value1[4] = {0,0,0,0};
    /*中值滤波*/
    for(int t=0;t<4;t++)
    {

	Value0[t] = FDC_MedianFilter(delay_time);
        
    }
     /*滑动中值滤波*/   
    for(int t=0;t<4;t++)
    {
        for(int l=0;l<4;l++)
        {
            Value0[0]=Value0[1];
            Value0[1]=Value0[2];
            Value0[2]=Value0[3];         
        }
        //1.取3次转换结果
	Value0[3] = FDC_MedianFilter(delay_time);
				
        for(int l=0;l<4;l++)
        {
            Value1[t]+=Value0[l];
        }
        Value1[t]/=4;
    }
    return (uint32_t)((Value1[0]+Value1[1]+Value1[2]+Value1[3])/4); 
}