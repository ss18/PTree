CC=g++
OBJ = main.o ptree.o panalyzer.o ptreecreator.o test.o

ptree: $(OBJ)
	$(CC) -o $@ $^

all:ptree

clean:
	rm *.o ptree