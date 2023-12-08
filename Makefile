OBJECT_SRC=$(foreach file, $(shell ls src/*.c), src/$(shell basename $(file) .c ).o )
FLAGS=-std=c99 -O2 -Wall
CC=cc

shiruku: $(OBJECT_SRC)
	$(CC) $(FLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	find . -type f -name "shiruku" -delete
	find . -type f -name '*.o' -delete