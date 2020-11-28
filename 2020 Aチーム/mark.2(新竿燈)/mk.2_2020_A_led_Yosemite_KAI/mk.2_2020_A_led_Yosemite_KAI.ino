#include <FastLED.h>
#include <stdlib.h>
#include "lib.h"
#define led2no 4
#define led3no 12
#define led4no 12
#define led5no 12
#define led6no 8

/*CRGB 列の番号[LEDの総数]*/
CRGB led2[led2no];
CRGB led3[led3no];
CRGB led4[led4no];
CRGB led5[led5no];
CRGB led6[led6no];

#if FASTLED_ALLOW_INTERRUPTS==0
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
      nextTime=interval+nextTime;
      return true;
    }else{
      return false;
    }
  }
  operator bool(){return ist();}
  void set(unsigned long val){interval=val;}
  unsigned long read(){return interval;}
};
#endif

rob::aXbeeArduinoHardwareSerial xbeeSerial(Serial);
rob::aXbeeCoreCallback<3> xbeeCore(&xbeeSerial);
rob::aXbeeCom doragon(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9D,0x4D));
rob::aXbeeCom controller(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9C,0xF1));
rob::aXbeeCom kantoMK1(xbeeCore,rob::xbee64bitAddress(0x00,0x13,0xa2,0x00,0x40,0xCA,0x9C,0x79));



//rob::aXbeeCom 名前（xbeeCore,rob::xbee64bitAddress(アドレス))

static int changecount=0;
static int saturation=0;
static int ledno=0;
static int hue=0;
static int lightpower=0;
static int value=0;
static int ledcount=0;
static char DangerousDate='S';

void check(){
  FastLED.show();  
}

void DangerousAngle(uint8_t array[],uint16_t arrayLen){
    //第一で通信の8bit配列データ。第二で配列の文字数
    /*if(arrayLen==1){//ミスの確認　アスキーコードでR赤　N戻す
      return;
    }*/
    DangerousDate=array[0];
    if(digitalRead(13)==HIGH){
    digitalWrite(13,LOW);
  }else{
    digitalWrite(13,HIGH);
  }
}   
  
void LED(){
  
 /* byte sendArray[]={1,ledcount};
  kantoMK1.send(sendArray,2);
  //初めに指定した名前*/
  
  if(DangerousDate=='S'){
  //はじまりの前
    for(ledno = 0; ledno <led2no ; ledno++) {
      led2 [ledno]= CHSV(hue,255,0);
      check();
    }
    for(ledno = 0; ledno <led3no ; ledno++) {
      led3 [ledno]= CHSV(hue,255,0);
      check();
    }
    for(ledno = 0; ledno <led4no ; ledno++) {
      led4 [ledno]= CHSV(hue,255,0);
      check();
    }
    for(ledno = 0; ledno <led5no ; ledno++) {  
      led5 [ledno]= CHSV(hue,255,0);
      check();
    }
    for(ledno = 0; ledno <led6no ; ledno++) {  
      led6 [ledno]= CHSV(hue,255,0);
      check();
    }
  }
  
  
  else if(DangerousDate=='R'){
    changecount++;
  //赤化
    hue=96;
    for(ledno = 0; ledno <led2no ; ledno++) {
      led2 [ledno]= CHSV(hue,255,255);
      check();
    }
    for(ledno = 0; ledno <led3no ; ledno++) {
      led3 [ledno]= CHSV(hue,255,255);
      check();
    }
    for(ledno = 0; ledno <led4no ; ledno++) {
      led4 [ledno]= CHSV(hue,255,255);
      check();
    }
    for(ledno = 0; ledno <led5no ; ledno++) {  
      led5 [ledno]= CHSV(hue,255,255);
      check();
    }
    for(ledno = 0; ledno <led6no ; ledno++) {  
      led6 [ledno]= CHSV(hue,255,255);
      check();
    }
  }
  else if(DangerousDate=='N'){
    changecount++;
    switch(ledcount){      
      
      case 0:
      
      //ろうそくのやつ
        saturation=240;
        hue=85;
        FastLED.setBrightness(255);
        lightpower=random(235,255);
        for(ledno = 0; ledno <led2no ; ledno++) {
          led2 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led3no ; ledno++) {
          led3 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led4no ; ledno++) {
          led4 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led5no ; ledno++) {  
          led5 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led6no ; ledno++) {  
          led6 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        if(changecount>350){//400大体50秒ぐらい
          ledcount++;
          lightpower=255;
          changecount=0;
          //Serial.println("candleled end");
          byte sendArray[]={1,1};
          kantoMK1.send(sendArray,2);
        }
        break;
                  
      case 1:
      //ろうそくからゲーミンgu
        FastLED.setBrightness(255);
        for(ledno = 0; ledno <led2no ; ledno++) {
          led2 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led3no ; ledno++) {
          led3 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led4no ; ledno++) {
          led4 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led5no ; ledno++) {  
          led5 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        for(ledno = 0; ledno <led6no ; ledno++) {  
          led6 [ledno]= CHSV(hue,saturation,lightpower);
          check();
        }
        lightpower=lightpower-10;
        if(changecount>24){
          ledcount++;
          changecount=0;
          //Serial.println("candlechange end");
          byte sendArray[]={1,2};
          kantoMK1.send(sendArray,2);
        }
        break;       

      case 2:
      //ウェーブ的なゲーミング    
        FastLED.setBrightness(255);     
        for(ledno = 0; ledno <led2no ; ledno++) {
          led2 [ledno]= CHSV(hue,255,255);
          check();
        }
        for(ledno = 0; ledno <led3no ; ledno++) {
          led3 [ledno]= CHSV(hue+30,255,255);
          check();
        }
        for(ledno = 0; ledno <led4no ; ledno++) {
          led4 [ledno]= CHSV(hue+60,255,255);
          check();
        }
        for(ledno = 0; ledno <led5no ; ledno++) {  
          led5 [ledno]= CHSV(hue+90,255,255);
          check();
        }
        for(ledno = 0; ledno <led6no ; ledno++) {  
          led6 [ledno]= CHSV(hue+120,255,255);
          check();
        }
        hue=hue+25;
        //Serial.println("gaming");
        if(hue>255){
          hue=0;
        }
        if(changecount>550){
          ledcount++;
          changecount=0;
          ledcount=0;
          //Serial.println("gaming end"); 
        }
        break;  
    }
  }
}         
        
 
void setup() { 
  //Serial.begin(9600);
  /*FastLED.addLeds<種類,ポート番号>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,led2no);
  FastLED.addLeds<WS2812,3>(led3,led3no);
  FastLED.addLeds<WS2812,4>(led4,led4no);
  FastLED.addLeds<WS2812,5>(led5,led5no);
  FastLED.addLeds<WS2812,6>(led6,led6no);
  xbeeSerial.begin(115200);
  doragon.attach(DangerousAngle);
  controller.attach(DangerousAngle);
  byte sendArray[]={1,0};
  kantoMK1.send(sendArray,2);
  
  //初めにアドレス書いたやつ（通信の対象）.attach(通信が来た時に呼び出す関数（ここに書いとけばvoidloopに書かなくてもいい));

  pinMode(13,OUTPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
}
 
void loop(){
  digitalWrite(9,LOW);
  xbeeCore.check();
  digitalWrite(9,HIGH);
  static regularC lockTime(100);
  if(lockTime){
    LED();
  }
  //Serial.println("voidloop");

}
