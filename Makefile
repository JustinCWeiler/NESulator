BIN = main
TEST = test_cpu_basic
BUILD_DIR = build

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Og -Iinclude
LDFLAGS = 
LDLIBS = -lSDL2

# automatic object bois
# space separated list of $(BUILD_DIR)/%.o for each %.c in src/lib
OBJECTS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(notdir $(wildcard src/lib/*.c))))
# find %.c in any dir in src
vpath %.c $(wildcard src/*) src

.PHONY: all run clean
.PRECIOUS: $(BUILD_DIR)/%.o
.SILENT: run test

all: $(BUILD_DIR)/$(BIN) $(BUILD_DIR)/$(TEST)
run: $(BUILD_DIR)/$(BIN)
	echo
	$<
test: $(BUILD_DIR)/$(TEST)
	echo
	$<
clean: $(BUILD_DIR)
	rm -r $(BUILD_DIR)


$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

%: $(BUILD_DIR)/%
%.o: $(BUILD_DIR)/%.o
