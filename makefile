CC = g++
CFLAGS = -Wall -g -Wpedantic -std=c++17 -Wshadow


SRCS = main.cpp genotype.cpp
OBJ = $(SRCS:.cpp=.o)

TARGET = main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)


%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)