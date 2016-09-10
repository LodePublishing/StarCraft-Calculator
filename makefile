CXX=g++
OBJ= scc.o protoss.o terra.o zerg.o race.o settings.o 
CXXFLAGS= -O3 -Wall
LIBS=
TARGET=scc

all:  $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LIBS) 

clean: 
	@rm -f *.o
	@rm -vf $(TARGET)
	@echo "done."
