#include <FastLED.h>
#include <stdlib.h>
/*CRGB 列の番号[LEDの総数]*/
CRGB led2[4];
CRGB led3[8];
CRGB led4[12];
CRGB led5[8];
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<チップの種類,ポート番号,色の形式RGBとか>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,4);
  FastLED.addLeds<WS2812,3>(led3,8);
  FastLED.addLeds<WS2812,4>(led4,12);
  FastLED.addLeds<WS2812,5>(led5,8);
  Serial.println("start");}
 
void loop(){ 
 int ledno,pattern,hue,lightpower,saturation;
   hue=85;
   saturation=240;
   lightpower=random(215,255);
   for(ledno = 0; ledno <4 ; ledno++) {
     led2 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();}
   for(ledno = 0; ledno <8 ; ledno++) {
     led3 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();}
   for(ledno = 0; ledno <12 ; ledno++) {
     led4 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();}
   for(ledno = 0; ledno <8 ; ledno++) {  
     led5 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();}
   
   FastLED.setBrightness(255);
   delay(100);
   }
