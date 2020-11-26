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
static int case4rotation=10;
static char DangerousDate='N';

void DangerousAngle(uint8_t array[],uint16_t arrayLen){
    //第一で通信の8bit配列データ。第二で配列の文字数
    /*if(arrayLen==1){//ミスの確認　アスキーコードでR赤　N戻す
      return;
    }*/
    DangerousDate=array[0];
    }   
  
void LED(){
  static regularC lockTime(100);
  if(lockTime){
    
    byte sendArray[]={1,ledcount,case4rotation};
    kantoMK1.send(sendArray,3);
    delay(1);
    //初めに指定した名前
    
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
      for(ledno = 0; ledno <led6no ; ledno++) {  
        led5 [ledno]= CHSV(hue,255,0);
        FastLED.show();
      }
    }
    
    
    if(DangerousDate=='R'){
      changecount++;
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
      for(ledno = 0; ledno <led6no ; ledno++) {  
        led6 [ledno]= CHSV(hue,255,255);
        FastLED.show();
      }
    }
    if(DangerousDate=='N'){
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
          for(ledno = 0; ledno <led6no ; ledno++) {  
            led6 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          if(changecount>0){//400
            ledcount++;
            lightpower=255;
            changecount=0;
            //Serial.println("candleled end");
          }
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
          for(ledno = 0; ledno <led6no ; ledno++) {  
            led6 [ledno]= CHSV(hue,saturation,lightpower);
            FastLED.show();
          }
          lightpower=lightpower-10;
          if(changecount>24){
            ledcount++;
            changecount=0;
            //Serial.println("candlechange end");
          }
          break;       
  
        case 2:
        //ウェーブ的なゲーミング
          lockTime.set(1);     
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
          for(ledno = 0; ledno <led6no ; ledno++) {  
            led6 [ledno]= CHSV(hue+120,255,255);
            FastLED.show();
          }
          hue=hue+25;
          //Serial.println("gaming");
          if(hue>255){
            hue=0;
          }
          if(changecount>0){//450
            ledcount++;
            ledcount++;
            changecount=0;
            lockTime.set(1);
            //Serial.println("gaming end"); 
          }
          break;  

        case 3:
          for(hue = 25.5; hue < 224.5; hue=hue+25.5) {
            FastLED.setBrightness(255);
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
              for(ledno = 0; ledno <led6no ; ledno++) {  
                led6 [ledno]= CHSV(hue,255,lightpower);
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
              for(ledno = 0; ledno <led6no ; ledno++) {  
                led6 [ledno]= CHSV(hue,255,lightpower);
                FastLED.show();
              }
            }
            if(changecount>1){
              ledcount++;
              changecount=0;
              lockTime.set(100);
              hue = 25.5;
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
             for(ledno = 0; ledno <led6no; ledno++){  
                led5 [ledno]= CRGB(0,0,0);
                FastLED.show();
              }
              case4rotation++;
              break;
            case 11:
              led3[0]=CHSV(hue,255,255);FastLED.show();
              led3[1]=CHSV(hue,255,255);FastLED.show();
              led3[2]=CHSV(hue,255,255);FastLED.show();
              led3[3]=CHSV(hue,255,255);FastLED.show();
              led3[8]=CHSV(hue,255,255);FastLED.show();
              led3[9]=CHSV(hue,255,255);FastLED.show();
              led3[10]=CHSV(hue,255,255);FastLED.show();
              led3[11]=CHSV(hue,255,255);FastLED.show();
              case4rotation++;
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
              case4rotation++;
              break;
            case 13:
              led5[0]=CHSV(hue,255,255);FastLED.show();
              led5[1]=CHSV(hue,255,255);FastLED.show();
              led5[2]=CHSV(hue,255,255);FastLED.show();
              led5[3]=CHSV(hue,255,255);FastLED.show();
              led5[8]=CHSV(hue,255,255);FastLED.show();
              led5[9]=CHSV(hue,255,255);FastLED.show();
              led5[10]=CHSV(hue,255,255);FastLED.show();
              led5[11]=CHSV(hue,255,255);FastLED.show();
              case4rotation++;
              break;
            case 14:
              led6[0]=CHSV(hue,255,255);FastLED.show();
              led6[1]=CHSV(hue,255,255);FastLED.show();
              led6[2]=CHSV(hue,255,255);FastLED.show();
              led6[3]=CHSV(hue,255,255);FastLED.show();
              led6[4]=CHSV(hue,255,255);FastLED.show();
              led6[5]=CHSV(hue,255,255);FastLED.show();
              led6[6]=CHSV(hue,255,255);FastLED.show();
              led6[7]=CHSV(hue,255,255);FastLED.show();
              case4rotation++;
              break;
            case 15:
              led5[4]=CHSV(hue,255,255);FastLED.show();
              led5[5]=CHSV(hue,255,255);FastLED.show();
              led5[6]=CHSV(hue,255,255);FastLED.show();
              led5[7]=CHSV(hue,255,255);FastLED.show();
              case4rotation++;
              break;
            case 16:
              led4[4]=CHSV(hue,255,255);FastLED.show();
              led4[5]=CHSV(hue,255,255);FastLED.show();
              led4[6]=CHSV(hue,255,255);FastLED.show();
              led4[7]=CHSV(hue,255,255);FastLED.show();
              case4rotation++;
              break;
            case 17:
              led3[4]=CHSV(hue,255,255);FastLED.show();
              led3[5]=CHSV(hue,255,255);FastLED.show();
              led3[6]=CHSV(hue,255,255);FastLED.show();
              led3[7]=CHSV(hue,255,255);FastLED.show();
              led3[0]=CHSV(hue,255,0);FastLED.show();
              led3[1]=CHSV(hue,255,0);FastLED.show();
              led3[2]=CHSV(hue,255,0);FastLED.show();
              led3[3]=CHSV(hue,255,0);FastLED.show();
              led3[8]=CHSV(hue,255,0);FastLED.show();
              led3[9]=CHSV(hue,255,0);FastLED.show();
              led3[10]=CHSV(hue,255,0);FastLED.show();
              led3[11]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 18:
              led2[1]=CHSV(hue,255,255);FastLED.show();
              led2[2]=CHSV(hue,255,255);FastLED.show();
              led2[3]=CHSV(hue,255,255);FastLED.show();
              led2[4]=CHSV(hue,255,255);FastLED.show();
              led4[0]=CHSV(hue,255,0);FastLED.show();
              led4[1]=CHSV(hue,255,0);FastLED.show();
              led4[2]=CHSV(hue,255,0);FastLED.show();
              led4[3]=CHSV(hue,255,0);FastLED.show();
              led4[8]=CHSV(hue,255,0);FastLED.show();
              led4[9]=CHSV(hue,255,0);FastLED.show();
              led4[10]=CHSV(hue,255,0);FastLED.show();
              led4[11]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 19:
              led5[0]=CHSV(hue,255,0);FastLED.show();
              led5[1]=CHSV(hue,255,0);FastLED.show();
              led5[2]=CHSV(hue,255,0);FastLED.show();
              led5[3]=CHSV(hue,255,0);FastLED.show();
              led5[8]=CHSV(hue,255,0);FastLED.show();
              led5[9]=CHSV(hue,255,0);FastLED.show();
              led5[10]=CHSV(hue,255,0);FastLED.show();
              led5[11]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 20:
              led6[0]=CHSV(hue,255,0);FastLED.show();
              led6[1]=CHSV(hue,255,0);FastLED.show();
              led6[2]=CHSV(hue,255,0);FastLED.show();
              led6[3]=CHSV(hue,255,0);FastLED.show();
              led6[4]=CHSV(hue,255,0);FastLED.show();
              led6[5]=CHSV(hue,255,0);FastLED.show();
              led6[6]=CHSV(hue,255,0);FastLED.show();
              led6[7]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 21:
              led5[4]=CHSV(hue,255,0);FastLED.show();
              led5[5]=CHSV(hue,255,0);FastLED.show();
              led5[6]=CHSV(hue,255,0);FastLED.show();
              led5[7]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;            
            case 22:
              led4[4]=CHSV(hue,255,0);FastLED.show();
              led4[5]=CHSV(hue,255,0);FastLED.show();
              led4[6]=CHSV(hue,255,0);FastLED.show();
              led4[7]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 23:
              led3[4]=CHSV(hue,255,0);FastLED.show();
              led3[5]=CHSV(hue,255,0);FastLED.show();
              led3[6]=CHSV(hue,255,0);FastLED.show();
              led3[7]=CHSV(hue,255,0);FastLED.show();
              case4rotation++;
              break;
            case 24:
              led2[4]=CHSV(hue,255,255);FastLED.show();
              led2[5]=CHSV(hue,255,255);FastLED.show();
              led2[6]=CHSV(hue,255,255);FastLED.show();
              led2[7]=CHSV(hue,255,255);FastLED.show(); 
              case4rotation=10; 
              break;
            if(changecount>450){
                ledcount=0;
                changecount=0;
            }
          break;
        } 
      }
    }
  }  
}         
        
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<種類,ポート番号>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,led2no);
  FastLED.addLeds<WS2812,3>(led3,led3no);
  FastLED.addLeds<WS2812,4>(led4,led4no);
  FastLED.addLeds<WS2812,5>(led5,led5no);
  FastLED.addLeds<WS2812,6>(led6,led6no);
  xbeeSerial.begin(38400);
  doragon.attach(DangerousAngle);
  controller.attach(DangerousAngle);
  //初めにアドレス書いたやつ（通信の対象）.attach(通信が来た時に呼び出す関数（ここに書いとけばvoidloopに書かなくてもいい));
  
}
 
void loop(){
  LED();
  //Serial.println("voidloop");
  xbeeCore.check();
}
