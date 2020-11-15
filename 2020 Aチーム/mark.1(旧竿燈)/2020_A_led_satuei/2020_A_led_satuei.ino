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
 int ledno,pattern,hue,lightpower,saturation,value; 
 long times=1;
 hue=85;

 delay(10000);
 
 for(;times<20000;){
   saturation=240;
   lightpower=random(215,255);
   for(ledno = 0; ledno <4 ; ledno++) {
     led2 [ledno]= CHSV(hue,saturation,lightpower);
     FastLED.show();
     times=millis();
     Serial.println(times);}
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

 for(;;){
    for(hue = 25.5; hue < 224.5; hue=hue+25.5){
        ledno=random(2);
        led2 [ledno*2]= CHSV(hue,255,255);
        led2 [ledno*2+1]=CHSV(hue,255,255);
        FastLED.show();
        times=millis();
        ledno=random(4);
        led3 [ledno*2]= CHSV(hue,255,255);
        led3 [ledno*2+1]= CHSV(hue,255,255);
        FastLED.show();
        ledno=random(6);
        led4 [ledno*2]= CHSV(hue,255,255);
        led4 [ledno*2+1]=CHSV(hue,255,255);
        FastLED.show();
        ledno=random(4);
        led5 [ledno*2]= CHSV(hue,255,255);
        led5 [ledno*2+1]=CHSV(hue,255,255);
        FastLED.show();
        delay(50);}}
  
 }
