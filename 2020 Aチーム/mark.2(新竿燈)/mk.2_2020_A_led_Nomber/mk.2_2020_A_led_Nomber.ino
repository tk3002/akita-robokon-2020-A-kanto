#include <FastLED.h>
#include <stdlib.h>
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
 
void setup() { 
  Serial.begin(9600);
  /*FastLED.addLeds<種類,ポート番号>(列の番号,LEDの総数);*/
  FastLED.addLeds<WS2812,2>(led2,led2no);
  FastLED.addLeds<WS2812,3>(led3,led3no);
  FastLED.addLeds<WS2812,4>(led4,led4no);
  FastLED.addLeds<WS2812,5>(led5,led5no);
  FastLED.addLeds<WS2812,6>(led6,led6no); 
}
 
void loop(){
int ledno,hue;  
hue=36;
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
  
  FastLED.setBrightness(255);       
  hue=52;
  led2 [0]= CHSV(hue,255,255);FastLED.show();
  led2 [1]= CHSV(hue,255,255);FastLED.show();
  led3 [6]= CHSV(hue,255,255);FastLED.show();
  led3 [7]= CHSV(hue,255,255);FastLED.show();
  led4 [6]= CHSV(hue,255,255);FastLED.show();
  led4 [7]= CHSV(hue,255,255);FastLED.show();
  led5 [6]= CHSV(hue,255,255);FastLED.show();
  led5 [7]= CHSV(hue,255,255);FastLED.show();
  delay(1000);

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
  led2 [0]= CHSV(hue,255,255);FastLED.show();
  led2 [1]= CHSV(hue,255,255);FastLED.show();
  led2 [2]= CHSV(hue,255,255);FastLED.show();
  led2 [3]= CHSV(hue,255,255);FastLED.show();
  
  led3 [2]= CHSV(hue,255,255);FastLED.show();
  led3 [3]= CHSV(hue,255,255);FastLED.show();
  led3 [6]= CHSV(hue,255,255);FastLED.show();
  led3 [7]= CHSV(hue,255,255);FastLED.show();
  
  led4 [4]= CHSV(hue,255,255);FastLED.show();
  led4 [5]= CHSV(hue,255,255);FastLED.show();
  
  led5 [2]= CHSV(hue,255,255);FastLED.show();
  led5 [3]= CHSV(hue,255,255);FastLED.show();
  led5 [4]= CHSV(hue,255,255);FastLED.show();
  led5 [5]= CHSV(hue,255,255);FastLED.show();
  led5 [6]= CHSV(hue,255,255);FastLED.show();
  led5 [7]= CHSV(hue,255,255);FastLED.show();
  delay(1000);
  
}
