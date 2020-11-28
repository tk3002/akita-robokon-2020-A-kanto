#include "aXbee.h"

namespace rob{

/*
bool xbee64bitAddress::operator==(const xbee64bitAddress &a){
  for(int i=0;i<addressLength;i++){
    if(address[i]!=a.address[i]){
      return false;
    }
  }
}*/

void aXbeeCom::callback(uint8_t *data,uint16_t dataSize){
  if(data[0]!=0x90){//Frame Type
    return;
  }
  for(int i=0;i<AXBEE_64BIT_ADDR_LENGTH;i++){//64bit address
    if(pairAddr.address[i]!=data[i+1]){
      return;
    }
  }
  pairAddr16[0]=data[9];pairAddr16[1]=data[10];//16bit address
  if(ifReceive!=NULL){
    ifReceive(data+12,dataSize-12);//Received Data
  }
}
aXbeeCom::aXbeeCom(aXbeeCoreInterface &parent,const xbee64bitAddress &pair):
  xbeeParent(parent),pairAddr(pair)
{
  xbeeParent.setCallback(this);
  pairAddr16[0]=0xff;pairAddr16[1]=0xfe;
}
void aXbeeCom::attach(void (*p)(uint8_t[],uint16_t)){
  ifReceive=p;
  return;
}
void aXbeeCom::send(uint8_t *data,uint16_t dataSize){
  const uint8_t constVal1[]={
    0x10,//Frame Type
    0x00,//Frame ID
  };
  const uint8_t constVal2[]={
    0x00,//Broadcast Radius
    0x00,//Oprions
  };
  const xbeeArrayNode frame[]={
    {constVal1,ARRAYLEN(constVal1)},
    {pairAddr.address,AXBEE_64BIT_ADDR_LENGTH},
    {pairAddr16,AXBEE_16BIT_ADDR_LENGTH},
    {constVal2,ARRAYLEN(constVal2)},
    {data,dataSize}
  };
  xbeeParent.sendFrame(frame,ARRAYLEN(frame));
}

}
