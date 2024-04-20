from flash.flash import FLASH
from pressure_sensor.APB2 import APB2
import threading

flash = None
pressure_sensor = None


periphs_init = threading.Event()
    
def read_flash(flash_queue,temp_queue, pressure_queue):
    global periphs_init
    
    periphs_init.wait()
    
    flash.read(0, 0, 256)
    
def read_APB2(temp_queue, pressure_queue):
    global periphs_init
    
    periphs_init.wait()
    
    pressure_sensor.read()
    
def init_threads():
      
    global flash
    global pressure_sensor
    flash = FLASH(14, 13, 12)     
    while not flash:
        i = 0
           
    pressure_sensor = APB2(1, 2, 3, 4, 5, 6)   
    while not pressure_sensor:
        i = 0
            
    

    
    

temp_queue = queue.Queue()
pressure_queue = queue.Queue()
flash_queue = queue.Queue()

init_thread = threading.Thread(target=init_threads)
flash_thread = threading.Thread(target=read_flash, args = (flash_queue))
pressure_thread = threading.Thread(target=read_APB2, args=(temp_queue, pressure_queue)) 


flash_thread.start()
pressure_thread.start()

flash_thread.join()
pressure_thread.join()

