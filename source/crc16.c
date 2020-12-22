uint16_t CRC16_function(uint8_t *buf, uint32_t len){
	uint16_t tmp =  0xFFFF;
	uint16_t i,j;
	for (i=0;i<len;i++)
	{
		tmp = tmp ^ buf[i];
		for (j=0;j<32;j++)
		{
			if(tmp& 0x8000)
			{
				tmp = (tmp << 1) ^ CRC16_POLY;
				}else{
				tmp = (tmp << 1);
			}
		}
	}
	return tmp;
}
