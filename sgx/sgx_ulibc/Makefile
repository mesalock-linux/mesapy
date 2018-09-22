CFLAGS := -O2 -fPIC -Wno-attributes

SRCS := $(wildcard *.c)
OBJS := $(sort $(SRCS:.c=.o))

TARGET  := libsgx_ulibc.a

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcsD $@ $^

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@$(RM) $(OBJS) $(TARGET)
