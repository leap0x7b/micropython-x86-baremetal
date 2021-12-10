#pragma once
#include <stdint.h>

#define EXCEPTION(n) \
    void isr_##n(exception_t *rsp) { \
        isr_handler(n, rsp); \
    }

typedef struct {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    uint64_t isr_number;
    uint64_t error_code;

    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} exception_t;

static char *exceptions[] = {
    [0] = "Division-by-zero",
    [1] = "Keyboard",
    [2] = "Non-maskable interrupt",
    [3] = "Breakpoint",
    [4] = "Overflow",
    [5] = "Bound range exceeded",
    [6] = "Invalid opcode",
    [7] = "Device not available",
    [8] = "Double fault",
    [9] = "Coprocessor segment overrun",
    [10] = "Invalid TSS",
    [11] = "Segment not present",
    [12] = "Stack fault",
    [13] = "General protection fault",
    [14] = "Page fault",
    [16] = "x87 floating-point exception",
    [17] = "Alignment check",
    [18] = "Machine check",
    [19] = "SIMD floating-point exception",
    [20] = "Virtualization exception",
    [30] = "Security exception"
};

void isr_handler(uint64_t irq, exception_t *rsp);
void isr_0(exception_t *rsp);
void isr_1(exception_t *rsp);
void isr_2(exception_t *rsp);
void isr_3(exception_t *rsp);
void isr_4(exception_t *rsp);
void isr_5(exception_t *rsp);
void isr_6(exception_t *rsp);
void isr_7(exception_t *rsp);
void isr_8(exception_t *rsp);
void isr_9(exception_t *rsp);
void isr_10(exception_t *rsp);
void isr_11(exception_t *rsp);
void isr_12(exception_t *rsp);
void isr_13(exception_t *rsp);
void isr_14(exception_t *rsp);
void isr_16(exception_t *rsp);
void isr_17(exception_t *rsp);
void isr_18(exception_t *rsp);
void isr_19(exception_t *rsp);
void isr_20(exception_t *rsp);
void isr_30(exception_t *rsp);
void isr_reserved(void);
