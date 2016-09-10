CXX=g++
OBJ= src/io.o src/scc24.o src/race.o src/anarace.o src/soup.o src/settings.o
CXXFLAGS= -ggdb
#-O4 -march=pentium4 -mcpu=pentium4 -ffast-math -pipe -funroll-loops -fforce-mem -malign-double -fforce-addr -fomit-frame-pointer
LIBS=
TARGET=scc24

all:  $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

clean: 
	@rm -f src/*.o
	@rm -vf $(TARGET)
	@echo "done."
