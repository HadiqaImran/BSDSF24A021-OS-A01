CC = gcc
AR = ar
CFLAGS = -Wall -I../include
OBJ_DIR = ../obj
BIN_DIR = ../bin
LIB_DIR = ../lib

LIBRARY_STATIC = $(LIB_DIR)/libmyutils.a
LIBRARY_SHARED = $(LIB_DIR)/libmyutils.so
TARGET_STATIC = $(BIN_DIR)/client_static
TARGET_DYNAMIC = $(BIN_DIR)/client_dynamic

LIB_SOURCES = mystrfunctions.c myfilefunctions.c
LIB_OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SOURCES))
LIB_OBJECTS_PIC = $(patsubst %.c,$(OBJ_DIR)/%_pic.o,$(LIB_SOURCES))
MAIN_OBJECT = $(OBJ_DIR)/main.o

all: $(TARGET_STATIC) $(TARGET_DYNAMIC)

$(LIBRARY_STATIC): $(LIB_OBJECTS)
	$(AR) rcs $(LIBRARY_STATIC) $(LIB_OBJECTS)

$(LIBRARY_SHARED): $(LIB_OBJECTS_PIC)
	$(CC) --shared $(LIB_OBJECTS_PIC) -o $(LIBRARY_SHARED)

$(TARGET_STATIC): $(MAIN_OBJECT) $(LIBRARY_STATIC)
	$(CC) $(MAIN_OBJECT) -L$(LIB_DIR) -lmyutils -o $(TARGET_STATIC)

$(TARGET_DYNAMIC): $(MAIN_OBJECT) $(LIBRARY_SHARED)
	$(CC) $(MAIN_OBJECT) -L$(LIB_DIR) -lmyutils -o $(TARGET_DYNAMIC)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%_pic.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_STATIC) $(TARGET_DYNAMIC) $(LIBRARY_STATIC) $(LIBRARY_SHARED)

.PHONY: all clean
