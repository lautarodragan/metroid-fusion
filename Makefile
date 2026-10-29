# Disable built-in rules
.SUFFIXES:

# Remove targets whose recipe failed (agbcc writes its output even on errors)
.DELETE_ON_ERROR:

REGION ?= us
PAD_TO = 0x08800000

ifeq ($(REGION),us)
	TARGET = mf_us
	GAME_TITLE = METROID4USA
	GAME_CODE = AMTE
	CPPFLAGS += -DREGION_US
	ASFLAGS += --defsym REGION_US=1
endif

# ifeq ($(REGION),eu)
# 	TARGET = mf_eu
# 	GAME_TITLE = METROID4EUR
# 	GAME_CODE = AMTP
# 	CPPFLAGS += -DREGION_EU
# 	ASFLAGS += --defsym REGION_EU=1
# endif

# ifeq ($(REGION),eu_beta)
# 	TARGET = mf_eu_beta
# 	GAME_TITLE = METROIDAGBJ
# 	GAME_CODE = METJ
# 	CPPFLAGS += -DREGION_EU -DREGION_EU_BETA -DDEBUG
# 	ASFLAGS += --defsym REGION_EU=1 --defsym REGION_EU_BETA=1 --defsym DEBUG=1
# 	PAD_TO = 0x09000000
# endif

# ifeq ($(REGION),jp)
# 	TARGET = mf_jp
# 	GAME_TITLE = METROID4JPN
# 	GAME_CODE = AMTJ
# 	CPPFLAGS += -DREGION_JP
# 	ASFLAGS += --defsym REGION_JP=1
# endif

# ifeq ($(REGION),cn)
# 	TARGET = mf_cn
# 	GAME_TITLE = METFUSIONCHN
# 	GAME_CODE = AMTC
# 	CPPFLAGS += -DREGION_CN
#	ASFLAGS += --defsym REGION_CN=1
# endif

ifeq ($(DEBUG),1)
	CPPFLAGS += -DDEBUG
	ASFLAGS += --defsym DEBUG=1
	TARGET := $(TARGET)_debug
endif

BASEROM := $(TARGET)_baserom.gba

# Shift test build: SHIFT=1 links the same objects with SHIFT_AMOUNT bytes of
# padding inserted in the middle of the code and again at the start of the
# data, into $(TARGET)_shifted.gba (see tools/check_shift.sh)
SHIFT ?= 0
SHIFT_AMOUNT ?= 0x100
ifeq ($(SHIFT),1)
	TARGET := $(TARGET)_shifted
	LD_CPPFLAGS += -DSHIFT_TEST=$(SHIFT_AMOUNT)
endif

# Non-matching variants (see book/src/performance.md):
#   PROFILE=1     cycle profiler, frame totals (include/profile.h), *_profile.gba
#   PROFILE=2     cycle profiler, every subsystem, *_profile2.gba
#   OPTIMIZE=...  performance changes, *_opt.gba: OPTIMIZE=1 enables all of
#                 them, or a list of names enables some (e.g.
#                 OPTIMIZE="PROJ_HIT DRAW_ORDER"), each one as
#                 -DOPTIMIZE_<name>
PROFILE ?= 0
OPTIMIZE ?= 0
OPTIMIZE_ALL = PROJ_HIT DRAW_ORDER
VARIANT_CPPFLAGS =
ifeq ($(PROFILE),1)
	VARIANT_CPPFLAGS += -DPROFILE
	TARGET := $(TARGET)_profile
endif
ifeq ($(PROFILE),2)
	VARIANT_CPPFLAGS += -DPROFILE -DPROFILE_DETAIL
	TARGET := $(TARGET)_profile2
endif
ifneq ($(OPTIMIZE),0)
	ifeq ($(OPTIMIZE),1)
		OPTIMIZE_NAMES = $(OPTIMIZE_ALL)
	else
		OPTIMIZE_NAMES = $(OPTIMIZE)
	endif
	VARIANT_CPPFLAGS += -DOPTIMIZE $(addprefix -DOPTIMIZE_,$(OPTIMIZE_NAMES))
	TARGET := $(TARGET)_opt
endif
CPPFLAGS += $(VARIANT_CPPFLAGS)

TARGET := $(TARGET).gba

# Default target
.PHONY: all
all: $(TARGET)

ELF = $(TARGET:.gba=.elf)
MAP = $(TARGET:.gba=.map)
SHA1FILE = $(TARGET:.gba=.sha1)
DUMPS = $(BASEROM:.gba=.dump) $(TARGET:.gba=.dump)
LD_SCRIPT = $(TARGET:.gba=.ld.pp)

# ROM header
MAKER_CODE = 01
GAME_REVISION = 00

