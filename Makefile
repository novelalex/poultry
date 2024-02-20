CC=gcc
CFLAGS=-Wall -Wold-style-definition -std=c11 -pedantic -I"C:/GCCDev/SDL2/include" -L"C:/GCCDev/SDL2/lib"
LIBS=-lmingw32 -lSDL2main -lSDL2

all:
	$(CC) $(CFLAGS) -o main src/main.c $(LIBS)