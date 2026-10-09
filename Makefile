TARGET := core_dump
CC ?= cc
LDLIBS += -lm
CPPFLAGS += -Isrc/include -D_POSIX_C_SOURCE=200809L
CFLAGS ?= -O3 -g
CFLAGS += -std=c11 -Wall -Wextra -Wpedantic
SOURCES := src/main.c $(wildcard src/modules/*.c)
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean check
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) -r build $(TARGET)

check: $(TARGET)
	./$(TARGET)
	./$(TARGET) -p
	./$(TARGET) --pi
	./$(TARGET) -c
	./$(TARGET) --crc32
	./$(TARGET) -h
	./$(TARGET) --help
	./$(TARGET) -s 1
	./$(TARGET) --sine=2
	! ./$(TARGET) -x
	! ./$(TARGET) --pi extra
	! ./$(TARGET) -s abc

-include $(DEPS)
