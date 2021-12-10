#include <stdint.h>
#include "src/cpu.h"

#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)
#define MICROPY_ENABLE_COMPILER (1)

//#define MICROPY_QSTR_EXTRA_POOL bmp_qstr_frozen_const_pool
#define MICROPY_ENABLE_GC (1)
#define MICROPY_HELPER_REPL (1)
#define MICROPY_MODULE_FROZEN_MPY (0)
#define MICROPY_ENABLE_EXTERNAL_IMPORT (0)
#define MICROPY_ENABLE_PYSTACK (0)
#define MICROPY_USE_INTERNAL_ERRNO (1)
#define MICROPY_PY_IO (0)
#define MICROPY_KBD_EXCEPTION (1)

#define MICROPY_ALLOC_PATH_MAX (256)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT (16)

typedef intptr_t mp_int_t;
typedef uintptr_t mp_uint_t;
typedef long mp_off_t;

#define MICROPY_PORT_BUILTINS \
    { MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_builtin_open_obj) },

#include <alloca.h>

static char brand[48];
static char *get_cpu_brand(void) {
    cpuid(0x80000002, (uint32_t *)&brand[0], (uint32_t *)&brand[4], (uint32_t *)&brand[8], (uint32_t *)&brand[12]);
    cpuid(0x80000003, (uint32_t *)&brand[16], (uint32_t *)&brand[20], (uint32_t *)&brand[24], (uint32_t *)&brand[28]);
    cpuid(0x80000004, (uint32_t *)&brand[32], (uint32_t *)&brand[36], (uint32_t *)&brand[40], (uint32_t *)&brand[44]);
    return brand;
}

#define MICROPY_HW_BOARD_NAME "PC"
//#define MICROPY_HW_MCU_NAME (get_cpu_brand())
#define MICROPY_HW_MCU_NAME ); mp_hal_stdout_tx_str(get_cpu_brand()); mp_hal_stdout_tx_str(

#ifdef __linux__
#define MICROPY_MIN_USE_STDOUT (1)
#endif

#ifdef __thumb__
#define MICROPY_MIN_USE_CORTEX_CPU (1)
#define MICROPY_MIN_USE_STM32_MCU (1)
#endif

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8];
