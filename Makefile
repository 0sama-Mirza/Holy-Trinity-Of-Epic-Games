# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion

# Source files directory
SRCDIR = src

# Object files directory
OBJDIR = objs

# Build directory
BUILDDIR = Build

# Executable name
EXEC = $(BUILDDIR)/HTEG

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Rule to create the object files directory if it doesn't exist
$(shell mkdir -p $(OBJDIR) $(BUILDDIR))

# Rule to compile .cpp files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executable created: $@"

# Rule to move the executable to the Build directory
move_executable:
	mv $(EXEC) $(BUILDDIR)/

# Rule to build the project (default rule)
build: $(EXEC) move_executable

# Rule to clean object files
clean:
	@echo "Cleaning object files"
	rm -rf $(OBJDIR)

# Phony targets to avoid conflicts with filenames
.PHONY: build clean move_executable
