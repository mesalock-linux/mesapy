SGX_SDK ?= /opt/intel/sgxsdk
CFLAGS := -O2 -fPIC -Wno-attributes
INCLUDEDIRS := -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include

SRCS := $(wildcard *.c) $(wildcard */*.c)
OBJS := $(sort $(SRCS:.c=.o))

TARGET  := libsgx_tlibc_ext.a

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcsD $@ $^

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDEDIRS) $< -o $@

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(TARGET)
