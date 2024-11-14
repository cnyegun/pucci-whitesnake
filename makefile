# Compiler
CC = clang 

# Source file
SRC = game.c

# Output executable
OUT = run 

# Compiler flags
CFLAGS = -Wall -O2

# Libraries needed for raylib
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Rule to build the executable
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

# Clean rule to remove the executable
clean:
	rm -f $(OUT)

# Phony targets
.PHONY: clean

