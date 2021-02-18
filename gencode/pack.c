/**
 * @file pack.c
 * @author edxian 
 * @brief 
 * @version 1.1
 * @date 2021-02-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "pack.h"




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

/**
 * @brief  to check the validation of packet
 * 
 * @param pack the receieved packet
 * @param len the legnth of the receieved packet
 * @return uint32_t the checksum value of the receieved packet 
 */

uint32_t check_function(uint8_t* pack,uint16_t len){
	 return sum32(pack, len);
}


/**
 * @brief to init the state of the parser
 * 
 * @param ps the state of the parser
 */

void parser_init(parse_state_t *ps){
        	ps->data_len = 0;
        	ps->start_idx = 0;
        	ps->rx_index = 0;
        	ps->now_idx = 0;
        	ps->data_len = 0;
        	ps->state = PARSE_STATE_START;
}

/**
 * @brief The function to config a packet
 * 
 * @param pack  a pointer of a header_t-type packet
 * @param header the start of header
 * @param len  the length of a packet
 * @param packet_type the id of a specific packet
 */

void header_config(header_t* pack,
	      uint8_t header,
	      uint8_t len,
	      uint8_t packet_type){
	
	 pack->header = header;
	 pack->len = len;
	 pack->packet_type = packet_type;

}
void err_config(err_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void err_ack_config(err_ack_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void bl_get_ver_config(bl_get_ver_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void bl_get_ver_ack_config(bl_get_ver_ack_t* pack,
	      header_t header,
	      uint8_t major,
	      uint8_t minor,
	      uint8_t patch,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->major = major;
	 pack->minor = minor;
	 pack->patch = patch;
	 pack->checksum = checksum;

}
void bl_set_ver_config(bl_set_ver_t* pack,
	      header_t header,
	      uint32_t app_addr,
	      uint8_t major,
	      uint8_t minor,
	      uint8_t patch,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->app_addr = app_addr;
	 pack->major = major;
	 pack->minor = minor;
	 pack->patch = patch;
	 pack->checksum = checksum;

}
void bl_set_ver_ack_config(bl_set_ver_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_get_id_config(bl_get_id_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void bl_get_id_ack_config(bl_get_id_ack_t* pack,
	      header_t header,
	      uint32_t chip_id,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->chip_id = chip_id;
	 pack->checksum = checksum;

}
void bl_jump_app_config(bl_jump_app_t* pack,
	      header_t header,
	      uint32_t addr,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->addr = addr;
	 pack->checksum = checksum;

}
void bl_jump_app_ack_config(bl_jump_app_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_mem_erase_config(bl_mem_erase_t* pack,
	      header_t header,
	      uint32_t start_addr,
	      uint32_t end_addr,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->start_addr = start_addr;
	 pack->end_addr = end_addr;
	 pack->checksum = checksum;

}
void bl_mem_erase_ack_config(bl_mem_erase_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_mem_write_config(bl_mem_write_t* pack,
	      header_t header,
	      uint32_t start_addr,
	      uint8_t follows,
	      uint8_t write,
	      uint8_t length,
	      uint8_t data[128],
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->start_addr = start_addr;
	 pack->follows = follows;
	 pack->write = write;
	 pack->length = length;
	 pack->data[128] = data[128];
	 pack->checksum = checksum;

}
void bl_mem_write_ack_config(bl_mem_write_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_mem_read_config(bl_mem_read_t* pack,
	      header_t header,
	      uint32_t start_addr,
	      uint32_t end_addr,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->start_addr = start_addr;
	 pack->end_addr = end_addr;
	 pack->checksum = checksum;

}
void bl_mem_read_ack_config(bl_mem_read_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint8_t read_length,
	      uint8_t data[128],
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->read_length = read_length;
	 pack->data[128] = data[128];
	 pack->checksum = checksum;

}
void bl_reset_config(bl_reset_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void bl_reset_ack_config(bl_reset_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_verify_config(bl_verify_t* pack,
	      header_t header,
	      uint32_t start_addr,
	      uint32_t end_addr,
	      uint32_t verify_code,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->start_addr = start_addr;
	 pack->end_addr = end_addr;
	 pack->verify_code = verify_code;
	 pack->checksum = checksum;

}
void bl_verify_ack_config(bl_verify_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}
void bl_get_acc_cmd_config(bl_get_acc_cmd_t* pack,
	      header_t header,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->checksum = checksum;

}
void bl_get_acc_cmd_ack_config(bl_get_acc_cmd_ack_t* pack,
	      header_t header,
	      uint32_t scale,
	      float acc_x,
	      float acc_y,
	      float acc_z,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->scale = scale;
	 pack->acc_x = acc_x;
	 pack->acc_y = acc_y;
	 pack->acc_z = acc_z;
	 pack->checksum = checksum;

}
void bl_set_acc_offset_cmd_config(bl_set_acc_offset_cmd_t* pack,
	      header_t header,
	      float norm,
	      float acc_x_offset,
	      float acc_y_offset,
	      float acc_z_offset,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->norm = norm;
	 pack->acc_x_offset = acc_x_offset;
	 pack->acc_y_offset = acc_y_offset;
	 pack->acc_z_offset = acc_z_offset;
	 pack->checksum = checksum;

}
void bl_set_acc_offset_cmd_ack_config(bl_set_acc_offset_cmd_ack_t* pack,
	      header_t header,
	      uint8_t valid,
	      uint32_t checksum){
	
	 pack->header = header;
	 pack->valid = valid;
	 pack->checksum = checksum;

}

/**
 * @brief encoded error packet
 * 
 * @param data NULL
 * @param pack the pointer of err_t packet
 * @param len the length of err_t packet
 * @return uint16_t 
 */

uint16_t err_encode(uint8_t* data, err_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_ERR_ID;
	pack->header.len = sizeof(err_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(err_t) -4));
	return sizeof(err_t);
}
            

uint16_t err_ack_encode(uint8_t* data, err_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_ERR_ACK_ID;
	pack->header.len = sizeof(err_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(err_ack_t) -4));
	return sizeof(err_ack_t);
}
            

uint16_t bl_get_ver_encode(uint8_t* data, bl_get_ver_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_VER_ID;
	pack->header.len = sizeof(bl_get_ver_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_ver_t) -4));
	return sizeof(bl_get_ver_t);
}
            

uint16_t bl_get_ver_ack_encode(uint8_t* data, bl_get_ver_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_VER_ACK_ID;
	pack->header.len = sizeof(bl_get_ver_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_ver_ack_t) -4));
	return sizeof(bl_get_ver_ack_t);
}
            

uint16_t bl_set_ver_encode(uint8_t* data, bl_set_ver_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_SET_VER_ID;
	pack->header.len = sizeof(bl_set_ver_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_set_ver_t) -4));
	return sizeof(bl_set_ver_t);
}
            

uint16_t bl_set_ver_ack_encode(uint8_t* data, bl_set_ver_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_SET_VER_ACK_ID;
	pack->header.len = sizeof(bl_set_ver_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_set_ver_ack_t) -4));
	return sizeof(bl_set_ver_ack_t);
}
            

