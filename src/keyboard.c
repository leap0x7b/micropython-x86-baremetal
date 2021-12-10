#include <stdbool.h>
#include "io.h"
#include "pic.h"
#include "keyboard.h"

bool shift = false;
bool ctrl = false;

uint8_t kbd[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\r',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,
    '*',
    0,
    ' ',
    0,
    0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0',
    '.',
    0, 0, 0,
    0,
    0,
    0
};

uint8_t kbd_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+', '\b',
    '\t',
    'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\r',
    0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', 0,
    '|', 'X', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?', 0,
    '*',
    0,
    ' ',
    0,
    0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    '7', '8', '9', '-',
    '4', '5', '6', '+',
    '1', '2', '3', '0',
    '.',
    0, 0, 0,
    0,
    0,
    0
};

uint8_t read_scan_code(void) {
    char c;
    c = inb(0x60);
    return c;
}

uint8_t scan_code_to_ascii(uint8_t scan_code, bool shift) {
    if (shift) return kbd_shift[(uint8_t)scan_code];
    return kbd[(uint8_t)scan_code];
}

void keyboard_handler(exception_t *rsp) {
    (void)rsp;
    outb(0x21, 0xFD);
}

uint8_t get_key_char(void) {
    pic_eoi(1);

    uint8_t state = inb(0x64);
    uint8_t scan_code = inb(0x60);

    if (state & 1) {
        if (scan_code & 0x80) {
            switch (scan_code) {
                case 0xaa:
                case 0xb6:
                    shift = false;
                    break;
                case 0x9d:
                    ctrl = false;
                    break;
            }
        } else {
            switch (scan_code) {
                case 0x2a:
                case 0x36:
                    shift = true;
                    break;
                case 0x1d:
                    ctrl = true;
                default: {
                    char c = scan_code_to_ascii(scan_code, shift);
                    if (ctrl) {
                        switch (c) {
                            case 'a':
                            case 'A':
                                return CHAR_CTRL_A;
                            case 'b':
                            case 'B':
                                return CHAR_CTRL_B;
                            case 'c':
                            case 'C':
                                return CHAR_CTRL_C;
                            case 'd':
                            case 'D':
                                return CHAR_CTRL_D;
                            case 'e':
                            case 'E':
                                return CHAR_CTRL_E;
                            case 'f':
                            case 'F':
                                return CHAR_CTRL_F;
                            case 'k':
                            case 'K':
                                return CHAR_CTRL_K;
                            case 'n':
                            case 'N':
                                return CHAR_CTRL_N;
                            case 'p':
                            case 'P':
                                return CHAR_CTRL_P;
                            case 'u':
                            case 'U':
                                return CHAR_CTRL_U;
                            case 'w':
                            case 'W':
                                return CHAR_CTRL_W;
                        }
                    }
                    return c;
                 }
            }
        }
    }

    return 0;
}
