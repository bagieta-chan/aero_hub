#include "FLASH_drv.h"

#define MAX_3BYTE_PAGE 65535
#define MAX_4BYTE_PAGE 1048575
#define MAX_3BYTE_BYTE 16777215
#define MAX_BLOCK_NUM 4095
#define MAX_SECTOR_NUM 65535
#define MAX_SECTOR_PER_BLOCK 16


#define CS_LOW() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

#define FLASH_SPI hspi1
//enable writing to the flash
void FLASH_writeenable(){
    uint8_t data = WRITE_ENABLE;
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, &data, 1, HAL_MAX_DELAY);

    CS_HIGH();
}

//diable writing to the flash
void FLASH_writedisable(){
    uint8_t data = WRITE_DISABLE;
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, &data, 1, HAL_MAX_DELAY);

    CS_HIGH();
}

//reset the flash, recommended when the flash is not responding or when program is being loaded
void FLASH_reset(){
    uint8_t data = ENABLE_RESET;
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, &data, 1, HAL_MAX_DELAY);
    data = RESET_DEVICE;
    HAL_SPI_Transmit(&FLASH_SPI, &data, 1, HAL_MAX_DELAY);

    CS_HIGH();
}
//read manufacturer and the device id
uint32_t FLASH_read_ID(){
    uint8_t data = JEDEC_ID;
    uint8_t id[3];
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, &data, 1, HAL_MAX_DELAY);   
    HAL_SPI_Receive(&FLASH_SPI, id, 3, HAL_MAX_DELAY);

    CS_HIGH();

    return (id[0] << 16) | (id[1] << 8) | id[2];
}
//read from the memory, case-sensitive when it comes to the address size
void FLASH_read(uint32_t Page, uint8_t offset, uint32_t size, uint8_t *buffer){

    uint8_t data[5];
    uint32_t memAddr = Page*256 + offset;

    if(memAddr < MAX_3BYTE_BYTE){
    
    
        data[0] = READ_DATA;
        data[1] = (memAddr >> 16) & 0xFF;
        data[2] = (memAddr >> 8) & 0xFF;
        data[3] = memAddr & 0xFF;

        CS_LOW();

        HAL_SPI_Transmit(&FLASH_SPI, data, 4, HAL_MAX_DELAY);
    }
    
    
    else{
        
        data[0] = READ_DATA_4_BYTE; 
        data[1] = (memAddr >> 24) & 0xFF;
        data[2] = (memAddr >> 16) & 0xFF;
        data[3] = (memAddr >> 8) & 0xFF;
        data[4] = memAddr & 0xFF;

        CS_LOW();

        HAL_SPI_Transmit(&FLASH_SPI, data, 5, HAL_MAX_DELAY);
    }

    
    CS_HIGH();
    HAL_SPI_Receive(buffer, size, HAL_MAX_DELAY);

}
//read from the memory, case-sensitive when it comes to the address size, faster than FLASH_read
void FLASH_fastread(uint32_t Page, uint8_t offset, uint32_t size, uint8_t *buffer){

    uint8_t data[6];
    uint32_t memAddr = Page*256 + offset;

    if(memAddr < MAX_3BYTE_BYTE){

        data[0] = FAST_READ;
        data[1] = (memAddr >> 16) & 0xFF;
        data[2] = (memAddr >> 8) & 0xFF;
        data[3] = memAddr & 0xFF;
        data[4] = 0x00

        CS_LOW();

        HAL_SPI_Transmit(&FLASH_SPI, data, 4, HAL_MAX_DELAY);
    }
    
    
    else{

        data[0] = FAST_READ_4_BYTE; 
        data[1] = (memAddr >> 24) & 0xFF;
        data[2] = (memAddr >> 16) & 0xFF;
        data[3] = (memAddr >> 8) & 0xFF;
        data[4] = memAddr & 0xFF;
        data[5] = 0x00;

        CS_LOW();

        HAL_SPI_Transmit(&FLASH_SPI, data, 5, HAL_MAX_DELAY);
    }

    CS_HIGH();
    HAL_SPI_Receive(buffer, size, HAL_MAX_DELAY);
    
}
//erase a block of memory
void FLASH_blockerase(uint32_t block){
    
    memAddr = block*16*16*256;
    uint8_t data[5];

    if(block>MAX_BLOCK_NUM) return;

    data[0] = BLOCK_ERASE_64KB; 
    data[1] = (memAddr >> 24) & 0xFF;
    data[2] = (memAddr >> 16) & 0xFF;
    data[3] = (memAddr >> 8) & 0xFF;
    data[4] = memAddr & 0xFF;

    CS_LOW(); 

    HAL_SPI_Transmit(&FLASH_SPI, data, 5, HAL_MAX_DELAY); 

    CS_HIGH(); 
}
//erase a sector of memory
void FLASH_sectorerase(uint32_t sector){

    memAddr = sector * 16 * 256;
    uint8_t data[6];

    if(sector>MAX_SECTOR_NUM) return;

    data[0] = SECTOR_ERASE; 
    data[1] = (memAddr >> 24) & 0xFF;
    data[2] = (memAddr >> 16) & 0xFF;
    data[3] = (memAddr >> 8) & 0xFF;
    data[4] = memAddr & 0xFF;

    CS_LOW();   

    HAL_SPI_Transmit(&FLASH_SPI, data, 5, HAL_MAX_DELAY);

    CS_HIGH();
}   
//erase the entire memory
void FLASH_chiperase(void){
    uint8_t data = CHIP_ERASE;
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, data, 1, HAL_MAX_DELAY);

    CS_HIGH();
}
//power down the memory
void FLASH_powerdown(void){
    uint8_t data = POWER_DOWN;
    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, data, 1, HAL_MAX_DELAY);

    CS_HIGH();
}
//release the memory from power down
void FLASH_releasepowerdown(void){
    uint8_t data[4];

    data[0] = RELEASE_POWER_DOWN;
    data[1] = 0xFF;
    data[2] = 0xFF;
    data[3] = 0xFF;

    CS_LOW();

    HAL_SPI_Transmit(&FLASH_SPI, data, 4, HAL_MAX_DELAY);

    CS_HIGH();
}
//determinates the number of bytes to write remaining
uint32_t bytesToWrite(uint32_t size, uint16_t offset){
    if((size+offset)<256) return size;
    else return 256-offset;
}
//write data into the memory, snsitive to the page boundaries
void FLASH_writepage(uint32_t page, uint8_t offset, uint32_t size, uint8_t *data){

    uint8_t tData[256];
    uint32_t start_page = page;
    uint32_t end_page = start_page + (size +offset -1)/256;
    uint32_t num_pages = end_page - start_page + 1;

    uint16_t start_sector = start_page/16;
    uint16_t end_sector = end_page/16;
    uint16_t sectors_num = end_sector - start_sector + 1;

    while(uint16_t i =0; i<sectors_num; i++){

        FLASH_sectorerase(start_sector++);
    }

    uint32_t data_pos = 0

    //write the data
    for(uint32_t i = start_page; i<=num_pages; i++){
       
       uint32_t memAddr = (start_page*256) + offset;

       uint16_t bytes_to_write = bytesToWrite(size, offset);

       index = 0;

       FLASH_writeenable();

       if(memAddr < MAX_3BYTE_BYTE){    
    
            tData[0] = PAGE_PROGRAM;
            tData[1] = (memAddr >> 16) & 0xFF;
            tData[2] = (memAddr >> 8) & 0xFF;
            tData[3] = memAddr & 0xFF;

            index = 4;

            CS_LOW();

            HAL_SPI_Transmit(&FLASH_SPI, data, 4, HAL_MAX_DELAY);

            CS_HIGH();
        }    
    
        else{

            tData[0] = PAGE_PROGRAM_4_BYTE; 
            tData[1] = (memAddr >> 24) & 0xFF;
            tData[2] = (memAddr >> 16) & 0xFF;
            tData[3] = (memAddr >> 8) & 0xFF;
            tData[4] = memAddr & 0xFF;

            index = 5;

            CS_LOW();

            HAL_SPI_Transmit(&FLASH_SPI, data, 5, HAL_MAX_DELAY);

            CS_HIGH();
        }

        uint16_t bytes_to_send = bytes_to_write + index;

        for(uint16_t i=0; i<bytes_to_write; i++){
            tData[index++] = data[i+data_pos];
        }

        CS_LOW();
        HAL_SPI_Write(&FLASH_SPI, tData, bytes_to_send, HAL_MAX_DELAY);
        CS_HIGH();

        start_page++;

        offset = 0;

        size = size - bytes-to_write;

        data_pos = data_pos + bytes_to_write;   

        HAL_Delay(3);

    }

}



