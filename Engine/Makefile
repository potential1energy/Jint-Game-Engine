CXX_LINUX = g++ -m64
CXX_WINDOWS = x86_64-w64-mingw32-g++
AR = ar rcs

# CFLAGS
CXXFLAGS_LINUX_RELEASE = -O3 -static-libgcc -static-libstdc++
CXXFLAGS_LINUX_DEBUG = -g -O0 -static-libgcc -static-libstdc++
CXXFLAGS_WINDOWS_RELEASE = -O3 -static-libgcc -static-libstdc++
CXXFLAGS_WINDOWS_DEBUG = -g -O0 -static-libgcc -static-libstdc++

# Include directories
INCLUDE_DIRS_GLOBAL = -Ideps/Global/include
INCLUDE_DIRS_LINUX_RELEASE = -Ideps/Linux/include
INCLUDE_DIRS_LINUX_DEBUG = -Ideps/Linux/include
INCLUDE_DIRS_WINDOWS_RELEASE = -Ideps/Windows/include
INCLUDE_DIRS_WINDOWS_DEBUG = -Ideps/Windows/include

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
HDR_DIR = $(SRC_DIR)/headers

# Targets
TARGET_LINUX_RELEASE = $(BIN_DIR)/Linux/x86_64/lib/libJint-Game-Engine_ENGINE_Linux-x86_64.a
TARGET_LINUX_DEBUG = $(BIN_DIR)/Linux/x86_64/lib/libJint-Game-Engine_ENGINE_Linux-x86_64_Debug.a
TARGET_WINDOWS_RELEASE = $(BIN_DIR)/Windows/x86_64/lib/libJint-Game-Engine_ENGINE_Windows-x86_64.a
TARGET_WINDOWS_DEBUG = $(BIN_DIR)/Windows/x86_64/lib/libJint-Game-Engine_ENGINE_Windows-x86_64_Debug.a

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS_LINUX_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Linux/x86_64/Release/%.o, $(SRCS))
OBJS_LINUX_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Linux/x86_64/Debug/%.o, $(SRCS))
OBJS_WINDOWS_RELEASE = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Windows/x86_64/Release/%.o, $(SRCS))
OBJS_WINDOWS_DEBUG = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/Windows/x86_64/Debug/%.o, $(SRCS))

HEADERS := $(shell find $(HDR_DIR) -type f -name '*.*')
CPHEADERS := $(patsubst $(HDR_DIR)/%, $(BIN_DIR)/include/JintGE/%, $(HEADERS))

all: LINUX_RELEASE LINUX_DEBUG WINDOWS_RELEASE WINDOWS_DEBUG

LINUX_RELEASE: $(TARGET_LINUX_RELEASE) $(CPHEADERS)
LINUX_DEBUG: $(TARGET_LINUX_DEBUG) $(CPHEADERS)
WINDOWS_RELEASE: $(TARGET_WINDOWS_RELEASE) $(CPHEADERS)
WINDOWS_DEBUG: $(TARGET_WINDOWS_DEBUG) $(CPHEADERS)

$(BIN_DIR)/include/JintGE/%: $(HDR_DIR)/%
	mkdir -p $(dir $@)
	cp -f $< $@

# Linux release x86_64 build rules

$(TARGET_LINUX_RELEASE): $(OBJS_LINUX_RELEASE)
	@mkdir -p $(dir $@)
	$(AR) $@ $^

$(OBJ_DIR)/Linux/x86_64/Release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_RELEASE) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_LINUX_RELEASE) $(INCLUDE_DIRS_LINUX_RELEASE) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_LINUX_RELEASE:.o=.d)

# Linux debug x86_64 build rules

$(TARGET_LINUX_DEBUG): $(OBJS_LINUX_DEBUG)
	@mkdir -p $(dir $@)
	$(AR) $@ $^

$(OBJ_DIR)/Linux/x86_64/Debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_LINUX) $(CXXFLAGS_LINUX_DEBUG) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_LINUX_DEBUG) $(INCLUDE_DIRS_LINUX_DEBUG) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_LINUX_DEBUG:.o=.d)

# Windows release x86_64 build rules

$(TARGET_WINDOWS_RELEASE): $(OBJS_WINDOWS_RELEASE)
	@mkdir -p $(dir $@)
	$(AR) $@ $^

$(OBJ_DIR)/Windows/x86_64/Release/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_RELEASE) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_WINDOWS_RELEASE) $(INCLUDE_DIRS_WINDOWS_RELEASE) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_WINDOWS_RELEASE:.o=.d)

# Windows debug x86_64 build rules

$(TARGET_WINDOWS_DEBUG): $(OBJS_WINDOWS_DEBUG)
	@mkdir -p $(dir $@)
	$(AR) $@ $^

$(OBJ_DIR)/Windows/x86_64/Debug/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_WINDOWS) $(CXXFLAGS_WINDOWS_DEBUG) $(PREPROCESSOR_DEFINITIONS_GLOBAL) $(PREPROCESSOR_DEFINITIONS_WINDOWS_DEBUG) $(INCLUDE_DIRS_WINDOWS_DEBUG) $(INCLUDE_DIRS_GLOBAL) -MMD -MP -c $< -o $@

-include $(OBJS_WINDOWS_DEBUG:.o=.d)

# Cleanup

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)