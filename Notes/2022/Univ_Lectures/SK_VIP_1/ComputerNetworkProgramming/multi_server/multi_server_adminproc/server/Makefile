CC = gcc
CFLAGS =
INCLUDE = -Iinclude/
SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = ./bin/server

# $(notdir names...) $(wildcard pattern)
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c)) 
OBJS = $(SRCS:.c=.o)

# $(patsubst pattern,replacement,text)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))  
DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -MD

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET) core

-include $(DEPS)