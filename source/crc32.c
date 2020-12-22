uint32_t CRC32_function(uint8_t *buf, uint32_t len){
	uint32_t tmp =  0xFFFFFFFF;
	uint16_t i,j;
	for (i=0;i<len;i++)
	{
		tmp = tmp ^ buf[i];
		for (j=0;j<32;j++)
		{
			if(tmp& 0x80000000)
			{
				tmp = (tmp << 1) ^ CRC32_POLY;
				}else{
				tmp = (tmp << 1);
			}
		}
	}
	return tmp;
}