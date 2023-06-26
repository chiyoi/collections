.PHONY = clean run_example example_heap example_map example_slice example

C          := clang
C_STD      := c89

LD := ld

TARGET := $(CURDIR)/target
OBJ    := collections.o

C_FLAGS = -std=$(C_STD) -fsanitize=address -Wall
CC      = $(C) $(C_FLAGS)

target: $(OBJ) heap/heap.h map/map.h slice/slice.h
	rm -rf target
	mkdir target
	mkdir target/include
	cp heap/heap.h map/map.h slice/slice.h target/include
	mkdir target/lib
	mv $(OBJ) target/lib

$(OBJ): heap.o map.o
	$(LD) -o $(OBJ) -r heap.o map.o
	rm -f heap.o map.o

heap.o: heap/heap.c
	$(CC) -c -o heap.o heap/heap.c

map.o: map/map.c
	$(CC) -c -o map.o map/map.c

clean:
	rm -rf target
	rm -f $(OBJ) heap.o map.o

run_example: a.out
	./a.out
	rm -f a.out

example_slice: slice/example.c slice/slice.h
	$(CC) -I./slice slice/example.c
	@make run_example

example_map: map/example.c map/map.c
	$(CC) map/example.c
	@make run_example

example_heap: heap/example.c heap/heap.c
	$(CC) heap/example.c
	@make run_example

example: example.c target
	$(CC) -I$(TARGET)/include target/lib/$(OBJ) example.c 
	@make run_example
