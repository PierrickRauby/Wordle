# the compiler: gcc for C program, define as g++ for C++
CC = c++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
# CFLAGS  = -g -Wall

# The build target 
TARGET = wordle

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC)  -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
