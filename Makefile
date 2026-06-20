# Compilador e flags
CXX       = g++
CXXFLAGS  = -std=c++11 -Wall -Wextra -I include
LDFLAGS   =

# Diretórios
SRC_DIR   = src
INC_DIR   = include
OBJ_DIR   = obj
BIN_DIR   = .

# Nome do executável
TARGET    = $(BIN_DIR)/loja

# Lista automática de fontes e objetos
SRCS      = $(wildcard $(SRC_DIR)/*.cpp)
OBJS      = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Alvo padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação de cada .cpp para .o dentro de obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta obj/ se não existir
$(OBJ_DIR):
	mkdir -p $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Execução (opcional)
run: $(TARGET)
	./$(TARGET)

# Declaração de alvos fictícios
.PHONY: all clean run
