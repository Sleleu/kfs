# ifndef KERNEL_INCLUDE_TIMER_H
# define KERNEL_INCLUDE_TIMER_H

#include <interrupt.h>

#define PIT_CHANNEL0        0x40
#define PIT_CHANNEL1        0x41
#define PIT_CHANNEL2        0x42
#define PIT_MODE_CMD_REG    0x43


void init_timer(void);
void on_irq0(struct interrupt_registers *regs);

#endif