# Binaries
CPP = cpp
TOOLCHAIN ?= arm-none-eabi-
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump

CC = agbcc

DIFF = diff -u
HOSTCC = cc
MKDIR = mkdir -p
RM = rm -f
SHA1SUM = sha1sum
TAIL = tail

# Tools
include make_tools.mk
GBAFIX = $(TOOLS_DIR)/gbafix/gbafix
PYTHON = python3
EXTRACTOR = $(PYTHON) $(TOOLS_DIR)/extractor.py
PREPROC = $(TOOLS_DIR)/preproc/preproc

# Flags
ASFLAGS += -mcpu=arm7tdmi
CFLAGS = -Werror -O2 -mthumb-interwork -fhex-asm
CPPFLAGS += -nostdinc -Iinclude/
PREPROCFLAGS = charmap.txt

# Objects
CSRC = $(wildcard src/**.c) $(wildcard src/**/**.c) $(wildcard src/**/**/**.c) $(wildcard src/**/**/**/**.c)
.PRECIOUS: $(CSRC:.c=.s)
ASMSRC = $(CSRC:.c=.s) $(wildcard asm/*.s) $(wildcard sound/*.s) $(wildcard sound/**/*.s)
OBJ = $(ASMSRC:.s=.o) 

# Detect if agbcc was installed into the project
ifneq (,$(wildcard tools/agbcc))
	AGBCC_BIN := tools/agbcc/bin/agbcc
	AGBCC_LIB := tools/agbcc/lib
	CC = $(AGBCC_BIN)
else
	# Dynamically find agbcc path and its lib folder
	AGBCC_BIN := $(shell which agbcc)
	AGBCC_DIR := $(dir $(AGBCC_BIN))/
	AGBCC_LIB := $(abspath $(AGBCC_DIR))
endif

LIBS := $(AGBCC_LIB)/libgcc.a $(AGBCC_LIB)/libc.a


# Enable verbose output
ifeq ($(V),1)
	Q =
	MSG = @:
else
	Q = @
	MSG = @echo " "
endif

# Rules that do not require scanning for dependencies
RULES_NO_SCAN += dump diff extract clean tidy check-synthetic check-shift

# Generate tools before building anything
SETUP_PREREQS ?= 1
# Disable generating tools for rules that do not build anything
ifneq (,$(MAKECMDGOALS))
  ifeq (,$(filter-out $(RULES_NO_SCAN),$(MAKECMDGOALS)))
    SETUP_PREREQS := 0
  endif
endif
.SHELLSTATUS ?= 0
ifeq ($(SETUP_PREREQS),1)
  $(foreach line, $(shell $(MAKE) -f make_tools.mk | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))
  ifneq ($(.SHELLSTATUS),0)
    $(error Errors occurred while building tools. See error messages above for more details)
  endif
endif

.PHONY: check
check: all
	$(MSG) SHA1SUM $(SHA1FILE)
	$Q$(SHA1SUM) -c $(SHA1FILE)

.PHONY: check-synthetic
check-synthetic:
	$Qtools/check_synthetic.sh

.PHONY: check-shift
check-shift:
	$Qtools/check_shift.sh

.PHONY: dump
dump: $(DUMPS)

.PHONY: diff
diff: $(DUMPS)
	$(MSG) DIFF $^
	$Q$(DIFF) $^

.PHONY: extract
extract:
	$(MSG) Extracting
	$Q$(EXTRACTOR) -r $(REGION)

.PHONY: clean
clean: clean-tools tidy

.PHONY: tidy
tidy:
	$(MSG) RM roms
# Delete every gba file that doesn't end with baserom
	$Qfind -type f -name "*.gba" -a ! -name "*baserom.gba" -delete
	$(MSG) RM elf
	$Q$(RM) *.elf
	$(MSG) RM map
	$Q$(RM) *.map

	$(MSG) RM \*.dump
	$Q$(RM) $(DUMPS)
	$(MSG) RM \*.o
	$Q$(RM) $(OBJ)
	$(MSG) RM data/*.s
	$(MSG) RM src/\*\*/\*.s
	$Q$(RM) $(CSRC:.c=.s)
	$(MSG) RM $(GBAFIX)
	$Q$(RM) $(GBAFIX)
ifeq ($(DATA),1)
	$(MSG) RM data/
	$Q$(RM) -r data
	$(MSG) RM sound/direct_sound_samples
	$Q$(RM) -r sound/direct_sound_samples
endif
	$(MSG) RM \*.ld.pp
	$Q$(RM) *.ld.pp

