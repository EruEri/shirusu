OBJECT_SRC=$(foreach file, $(shell ls src/*.c), src/$(shell basename $(file) .c ).o )
FLAGS=-std=c99 -O2 -Wall
DEBUG=
TARGET=shirusu
CC=cc


$(TARGET): $(OBJECT_SRC)
	$(CC) $(FLAGS) $(DEBUG) -o $@ $^

src/%.o: src/%.c
	$(CC) $(FLAGS) $(DEBUG) -c -o $@ $<

clean:
	find . -type f -name "$(TARGET)" -delete
	find . -type f -name '*.o' -delete
