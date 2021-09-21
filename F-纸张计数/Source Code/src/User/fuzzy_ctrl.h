#ifndef _FUZZY_CTRL_H_
#define _FUZZY_CTRL_H_


#define NL -3.0
#define NM -2.0
#define NS -1.0
#define ZE 0.0
#define PS 1.0
#define PM 2.0
#define PL 3.0


typedef struct{
	float Kp;
	float Ki;
	float Kd;
}pid_ctrl_t;

extern float fuzzyRuleKp[7][7];
extern float fuzzyRuleKi[7][7];
extern float fuzzyRuleKd[7][7];

pid_ctrl_t fuzzy(float e,float ec);


//typedef enum 
//{
//   NL=-3,
//   NM=-2,
//   NS=-1,
//   ZE=0,
//   PS=1,
//   PM=2,
//   PL=3,
//}_fuzzy_rules_t;

//float   NL=-3.0;
//float   NM=-2.0;
//float   NS=-1.0;
//float   ZE=0.0;
//float   PS=1.0;
//float   PM=2.0;
//float   PL=3.0; 


/*仅用于按键调参,并非算法使用*/
typedef struct 
{
    float NL_LastValue;
    float NL_CurrentValue;
 
    float NM_LastValue;
    float NM_CurrentValue;
    
    float NS_LastValue;
    float NS_CurrentValue;
    
    float ZE_LastValue;
    float ZE_CurrentValue;
    
    float PS_LastValue;
    float PS_CurrentValue;

    float PM_LastValue;
    float PM_CurrentValue;
    
    float PL_LastValue;
    float PL_CurrentValue;
}_fuzzy_value_t;


typedef enum
{
  NL_T,
  NM_T,
  NS_T,
  ZE_T,
  PS_T,
  PM_T,
  PL_T,
}_fuzzy_ctrl_type_t_;

extern _fuzzy_value_t Fuzzy_Value;
extern _fuzzy_ctrl_type_t_ fuzzy_ctrl_type;
/*仅用于按键调参,并非算法使用*/

#endif