CC = gcc
AR = ar
CFLAGS = -Wall -I../include
OBJ_DIR = ../obj
BIN_DIR = ../bin
LIB_DIR = ../lib

LIBRARY = $(LIB_DIR)/libmyutils.a
TARGET_STATIC = $(BIN_DIR)/client_static

LIB_SOURCES = mystrfunctions.c myfilefunctions.c
LIB_OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SOURCES))
MAIN_OBJECT = $(OBJ_DIR)/main.o

all: $(TARGET_STATIC)

$(LIBRARY): $(LIB_OBJECTS)
	$(AR) rcs $(LIBRARY) $(LIB_OBJECTS)

$(TARGET_STATIC): $(MAIN_OBJECT) $(LIBRARY)
	$(CC) $(MAIN_OBJECT) -L$(LIB_DIR) -lmyutils -o $(TARGET_STATIC)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_STATIC) $(LIBRARY)

.PHONY: all clean
