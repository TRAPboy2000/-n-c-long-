#ifndef TCS3200_H
#define TCS3200_H
#include <stdlib.h>
#include<Arduino.h>
#include<math.h>
const float f_w[3] = {187.26, 197.94, 245.69};
const float f_d[3] = {8.98, 10.97, 14.95};


typedef struct
{
  char label;
  uint8_t data[3];
  float d;
}c_m;

typedef struct 
{
  char label;
  uint8_t count;
}knn;


extern c_m sample[];




typedef struct
{
	uint8_t S0, S1, S2, S3, sensorOut;
}TCS3200;





TCS3200 *TCS3200_init(uint8_t S0, uint8_t S1, uint8_t S2, uint8_t S3, uint8_t sensorOut);
void TCS3200_cleanUp(TCS3200 *self);
void TCS3200_setFreqScale(TCS3200 *self, int8_t freqScale);
void TCS3200_setFilter(TCS3200 *self, char channel);
void TCS3200_getRaw(TCS3200 *self, float *r_d);
void RGB(float *r_data, uint8_t *rgb);
char color_match(uint8_t *rgb, uint8_t k);
static void merge(c_m *ptr, uint8_t beg, uint8_t mid, uint8_t End);
static void mergeSort(c_m *ptr, uint8_t beg, uint8_t End);
#endif
