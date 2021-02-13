#include "include.h"
#include "interpolation.h"
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

uint16_t arrColor[1600];
uint16_t camColors[] = {0x480F,
0x400F,0x400F,0x400F,0x4010,0x3810,0x3810,0x3810,0x3810,0x3010,0x3010,
0x3010,0x2810,0x2810,0x2810,0x2810,0x2010,0x2010,0x2010,0x1810,0x1810,
0x1811,0x1811,0x1011,0x1011,0x1011,0x0811,0x0811,0x0811,0x0011,0x0011,
0x0011,0x0011,0x0011,0x0031,0x0031,0x0051,0x0072,0x0072,0x0092,0x00B2,
0x00B2,0x00D2,0x00F2,0x00F2,0x0112,0x0132,0x0152,0x0152,0x0172,0x0192,
0x0192,0x01B2,0x01D2,0x01F3,0x01F3,0x0213,0x0233,0x0253,0x0253,0x0273,
0x0293,0x02B3,0x02D3,0x02D3,0x02F3,0x0313,0x0333,0x0333,0x0353,0x0373,
0x0394,0x03B4,0x03D4,0x03D4,0x03F4,0x0414,0x0434,0x0454,0x0474,0x0474,
0x0494,0x04B4,0x04D4,0x04F4,0x0514,0x0534,0x0534,0x0554,0x0554,0x0574,
0x0574,0x0573,0x0573,0x0573,0x0572,0x0572,0x0572,0x0571,0x0591,0x0591,
0x0590,0x0590,0x058F,0x058F,0x058F,0x058E,0x05AE,0x05AE,0x05AD,0x05AD,
0x05AD,0x05AC,0x05AC,0x05AB,0x05CB,0x05CB,0x05CA,0x05CA,0x05CA,0x05C9,
0x05C9,0x05C8,0x05E8,0x05E8,0x05E7,0x05E7,0x05E6,0x05E6,0x05E6,0x05E5,
0x05E5,0x0604,0x0604,0x0604,0x0603,0x0603,0x0602,0x0602,0x0601,0x0621,
0x0621,0x0620,0x0620,0x0620,0x0620,0x0E20,0x0E20,0x0E40,0x1640,0x1640,
0x1E40,0x1E40,0x2640,0x2640,0x2E40,0x2E60,0x3660,0x3660,0x3E60,0x3E60,
0x3E60,0x4660,0x4660,0x4E60,0x4E80,0x5680,0x5680,0x5E80,0x5E80,0x6680,
0x6680,0x6E80,0x6EA0,0x76A0,0x76A0,0x7EA0,0x7EA0,0x86A0,0x86A0,0x8EA0,
0x8EC0,0x96C0,0x96C0,0x9EC0,0x9EC0,0xA6C0,0xAEC0,0xAEC0,0xB6E0,0xB6E0,
0xBEE0,0xBEE0,0xC6E0,0xC6E0,0xCEE0,0xCEE0,0xD6E0,0xD700,0xDF00,0xDEE0,
0xDEC0,0xDEA0,0xDE80,0xDE80,0xE660,0xE640,0xE620,0xE600,0xE5E0,0xE5C0,
0xE5A0,0xE580,0xE560,0xE540,0xE520,0xE500,0xE4E0,0xE4C0,0xE4A0,0xE480,
0xE460,0xEC40,0xEC20,0xEC00,0xEBE0,0xEBC0,0xEBA0,0xEB80,0xEB60,0xEB40,
0xEB20,0xEB00,0xEAE0,0xEAC0,0xEAA0,0xEA80,0xEA60,0xEA40,0xF220,0xF200,
0xF1E0,0xF1C0,0xF1A0,0xF180,0xF160,0xF140,0xF100,0xF0E0,0xF0C0,0xF0A0,
0xF080,0xF060,0xF040,0xF020,0xF800,};
void set_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y, float f) 
{
  if ((x < 0) || (x >= cols)) return;
  if ((y < 0) || (y >= rows)) return;
  p[y * cols + x] = f;
} 

float map(float val, float I_Min, float I_Max, float O_Min, float O_Max)
{
    return(val/(I_Max-I_Min)*(O_Max-O_Min) + O_Min);
}

