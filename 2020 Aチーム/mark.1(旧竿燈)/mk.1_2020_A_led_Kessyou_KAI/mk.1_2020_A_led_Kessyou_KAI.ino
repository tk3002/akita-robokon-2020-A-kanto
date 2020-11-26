/*
 タイミングの同期

 Nで通常モード
 Sで停止
 Rで赤化

 
 */

#include <FastLED.h>
#include <stdlib.h>
#include "lib.h"
#define led2no 4
#define led3no 8
#define led4no 12
#define led5no 8

/*CRGB 列の番号[LEDの総数]*/
CRGB led2[led2no];
CRGB led3[led3no];
CRGB led4[led4no];
CRGB led5[led5no];


class regularC{
private:
  unsigned long interval;
  unsigned long nextTime;
public:
  regularC(unsigned long intervalArg,unsigned long start=0):
    interval(intervalArg)
  {
    nextTime=start;
  }
  bool ist(){
    if(nextTime<millis()){
      nextTime=interval+millis();
      return true;
    }else{
      return false;
    }
  }
  operator bool(){return ist();}
  void set(unsigned long val){interval=val;}
  unsigned long read(){return interval;}
};

rob::aXbeeArduinoHardwareSerial xbeeSerial(Serial);
rob::aXbeeCoreCallback<3> xbeeCore(&xbeeSerial);
rob::aXbeeCom tomoshibi(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9D,0x3B));
rob::aXbeeCom controller(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9C,0xF1));
rob::aXbeeCom kantoMK2(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9D,0x0B));
//rob::aXbeeCom -名前-（xbeeCore,rob::xbee64bitAddress(-アドレス-))

static int changecount=0;
static int saturation=0;
static int ledno=0;
static int hue=0;
static int lightpower=0;
static int value=0;
static int ledcount=0;
static byte timingDate=0;
static int case4rotation=0;
static char DangerousDate='N';


void DangerousAngle(uint8_t array[],uint16_t arrayLen){
    //第一で通信の8bit配列データ。第二で配列の文字数
    /*if(arrayLen==1){//ミスの確認　アスキーコードでR赤　N戻す
      return;
    }*/
    DangerousDate=array[0];
}   

void timing(uint8_t sendArray[],uint16_t sendArrayLen){
  Serial.println("timing");
  if(sendArray[0]==1){
    timingDate=1;
  }
  ledcount=sendArray[1];
  case4rotation=sendArray[2];
}
  
