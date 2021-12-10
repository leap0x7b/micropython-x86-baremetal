#pragma once
#include <stdint.h>

static inline void cpuid(uint32_t code, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    asm volatile("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(code));
}

static char string[13];
static inline char *cpuid_string(uint32_t code) {
    uint32_t eax, ebx, ecx, edx;

    cpuid(code, &eax, &ebx, &ecx, &edx);
    *(uint32_t *)&string[0] = ebx;
    *(uint32_t *)&string[4] = edx;
    *(uint32_t *)&string[8] = ecx;
    string[12] = '\0';

    return string;
}
