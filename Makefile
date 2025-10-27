.PHONY := all clean info clean-cache dev-deps install uninstall dist

# 🎨 Colores
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
RED := \033[1;31m
RESET := \033[0m

# Configuración de rutas
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
DIST_DIR := dist
LIB_DIR := vendor/lib/
RAYLIB := libraylib.a
RAYLIB_DEP := $(addprefix $(LIB_DIR),$(RAYLIB))

# Variables de instalación
PREFIX ?= /usr/local
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib/$(APP_NAME)
DATADIR := $(PREFIX)/share/$(APP_NAME)
INSTALL := install
INSTALL_PROGRAM := $(INSTALL) -m 0755
INSTALL_DATA := $(INSTALL) -m 0644
INSTALL_DIR := $(INSTALL) -d
APP_NAME ?= game
ASSETS_DIR := assets

# Buscar todos los .cpp recursivamente dentro de src/
SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Generar los .o correspondientes en obj/ con la misma estructura
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Dependencias de enlace
DEPENDENCIES := -lraylib -lGL -lm -lpthread -lrt -lX11

# Incluir automáticamente todos los subdirectorios de src/
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_VENDORS := $(shell find vendor/include -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) $(addprefix -I,$(INC_VENDORS))

# =====================================
# Objetivo principal
# =====================================
all: $(RAYLIB_DEP) $(BIN_DIR)/game

$(BIN_DIR)/game: $(OBJECTS)
	@echo "$(BLUE)🔗 Enlazando objetos...$(RESET)"
	@mkdir -p $(BIN_DIR)
	@ccache g++ -o $@ $^ -L $(LIB_DIR) $(DEPENDENCIES)
	@echo "$(GREEN)✅ Ejecutable generado: $(BIN_DIR)/game$(RESET)"

# =====================================
# 🧱 Regla de compilación
# =====================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(YELLOW)🧱 Compilando $< → $@$(RESET)"
	@mkdir -p $(dir $@)
	@ccache g++ -c $^ -o $@ $(INC_FLAGS)

# =====================================
# Instalación
# =====================================
install: $(BIN_DIR)/game
	@echo "$(BLUE)📦 Instalando binario en $(DESTDIR)$(LIBDIR)...$(RESET)"
	$(INSTALL_DIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL_PROGRAM) $(BIN_DIR)/game $(DESTDIR)$(LIBDIR)/$(APP_NAME).bin
	@echo "$(BLUE)📦 Creando wrapper script en $(DESTDIR)$(BINDIR)...$(RESET)"
	$(INSTALL_DIR) $(DESTDIR)$(BINDIR)
	@printf '#!/bin/sh\ncd $(DATADIR) || exit 1\nexec $(LIBDIR)/$(APP_NAME).bin "$@"\n' > $(DESTDIR)$(BINDIR)/$(APP_NAME)
	@chmod 0755 $(DESTDIR)$(BINDIR)/$(APP_NAME)
	@echo "$(BLUE)📦 Instalando assets en $(DESTDIR)$(DATADIR)/assets...$(RESET)"
	$(INSTALL_DIR) $(DESTDIR)$(DATADIR)/assets
	@if [ -d "$(ASSETS_DIR)" ]; then \
		cp -r $(ASSETS_DIR)/* $(DESTDIR)$(DATADIR)/assets/; \
		find $(DESTDIR)$(DATADIR)/assets -type f -exec chmod 0644 {} \;; \
		find $(DESTDIR)$(DATADIR)/assets -type d -exec chmod 0755 {} \;; \
		echo "$(GREEN)✅ Assets instalados correctamente.$(RESET)"; \
	else \
		echo "$(YELLOW)⚠️  No se encontró la carpeta de assets.$(RESET)"; \
	fi
	@echo "$(GREEN)✅ Instalación completada.$(RESET)"

# =====================================
# Desinstalación
# =====================================
uninstall:
	@echo "$(RED)🗑️ Desinstalando $(DESTDIR)$(BINDIR)/$(APP_NAME)...$(RESET)"
	@rm -f $(DESTDIR)$(BINDIR)/$(APP_NAME)
	@echo "$(RED)🗑️ Eliminando binario de $(DESTDIR)$(LIBDIR)...$(RESET)"
	@rm -rf $(DESTDIR)$(LIBDIR)
	@echo "$(RED)🗑️ Eliminando assets de $(DESTDIR)$(DATADIR)...$(RESET)"
	@rm -rf $(DESTDIR)$(DATADIR)
	@echo "$(GREEN)✅ Desinstalación completada.$(RESET)"

# =====================================
# Limpieza
# =====================================
clean:
	@echo "$(RED)🧹 Limpiando...$(RESET)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(GREEN)✅ Limpieza completada.$(RESET)"

# =====================================
# Información
# =====================================
info:
	$(info SRC = $(SRC))
	$(info OBJECTS = $(OBJECTS))
	$(info INC_FLAGS = $(INC_FLAGS))
	$(info LIB_DEPS = $(LIB_DEP))
	$(info RAYLIB= $(RAYLIB_DEP))

dist:
	@echo "$(BLUE)📦 Generando distribución debian en $(DIST_DIR)...$(RESET)"
	@dpkg-buildpackage -us -uc -b
	@mkdir -p $(DIST_DIR)
	@mv ../*.deb $(DIST_DIR)/ 2>/dev/null || true
	@mv ../*.buildinfo $(DIST_DIR)/ 2>/dev/null || true
	@mv ../*.changes $(DIST_DIR)/ 2>/dev/null || true
	@echo "$(GREEN)✅ Paquete en $(DIST_DIR)/$(RESET)"
	@ls -lh $(DIST_DIR)/*.deb

clean-cache:
	ccache -C
	ccache --zero-stats

$(RAYLIB_DEP): | $(LIB_DEP)
	@if [ ! -f "$(RAYLIB_DEP)" ]; then \
		echo "$(YELLOW)🧱 Raylib no está instalada. Descargando...$(RESET)"; \
		git clone --depth 1 https://github.com/raysan5/raylib.git; \
		$(MAKE) -C raylib/src/ PLATFORM=PLATFORM_DESKTOP; \
		mkdir -p $(LIB_DIR); \
		mv raylib/src/libraylib.a $(LIB_DIR)/; \
		rm -rf raylib; \
		echo "$(GREEN)✅ Raylib instalada correctamente.$(RESET)"; \
	else \
		echo "$(GREEN)✅ Raylib ya instalada. Omitiendo descarga.$(RESET)"; \
	fi

$(LIB_DEP):
	mkdir -p vendor/lib