uint16_t bl_get_id_encode(uint8_t* data, bl_get_id_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_ID_ID;
	pack->header.len = sizeof(bl_get_id_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_id_t) -4));
	return sizeof(bl_get_id_t);
}
            

uint16_t bl_get_id_ack_encode(uint8_t* data, bl_get_id_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_ID_ACK_ID;
	pack->header.len = sizeof(bl_get_id_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_id_ack_t) -4));
	return sizeof(bl_get_id_ack_t);
}
            

uint16_t bl_jump_app_encode(uint8_t* data, bl_jump_app_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_JUMP_APP_ID;
	pack->header.len = sizeof(bl_jump_app_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_jump_app_t) -4));
	return sizeof(bl_jump_app_t);
}
            

uint16_t bl_jump_app_ack_encode(uint8_t* data, bl_jump_app_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_JUMP_APP_ACK_ID;
	pack->header.len = sizeof(bl_jump_app_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_jump_app_ack_t) -4));
	return sizeof(bl_jump_app_ack_t);
}
            

uint16_t bl_mem_erase_encode(uint8_t* data, bl_mem_erase_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_ERASE_ID;
	pack->header.len = sizeof(bl_mem_erase_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_erase_t) -4));
	return sizeof(bl_mem_erase_t);
}
            

uint16_t bl_mem_erase_ack_encode(uint8_t* data, bl_mem_erase_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_ERASE_ACK_ID;
	pack->header.len = sizeof(bl_mem_erase_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_erase_ack_t) -4));
	return sizeof(bl_mem_erase_ack_t);
}
            

