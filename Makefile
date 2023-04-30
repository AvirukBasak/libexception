# Compiler and flags
CC            := gcc # -Xanalyzer
CFLAGS        := -Wall -Wextra -std=c99 -fsanitize=address -g
CRELFLAGS     := -Wall -Wextra -std=c99 -O2

# Directories
INC_DIR       := include
SRC_DIR       := src
LIB_DIR       := lib
OBJ_DIR       := obj
BIN_DIR       := bin

INCLUDES      := -I$(INC_DIR)

# Libraries
LIBS          := -L$(LIB_DIR)

# Static library
TARGET        := $(BIN_DIR)/libexception

# Sources and objects
TARGET_SRC    := $(wildcard $(SRC_DIR)/*.c)
TARGET_OBJ    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(TARGET_SRC))

# Targets
.PHONY: all release clean

all: $(TARGET)

release: CFLAGS := $(CRELFLAGS) $(TARGET)

# Main code

$(TARGET): directories $(TARGET_OBJ)
	ar rcs $(TARGET) $(TARGET_OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Testing
test/test: $(TARGET)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o test/test.out test/test.c $(TARGET_OBJ) # -L$(BIN_DIR) -lexception

test: test/test
	@ASAN_OPTIONS=detect_leaks=1 ./test/test.out

# Supporting code

directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(OBJ_DIR)

# Library specific code
