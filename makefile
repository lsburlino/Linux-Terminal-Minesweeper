OFILES = main.o minesweep.o board.o

minesweep: $(OFILES)
	gcc -g -o minesweep $(OFILES)

main.o: main.c minesweep.h
	gcc -c -g main.c

minesweep.o: minesweep.c board.h cell.h minesweep.h
	gcc -c -g minesweep.c

board.o: board.c board.h cell.h minesweep.h
	gcc -c -g board.c

clean:
	/bin/rm -f minesweep *.o
