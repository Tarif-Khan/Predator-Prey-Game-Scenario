CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lncurses

SRCS = main.cpp critter.cpp ant.cpp queen.cpp doodlebug.cpp grid.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
