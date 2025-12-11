CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -Llib -lcollections -lsdd -lcunit
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin
TEST_DIR = tests

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(TEST_DIR)/test_graphe

MAIN_SRC = $(SRC_DIR)/main.c
SOURCES = $(SRC_DIR)/graphe.c $(SRC_DIR)/creationGraphe.c $(MAIN_SRC)
TEST_SOURCES = $(SRC_DIR)/graphe.c $(SRC_DIR)/creationGraphe.c $(SRC_DIR)/test_graphe.c

OBJECTS = $(SRC_DIR)/graphe.o $(SRC_DIR)/creationGraphe.o $(SRC_DIR)/main.o
TEST_OBJECTS = $(SRC_DIR)/graphe.o $(SRC_DIR)/creationGraphe.o $(SRC_DIR)/test_graphe.o

.PHONY: all clean test run_test

all: directories $(TARGET)

test: directories $(TEST_TARGET)
	@echo "Exécutable de test généré : $(TEST_TARGET)"

run_test: $(TEST_TARGET)
	@echo "Exécution des tests..."
	@$(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS)
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
