CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -Llib -lcollections -lsdd -lcunit
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin
TEST_DIR = tests

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(TEST_DIR)/test_CreationGraphe

# Sources pour le programme principal
MAIN_SRC = $(SRC_DIR)/main.c
SOURCES_MAIN = $(SRC_DIR)/graphe.c \
               $(SRC_DIR)/creationGraphe.c \
               $(SRC_DIR)/dijkstra.c \
               $(SRC_DIR)/creationFichierOrdres.c \
               $(MAIN_SRC)

# Sources pour les tests
SOURCES_TEST = $(SRC_DIR)/graphe.c \
               $(SRC_DIR)/creationGraphe.c \
               $(SRC_DIR)/dijkstra.c \
               $(SRC_DIR)/creationFichierOrdres.c \
               $(SRC_DIR)/test_CreationGraphe.c

# Génération des objets
OBJECTS_MAIN = $(SOURCES_MAIN:.c=.o)
OBJECTS_TEST = $(SOURCES_TEST:.c=.o)

.PHONY: all clean test

all: directories $(TARGET)

test: directories $(TEST_TARGET)
	@echo "Exécutable de test généré : $(TEST_TARGET)"

$(TARGET): $(OBJECTS_MAIN)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(OBJECTS_TEST)
	$(CC) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(TEST_DIR)
	mkdir -p $(SRC_DIR)
	mkdir -p $(INCLUDE_DIR)
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)
