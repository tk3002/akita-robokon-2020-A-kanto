#include <FastLED.h>
#include <stdlib.h>
/*CRGB 列の番号[LEDの総数]*/
CRGB led2[4];
CRGB led3[12];
CRGB led4[12];
CRGB led5[12];
CRGB led6[8];
unsigned long time;
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<チップの種類,ポート番号>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,4);
  FastLED.addLeds<WS2812,3>(led3,12);
  FastLED.addLeds<WS2812,4>(led4,12);
  FastLED.addLeds<WS2812,5>(led5,12);
  FastLED.addLeds<WS2812,6>(led6,8);
  }
 
void loop(){
 int ledno,pattern,hue,lightpower,saturation,value,times; 
 times=1;

 for(;;){
   for(hue = 0; hue < 255; hue=hue+20) {
     for(ledno = 0; ledno <4 ; ledno++) {
       led2 [ledno]= CHSV(hue,255,255);
       FastLED.show();
       times=millis();}
     for(ledno = 0; ledno <12 ; ledno++) {
       led3 [ledno]= CHSV(hue+30,255,255);
       FastLED.show();}
     for(ledno = 0; ledno <12 ; ledno++) {
       led4 [ledno]= CHSV(hue+60,255,255);
       FastLED.show();}
     for(ledno = 0; ledno <12 ; ledno++) {  
       led5 [ledno]= CHSV(hue+90,255,255);
       FastLED.show();}
      for(ledno = 0;ledno <8 ; ledno++) {  
       led6 [ledno]= CHSV(hue+120,255,255);
       FastLED.show();}
     FastLED.setBrightness(25);}}
        
       }       
