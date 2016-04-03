#include <iostream>
#include <cstdlib>

using namespace std;

#include "Sudoku.h"

/* for each elements, there should be 9 lights. The lights represent 
   the number. For example,if the number is 4, the lights for the 
   element will only have one light be up ( other will be turned off.)*/
bool light[81][9];
int lightbulb;	//for light[81][9]
int Ans = 0 ;

void Initialize(bool lgt[81][9]);
bool NoLight(bool lgt[81][9]);
void printLight(bool lgt[81][9]);
bool CheckRule(int*);

void Sudoku::solve(){
	
	int i,j;
	int record_map[81];
	bool record_light[81][9];

	//solving skill
	Initialize(light);
	TurnOffOrigin(light,Sudoku::q);
	CheckSmlMatrix(light,Sudoku::q);
	CheckRow(light ,Sudoku::q);
	CheckCol(light,Sudoku::q);
	OnlyRemain(light,Sudoku::q);
	Refill(light,Sudoku::q);

	for( i = 0 ;i < 81 ;i++ ){
		record_map[i] = Sudoku::q[i];
		for( j = 0 ; j < 9 ; j++ ) record_light[i][j] = light[i][j];
	}
	
	TraceBack(0,record_light,record_map);

	if(Ans == 0 || Ans == 2){
		cout << "2" << endl;
//		cout << "Ans = " << Ans << endl;
//		printOut(true);
		return;
	}
	else{
		cout << "1" << endl;
//		cout << "Ans = " << Ans << endl;
		printOut(true);
		return;
	}
}

void Initialize(bool lgt[81][9]){
	int i,j;
	for(i=0;i<81;i++){
		for(j=0;j<9;j++){
			lgt[i][j] = true;
		}
	}
}

