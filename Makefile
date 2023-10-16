CC=gcc
CFLAGS=-Wall -g -O0
LDFLAGS=
EXE=driver
SRC=main.c perceptron.c
OBJ=$(SRC:.c=.o)

.PHONY: run
run: $(EXE)
	@echo "==========Running=========="
	./$(EXE) train.dat test.dat

$(EXE): $(OBJ)
	@echo "==========Linking=========="
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c perceptron.o perceptron.h
	@echo "==========Compiling=========="
	$(CC) $(CFLAGS) -c -o $@ $<

perceptron.o: perceptron.c perceptron.h
	@echo "==========Compiling=========="
	$(CC) $(CFLAGS) -c -o $@ $<

perceptron.h:

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ)
