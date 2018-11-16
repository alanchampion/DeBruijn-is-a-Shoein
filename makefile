# To build the program simply type:
#   make
#
# To clean up and remove the compiled binary and other generated files, type:
#   make clean
#
# To build AND run the shell, type:
#   make run
#

# The name of the binary
NAME = shoein

# Flags passed to the preprocessor
CPPFLAGS += -std=c++11

# NVCC compiler
NVCC = nvcc

# ALL .cu files.
SRCS = $(shell find src -name '*.cu')
OBJS = $(SRCS:src/%.cu=bin/%.o)
DEPS = $(SRCS:src/%.cu=bin/%.d)

# Default target
$(NAME): $(OBJS)
	$(NVCC) $(CPPFLAGS) $^ -o $(NAME)

# Build and run the program
run: $(NAME)
	./$(NAME) 

# Remove all generated files.
clean:
	rm -rf $(NAME)* bin/

# Ensure the bin/ directories are created.
$(SRCS): | bin

# Mirror the directory structure of src/ under bin/
bin:
	mkdir -p $(shell find src -type d | sed "s/src/bin/")

# Build objects.
bin/%.o: src/%.cu
	$(NVCC) $(CPPFLAGS) $< -c -o $@

# Auto dependency management.
-include $(DEPS)