.PHONY: help
help:
	@echo 'Targets:'
	@echo '  all: build the ROM'
	@echo '  check: checksum the ROM'
	@echo '  check-synthetic: build from a synthetic baserom and compare with mf_us_synthetic.sha1'
	@echo '  check-shift: check for hardcoded ROM addresses and that pointers follow a shifted build'
	@echo '  dump: dump the ROMs'
	@echo '  diff: compare the ROM with the original'
	@echo '  clean: remove the ROM and intermediate files'
	@echo '  	DATA=1: removes the data folder generated by the extractor'
	@echo '  help: show this message'
	@echo ''
	@echo 'Flags:'
	@echo '  V=1: enable verbose output'
	@echo '  REGION=<region>: selects the region of the ROM, possible values are "us", "eu", "jp", "cn", and "eu_beta"'
	@echo '  DEBUG=1: enables the debug code'
	@echo '  SHIFT=1: link a shift test ROM (*_shifted.gba) with SHIFT_AMOUNT (default 0x100) bytes of padding in the code and data'
	@echo '  PROFILE=1|2: non-matching build with a cycle profiler, frame totals or detailed (*_profile.gba, *_profile2.gba)'
	@echo '  OPTIMIZE=1|"NAME ...": non-matching build with performance changes (*_opt.gba)'

$(TARGET): $(ELF)
	$(MSG) OBJCOPY $@
	$Q$(OBJCOPY) -O binary --gap-fill 0xff --pad-to $(PAD_TO) $< $@
	$(MSG) GBAFIX $@
	$Q$(GBAFIX) $@ -t$(GAME_TITLE) -c$(GAME_CODE) -m$(MAKER_CODE) -r$(GAME_REVISION)

$(ELF) $(MAP): $(OBJ) $(LD_SCRIPT)
	$(MSG) LD $@
	$Q$(LD) $(LDFLAGS) -n -T $(LD_SCRIPT) -Map=$(MAP) $(LIBS) -o $@

$(LD_SCRIPT): linker.ld
	$(MSG) CPP $@
	$Q$(CPP) $(CPPFLAGS) $(LD_CPPFLAGS) $< -o $@

ifeq ($(SHIFT),1)
# Always regenerate the shift test linker script, SHIFT_AMOUNT may have changed
$(LD_SCRIPT): FORCE
.PHONY: FORCE
FORCE:
endif

%.dump: %.gba
	$(MSG) OBJDUMP $@
	$Q$(OBJDUMP) -D -bbinary -marm7tdmi -Mforce-thumb  $< | $(TAIL) -n+3 >$@
#--stop-address 0x8c71c
%.o: %.s
	$(MSG) AS $@
	$Q$(AS) $(ASFLAGS) $< -o $@

# The objects of C files depend on the variant flags: switching between the
# normal build and a variant rebuilds them (.build_flags holds the flags of
# the last build)
FLAGS_STAMP = .build_flags
ifneq ($(SETUP_PREREQS),0)
  ifneq ($(strip $(VARIANT_CPPFLAGS)),$(strip $(file <$(FLAGS_STAMP))))
    $(file >$(FLAGS_STAMP),$(strip $(VARIANT_CPPFLAGS)))
  endif
endif
$(CSRC:.c=.s): $(FLAGS_STAMP)
# (there is no header dependency tracking; the variant headers are the exception)
VARIANT_HEADERS = include/profile.h include/optimize.h
$(patsubst %.c,%.s,$(shell grep -l -e '"profile.h"' -e '"optimize.h"' $(CSRC) 2>/dev/null)): $(wildcard $(VARIANT_HEADERS))
$(FLAGS_STAMP):
	$Qtouch -d @0 $@

%.s: %.c
	$(MSG) CC $@
	$Q$(PREPROC) $< $(PREPROCFLAGS) | $(CPP) $(CPPFLAGS) | $(CC) -o $@ $(CFLAGS) && printf '\t.align 2, 0 @ dont insert nops\n' >> $@

src/dma.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
src/dma.s: src/dma.c

src/sram/%.s: CFLAGS = -O1 -mthumb-interwork -fhex-asm
src/sram/%.s: src/sram/%.c

.PHONY: us
# us_debug eu eu_debug eu_beta jp jp_debug cn cn_debug

us:
	$(MAKE) REGION=us
# us_debug:
# 	$(MAKE) REGION=us DEBUG=1

# eu:
# 	$(MAKE) REGION=eu
# eu_debug:
# 	$(MAKE) REGION=eu DEBUG=1
# eu_beta:
# 	$(MAKE) REGION=eu_beta

# jp:
# 	$(MAKE) REGION=jp
# jp_debug:
# 	$(MAKE) REGION=jp DEBUG=1

# cn:
# 	$(MAKE) REGION=cn
# cn_debug:
# 	$(MAKE) REGION=cn DEBUG=1
