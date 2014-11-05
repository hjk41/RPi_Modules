#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "RPi_GPIO.h"

namespace GPIO
{

    #define BASE 0x20000000
    #define GPIO_BASE (BASE + 0x200000)
    #define GPIO_LENGTH 4096

    volatile uint32_t* __gpio_start_addr = NULL;

    GPIO_EC GPIOInit(void) 
    {
        if (__gpio_start_addr == NULL) 
        {
            int fd = open("/dev/mem", O_RDWR | O_SYNC);
            if (fd == -1) 
            {
                // Error opening /dev/mem.  Probably not running as root.
                return GPIO_ERROR_PRIVILEDGE;
            }
            // Map GPIO memory to location in process space.
            __gpio_start_addr = (uint32_t*)mmap(NULL, GPIO_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
            close(fd);
            if (__gpio_start_addr == MAP_FAILED) 
            {
                // Don't save the result if the memory mapping failed.
                __gpio_start_addr = NULL;
                return GPIO_ERROR_MMAP;
            }
        }
        return GPIO_SUCCESS;
    }

}
