FLAGS=-Wall -Wextra -Wdeclaration-after-statement -Werror=vla -g
SDL_FLAGS=-lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
CC = gcc
BUILD_DIR=build
SRC_DIR=src
RAPPORT_DIR=rapport
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
.PHONY: clean all rapport

all : dir game

dir:
	@if [ ! -d "build" ]; then mkdir $(BUILD_DIR); fi

game: $(OBJECTS)
	@$(CC) -o $@ $^ $(FLAGS) $(SDL_FLAGS)
	@echo "Executer le programme avec ./game"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c -o $@ $< $(FLAGS) $(SDL_FLAGS)

clean:
	rm -Rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gch
