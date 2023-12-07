OBJECT_SRC=$(foreach file, $(shell ls *.c), $(shell basename $(file) .c ).o )
FLAGS=--std=c99 -O2 -Wall


shiruku: $(OBJECT_SRC)
	cc $(FLAGS) -o $@ $^


%.o: %.c
	cc $(FLAGS) -c $<

clean:
	find . -type f -name "shiruku" -delete
	find . -type f -name '*.o' -delete