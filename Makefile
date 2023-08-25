TARGET = ant2
VERSION = 0.0.1

CPP = clang++
CPP_FLAGS = -O2 -g  -Wall -Wextra -std=c++20 -finline-functions
CPP_LIBS = -lpthread -lncurses

LDFLAGS = 

SRC = src
BUILD = build

SRCS = $(shell find $(SRC_DIR) -type f -name '*.cc')
OBJS = $(patsubst $(SRC)/%.cc, $(BUILD)/%.o, $(SRCS))

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CPP) $(LDFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
