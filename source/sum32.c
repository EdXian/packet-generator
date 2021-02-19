/**
 * @brief the implementation of the check_function
 * 
 * @param data  the pointer of an byte array.
 * @param len  the length of an array.
 * @return uint32_t return summation of an array.
 */
uint32_t sum32(uint8_t*data, uint16_t len){
  uint32_t sum = 0x0000; 
uint16_t i;
  for(i=0;i<len;i++){
   	sum+= data[i];
   }
  return sum;
}