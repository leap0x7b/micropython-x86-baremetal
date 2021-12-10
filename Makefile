include external/micropython/py/mkenv.mk
MICROPY_ROM_TEXT_COMPRESSION ?= 0
include $(TOP)/py/py.mk

CC = clang
LD = ld.lld

INC += -I.
INC += -Isrc
INC += -Isrc/libc
INC += -Iexternal/stivale
INC += -I$(TOP)
INC += -I$(BUILD)

QSTR_GEN_CFLAGS = $(INC)
QSTR_GEN_CXXFLAGS = $(INC)

CFLAGS = -target x86_64-none-elf $(INC) -nostdlib -ffreestanding -fno-stack-protector -fno-pic -mabi=sysv -mcmodel=kernel -mno-red-zone -msoft-float $(CFLAGS_EXTRA)
LDFLAGS = -nostdlib -Tsrc/linker.ld -melf_x86_64 -z max-page-size=0x1000 -static
CXXFLAGS += $(filter-out -std=c99,$(CFLAGS))
CXXFLAGS += $(CXXFLAGS_MOD)
CFLAGS += $(CFLAGS_MOD)
LDFLAGS += $(LDFLAGS_MOD)

SRC_C += $(wildcard src/*.c src/*/*.c) shared/libc/printf.c shared/readline/readline.c shared/runtime/gchelper_generic.c shared/runtime/pyexec.c shared/runtime/stdout_helpers.c shared/runtime/interrupt_char.c shared/libc/string0.c
SRC_C += $(SRC_MOD)
SRC_CXX += $(SRC_MOD_CXX)
SRC_QSTR += $(SRC_MOD) $(SRC_MOD_CXX)

OBJ += $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_CXX:.cpp=.o))

all: $(shell mkdir -p $(BUILD)) $(BUILD)/micropython.iso

limine:
	$(Q)$(MAKE) --no-print-directory -C external/limine

$(BUILD)/micropython.iso: limine $(BUILD)/kernel.elf
	$(Q)$(RM) -rf $(BUILD)/sysroot
	$(Q)mkdir -p $(BUILD)/sysroot/boot
	$(Q)cp -r src/limine.cfg $(BUILD)/sysroot
	$(Q)cp $(BUILD)/kernel.elf external/limine/limine.sys $(BUILD)/sysroot/boot
	$(Q)cp external/limine/limine-cd.bin external/limine/limine-eltorito-efi.bin $(BUILD)/sysroot
	$(ECHO) "XORRISO $@"
	$(Q)xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-eltorito-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		$(BUILD)/sysroot -o $@
	$(ECHO) "LIMINE $@"
	$(Q)external/limine/limine-install $@

$(BUILD)/kernel.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	$(Q)$(SIZE) $@

run: $(BUILD)/micropython.iso
	qemu-system-x86_64 -m 2G -M q35 -cdrom $< -serial stdio -no-reboot -no-shutdown $(QEMUFLAGS)

include $(TOP)/py/mkrules.mk
