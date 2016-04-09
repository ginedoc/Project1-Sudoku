#include <iostream>
#include <cstdlib>

using namespace std;

#include "Sudoku.h"

/* for each elements, there should be 9 lights. The lights represent 
   the number. For example,if the number is 4, the lights for the 
   element will only have one light be up ( other will be turned off.)*/
bool light[81][9];
int lightbulb;	//for light[81][9]
int A[81];
int Ans = -1 ;

void Initialize(bool lgt[81][9]);
bool NoLight(bool lgt[81][9]);
void printLight(bool lgt[81][9]);
bool CheckRule(int*);
bool MaybeMat(bool *l,int a);
bool TwoLight(bool l[81][9]);
bool Equal(int a[81],int b[81]);
int getBackwardValid(int ,int *);
void CheckZeroAnswer(bool l[81][9],int a[81]);

void Sudoku::solve(){
	
	int i,j;
	int record_map[81];
	bool record_light[81][9];
	
	while(true){
		//solving skill
		Initialize(light);
		TurnOffOrigin(light,Sudoku::q);
		CheckSmlMatrix(light,Sudoku::q);
		CheckRow(light ,Sudoku::q);
		CheckCol(light,Sudoku::q);
		OnlyRemain(light,Sudoku::q);
		Refill(light,Sudoku::q);
		if(!Equal(A,q)){
			for(i=0;i<81;i++) A[i] = q[i];
		}
		if(Equal(A,q))	break;
	}

	
	for( i = 0 ;i < 81 ;i++ ){
		record_map[i] = Sudoku::q[i];
		A[i] = 0;
		for( j = 0 ; j < 9 ; j++ ) record_light[i][j] = light[i][j];
	}
	
	TraceBack(record_light,record_map);
	Ans = CheckSolution(record_light);
	

	if(Ans == 2){
		cout << "2" << endl;
		return;
	}
	else if(Ans == 0){
		cout << "0" << endl;
	}
	else if(Ans == 1){
		cout << "1" << endl;
		printOut(true,record_map);
		return;
	}
	else return;
}
int Sudoku::CheckSolution(bool l[81][9]){
	
	if(Ans==-1){	
		if(ExsistZero())	return 0;
		else if( Equal(q,A) && CheckMap())	return 1;
		else if( !Equal(q,A))	return 2;
		else 			return 3;
	}
	if(Ans = 0) return 0;
	if(Ans == 2 ) return 2;
}
bool Sudoku::ExsistZero(){
	int i;
	for(i=0;i<81;i++){
		if(q[i] == 0)return true;
	}
	return false;
}
bool Equal(int a[81],int b[81]){
	int i;
	int cnt = 0;
	for(i=0;i<81;i++){
		if(a[i] == b[i]) cnt++;
	}
	if( cnt == 81) return true;
	return false;

}
bool TwoLight(bool l[81][9]){
	int i,j;
	int cnt;
	for(i=0;i<81;i++){
		cnt = 0;
		for(j=0;j<9;j++){
			if(l[i][j] == true) cnt++;
		}
		if( cnt > 1 ) return true;
	}
	return false;
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
void Sudoku::TraceBack(bool l[81][9],int a[81]){
	int i,j;
	int tmp[81];
	int valid = getValid(-1);
	int POS[81];
	int lastPOS = 0;
	CheckZeroAnswer(l,a);
	if(Ans == -1){
		do{
			a[valid]++;
	
			if(a[valid] > 9){
				a[valid] = 0;
				if(lastPOS < 0)	valid = -1;
				else{
					valid = POS[--lastPOS];
				}
			}	 
			else{
				if(MaybeMat(l[valid],a[valid]) && CheckRule(a)){
					POS[lastPOS++] = valid;
					valid = getValid(valid);
					
				}
			}
		}while( valid >= 0 && valid < 81) ;
		
		for(i=0;i<81;i++){
			tmp[i] = q[i];
			q[i] = a[i];
			a[i] = tmp[i];
		}
		
		
		for(i=0;i<81;i++){
			if(a[i]==0) a[i] = 10;
		}
	
		valid = getBackwardValid(-1,a);
		lastPOS = 0;
		do{
			if(valid > 80)break;
			a[valid]--;
	
			if(a[valid] < 1){
				a[valid] = 10;
				if(lastPOS < 0) valid = -1;
				else {
					valid = POS[--lastPOS];
				}
			}
			else{
				if(MaybeMat(l[valid],a[valid]) && CheckRule(a)){
					POS[lastPOS++] = valid;
					valid = getBackwardValid(valid,a);
				}
			}
		}while( valid >=0 && valid < 81);
	
		for(i=0;i<81;i++) A[i] = a[i];
	}		
}
void CheckZeroAnswer(bool l[81][9],int a[81]){
	int i,j,k;
	int cnt = 0;
	int cnt1 = 0;
	int t = 0;
	for(i=0;i<81;i++){
		if(a[i] != 0) cnt++;
	}
	if(cnt < 17){
		for(i=0;i<81;i++){
			t = 0;
			for(j=0;j<9;j++){
				if(l[i][j] == true) t++;
			}
			if( t == 0 ){
				Ans = 0;
				return;
			}
		}
		Ans = 2;
		return;
	}
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			cnt = 0;
			cnt1 = 0;
			for(k=0;k<9;k++){
				if(a[j*9+k] == i+1) cnt++;
				if(a[k*9+j] == i+1) cnt1++;
			}
			if(cnt > 1 || cnt1 > 1){
				Ans = 0;
				return;
			}
		}
	}
}
int Sudoku::getValid(int blank){
	do{
		blank++;
	}while(blank < 81 && q[blank] > 0);
	return blank;
}
int getBackwardValid(int blank,int a[81]){
	do{
		blank++;
	}while(blank < 81 && a[blank] < 10);
	return blank;
}
bool MaybeMat(bool *l,int a){
	int i;
	if(l[a-1]==true)	return true;
	else return false;
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


bool Sudoku::CheckMap(){
	int i,j,k;

	int num = 0;

	for(i=0;i<81;i++){
		if(q[i] == 0)	return false;
	}

	for(i=0;i<9;i++){
		num = 0;
		for(j=0;j<9;j++){
			if(q[i*9+j]>0)	num = num + q[i*9+j];
		}
		if(num != 45) return false;	
	}

	for(i=0;i<9;i++){
		num = 0;
		for(j=0;j<9;j++){
			if(q[i*9+j]>0)num = num + q[j*9+i];
		}
		if(num != 45) return false;	
	}

	

	int n = 0;
	while( n<9 ){

		num = 0;

		if( n>=0 && n<3 ){
			for( i=0 ; i<3 ; i++){
			for(j=n*3 ; j<n*3+3 ; j++){
				if(q[i*9+j]>0)num = num + q[i*9+j];
			}
			}
		}
		else if( n>=3 && n<6 ){
			for( i=3 ; i<6 ; i++){
			for( j=(n-3)*3 ; j<(n-3)*3+3 ; j++){
				if(q[i*9+j]>0)num = num + q[i*9+j];
			}
			}
		}
		else{
			for( i=6 ; i<9 ; i++){
			for( j =(n-6)*3 ; j<(n-6)*3+3 ; j++){
				if(q[i*9+j]>0)num = num + q[i*9+j];
			}
			}
			
		}
		if(num != 45) return false;
		n++;
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
				cnt = 0;
				for( i=0 ; i<3 ; i++){
				for(j=n*3 ; j<n*3+3 ; j++){
						if(map[i*9+j]==k) cnt++;
				}
				if( cnt > 1 ) return false;
				}	
			}
		}
		else if( n>=3 && n<6 ){
			for(k=1;k<10;k++){
				cnt = 0;
				for( i=3 ; i<6 ; i++){
				for( j=(n-3)*3 ; j<(n-3)*3+3 ; j++){
						if(map[i*9+j]==k) cnt++;
				}
				if( cnt > 1 ) return false;
				}
			}
		}
		else{
			for(k=1;k<10;k++){
				cnt = 0;
				for( i=6 ; i<9 ; i++){
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

void Sudoku::printOut(bool Answ,int m[81]){
	int i,j;
	
	if(!Answ){
		for(i=0;i<81;i++){
			if(i%9==0) cout << endl;
			cout << m[i] << " ";
		}
	}
	else {
		for(i=0;i<81;i++){
			if(i%9==0) cout << endl;
			cout << Sudoku::q[i] << " ";
		}
	}
}
