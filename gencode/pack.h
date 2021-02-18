/**
 * @file pack.h
 * @author edxian
 * @brief 
 * @version 1.1
 * @date 2021-02-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "stdint.h"  
#include "stdio.h"  
#ifndef __BOOT_H_ 
#define __BOOT_H_ 


#define	PACK_LEN	200    ///@brief length of buffer
#define	BOOT_MODE	0
#define	CRC_CHECK_LENGTH	128
#define	BL_FLASH_IO	FLASH_0
#define	BL_USART_IO	USART_0
#define	IS_BOOT_MODE	(pin_mode == BOOT_MODE)
#define	BL_ACK	0XA5
#define	BL_NACK	0X7F
/* CHIP_ID macros */ 
#define	CHIPID_W0	((uint32_t*)( 0x008061FC))
#define	CHIPID_W1	((uint32_t*)( 0x00806010))
#define	CHIPID_W2	((uint32_t*)( 0x00806014))
#define	CHIPID_W3	((uint32_t*)( 0x00806018))
/* MEMORY_MAP macros */ 
#define	BL_START_ADDRESS	0x00000000
#define	BL_END_ADDRESS	0x00002000
#define	APP_START_ADDRESS	0x6000
#define	APP_END_ADDRESS	0x37FFF
#define	APP_SIZE	(APP_END_ADDRESS-APP_START_ADDRESS)
#define	BACKUP_APP_START_ADDRESS	0x42000
#define	BACKUP_APP_END_ADDRESS	0x73FFF
#define	BACKUP_APP_SIZE	(BACKUP_APP_END_ADDRESS-BACKUP_APP_START_ADDRESS)

/* MEMORY_MAP enumeration */ 



        
enum parser{
	PARSE_STATE_START=0,
	PARSE_STATE_LEN=1,
	PARSE_STATE_DATA=2,
	PARSE_STATE_CHECK =3
};
        
typedef struct parse_state{
	uint8_t now_idx;
	uint8_t rx_index;
	uint8_t state;
	uint8_t data_len;
	uint8_t start_idx;
}parse_state_t;
            


#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct header_struct{

	uint8_t header;
	uint8_t len;
	uint8_t packet_type;

}header_t;


#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct label_struct{

	uint32_t app_addr;
	uint8_t major;
	uint8_t minor;
	uint8_t patch;

}label_t;

#define PACK_ERR_ID 1
#define PACK_ERR_LEN sizeof(err_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct err_struct{

	header_t header;
	uint32_t checksum;

}err_t;

#define PACK_ERR_ACK_ID 2
#define PACK_ERR_ACK_LEN sizeof(err_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct err_ack_struct{

	header_t header;
	uint32_t checksum;

}err_ack_t;

#define PACK_BL_GET_VER_ID 3
#define PACK_BL_GET_VER_LEN sizeof(bl_get_ver_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_ver_struct{

	header_t header;
	uint32_t checksum;

}bl_get_ver_t;

#define PACK_BL_GET_VER_ACK_ID 4
#define PACK_BL_GET_VER_ACK_LEN sizeof(bl_get_ver_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_ver_ack_struct{

	header_t header;
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	uint32_t checksum;

}bl_get_ver_ack_t;

#define PACK_BL_SET_VER_ID 5
#define PACK_BL_SET_VER_LEN sizeof(bl_set_ver_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_set_ver_struct{

	header_t header;
	uint32_t app_addr;
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	uint32_t checksum;

}bl_set_ver_t;

#define PACK_BL_SET_VER_ACK_ID 6
#define PACK_BL_SET_VER_ACK_LEN sizeof(bl_set_ver_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_set_ver_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_set_ver_ack_t;

#define PACK_BL_GET_ID_ID 7
#define PACK_BL_GET_ID_LEN sizeof(bl_get_id_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_id_struct{

	header_t header;
	uint32_t checksum;

}bl_get_id_t;

#define PACK_BL_GET_ID_ACK_ID 8
#define PACK_BL_GET_ID_ACK_LEN sizeof(bl_get_id_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_id_ack_struct{

	header_t header;
	uint32_t chip_id;
	uint32_t checksum;

}bl_get_id_ack_t;

#define PACK_BL_JUMP_APP_ID 9
#define PACK_BL_JUMP_APP_LEN sizeof(bl_jump_app_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_jump_app_struct{

	header_t header;
	uint32_t addr;
	uint32_t checksum;

}bl_jump_app_t;