uint16_t bl_mem_write_encode(uint8_t* data, bl_mem_write_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_WRITE_ID;
	pack->header.len = sizeof(bl_mem_write_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_write_t) -4));
	return sizeof(bl_mem_write_t);
}
            

uint16_t bl_mem_write_ack_encode(uint8_t* data, bl_mem_write_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_WRITE_ACK_ID;
	pack->header.len = sizeof(bl_mem_write_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_write_ack_t) -4));
	return sizeof(bl_mem_write_ack_t);
}
            

uint16_t bl_mem_read_encode(uint8_t* data, bl_mem_read_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_READ_ID;
	pack->header.len = sizeof(bl_mem_read_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_read_t) -4));
	return sizeof(bl_mem_read_t);
}
            

uint16_t bl_mem_read_ack_encode(uint8_t* data, bl_mem_read_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_MEM_READ_ACK_ID;
	pack->header.len = sizeof(bl_mem_read_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_read_ack_t) -4));
	return sizeof(bl_mem_read_ack_t);
}
            

uint16_t bl_reset_encode(uint8_t* data, bl_reset_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_RESET_ID;
	pack->header.len = sizeof(bl_reset_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_reset_t) -4));
	return sizeof(bl_reset_t);
}
            

uint16_t bl_reset_ack_encode(uint8_t* data, bl_reset_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_RESET_ACK_ID;
	pack->header.len = sizeof(bl_reset_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_reset_ack_t) -4));
	return sizeof(bl_reset_ack_t);
}
            

uint16_t bl_verify_encode(uint8_t* data, bl_verify_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_VERIFY_ID;
	pack->header.len = sizeof(bl_verify_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_verify_t) -4));
	return sizeof(bl_verify_t);
}
            

uint16_t bl_verify_ack_encode(uint8_t* data, bl_verify_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_VERIFY_ACK_ID;
	pack->header.len = sizeof(bl_verify_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_verify_ack_t) -4));
	return sizeof(bl_verify_ack_t);
}
            

uint16_t bl_get_acc_cmd_encode(uint8_t* data, bl_get_acc_cmd_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_ACC_CMD_ID;
	pack->header.len = sizeof(bl_get_acc_cmd_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_acc_cmd_t) -4));
	return sizeof(bl_get_acc_cmd_t);
}
            

uint16_t bl_get_acc_cmd_ack_encode(uint8_t* data, bl_get_acc_cmd_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_GET_ACC_CMD_ACK_ID;
	pack->header.len = sizeof(bl_get_acc_cmd_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_acc_cmd_ack_t) -4));
	return sizeof(bl_get_acc_cmd_ack_t);
}
            

uint16_t bl_set_acc_offset_cmd_encode(uint8_t* data, bl_set_acc_offset_cmd_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_SET_ACC_OFFSET_CMD_ID;
	pack->header.len = sizeof(bl_set_acc_offset_cmd_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_set_acc_offset_cmd_t) -4));
	return sizeof(bl_set_acc_offset_cmd_t);
}
            

uint16_t bl_set_acc_offset_cmd_ack_encode(uint8_t* data, bl_set_acc_offset_cmd_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
    pack->header.packet_type = PACK_BL_SET_ACC_OFFSET_CMD_ACK_ID;
	pack->header.len = sizeof(bl_set_acc_offset_cmd_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_set_acc_offset_cmd_ack_t) -4));
	return sizeof(bl_set_acc_offset_cmd_ack_t);
}

