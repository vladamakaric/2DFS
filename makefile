SRC = $(wildcard src/*.cpp)
LIB = -lfltk -lfltk_gl -lGL -lGLU


all: 
	g++ -std=c++11 $(SRC) -o f2d $(LIB) 

clean:
	@echo Cleaning up...
	@rm f2d
	@echo Done.
