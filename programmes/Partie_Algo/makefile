CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -Llib -Wl,-rpath,'$$ORIGIN/../lib' -lcollections -lsdd -lcunit

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin
TEST_DIR = tests
DOC_DIR = doc

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(TEST_DIR)/test_graphe
DOXYFILE = Doxyfile

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

.PHONY: all clean test doc

all: directories $(TARGET) $(TEST_TARGET) doc

prg: directories $(TARGET)

test: directories $(TEST_TARGET)
	@echo "Exécutable de test généré : $(TEST_TARGET)"

doc: directories $(DOXYFILE)
	doxygen $(DOXYFILE)

$(DOXYFILE):
	@echo "Génération du fichier de configuration Doxygen..."
	doxygen -g
	@echo "Modification du fichier de configuration Doxygen..."
	@sed -i 's|^PROJECT_NAME.*$$|PROJECT_NAME           = "PI-Smart-Robot-315"|' $(DOXYFILE)
	@sed -i 's|^INPUT.*$$|INPUT                  = $(SRC_DIR) $(INCLUDE_DIR)|' $(DOXYFILE)
	@sed -i 's|^RECURSIVE.*$$|RECURSIVE              = YES|' $(DOXYFILE)
	@sed -i 's|^OUTPUT_DIRECTORY.*$$|OUTPUT_DIRECTORY       = $(DOC_DIR)|' $(DOXYFILE)
	@sed -i 's|^GENERATE_LATEX.*$$|GENERATE_LATEX         = YES|' $(DOXYFILE)
	@sed -i 's|^HAVE_DOT.*$$|HAVE_DOT               = YES|' $(DOXYFILE)
	@sed -i 's|^UML_LOOK.*$$|UML_LOOK               = YES|' $(DOXYFILE)
	@sed -i 's|^CALL_GRAPH.*$$|CALL_GRAPH             = YES|' $(DOXYFILE)
	@sed -i 's|^CALLER_GRAPH.*$$|CALLER_GRAPH           = YES|' $(DOXYFILE)
	@sed -i 's|^OPTIMIZE_OUTPUT_FOR_C.*$$|OPTIMIZE_OUTPUT_FOR_C   = YES|' $(DOXYFILE)
	@sed -i 's|^EXTRACT_ALL.*$$|EXTRACT_ALL            = YES|' $(DOXYFILE)
	@sed -i 's|^EXTRACT_PRIVATE.*$$|EXTRACT_PRIVATE         = YES|' $(DOXYFILE)

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
	mkdir -p $(DOC_DIR)

clean:
	rm -rf $(SRC_DIR)/*.o $(TARGET) $(TEST_TARGET)

clean-doc:
	rm -rf $(DOC_DIR)/*

distclean: clean clean-doc
	rm -f $(DOXYFILE)
