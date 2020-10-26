EXENAME = main

CXX = clang++
CXXFLAGS = -std=c++11 -g -O0 -Wall -Wextra

all : $(EXENAME)

$(EXENAME): main.cpp tree.o
	$(CXX) $(CXXFLAGS) main.cpp tree.o -o $(EXENAME)

bst.o: tree.h tree.cpp
	$(CXX) $(CXXFLAGS) -c tree.cpp

.PHONY: clean
clean:
	rm -f *.o $(EXENAME)