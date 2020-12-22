uint8_t sum8(uint8_t*data, uint16_t len){
  uint8_t sum = 0; 
  for(uint16_t i=0;i<len;i++){
   	sum+= data[i];
   }
  return sum;
}