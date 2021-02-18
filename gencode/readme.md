# bootloader

## 編譯器
	* GCC

## Target
	* PC
	* ARM Cortex-M4系列 MCU
	* 8/16位 MCU

## 可實現功能
	1. 讀/寫記憶體資料
	2. 讀/寫韌體版本
	3. 針對app進行更新

## Byte-oriented protocol
可適用於位元傳輸的協定、例如UART、TCP/UDP、SPI、BLE...

## 移植
	1. 將'pack.c'和 'pack.h'移入想要的專案
	2. 加入include 'pack.h'
	3. 複製原始'main.c'到 新專案中
	4. 填入對應的 io descripter 
~~~~~~~~~~~~~{.c}
 BL_FLASH_IO   FLASH_0    
 BL_USART_IO   USART_0 
~~~~~~~~~~~~~
	5. 編譯測試


## 新增bootloader功能
### 定義新的封包型態
可以使用[packet-generator](https://github.com/EdXian/packet-generator)   新增新的封包格式，或是手動新增(不建議)。

~~~~~~~~~~~~~{.c}
#define PACK_BL_MEM_WRITE_ID 13    //需要記住 PACK_BL_MEM_WRITE_ID 之後會用到
#define PACK_BL_MEM_WRITE_LEN sizeof(bl_mem_write_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian    //使用little-endian 格式儲存資料
typedef struct bl_mem_write_struct{

	header_t header;
	uint32_t start_addr;
	uint8_t follows;
	uint8_t write;
	uint8_t length;
	uint8_t data[128];
	uint32_t checksum;

}bl_mem_write_t;

~~~~~~~~~~~~~
實現對應的encode函數
~~~~~~~~~~~~~{.c}
uint16_t bl_mem_write_encode(uint8_t* data, bl_mem_write_t* pack, uint16_t len){
	....
}
~~~~~~~~~~~~~

### 定義新的handler函數
~~~~~~~~~~~~~{.c}
void bootloader_handle_mem_write_cmd(bl_mem_write_t cmd)
{
	....
}
~~~~~~~~~~~~~

### 實現函數的功能
在message_decode 中實現
~~~~~~~~~~~~~{.c}
uint8_t message_decode(uint8_t* buf,uint8_t msg_id){
	switch (msg_id)
	{
		...
			
		case PACK_BL_MEM_WRITE_ID:   //需要依照對應的ID填寫，須注意。
			memcpy(&mem_write_cmd,buf,sizeof(mem_write_cmd));  //將接收到的buffer存入mem_write_cmd中
			bootloader_handle_mem_write_cmd(mem_write_cmd);    //執行函數
			break;
			
		...
	
	}
}
~~~~~~~~~~~~~


### 主程式實作

~~~~~~~~~~~~~{.c}
int main(void)
{
	uint8_t recv_char;

	atmel_start_init();
	usart_sync_enable(&BL_USART_IO);
	pin_mode = gpio_get_pin_level(BOOT_PIN); //ensure pin mode
	pin_mode = gpio_get_pin_level(BOOT_PIN);
	delay_ms(1);
	pin_mode = gpio_get_pin_level(BOOT_PIN); //ensure pin mode
	pin_mode = gpio_get_pin_level(BOOT_PIN);
	memset(pdata,0,200);
	while (1)
	{
		pin_mode = gpio_get_pin_level(BOOT_PIN);
		if(IS_BOOT_MODE){

			uart_recv(&buf,1);       //使用uart接收 1 byte 資料
			msg_id = packet_parser(pdata,buf,&ps);  //進行資料解析
			if (msg_id)
			{
				//gpio_set_pin_level(BUSY_PIN,false);
				message_decode(pdata,msg_id);
				memset(pdata,0,200);
				sp+=1;
				//gpio_set_pin_level(BUSY_PIN,true);
			}
				
			//can_bootloader_run
			//spi_bootloader_run
		}else{
			jump_to_application();
		}

	}
}
~~~~~~~~~~~~~



## 封包格式
![](https://i.imgur.com/zg8it96.png =100x20)
