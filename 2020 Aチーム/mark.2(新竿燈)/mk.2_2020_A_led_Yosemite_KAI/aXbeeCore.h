#ifndef AXBEE_CORE_H_INCLUDE_GUARD
#define AXBEE_CORE_H_INCLUDE_GUARD

#include "Arduino.h"
#include <SoftwareSerial.h>

namespace rob{

#ifndef ARRAYLEN
#define ARRAYLEN(X) (sizeof(X)/sizeof(X[0]))
#endif

#define AXBEE_IF_RECEIVE_CALLBACK_MAXSIZE 16

#define AXBEE_16BIT_ADDR_LENGTH 2
#define AXBEE_64BIT_ADDR_LENGTH 8


class aXbeeArduinoSerialInterface{
  public:
  virtual void begin(unsigned long baud)=0;
  virtual int read(void)=0;
  virtual size_t write(uint8_t c)=0;
  virtual int available(void)=0;
};

template<class SRL>
class aXbeeArduinoSerial:
  public aXbeeArduinoSerialInterface
{
  protected:
  SRL &srl;
  public:
  aXbeeArduinoSerial(SRL &srlArg):srl(srlArg){}
  int read(void){return srl.read();}
  size_t write(uint8_t c){return srl.write(c);}
  int available(void){return srl.available();}
};
class aXbeeArduinoHardwareSerial:
  public aXbeeArduinoSerial<HardwareSerial>
{
  public:
  aXbeeArduinoHardwareSerial(HardwareSerial &srlArg):rob::aXbeeArduinoSerial<HardwareSerial>(srlArg){}
  //void begin(unsigned long baud){rob::aXbeeArduinoSerial<HardwareSerial>::srl.begin(baud);}
  void begin(unsigned long baud){srl.begin(baud);}
};


struct xbeeArrayNode{
  const uint8_t *p;
  const uint16_t length;
};


class aXbeeCallbackInterface{
  public:
  virtual void callback(uint8_t[],uint16_t)=0;
};

class aXbeeCoreInterface{
  public:
  virtual void sendFrame(const uint8_t frameData[],const uint16_t frameDataSize)=0;
  virtual void sendFrame(const xbeeArrayNode* frameData,const uint16_t nodeSize)=0;
  virtual void setCallback(aXbeeCallbackInterface*)=0;
};
class aXbeeCoreBase:
  public aXbeeCoreInterface
{
protected:
  static const int AXBEE_RBUFF_SIZE=255;
  static const int AXBEE_TIMEOUT=3000;//us
  aXbeeArduinoSerialInterface *srl;
  void ifReceive();
  
  byte rcounter;
  uint8_t rbuff[AXBEE_RBUFF_SIZE];
  unsigned int rbuffTotal;
  
  byte rframeSize;
  int rframeCounter;
  //void (*ifReceiveFrame)(uint8_t*,uint16_t);
  //Callback<void(uint8_t*,uint16_t)> ifReceiveFrame;
  virtual void ifReceiveFrame(uint8_t[],uint16_t)=0;
  int getByte();
public:
  aXbeeCoreBase(aXbeeArduinoSerialInterface*);
  void check();
  void sendFrame(const uint8_t frameData[],const uint16_t frameDataSize);
  void sendFrame(const xbeeArrayNode node[],const uint16_t nodeSize);
};


template<int N>
class aXbeeCoreCallback:
  public aXbeeCoreBase
{
  private:
  int callbackArrayCont;
  aXbeeCallbackInterface *callbackArray[N];
  public:
  aXbeeCoreCallback(aXbeeArduinoSerialInterface*);
  int addCallback(aXbeeCallbackInterface*);
  void setCallback(aXbeeCallbackInterface *p){addCallback(p);}
  protected:
  void ifReceiveFrame(uint8_t[],uint16_t);
};


template<int N>
inline aXbeeCoreCallback<N>::aXbeeCoreCallback(aXbeeArduinoSerialInterface *srl):
  aXbeeCoreBase(srl),callbackArrayCont(0)
{
  for(int i=0;i<N;i++){
    callbackArray[i]=NULL;
  }
  
}
template<int N>
inline int aXbeeCoreCallback<N>::addCallback(aXbeeCallbackInterface *p){
  if(!(callbackArrayCont<N))return -1;
  callbackArray[callbackArrayCont]=p;
  return callbackArrayCont++;
}
template<int N>
inline void aXbeeCoreCallback<N>::ifReceiveFrame(uint8_t array[],uint16_t arrayLen){
  for(int i=0;i<callbackArrayCont;i++){
    callbackArray[i]->callback(array,arrayLen);
  }
}


template<>
class aXbeeCoreCallback<1>:
  public aXbeeCoreBase
{
  private:
  aXbeeCallbackInterface *callbackClass;
  public:
  aXbeeCoreCallback(aXbeeArduinoSerialInterface*);
  int addCallback(aXbeeCallbackInterface*);
  void setCallback(aXbeeCallbackInterface *p){addCallback(p);}
  protected:
  void ifReceiveFrame(uint8_t[],uint16_t);
};
inline aXbeeCoreCallback<1>::aXbeeCoreCallback(aXbeeArduinoSerialInterface *srl):
  aXbeeCoreBase(srl)
{}
inline int aXbeeCoreCallback<1>::addCallback(aXbeeCallbackInterface *p){
  if(callbackClass!=NULL)return -1;
  callbackClass=p;
  return 1;
}
inline void aXbeeCoreCallback<1>::ifReceiveFrame(uint8_t array[],uint16_t arrayLen){
  if(callbackClass==NULL)return;
  callbackClass->callback(array,arrayLen);
}


}//namespace rob

#endif
