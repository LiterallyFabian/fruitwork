# The game project
PROJECT_DIR = ../project
PROJECT_METADATA_FILE = $(PROJECT_DIR)/metadata.res

# Executable name and build directory
OBJ_NAME = yuzu!catch
BUILD_DIR = ../build/${OBJ_NAME}

# The fruitwork engine
FRUITWORK_DIR = .

# Compiler (g++/g++-12/c++/c++-12 depending on installation)
CC = g++

# Compiler flags
# -Wno-unknown-pragmas - some valid pragmas are not recognized by the compiler
# -Wno-sign-compare - bad practice to disable but whatever
COMPILER_FLAGS = -std=c++17 -Wall -Wno-unknown-pragmas -O0 -g -Wno-sign-compare

# All source files found in fruitwork and project directories
SRC_FILES = $(wildcard $(PROJECT_DIR)/src/*.cpp) $(wildcard $(FRUITWORK_DIR)/src/*.cpp)
SRC_FILES += $(wildcard $(PROJECT_DIR)/lib/*/*.cpp) $(wildcard $(FRUITWORK_DIR)/lib/*/*.cpp)

# Include paths (SDL2, engine, project)
INCLUDE_PATHS = -Iinclude -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/SDL2
INCLUDE_PATHS += -I$(FRUITWORK_DIR)/include -I$(PROJECT_DIR)/include
INCLUDE_PATHS += -I$(FRUITWORK_DIR)/lib

# Library paths
LIBRARY_PATHS = -Llib -LC:/msys64/mingw64/lib

# Linker flags
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: $(BUILD_DIR)/$(OBJ_NAME) copy_resources

$(BUILD_DIR)/$(OBJ_NAME): $(SRC_FILES) create_build_dir
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $@ ${PROJECT_METADATA_FILE}

# Copies resources from project & engine to build directory
copy_resources:
	if exist "$(FRUITWORK_DIR)\resources" xcopy /s /e /y /i /q "$(FRUITWORK_DIR)\resources" "$(BUILD_DIR)\resources"
	if exist "$(PROJECT_DIR)\resources" xcopy /s /e /y /i /q "$(PROJECT_DIR)\resources" "$(BUILD_DIR)\resources"

create_build_dir:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"