#pragma once
#include <stdint.h>
#include "isr.h"

#define CHAR_CTRL_A (1)
#define CHAR_CTRL_B (2)
#define CHAR_CTRL_C (3)
#define CHAR_CTRL_D (4)
#define CHAR_CTRL_E (5)
#define CHAR_CTRL_F (6)
#define CHAR_CTRL_K (11)
#define CHAR_CTRL_N (14)
#define CHAR_CTRL_P (16)
#define CHAR_CTRL_U (21)
#define CHAR_CTRL_W (23)

void keyboard_handler(exception_t *rsp);
uint8_t read_scan_code(void);
uint8_t scan_code_to_ascii(uint8_t scan_code, _Bool shift);
uint8_t get_key_char(void);
