CXX=g++
OBJ= src/scc.o src/protoss.o src/terra.o src/zerg.o src/race.o src/settings.o 
CXXFLAGS= -O3
LIBS=
TARGET=scc

all:  $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS) 

clean: 
	@rm -f src/*.o
	@rm -vf $(TARGET)
	@echo "done."
