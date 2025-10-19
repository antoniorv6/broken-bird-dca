.PHONY := info

GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RED    := \033[1;31m
RESET  := \033[0m

SRC_DIR := src
OBJ_DIR := obj
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEPENDENCIES := -lraylib -lGL -lm -lpthread -lrt -lX11

game:$(OBJECTS)
	g++ -o $@ $^ -L vendor/lib $(DEPENDENCIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "$(YELLOW)🧱 Compilando $< → $@$(RESET)"
	@g++ -o $@ -c $^ -I $(SRC_DIR) -I vendor/include

$(OBJ_DIR):
	mkdir obj

info:
	$(info $(OBJECTS))
	$(info $(SRC))

clean:
	rm -rf obj
	rm -rf dist