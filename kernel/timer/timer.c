#include <interrupt.h>
#include <io.h>
#include <timer.h>

uint64_t ticks;
const uint32_t freq = 100;

void on_irq0(struct interrupt_registers *regs) {
    (void)regs;
    ticks += 1;
    //printk("timer tick: %d\n", ticks);
}

void init_timer(void) {
    ticks = 0;
    irq_install_handler(0, &on_irq0);

    // 1193118.16666 hz
    uint32_t divisor = 1193180 / freq;

    outb(PIT_MODE_CMD_REG, 0x36); // 00110110 => channel 0 | Access mode = lobyte/hibyte | mode 3 = square wave generator
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);

}