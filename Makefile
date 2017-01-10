EXECUTABLE	:=  bin/test_pathing.exe

BIN_DIR		:=  bin
SRC_DIR		:=  src
OBJ_DIR		:=  obj
INC_DIR		:=  include

SRC_FILES   :=  $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES   :=  $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES   :=  $(OBJ_FILES:.o=.d)

#Linker flags
#LDLIBS      :=  -lpng -lstdc++ -lGL -lGLU -lGLEW -lSDLmain -lSDL -lgomp
#LDFLAGS     :=  -L/usr/local/lang/NVIDIA_GPU_Computing_SDK/sdk/C/common/lib/linux/

# Preprocessor flags
# -MMD and -MP handle dependency generation
CPPFLAGS	:=  -MMD -MP -I $(INC_DIR)
# Compiler flags
CXXFLAGS	:=  -Wall -std=c++14

.PHONY: all clean

all:    $(EXECUTABLE)

# Windows doesn't have rm. Damn windows.
cleanwin:
	del /Q $(OBJ_DIR) $(EXECUTABLE)

clean:
	$(RM) -r $(OBJ_DIR) $(EXECUTABLE)

# By default all object files are compiled for the executable. For now, only include ones necessary for testing.
#$(EXECUTABLE):  $(OBJ_FILES)
$(EXECUTABLE):  obj/test_pathing.o | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# .o files are build from the corresponding .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp| $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

# If output directory is missing, create it.
$(OBJ_DIR) $(BIN_DIR):
	mkdir $@

# Causes dependency files to be read in.
ifneq "$(MAKECMDGOALS)" ""
-include $(DEP_FILES)
endif
