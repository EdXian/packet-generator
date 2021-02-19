/**
 * @brief the implementation of the check_function
 * 
 * @param data  the pointer of an byte array.
 * @param len  the length of an array.
 * @return uint32_t return summation of an array.
 */

uint8_t sum8(uint8_t*data, uint16_t len){
  uint8_t sum = 0; 
  for(uint16_t i=0;i<len;i++){
   	sum+= data[i];
   }
  return sum;
}