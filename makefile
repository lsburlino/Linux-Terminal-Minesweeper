OFILES = main.o minesweep.o board.o

minesweep: $(OFILES)
	gcc -o minesweep $(OFILES)

main.o: main.c minesweep.h
	gcc -c main.c

minesweep.o: minesweep.c board.h cell.h minesweep.h
	gcc -c minesweep.c

board.o: board.c board.h cell.h minesweep.h
	gcc -c board.c

clean:
	/bin/rm -f minesweep *.o
