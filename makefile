#*******************************************************************************
#	Filename: 	makefile
#	Programmer: Gideon Walker
#	Class:		CS 5201 - Prof. Price
#	Assignment: Final Project
#	Due: 		
#
#	Description:
#		A makefile to compile pretty much any C++ project.
#*******************************************************************************

.PHONY: all clean

CXX = g++-7
CXXFLAGS = -Wpedantic -Wall -Wextra -Wfloat-conversion -Werror

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

OBJECTS = $(SOURCES:%.cpp=%.o)

default: driver

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

driver: $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f depend
	-@rm -f $(OBJECTS)

depend: $(SOURCES) $(HEADERS)
	@$(CXX) -MM *.cpp > $@

-include depend
