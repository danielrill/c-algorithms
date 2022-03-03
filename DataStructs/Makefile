#
#
# Makefile
#
#

CXX = g++
CXXFLAGS = -g -Wall -std=c++11

TARGET = test

HEADER = myArray.h \
                  mySharedPtr.h \
                  linked_list.h \
                  

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o

$(TARGET): $(TARGET).o
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TARGET).o : $(TARGET).cpp $(HEADER)
