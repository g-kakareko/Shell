CC = gcc
FILES = proj1.c 
OUT_EXE = hw1

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core
rebuild: clean build


