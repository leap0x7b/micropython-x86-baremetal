#include "kernel.h"
#include "keyboard.h"
#include "py/mpconfig.h"

int mp_hal_stdin_rx_chr(void) {
    uint8_t c = 0;
    c = get_key_char();
    return c;
}

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    term_write(str, len);
}
