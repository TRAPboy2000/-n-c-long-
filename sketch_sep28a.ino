#include "tcs3200.h"
#include "SimpleKalmanFilter.h"
#include "CircularQueue.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
uint8_t test_rgb[] = {10, 23, 45};
#define S0 7
#define S1 6
#define S2 4
#define S3 3
#define rawDataTest 1
#define RGBTest 2
#define colorTest 3
#define sensorOut 5
#define xylanhXanh 9 
#define xylanhDo 8
#define ir 10
uint32_t r = 0;
uint32_t g = 0;
uint32_t b = 0;
uint8_t rgb[3];
float r_data[3];
char l;
uint8_t r_count = 0;
uint8_t b_count = 0;
uint8_t g_count = 0;
uint8_t s;
uint32_t t;
product d;
uint8_t s_state = 0;
uint32_t test_begin;
uint8_t total = 0;
typedef enum
{
  CHUA_CO_SAN_PHAM,
  DAY_RA,
  DOI_DAY_RA,
  RUT_LAI,
  DOI_RUT_LAI
}trangThaiXylanh;


typedef enum
{
  IR1,
  IR1_TRAP,
  IR1_PASS,
  WAITING,
  DOC_CAM_BIEN,
  TRAP
}camBien;

uint8_t state = 0;
typedef struct
{
  uint8_t trangthai1, trangthai2, trangthai3, camBienMau;
}he_thong_phan_loai;

he_thong_phan_loai phan_loai_mau;
TCS3200 *CS = TCS3200_init(S0, S1, S2, S3, sensorOut);
SimpleKalmanFilter RF = SimpleKalmanFilter(10, 5, 0.7);
SimpleKalmanFilter GF = SimpleKalmanFilter(10, 5, 0.7);
SimpleKalmanFilter BF = SimpleKalmanFilter(10, 5, 0.7); 
Queue *red_queue = queue_init(20);
Queue *green_queue = queue_init(20);
void f(float *r_d)
{
  r_d[0] = RF.updateEstimate(r_d[0]);
  r_d[1] = GF.updateEstimate(r_d[1]);
  r_d[2] = BF.updateEstimate(r_d[2]);
}
uint8_t calibrate(uint8_t state, float *r_data)
{
  static uint16_t i = 0;
  static uint32_t s1 = 0;
  static uint32_t s2 = 0;
  static uint32_t s3 = 0;
  switch(state)
  {
    case 0:
      i++;
      if(i >= 5)
      {
        state++;
      }
      break;
    case 1:
        Serial.println(i - 5);
        TCS3200_getRaw(CS, r_data);
        f(r_data);
        s1 += r_data[0];
        s2 += r_data[1];
        s3 += r_data[2];
        i++;
        if(i >= 1005)
        {
          Serial.print((float)s1 / 1000);
          Serial.print(", ");
          Serial.print((float)s2 / 1000);
          Serial.print(", ");
          Serial.print((float)s3 / 1000);
          while(1);
        }
      
  }
  return state;
}



void NhanDienMau(he_thong_phan_loai *s)
{ 
    TCS3200_setFreqScale(CS, 2);
    switch(s->camBienMau)
    {
      case IR1:
        if(!digitalRead(ir))
        {
          s->camBienMau = IR1_TRAP;
          t = millis();
          break;
        }
        break;
      case IR1_TRAP:
        if(millis() - t >= 100)
        {
          if(!digitalRead(ir))
          {
            s->camBienMau = IR1_PASS;
            break;
          }
          else if(digitalRead(ir))
          {
            s->camBienMau = IR1;
            break;
          }
        }
        case IR1_PASS:
          if(digitalRead(ir))
          {
            s->camBienMau = WAITING;
            t = millis();
            break;
          }
          break;
        case WAITING:
          if(millis() - t >= 50)
          {
            s->camBienMau = DOC_CAM_BIEN;
            break;
          }
           TCS3200_getRaw(CS, r_data);
           f(r_data);
          break;
        case DOC_CAM_BIEN:
          TCS3200_getRaw(CS, r_data);
          f(r_data);
          RGB(r_data, rgb);
          l = color_match(rgb, 20);
          Serial.println(l);
          switch(l)
          {
            case 'r':
              d.n = 'r';
              d.timePass = millis();
              Enqueue(red_queue, d); 
              r++;
              break;
            case 'g':
              d.n = 'g';
              d.timePass = millis();
              Enqueue(green_queue, d);
              g++;
              break;
            case 'b':
              b++;
          }
          lcd.setCursor(4, 0);
          lcd.print(r);
          lcd.setCursor(6, 1);
          lcd.print(g);
          lcd.setCursor(5, 2);
          lcd.print(b);
          s->camBienMau = IR1;
          break;
    }
}


