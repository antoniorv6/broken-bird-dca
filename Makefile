.PHONY := all clean info clean-cache dev-deps

# 🎨 Colores
GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RED    := \033[1;31m
RESET  := \033[0m

# ⚙️ Configuración de rutas
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := dist
LIB_DEP := vendor/lib

# 🔍 Buscar todos los .cpp recursivamente dentro de src/
SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# 🧱 Generar los .o correspondientes en obj/ con la misma estructura
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# ⚙️ Dependencias de enlace
DEPENDENCIES := -lraylib -lGL -lm -lpthread -lrt -lX11

# 📁 Incluir automáticamente todos los subdirectorios de src/
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_VENDORS := $(shell find vendor/include -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(addprefix -I,$(INC_VENDORS))

# =====================================
# 🎯 Objetivo principal
# =====================================
all: $(BIN_DIR)/game

$(BIN_DIR)/game: $(OBJECTS)
	@echo "$(BLUE)🔗 Enlazando objetos...$(RESET)"
	@mkdir -p $(BIN_DIR)
	@ccache g++ -o $@ $^ -L $(LIB_DEP) $(DEPENDENCIES)
	@echo "$(GREEN)✅ Ejecutable generado: $(BIN_DIR)/game$(RESET)"

# =====================================
# 🧱 Regla de compilación
# =====================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(YELLOW)🧱 Compilando $< → $@$(RESET)"
	@mkdir -p $(dir $@)
	@ccache g++ -c $^ -o $@ $(INC_FLAGS)

# =====================================
# 🧹 Limpieza
# =====================================
clean:
	@echo "$(RED)🧹 Limpiando...$(RESET)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(GREEN)✅ Limpieza completada.$(RESET)"

# =====================================
# 🧾 Información
# =====================================
info:
	$(info SRC = $(SRC))
	$(info OBJECTS = $(OBJECTS))
	$(info INC_FLAGS = $(INC_FLAGS))

clean-cache:
	ccache -C
	ccache --zero-stats

dev-deps: | $(LIB_DEP)
	git clone --depth 1 https://github.com/raysan5/raylib.git
	$(MAKE) -C raylib/src/ PLATFORM=PLATFORM_DESKTOP
	mv raylib/src/libraylib.a vendor/lib/
	rm -rf raylib

$(LIB_DEP):
	mkdir -p vendor/lib


