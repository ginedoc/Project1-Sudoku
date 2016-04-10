Project1:	Sudoku.o main.o 
	g++ -o Project1 Sudoku.o main.o 
Sudoku.o:	Sudoku.h Sudoku.cpp 
	g++ -g -c Sudoku.cpp
main.o:	main.cpp Sudoku.h
	g++ -g -c main.cpp

clean:
	rm main.o Sudoku.o Sudoku_solve.o
