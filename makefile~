SRC = $(wildcard src/*.cpp)
LIB = -lGL -lGLU -lSDL -lSDLmain

all: 
	g++ -std=c++11 $(SRC) -o terrainExp $(LIB) 

clean:
	@echo Cleaning up...
	@rm flockSim
	@echo Done.


# CXX = g++ RM = rm -f
# CFLAGS = -Wall -g -std=c++11
# INCLUDES = -I../include
# LFLAGS = -L../lib
# LIBS = -lSDL2 
# SRCS = $(wildcard src/*.cpp)
# OBJS = $(subst .cpp,.o,$(SRCS))
# MAIN = prog
#
# all: $(MAIN)
#
# $(MAIN): $(OBJS)
# 	$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
#
# %.o: %.cpp
# 	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@
#
# depend: .depend
#
# #ovo parce koda koristi MM flag da generise zavisnosti za svaki .o file,
# #sve hedere koje poziva odgovarajuci .cpp fajl se generisu. 
# #$^ je automatska promenjiva, jednaka je svim zavisnostima
# .depend: $(SRCS)
# 	$(RM) ./.depend
# 	$(CXX) $(CFLAGS) $(INCLUDES) -MM $^ >./.depend
# 	
# clean: 
# 	$(RM) *.o
#
# include .depend