void Sudoku::TurnOffOrigin(bool lgt[81][9], int a[81]){
	
	int i,j;

	for(i=0;i<81;i++){
		if( a[i] !=  0){
			lightbulb = a[i] - 1;
			for(j=0;j<9;j++){
				if((lightbulb) == j) lgt[i][j] = true;
				else{ 
					lgt[i][j] = false;
				}
			}
		}
		else continue;
	}

}
int A[81];
void Sudoku::TraceBack(int n,bool l[81][9],int a[81]){
	int i,j,k;
	int cnt;
	int tmp[81];
	bool r[81][9];
	
//	cout << "n = " << n << endl;
//	for(i=0;i<81;i++){
//		if(i%9==0) cout << endl;
//		cout << a[i] << " ";
//	}
//	cout << endl;


	if( CheckMap(a)){
		cout << "test1\n";
		Ans++;
		for( i=0;i<81;i++ ) q[i] = a[i];
		
	//	printOut(false);

		if( Ans == 1 ){

		
			for(i=0;i<81;i++){
				cnt = 0;
				for(j=0;j<9;j++){
					if(light[i][j] == true) cnt++;
				}
				if(cnt > 1){
					for(j=0;j<9;j++){
						if(light[i][j] == true ) light[i][j] = false;
						break;
					}
					for(j=0;j<81;j++){
						a[j] = 0;
						for(k=0;j<9;k++){
							l[j][k] = light[j][k];
						}
					}
					Refill(l,a);
					TraceBack(0,l,a);
				}
			}
		}
		if( Ans == 2 ) return;

		

	}	
	if( NoLight(l)){

		cout << "test2\n";

		for(i=0;i<81;i++){
		a[i] = q[i];
		for(j=0;j<9;j++){
			l[i][j] = light[i][j];
		}
		}
		for(i=0;i<9;i++){
			if(l[n-1][i]==true){
				l[n-1][i]=false;
				break;
			}
		}

		TraceBack(0,l,a);
	}
	if( n < 0 ) return;
	if(CheckRule(a)){

		for( i = 0 ; i< 9 ;i++ ){
			if( l[n][i] == true ){
	
				a[n] = i+1;
				for(j=0;j<81;j++){
				for(k=0;k<9;k++){
					r[j][k] = l[j][k];
				}
				}
	
				TurnOffOrigin(l,a);
				CheckSmlMatrix(l,a);
				CheckRow(l,a);
				CheckCol(l,a);
				OnlyRemain(l,a);
				Refill(l,a);
			
				if(NoLight(l)){
	
					cout << "No Light" << endl;
	
					for(j=0;j<9;j++){
						l[n][j] = r[n][j];
					}
					for(j=0;j<9;j++){
						if(l[n][i]==true){ 
							l[n][i] = false;
							break;
						}
					}
				TraceBack(n,l,a);
				}

		//		printLight(l);
			
				TraceBack(n+1,l,a);
			}
		}
	}
}
bool NoLight(bool lgt[81][9]){
	int i,j;
	int cnt;
	for(i=0;i<81;i++){
		cnt = 0;
		for(j=0;j<9;j++){
			if(lgt[i][j]) cnt++;
		}
		if( cnt == 0 ) {
			return true;
		}
	}
	return false;

}
void printLight(bool a[81][9]){
	int i,j;
	cout << "================" << endl;
	for(i = 0 ;i < 81 ; i++ ) {
		if( i%9==0) cout << endl;
		for( j =0;j<9;j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void Sudoku::CheckSmlMatrix(bool lgt[81][9],int b[81]){
	int n = 0;
	int tmp[9];
	int i,j,k;
	int a;

	while( n<9 ){
		
		a=0;

		if( (n>=0) && (n<3) ){

			for(i=0;i<3;i++){
				for(j=3*n;j<3*n+3;j++){
					tmp[a++] = b[i*9+j];
				}
			}	

			//turn off the light
			for(a=0;a<9;a++){
				for(i=0;i<3;i++){
					for(j=n*3;j<n*3+3;j++){
	
						lightbulb = tmp[a]-1;

						if((b[i*9+j] != tmp[a]) && (tmp[a] != 0))	lgt[i*9+j][lightbulb] = false;
						else continue;
					}
				}
			}
		}
		
		else if( (n>=3) && (n<6)){
		
			for(i = 3 ; i < 6 ; i++){
				for(j = n*3-9 ; j < n*3-6 ; j++){	
					tmp[a++] = b[i*9+j];
				}
			}

			//turn off the light
			for(a=0;a<9;a++){
				for(i = 3 ; i < 6 ; i++){
					for(j = n*3-9 ;j < n*3-6 ; j++ ){			
								
						lightbulb = tmp[a]-1;	
	
						if((b[i*9+j] != tmp[a]) && (tmp[a] != 0))	lgt[i*9+j][lightbulb] = false;
						else continue;
					}
				}	
			}
		}
		
		else{
			for(i = 6 ; i< 9 ; i++){
				for(j = n*3-18;j < n*3-15 ; j++){	
					tmp[a++] = b[i*9+j];
				}
			}
	
			//turn off the light
			for(a=0;a<9;a++){
				for(i = 6 ; i < 9 ; i++){
					for(j = n*3-18;j < n*3-15 ; j++){			
							
						lightbulb = tmp[a]-1;	
	
						if((b[i*9+j] != tmp[a]) && (tmp[a] != 0))	lgt[i*9+j][lightbulb] = false;
						else continue;
					}
				}	
			}
		}
		n++;
	}
}

void Sudoku::CheckRow(bool lgt[81][9], int a[81]){
	int i,j;
	int n = 0;

	while(n<9){
		for(i=0;i<9;i++){
			lightbulb = a[n*9+i];

			for(j=0;j<9;j++){
				if((lightbulb != a[n*9+j]) && (lightbulb != 0) && (i != j))	lgt[n*9+j][lightbulb-1] = false;
			}
		}
		
		n++;
	}
}

void Sudoku::CheckCol(bool lgt[81][9], int a[81]){
	int i,j;
	int n = 0;

	while(n < 9){
		for(i=0;i<9;i++){
			lightbulb = a[i*9+n];

			for(j=0;j<9;j++){
				if((lightbulb != a[j*9+n]) && (lightbulb != 0) && (i != j))	lgt[j*9+n][lightbulb-1] = false;
			}
		}
		n++;
	}
}

void Sudoku::Refill(bool lgt[81][9], int a[81]){
	int i,j;
	int count = 0;
	int tmp;

	for(i=0;i<81;i++){
		
		count = 0;

		for(j=0;j<9;j++){
			if(lgt[i][j] != 0 ){
				count++;
				tmp = j + 1;
				if(count > 1 ) break;
			}
		}
		if( count == 1 ) a[i] = tmp;
	}
	
}

void Sudoku::OnlyRemain(bool lgt[81][9],int a[81]){
	
	int i,j,k;
	int n;
	int count = 0;
	int tmp;

	//Small Matrix
	n = 0;
	while( n<9 ){
		if( n>=0 && n<3 ){
			
			for( k=0 ; k<9 ; k++){

				count = 0;

				for( i=0 ; i<3 ; i++){
					for(j=n*3 ; j<n*3+3 ; j++){
						if(lgt[i*9+j][k] == true){
							count++;
							tmp = i*9+j;
						}
						if(count >=2 )	break;
					}
				}
				if(count == 1){
					for(i=0;i<9;i++)	lgt[tmp][i] = false;
					lgt[tmp][k] = true;
				}
			}
		}
		else if( n>=3 && n<6 ){

			for( k=0 ; k<9 ; k++){

				count = 0;

				for( i=3 ; i<6 ; i++){
					for( j=(n-3)*3 ; j<(n-3)*3+3 ; j++){
						if(lgt[i*9+j][k] == true){
							count++;
							tmp = i*9+j;
						}
						if(count >= 2)	break;
					}
				}

				if(count == 1){
					for(i=0 ; i<9 ; i++)	lgt[tmp][i] = false;
					lgt[tmp][k] = true;
				}
			}
		}
		else{
			for(k=0 ; k<9 ; k++){

				count = 0;

				for( i=6 ; i<9 ; i++){
					for( j =(n-6)*3 ; j<(n-6)*3+3 ; j++){
						if(lgt[i*9+j][k] == true){
							count++;
							tmp = i*9+j;
						}
						if(count >= 2)	break;
					}
				}
				if(count == 1){
					for(i=0 ; i<9 ; i++)	lgt[tmp][i] = false;
					lgt[tmp][k] = true;
				}
			}
		}
		
		n++;
	}
	
	//Row
	n = 0;
	
	while( n < 9 ){
		for(i=0;i<9;i++){

			count = 0;

			for( j=0 ; j<9 ; j++){
				if(lgt[n*9+j][i] == true){
					count++;
					tmp = n*9 + j;
				}
				if(count >= 2)	break;
			}

			if(count == 1){
				for( j=0 ; j<9 ; j++)	lgt[tmp][j] = false;
				lgt[tmp][i] = true;
			}
		}

		n++;
	}

	//Column
	n = 0;

	while( n < 9 ){
		for(i=0 ; i<9 ; i++){
			
			count = 0;

			for( j=0 ; j<9 ; j++){
				if(lgt[j*9+n][i] == true){
					count++;
					tmp = j*9 + n;
				}
				if(count >= 2)	break;
			}

			if(count == 1){
				for( j=0 ; j<9 ; j++)	lgt[tmp][j] = false;
				lgt[tmp][i] = true;
			}
		}
		n++;
	}

}


bool Sudoku::CheckMap(int map[81]){
	int i,j,k;

	int num = 0;

	for(i=0;i<81;i++){
		[
	}
	

	int n = 0;
	while( n<9 ){
		if( n>=0 && n<3 ){
			for(k=1;k<10;k++){
				cnt = 0;
				for( i=0 ; i<3 ; i++){
				for(j=n*3 ; j<n*3+3 ; j++){
						if(map[i*9+j]==k){
							l3[k-1]++;
							cnt++;
						}
				}
				}
				if(cnt !=  1) return false;
			}
		}
		else if( n>=3 && n<6 ){
			for(k=1;k<10;k++){
				cnt = 0;
				for( i=3 ; i<6 ; i++){
				for( j=(n-3)*3 ; j<(n-3)*3+3 ; j++){
						if(map[i*9+j]==k){
							l3[k-1]++;
							cnt++;
						}
				}
				}
				if( cnt != 1 ) return false;
			}
		}
		else{
			for(k=1;k<10;k++){
				cnt = 0;
				for( i=6 ; i<9 ; i++){
				for( j =(n-6)*3 ; j<(n-6)*3+3 ; j++){
						if(map[i*9+j]==k){
							l3[k-1]++;
							cnt++;
						}
				}
				}
				if( cnt != 1 ) return false;
			}
			
		}
		n++;
	}
	
	for( i =0 ; i< 9 ; i++ ){
		if( l1[i] != 9 || l2[i] != 9 || l3[i] != 9 ) return false;
	}
	return true;

}
bool CheckRule(int map[81]){
	int i,j,k;
	int cnt;
	for(k=0;k<9;k++){
		for(i=0;i<9;i++){
		cnt = 0;
		for(j=0;j<9;j++){
			if(map[i*9+j] == k+1) cnt++;
		}
		if( cnt > 1) return false;
		}
	}
	for(k=0;k<9;k++){
		for(i=0;i<9;i++){
		cnt = 0;
		for(j=0;j<9;j++){
			if(map[j*9+i] == k+1) cnt++;
		}
		if( cnt > 1) return false;
		}
	}
	int n = 0;
	while( n<9 ){
		if( n>=0 && n<3 ){
			for(k=1;k<10;k++){	
				for( i=0 ; i<3 ; i++){
				cnt = 0;
				for(j=n*3 ; j<n*3+3 ; j++){
						if(map[i*9+j]==k) cnt++;
				}
				if( cnt > 1 ) return false;
				}	
			}
		}
		else if( n>=3 && n<6 ){
			for(k=1;k<10;k++){
				for( i=3 ; i<6 ; i++){
				cnt = 0;
				for( j=(n-3)*3 ; j<(n-3)*3+3 ; j++){
						if(map[i*9+j]==k) cnt++;
				}
				if( cnt > 1 ) return false;
				}
			}
		}
		else{
			for(k=1;k<10;k++){
				for( i=6 ; i<9 ; i++){
				cnt = 0;
				for( j =(n-6)*3 ; j<(n-6)*3+3 ; j++){
						if(map[i*9+j]==k) cnt++;
				}
				if( cnt > 1 ) return false;
				}
			}
			
		}
		n++;
	}
	
	return true;
}

void Sudoku::printOut(bool Ans){
	int i,j;
	
	if(!Ans){
		for(i=0;i<81;i++){
			if(i%9==0) cout << endl;
			cout << map[i] << " ";
		}
	}
	else {
		for(i=0;i<81;i++){
			if(i%9==0) cout << endl;
			cout << Sudoku::q[i] << " ";
		}
	}
}
