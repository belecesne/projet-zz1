FLAGS=-Wall -Wextra -Werror=vla -g -lm
SDL_FLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf
CC = gcc
BUILD_DIR=build
SRC_DIR=src
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
.PHONY: clean all

all : dir snake

dir:
	@if [ ! -d "build" ]; then mkdir $(BUILD_DIR); fi

snake: $(OBJECTS)
	@$(CC) -o $@ $^ $(FLAGS) $(SDL_FLAGS)
	@echo "Executer le programme avec ./snake"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c -o $@ $< $(FLAGS) $(SDL_FLAGS)

clean:
	rm -Rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gch
