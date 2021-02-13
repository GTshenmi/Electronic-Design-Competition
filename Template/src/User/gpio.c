#include "include.h"
#include "gpio.h"

void GPIO_Init(GPIO_TypeDef *IO,io_handle_t *handle)
{
   if(!handle->UsingDefaultConfig)
   {
     IO->Handle.IOState = handle->IOState;
       
     if(handle->IOState == Reverse)
     IO->Handle.IOState = High;
     
     IO->Handle.Ptx_n = handle->Ptx_n;
     IO->Handle.IOConfig = handle->IOConfig;
   } 
   
   GPIO_PinInit(IO->Handle.Ptx_n,IO->Handle.IOConfig,IO->Handle.IOState);
   IO->IO_SHIELD = false;
}

void GPIO_DeInit(GPIO_TypeDef *IO)
{
   IO->IO_SHIELD = true;
}

void GPIO_SetReverseTime(GPIO_TypeDef *IO,uint32_t ms)
{
   IO->ReverseTime = ms;
}

void Task_IOScan()
{
   static uint16_t state[12] = {IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState,IOTaskInitState};
   static GPIO_CFG config[12] = {GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR,GPO_HDS_SSR};
   for(int i = 0;i < 12;i++)
   {
     if(!IO[i].IO_SHIELD) 
     {
          if(IO[i].Handle.IOConfig == GPO)
          {
               if(config[i] != GPO)
               {
                  if(IO[i].Handle.IOState >= Reverse)
                  {
                    GPIO_PinSetDir(IO[i].Handle.Ptx_n,GPO);
                    GPIO_PinWrite(IO[i].Handle.Ptx_n,High);
                  }
                  else
                  {
                    GPIO_PinSetDir(IO[i].Handle.Ptx_n,GPO);
                    GPIO_PinWrite(IO[i].Handle.Ptx_n,IO[i].Handle.IOState);
                  }
                  
                  config[i] = GPO;
               }
               if(state[i] != IO[i].Handle.IOState)
               {
                  state[i] = IO[i].Handle.IOState;
                  
                  if(IO[i].Handle.IOState == High)
                    GPIO_PinWrite(IO[i].Handle.Ptx_n,1);
                  if(IO[i].Handle.IOState == Low)
                    GPIO_PinWrite(IO[i].Handle.Ptx_n,0);
                  
                  if(IO[i].Handle.IOState == Reverse)
                  {
                      IO[i].ReverseCount = IO[i].ReverseTime/IO_Scan_Interval;
                      
                      GPIO_PinReverse(IO[i].Handle.Ptx_n);
                  }
               }
          }
          else if(IO[i].Handle.IOConfig == GPI)
          {
               if(config[i] != GPI)
               {
                  GPIO_PinSetDir(IO[i].Handle.Ptx_n,GPI); 
                  config[i] = GPI;
               }
               IO[i].Handle.IOState = GPIO_PinRead(IO[i].Handle.Ptx_n);
          }
          else
          {
             IO[i].IO_SHIELD = true;
             config[i] = GPO_HDS_SSR;
          }
        
        if(IO[i].Handle.IOConfig == GPO && IO[i].Handle.IOState == Reverse)
        {
           IO[i].ReverseCount--;
           if(IO[i].ReverseCount == 0)
           {
              GPIO_PinReverse(IO[i].Handle.Ptx_n);
              IO[i].ReverseCount = IO[i].ReverseTime/IO_Scan_Interval;
           }
        }
        
     }
   }
}

GPIO_TypeDef IO[12] =
{
//  [0] = 
//  {
//     .Handle.IOState = IOTaskInitState,
//     .IO_SHIELD = true,
//     .Handle.Ptx_n = PTC0,
//     .Handle.IOConfig = GPO,
//  },
//  [1] = 
//  {
//     .Handle.IOState = IOTaskInitState,
//     .IO_SHIELD = true, 
//     .Handle.Ptx_n = PTA17,
//     .Handle.IOConfig = GPO,
//  },
//  [2] = 
//  {
//     .Handle.IOState = IOTaskInitState,
//     .IO_SHIELD = true,   
//     .Handle.Ptx_n = PTE26,
//     .Handle.IOConfig = GPO,
//  },  
//  [3] = 
//  {
//     .Handle.IOState = IOTaskInitState,
//     .IO_SHIELD = true,    
//     .Handle.Ptx_n = PTD15,
//     .Handle.IOConfig = GPO,
//  },
  [0] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,
     .Handle.Ptx_n = PTB16,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [1] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true, 
     .Handle.Ptx_n = PTB10,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [2] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,   
     .Handle.Ptx_n = PTB8,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },  
  [3] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,    
     .Handle.Ptx_n = PTB17,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [4] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,   
     .Handle.Ptx_n = PTB11,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [5] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,   
     .Handle.Ptx_n = PTB9,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [6] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,
     .Handle.Ptx_n = PTB19,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [7] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true, 
     .Handle.Ptx_n = PTB21,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [8] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,
     .Handle.Ptx_n = PTB23,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [9] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true,
     .Handle.Ptx_n = PTB18,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [10] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true, 
     .Handle.Ptx_n = PTB20,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  },
  [11] = 
  {
     .Handle.IOState = IOTaskInitState,
     .IO_SHIELD = true, 
     .Handle.Ptx_n = PTB22,
     .Handle.IOConfig = GPO,
     .Handle.UsingDefaultConfig = true,
  }, 
};