#####################################################
# You may need to change the parameters under here. #
#####################################################


CXX=g++

# Set default compiler parameters
# -Wall 	shows all warnings when compiling, always use this!
# -std=c++11 	enables the C++11 standard mode
CXXFLAGS = -Wall -std=c++14

# Step 2: If you use clang++ under Mac OS X, remove these comments
#CXXFLAGS += -stdlib=libc++
#LFLAGS += -stdlib=libc++

# Step 3: Run 'make' in the same directory as this file


############################
# Settings for the library #
############################


# Compiler flag -Idir specifies, that there are includes in the 'dir' directory
LIB_CXXFLAGS = $(CXXFLAGS) -Iinclude

# List of objects for the library
LIBOBJS = obj/test_tstar.o obj/tstar_algo.o

# Name of the library
LIBRARY = lib/libpath.a

################################
# Settings for the testing app #
################################

# Compiler flags for the testing app
APP_CXXFLAGS = $(CXXFLAGS) -Iinclude

# Linker flags (order the compiler to link with our library)
LFLAGS += -Llib -lpath

# The object for the testing app
TESTOBJS = obj/test_tstar.o


# The name of the testing app
TESTAPP = bin/test_tstar.exe

# This is the first target. It will be built when you run 'make' or 'make build'
build: $(LIBRARY) $(TESTAPP)
# Create the library by using 'ar'
$(LIBRARY) : $(LIBOBJS)
	ar cr $(LIBRARY) $(LIBOBJS)

# Compile each source file of the librar
obj/tstar_algo.o: src/tstar_algo.cpp
	$(CXX) $(LIB_CXXFLAGS) -c src/tstar_algo.cpp -o obj/tstar_algo.o

obj/test_tstar.o: src/test_tstar.cpp
	$(CXX) $(APP_CXXFLAGS) -c src/test_tstar.cpp -o obj/test_tstar.o 	

	
# Rule for linking the test app with our library
$(TESTAPP): $(TESTOBJS) $(LIBRARY)
	$(CXX) $(TESTOBJS) -o $(TESTAPP) $(LFLAGS) 
	
# Compile each source file of the library


doc:
	doxygen

clean:
	rm -rf $(LIBOBJS)
	rm -rf $(TESTOBJS)
	rm -rf $(LIBRARY)
	rm -rf $(TESTAPP)
	rm -rf docs