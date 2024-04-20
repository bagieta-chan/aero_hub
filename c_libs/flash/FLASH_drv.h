#include "stm32f7xx_hal.h"
#include "spi.h"




#define BLOCK_NUM 4096
#define SECTOR_NUM 16

#define READ_STATUS_REGISTER1 0x05
#define READ_STATUS_REGISTER2 0x35
#define READ_STATUS_REGISTER3 0x15
#define READ_SFDP_REGISTER 0x5A

#define ERASE_SUSPEND 0x75
#define ERASE_RESUME 0x7A

#define WRITE_ENABLE 0x06
#define VOLATILE_SR_WRITE_ENABLE 0x50
#define WRITE_DISABLE 0x04

#define READ_UNIQUE_ID 0x4B
#define RELEASE_POWER_DOWN 0xAB
#define DEVICE_ID 0x90
#define JEDEC_ID 0x9F
#define CHIP_ERASE 0x60

#define WRITE_STATUS_REGISTER1 0x01
#define WRITE_STATUS_REGISTER2 0x31
#define WRITE_STATUS_REGISTER3 0x11

#define GLOBAL_BLOCK_LOCK 0x7E
#define GLOBAL_BLOCK_UNLOCK 0x98

#define POWER_DOWN 0xB9

#define ENTER_4_BYTE_ADDRESS_MODE 0xB7
#define EXIT_4_BYTE_ADDRESS_MODE 0xE9

#define ENABLE_RESET 0x66
#define RESET_DEVICE 0x99

#define SOFTWARE_DIE_SELECT 0xC2

#define READ_DATA 0x03
#define READ_DATA_4_BYTE 0x13
#define FAST_READ 0x0B
#define FAST_READ_4_BYTE 0x0C

#define PAGE_PROGRAM 0x02
#define PAGE_PROGRAM_4_BYTE 0x12

#define SECTOR_ERASE 0x20
#define SECTOR_ERASE_4_BYTE 0x21

#define BLOCK_ERASE_32KB 0x52
#define BLOCK_ERASE_64KB 0xD8
#define BLOCK_ERASE_32KB_4_BYTE 0xD8
#define ERASE_SECURITY_REGISTER 0x44
#define PROGRAM_SECURITY_REGISTER 0x42
#define READ_SECURITY_REGISTER 0x48

#define READ_BLOCK_LOCK 0x3D
#define INDIVIDUAL_BLOCK_LOCK 0x36
#define INDIVIDUAL_BLOCK_UNLOCK 0x39

#define FAST_READ_DUAL_OUTPUT 0x3B
#define FAST_READ_DUAL_OUTPUT_4_BYTE 0x3C

uint32_t flash_device_id = 0;


void FLASH_init(void); //not defined
//fnctions for reading from the memory
void FLASH_read(uint32_t Page, uint8_t offset, uint32_t size, uint8_t *buffer);
void FLASH_fastread(uint32_t Page, uint8_t offset, uint32_t size, uint8_t *buffer);
//functions to write into memory
void FLASH_writepage(uint32_t page, uint8_t offset, uint32_t size, uint8_t *data);
void FLASH_writeenable(void);
void FLASH_writedisable();
//functions to erase memory based on the size
void FLASH_blockerase(void);
void FLASH_sectorerase(void);
void FLASH_chiperase(void);
//functions to reset the module
void FLASH_reset(void);
//functions to set device into low power mode
void FLASH_powerdown(void);
void FLASH_powerdownrelease(void);
//functions to read id of the device
uint32_t FLASH_read_ID(void);