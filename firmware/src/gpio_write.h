#ifndef _GPIO_WRITE_H_
#define _GPIO_WRITE_H_

void gpio_write_on_mask(int PinMask);
void gpio_write_off_mask_maybe(int PinMask);
void gpio_init_read_mask(int gpio_mask);
void gpio_init_write_mask(int gpio_mask);

#endif
