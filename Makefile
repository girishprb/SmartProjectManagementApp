# the compiler: gcc f	or C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#CFLAGS  = -g -Wall -std=c++11
CFLAGS  =  -g -std=c++11

# the build target executable:
TARGET = main

all: $(TARGET)

ActivityNode.o:  ActivityNode.cc ActivityNode.h
	$(CC) $(CFLAGS) -c ActivityNode.cc 

#Utils.o: Utils.h Utils.cc
#	$(CC) $(CFLAGS) -c Utils.cc

SmartProjMgnt.o:  SmartProjMgnt.cc SmartProjMgnt.h ActivityNode.h Utils.h Utils.cc
	$(CC) $(CFLAGS) -c SmartProjMgnt.cc

$(TARGET): SmartProjMgnt.o  ActivityNode.o #Utils.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cc SmartProjMgnt.o  ActivityNode.o #Utils.o

clean:
	$(RM) $(TARGET)
