CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OUT_DIR = output
SVG_OUT = $(OUT_DIR)/svg

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = $(OUT_DIR)/programa

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(SVG_OUT)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(OUT_DIR)/*.exe $(OUT_DIR)/programa
	rm -rf *.html

.PHONY: all clean run
