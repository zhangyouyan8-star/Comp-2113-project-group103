CC = g++
CFLAGS = -Wall -std=c++11
TARGET = snake_game
SRCS = main.cpp snake.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = snake.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
