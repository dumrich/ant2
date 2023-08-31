TARGET = ant2
VERSION = 0.0.1

CPP = clang++
CPP_FLAGS = -O2 -g  -Wall -Wextra -std=c++20 -finline-functions
CPP_LIBS = -lpthread -lncurses

LDFLAGS = 

SRC = src
BUILD = build

SRCS = $(shell find $(SRC) -type f -name '*.cc')
OBJS = $(patsubst $(SRC)/%.cc, $(BUILD)/%.o, $(SRCS))

all: $(TARGET)

$(BUILD)/%.o: $(SRC)/%.cc | $(BUILD)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CPP) $(LDFLAGS) $^ -o $@

$(BUILD):
	mkdir -p $(BUILD)

.PHONY: all clean
clean:
	rm -rf $(BUILD) $(TARGET)
