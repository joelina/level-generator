CXX = g++

SDL_LIB = -L/usr/local/lib -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = level-generator

all: $(EXE)

$(EXE): main.o
	$(CXX) $< $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)