void test(uint8_t  test_mode)
{
  TCS3200_getRaw(CS, r_data);
  f(r_data);
  RGB(r_data, rgb);
  if(test_mode == RGBTest)
  {
    Serial.print(rgb[0]);
    Serial.print(",");
    Serial.print(rgb[1]);
    Serial.print(",");
    Serial.println(rgb[2]);
  }
  else if(test_mode == rawDataTest) 
  {
    Serial.print(r_data[0]);
    Serial.print(",");
    Serial.print(r_data[1]);
    Serial.print(",");
    Serial.println(r_data[2]);  
  }
  else if()
  {
    Serial.println(color_match(rgb, 20));
  }
 
    
}

void xylanh_mau_do(he_thong_phan_loai *phan_loai_mau)
{
  static uint32_t thoigian;
  switch(phan_loai_mau->trangthai1)
  {
    case CHUA_CO_SAN_PHAM:
      if(!IsEmpty(red_queue))
      {
        if(millis() - Front(red_queue).timePass >= 1400)
        {
          phan_loai_mau->trangthai1 = DAY_RA;
          break;
        }
      }
      break;
    case DAY_RA:
      digitalWrite(xylanhDo, 1);
      thoigian = millis();
      phan_loai_mau->trangthai1 = DOI_DAY_RA;
      break;
    case DOI_DAY_RA:
      if(millis() - thoigian >= 350)
      {
        phan_loai_mau->trangthai1 = RUT_LAI;
        break;
      }
      break;
    case RUT_LAI:
      digitalWrite(xylanhDo, 0);
      thoigian = millis();
      phan_loai_mau->trangthai1 = DOI_RUT_LAI;
      break;
    case DOI_RUT_LAI:
      if(millis() - thoigian >= 350)
      {
        Dequeue(red_queue);
        phan_loai_mau->trangthai1 = CHUA_CO_SAN_PHAM;
        break;
      }
  }
}






void xylanh_mau_xanhLC(he_thong_phan_loai *phan_loai_mau)
{
  static uint32_t thoigian;
  switch(phan_loai_mau->trangthai2)
  {
    case CHUA_CO_SAN_PHAM:
      if(!IsEmpty(green_queue))
      {
        if(millis() - Front(green_queue).timePass >= 2700)
        {
          phan_loai_mau->trangthai2 = DAY_RA;
          break;
        }
      }
      break;
  
    case DAY_RA:
      digitalWrite(xylanhXanh, 0);
      thoigian = millis();
      phan_loai_mau->trangthai2 = DOI_DAY_RA;
      break;
    case DOI_DAY_RA:
      if(millis() - thoigian >= 350)
      {
        phan_loai_mau->trangthai2 = RUT_LAI;
        break;
      }
      break;
    case RUT_LAI:
      digitalWrite(xylanhXanh, 1);
      thoigian = millis();
      phan_loai_mau->trangthai2 = DOI_RUT_LAI;
      break;
    case DOI_RUT_LAI:
      if(millis() - thoigian >= 350)
      {
        Dequeue(green_queue);
        phan_loai_mau->trangthai2 = CHUA_CO_SAN_PHAM;
        break;
      }
  }
}


void khoitao(he_thong_phan_loai *phan_loai_mau)
{
  phan_loai_mau->trangthai1 = 0;
  phan_loai_mau->trangthai2 = 0;
  phan_loai_mau->camBienMau = 0;
}

void setup() 
{
  Serial.begin(115200);
  TCS3200_setFreqScale(CS, 2);
  pinMode(xylanhDo, OUTPUT);
  pinMode(xylanhXanh, OUTPUT);
  pinMode(ir, INPUT);
  khoitao(&phan_loai_mau);
  digitalWrite(xylanhXanh, 1);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("red: ");
  lcd.setCursor(0, 1);
  lcd.print("green: ");
  lcd.setCursor(0, 2);
  lcd.print("blue: ");
  lcd.setCursor(4, 0);
  lcd.print(r);
  lcd.setCursor(6, 1);
  lcd.print(g);
  lcd.setCursor(5, 2);
  lcd.print(b);
}

void debug()
{
  TCS3200_setFilter(CS, 'r');
  Serial.print(pulseIn(sensorOut , LOW));
  Serial.print(",");
  delay(10);
  TCS3200_setFilter(CS, 'g');
  Serial.print(pulseIn(sensorOut, LOW));
  Serial.print(",");
  TCS3200_setFilter(CS, 'b');
  Serial.println(pulseIn(sensorOut, LOW));
  delay(10);
}



void loop()
{
    // state = calibrate(state, r_data);
    // test(1);
    //debug();
    NhanDienMau(&phan_loai_mau);
    xylanh_mau_do(&phan_loai_mau);
    xylanh_mau_xanhLC(&phan_loai_mau); 
}