#define PACK_BL_JUMP_APP_ACK_ID 10
#define PACK_BL_JUMP_APP_ACK_LEN sizeof(bl_jump_app_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_jump_app_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_jump_app_ack_t;

#define PACK_BL_MEM_ERASE_ID 11
#define PACK_BL_MEM_ERASE_LEN sizeof(bl_mem_erase_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_erase_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t checksum;

}bl_mem_erase_t;

#define PACK_BL_MEM_ERASE_ACK_ID 12
#define PACK_BL_MEM_ERASE_ACK_LEN sizeof(bl_mem_erase_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_erase_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_mem_erase_ack_t;

#define PACK_BL_MEM_WRITE_ID 13
#define PACK_BL_MEM_WRITE_LEN sizeof(bl_mem_write_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_write_struct{

	header_t header;
	uint32_t start_addr;
	uint8_t follows;
	uint8_t write;
	uint8_t length;
	uint8_t data[128];
	uint32_t checksum;

}bl_mem_write_t;

#define PACK_BL_MEM_WRITE_ACK_ID 14
#define PACK_BL_MEM_WRITE_ACK_LEN sizeof(bl_mem_write_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_write_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_mem_write_ack_t;

#define PACK_BL_MEM_READ_ID 15
#define PACK_BL_MEM_READ_LEN sizeof(bl_mem_read_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_read_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t checksum;

}bl_mem_read_t;

#define PACK_BL_MEM_READ_ACK_ID 16
#define PACK_BL_MEM_READ_ACK_LEN sizeof(bl_mem_read_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_read_ack_struct{

	header_t header;
	uint8_t valid;
	uint8_t read_length;
	uint8_t data[128];
	uint32_t checksum;

}bl_mem_read_ack_t;

#define PACK_BL_RESET_ID 17
#define PACK_BL_RESET_LEN sizeof(bl_reset_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_reset_struct{

	header_t header;
	uint32_t checksum;

}bl_reset_t;

#define PACK_BL_RESET_ACK_ID 18
#define PACK_BL_RESET_ACK_LEN sizeof(bl_reset_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_reset_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_reset_ack_t;

#define PACK_BL_VERIFY_ID 19
#define PACK_BL_VERIFY_LEN sizeof(bl_verify_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_verify_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t verify_code;
	uint32_t checksum;

}bl_verify_t;

#define PACK_BL_VERIFY_ACK_ID 20
#define PACK_BL_VERIFY_ACK_LEN sizeof(bl_verify_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_verify_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_verify_ack_t;

#define PACK_BL_GET_ACC_CMD_ID 21
#define PACK_BL_GET_ACC_CMD_LEN sizeof(bl_get_acc_cmd_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_acc_cmd_struct{

	header_t header;
	uint32_t checksum;

}bl_get_acc_cmd_t;

#define PACK_BL_GET_ACC_CMD_ACK_ID 22
#define PACK_BL_GET_ACC_CMD_ACK_LEN sizeof(bl_get_acc_cmd_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_acc_cmd_ack_struct{

	header_t header;
	uint32_t scale;
	float acc_x;
	float acc_y;
	float acc_z;
	uint32_t checksum;

}bl_get_acc_cmd_ack_t;

#define PACK_BL_SET_ACC_OFFSET_CMD_ID 23
#define PACK_BL_SET_ACC_OFFSET_CMD_LEN sizeof(bl_set_acc_offset_cmd_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_set_acc_offset_cmd_struct{

	header_t header;
	float norm;
	float acc_x_offset;
	float acc_y_offset;
	float acc_z_offset;
	uint32_t checksum;

}bl_set_acc_offset_cmd_t;

#define PACK_BL_SET_ACC_OFFSET_CMD_ACK_ID 24
#define PACK_BL_SET_ACC_OFFSET_CMD_ACK_LEN sizeof(bl_set_acc_offset_cmd_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_set_acc_offset_cmd_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_set_acc_offset_cmd_ack_t;


typedef union joint_union{

 struct {
	uint8_t header_leg : 1;
	uint8_t pillow : 1;
	uint8_t neck : 1;
	uint8_t back : 1;
	uint8_t lumbar : 1;
	uint8_t buttocks : 1;
	uint8_t reserved : 1;
	};
	uint8_t joint_value;

}joint_u;


#endif
