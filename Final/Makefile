EXEC = chess
OBJECTS = main.o bishop.o board.o difficulty1.o difficulty2.o difficulty3.o difficulty4.o window.o game.o human.o king.o knight.o move.o pawn.o player.o queen.o rook.o square.o textdisplay.o piece.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	g++ -Wall -MMD ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
