CC = gcc
CFLAGS = -Wall -g

SRC = bst.c float_rndm.c iom361_r2.c main.c test_bst.c

HEADERS = bst.h float_rndm.h iom361_r2.h

OBJ = $(SRC:.c=.o)

TARGET = bst_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

Debug: all
