#include <interrupt.h>
#include <keyboard.h>
#include <kfslib.h>
#include <io.h>

keyboard_state kb_state;

#define KEY_CTRL        29
#define KEY_SHIFT       42
#define KEY_ALT         56
#define KEY_CAPS_LOCK   58
#define KEY_SPEC_RIGHT  96 // used with right CTRL and right ALT

#define KEY_LEFT_ARROW  75
#define KEY_RIGHT_ARROW 77

const uint32_t lowercase[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

const uint32_t uppercase[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


void keyboard_handler(struct interrupt_registers *regs) {
    (void) regs;
    unsigned char scancode = inb(0x60) & 0x7F; // what key is pressed
    unsigned char press = inb(0x60) & 0x80; // press down or released

    //printk("scan code %d, press %d\n", scancode, press);

    switch (scancode) {
        case KEY_SHIFT:
            if (press == 0)
                kb_state.shift_press = true;
            else
                kb_state.shift_press = false;
            break;
        case KEY_ALT:
            if (press == 0)
                kb_state.alt_press = true;
            else
                kb_state.alt_press = false;
            break;
        case KEY_CTRL:
            if (press == 0)
                kb_state.ctrl_press = true;
            else
                kb_state.ctrl_press = false;
            break;
        case KEY_SPEC_RIGHT:
            if (press == 0)
                kb_state.special_right = true;
            else
                kb_state.special_right = false;
            break;
        case KEY_CAPS_LOCK:
            if (!kb_state.caps_lock && press == 0)
                kb_state.caps_lock = true;
            else if (kb_state.caps_lock && press == 0)
                kb_state.caps_lock = false;
            break;
        case KEY_LEFT_ARROW:
            if (kb_state.special_right && press == 0)
              cursor_left();
            break;
        case KEY_RIGHT_ARROW:
            if (kb_state.special_right && press == 0)
              cursor_right();
            break;
        default:
            if (press == 0) {
                if (kb_state.caps_lock || kb_state.shift_press)
                    printk("%c", uppercase[scancode]);
                else
                    printk("%c", lowercase[scancode]);
            }
    }

}

void init_keyboard(void) {
    kb_state.shift_press = false;
    kb_state.caps_lock = false;
    kb_state.ctrl_press = false;
    kb_state.alt_press = false;
    
    // install IRQ1 handler
    irq_install_handler(1, &keyboard_handler);
}
