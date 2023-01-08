#include "tcs3200.h"  

c_m sample[] =
{ 
  {'r', {255, 62, 60}},
  {'r', {64, 5, 6}},
  {'r', {107, 11, 8}},
  {'r', {124, 18, 17}},
  {'r', {129, 9, 11}},
  {'r', {150, 14, 17}},
  {'r', { 107,11,8}},
  {'r', { 104,13,10}},
  {'r', { 110,14,13}},
  {'r', { 115,16,14}},
  {'r', { 118,16,15}},
  {'r', { 122,17,16}},
  {'r', { 122,17,16}},
  {'r', { 123,18,17}},
  {'r', { 124,18,17}},
  {'r', { 124,18,17}},
  {'r', { 136,14,17}},
  {'r', { 156,19,22}},
  {'r', { 138,19,16}},
  {'r', { 130,18,16}},
  {'g', {66, 116, 69}},
  {'g', {16, 48, 26}},
  {'g', {23, 48, 22}},
  {'g', {15, 33, 13}},
  {'g', {22, 40, 16}},
  {'g', {8, 28, 9}},
  {'g', {4,15,2}},
  {'g', {7,23,7}},
  {'g', {10,28,9}},
  {'g', {12,30,11}},
  {'g', {13,31,12}},
  {'g', {15,34,14}},
  {'g', {17,37,12}},
  {'g', {17,33,9}},
  {'g', {14,22,4}},
  {'g', {9,10,0}},
  {'g', {9,22,8}},
  {'g', {12,29,11}},
  {'g', {15,34,14}},
  {'g', {3,12,2}}, 
  {'b', {10, 58, 103}},
  {'b', {13, 57, 95}},
  {'b', {12, 65, 117}},
  {'b', {48, 118, 179}},
  
  {'b', {16,60,105}},
  {'b', {16,58,95}},
  {'b', {7,56,112}},
  {'b', {10,62,116}},
  {'b', {13,66,117}},
  {'b', {15,67,117}},
  {'b', {16,68,117}},
  {'b', {17,68,115}},
  {'b', {17,67,113}},
  {'b', {17,66,112}},
  {'b', {18,67,113}},
  {'b', {18,68,115}},
  {'b', {19,68,117}},
  {'b', {19,68,113}},
  {'b', {8,51,97}},
  {'b', {10,55,102}},
  {'b', {11,58,105}},
  {'b', {13,61,109}},
  {'b', {14,63,110}},
  {'b', {15,63,105}},
  {'b', {9,58,108}},
  {'b', {12,60,106}},
  {'b', {16,59,102}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
   {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'W', {255, 255, 255}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}}, 
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}}, 
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}}, 
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  {'B', {0, 0, 0}},
  
};



TCS3200 *TCS3200_init(uint8_t _S0, uint8_t _S1, uint8_t _S2, uint8_t _S3, uint8_t sensorOut)
{
	TCS3200 *self = (TCS3200*)malloc(sizeof(TCS3200));
	self->S0 = _S0;		
	self->S1 = _S1;
	self->S2 = _S2;
	self->S3 = _S3;
	self->sensorOut = sensorOut;
	uint8_t temp[] = {self->S0, self->S1, self->S2, self->S3}; 
	for(uint8_t i = 0; i < sizeof(temp) / sizeof(uint8_t); i++)
	{
		pinMode(temp[i], OUTPUT);
	}
  pinMode(self->sensorOut, INPUT);
 
	return self;
}



void TCS3200_clean_up(TCS3200 *self)
{
	free(self);
}



void TCS3200_setFreqScale(TCS3200 *self, int8_t freqScale)
{
	switch(freqScale)
	{
		case 0:
			digitalWrite(self->S0, 0);
			digitalWrite(self->S1, 0);
			break;
		case 2:
			digitalWrite(self->S0, 0);
			digitalWrite(self->S1, 1);
			break;
		case 20:
			digitalWrite(self->S0, 1);
			digitalWrite(self->S1, 0);
			break;
		case 100:
			digitalWrite(self->S0, 1);
			digitalWrite(self->S1, 1);
			break;
	}
}


void TCS3200_setFilter(TCS3200 *self, char channel)
{
	switch(channel)
	{
		case 'r':
			digitalWrite(self->S2, 0);
			digitalWrite(self->S3, 0);
			break;
		case 'b':
			digitalWrite(self->S2, 0);
			digitalWrite(self->S3, 1);
			break;
		case 'g':
			digitalWrite(self->S2, 1);
			digitalWrite(self->S3, 1);
			break;
		case 'n':
			digitalWrite(self->S2, 1);
			digitalWrite(self->S3, 0);
			break;
	}	
}


