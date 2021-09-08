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
                        @Write By DJ
*/

void Debug_Console() 
{       
    
}

void ValueInit() 
{
    
}
/*M.A.I.N.2*/
/*②*/
void main(void)           
{     
    _SystemInit_();
    
    OLED_ShowInitUI();
   
    uint32_t now_time = systime.get_time_ms();  

    while(1)
    {      
          //Key_Effect();
          if(systime.get_time_ms() - now_time >= 50)
          {
              now_time = systime.get_time_ms();
              OLED_Display();
              
          }
    }
}

void _SystemInit_()/*?*/
{
	PLL_Init(PLL180);                       //初始化PLL为180M  

        NVIC_SetPriorityGrouping(0x07 - 2);      
        systime.init();                         

        LED_Init();   
        BEEP_Init();                            
        
        //KEY_Init();        
        
        //MotorInit();

        OLED_Init();                            
        
        WLUART_Init();    
        
 //       ADCx_Init();
        
        PITx_Init();
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
      
      NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,3));
      NVIC_EnableIRQ(PIT2_IRQn);   
}
void PIT3_Init() 
{
      PIT_Init(PIT3,100);
      
      NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,0));
      NVIC_EnableIRQ(PIT3_IRQn); 
}