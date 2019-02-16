INCLUDE_PATH=/home1/ugrads/marsene3/include
LIBRARY_PATH=/home1/ugrads/marsene3/lib

build: main.h app.h imgui.h font.h main.cpp app.cpp imgui.cpp font.cpp
	@g++ -g -std=c++11 -Wl,-rpath-link,./ *.cpp -o build/app -I${INCLUDE_PATH} -L${LIBRARY_PATH} -lSDL2

run: build/app
	@env LD_LIBRARY_PATH=/home1/ugrads/marsene3/lib build/app