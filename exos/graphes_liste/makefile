FLAGS=-Wall -Wextra -Werror=vla -g
CC = gcc
BUILD_DIR=build
SRC_DIR=src
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
.PHONY: clean all

all : dir graphe

dir:
	@if [ ! -d "build" ]; then mkdir $(BUILD_DIR); fi

graphe: $(OBJECTS)
	@$(CC) -o $@ $^ $(FLAGS)
	@echo "Executer le programme avec ./graphe"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c -o $@ $< $(FLAGS)

clean:
	rm -Rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.gch
