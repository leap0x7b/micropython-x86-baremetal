#pragma once
#include <stddef.h>

extern void (*term_write)(const char *string, size_t length);
