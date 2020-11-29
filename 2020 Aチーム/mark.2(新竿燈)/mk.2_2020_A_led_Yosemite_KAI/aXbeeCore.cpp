#include "aXbeeCore.h"



//////////////////////////////////////////////////////////////////////////////////aXbeeCore ここから

namespace rob{

//constructor 内部でbeginできない理由
//https://forum.arduino.cc/index.php?topic=23708.0
aXbeeCoreBase::aXbeeCoreBase(aXbeeArduinoSerialInterface *srlArg):
  rcounter(0)
{
  srl=srlArg;
}

int aXbeeCoreBase::getByte(){
  const unsigned long timeOut=micros()+AXBEE_TIMEOUT;
  while(true){
    if(srl->available()){
      return srl->read();
    }else if(micros()>timeOut){
      return -1;
    }
  }
}

//送信の本体(APIのフレームにして送信)
//フレームデータ(Frame-Specific Data)の入った配列とその長さを受けっとって送信する
//後でエスケープに対応させること(api=2)
void aXbeeCoreBase::sendFrame(const uint8_t frameData[],const uint16_t frameDataSize){
  unsigned int frameDataTotal=0;
  
  //Start Delimiter
  srl->write(0x7E);

  //Length MSB
  srl->write(0x00);

  //Length LSB
  srl->write(frameDataSize);

  //Frame-Specific Data (FrameData)
  for(byte i=0;i<frameDataSize;i++){
    frameDataTotal += frameData[i];
    srl->write(frameData[i]);
  }

  //CheckSum
  srl->write(0xFF - (frameDataTotal & 0xFF));
}

void aXbeeCoreBase::sendFrame(const xbeeArrayNode node[],const uint16_t nodeSize){
  unsigned int frameDataTotal=0;

  //Start Delimiter
  srl->write(0x7E);
  
  uint16_t frameDataSize=0;
  for(int i=0;i<nodeSize;i++){
    frameDataSize+=node[i].length;
  }
  //Length MSB
  srl->write((frameDataSize>>8)&0xFF);

  //Length LSB
  srl->write(frameDataSize&0xFF);

  //Frame-Specific Data (FrameData)
  for(int i=0;i<nodeSize;i++){
    for(int j=0;j<node[i].length;j++){
      frameDataTotal += node[i].p[j];
      srl->write(node[i].p[j]);
    }
  }

  //CheckSum
  srl->write(0xFF - (frameDataTotal & 0xFF));

  return;
}

void aXbeeCoreBase::check(){
  const unsigned long timeOut=micros()+AXBEE_TIMEOUT;
  while(true){
    if(srl->available()){
      ifReceive();
    }else if(micros()>timeOut){
      return;
    }
  }
}

void aXbeeCoreBase::ifReceive(){
  const uint8_t data=(uint8_t)srl->read();
  switch(rcounter){
  case 0:
    if(data==0x7E){
      rcounter++;
    }
    break;
  case 1:
    rframeSize=(uint16_t)(data<<8);
    rcounter++;
    break;
  case 2:
    rframeSize|=(uint16_t)data;
    if(rframeSize>AXBEE_RBUFF_SIZE){
      rcounter=0;
    }else{
      rcounter++;
      rframeCounter=0;
      rbuffTotal=0;
    }
    break;
  case 3:
    rbuff[rframeCounter]=data;
    rbuffTotal+=data;
    rframeCounter++;
    if(!(rframeCounter<rframeSize)){
      rcounter++;
    }
    break;
  case 4:
    if((0xFF-(rbuffTotal&0xFF)) == data){
      ifReceiveFrame(rbuff,rframeSize);
    }
    rcounter=0;
    break;
  }
}

}//namespace rob



//////////////////////////////////////////////////////////////////////////////////aXbeeCore ここまで
