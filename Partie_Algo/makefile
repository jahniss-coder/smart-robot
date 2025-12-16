CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -Llib -Wl,-rpath,'$$ORIGIN/../lib' -lcollections -lsdd -lcunit

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin
TEST_DIR = tests

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(TEST_DIR)/test_graphe

# Sources pour le programme principal
MAIN_SRC = $(SRC_DIR)/main.c
SOURCES_MAIN = $(SRC_DIR)/graphe.c \
               $(SRC_DIR)/graphe_dijkstra.c \
               $(SRC_DIR)/creationFichierOrdres.c \
               $(SRC_DIR)/file.c \
               $(SRC_DIR)/TAD_robot.c \
               $(SRC_DIR)/chemin.c \
               $(MAIN_SRC)

# Sources pour les tests
SOURCES_TEST = $(SRC_DIR)/graphe.c \
               $(SRC_DIR)/graphe_dijkstra.c \
               $(SRC_DIR)/creationFichierOrdres.c \
               $(SRC_DIR)/file.c \
               $(SRC_DIR)/TAD_robot.c \
               $(SRC_DIR)/chemin.c \
               $(SRC_DIR)/test_graphe.c

# Génération des objets
OBJECTS_MAIN = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SOURCES_MAIN))
OBJECTS_TEST = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SOURCES_TEST))

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
