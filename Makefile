CXX = g++
CXXFLAGS_RELEASE = -O3 -std=c++20
CXXFLAGS_DEBUG = -g -O0 -std=c++20

INCLUDE_DIRS =
LIB_DIRS =
LIBS = -lGLEW -lGL -lglfw

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET_RELEASE = $(BIN_DIR)/Release/Jint-Game-Engine
TARGET_DEBUG = $(BIN_DIR)/Debug/Jint-Game-Engine

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Release/%.o, $(SRCS))
OBJS_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Debug/%.o, $(SRCS))

all: release

# Release

release: $(TARGET_RELEASE)

$(TARGET_RELEASE): $(OBJS_RELEASE)
	@mkdir -p $(BIN_DIR)/Release
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $^ $(LIB_DIRS) $(LIBS)

$(OBJ_DIR)/Release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/Release
	$(CXX) $(CXXFLAGS_RELEASE) $(INCLUDE_DIRS) -MMD -MP -c $< -o $@

-include $(OBJS_RELEASE:.o=.d)

# Debug

debug: $(TARGET_DEBUG)

$(TARGET_DEBUG): $(OBJS_DEBUG)
	@mkdir -p $(BIN_DIR)/Debug
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^ $(LIB_DIRS) $(LIBS)

$(OBJ_DIR)/Debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)/Debug
	$(CXX) $(CXXFLAGS_DEBUG) $(INCLUDE_DIRS) -MMD -MP -c $< -o $@

-include $(OBJS_DEBUG:.o=.d)

# Cleanup

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean