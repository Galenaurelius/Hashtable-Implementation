# Zuhayr Choudhury (zmc8tk)

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-O2
DEBUG=
OBJECTS=hashTable.o timer.o wordPuzzle.o

wordPuzzle: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS)

hashTable.o: hashTable.cpp hashTable.h
timer.o: timer.cpp timer.h
wordPuzzle.o: wordPuzzle.cpp hashTable.h timer.h


.PHONY: clean
clean:
	-rm -f *.o *~ a.out
