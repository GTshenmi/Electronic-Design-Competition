#include "include.h"


/* 
                       作者：DJ
                         .::::.
                       .::::::::.
                      :::::::::::
                   ..:::::::::::'
                '::::::::::::'
                  .::::::::::
             '::::::::::::::..
                  ..::::::::::::.
                ``::::::::::::::::
                 ::::``:::::::::'        .:::.
                ::::'   ':::::'       .::::::::.
              .::::'     :::::     .:::::::'::::.
             .:::'       :::::  .:::::::::' ':::::.
            .::'        :::::.:::::::::'      ':::::.
           .::'         ::::::::::::::'         ``::::.
       ...:::           ::::::::::::'              ``::.
      ```` ':.          ':::::::::'                  ::::..
                         '.:::::'                    ':'````..
  
              佛祖保佑               永无BUG
                         不要烧芯片
                         无玄学问题
                        @Write By DJ
*/

void Debug_Console() 
{       
    
}

void ValueInit() 
{
   
}

bool do_main_cycle = true;

void main(void)           
{     
    _SystemInit_();
    uint32_t now_time = systime.get_time_ms();
    //systime.delay_ms(5000);
//    uint8_t Str[12] = {'f','f','f','f','f','f','f','f','f'};
    StartCycle:
    while(do_main_cycle)
    {      
          if(systime.get_time_ms() - now_time >= 200)
          {
                LCD.Debug.Clear(WHITE);
                
                //UARTx_SendStr(&uart[1],"Hello,OpenMV");
                //UART4_Printf("%s","Hello,OpenMV");
                //LCD.Write.XLine(0,"Send:%s","Hello,OpenMV");
                
                //UART4_Printf("K66 ID:%.3f",123.456);
                
//                if(uart[1].CacheIsFull)
//                {
//                   //uart[1].ReceiveLen = 9;
//                   for(int i = 0;i<12;i++)
//                   {
//                     Str[i] = uart[1].Cache[i];
//                   }
//                   //LCD.Write.XLine(2,"Receive:%s",Str);
//                   uart[1].StartReceive = true;
////                   uart[1].CacheIsFull = false;
//                }
//                
//                LCD.Write.XLine(2,"Receive:%12s",Str);
                //UARTx_Printf(&uart[1],"Hello,OpenMV");
                //UART4_Printf("[info]:Hello,OpenMV,K66 ID:%.3f",100.000);
                //UARTx_SendStr(&Uart[1],"sssss");
                //LCD.Write.XLine(2,"Welcome.");
                
         
                now_time = systime.get_time_ms();
//                TempSensor.Temperature = TempSensor.Read();
                //LCD.Write.XLine(2,"Receive:%s",Str);
                
                //LCD.Debug.Clear(WHITE);
                LCD.Write.XLine(0,"Temp%.3f C",TempSensor.Read());
//                
//                InfraredSensor.Temperature = InfraredSensor.Read();
//          
//                LCD.Write.XLine(1,"Temp:%.3f C",InfraredSensor.Temperature);
//               SetMotorParameter(&Motor[0],5000); 
//               LCD.Write.XLine(8,"Speed:%d",GetMotorParameter(&Motor[0]));
               
//               EGCSensor.Read(0);
//               
//               LCD.Write.XLine(2,"EGC:%lu",EGCSensor.Local->Channle[0] + EGCSensor.Local->Channle[1]);
                
          }
    }
    goto StartCycle;
}

void _SystemInit_()
{
      PLL_Init(PLL180);                       //初始化PLL为180M  

      NVIC_SetPriorityGrouping(0x07 - 2);      
      systime.init();                         

      LED_Init();   
      BEEP_Init();
      
      MotorxInit();
        
      TriHeadxInit();
        
      KEY_Init();        
        
      //ADCxInit();
        
      PITx_Init();

      ValueInit(); 
        
      LCD.Init();
      
      //InfraredSensor.Init();
      //EGCSensor.Init();
      TempSensor.Init();
      
      //UARTxInit();
}     

void PITx_Init() 
{
    PIT0_Init();
    PIT1_Init();
    PIT2_Init();
    PIT3_Init();
}
void PITx_Close()
{
   PIT_Close(PIT0);
   PIT_Close(PIT1);
   PIT_Close(PIT2);
   PIT_Close(PIT3);
}
void PIT0_Init() 
{
      PIT_Init(PIT0,250);

      NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
      NVIC_EnableIRQ(PIT0_IRQn); 
}
void PIT1_Init() 
{
      PIT_Init(PIT1,2);
      
      NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));
      NVIC_EnableIRQ(PIT1_IRQn); 
}
void PIT2_Init() 
{
      PIT_Init(PIT2,20);
      
      NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3,3));
      NVIC_EnableIRQ(PIT2_IRQn);   
}
void PIT3_Init() 
{
      PIT_Init(PIT3,100);
      
      NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,0));
      NVIC_EnableIRQ(PIT3_IRQn); 
}