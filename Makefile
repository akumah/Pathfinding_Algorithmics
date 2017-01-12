BIN_DIR		:=  bin
SRC_DIR		:=  src
OBJ_DIR		:=  obj
INC_DIR		:=  include

vpath %.o $(OBJ_DIR)

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
CXXFLAGS	:=  -Wall -Wextra -std=c++14 -g

.PHONY: all clean

all:    $(EXECUTABLE)

# Windows doesn't have rm. Damn windows.
cleanwin:
	rd /S /Q $(OBJ_DIR) $(BIN_DIR)

clean:
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)

$(EXECUTABLE):  $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR)/test_simple_mesh.exe:  test_simple_mesh.o point2d.o simple_mesh.o | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR)/test_jump_mesh.exe:  test_jump_mesh.o point2d.o simple_mesh.o jump_mesh.o | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR)/test_tstar.exe:  Test_tstar.o tstar_algo.o simple_mesh.o point2d.o | $(BIN_DIR)
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