void show(uint16_t *pBuf)
{	 
	u8 i=0;
	u8 j=0;
	u8 x=0;
	u8 y=0;
	u16 colorr1=0;
//	u8 colorr=0;
	for(j=0;j<40;j++)
	{
		for(i=0;i<40;i++)
		{				
                     LCD.Draw.Sqr(i*2,j*2,(i*2)+2,(j*2)+2,(lcd_color_t)arrColor[colorr1]);	
                     colorr1++;
		}
	}
		
		//中心点
	for(x=19;x<=20;x++)
	{
		for(y=19;y<=20;y++)
		{
                  LCD.Draw.Sqr(y*2,x*2,(y*2)+2,(x*2)+2,(lcd_color_t)WHITE);	
		}
	}
}
float cubicInterpolate(float p[], float x) {
    float r = p[1] + (0.5 * x * (p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0]))));
  /*
    Serial.print("interpolating: ["); 
    Serial.print(p[0],2); Serial.print(", ");
    Serial.print(p[1],2); Serial.print(", ");
    Serial.print(p[2],2); Serial.print(", ");
    Serial.print(p[3],2); Serial.print("] w/"); Serial.print(x); Serial.print(" = ");
    Serial.println(r);
  */
    return r;
}
float get_point(float *p, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {
  if (x < 0)        x = 0;
  if (y < 0)        y = 0;
  if (x >= cols)    x = cols - 1;
  if (y >= rows)    y = rows - 1;
  return p[y * cols + x];
}
float bicubicInterpolate(float p[], float x, float y) {
    float arr[4] = {0,0,0,0};
    arr[0] = cubicInterpolate(p+0, x);
    arr[1] = cubicInterpolate(p+4, x);
    arr[2] = cubicInterpolate(p+8, x);
    arr[3] = cubicInterpolate(p+12, x);
    return cubicInterpolate(arr, y);
}
void get_adjacents_1d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {
    //Serial.print("("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(")");
    // pick two items to the left
    dest[0] = get_point(src, rows, cols, x-1, y);
    dest[1] = get_point(src, rows, cols, x, y);
    // pick two items to the right
    dest[2] = get_point(src, rows, cols, x+1, y);
    dest[3] = get_point(src, rows, cols, x+2, y);
}
void get_adjacents_2d(float *src, float *dest, uint8_t rows, uint8_t cols, int8_t x, int8_t y) {
    //Serial.print("("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(")");
//    float arr[4];
    for (int8_t delta_y = -1; delta_y < 3; delta_y++) { // -1, 0, 1, 2
        float *row = dest + 4 * (delta_y+1); // index into each chunk of 4
        for (int8_t delta_x = -1; delta_x < 3; delta_x++) { // -1, 0, 1, 2
            row[delta_x+1] = get_point(src, rows, cols, x+delta_x, y+delta_y);
        }
    }
}

void interpolate_image(float *src, uint8_t src_rows, uint8_t src_cols, 
                       float *dest, uint8_t dest_rows, uint8_t dest_cols) {
  float mu_x = (src_cols - 1.0) / (dest_cols - 1.0);
  float mu_y = (src_rows - 1.0) / (dest_rows - 1.0);

  float adj_2d[16]; // matrix for storing adjacents
  
  for (uint8_t y_idx=0; y_idx < dest_rows; y_idx++) {
    for (uint8_t x_idx=0; x_idx < dest_cols; x_idx++) {
       float x = x_idx * mu_x;
       float y = y_idx * mu_y;
       //Serial.print("("); Serial.print(y_idx); Serial.print(", "); Serial.print(x_idx); Serial.print(") = ");
       //Serial.print("("); Serial.print(y); Serial.print(", "); Serial.print(x); Serial.print(") = ");
       get_adjacents_2d(src, adj_2d, src_rows, src_cols,(int) x, (int) y);
       /*
       Serial.print("[");
       for (uint8_t i=0; i<16; i++) {
         Serial.print(adj_2d[i]); Serial.print(", ");
       }
       Serial.println("]");
       */
       float frac_x = x - (int)x; // we only need the ~delta~ between the points
       float frac_y = y - (int)y; // we only need the ~delta~ between the points
       float out = bicubicInterpolate(adj_2d, frac_x, frac_y);
       //Serial.print("\tInterp: "); Serial.println(out);
       set_point(dest, dest_rows, dest_cols, x_idx, y_idx, out);
    }
  }
}
void amg88xx_ShowPixels(float *buf,float *buf_2d)
{               
        float max = 0.0;
        float min = 0.0;
        float ctr = 0.0;
               // uint16_t colorIndex = 0;
	interpolate_image(buf,8,8,buf_2d,40,40);//将pixels数组中的8*8放大到40*40，保存在dest_2d中
			//循环找到数组中的最大值和最小值
	for(int i = 1; i <= 1600; i++)
	{
				if(i == 1)
				{
					max = buf_2d[i-1];
					min = buf_2d[i-1];
				}
				else
				{
					if(buf_2d[i-1] > max)
						max = buf_2d[i-1];
					if(buf_2d[i-1] < min)
						min = buf_2d[i-1];
				}
	}
			
			//计算出中心点四个温度数据的平均温度作为中心点温度
	ctr = (buf_2d[739]+buf_2d[740]+buf_2d[779]+buf_2d[780])/4;
			
			//将dest_2d中的40*40温度数据转换为对应温度保存在camColors数组中
			//1、对dest_2d数组中的数据进行归一化
			//2、确定温度归一化的数据colorIndex在1到255之间
			//3、根据归一化的数据在camColors找到对应的颜色，保存在arrColor数组中
	for(int y = 1; y <= 1600;y++)
	{
		uint8_t colorIndex =(uint8_t) map(buf_2d[y-1], min, max, 0, 255);
		//colorIndex = (uint8_t)(constrain(colorIndex, 1, 255));//无符号数永远大于或等于0
                
                if (colorIndex <= 1)
                  colorIndex = 1;
                else if(colorIndex >= 255)
                  colorIndex = 255;
             
		arrColor[y-1] = camColors[colorIndex];
	}
	//将arrColor数组中的颜色数据显示在LCD屏幕上
	show(arrColor);
	
	//LCD屏幕上显示最大值、最小值、中心值数据
	LCD.Write.XLine(16,"Max:%6.3f",max);
        LCD.Write.XLine(17,"Min:%6.3f",min);
        LCD.Write.XLine(18,"Ctr:%6.3f",ctr);

}