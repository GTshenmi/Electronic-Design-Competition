#include "include.h"
#include "papercount.h"

#define MaxNum 100

uint32_t C = 0;
uint32_t num = 0;
uint32_t RawC = 0;
uint32_t totaltime = 0;

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

//55



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