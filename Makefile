CC = gcc
SRCS = $(filter-out main.c,$(foreach file,$(wildcard src/*),$(notdir $(file))))
GAME = rogue
BUILD_DIR = build_$(CC)
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = cp -r

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(prefix)/bin
datarootdir = $(prefix)/share
datadir = $(datarootdir)
libdir = $(exec_prefix)/lib

CFLAGS_gcc = -Iinclude -std=c99 -g -Wall -Werror `pkg-config guile-2.0 --cflags`
CFLAGS = $(CFLAGS_$(CC))
LINKER_FLAGS_gcc = -lncurses -lm -lcuttle `pkg-config guile-2.0 --libs` -lGLEW -lSDL2 -lGL -lGLU -lSDL2_image -lSDL2_mixer
LINKER_FLAGS = $(LINKER_FLAGS_$(CC))

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
