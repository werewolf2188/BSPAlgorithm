#include dirs
ISDL2DIR = Libraries/SDL2/include
IIMGUIDIR = ImGUISDL
IUTILSDIR = Utils
ICLASSESDIR = Classes
ITESTDIR = Test
IBSPDIR = BSP

#libraries 
LSDL2DIR = Libraries/SDL2/lib
SDL2 = Libraries\\SDL2\\lib\\SDL2.dll

#obj dir
ODIR=obj

#dependencies
_DEPSCLASSES = GameLoop.h\
Graphics.h\
Keyboard.h\
Mouse.h\
PollingGameLoop.h\
RenderGraphics.h\
Sprite.h\
Structs.h\
SurfaceGraphics.h\
UI.h\
UserInputGameLoop.h\
Window.h
DEPSCLASSES = $(patsubst %, $(ICLASSESDIR)/%,$(_DEPSCLASSES))

_DEPSTEST = AbsoluteMap.h\
Boundaries.h\
PerspectiveTransformedMap.h\
Player.h\
TransformedMap.h\
Wall.h
DEPSTEST = $(patsubst %, $(ITESTDIR)/%,$(_DEPSTEST))

_DEPSBSP = Constants.h\
Loader.h\
MapSprite.h\
BSPMath.h\
Player.h\
Sector.h\
Vector.h
DEPSBSP = $(patsubst %, $(IBSPDIR)/%,$(_DEPSBSP))

DEPSQUEUE = $(IUTILSDIR)/CQueue.h

MAPCLEAR = map-clear.txt

#objects
_OBJS = Color.o\
PollingGameLoop.o\
RenderGraphics.o\
SurfaceGraphics.o\
UI.o\
UserInputGameLoop.o\
Window.o\
AbsoluteMap.o\
Boundaries.o\
PerspectiveTransformedMap.o\
PlayerTest.o\
TransformedMap.o\
Wall.o\
Loader.o\
MapSprite.o\
PlayerBSP.o\
Sector.o\
Vector.o\
main.o
OBJS = $(patsubst %, $(ODIR)/%,$(_OBJS))

#Compiler 
CC=clang++
CPPLANG = -g -O0 -x c++ -std=gnu++14 -stdlib=libstdc++ -pedantic -Wall
CFLAGS = -I$(ISDL2DIR) -I$(IIMGUIDIR)/include -I$(IUTILSDIR) -I$(ICLASSESDIR) -I$(ITESTDIR) -I$(IBSPDIR)
LDFLAGS = -L$(LSDL2DIR) -lmingw32 -lSDL2main -limguisdl -lSDL2 
COMPILERFLAGS = -w -Wl,-subsystem,windows

all: $(OBJS)
	$(CC) -g -O0 -o $(ODIR)/BSP.exe $^ $(LDFLAGS) $(COMPILERFLAGS)
	xcopy /Y $(MAPCLEAR) $(ODIR)$\
	xcopy /Y $(SDL2) $(ODIR)$\
	
$(ODIR)/%.o: $(ICLASSESDIR)/%.cpp $(DEPSCLASSES)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(ITESTDIR)/%.cpp $(DEPSTEST)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)	

$(ODIR)/%.o: $(IBSPDIR)/%.cpp $(DEPSBSP) $(DEPSQUEUE)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)	

$(ODIR)/PlayerTest.o: $(ITESTDIR)/Player.cpp $(DEPSTEST)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)	

$(ODIR)/PlayerBSP.o: $(IBSPDIR)/Player.cpp $(DEPSBSP) $(DEPSQUEUE)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)	

$(ODIR)/main.o: main.cpp $(DEPSCLASSES) $(DEPSTEST) $(DEPSBSP) $(DEPSQUEUE)
	$(CC) $(CPPLANG) -c -o $@ $< $(CFLAGS)
	
$(OBJS): | $(ODIR)

$(ODIR): 
	mkdir $(ODIR)

.PHONY: clean

clean:
	del /Q $(ODIR)\*.*
	rmdir $(ODIR)