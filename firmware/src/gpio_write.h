#ifndef _GPIO_WRITE_H_
#define _GPIO_WRITE_H_

void gpio_write_on(uint32_t PinMask);
void gpio_write_off(uint32_t PinMask);
void gpio_init_read_mask(uint gpio_mask);
void gpio_init_write_mask(uint gpio_mask);

#endif
