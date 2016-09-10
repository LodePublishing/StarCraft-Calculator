CXX=g++
OBJ= src/scc22.o src/race.o src/settings.o src/soup.o src/io.o src/anarace.o
CXXFLAGS= -O3 -Wall
# -march=pentium4 -mcpu=pentium4 -ffast-math -pipe -funroll-loops -fforce-mem -malign-double -fforce-addr -fomit-frame-pointer
LIBS=
TARGET=scc22

all:  $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

clean: 
	@rm -f src/*.o
	@rm -vf $(TARGET)
	@echo "done."