void LED(){
  if(timingDate==1){
    timingDate=0;
    if(DangerousDate=='S'){
    //はじまりの前
      for(ledno = 0; ledno <led2no ; ledno++) {
        led2 [ledno]= CHSV(hue,255,0);
        FastLED.show();
      }
      for(ledno = 0; ledno <led3no ; ledno++) {
        led3 [ledno]= CHSV(hue,255,0);
        FastLED.show();
      }
      for(ledno = 0; ledno <led4no ; ledno++) {
        led4 [ledno]= CHSV(hue,255,0);
        FastLED.show();
      }
      for(ledno = 0; ledno <led5no ; ledno++) {  
        led5 [ledno]= CHSV(hue,255,0);
        FastLED.show();
      }
    }
    
    if(DangerousDate=='R'){
    //赤化
      hue=96;
      for(ledno = 0; ledno <led2no ; ledno++) {
        led2 [ledno]= CHSV(hue,255,255);
        FastLED.show();
      }
      for(ledno = 0; ledno <led3no ; ledno++) {
        led3 [ledno]= CHSV(hue,255,255);
        FastLED.show();
      }
      for(ledno = 0; ledno <led4no ; ledno++) {
        led4 [ledno]= CHSV(hue,255,255);
        FastLED.show();
      }
      for(ledno = 0; ledno <led5no ; ledno++) {  
        led5 [ledno]= CHSV(hue,255,255);
        FastLED.show();
      }
    }
    if(DangerousDate=='N'){
      switch(ledcount){
        case 0:
        //ろうそくのやつ
          saturation=240;
          hue=85;
          FastLED.setBrightness(255);
          lightpower=random(235,255);
          for(ledno = 0; ledno <led2no ; ledno++) {
            led2 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led3no ; ledno++) {
            led3 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led4no ; ledno++) {
            led4 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led5no ; ledno++) {  
            led5 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          Serial.println("candleled");
          break;
                    
        case 1:
        //ろうそくからゲーミンgu
          FastLED.setBrightness(255);
          for(ledno = 0; ledno <led2no ; ledno++) {
            led2 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led3no ; ledno++) {
            led3 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led4no ; ledno++) {
            led4 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          for(ledno = 0; ledno <led5no ; ledno++) {  
            led5 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          lightpower=lightpower-10;
          break;       
  
        case 2:
        //ウェーブ的なゲーミング     
          FastLED.setBrightness(255);     
          for(ledno = 0; ledno <led2no ; ledno++) {
            led2 [ledno]= CHSV(hue,255,255);
            FastLED.show();
          }
          for(ledno = 0; ledno <led3no ; ledno++) {
            led3 [ledno]= CHSV(hue+30,255,255);
            FastLED.show();
          }
          for(ledno = 0; ledno <led4no ; ledno++) {
            led4 [ledno]= CHSV(hue+60,255,255);
            FastLED.show();
          }
          for(ledno = 0; ledno <led5no ; ledno++) {  
            led5 [ledno]= CHSV(hue+90,255,255);
            FastLED.show();
          }
          hue=hue+25;
          Serial.println("gaming");
          if(hue>255){
            hue=0;
          }
          break;  
        
        case 3:
          for(hue = 25.5; hue < 224.5; hue=hue+25.5) {
           //ゆっくりついてゆっくり消える
           for(lightpower=0;lightpower<255;lightpower=lightpower+25){
             for(ledno = 0; ledno <led2no ; ledno++) {
               led2 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led3no ; ledno++) {
               led3 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led4no ; ledno++) {
               led4 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led5no ; ledno++) {  
               led5 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }             
           }
           for(lightpower=255;lightpower>0;lightpower=lightpower-25){
             for(ledno = 0; ledno <led2no ; ledno++) {
               led2 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led3no ; ledno++) {
               led3 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led4no ; ledno++) {
               led4 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
             for(ledno = 0; ledno <led5no ; ledno++) {  
               led5 [ledno]= CHSV(hue,255,lightpower);
               FastLED.show();
             }
           }  
         }   
         break; 

        case 4:
        //回レ回レ
          FastLED.setBrightness(255);
          if(hue>224.5){
              hue = 25.5;
          }
          switch(case4rotation){
            case 10:    
              hue=hue+25.5;     
              for(ledno = 0; ledno <led2no; ledno++){
                led2 [ledno]= CRGB(0,0,0);
                FastLED.show();
              }
              for(ledno = 0; ledno <led3no; ledno++){
                led3 [ledno]= CRGB(0,0,0);
                FastLED.show();
              }
              for(ledno = 0; ledno <led4no; ledno++){
                led4 [ledno]= CRGB(0,0,0);
                FastLED.show();
              }
              for(ledno = 0; ledno <led5no; ledno++){  
                led5 [ledno]= CRGB(0,0,0);
                FastLED.show();
              }
            break;
          case 11:
            led3[0]=CHSV(hue,255,255);FastLED.show();
            led3[1]=CHSV(hue,255,255);FastLED.show();
            led3[6]=CHSV(hue,255,255);FastLED.show();
            led3[7]=CHSV(hue,255,255);FastLED.show();
            break;
          case 12:
            led4[0]=CHSV(hue,255,255);FastLED.show();
            led4[1]=CHSV(hue,255,255);FastLED.show();
            led4[2]=CHSV(hue,255,255);FastLED.show();
            led4[3]=CHSV(hue,255,255);FastLED.show();
            led4[8]=CHSV(hue,255,255);FastLED.show();
            led4[9]=CHSV(hue,255,255);FastLED.show();
            led4[10]=CHSV(hue,255,255);FastLED.show();
            led4[11]=CHSV(hue,255,255);FastLED.show();
            break;
          case 13:
            led4[0]=CHSV(hue,255,255);FastLED.show();
            led4[1]=CHSV(hue,255,255);FastLED.show();
            led4[2]=CHSV(hue,255,255);FastLED.show();
            led4[3]=CHSV(hue,255,255);FastLED.show();
            led4[8]=CHSV(hue,255,255);FastLED.show();
            led4[9]=CHSV(hue,255,255);FastLED.show();
            led4[10]=CHSV(hue,255,255);FastLED.show();
            led4[11]=CHSV(hue,255,255);FastLED.show();
            break;
          case 14:
            led5[0]=CHSV(hue,255,255);FastLED.show();
            led5[1]=CHSV(hue,255,255);FastLED.show();
            led5[6]=CHSV(hue,255,255);FastLED.show();
            led5[7]=CHSV(hue,255,255);FastLED.show();
            break;
          case 15:
            led5[2]=CHSV(hue,255,255);FastLED.show();
            led5[3]=CHSV(hue,255,255);FastLED.show();
            led5[4]=CHSV(hue,255,255);FastLED.show();
            led5[5]=CHSV(hue,255,255);FastLED.show();
            led3[2]=CRGB(0,0,0);FastLED.show();
            led3[3]=CRGB(0,0,0);FastLED.show();
            led3[4]=CRGB(0,0,0);FastLED.show();
            led3[5]=CRGB(0,0,0);FastLED.show();
            break;
          case 16:
            led4[4]=CHSV(hue,255,255);FastLED.show();
            led4[5]=CHSV(hue,255,255);FastLED.show();
            led4[6]=CHSV(hue,255,255);FastLED.show();
            led4[7]=CHSV(hue,255,255);FastLED.show();
            led2[0]=CRGB(0,0,0);FastLED.show();
            led2[1]=CRGB(0,0,0);FastLED.show();
            led2[2]=CRGB(0,0,0);FastLED.show();
            led2[3]=CRGB(0,0,0);FastLED.show();
            break;
          case 17:
            led3[2]=CHSV(hue,255,255);FastLED.show();
            led3[3]=CHSV(hue,255,255);FastLED.show();
            led3[4]=CHSV(hue,255,255);FastLED.show();
            led3[5]=CHSV(hue,255,255);FastLED.show();
            led3[0]=CRGB(0,0,0);FastLED.show();
            led3[1]=CRGB(0,0,0);FastLED.show();
            led3[6]=CRGB(0,0,0);FastLED.show();
            led3[7]=CRGB(0,0,0);FastLED.show();
            break;
          case 18:
            led2[0]=CHSV(hue,255,255);FastLED.show();
            led2[1]=CHSV(hue,255,255);FastLED.show();
            led2[2]=CHSV(hue,255,255);FastLED.show();
            led2[3]=CHSV(hue,255,255);FastLED.show();
            led4[0]=CRGB(0,0,0);FastLED.show();
             led4[1]=CRGB(0,0,0);FastLED.show();
            led4[2]=CRGB(0,0,0);FastLED.show();
            led4[3]=CRGB(0,0,0);FastLED.show();
            led4[8]=CRGB(0,0,0);FastLED.show();
            led4[9]=CRGB(0,0,0);FastLED.show();
            led4[10]=CRGB(0,0,0);FastLED.show();
            led4[11]=CRGB(0,0,0);FastLED.show();
            break;
          case 19:
            led5[0]=CRGB(0,0,0);FastLED.show();
            led5[1]=CRGB(0,0,0);FastLED.show();
            led5[6]=CRGB(0,0,0);FastLED.show();
            led5[7]=CRGB(0,0,0);FastLED.show();
            break;
          case 20:
            led5[2]=CRGB(0,0,0);FastLED.show();
            led5[3]=CRGB(0,0,0);FastLED.show();
            led5[4]=CRGB(0,0,0);FastLED.show();
            led5[5]=CRGB(0,0,0);FastLED.show();
            break;
          case 21:
            led4[4]=CRGB(0,0,0);FastLED.show();
            led4[5]=CRGB(0,0,0);FastLED.show();
            led4[6]=CRGB(0,0,0);FastLED.show();
            led4[7]=CRGB(0,0,0);FastLED.show();
            break;
          case 22:
            led4[4]=CRGB(0,0,0);FastLED.show();
            led4[5]=CRGB(0,0,0);FastLED.show();
            led4[6]=CRGB(0,0,0);FastLED.show();
            led4[7]=CRGB(0,0,0);FastLED.show();
            break;
          case 23:
            led3[2]=CRGB(0,0,0);FastLED.show();
            led3[3]=CRGB(0,0,0);FastLED.show();
            led3[4]=CRGB(0,0,0);FastLED.show();
            led3[5]=CRGB(0,0,0);FastLED.show();
            break;
          }  
        break; 
      }
    }
  }  
}         
        
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<種類,ポート番号,色の形式RGBとか>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,led2no);
  FastLED.addLeds<WS2812,3>(led3,led3no);
  FastLED.addLeds<WS2812,4>(led4,led4no);
  FastLED.addLeds<WS2812,5>(led5,led5no);
  xbeeSerial.begin(38400);
  tomoshibi.attach(DangerousAngle);
  controller.attach(DangerousAngle);
  kantoMK2.attach(timing);
  //初めにアドレス書いたやつ（通信の対象）.attach(通信が来た時に呼び出す関数（ここに書いとけばvoidloopに書かなくてもいい));
}
 
void loop(){
  LED();
  xbeeCore.check();
  Serial.println("loop");
}
