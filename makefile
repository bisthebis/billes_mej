OBJ = main.o
LIB = -lsfml-graphics -lsfml-window -lsfml-system -pthread
CFLAGS = -Wall -Wextra -Werror -O2 -std=c++14
CC = g++
TARGET = Programme

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIB) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $<


clean:
	rm *.o

mrproper: clean
	rm Programme
