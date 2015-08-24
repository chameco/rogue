CC = gcc
SRCS = $(filter-out main.c,$(foreach file,$(wildcard src/*),$(notdir $(file))))
GAME = rogue
BUILD_DIR = build_$(CC)
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

CFLAGS = -Iinclude -std=c99 -g -Wall -Werror

LINKER_FLAGS = -lncurses -lm -lcuttle

vpath %.c src

.PHONY: all directories install uninstall clean

all: directories $(GAME)

directories: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

$(GAME): $(BUILD_DIR)/main.o $(OBJS)
	$(CC) $^ $(LINKER_FLAGS) -o $@

clean:
	rm $(BUILD_DIR)/*.o
	rm dungeons/overworld/*
