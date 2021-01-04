uint32_t sum32(uint8_t*data, uint16_t len){
  uint32_t sum = 0x0000; 
uint16_t i;
  for(i=0;i<len;i++){
   	sum+= data[i];
   }
  return sum;
}