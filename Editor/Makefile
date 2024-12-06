CXX_LINUX = g++ -m64
CXX_WINDOWS = x86_64-w64-mingw32-g++

# CFLAGS
CXXFLAGS_LINUX_RELEASE = -O3 -static-libgcc -static-libstdc++
CXXFLAGS_LINUX_DEBUG = -g -O0 -static-libgcc -static-libstdc++
CXXFLAGS_WINDOWS_RELEASE = -O3 -static-libgcc -static-libstdc++
CXXFLAGS_WINDOWS_DEBUG = -g -O0 -static-libgcc -static-libstdc++

# Include directories
INCLUDE_DIRS_GLOBAL = -Ideps/Global/include -I../Engine/bin/include/JintGE
INCLUDE_DIRS_LINUX_RELEASE = -Ideps/Linux/include
INCLUDE_DIRS_LINUX_DEBUG = -Ideps/Linux/include
INCLUDE_DIRS_WINDOWS_RELEASE = -Ideps/Windows/include
INCLUDE_DIRS_WINDOWS_DEBUG = -Ideps/Windows/include

# Library directories
LIB_DIRS_GLOBAL = -Ldeps/Global/lib
LIB_DIRS_LINUX_RELEASE = -Ldeps/Linux/lib -L../Engine/bin/Linux/x86_64/lib
LIB_DIRS_LINUX_DEBUG = -Ldeps/Linux/lib -L../Engine/bin/Linux/x86_64/lib
LIB_DIRS_WINDOWS_RELEASE = -Ldeps/Windows/lib -L../Engine/bin/Windows/x86_64/lib
LIB_DIRS_WINDOWS_DEBUG = -Ldeps/Windows/lib -L../Engine/bin/Windows/x86_64/lib

# Libraries
LIBS_GLOBAL =
LIBS_LINUX_RELEASE = -lJint-Game-Engine_ENGINE_Linux-x86_64 -lX11 -lglad -lGL -lGLX
LIBS_LINUX_DEBUG = -lJint-Game-Engine_ENGINE_Linux-x86_64_Debug -lX11 -lglad -lGL -lGLX
LIBS_WINDOWS_RELEASE = -lJint-Game-Engine_ENGINE_Windows-x86_64
LIBS_WINDOWS_DEBUG = -lJint-Game-Engine_ENGINE_Windows-x86_64_Debug

# Preprocessor definitions
PREPROCESSOR_DEFINITIONS_GLOBAL =
PREPROCESSOR_DEFINITIONS_LINUX_RELEASE =
PREPROCESSOR_DEFINITIONS_LINUX_DEBUG =
PREPROCESSOR_DEFINITIONS_WINDOWS_RELEASE =
PREPROCESSOR_DEFINITIONS_WINDOWS_DEBUG =

# Build directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Targets
TARGET_LINUX_RELEASE = $(BIN_DIR)/Linux/x86_64/Release/Jint-Game-Engine_EDITOR_Linux-x86_64
TARGET_LINUX_DEBUG = $(BIN_DIR)/Linux/x86_64/Debug/Jint-Game-Engine_EDITOR_Linux-x86_64_Debug
TARGET_WINDOWS_RELEASE = $(BIN_DIR)/Windows/x86_64/Release/Jint-Game-Engine_EDITOR_Windows-x86_64.exe
TARGET_WINDOWS_DEBUG = $(BIN_DIR)/Windows/x86_64/Debug/Jint-Game-Engine_EDITOR_Windows-x86_64_Debug.exe

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS_LINUX_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Linux/x86_64/Release/%.o, $(SRCS))
OBJS_LINUX_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Linux/x86_64/Debug/%.o, $(SRCS))
OBJS_WINDOWS_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Windows/x86_64/Release/%.o, $(SRCS))
OBJS_WINDOWS_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Windows/x86_64/Debug/%.o, $(SRCS))

all: LINUX_RELEASE LINUX_DEBUG WINDOWS_RELEASE WINDOWS_DEBUG

LINUX_RELEASE: $(TARGET_LINUX_RELEASE)
LINUX_DEBUG: $(TARGET_LINUX_DEBUG)
WINDOWS_RELEASE: $(TARGET_WINDOWS_RELEASE)
WINDOWS_DEBUG: $(TARGET_WINDOWS_DEBUG)

# Linux release x86_64 build rules

$(TARGET_LINUX_RELEASE): $(OBJS_LINUX_RELEASE) ../Engine/bin/Linux/x86_64/lib/libJint-Game-Engine_ENGINE_Linux-x86_64.a
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_RELEASE) -o $@ $^ $(LIB_DIRS_LINUX_RELEASE) $(LIBS_LINUX_RELEASE) $(LIB_DIRS_GLOBAL) $(LIBS_GLOBAL)

$(OBJ_DIR)/Linux/x86_64/Release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_RELEASE) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_LINUX_RELEASE) $(INCLUDE_DIRS_LINUX_RELEASE) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_LINUX_RELEASE:.o=.d)

# Linux debug x86_64 build rules

$(TARGET_LINUX_DEBUG): $(OBJS_LINUX_DEBUG) ../Engine/bin/Linux/x86_64/lib/libJint-Game-Engine_ENGINE_Linux-x86_64_Debug.a
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_DEBUG) -o $@ $^ $(LIB_DIRS_LINUX_DEBUG) $(LIBS_LINUX_DEBUG) $(LIB_DIRS_GLOBAL) $(LIBS_GLOBAL)

$(OBJ_DIR)/Linux/x86_64/Debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_DEBUG) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_LINUX_DEBUG) $(INCLUDE_DIRS_LINUX_DEBUG) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_LINUX_DEBUG:.o=.d)

# Windows release x86_64 build rules

$(TARGET_WINDOWS_RELEASE): $(OBJS_WINDOWS_RELEASE) ../Engine/bin/Windows/x86_64/lib/libJint-Game-Engine_ENGINE_Windows-x86_64.a
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_RELEASE) -o $@ $^ $(LIB_DIRS_WINDOWS_RELEASE) $(LIBS_WINDOWS_RELEASE) $(LIB_DIRS_GLOBAL) $(LIBS_GLOBAL)

$(OBJ_DIR)/Windows/x86_64/Release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_RELEASE) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_WINDOWS_RELEASE) $(INCLUDE_DIRS_WINDOWS_RELEASE) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_WINDOWS_RELEASE:.o=.d)

# Windows debug x86_64 build rules

$(TARGET_WINDOWS_DEBUG): $(OBJS_WINDOWS_DEBUG) ../Engine/bin/Windows/x86_64/lib/libJint-Game-Engine_ENGINE_Windows-x86_64_Debug.a
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_DEBUG) -o $@ $^ $(LIB_DIRS_WINDOWS_DEBUG) $(LIBS_WINDOWS_DEBUG) $(LIB_DIRS_GLOBAL) $(LIBS_GLOBAL)

$(OBJ_DIR)/Windows/x86_64/Debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_DEBUG) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_WINDOWS_DEBUG) $(INCLUDE_DIRS_WINDOWS_DEBUG) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_WINDOWS_DEBUG:.o=.d)

# Cleanup

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)