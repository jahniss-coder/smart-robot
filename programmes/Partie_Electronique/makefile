CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -Llib -Wl,-rpath,'$$ORIGIN/../lib' -lwiringPi -lwiringPiDev -lpthread

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib
BIN_DIR = bin

TARGET = $(BIN_DIR)/main_robot

# Sources pour le programme principal
MAIN_SRC = $(SRC_DIR)/main_robot.c
SOURCES_MAIN = $(SRC_DIR)/affichage.c \
               $(SRC_DIR)/actions.c \
               $(SRC_DIR)/buzzer.c \
               $(SRC_DIR)/capteurs.c \
               $(SRC_DIR)/configuration_GPIO.c \
               $(SRC_DIR)/detections.c \
               $(SRC_DIR)/moteur.c \
               $(MAIN_SRC)

# Génération des objets
OBJECTS_MAIN = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SOURCES_MAIN))

.PHONY: all clean

all: directories $(TARGET)

$(TARGET): $(OBJECTS_MAIN)
	$(CC) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(SRC_DIR)
	mkdir -p $(INCLUDE_DIR)
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(SRC_DIR)/*.o $(TARGET)
