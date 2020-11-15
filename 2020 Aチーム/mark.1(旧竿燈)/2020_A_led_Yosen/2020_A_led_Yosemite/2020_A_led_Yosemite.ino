#include <FastLED.h>
#include <stdlib.h>
/*CRGB 列の番号[LEDの総数]*/
CRGB led2[4];
CRGB led3[8];
CRGB led4[12];
CRGB led5[8];
unsigned long time;
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<種類,ポート番号,色の形式RGBとか>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,4);
  FastLED.addLeds<WS2812,3>(led3,8);
  FastLED.addLeds<WS2812,4>(led4,12);
  FastLED.addLeds<WS2812,5>(led5,8);}
 
void loop(){
 int ledno,pattern,hue,lightpower,saturation,value,times; 
 times=1;
 hue=85;
 for(;times<53000;){
   saturation=240;
   lightpower=random(215,255);
   for(ledno = 0; ledno <4 ; ledno++) {
     led2 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();
     times=millis();}
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
   delay(100);}
 Serial.println("change");

 for(lightpower=220;lightpower>0;lightpower=lightpower-5){
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
   FastLED.setBrightness(255);}

  for(;times<120000;){ 
   for(hue = 0; hue < 255; hue=hue+25) {
     for(ledno = 0; ledno <4 ; ledno++) {
       led2 [ledno]= CHSV(hue,255,255);
       FastLED.show();
       times=millis();}
     for(ledno = 0; ledno <8 ; ledno++) {
       led3 [ledno]= CHSV(hue+30,255,255);
       FastLED.show();}
     for(ledno = 0; ledno <12 ; ledno++) {
       led4 [ledno]= CHSV(hue+60,255,255);
       FastLED.show();}
     for(ledno = 0; ledno <8 ; ledno++) {  
       led5 [ledno]= CHSV(hue+90,255,255);
       FastLED.show();}
     FastLED.setBrightness(255);}}
 }