void TCS3200_getRaw(TCS3200 *self, float *r_d)
{
  TCS3200_setFilter(self, 'r');
  r_d[0] = (100000.0)/(2*pulseIn(self->sensorOut, LOW));
  delay(10);
  TCS3200_setFilter(self, 'g');
  r_d[1] = (100000.0)/(2*pulseIn(self->sensorOut, LOW));
  delay(10);
  TCS3200_setFilter(self, 'b');
  r_d[2] =(100000.0)/(2*pulseIn(self->sensorOut, LOW));
  delay(10);
}

void RGB(float *r_data, uint8_t *rgb)
{
   for(uint8_t i = 0; i < 3; i++)
   {
      float temp = (255*(r_data[i] - f_d[i])) /(f_w[i] - f_d[i]);
      if(temp < 0)
      {
        rgb[i] = 0;
      }
      else if(temp > 255)
      {
        rgb[i] = 255;
      }
      else
      {
        rgb[i] = temp;
      }
   }
}

static void merge(c_m *ptr, uint8_t beg, uint8_t mid, uint8_t End)    
{    
    uint8_t i, j, k;  
    uint8_t n1 = mid - beg + 1;    
    uint8_t n2 = End - mid;    
      
    c_m LeftArray[n1], RightArray[n2]; 
      
      
    for (uint8_t i = 0; i < n1; i++)    
      LeftArray[i] = ptr[beg + i];    
    for (uint8_t j = 0; j < n2; j++)    
      RightArray[j] = ptr[mid + 1 + j];    
      
    i = 0, 
    j = 0;    
    k = beg;
      
    while (i < n1 && j < n2)    
    {    
        if(LeftArray[i].d <= RightArray[j].d)    
        {    
            ptr[k] = LeftArray[i];    
            i++;    
        }    
        else    
        {    
            ptr[k] = RightArray[j];    
            j++;    
        }    
        k++;    
    }    
    while (i<n1)    
    {    
        ptr[k] = LeftArray[i];    
        i++;    
        k++;    
    }    
      
    while (j<n2)    
    {    
        ptr[k] = RightArray[j];    
        j++;    
        k++;    
    }    
}    


static void mergeSort(c_m *ptr, uint8_t beg, uint8_t End)  
{  
    if(beg < End)   
    {  
        int mid = (beg + End) / 2;  
        mergeSort(ptr, beg, mid);  
        mergeSort(ptr, mid + 1, End);  
        merge(ptr, beg, mid, End);  
    }  
}  


char color_match(uint8_t *rgb, uint8_t k)
{
   size_t len = sizeof(sample) / sizeof(c_m);
   for(uint8_t i = 0; i < len; i++)
   {
      float s = 0;
      for(uint8_t j = 0; j < 3; j++)
      {
        s += pow(sample[i].data[j] - rgb[j], 2);
      }
      sample[i].d = sqrt(s);
   }
   mergeSort(sample, 0, len - 1);
   uint8_t r = 0; 
   uint8_t g = 0; 
   uint8_t b = 0; 
   uint8_t W = 0; 
   uint8_t B = 0;
   char label;
   for(uint8_t i = 0; i < k; i++)
   { 
      switch(sample[i].label)
      {
        case 'r':
          r++;
          break;
        case 'g':
          g++;
          break;
        case 'b':
          b++;
          break;
        case 'W':
          W++;
          break;
        case 'B':
          B++;
          break;   
      }
   } 
   Serial.print(r);
   Serial.print(" ");
   Serial.print(g);
   Serial.print(" ");
   Serial.print(b);
   Serial.print(" ");
   Serial.print(W);
   Serial.print(" ");
   Serial.println(B);
    if(r > g && r > b && r > W && r > B)
      {
        label = 'r';
        
      }
      else if(g > r && g > b && g > W && g > B)
      {
        label = 'g';
      }
      else if(b > r && b > g && b > W && b > B)
      {
        label = 'b';
      }
      else if(W > r && W > g && W > B && W > b)
      {
        label =  'W';
      }
      else if(B > r && B > g && B > W && B > b)
      {
        label =  'B';
      }
   return label;  
}
