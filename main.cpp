#include <iostream>
#include <cstdlib>

using namespace std;

#include "Sudoku.h"


int main(){

	Sudoku ss;

	ss.giveQuestion();
	cout << endl;

	ss.readIn();
	cout << endl;
	
	ss.transform();
	cout << endl;

	ss.solve();
	cout << endl;
}
