CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRC_DIR = Terminal_game

TARGET = terminal_game.exe

ifeq ($(OS),Windows_NT)
    RM_CMD = del /Q /F
    DEV_NULL = >nul 2>&1
else
    TARGET = terminal_game
    RM_CMD = rm -f
    DEV_NULL = >/dev/null 2>&1
endif

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRCS))

CXXFLAGS += -I$(SRC_DIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	$(RM_CMD) $(OBJS) $(DEV_NULL)

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM_CMD) $(TARGET) $(OBJS) $(DEV_NULL)

.PHONY: all clean