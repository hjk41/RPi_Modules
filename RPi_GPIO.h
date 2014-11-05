#pragma once

#include <stdint.h>

namespace GPIO
{

    enum GPIO_EC
    {
        GPIO_SUCCESS = 0,
        GPIO_ERROR_PRIVILEDGE = -1,
        GPIO_ERROR_MMAP = -2
    };

    extern volatile uint32_t* __gpio_start_addr;

    GPIO_EC GPIOInit(void);

    inline bool GPIOInitialized()
    {
        return __gpio_start_addr != NULL;
    }

    inline void GPIOSetInput(const int pin) 
    {
        // Set GPIO pin to input mode
        *(__gpio_start_addr + ((pin) / 10)) &= ~(7 << (((pin) % 10) * 3));
    }

    inline void GPIOSetOutput(const int pin)
    {
        // Set GPIO pin to output mode
        GPIOSetInput(pin);
        *(__gpio_start_addr + ((pin) / 10)) |= (1 << (((pin) % 10) * 3));
    }

    inline void GPIOSetHigh(const int pin)
    {
        // set GPIO pin to high
        *(__gpio_start_addr + 7) = 1 << pin;
    }

    inline void GPIOSetLow(const int pin)
    {
        // set GPIO pin to high
        *(__gpio_start_addr + 10) = 1 << pin;
    }

    inline bool GPIORead(const int pin) {
        // read value from pin, high is true, low is false
        return (*(__gpio_start_addr + 13) & (1 << pin)) > 0;
    }

}
