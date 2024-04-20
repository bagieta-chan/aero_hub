BLOCK_NUM = 4096
SECTOR_NUM = 16

READ_STATUS_REGISTER1 = 0x05
READ_STATUS_REGISTER2 = 0x35
READ_STATUS_REGISTER3 = 0x15
READ_SFDP_REGISTER = 0x5A

ERASE_SUSPEND = 0x75
ERASE_RESUME =0x7A

WRITE_ENABLE = 0x06
VOLATILE_SR_WRITE_ENABLE = 0x50
WRITE_DISABLE = 0x04

READ_UNIQUE_ID = 0x4B
RELEASE_POWER_DOWN = 0xAB
DEVICE_ID = 0x90
JEDEC_ID = 0x9F
CHIP_ERASE = 0x60

WRITE_STATUS_REGISTER1 = 0x01
WRITE_STATUS_REGISTER2 = 0x31
WRITE_STATUS_REGISTER3 = 0x11

GLOBAL_BLOCK_LOCK = 0x7E
GLOBAL_BLOCK_UNLOCK = 0x98

POWER_DOWN = 0xB9

ENTER_4_BYTE_ADDRESS_MODE = 0xB7
EXIT_4_BYTE_ADDRESS_MODE = 0xE9

ENABLE_RESET = 0x66
RESET_DEVICE = 0x99

SOFTWARE_DIE_SELECT = 0xC2
READ_DATA = 0x03
READ_DATA_4_BYTE = 0x13
FAST_READ = 0x0B
FAST_READ_4_BYTE = 0x0C

PAGE_PROGRAM = 0x02
PAGE_PROGRAM_4_BYTE = 0x12

SECTOR_ERASE = 0x20
SECTOR_ERASE_4_BYTE = 0x21

BLOCK_ERASE_32KB = 0x52
BLOCK_ERASE_64KB = 0xD8
BLOCK_ERASE_32KB_4_BYTE = 0xD8
ERASE_SECURITY_REGISTER = 0x44
PROGRAM_SECURITY_REGISTER = 0x42
READ_SECURITY_REGISTER = 0x48

READ_BLOCK_LOCK = 0x3D
INDIVIDUAL_BLOCK_LOCK = 0x36
INDIVIDUAL_BLOCK_UNLOCK = 0x39

FAST_READ_DUAL_OUTPUT = 0x3B
FAST_READ_DUAL_OUTPUT_4_BYTE = 0x3C