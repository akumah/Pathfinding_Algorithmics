BIN_DIR		:=  bin
SRC_DIR		:=  src
OBJ_DIR		:=  obj
INC_DIR		:=  include

EXECUTABLE	:=  $(BIN_DIR)/final_app.txt

SRC_FILES   :=  $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES   :=  $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_FILES   :=  $(OBJ_FILES:.o=.d)

#Linker flags
#LDLIBS      :=  -lpng -lstdc++ -lGL -lGLU -lGLEW -lSDLmain -lSDL -lgomp
LDFLAGS     :=  -g

# Preprocessor flags
# -MMD and -MP handle dependency generation
CPPFLAGS	:=  -MMD -MP -I $(INC_DIR)
# Compiler flags
CXXFLAGS	:=  -Wall -std=c++14 -g

.PHONY: all clean

all:    $(EXECUTABLE)

# Windows doesn't have rm. Damn windows.
cleanwin:
	del /Q $(OBJ_DIR) $(EXECUTABLE)

clean:
	$(RM) -r $(OBJ_DIR) $(EXECUTABLE)

$(EXECUTABLE):  $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR)/test_mesh.exe:  $(OBJ_DIR)/test_mesh.o $(OBJ_DIR)/point2d.o $(OBJ_DIR)/simple_mesh.o | $(BIN_DIR)
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
