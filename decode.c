uint8_t msg_buf[200];
uint8_t tmp;
uint8_t data_len = 0;
uint32_t s32 = 0;

//a parser to parse all kinds of packets

enum parser{
	PARSE_STATE_START=0,
	PARSE_STATE_LEN=1,
	PARSE_STATE_DATA=2,
	PARSE_STATE_CHECK =3
};

typedef  uint8_t pack_id;
//0x0000010A
#define PACK_XX_LEN 10
#define PACK_CRC_LEN 4

uint32_t sum32(uint8_t*data, uint16_t len){
	uint32_t sum = 0x00000000;
	for(uint16_t i=0;i<len;i++){
		sum+= data[i];
	}
	return sum;
}

typedef struct parse_state{
	uint8_t now_idx;
	uint8_t rx_index;
	uint8_t state;
}parse_state_t;

uint8_t packet_parser(uint8_t* buf,uint8_t data,parse_state_t* ps){
	//need a struct to record FSM state
	uint32_t crc_val;
	buf[ps->rx_index] = data;
	
	switch (ps->state)
	{
		case PARSE_STATE_START:
			if (buf[ps->rx_index] == 0x55)
			{
				ps->state = PARSE_STATE_LEN;
			}
			break;
		case PARSE_STATE_LEN:
			if(buf[ps->rx_index]<255)   //packet should be smaller than 255 bytes
			{
				data_len = buf[ps->rx_index];
				ps->state = PARSE_STATE_DATA;
			}
			break;
		case PARSE_STATE_DATA:
			ps->now_idx++;
			if(ps->now_idx == data_len)
			{
				ps->state = PARSE_STATE_CHECK;
				uint8_t ind = PACK_XX_LEN - PACK_CRC_LEN;
				crc_val =(uint32_t)(buf[ind+0]<<0)  + 
						(uint32_t)(buf[ind+1]<<8)  + 
						(uint32_t)(buf[ind+2]<<16) + 
						(uint32_t)(buf[ind+3]<<24);
				 
				 //sum = sum32(buf,ind);
				 //sum2 = crc_val;
				 if(sum32(buf,ind) == crc_val){
					ps->rx_index = 0;
					ps->now_idx = 0;
					ps->state = PARSE_STATE_START;
					return buf[2];
				 }

			}
			break;
	}
	ps->rx_index++;
	return 0;
}

uint8_t packet_decode(uint8_t* buf,uint8_t msg_id){
	switch (msg_id)
	{
		case 1:
			
			memset(buf,0,200);
			break;
			
		case 2:
			
			memset(buf,0,200);
			break;
			
		case 3:
		
			memset(buf,0,200);
			break;

	}
}