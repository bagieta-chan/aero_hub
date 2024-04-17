
import machine
import time
from constants import *

class FLASH:
    def __init__(self, sck_pin: int, mosi_pin: int, miso_pin: int, baudrate: int = 1000000, polarity: int = 0, phase: int = 0, cs: int = 15):
        self.spi = machine.SPI(1, baudrate=baudrate, polarity=polarity, phase=phase, sck=machine.Pin(sck_pin), mosi=machine.Pin(mosi_pin), miso=machine.Pin(miso_pin))
        self.cs = machine.Pin(cs, machine.Pin.OUT)
        self.cs.value(1)
        self.spi.init()
    
    def cs_low(self):
        self.cs.value(0)
    
    def cs_high(self):
        self.cs.value(1)
        
    def write_enable(self):
        self.cs_low()
        self.spi.write(WRITE_ENABLE)
        self.cs_high()
    
    def write_disable():
        self.cs_low()
        self.spi.write(WRITE_DISABLE)
        self.cs_high()
    
    def reset():
        self.cs_low()
        self.spi.write(ENABLE_RESET)
        self.spi_write(RESET_DEVICE)    
        
    def read_ID(self) -> bytes:
        self.cs_low()
        self.spi.write(DEVICE_ID)
        data = self.spi.read(3)
        self.cs_high()
        return data
    
    def read(Page: int, offset: int, size: int) -> bytes:
        memory_address = Page*256 + offset
        
        if memory_address < MAX_3_BYTE_ADDRESS:
            self.cs_low()
            self.spi.write(READ_DATA)
            self.spi.write(memory_address.to_bytes(3, 'big'))
            data = self.spi.read(size)
            self.cs_high()
            return data
        else:
            self.cs_low()
            self.spi.write(READ_DATA_4_BYTE)
            self.spi.write(memory_address.to_bytes(4, 'big'))
            data = self.spi.read(size)
            self.cs_high()
            return data
        
        
    def fast_read(self, Page: int, offset: int, size: int) -> bytes:
        memory_address = Page*256 + offset
        
        if memory_address < MAX_3_BYTE_ADDRESS:
            self.cs_low()
            self.spi.write(FAST_READ)
            self.spi.write(memory_address.to_bytes(3, 'big'))
            self.spi.write(0)
            data = self.spi.read(size)
            self.cs_high()
            return data
        else:
            self.cs_low()
            self.spi.write(FAST_READ_4_BYTE)
            self.spi.write(memory_address.to_bytes(4, 'big'))
            self.spi.write(0)
            data = self.spi.read(size)
            self.cs_high()
            return data
        
    def block_erase_64KB(self, block: int):
        memory_address = block*64*1024
        
        if memory_address < MAX_3_BYTE_ADDRESS:
            self.cs_low()
            self.spi.write(BLOCK_ERASE_64KB)
            self.spi.write(memory_address.to_bytes(3, 'big'))
            self.cs_high()
        else:
            self.cs_low()
            self.spi.write(BLOCK_ERASE_32KB_4_BYTE)
            self.spi.write(memory_address.to_bytes(4, 'big'))
            self.cs_high()
    
    def sector_erase(self, sector: int):
        memory_address = sector*4*1024
        
        if memory_address < MAX_3_BYTE_ADDRESS:
            self.cs_low()
            self.spi.write(SECTOR_ERASE)
            self.spi.write(memory_address.to_bytes(3, 'big'))
            self.cs_high()
        else:
            self.cs_low()
            self.spi.write(SECTOR_ERASE_4_BYTE)
            self.spi.write(memory_address.to_bytes(4, 'big'))
            self.cs_high()
    
    def
        
    
    
        
    