#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "Sudoku.h"

using namespace std;

Sudoku::Sudoku(){
	int i;
	for(i=0;i<81;i++){
		Sudoku::q[i]=0;
	}
}

void Sudoku::giveQuestion(){
	int i,j;
	ofstream output;
/*  	int matrix[9][9]={{5,3,0,0,7,0,0,0,0},
			  {6,0,0,1,9,5,0,0,0},
			  {0,9,8,0,0,0,0,6,0},
			  {8,0,0,0,6,0,0,0,3},
			  {4,0,0,8,0,3,0,0,1},
			  {7,0,0,0,2,0,0,0,6},
			  {0,6,0,0,0,0,2,8,0},
			  {0,0,0,4,1,9,0,0,5},
			  {0,0,0,0,8,0,0,7,9}};
*/  	
	int matrix[9][9]={{8,0,0,0,0,0,0,0,0},
			  {0,0,3,6,0,0,0,0,0},
			  {0,7,0,0,9,0,2,0,0},
			  {0,5,0,0,0,7,0,0,0},
			  {0,0,0,0,4,5,7,0,0},
			  {0,0,0,1,0,0,0,3,0},
			  {0,0,1,0,0,0,0,6,8},
			  {0,0,8,5,0,0,0,1,0},
			  {0,9,0,0,0,0,4,0,0}};
   
	//open output question in txt
	output.open("F74046153.txt",ios::out|ios::trunc);
	if(!output){
		cerr << "failure:open file" << endl;
		exit(1);
	}

	//print the question to output
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			output << matrix[i][j] << " ";
		}
		output << endl;
	}
}

//read sudoku in
void Sudoku::readIn(){
	int i;

	i=0;
	
	while( i < 81 ){
		cin >> Sudoku::q[i] ;
		map[i] = Sudoku::q[i];
		i++;	
	}
	
}

void Sudoku::changeNum(int a,int b){
	int i,j;

	//check & change
	
	if( a<=0 || b<=0 || a>9 || b>9 ){
		cerr << "usage: 1 <= (a,b) <= 9" << endl;
	}
	else{
		for(i=0;i<81;i++){
			if	(q[i] == a)	q[i] = b;
			else if	(q[i] == b)	q[i] = a;
			else continue;
		}
	}

}

void Sudoku::changeRow(int a,int b){
	int i;
	int tmp;

	//check & change [ a row <-> b row ]
	
	if( a<0 || b<0 || a>2 || b>2 ){
		cerr << "usage: 1 <= (a,b) <= 2" << endl;
		exit(1);
	}
	else{
		for( i=0;i<27;i++ ){
			tmp = q[a * 27 + i];
			q[a * 27 + i] = q[b * 27 + i];
			q[b * 27 + i] = tmp;
		}
	}
}

void Sudoku::changeCol(int a,int b){
	int i,j;
	int tmp;
	
	//check & change [ a column <-> b column ]

	if( a<0 || b<0 || a>2 || b>2 ){
		cerr << "usage: 1 <= (a,b) <=2" << endl;
		exit(1);
	}
	else{
		for( i=0;i<27;i++ ){
			tmp = q[ i%3 + a*3 + (i/3)*9 ];
			q[ i%3 + a*3 + (i/3)*9 ] = q[ i%3 + b*3 + (i/3)*9 ];
			q[ i%3 + b*3 + (i/3)*9 ] = tmp;
		}	 
	}
	
}

void Sudoku::rotate(int n){
	int i,j;
	
	int tmp[81];

	while(n>0){
		for( i=0;i<9;i++ ){
			for( j=0;j<9;j++ ){
				tmp[j*9+(8-i)] = q[i*9+j];
			}		
		}
		for(i=0;i<81;i++){
			q[i] = tmp[i];
		}
		n--;
	}
}
void Sudoku::flip(int n){
	int i,j;

	int tmp[81];

	if( n<0 || n>1){
		cerr << "usage: 0 <= n <= 1" << endl;
		exit(1);
	}
	else{
		//vertical
		if( n==0 ){
			for( i=0;i<9;i++){
				for( j=0;j<9;j++){
					tmp[i*9+j] = q[(8-i)*9+j];
				}
			}
		}
		//horizontal
		else{
			for( i=0;i<9;i++){
				for(j=0;j<9;j++){
					tmp[i*9+j] = q[i*9+(8-j)];
				}
			}
		}
		for( i=0;i<81;i++ ){
			q[i] = tmp[i];
		}
	}
}

void Sudoku::transform(){
	readIn();
	change();
	printOut(false,q);
}

void Sudoku::change(){
	srand(time(NULL));
	Sudoku::changeNum(rand()%9+1,rand()%9+1);
	Sudoku::changeRow(rand()%3,rand()%3);
	Sudoku::changeCol(rand()%3,rand()%3);
	Sudoku::rotate(rand()%4+1);
	Sudoku::flip(rand()%2);
}

