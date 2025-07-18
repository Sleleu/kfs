#ifndef KERNEL_INCLUDE_KEYBOARD_H
#define KERNEL_INCLUDE_KEYBOARD_H

typedef struct {
    bool shift_press;
    bool caps_lock;
    bool ctrl_press;
    bool alt_press;
} keyboard_state;

void init_keyboard(void);

#endif